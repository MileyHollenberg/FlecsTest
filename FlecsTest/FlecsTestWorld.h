#pragma once
#include "flecs/flecs.h"

class FlecsTestWorld
{
public:
    void Start() const;

private:
    flecs::world _world;
};
