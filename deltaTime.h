#pragma once
#include <chrono>
#include <list>

extern std::chrono::high_resolution_clock timer;

class DeltaTime {
public:
    void updateTime();
    void resetTime();
    operator float() const;

    DeltaTime();
private:
    float value_ = 0.1f;
    std::chrono::steady_clock::time_point oldTime_, newTime_;
};

extern DeltaTime deltaTime;