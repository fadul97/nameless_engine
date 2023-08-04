#include "defines.h"
#include <iostream>
#include "error_list.h"
#include "window_x11.h"
#include "context_gl.h"

int main()
{
    WindowX11* window = new WindowX11();
    GLContext* context = new GLContext(*window);

    int result = window->init();
    if(result != OK)
    {
        std::cout << "Failed to initalize window - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = context->create();
    if(result != OK)
    {
        std::cout << "Failed to create context - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = window->create();
    if(result != OK)
    {
        std::cout << "Failed to create window - " << "[" << error_names[result] << "]\n";
        return result;
    }

    context->make_current();
    window->show();

    // Main loop
    window->run();
    
    context->destroy();
    window->destroy();

    return 0;
}