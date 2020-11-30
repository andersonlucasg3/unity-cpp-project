#include "ManagedAssembly.h"

#include <string>

using namespace std;

namespace UnityEngine::ManagedBridge {
    ManagedAssembly::ManagedAssembly(const char *type, const char *assembly) {
        _type = type;
        _assembly = assembly;
    }

    const char * ManagedAssembly::name() const {
        string str(_type);
        return str
            .append(", ")
            .append(_assembly)
            .c_str();
    }
}