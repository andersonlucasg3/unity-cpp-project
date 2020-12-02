#pragma once

#include <cstdint>

namespace ManagedBridge {
    struct ManagedPointer {
    private:
        const void *_managedRef;

    public:
        static const ManagedPointer null;

        ManagedPointer();
        explicit ManagedPointer(const void *pointer);

        const void *toManaged() const;

        bool operator==(ManagedPointer other);
        bool operator!=(ManagedPointer other);
        bool operator==(void *pointer);
        bool operator!=(void *pointer);
    };
}