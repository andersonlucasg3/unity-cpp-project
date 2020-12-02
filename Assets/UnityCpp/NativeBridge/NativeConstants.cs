#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
#define UNITY_WINDOWS
#endif

namespace UnityCpp
{
    internal static class NativeConstants
    {
#if UNITY_WINDOWS
#if UNITY_EDITOR
        internal const string nativeCodeAssemblyPath = "/Plugins/NativeComponents/UnityCppLib";
#else
        internal const string nativeCodeAssemblyPath = "/Plugins/UnityCppLib";
#endif
#else
#if UNITY_EDITOR
        internal const string nativeCodeAssemblyPath = "/Plugins/NativeComponents/libUnityCppLib.dylib";
#else
        internal const string nativeCodeAssemblyPath = "/Plugins/libUnityCppLib.dylib";
#endif
#endif
        internal const string nativeLoaderName = "UnityCppAssemblyHelper";
        internal const string nativeGetErrorFuncName = "__GetError";
        internal const string nativeLoadLibraryFuncName = "__LoadLibrary";
        internal const string nativeFreeLibraryFuncName = "__FreeLibrary";
        internal const string nativeGetProcAddressFuncName = "__GetProcAddress";
    }
}