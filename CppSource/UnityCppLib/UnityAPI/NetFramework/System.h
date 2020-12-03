#pragma once

#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

namespace ManagedBridge {
    class ManagedType;
}

using namespace ManagedBridge;

namespace System {
    typedef unsigned int uint;
    typedef unsigned long ulong;
    typedef unsigned short ushort;
    typedef const char *string_c;
    typedef char *string_m;
    typedef const void *pointer_c;
    typedef void *pointer_m;

    extern ManagedType stringType;

    void InitializeManagedBridge();
}