#pragma once

#include "make_enum.h"

// Generate MyEnum1 with helper functions.
#define FOREACH_IN_MY_ENUM_1(EnumName, X)       \
    X(EnumName, FOO, 0)                         \
    X(EnumName, BAR, 1)                         \
    X(EnumName, BAZ, 2)
MAKE_ENUM_DECLARATION(MyEnum1, FOREACH_IN_MY_ENUM_1)

// Generate MyEnum2 with helper functions.
#define FOREACH_IN_MY_ENUM_2(EnumName, X)       \
    X(EnumName, SPAM, 0)                        \
    X(EnumName, EGGS, 1)
MAKE_ENUM_CLASS_DECLARATION(MyEnum2, FOREACH_IN_MY_ENUM_2)
