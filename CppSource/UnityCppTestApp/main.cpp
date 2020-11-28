#include "UnityInitialization.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "Game/TestComponent.h"

#include <iostream>

using namespace std;
using namespace CppSource::Game;

void DebugLog(const char *message) {
    string messageStr(message);
    cout << messageStr.append("\n").c_str();
}

extern "C" {
    UNITY_IMPORT void SetUnityDebugLogMethod(void (*)(const char *));
    UNITY_IMPORT NativeComponent *CreateNativeInstance(const char *className);
}

int main(int argc, char **argv) {
    SetUnityDebugLogMethod(&DebugLog);
    InitializeNative();

    NativeComponent *component = CreateNativeInstance("TestComponent");
    assert(typeid(*component) == typeid(TestComponent));
    return 0;
}