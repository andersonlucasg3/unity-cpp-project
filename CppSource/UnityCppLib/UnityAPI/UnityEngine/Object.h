#pragma once

#include "HideFlags.h"
#include "UnityAPI/ManagedBridge/ManagedPointer.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

#include <cstdint>

namespace UnityEngine {
    using namespace ManagedBridge;
    using namespace ManagedBridge::Members;

    class Object {
    protected:
        ManagedType _type = ManagedType::null;
        ManagedInstance _instance = ManagedInstance::null;

        explicit Object(ManagedType type);
        explicit Object(ManagedInstance instance);
        ~Object();

    public:
        [[nodiscard,maybe_unused]] const char *name() const;
        [[maybe_unused]] void setName(const char *name) const;

        [[nodiscard,maybe_unused]] HideFlags hideFlags() const;

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}