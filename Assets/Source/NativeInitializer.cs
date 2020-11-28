using System.Runtime.InteropServices;
using UnityCpp.NativeBridges;
using UnityEngine;

namespace UnityCpp
{
    public class NativeInitializer : MonoBehaviour
    {
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InitializeNative")]
        private static extern void InitializeNative();
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "SetUnityDebugLogMethod")]
        private static extern void SetUnityDebugLogMethod(UnityDebugLogDelegate action);
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "SetUnitySendMessageMethod", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetUnitySendMessageMethod(UnitySendMessageDelegate func);

        private void Awake()
        {
            SetUnityDebugLogMethod(DebugLog);
            SetUnitySendMessageMethod(UnitySendMessage);
            InitializeNative();
            NativeBridge.Initialize();
        }
        
        private static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string message)
        {
            Debug.Log(message);
        }
        
        private static void UnitySendMessage(string gameObjectName, string methodName, string message)
        {
            GameObject.Find(gameObjectName).SendMessage(methodName, message, SendMessageOptions.RequireReceiver);
        }
        
        private delegate void UnityDebugLogDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string message
        );
        
        private delegate void UnitySendMessageDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string gameObjectName,
            [MarshalAs(UnmanagedType.LPStr)] string methodName,
            [MarshalAs(UnmanagedType.LPStr)] string message
        );
    }
}