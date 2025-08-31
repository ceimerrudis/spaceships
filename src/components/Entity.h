#pragma once
#include "GlobalInclude.h"

struct Entity
{
    #if DEBUG
        bool initialized;
    #endif
    unsigned int ID;
};
