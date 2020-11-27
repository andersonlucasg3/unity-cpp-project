using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp
{
    public abstract class NativeComponent : MonoBehaviour
    {
#if UNITY_EDITOR_WIN
        private const string _nativePluginName = "CppSource.dll";
#endif
#if UNITY_EDITOR_OSX
        private const string _nativePluginName = "libCppSource.dylib";
#endif

        private delegate void UnitySendMessageDelegate(
            string gameObjectName,
            string methodName,
            string message
        );

        [DllImport(_nativePluginName, EntryPoint = "SetUnitySendMessageMethod")]
        private static extern void SetUnitySendMessageMethod(UnitySendMessageDelegate func);
        [DllImport(_nativePluginName, EntryPoint = "CreateCustomClassHandle")]
        private static extern long CreateCustomClassHandle(string className, string gameObjectName);
        [DllImport(_nativePluginName, EntryPoint = "InvokeNativeAwake")]
        private static extern void InvokeNativeAwake(long handle);
        [DllImport(_nativePluginName, EntryPoint = "InvokeNativeStart")]
        private static extern void InvokeNativeStart(long handle);

        private long _nativeHandle;

        private void Awake()
        {
            _nativeHandle = CreateCustomClassHandle(GetType().Name, gameObject.name);

            InvokeNativeAwake(_nativeHandle);            
        }

        private void Start()
        {
            InvokeNativeStart(_nativeHandle);
        }

        public void DoLog(string message)
        {
            Debug.Log(message);
        }
    }
}
