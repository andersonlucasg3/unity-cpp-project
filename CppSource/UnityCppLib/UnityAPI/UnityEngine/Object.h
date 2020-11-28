#pragma once

namespace UnityEngine {
    class Managed;

    class Object {
    private:
        Managed *_managed;

    protected:
        Object();
        ~Object();

        void setValue(const char *propertyName, void *value);
    };
}