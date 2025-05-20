#pragma once
#include <atomic>

#include "flecs/flecs.h"

std::atomic<long long> FruitDecayProcessingTime;
inline void RegisterFruitDecaySystem(const flecs::world& world)
{
    world.system<FruitTag>()
        .without<Countdown>()
        .multi_threaded()
        .run([](flecs::iter& it)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            while (it.next())
            {
                for (const auto i : it)
                    it.entity(i).destruct();
            }

            const auto end = std::chrono::high_resolution_clock::now();
            FruitDecayProcessingTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        });
}