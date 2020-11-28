#include "UnityInitialization.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "NativeComponentPrivate.h"
#include "Game/TestComponent.h"

#include <iostream>

using namespace std;
using namespace CppSource::Game;

void DebugLog(const char *message) {
    string messageStr(message);
    cout << messageStr.append("\n").c_str();
}

int main(int argc, char **argv) {
    SetUnityDebugLogMethod(&DebugLog);
    InitializeNative();

    NativeComponent *component = CreateNativeInstance("TestComponent", "TestGameObjectName");
    assert(typeid(*component) == typeid(TestComponent));
    assert(strcmp(component->GetGameObjectName(), "TestGameObjectName") == 0);
    return 0;
}