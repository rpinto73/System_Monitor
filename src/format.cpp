#include <string>
#include <cmath>

#include "format.h"

// DONE: Complete this helper function


// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

std::string TwoDigits(int val){
    std::string twoDigits = "";
    if(val<10){
        twoDigits ="0";
        }
    twoDigits = twoDigits + std::to_string(val);
    return twoDigits;
}
std::string Format::ElapsedTime(long times) { 

    int h, m, R_h, R_m, s;

    h = floor(times/3600); //number of hours
    R_h = times%3600; //remainder in seconds

    m = floor(R_h/60); //number of min
    R_m = R_h%60; //remainder in seconds

    s = R_m; 

    return TwoDigits(h) + ":" + TwoDigits(m) + ":" + TwoDigits(s);
    }