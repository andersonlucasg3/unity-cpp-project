#include "System.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

namespace System {
    ManagedAssemblyInfo _systemStringAssemblyInfo("System.String");

    ManagedType managedStringType = ManagedType::null;

    void InitializeManagedBridge() {
        managedStringType = ManagedType(_systemStringAssemblyInfo);
    }
}