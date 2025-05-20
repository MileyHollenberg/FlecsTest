#pragma once
#include <random>

inline float GetRandomCountdown(const float min, const float max)
{
    thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}
