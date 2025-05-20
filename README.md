# FlecsTest
A simple test project to learn more about ECS using the [Flecs](https://github.com/SanderMertens/flecs) library

## How to run
The project was made with Rider 2025.1.2, only change from the default template is that the `./` folder is added to the include directory for both debug and release configs so `#include "flecs/flecs.h"` can work from anywhere (I should likely put it in a lib folder somewhere but I'm not too concerned about that for this test project). The project should just run as-is from Rider and likely also Visual Studio
