#pragma once

namespace UnityEngine::ManagedBridge {
    struct ManagedAssembly {
    private:
        const char *_type;
        const char *_assembly;

    public:
        ManagedAssembly(const char *type, const char *assembly);

        [[nodiscard]] const char *name() const;
    };
}