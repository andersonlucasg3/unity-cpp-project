#include "UnmanagedValue.h"
#include "UnityAPI/Helpers/Helpers.h"

using namespace Helpers;

namespace ManagedBridge {
    template<typename TValue>
    pointer_m createValue(TValue value) {
        TValue *alloc = (TValue *)malloc(sizeof(TValue));
        (*alloc) = value;
        return alloc;
    }

    template<typename TValue>
    TValue getValue(pointer_m pointer) {
        TValue *value = (TValue *)pointer;
        return *value;
    }

    UnmanagedValue::UnmanagedValue() : ptr(nullptr), type(::pointerType) { }

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

    UnmanagedValue::operator bool() const {
        return getValue<bool>(ptr);
    }

    UnmanagedValue::operator byte() const {
        return getValue<byte>(ptr);
    }

    UnmanagedValue::operator short() const {
        return getValue<short>(ptr);
    }

    UnmanagedValue::operator ushort() const {
        return getValue<ushort>(ptr);
    }

    UnmanagedValue::operator int() const {
        return getValue<int>(ptr);
    }

    UnmanagedValue::operator uint() const {
        return getValue<uint>(ptr);
    }

    UnmanagedValue::operator long() const {
        return getValue<long>(ptr);
    }
    UnmanagedValue::operator ulong() const {
        return getValue<ulong>(ptr);
    }

    UnmanagedValue::operator float() const {
        return getValue<float>(ptr);
    }

    UnmanagedValue::operator double() const {
        return getValue<double>(ptr);
    }

    UnmanagedValue::operator string_c() const {
        return (string_c)ptr;
    }

    UnmanagedValue::operator string_m() const {
        return (string_m)ptr;
    }

    UnmanagedValue::operator pointer_c() const {
        return ptr;
    }

    UnmanagedValue::operator pointer_m() const {
        return ptr;
    }
}