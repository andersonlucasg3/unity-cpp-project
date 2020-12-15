#include "ManagedPointer.h"

namespace ManagedBridge {
    const ManagedPointer ManagedPointer::null = ManagedPointer(nullptr);

    ManagedPointer::ManagedPointer() {
        _managedRef = nullptr;
    }

    ManagedPointer::ManagedPointer(pointer_c pointer) {
        _managedRef = pointer;
    }

    pointer_c ManagedPointer::toManaged() const {
        return _managedRef;
    }

    bool ManagedPointer::operator==(ManagedPointer other) {
        return _managedRef == other._managedRef;
    }

    bool ManagedPointer::operator!=(ManagedPointer other) {
        return _managedRef != other._managedRef;
    }

    bool ManagedPointer::operator==(pointer_m pointer) {
        return _managedRef == pointer;
    }

    bool ManagedPointer::operator!=(pointer_m pointer) {
        return _managedRef != pointer;
    }
}