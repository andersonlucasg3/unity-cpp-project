#pragma once

#include "UnityAPI/NetFramework/System.h"
#include "UnityAPI/UnityAPIExtern.h"

#include <iostream>

using namespace System;
using namespace std;

namespace ManagedBridge {
    enum UnmanagedType {
        boolType = 0,
        byteType,
        shortType,
        ushortType,
        intType,
        uintType,
        longType,
        ulongType,
        floatType,
        doubleType,
        stringType,
        pointerType
    };

    struct UnmanagedValue {
    private:
        pointer_m ptr;
        UnmanagedType type;

    public:
        [[maybe_unused]] explicit UnmanagedValue(UnmanagedType type);
        [[maybe_unused]] UnmanagedValue(pointer_m ptr, UnmanagedType type);
        [[maybe_unused]] UnmanagedValue(bool value);
        [[maybe_unused]] UnmanagedValue(byte value);
        [[maybe_unused]] UnmanagedValue(short value);
        [[maybe_unused]] UnmanagedValue(ushort value);
        [[maybe_unused]] UnmanagedValue(int value);
        [[maybe_unused]] UnmanagedValue(uint value);
        [[maybe_unused]] UnmanagedValue(long value);
        [[maybe_unused]] UnmanagedValue(ulong value);
        [[maybe_unused]] UnmanagedValue(float value);
        [[maybe_unused]] UnmanagedValue(double value);
        [[maybe_unused]] UnmanagedValue(string_c value);
        [[maybe_unused]] UnmanagedValue(string_m value);
        [[maybe_unused]] UnmanagedValue(pointer_c value);
        [[maybe_unused]] UnmanagedValue(pointer_m value);
        ~UnmanagedValue();

        operator bool() const;
        operator byte() const;
        operator short() const;
        operator ushort() const;
        operator int() const;
        operator uint() const;
        operator long() const;
        operator ulong() const;
        operator float() const;
        operator double() const;
        operator string_c() const;
        operator string_m() const;
        operator pointer_c() const;
        operator pointer_m() const;
    } STRUCT_ALIGN;
}