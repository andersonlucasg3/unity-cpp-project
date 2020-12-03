#include "System.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

namespace System {
    ManagedAssemblyInfo _systemStringAssemblyInfo("System.String");

    ManagedType stringType = ManagedType::null;

    void InitializeManagedBridge() {
        stringType = ManagedType(_systemStringAssemblyInfo);
    }
}