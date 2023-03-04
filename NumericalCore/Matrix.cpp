#include "Matrix.h"

namespace NumericalCore{

std::string intervalToString(interval_arithmetic::Interval<long double> interval, bool width, bool scientificNotation, int precision){
    std::string left, right;
    interval.IEndsToStrings(left, right);
    std::stringstream intervalss;
    intervalss << "[" << left << ", " << right << "]";

    if(width){
        intervalss << ",\t width = ";
        if(scientificNotation){
            intervalss << std::scientific;
        }
        else{
            intervalss << std::fixed;
        }
        intervalss << std::setprecision(precision);
        intervalss << interval.GetWidth();
    }

    return intervalss.str();
}

std::string intervalToString(interval_arithmetic::Interval<long double> interval, bool width) {
     return intervalToString(interval, width, true, std::numeric_limits<long double>::max_digits10);
}

template <>
Matrix<interval_arithmetic::Interval<long double>>::Matrix(std::string matrixString, bool intervalInput){
     std::stringstream ssmatrix(matrixString);

    std::string rowString;
    int rowNumber = 0;
    int rowLength  = -1;

    while(std::getline(ssmatrix, rowString)){
        matrix.push_back({});
        std::stringstream ssrow(rowString);

        std::string elementString;
        size_t idx = 0;

        if(intervalInput){
            while(ssrow >> elementString){
                long double left, right;
                left = interval_arithmetic::LeftRead<long double>(elementString);
                if(ssrow >> elementString){
                    right = interval_arithmetic::RightRead<long double>(elementString);
                    matrix[rowNumber].push_back(interval_arithmetic::Interval<long double>(left,right));
                }
                else{
                    throw std::invalid_argument("odd number of numbers - intervals could not be created");
                }
            }
        }
        else{
            while(ssrow >> elementString){
                matrix[rowNumber].push_back(interval_arithmetic::IntRead<long double>(elementString));
            }
        }

        if(rowLength == -1){
            rowLength = matrix[rowNumber].size();
        }
        else if(matrix[rowNumber].size() != rowLength){
            throw std::invalid_argument("rows of different lengths");
        }

        rowNumber++;
    }

    rows = matrix.size();
    columns = rowLength;
}

template <>
Matrix<interval_arithmetic::Interval<long double>>::Matrix(std::string matrixString) : Matrix(matrixString, false) { }

template <>
void Matrix<interval_arithmetic::Interval<long double>>::multiplyColumnByNumber(int column, interval_arithmetic::Interval<long double> number){
    if(column < 0 || column >=  columns){
        throw std::out_of_range("try to access column outside the matrix");
    }
    if(intervalContains(number, 0.0L)){
        throw std::invalid_argument("divisor must not contain zero");
    }

    for(int r = 0; r < rows; ++r){
        matrix[r][column] = matrix[r][column] * number;
    }
}

template <>
void Matrix<interval_arithmetic::Interval<long double>>::divideRowByNumber(int row, interval_arithmetic::Interval<long double> divisor){
    if(row < 0 || row >=  rows){
        throw std::out_of_range("try to access row outside the matrix");
    }
    if(intervalContains(divisor, 0.0L)){
        throw std::invalid_argument("divisor must not contain zero");
    }

    for(int c = 0; c < columns; ++c){
        matrix[row][c] = matrix[row][c] / divisor;
    }
}

template <>
MatrixIndex Matrix<interval_arithmetic::Interval<long double>>::findMaxAbs(MatrixIndex upperLeftBoundsCorner, MatrixIndex bottomRightBoundsCorner){
    if(!indexValidation(upperLeftBoundsCorner) || !indexValidation(bottomRightBoundsCorner)){
        throw std::out_of_range("try to access index outside the matrix");
    }

    MatrixIndex maximumIndex = upperLeftBoundsCorner;
    long double maximum = -1.0L;
    for(int r = upperLeftBoundsCorner.row; r <= bottomRightBoundsCorner.row; ++r){
        for(int c = upperLeftBoundsCorner.column; c <= bottomRightBoundsCorner.column; ++c){
            long double distanceFromZero = std::min(std::abs(matrix[r][c].a), std::abs(matrix[r][c].b));
            if(intervalContains(matrix[r][c], 0.0L)){
                distanceFromZero *= -1;
            }
            if(distanceFromZero > maximum){
                maximum = distanceFromZero;
                maximumIndex = {r,c};
            }
        }
    }
    return maximumIndex;
}

template <>
std::string Matrix<interval_arithmetic::Interval<long double>>::toString(std::string columnSeparator, std::string rowSeparator, int precision, bool scientificNotation){
    std::stringstream ssresult;
    if(scientificNotation){
        ssresult << std::scientific;
    }
    else{
        ssresult << std::fixed;
    }
    ssresult << std::setprecision(precision);
    for(int r = 0; r < matrix.size(); ++r){
        for(int c = 0; c < matrix[r].size(); ++c){
            ssresult << intervalToString(matrix[r][c], false) << columnSeparator;
        }
        ssresult << rowSeparator;
    }
    return ssresult.str();
}

template <>
std::string Matrix<interval_arithmetic::Interval<long double>>::toString() {
     return toString("\t", "\n", std::numeric_limits<long double>::max_digits10, true);
}

}
