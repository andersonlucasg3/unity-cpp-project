#include "ManagedAssemblyInfo.h"

#include <string>

using namespace std;

namespace UnityEngine::ManagedBridge {
    ManagedAssemblyInfo::ManagedAssemblyInfo(const char *type, const char *assembly) {
        string str(type);
        str = str.append(", ").append(assembly);
        char *fullName = new char [str.length()];
        str.copy(fullName, str.length());
        _fullName = fullName;
    }

    ManagedAssemblyInfo::~ManagedAssemblyInfo() {
        delete[] _fullName;
    }

    const char * ManagedAssemblyInfo::name() const {
        return _fullName;
    }
}