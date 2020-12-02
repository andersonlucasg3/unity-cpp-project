#pragma once

#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

using namespace ManagedBridge;

namespace System {
    extern ManagedType stringType;

    void InitializeManagedBridge();
}