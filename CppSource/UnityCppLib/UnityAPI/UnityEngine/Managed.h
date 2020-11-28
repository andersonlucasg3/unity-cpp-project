#pragma once

#include <cstdint>

namespace UnityEngine {
    typedef void (*UnitySendMessageMethod)(const char *gameObjectName, const char *methodName, const char *message);

    class Managed {
    private:
        intptr_t *_instance;



    public:
        static UnitySendMessageMethod UnitySendMessage;

        ~Managed();

        void newInstance(const char *typeName);
        void setValue(const char *propertyName, void *value);
    };
}