#pragma once

#include <string>

using namespace std;

namespace UnityEngine {
    class Debug {
    public:
        static void Log(const char *message);
        static void Log(const string& message);
    };
}
