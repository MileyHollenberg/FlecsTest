#pragma once
#include <atomic>
#include <chrono>

#include "flecs/flecs.h"
#include "components/Countdown.h"

std::atomic<long long> CountdownProcessingTime;
inline void RegisterCountdownSystem(const flecs::world& world)
{
    world.system<Countdown>()
        .multi_threaded()
        .run([](flecs::iter& it)
        {
            const auto start = std::chrono::high_resolution_clock::now();
    
            const float deltaTime = it.delta_time();
            
            while (it.next())
            {
                auto countdown = it.field<Countdown>(0);
        
                for (const auto i : it)
                {
                    countdown[i].TimeLeft -= deltaTime;
                    if (countdown[i].TimeLeft < 0)
                        it.entity(i).remove<Countdown>();
                }
            }

            const auto end = std::chrono::high_resolution_clock::now();
            CountdownProcessingTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        });
}