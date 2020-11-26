#include <string>
#include "../Components/Factory/ComponentFactory.h"

using namespace std;

namespace CppSource::Game {
    class TestComponent;
}

namespace CppSource::Components::Factory {
    template<> void ComponentFactory::RegisterComponent<CppSource::Game::TestComponent>(const string &clsName);
}