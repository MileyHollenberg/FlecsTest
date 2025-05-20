#include "FlecsTestWorld.h"

#include <chrono>
#include <iostream>

#include "components/Countdown.h"
#include "components/Tags.h"
#include "systems/CountdownSystem.hpp"
#include "systems/FruitDecaySystem.hpp"
#include "systems/SpawnFruitSystem.hpp"
#include "utils/random.h"

constexpr float secondsPerTick = 5.0f; // How many seconds each world.progress will simulate
constexpr float deltaTime = secondsPerTick;
constexpr float dayTicks = (24 * 60 * 60) / deltaTime; // The amount of ticks needed to simulate a full day

void FlecsTestWorld::Start() const
{
    _world.set_threads(24);
    
    for (int i = 0; i < 10000; i++)
    {
        _world.entity()
            .set<Countdown>({ GetRandomCountdown(50, 60) })
            .add<TreeTag>();
    }
    
    RegisterCountdownSystem(_world);
    RegisterSpawnFruitSystem(_world);
    RegisterFruitDecaySystem(_world);

    std::cout << "Start processing for " << static_cast<int>(dayTicks) <<  " ticks..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < static_cast<int>(dayTicks); i++)
        _world.progress(deltaTime);
    
    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";

    std::cout << "Countdown System time: " << CountdownProcessingTime / 1000 << "ms\n";
    std::cout << "Fruit Decay System time: " << FruitDecayProcessingTime / 1000 << "ms\n";
    std::cout << "Spawn Fruit System time: " << SpawnFruitTime / 1000 << "ms\n";
    std::cout << "Create Fruit time: " << CreateFruitTime / 1000 << "ms\n";
    
    const int fruitCount = _world.count<FruitTag>();
    std::cout << "Entities with FruitTag: " << fruitCount << std::endl;
}
