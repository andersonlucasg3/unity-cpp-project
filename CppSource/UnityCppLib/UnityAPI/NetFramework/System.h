#pragma once

#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

namespace ManagedBridge {
    class ManagedType;
}

using namespace ManagedBridge;

namespace System {
#if defined(__MINGW32__) || defined(__MINGW64__)
    typedef unsigned char byte;
#endif
    typedef unsigned int uint;
    typedef unsigned long ulong;
    typedef unsigned short ushort;
    typedef const char *string_c;
    typedef char *string_m;
    typedef const void *pointer_c;
    typedef void *pointer_m;

    extern ManagedType managedIntPtrType;
    extern ManagedType managedStringType;
    extern ManagedType managedArrayType;

    void InitializeManagedBridge();
}