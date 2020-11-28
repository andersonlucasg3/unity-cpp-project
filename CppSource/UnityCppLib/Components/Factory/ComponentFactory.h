#pragma once

#include <string>
#include <map>
#include "../../Game/ComponentsRegistration.h"

using namespace std;

namespace CppSource::Components {
    class NativeComponent;
}

namespace CppSource::Components::Factory {
    class ComponentFactory {
    private:
        map<string, NativeComponent *(*)()> _componentMap;

        ComponentFactory();

    public:
        static ComponentFactory *Instance();

        NativeComponent *InstantiateHandle(const char *className);
        void RegisterComponent(const char *className, NativeComponent *(*constructor)());
    };
}
