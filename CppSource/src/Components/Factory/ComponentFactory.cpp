#include "ComponentFactory.h"

namespace CppSource::Components::Factory {
    ComponentFactory *_shared = nullptr;

    ComponentFactory ComponentFactory::Instance() {
        if (!_shared) {
            _shared = new ComponentFactory();
        }
        return *_shared;
    }

    ComponentFactory::ComponentFactory() {
        _componentMap = new std::map<std::string, CustomComponent *(*)()>;
    }

    intptr_t ComponentFactory::InstantiateHandle(const std::string& clsName) {
        return intptr_t(_componentMap->find(clsName)->second());
    }

    template<typename TComponent> void ComponentFactory::RegisterComponent(const std::string& clsName) {
        _componentMap->insert(std::make_pair(clsName, &CreateInstance<TComponent>));
    }

    template<typename TComponent> CustomComponent *ComponentFactory::CreateInstance() {
        return new TComponent;
    }
}