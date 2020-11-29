#pragma once

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    class Managed;
    class ManagedMember;
}

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    enum HideFlags;

    class Object {
    private:
        ManagedMember *_nameProperty{};
        ManagedMember *_hideFlagsProperty{};

    protected:
        Managed *_managed{};

        Object();
        explicit Object(intptr_t *instance);
        ~Object();

        void createManagedInstance(const char *className);
        virtual void InitializeMembers();

    public:
        [[nodiscard,maybe_unused]] const char *name() const;
        [[maybe_unused]] void setName(const char *name) const;

        [[nodiscard,maybe_unused]] HideFlags hideFlags() const;
    };
}