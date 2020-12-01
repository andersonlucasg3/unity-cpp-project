#include "ManagedPointer.h"

namespace UnityEngine::ManagedBridge {
    const ManagedPointer ManagedPointer::null = ManagedPointer((void *)nullptr);

    ManagedPointer::ManagedPointer() {
        _managedRef = nullptr;
    }

    ManagedPointer::ManagedPointer(const void *pointer) {
        _managedRef = pointer;
    }

    const void *ManagedPointer::toManaged() const {
        return _managedRef;
    }

    bool ManagedPointer::operator==(ManagedPointer other) {
        return _managedRef == other._managedRef;
    }

    bool ManagedPointer::operator!=(ManagedPointer other) {
        return _managedRef != other._managedRef;
    }

    bool ManagedPointer::operator==(void *pointer) {
        return _managedRef == pointer;
    }

    bool ManagedPointer::operator!=(void *pointer) {
        return _managedRef != pointer;
    }
}