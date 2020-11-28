#pragma once

#include "Components/NativeComponent.h"

using namespace CppSource::Components;

extern "C" {
    NativeComponent *CreateNativeInstance(const char *className, const char *gameObjectName);
}