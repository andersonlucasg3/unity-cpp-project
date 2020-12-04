#pragma once

#include <cstdint>

#if defined(__APPLE__) || defined(__MACH__)

#ifndef UNITY_EXPORT
#define UNITY_EXPORT
#endif

#ifndef UNITY_IMPORT
#define UNITY_IMPORT
#endif

#ifndef UNITY_METHOD
#define UNITY_METHOD
#endif

#ifndef STRUCT_ALIGN
#define STRUCT_ALIGN __attribute__((aligned(16)))
#endif

#else

#ifndef UNITY_EXPORT
#define UNITY_EXPORT __declspec(dllexport)
#endif

#ifndef UNITY_IMPORT
#define UNITY_IMPORT __declspec(dllimport)
#endif

#ifndef UNITY_METHOD
#define UNITY_METHOD __cdecl
#endif

#ifndef STRUCT_ALIGN
#define STRUCT_ALIGN
#endif

#endif