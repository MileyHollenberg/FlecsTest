#pragma once
#include <atomic>

#include "flecs/flecs.h"
#include "utils/random.h"

std::atomic<long long> SpawnFruitTime;
std::atomic<long long> CreateFruitTime;
inline void RegisterSpawnFruitSystem(const flecs::world& world)
{
    world.system<TreeTag>()
        .without<Countdown>()
        .multi_threaded()
        .run([](flecs::iter& it)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            while (it.next())
            {
                for (const auto i : it)
                {
                    it.entity(i).set<Countdown>({ GetRandomCountdown(50, 60) });
                    it.entity(i).add<SpawnFruitTag>();
                }
            }

            const auto end = std::chrono::high_resolution_clock::now();
            SpawnFruitTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        });

    world.observer<SpawnFruitTag>()
        .event(flecs::OnAdd)
        .run([](flecs::iter& it)
        {
            const auto start = std::chrono::high_resolution_clock::now();
    
            while (it.next())
            {
                for (const auto i : it)
                {
                    it.entity(i).remove<SpawnFruitTag>();
                    it.world().entity()
                        .set<Countdown>({ GetRandomCountdown(20, 30) })
                        .add<FruitTag>();
                }
            }

            const auto end = std::chrono::high_resolution_clock::now();
            CreateFruitTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        });
}