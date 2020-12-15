#include "System.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

namespace System {
    ManagedAssemblyInfo _systemStringAssemblyInfo("System.String");
    ManagedAssemblyInfo _systemArrayAssemblyInfo("System.Array");

    ManagedType managedStringType = ManagedType::null;
    ManagedType managedArrayType = ManagedType::null;

    void InitializeManagedBridge() {
        managedStringType = ManagedType(_systemStringAssemblyInfo);
        managedArrayType = ManagedType(_systemArrayAssemblyInfo);
    }
}