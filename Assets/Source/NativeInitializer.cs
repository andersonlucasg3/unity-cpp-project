using System.Runtime.InteropServices;
using UnityCpp.NativeBridges;
using UnityEngine;

namespace UnityCpp
{
    public class NativeInitializer : MonoBehaviour
    {
        [DllImport(NativeConstants.nativePluginName)]
        private static extern void InitializeNative();

        [DllImport(NativeConstants.nativePluginName)]
        private static extern void NativeInitialized();
        
        [DllImport(NativeConstants.nativePluginName)]
        private static extern void SetUnityDebugLogMethod(UnityDebugLogDelegate action);

        private void Awake()
        {
            SetUnityDebugLogMethod(DebugLog);
            InitializeNative();
            NativeBridge.Initialize();
            
            // native application entry-point
            NativeInitialized();
        }
        
        private static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string message)
        {
            Debug.Log(message);
        }
        
        private delegate void UnityDebugLogDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string message
        );
    }
}