#pragma once

#include "UnityAPI/NetFramework/System.h"

using namespace System;

namespace Helpers {
    string_m stringInstance(string_c src);
    void freeStringInstance(string_m ptr);
}