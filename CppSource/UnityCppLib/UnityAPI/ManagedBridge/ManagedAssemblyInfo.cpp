#include "ManagedAssemblyInfo.h"

#include <string>

using namespace std;

namespace UnityEngine::ManagedBridge {
    ManagedAssemblyInfo::ManagedAssemblyInfo(const char *type, const char *assembly) {
        _type = type;
        _assembly = assembly;
    }

    const char * ManagedAssemblyInfo::name() const {
        string str(_type);
        return str
            .append(", ")
            .append(_assembly)
            .c_str();
    }
}