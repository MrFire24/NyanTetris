#include "deltaTime.h"

std::chrono::high_resolution_clock timer;

DeltaTime deltaTime;

DeltaTime::DeltaTime() {
    oldTime_ = timer.now();
    newTime_ = timer.now();
}


void DeltaTime::updateTime() {
    newTime_ = timer.now();
    value_ = std::chrono::duration_cast<std::chrono::milliseconds>(newTime_ - oldTime_).count() / 1000.f;
}

void DeltaTime::resetTime() {
    oldTime_ = newTime_;
    updateTime();
}

DeltaTime::operator float() const {
    return value_;
}