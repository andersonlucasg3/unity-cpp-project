#include "System.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

namespace System {
    ManagedAssemblyInfo _systemIntPtrAssemblyInfo("System.IntPtr");
    ManagedAssemblyInfo _systemStringAssemblyInfo("System.String");
    ManagedAssemblyInfo _systemArrayAssemblyInfo("System.Array");

    ManagedType managedIntPtrType = ManagedType::null;
    ManagedType managedStringType = ManagedType::null;
    ManagedType managedArrayType = ManagedType::null;

    void InitializeManagedBridge() {
        managedIntPtrType = ManagedType(_systemIntPtrAssemblyInfo);
        managedStringType = ManagedType(_systemStringAssemblyInfo);
        managedArrayType = ManagedType(_systemArrayAssemblyInfo);
    }
}