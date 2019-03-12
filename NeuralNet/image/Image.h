/*
 * Image.h
 *
 *  Created on: Oct 11, 2018
 *      Author: sameriksson
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
struct jpeg_error_mgr;

namespace DeepNeural {

class Image {
public:
    explicit Image( const std::string& fileName );
    Image( const Image& rhs );
    Image& operator=( const Image& ) = delete;
    Image( Image&& )                 = delete;
    Image& operator=( Image&& )      = delete;
	virtual ~Image();
    void save( const std::string& fileName, int quality = 95 ) const;
    void savePpm( const std::string& fileName ) const;
    size_t getHeight()    const { return height; }
    size_t getWidth()     const { return width;  }
    size_t getPixelSize() const { return pixelSize; }
    std::vector<uint8_t> getPixel( size_t x, size_t y ) const;
    uint8_t getLuminance( size_t x, size_t y ) const;
    std::vector<uint8_t> getAverage( size_t x, size_t y, size_t boxSize ) const;
    void shrink( size_t newWidth );
    void expand( size_t newWidth );
    void resize( size_t newWidth );
private:
    std::shared_ptr< ::jpeg_error_mgr > errorMgr;
    std::vector<std::vector<uint8_t> > bitmapData;
    size_t                            width;
    size_t                            height;
    size_t                            pixelSize;
    int                               colourSpace;
};

} /* namespace DeepNeural */

#endif /* IMAGE_H_ */
