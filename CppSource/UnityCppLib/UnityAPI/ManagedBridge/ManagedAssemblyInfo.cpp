#include "ManagedAssemblyInfo.h"

#include <string>

#if defined(__MINGW32__) || defined(__MINGW64__)
#include <cstring>
#endif // MinGW

using namespace std;

namespace ManagedBridge {
    ManagedAssemblyInfo::ManagedAssemblyInfo(const char *type) {
        _fullName = type;
    }

    ManagedAssemblyInfo::ManagedAssemblyInfo(const char *type, const char *assembly) {
        string str(type);
        const char *namePtr = str.append(", ").append(assembly).c_str();
        _fullName = new char [strlen(namePtr)];
        strcpy((char *)_fullName, namePtr);
    }

    const char * ManagedAssemblyInfo::name() const {
        return _fullName;
    }
}