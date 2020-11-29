#pragma once

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    typedef void (*UnitySendMessageMethod)(const char *gameObjectName, const char *methodName, const char *message);

    class ManagedMember;
    enum MemberType;

    class Managed {
        friend class ManagedMember;
    private:
        intptr_t *_instance;

    public:
        static UnitySendMessageMethod UnitySendMessage;

        Managed();
        ~Managed();

        void construct(const char *typeName);

        ManagedMember *getMember(const char *memberName, MemberType type);
        static void destroy(ManagedMember *member);
    };


}