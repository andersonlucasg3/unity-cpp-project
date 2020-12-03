#include "UnmanagedValue.h"

namespace ManagedBridge {
    UnmanagedValue::UnmanagedValue(pointer_m ptr, UnmanagedType type) : ptr(ptr), type(type) { }

    UnmanagedValue::UnmanagedValue(bool value) : ptr(&value), type(::boolType) { }

    UnmanagedValue::UnmanagedValue(byte value) : ptr(&value), type(::boolType) { }
}