#ifndef LINEAREQUATIONSSYSTEM_H_INCLUDED
#define LINEAREQUATIONSSYSTEM_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Matrix.h"

namespace NumericalCore{

template <typename T>
class LinearEquationsSystem{
public:
    LinearEquationsSystem(Matrix<T> systemMatrix);
    LinearEquationsSystem(std::vector<std::vector<T>> systemMatrix) : LinearEquationsSystem(Matrix<T>(systemMatrix)) { }
    LinearEquationsSystem(std::string systemMatrixString) : LinearEquationsSystem(Matrix<T>(systemMatrixString)) { }
    LinearEquationsSystem();
    Matrix<T>* getMatrix() { return &matrix; }
    int getEquationsNumber() { return equationsNumber; }
    std::vector<T> GaussJordan();

    std::string getFormattedMatrix(){ return matrix.toString(); }
    std::string getFormattedResult(std::string variableName, std::string separator, int precision, bool scientificNotation);
    std::string getFormattedResult();

    enum class Status{
        empty,
        solved,
        unsolved,
        wrongEquationsNumber,
        error
        //TODO:: more states
    };

private:
    Matrix<T> matrix;
    int equationsNumber;
    int constatntTermsColumn;
    std::vector<int> columnsOrder;
    std::vector<T> result;
    Status status = Status::empty;

    void replaceRows(int row1, int row2);
    void replaceColumns(int column1, int column2);
};

template <typename T>
LinearEquationsSystem<T>::LinearEquationsSystem(Matrix<T> systemMatrix){
    matrix = systemMatrix;
    equationsNumber = systemMatrix.getRowsNumber();
    constatntTermsColumn = systemMatrix.getColumnsNumber() - 1;

    columnsOrder.resize(constatntTermsColumn);
    for(long unsigned int i = 0; i < columnsOrder.size(); ++i){
        columnsOrder[i] = i;
    }

    result.resize(constatntTermsColumn);

    if(constatntTermsColumn == equationsNumber){
        status = Status::unsolved;
    }
    else{
        status = Status::wrongEquationsNumber;
    }
}

template <typename T>
LinearEquationsSystem<T>::LinearEquationsSystem(){
    status = Status::empty;
}

template <typename T>
std::vector<T> LinearEquationsSystem<T>::GaussJordan(){
    try{
        MatrixIndex maxElement;
        for(int i = 0; i < equationsNumber; ++i){
            maxElement = matrix.findMaxAbs( {i, i}, {equationsNumber - 1, equationsNumber - 1} );
            replaceRows(i, maxElement.row);
            replaceColumns(i, maxElement.column);
            matrix.divideRowByNumber(i, matrix.valueAt(i,i));
            for(int j = 0; j < equationsNumber; ++j){
                if(j == i){
                    continue;
                }
                matrix.addMultiplyOfRow(i, -1 * matrix.valueAt(j, i), j);
            }
        }

        for(int i = 0; i < columnsOrder.size(); ++i){
            result[columnsOrder[i]] = matrix.valueAt(i, constatntTermsColumn);
        }

        status = Status::solved;

        return result;
    }
    catch(...){
        status = Status::error;
        return {};
    }
}

template <typename T>
void LinearEquationsSystem<T>::replaceRows(int row1, int row2){
    matrix.replaceRows(row1, row2);
}

template <typename T>
void LinearEquationsSystem<T>::replaceColumns(int column1, int column2){
    matrix.replaceColumns(column1, column2);
    std::swap(columnsOrder[column1], columnsOrder[column2]);
}

template <typename T>
std::string LinearEquationsSystem<T>::getFormattedResult(std::string variableName, std::string separator, int precision, bool scientificNotation){
    if(status == Status::unsolved){
        GaussJordan();
    }

    if(status == Status::error || status == Status::empty){
        return "the equation cannot be solved";
    }
    else if(status == Status::wrongEquationsNumber){
        return "the equation cannot be solved: wrong number of rows/culumns";
    }

    std::stringstream ssresult;
    if(scientificNotation){
        ssresult << std::scientific;
    }
    else{
        ssresult << std::fixed;
    }
    ssresult << std::setprecision(precision);
    for(int i = 0; i < result.size(); ++i){
        ssresult << variableName << "[" << i << "] = " << result[i];
        if(i != result.size() - 1){
            ssresult << separator;
        }
    }
    return ssresult.str();

}

template <>
std::string LinearEquationsSystem<interval_arithmetic::Interval<long double>>::getFormattedResult(std::string variableName, std::string separator, int precision, bool scientificNotation);

template <typename T>
std::string LinearEquationsSystem<T>::getFormattedResult(){
    return getFormattedResult("x","\n", std::numeric_limits<T>::max_digits10, true);
}

template <>
std::string LinearEquationsSystem<interval_arithmetic::Interval<long double>>::getFormattedResult();

}

#endif // LINEAREQUATIONSSYSTEM_H_INCLUDED
