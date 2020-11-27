#pragma once

#define REQUIRED_COMPONENT_HEADER \
namespace CppSource::Components::Factory{ \
    class ComponentFactory; \
}
#define REQUIRED_COMPONENT_BODY(CLASS) \
    friend class constructor; \
    struct constructor { \
        constructor(); \
    }; \
    static constructor cons;
#define REQUIRED_COMPONENT_REGISTER_HEADER "../Components/Factory/ComponentFactory.h"
#define REQUIRED_COMPONENT_REGISTER_NAMESPACE \
    using namespace CppSource::Components::Factory;
#define REQUIRED_COMPONENT_REGISTER(CLASS) \
    CustomComponent *CreateInstance() {    \
        return new CLASS(); \
    }\
    CLASS::constructor::constructor() { \
        ComponentFactory::Instance().RegisterComponent(#CLASS, &CreateInstance); \
    }                                      \
    CLASS::constructor CLASS::cons;