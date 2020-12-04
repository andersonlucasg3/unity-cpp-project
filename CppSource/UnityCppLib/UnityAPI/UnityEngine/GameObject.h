#pragma once

#include "Object.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/NetFramework/System.h"

using namespace System;

namespace UnityEngine {
    class Transform;
    class Component;

    class GameObject : public Object {
        friend class Component;

    private:
        static ManagedType _gameObjectType;

        static ConstructorMember _defaultConstructor;
        static ConstructorMember _secondConstructor;
        static ConstructorMember _thirdConstructor;

        static PropertyMember _activeInHierarchyProperty;
        static PropertyMember _sceneCullingMaskProperty;
        static PropertyMember _activeSelfProperty;
        static PropertyMember _isStaticProperty;
        static PropertyMember _layerProperty;
        static PropertyMember _tagProperty;
        static PropertyMember _transformProperty;

        Transform *_transform = nullptr;

        explicit GameObject(ManagedInstance instance);

    public:
        explicit GameObject();
        explicit GameObject(string_c name);
        explicit GameObject(string_c name, ManagedType components[], int componentCount);
        ~GameObject();

        [[nodiscard,maybe_unused]] bool activeSelf() const;
        [[nodiscard,maybe_unused]] bool activeInHierarchy() const;
        [[nodiscard,maybe_unused]] unsigned long sceneCullingMask() const;
        [[nodiscard,maybe_unused]] bool isStatic() const;
        [[maybe_unused]] void setIsStatic(bool isStatic) const;
        [[nodiscard,maybe_unused]] int layer() const;
        [[maybe_unused]] void setLayer(int layer) const;
        [[nodiscard,maybe_unused]] string_c tag() const;
        [[maybe_unused]] void setTag(string_c tag) const;
        [[nodiscard,maybe_unused]] Transform *transform() const;

        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *addComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *getComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] bool tryGetComponent(const TComponent &component);

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}