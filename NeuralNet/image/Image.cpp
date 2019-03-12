/*
 * Image.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: sameriksson
 */

#include "Image.h"
#include "../externalheader/jpeglib.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace DeepNeural {

 Image::Image( const std::string& fileName ) {
	 auto dt = []( ::jpeg_decompress_struct *ds ){
		 ::jpeg_destroy_decompress( ds );
	 };
	 std::unique_ptr<::jpeg_decompress_struct, decltype(dt)> decompressInfo( new ::jpeg_decompress_struct, dt );
	 errorMgr = std::make_shared<::jpeg_error_mgr>();
	 auto fdt = []( FILE* fp ) {fclose( fp );};
	 std::unique_ptr<FILE, decltype(fdt)> infile(
			 fopen( fileName.c_str(), "rb" ), fdt);
	 if ( infile.get() == NULL ) {
		 throw std::runtime_error( "Could not open " + fileName );
	 }
	 decompressInfo->err = ::jpeg_std_error( errorMgr.get() );
	 errorMgr->error_exit = [](::j_common_ptr cinfo){
		 char jpegLastErrorMsg[JMSG_LENGTH_MAX];
		 ( *( cinfo->err->format_message ) )
				 ( cinfo, jpegLastErrorMsg );
		 throw std::runtime_error( jpegLastErrorMsg );
	 };
	 ::jpeg_create_decompress( decompressInfo.get() );
	 ::jpeg_stdio_src( decompressInfo.get(), infile.get() );
	 int rc = ::jpeg_read_header( decompressInfo.get(), TRUE );
	 if (rc != 1) {
		 throw std::runtime_error( "File does not seem to be a normal JPEG");
	 }
	    ::jpeg_start_decompress( decompressInfo.get() );
	    width       = decompressInfo->output_width;
	    height      = decompressInfo->output_height;
	    pixelSize   = decompressInfo->output_components;
	    colourSpace = decompressInfo->out_color_space;
	    size_t row_stride = width * pixelSize;
	    bitmapData.clear();
	    bitmapData.reserve( height );
	    while ( decompressInfo->output_scanline < height )
	    {
	        std::vector<uint8_t> vec(row_stride);
	        uint8_t* p = vec.data();
	        ::jpeg_read_scanlines( decompressInfo.get(), &p, 1 );
	        bitmapData.push_back( vec );
	    }
	    ::jpeg_finish_decompress( decompressInfo.get() );
 }

 Image::Image( const Image& rhs ) {
     errorMgr      = rhs.errorMgr;
     bitmapData    = rhs.bitmapData;
     width         = rhs.width;
     height        = rhs.height;
     pixelSize     = rhs.pixelSize;
     colourSpace   = rhs.colourSpace;
 }

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::save( const std::string& fileName, int quality ) const {
	if ( quality < 0 ) { quality = 0; }
    if ( quality > 100 ) { quality = 100; }
    FILE* outfile = fopen( fileName.c_str(), "wb" );
    if ( outfile == NULL ) {
    	throw std::runtime_error("Could not open " + fileName + " for writing");
    }
    auto dt = []( ::jpeg_compress_struct *cs ) {
    	::jpeg_destroy_compress( cs );
    };
    std::unique_ptr<::jpeg_compress_struct, decltype(dt)> compressInfo(
    		new ::jpeg_compress_struct, dt );
    ::jpeg_create_compress( compressInfo.get() );
    ::jpeg_stdio_dest( compressInfo.get(), outfile);
    compressInfo->image_width = width;
    compressInfo->image_height = height;
    compressInfo->input_components = pixelSize;
    compressInfo->in_color_space = static_cast<::J_COLOR_SPACE>( colourSpace );
    compressInfo->err = ::jpeg_std_error( errorMgr.get() );
    ::jpeg_set_defaults( compressInfo.get() );
    ::jpeg_set_quality( compressInfo.get(), quality, TRUE );
    ::jpeg_start_compress( compressInfo.get(), TRUE);
    for ( auto const& vecLine : bitmapData ){
    	::JSAMPROW rowPtr[1];
        rowPtr[0] = const_cast<::JSAMPROW>( vecLine.data() );
        ::jpeg_write_scanlines(
                    compressInfo.get(),
                    rowPtr,
                    1
                    );
    }
    ::jpeg_finish_compress( compressInfo.get() );
    fclose( outfile );
}

void Image::savePpm( const std::string& fileName ) const {
    std::ofstream ofs( fileName, std::ios::out | std::ios::binary );
    if ( ! ofs ) {
    	throw std::runtime_error("Could not open " + fileName + " for saving");
    }
    ofs << "P6 " << width << " " << height << " 255\n";
    for ( auto& v : bitmapData ) {
        ofs.write( reinterpret_cast<const char *>(v.data()), v.size() );
    }
    ofs.close();
}

