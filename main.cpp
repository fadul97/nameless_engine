#include <iostream>
#include "test_app.h"

#include "logger.h"

int main(int argc, char** argv)
{
    u32 e = 50;
    Logger::log_output(LOG_LEVEL_ERROR, ERR_WINDOW, "Whatever %d", e);
    std::cout << "E agora?\n";

    auto engine = new NamelessEngine(RENDERER_GLX);
    b8 result = engine->init("JOJ Engine", 800, 600);
    if(result != OK)
    {
        std::cout << "Failed to initalize engine.\n";
        return result;
    }
    
    if(argc < 1) {
        std::cout << "No obj file\n";

        // Main loop
        engine->run(new TestApp(engine->get_renderer(), ""));
        
        return 0;
    }
    
    // Main loop
    engine->run(new TestApp(engine->get_renderer(), argv[1]));
    
    engine->shutdown();

    delete engine;
    
    return 0;
}