#include "UnmanagedValue.h"
#include "UnityAPI/Helpers/Helpers.h"

using namespace Helpers;

namespace ManagedBridge {
    template<typename TValue>
    pointer_m createValue(TValue value) {
        TValue *alloc = (TValue *)malloc(sizeof(TValue));
        alloc[0] = value;
        return alloc;
    }

    UnmanagedValue::UnmanagedValue(pointer_m ptr, UnmanagedType type) : ptr(ptr), type(type) { }

    UnmanagedValue::UnmanagedValue(bool value) {
        ptr = createValue(value);
        type = ::boolType;
    }

    UnmanagedValue::UnmanagedValue(byte value) {
        ptr = createValue(value);
        type = ::byteType;
    }

    UnmanagedValue::UnmanagedValue(short value) {
        ptr = createValue(value);
        type = ::shortType;
    }

    UnmanagedValue::UnmanagedValue(ushort value) {
        ptr = createValue(value);
        type = ::ushortType;
    }

    UnmanagedValue::UnmanagedValue(int value) {
        ptr = createValue(value);
        type = ::intType;
    }

    UnmanagedValue::UnmanagedValue(uint value) {
        ptr = createValue(value);
        type = ::uintType;
    }

    UnmanagedValue::UnmanagedValue(long value) {
        ptr = createValue(value);
        type = ::longType;
    }

    UnmanagedValue::UnmanagedValue(ulong value) {
        ptr = createValue(value);
        type = ::ulongType;
    }

    UnmanagedValue::UnmanagedValue(float value) {
        ptr = createValue(value);
        type = ::floatType;
    }

    UnmanagedValue::UnmanagedValue(double value) {
        ptr = createValue(value);
        type = ::doubleType;
    }

    UnmanagedValue::UnmanagedValue(string_m value) {
        ptr = stringInstance(value);
        type = ::stringType;
    }

    UnmanagedValue::UnmanagedValue(string_c value) {
        ptr = stringInstance(value);
        type = ::stringType;
    }

    UnmanagedValue::UnmanagedValue(pointer_c value) {
        ptr = (pointer_m)value;
        type = ::pointerType;
    }

    UnmanagedValue::UnmanagedValue(pointer_m value) {
        ptr = value;
        type = ::pointerType;
    }

    UnmanagedValue::~UnmanagedValue() {
        if (type == ::pointerType) return;

        if (type == ::stringType) {
            freeStringInstance((string_m)ptr);
            return;
        }

        if (type >= ::boolType) free(ptr);
    }
}