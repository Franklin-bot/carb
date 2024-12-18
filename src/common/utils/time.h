#pragma once

#include "date.h"
#include "cstdint"

inline uint64_t convertTime(const std::string& time){
    std::istringstream stream(time);

    date::sys_time<std::chrono::milliseconds> tTimePoint;
    date::from_stream(stream, "%Y-%m-%dT%H:%M:%S%Z", tTimePoint);

    uint64_t timestamp = tTimePoint.time_since_epoch().count();

    return timestamp;
}

 
