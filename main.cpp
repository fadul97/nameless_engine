#include "engine.h"
#include "error_list.h"
#include <iostream>

int main()
{
    auto engine = new NamelessEngine();
    b8 result = engine->init("JOJ Engine", 400, 400);
    if(result != OK)
    {
        std::cout << "Failed to initalize engine - " << "[" << error_names[result] << "]\n";
        return result;
    }
    
    // Main loop
    engine->run();
    
    engine->shutdown();

    delete engine;
    
    return 0;
}