#pragma once

#define REGISTER_COMPONENT_CREATE_INSTANCE_DECLARE_METHOD(CLASS) \
    NativeComponent *CreateInstance_##CLASS() {    \
        return new CLASS(); \
    }
#define REGISTER_COMPONENT_CALL(CLASS) \
    ComponentFactory::Instance()->RegisterComponent(#CLASS, &CreateInstance_##CLASS);