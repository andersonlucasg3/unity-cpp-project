#pragma once

#include "HideFlags.h"
#include "UnityAPI/ManagedBridge/ManagedPointer.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"
#include "UnityAPI/NetFramework/System.h"

#include <cstdint>

using namespace System;

namespace UnityEngine {
    using namespace ManagedBridge;
    using namespace ManagedBridge::Members;

    class Object {
    protected:
        static ManagedType _objectType;
        static PropertyMember _nameProperty;
        static PropertyMember _hideFlagsProperty;

        ManagedInstance _instance = ManagedInstance::null;

        explicit Object();
        explicit Object(ManagedInstance instance);
        ~Object();

    public:
        [[nodiscard,maybe_unused]] string_c name() const;
        [[maybe_unused]] void setName(string_c name) const;

        [[nodiscard,maybe_unused]] HideFlags hideFlags() const;
        [[maybe_unused]] void setHideFlags(HideFlags flags) const;

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}