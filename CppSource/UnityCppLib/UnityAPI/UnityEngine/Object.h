#pragma once

#include "HideFlags.h"
#include "UnityAPI/ManagedBridge/ManagedPointer.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/Members/MethodMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"
#include "UnityAPI/NetFramework/System.h"

#include <cstdint>

using namespace System;

namespace UnityEngine {
    using namespace ManagedBridge;
    using namespace ManagedBridge::Members;

    class Object {
    protected:
        static ManagedType _objectBridgeType;
        static ManagedType _objectType;

        static PropertyMember _nameProperty;
        static PropertyMember _hideFlagsProperty;

        static MethodMember _destroyMethod;
        static MethodMember _destroyImmediateMethod;
        static MethodMember _dontDestroyOnLoadMethod;

        ManagedInstance _instance = ManagedInstance::null;

        explicit Object();
        explicit Object(ManagedInstance instance);
        ~Object();

    public:
        string_c name() const;
        void setName(string_c name) const;

        HideFlags hideFlags() const;
        void setHideFlags(HideFlags flags) const;

        static void destroy(Object *obj, float t = 0.0);
        static void destroyImmediate(Object *obj, bool allowDestroyingAssets = false);
        static void dontDestroyOnLoad(Object *target);

        static ManagedType type();
        static ManagedType unityType();
        static void InitializeManagedBridge();
    };
}