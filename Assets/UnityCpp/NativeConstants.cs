namespace UnityCpp
{
    internal static class NativeConstants
    {
#if UNITY_EDITOR_WIN
        internal const string nativeCodeAssemblyName = "UnityCppLib.dll";
        internal const string nativeLoaderName = "kernel32";

        internal const string nativeLoadLibraryFuncName = "LoadLibrary";
        internal const string nativeFreeLibraryFuncName = "FreeLibrary";
        internal const string nativeGetProcAddressFuncName = "GetProcAddress";
        internal const string nativeGetErrorFuncName = "GetLastError";
#else
        internal const string nativeCodeAssemblyName = "Assets/Plugins/NativeComponents/libUnityCppLib.dylib";
        internal const string nativeLoaderName = "UnityCppAssemblyHelper";
        internal const string nativeGetErrorFuncName = "GetError";
#endif
    }
}