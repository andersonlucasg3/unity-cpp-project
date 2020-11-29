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
        intptr_t *_instance;
        Managed *_managed;
        MemberType _type;

        ManagedMember(intptr_t *_instance, Managed *_managed, MemberType type);

        template<typename TValue> TValue *callGet(void *) const;
        template<typename TValue> void callSet(void *, TValue *value) const;

    public:
        [[nodiscard]] const char *getValueString() const;
        void setValueString(const char *value) const;

        [[nodiscard]] int getValueInt() const;
        void setValueInt(int value) const;

        [[nodiscard]] long getValueLong() const;
        void setValueLong(long value) const;

        [[nodiscard]] float getValueFloat() const;
        void setValueFloat(float value) const;

        [[nodiscard]] double getValueDouble() const;
        void setValueDouble(double value) const;
    };
}