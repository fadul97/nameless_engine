#ifndef JOJ_APP_H
#define JOJ_APP_H

#include "engine.h"
#include <unistd.h>

class App
{
public:
    App();
    virtual ~App();

    virtual void init() = 0;
    virtual void update(f32 delta_time) = 0;
    virtual void shutdown() = 0;

    virtual void draw() {}
    virtual void on_pause() { usleep(10); }

    void set_input(InputX11& input);

protected:
    InputX11* input;
};

inline void App::set_input(InputX11& input)
{ this->input = &input; }

#endif // !JOJ_APP_H