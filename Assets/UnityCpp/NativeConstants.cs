using UnityEngine;

namespace UnityCpp
{
    internal static class NativeConstants
    {
#if UNITY_EDITOR_WIN
        internal const string nativeCodeAssemblyPath = "Assets/Plugins/NativeComponents/UnityCppLib";
#else
        internal const string nativeCodeAssemblyPath = "Assets/Plugins/NativeComponents/libUnityCppLib.dylib";
#endif
        internal const string nativeLoaderName = "UnityCppAssemblyHelper";
        internal const string nativeGetErrorFuncName = "__GetError";
        internal const string nativeLoadLibraryFuncName = "__LoadLibrary";
        internal const string nativeFreeLibraryFuncName = "__FreeLibrary";
        internal const string nativeGetProcAddressFuncName = "__GetProcAddress";
    }
}