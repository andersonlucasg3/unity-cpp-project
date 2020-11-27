#include <cstdint>
#include "ComponentFactory.h"
#include "../CustomComponent.h"

using namespace std;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;

long long CreateCustomClassHandle(const char *clsName, const char *gameObjectName)
{
    CustomComponent *component = ComponentFactory::Instance().InstantiateHandle(clsName);
    component->SetGameObjectName(gameObjectName);
    return intptr_t(component);
}

template<typename TComponent> TComponent *CastFrom(intptr_t handle) {
    return (TComponent *)intptr_t(handle);
}

void InvokeNativeAwake(int handle) {
    CastFrom<CustomComponent>(handle)->Awake();
}

void InvokeNativeStart(int handle) {
    CastFrom<CustomComponent>(handle)->Start();
}
