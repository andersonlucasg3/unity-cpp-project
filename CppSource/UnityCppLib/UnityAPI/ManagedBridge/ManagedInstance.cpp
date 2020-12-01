#include "ManagedInstance.h"
#include "ManagedPointer.h"

namespace UnityEngine::ManagedBridge {
    const ManagedInstance ManagedInstance::null = ManagedInstance();

    ManagedInstance::ManagedInstance() : Managed(nullptr) { }

    ManagedInstance::ManagedInstance(ManagedPointer ptr) : Managed(ptr) { }
}