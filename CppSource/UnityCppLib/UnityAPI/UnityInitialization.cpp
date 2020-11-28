#include "../../UnityCppTestApp/UnityInitialization.h"
#include "../Game/ComponentsRegistration.h"
#include "../Components/Factory/ComponentFactory.h"
#include "UnityAPIExtern.h"

using namespace CppSource::Game;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;

REGISTER_DECLARE_ALL_COMPONENTS

extern "C" {
    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL
    }
}