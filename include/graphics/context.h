#ifndef CONTEXT_H
#define CONTEXT_H

#include "core/defines.h"

#include "engine/joj_window.h"

class Context
{
public:
    virtual ~Context();

    virtual b8 create() = 0;
    virtual void make_current() = 0;
    virtual void destroy() = 0;
};

#endif // CONTEXT_H