#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "Interval.h"

namespace NumericalCore{

template <typename T>
void printVector(std::vector<T>& vec){
    for(T elem : vec){
        std::cout << elem << " ";
    }
}

template <typename T>
bool intervalContains(interval_arithmetic::Interval<T> interval, T number){
    if(interval.a <= number && interval.b >= number){
        return true;
    }
    else{
        return false;
    }
}

std::string intervalToString(interval_arithmetic::Interval<long double> interval, bool width, bool scientificNotation, int precision);
std::string intervalToString(interval_arithmetic::Interval<long double> interval, bool width);

struct MatrixIndex{
    int row;
    int column;

    void print(){
        std::cout << "[" << row << ", " << column << "]";
    }
};

template <typename T>
class Matrix{
public:
    Matrix(std::vector<std::vector<T>> matrix);
    Matrix(int rows, int columns);
    Matrix() : Matrix(0, 0) { }
    Matrix(std::string matrixString, bool intervalInput);
    Matrix(std::string matrixString);

    T valueAt(MatrixIndex index);
    T valueAt(int r, int c);
    void setValue(MatrixIndex index, T value);
    void setValue(int r, int c, T value);

    int getRowsNumber() { return rows; }
    int getColumnsNumber() { return columns; }

    void replaceRows(int row1, int row2);
    void replaceColumns(int column1, int culumn2);
    void multiplyRowByNumber(int row, T number);
    void multiplyColumnByNumber(int column, T number);
    void divideRowByNumber(int row, T divisor);
    void divideColumnByNumber(int column, T divisor);
    void addMultiplyOfRow(int rowToAdd, T multiply, int addToRow);
    void addMultiplyOfColumn(int columnToAdd, T multiply, int addToColumn);
    void addDividedRow(int rowToAdd, T divisor, int addToRow);
    void addDividedColumn(int columnToAdd, T divisor, int addToColumn);

    bool indexValidation(MatrixIndex index);

    MatrixIndex findMaxAbs();
    MatrixIndex findMaxAbs(MatrixIndex upperLeftBoundsCorner, MatrixIndex bottomRightBoundsCorner);

