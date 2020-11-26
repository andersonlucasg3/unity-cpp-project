#pragma once

#include <string>
#include <map>

using namespace std;

namespace CppSource::Components {
    class CustomComponent;
}

namespace CppSource::Components::Factory {
    class ComponentFactory {
    public:
        static ComponentFactory Instance();

        intptr_t InstantiateHandle(const std::string& clsName);
        template<typename TComponent> void RegisterComponent(const std::string& clsName);

    private:
        map<string, CustomComponent *(*)()> *_componentMap;

        ComponentFactory();

        template<typename TComponent> CustomComponent *CreateInstance();
    };
}
