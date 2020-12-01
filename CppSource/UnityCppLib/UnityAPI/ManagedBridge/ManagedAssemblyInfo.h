#pragma once

namespace UnityEngine::ManagedBridge {
    struct ManagedAssemblyInfo {
    private:
        const char *_fullName;

    public:
        ManagedAssemblyInfo(const char *type, const char *assembly);
        ~ManagedAssemblyInfo();

        [[nodiscard]] const char *name() const;
    };
}