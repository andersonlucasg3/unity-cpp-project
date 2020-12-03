#pragma once

#include "UnityAPI/NetFramework/System.h"

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
        intPtrType
    };

    struct [[maybe_unused]] UnmanagedValue {
    private:
        pointer_m ptr;
        UnmanagedType type;

    public:
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
    } __attribute__((aligned(16)));
}