std::vector<uint8_t> Image::getPixel( size_t x, size_t y ) const{
    if ( y >= bitmapData.size() ) {
        throw std::out_of_range( "Y value too large" );
    }
    if ( x >= bitmapData[0].size() / pixelSize ) {
        throw std::out_of_range( "X value too large" );
    }
    std::vector<uint8_t> vec;
    for ( size_t n = 0; n < pixelSize; ++n ) {
        vec.push_back( bitmapData[ y ][ x * pixelSize + n ] );
    }
    return vec;
}

uint8_t Image::getLuminance( size_t x, size_t y ) const {
    auto vec = getPixel( x, y );
    if ( vec.size() == 1 ) { return vec[0]; }
    if ( vec.size() == 3 ) { return static_cast<uint8_t>(
            ( vec[0] * 2 + vec[1] * 3 + vec[2] ) / 6);}
    return 0;
}

std::vector<uint8_t> Image::getAverage( size_t x, size_t y, size_t boxSize ) const {
    if ( boxSize > width ) {
        throw std::out_of_range( "Box size is greater than image width" );
    }
    if ( boxSize > height ) {
        throw std::out_of_range( "Box size is greater than image height" );
    }
    if ( x + boxSize  >= width ) {
        x = width - boxSize;
    }
    if ( y + boxSize >= height ) {
        y = height - boxSize;
    }
    size_t r{ 0 };
    size_t g{ 0 };
    size_t b{ 0 };
    for ( size_t row = y; row < y + boxSize; ++row ) {
        for ( size_t col = x; col < x + boxSize; ++col ) {
            auto vec = getPixel( col, row );
            r += vec[0];
            if ( vec.size() == 3 ) {
                g += vec[1];
                b += vec[2];
            }
        }
    }
    std::vector<uint8_t> retVec;
    r /= ( boxSize * boxSize );
    retVec.push_back( r );
    if ( pixelSize == 3 ) {
        g /= ( boxSize * boxSize );
        retVec.push_back( g );
        b /= ( boxSize * boxSize );
        retVec.push_back( b );
    }
    return retVec;
}

void Image::shrink( size_t newWidth )
{
    if ( newWidth >= width ) {
        return;
    }

    if ( newWidth == 0 ) {
        throw std::out_of_range( "New width cannot be zero" );
    }

    float scaleFactor = static_cast<float>(newWidth) / width;
    size_t newHeight = scaleFactor * height;
    std::vector<std::vector<uint8_t> > vecNewBitmap;
    vecNewBitmap.reserve( newHeight );

    std::vector<size_t> runningTotals( newWidth * pixelSize );
    std::vector<size_t> runningCounts( newWidth * pixelSize );
    size_t oldRow = 0;
    for ( size_t row = 0; row < height; ++row ) {
        for ( size_t col = 0; col < width * pixelSize; ++col ) {
            size_t idx = scaleFactor * col;
            runningTotals[ idx ] += bitmapData[row][col];
            ++runningCounts[ idx ];
        }
        if ( static_cast<size_t>( scaleFactor * row ) > oldRow ) {
            oldRow = scaleFactor * row;
            std::vector<uint8_t> newLine;
            newLine.reserve( newWidth * pixelSize );
            for ( size_t i = 0; i < newWidth * pixelSize; ++i ) {
                newLine.push_back( runningTotals[i] / runningCounts[i] );
                runningTotals[i] = 0;
                runningCounts[i] = 0;
            }
            vecNewBitmap.push_back( newLine );
        }
    }
    bitmapData = vecNewBitmap;
    height = bitmapData.size();
    width = bitmapData[0].size() / pixelSize;
}

void Image::expand( size_t newWidth )
{
    if ( newWidth <= width ) {
        return;
    }

    float scaleFactor = static_cast<float>(newWidth) / width;
    size_t newHeight = scaleFactor * height;
    std::vector<std::vector<uint8_t> > vecNewBitmap;
    vecNewBitmap.reserve( newHeight );

    for ( size_t row = 0; row < newHeight; ++row ) {
        size_t oldRow = row / scaleFactor;
        std::vector<uint8_t> vecNewLine( newWidth * pixelSize );
        for ( size_t col = 0; col < newWidth; ++col ) {
            size_t oldCol = col / scaleFactor;
            for ( size_t n = 0; n < pixelSize; ++n ) {
                vecNewLine[ col * pixelSize + n ] =
                    bitmapData[ oldRow ][ oldCol * pixelSize + n ];
            }
        }
        vecNewBitmap.push_back( vecNewLine );
    }
    bitmapData = vecNewBitmap;
    height = bitmapData.size();
    width = bitmapData[0].size() / pixelSize;
}

void Image::resize( size_t newWidth ) {
    if ( newWidth < width ) {
        shrink( newWidth );
    }
    else if ( newWidth > width ) {
        expand( newWidth );
    }
}

} /* namespace DeepNeural */
