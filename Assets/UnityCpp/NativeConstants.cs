namespace UnityCpp
{
    internal static class NativeConstants
    {
#if UNITY_EDITOR_WIN
        internal const string nativeCodeAssemblyName = "UnityCppLib";
        internal const string nativeLoaderName = "kernel32";
#else
        internal const string nativeCodeAssemblyName = "Assets/Plugins/NativeComponents/libUnityCppLib.dylib";
        internal const string nativeLoaderName = "UnityCppAssemblyHelper";
#endif
    }
}