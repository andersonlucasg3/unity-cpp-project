namespace UnityCpp
{
    internal static class NativeConstants
    {
        internal const string nativeCodeAssemblyName = "UnityCppLib";
#if UNITY_EDITOR_WIN
        internal const string nativeLoaderName = "kernel32";
#else
        internal const string nativeLoaderName = "UnityCppAssemblyHelper";
#endif
    }
}