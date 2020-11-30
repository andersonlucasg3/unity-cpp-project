#include "ManagedInstance.h"
#include "ManagedPointer.h"

namespace UnityEngine::ManagedBridge {
    const ManagedInstance ManagedInstance::null = ManagedInstance();

    ManagedInstance::ManagedInstance() : Managed(ManagedPointer::null) {
        _type = ManagedType(ManagedPointer::null);
    }

    ManagedInstance::ManagedInstance(ManagedType type, ManagedPointer ptr) : Managed(ptr) {
        _type = type;
    }

    const ManagedType ManagedInstance::type() const {
        return _type;
    }
}