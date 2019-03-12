/*
 * Matrix.h
 *
 *  Created on: Oct 9, 2018
 *      Author: sameriksson
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

namespace DeepNeural {

    class Matrix {
    public:
        Matrix();
        Matrix(long width, long height, double prepopulate);
        Matrix(std::vector<std::vector<double>> data);
        virtual ~Matrix();
        void saveMatrix(const std::string& filename );
        long getHeight();
        long getWidth();
        double getValue(long posx, long posy);
        void addRow(std::vector<double> row);
        void loadMatrix(const std::string& filename);
        bool ifExistsLoad(const std::string& filename);
        void padWith(const long width, long height, double value);
        double mean();
        double stdev();
        double average=0;
        double standarddev=0;
        double numberOfpoints=0;
        void setValue(long x, long y, double value);
        void addDerivativeRow(std::vector< double >  row);
        void initializeDerivative(long width, long height, double value);
        void setValueDerivative(long x, long y, double value);
        double getValueDerivative(long x, long y);
        Matrix getDerivative();
        void clearValues();
        void clearDerivativeValues();
        void invert(int max);
        double getMinimum();
        double getMax();
    private:
        std::vector< std::vector< double > > values;
        std::vector< std::vector< double > > derivative;
    };
} /* namespace DeepNeural */

#endif /* MATRIX_H_ */
