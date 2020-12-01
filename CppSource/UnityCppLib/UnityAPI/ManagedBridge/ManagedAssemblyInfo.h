#pragma once

namespace UnityEngine::ManagedBridge {
    struct ManagedAssemblyInfo {
    private:
        const char *_type;
        const char *_assembly;

    public:
        ManagedAssemblyInfo(const char *type, const char *assembly);

        [[nodiscard]] const char *name() const;
    };
}