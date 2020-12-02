#include "System.h"

#include <memory>

namespace System {
    ManagedAssemblyInfo _systemStringAssemblyInfo("System.String");

    ManagedType stringType = ManagedType::null;

    void InitializeManagedBridge() {
        stringType = ManagedType(_systemStringAssemblyInfo);
    }
}