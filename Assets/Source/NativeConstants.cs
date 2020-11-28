namespace UnityCpp
{
    internal static class NativeConstants
    {
#if UNITY_EDITOR_WIN
        internal const string nativePluginName = "CppSource.dll";
#endif
#if UNITY_EDITOR_OSX
        internal const string nativePluginName = "CppSource";
#endif
    }
}