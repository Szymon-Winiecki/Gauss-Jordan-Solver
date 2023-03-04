#include "LinearEquationsSystem.h"

namespace NumericalCore{

template <>
std::string LinearEquationsSystem<interval_arithmetic::Interval<long double>>::getFormattedResult(std::string variableName, std::string separator, int widthPrecision, bool scientificNotation){
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
    ssresult << std::setprecision(widthPrecision);
    for(int i = 0; i < result.size(); ++i){
        ssresult << variableName << "[" << i << "] = " << intervalToString(result[i], true, scientificNotation, widthPrecision);
        if(i != result.size() - 1){
            ssresult << separator;
        }
    }
    return ssresult.str();

}

template <>
std::string LinearEquationsSystem<interval_arithmetic::Interval<long double>>::getFormattedResult(){
    return getFormattedResult("x","\n", 1, true);
}


}
