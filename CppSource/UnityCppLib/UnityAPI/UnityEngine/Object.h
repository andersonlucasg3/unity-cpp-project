#pragma once

namespace UnityEngine::ManagedBridge {
    class Managed;
    class ManagedMember;
}

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    class Object {
    private:
        Managed *_managed;
        ManagedMember *_nameProperty;

    protected:
        Object();
        ~Object();

        void createManagedInstance(const char *className);

    public:
        [[nodiscard]] const char *name() const;
        void setName(const char *name) const;
    };
}