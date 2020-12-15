#pragma once

#include "Object.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/Members/MethodMember.h"
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

        static MethodMember _addComponentMethod;
        static MethodMember _getComponentMethod;
        static MethodMember _tryGetComponentMethod;

        Transform *_transform = nullptr;

        explicit GameObject(ManagedInstance instance);

    public:
        explicit GameObject();
        explicit GameObject(string_c name);
        explicit GameObject(string_c name, ManagedType components[], int componentCount);
        ~GameObject();

        bool activeSelf() const;
        bool activeInHierarchy() const;
        unsigned long sceneCullingMask() const;
        bool isStatic() const;
        void setIsStatic(bool isStatic) const;
        int layer() const;
        void setLayer(int layer) const;
        string_c tag() const;
        void setTag(string_c tag) const;
        Transform *transform() const;

        template<class TComponent> TComponent *addComponent() const;
        template<class TComponent> TComponent *getComponent() const;
        template<class TComponent> bool tryGetComponent(TComponent **component);

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}