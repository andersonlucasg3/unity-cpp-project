#include "ManagedInstance.h"
#include "ManagedPointer.h"

namespace ManagedBridge {
    const ManagedInstance ManagedInstance::null = ManagedInstance();

    ManagedInstance::ManagedInstance() : Managed(ManagedPointer::null) { }

    ManagedInstance::ManagedInstance(ManagedPointer ptr) : Managed(ptr) { }
}