using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.Assertions;

namespace UnityCpp
{
    public abstract class NativeComponent : MonoBehaviour
    {
        private delegate void UnitySendMessageDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string gameObjectName,
            [MarshalAs(UnmanagedType.LPStr)] string methodName,
            [MarshalAs(UnmanagedType.LPStr)] string message
        );

        [DllImport(NativeConstants.nativePluginName, EntryPoint = "CreateNativeInstance")]
        private static extern int CreateNativeInstance(
            [MarshalAs(UnmanagedType.LPStr)] string className, 
            [MarshalAs(UnmanagedType.LPStr)] string gameObjectName
        );
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeAwake", CallingConvention = CallingConvention.Cdecl)]
        private static extern void InvokeNativeAwake(IntPtr handle);
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeStart", CallingConvention = CallingConvention.Cdecl)]
        private static extern void InvokeNativeStart(IntPtr handle);
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "SetUnitySendMessageMethod", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetUnitySendMessageMethod(UnitySendMessageDelegate func);

        

        private IntPtr _nativeHandle;

        private void Awake()
        {
            
            
            string typeName = GetType().Name;
            string objectName = gameObject.name;
            CreateNativeInstance(typeName, objectName);
            // SetUnitySendMessageMethod(UnitySendMessage);
            // _nativeHandle = new IntPtr();
            // 
            //
            // InvokeNativeAwake(_nativeHandle);
        }

        private void Start()
        {
            // InvokeNativeStart(_nativeHandle);
        }

        private static void UnitySendMessage(string gameObjectName, string methodName, string message)
        {
            GameObject.Find(gameObjectName).SendMessage(methodName, message, SendMessageOptions.RequireReceiver);
        }
    }
}
