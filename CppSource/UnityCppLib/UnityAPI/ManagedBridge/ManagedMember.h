#pragma once

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    class Managed;

    enum MemberType {
        field = 0,
        property,
        method
    };

    class ManagedMember {
        friend class Managed;
    private:
        intptr_t *_memberPtr;
        intptr_t *_managedPtr;
        MemberType _type;

        ManagedMember(intptr_t *memberPtr, intptr_t *managedPtr, MemberType type);
        ~ManagedMember();

        template<typename TValue> TValue *callGet(void *) const;
        template<typename TValue> void callSet(void *, TValue *value) const;

    public:
        [[nodiscard,maybe_unused]] const char *getValueString() const;
        [[maybe_unused]] void setValueString(const char *value) const;

        [[nodiscard,maybe_unused]] int getValueInt() const;
        [[maybe_unused]] void setValueInt(int value) const;

        [[nodiscard,maybe_unused]] long getValueLong() const;
        [[maybe_unused]] void setValueLong(long value) const;

        [[nodiscard,maybe_unused]] float getValueFloat() const;
        [[maybe_unused]] void setValueFloat(float value) const;

        [[nodiscard,maybe_unused]] double getValueDouble() const;
        [[maybe_unused]] void setValueDouble(double value) const;
    };
}