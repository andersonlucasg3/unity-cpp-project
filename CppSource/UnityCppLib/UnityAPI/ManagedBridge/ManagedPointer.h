#pragma once

#include "UnityAPI/NetFramework/System.h"

#include <cstdint>

using namespace System;

namespace ManagedBridge {
    struct ManagedPointer {
    private:
        pointer_c _managedRef;

    public:
        static const ManagedPointer null;

        ManagedPointer();
        explicit ManagedPointer(pointer_c pointer);

        pointer_c toManaged() const;

        bool operator==(ManagedPointer other);
        bool operator!=(ManagedPointer other);
        bool operator==(pointer_m pointer);
        bool operator!=(pointer_m pointer);
    };
}