    void print();
    std::string toString(std::string columnSeparator, std::string rowSeparator, int precision, bool scientificNotation);
    std::string toString();

private:
    int rows;
    int columns;
    std::vector<std::vector<T>> matrix;
};

template <typename T>
Matrix<T>::Matrix(int rows, int cols){
    this->rows = rows;
    this->columns = columns;

    this->matrix.resize(rows);
    for(long unsigned int i = 0; i < matrix.size(); ++i){
        matrix[i].resize(columns);
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> matrix){
    this->matrix = matrix;
    this->rows = matrix.size();

    int rowLength = matrix[0].size();
    for(int i = 1; i < matrix.size(); ++i){
        if(matrix[i].size() != rowLength){
            throw std::invalid_argument("rows of different lengths");
        }
    }

    this->columns = rowLength;
}

template <typename T>
Matrix<T>::Matrix(std::string matrixString){

    std::stringstream ssmatrix(matrixString);

    std::string rowString;
    int rowNumber = 0;
    int rowLength  = -1;

    while(std::getline(ssmatrix, rowString)){
        matrix.push_back({});
        std::stringstream ssrow(rowString);

        std::string elementString;
        long double element;
        size_t idx = 0;

        while(ssrow >> elementString){
            element = stold(elementString, &idx);
            if(elementString.length() - idx != 0){
                throw std::invalid_argument("non-number values");
            }
            matrix[rowNumber].push_back(element);
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

template <typename T>
Matrix<T>::Matrix(std::string matrixString, bool intervalInput) : Matrix(matrixString) { }

template <>
Matrix<interval_arithmetic::Interval<long double>>::Matrix(std::string matrixString, bool intervalInput);

template <>
Matrix<interval_arithmetic::Interval<long double>>::Matrix(std::string matrixString);

template <typename T>
bool Matrix<T>::indexValidation(MatrixIndex index){
    if(index.row < 0 || index.row >= rows || index.column < 0 || index.column >= columns){
        return false;
    }

    return true;
}

template <typename T>
T Matrix<T>::valueAt(MatrixIndex index){
    if(!indexValidation(index)){
        throw std::out_of_range("try to access index outside the matrix");
    }

    return matrix[index.row][index.column];
}

template <typename T>
T Matrix<T>::valueAt(int r, int c){
    return valueAt({r,c});
}

template <typename T>
void Matrix<T>::setValue(MatrixIndex index, T value){
    if(!indexValidation(index)){
        throw std::out_of_range("try to access index outside the matrix");
    }
    matrix[index.row][index.column] = value;
}

template <typename T>
void Matrix<T>::setValue(int r, int c, T value){
    setValue({r,c}, value);
}

template <typename T>
void Matrix<T>::replaceRows(int row1, int row2){
    if(row1 == row2){
        return;
    }

    if(row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows){
        throw std::out_of_range("try to access row outside the matrix");
    }

    std::swap(matrix[row1], matrix[row2]);
}

template <typename T>
void Matrix<T>::replaceColumns(int column1, int column2){
    if(column1 == column2){
        return;
    }

    if(column1 < 0 || column1 >= columns || column2 < 0 || column2 >= columns){
        throw std::out_of_range("try to access column outside the matrix");
    }

    for(int r = 0; r < rows; ++r){
        std::swap(matrix[r][column1], matrix[r][column2]);
    }
}

template <typename T>
void Matrix<T>::multiplyRowByNumber(int row, T number){
    if(row < 0 || row >=  rows){
        throw std::out_of_range("try to access row outside the matrix");
    }
    if(number == 0){
        throw std::invalid_argument("multiplier must be non-zero");
    }

    for(int c = 0; c < columns; ++c){
        matrix[row][c] *= number;
    }
}

template <typename T>
void Matrix<T>::multiplyColumnByNumber(int column, T number){
    if(column < 0 || column >=  columns){
        throw std::out_of_range("try to access column outside the matrix");
    }
    if(number == 0){
        throw std::invalid_argument("multiplier must be non-zero");
    }

    for(int r = 0; r < rows; ++r){
        matrix[r][column] *= number;
    }
}

template <>
void Matrix<interval_arithmetic::Interval<long double>>::multiplyColumnByNumber(int column, interval_arithmetic::Interval<long double> number);

template <typename T>
void Matrix<T>::divideRowByNumber(int row, T divisor){
    if(row < 0 || row >=  rows){
        throw std::out_of_range("try to access row outside the matrix");
    }
    if(divisor == 0){
        throw std::invalid_argument("divisor must be non-zero");
    }

    for(int c = 0; c < columns; ++c){
        matrix[row][c] /= divisor;
    }
}

template <>
void Matrix<interval_arithmetic::Interval<long double>>::divideRowByNumber(int row, interval_arithmetic::Interval<long double> divisor);

template <typename T>
void Matrix<T>::divideColumnByNumber(int column, T divisor){
    if(column < 0 || column >=  columns){
        throw std::out_of_range("try to access column outside the matrix");
    }
    if(divisor == 0){
        throw std::invalid_argument("divisor must be non-zero");
    }

    for(int r = 0; r < rows; ++r){
        matrix[r][column] /= divisor;
    }
}

template <typename T>
void Matrix<T>::addMultiplyOfRow(int rowToAdd, T multiply, int addToRow){
    if(rowToAdd < 0 || rowToAdd >= rows || addToRow < 0 || addToRow >= rows){
        throw std::out_of_range("try to access row outside the matrix");
    }

    for(int c =  0; c < columns; ++c){
        matrix[addToRow][c] = matrix[addToRow][c] + matrix[rowToAdd][c] * multiply;
    }
}

template <typename T>
void Matrix<T>::addMultiplyOfColumn(int columnToAdd, T multiply, int addToColumn){
    if(columnToAdd < 0 || columnToAdd >= columns || addToColumn < 0 || addToColumn >= columns){
        throw std::out_of_range("try to access column outside the matrix");
    }

    for(int r =  0; r < rows; ++r){
        matrix[r][addToColumn] += matrix[r][columnToAdd] * multiply;
    }
}

template <typename T>
void Matrix<T>::addDividedRow(int rowToAdd, T divisor, int addToRow){
    if(rowToAdd < 0 || rowToAdd >= rows || addToRow < 0 || addToRow >= rows){
        throw std::out_of_range("try to access row outside the matrix");
    }

    for(int c =  0; c < columns; ++c){
        matrix[addToRow][c] += matrix[rowToAdd][c] / divisor;
    }
}

template <typename T>
void Matrix<T>::addDividedColumn(int columnToAdd, T divisor, int addToColumn){
    if(columnToAdd < 0 || columnToAdd >= columns || addToColumn < 0 || addToColumn >= columns){
        throw std::out_of_range("try to access column outside the matrix");
    }

    for(int r =  0; r < rows; ++r){
        matrix[r][addToColumn] += matrix[r][columnToAdd] / divisor;
    }
}

template <typename T>
MatrixIndex Matrix<T>::findMaxAbs(MatrixIndex upperLeftBoundsCorner, MatrixIndex bottomRightBoundsCorner){
    if(!indexValidation(upperLeftBoundsCorner) || !indexValidation(bottomRightBoundsCorner)){
        throw std::out_of_range("try to access index outside the matrix");
    }

    MatrixIndex maximumIndex = {upperLeftBoundsCorner.row, upperLeftBoundsCorner.column};
    T maximum = valueAt(maximumIndex);
    for(int r = upperLeftBoundsCorner.row; r <= bottomRightBoundsCorner.row; ++r){
        for(int c = upperLeftBoundsCorner.column; c <= bottomRightBoundsCorner.column; ++c){
            if(std::abs(matrix[r][c]) > maximum){
                maximum = std::abs(matrix[r][c]);
                maximumIndex = {r,c};
            }
        }
    }
    return maximumIndex;
}

template <>
MatrixIndex Matrix<interval_arithmetic::Interval<long double>>::findMaxAbs(MatrixIndex upperLeftBoundsCorner, MatrixIndex bottomRightBoundsCorner);

template <typename T>
MatrixIndex Matrix<T>::findMaxAbs(){
    return findMaxAbs({0,0}, {rows-1, columns-1});
}

template <typename T>
std::string Matrix<T>::toString(std::string columnSeparator, std::string rowSeparator, int precision, bool scientificNotation){
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
            ssresult << matrix[r][c] << columnSeparator;
        }
        ssresult << rowSeparator;
    }
    return ssresult.str();
}

template <typename T>
std::string Matrix<T>::toString() {
     return toString("\t", "\n", std::numeric_limits<T>::max_digits10, true);
}

template <>
std::string Matrix<interval_arithmetic::Interval<long double>>::toString(std::string columnSeparator, std::string rowSeparator, int precision, bool scientificNotation);

template <>
std::string Matrix<interval_arithmetic::Interval<long double>>::toString();

template <typename T>
void Matrix<T>::print(){
    std::cout << toString();
}

}

#endif // MATRIX_H_INCLUDED
