#pragma once
#include <chrono>
#include <list>

extern std::chrono::high_resolution_clock timer;

class DeltaTime {
private:
    float value_ = 0.1f;
    std::chrono::steady_clock::time_point oldTime_, newTime_;
public:
    DeltaTime();

    void updateTime();
    void resetTime();
    operator float() const;
};

extern DeltaTime deltaTime;