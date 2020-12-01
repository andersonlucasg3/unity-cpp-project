#pragma once

namespace ManagedBridge {
    struct ManagedAssemblyInfo {
    private:
        const char *_fullName;

    public:
        ManagedAssemblyInfo(const char *type);
        ManagedAssemblyInfo(const char *type, const char *assembly);

        [[nodiscard]] const char *name() const;
    };
}