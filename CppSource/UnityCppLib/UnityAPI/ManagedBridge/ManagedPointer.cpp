#include "ManagedPointer.h"

namespace UnityEngine::ManagedBridge {
    const ManagedPointer ManagedPointer::null = ManagedPointer((void *)nullptr);

    ManagedPointer::ManagedPointer(const void *pointer) {
        _managedRef = pointer;
    }

    bool ManagedPointer::notNull() const {
        return _managedRef != nullptr;
    }

    ManagedPointer::operator const void *() const {
        return _managedRef;
    }
}