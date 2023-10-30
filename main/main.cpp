#include <iostream>

#include "engine/joj_engine.h"

int main()
{
    Keys key = KEY_0;
    int v = 1;
    std::cout << "Hello, JOJEngine!\n" << key << "\n" << v << "\n";

    auto engine = new NamelessEngine();

    b8 result = engine->init(800, 600, "JOJ Engine");
    if(result != OK)
    {
        std::cout << "Failed to initalize engine.\n";
        return result;
    }

    // Main loop
    engine->run();
    
    engine->shutdown();

    delete engine;

    return 0;
}