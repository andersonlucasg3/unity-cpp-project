#include <cstdint>
#include "ComponentFactory.h"
#include "../CustomComponent.h"

using namespace std;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;

intptr_t CreateCustomClassHandle(const string& clsName)
{
    return ComponentFactory::Instance().InstantiateHandle(clsName);
}

template<typename TComponent> TComponent *CastFrom(intptr_t handle) {
    return (TComponent *)handle;
}

void InvokeNativeAwake(intptr_t handle) {
    CastFrom<CustomComponent>(handle)->Awake();
}

void InvokeNativeStart(intptr_t handle) {
    CastFrom<CustomComponent>(handle)->Start();
}
