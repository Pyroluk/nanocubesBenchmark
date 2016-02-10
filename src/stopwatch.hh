#pragma once

#include <chrono>

namespace stopwatch {
    
    //
    // Stopwatch
    //
    
    typedef int Milliseconds;
    struct Stopwatch
    {
        Stopwatch();
        void start();
        void stop();
        Milliseconds time();
        int timeInSeconds();
        
        
        bool started;
        std::chrono::time_point<std::chrono::system_clock> t0, t1;
    };
    
    //
    // StartStop: RAII
    //
    
    struct StartStop
    {
        StartStop(Stopwatch &stopwatch, Milliseconds &result);
        ~StartStop();
        
        Stopwatch &stopwatch;
        Milliseconds &result;
    };
    
    
    using Nanoseconds = int64_t;
    
    struct StartStop2
    {
        using clock_type      = std::chrono::high_resolution_clock;
        using time_point_type = clock_type::time_point;
        using duration_type   = std::chrono::nanoseconds;
        
        StartStop2(Nanoseconds &result);
        ~StartStop2();
        
        time_point_type t0;
        time_point_type t1;
        Nanoseconds &result;
    };
    
    
    
}
