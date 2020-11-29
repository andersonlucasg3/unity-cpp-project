#pragma once

#include <cstdint>

#include "MemberType.h"

namespace UnityEngine {
    class Object;
}

namespace UnityEngine::ManagedBridge {
    class Managed;

    class ManagedMember {
        friend class Managed;
    private:
        intptr_t *_memberPtr;
        intptr_t *_managedPtr;
        MemberType _type;

        ManagedMember(intptr_t *memberPtr, intptr_t *managedPtr, MemberType type);
        ~ManagedMember();

        template<typename TValue> void callGet(void *func, TValue &pointer) const;
        template<typename TValue> void callSet(void *, TValue *value) const;

    public:
        [[nodiscard,maybe_unused]] const char *getString() const;
        [[maybe_unused]] void setString(const char *value) const;

        [[nodiscard,maybe_unused]] int getInt() const;
        [[maybe_unused]] void setInt(int value) const;

        [[nodiscard,maybe_unused]] long getLong() const;
        [[maybe_unused]] void setLong(long value) const;

        [[nodiscard,maybe_unused]] float getFloat() const;
        [[maybe_unused]] void setFloat(float value) const;

        [[nodiscard,maybe_unused]] double getDouble() const;
        [[maybe_unused]] void setDouble(double value) const;

        [[nodiscard,maybe_unused]] intptr_t *getObject() const;
        [[maybe_unused]] void setObject(Managed *object) const;
    };
}