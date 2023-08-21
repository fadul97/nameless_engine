#include <iostream>
#include "test_app.h"

int main()
{
    auto engine = new NamelessEngine(RENDERER_GLX);
    b8 result = engine->init("JOJ Engine", 800, 600);
    if(result != OK)
    {
        std::cout << "Failed to initalize engine.\n";
        return result;
    }
    
    // Main loop
    engine->run(new TestApp(engine->get_renderer()));
    
    engine->shutdown();

    delete engine;
    
    return 0;
}