#pragma once

#include <string>
#include <map>
#include "../../Game/ComponentsRegistration.h"

using namespace std;

COMPONENTS_REGISTER_TEMPLATES_HEADER

namespace CppSource::Components {
    class CustomComponent;
}

namespace CppSource::Components::Factory {
    class ComponentFactory {
    private:
        map<string, CustomComponent *(*)()> *_componentMap;

        ComponentFactory();

    public:
        static ComponentFactory Instance();

        CustomComponent *InstantiateHandle(const string& clsName);
        void RegisterComponent(const string &clsName, CustomComponent *(*constructor)());
    };
}
