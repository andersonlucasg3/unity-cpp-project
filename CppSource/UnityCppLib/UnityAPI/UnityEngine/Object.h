#pragma once

#include <cstdint>

#include "HideFlags.h"

namespace UnityEngine::ManagedBridge {
    class Managed;
    class ManagedMember;
}

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
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