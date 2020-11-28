using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp
{
    public class NativeInitializer : MonoBehaviour
    {
        private delegate void UnityDebugLogDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string message
        );
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InitializeNative")]
        private static extern void InitializeNative();
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "SetUnityDebugLogMethod")]
        private static extern void SetUnityDebugLogMethod(UnityDebugLogDelegate action);

        private NativeInitializer()
        {
            InitializeNative();
            SetUnityDebugLogMethod(DebugLog);
        }
        
        private static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string message)
        {
            Debug.Log(message);
        }
    }
}