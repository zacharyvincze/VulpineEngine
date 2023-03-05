#pragma once

#include "Logger.h"

#define VP_CORE_ASSERT(check, ...)                                                                                     \
    if (!(check))                                                                                                      \
    {                                                                                                                  \
        VP_CORE_ERROR(__VA_ARGS__);                                                                                    \
        assert(check);                                                                                                 \
    }
