#pragma once

#include <cstdint>

#ifndef UNITY_EXPORT
#define UNITY_EXPORT __declspec(dllexport)
#endif

#ifndef UNITY_IMPORT
#define UNITY_IMPORT __declspec(dllimport)
#endif

#ifndef UNITY_METHOD
#define UNITY_METHOD __cdecl
#endif