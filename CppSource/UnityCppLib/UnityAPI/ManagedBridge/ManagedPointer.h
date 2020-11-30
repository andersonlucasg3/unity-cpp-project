#pragma once

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    struct ManagedPointer {
    private:
        const void *_managedRef;

    public:
        static const ManagedPointer null;

        ManagedPointer(const void *pointer);

        [[nodiscard]] bool notNull() const;

        operator const void *() const;
    };
}