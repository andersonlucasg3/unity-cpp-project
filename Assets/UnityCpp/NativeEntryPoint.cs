using System;
using System.Runtime.InteropServices;
using UnityCpp.Loader;
using UnityCpp.NativeBridge;
using UnityEngine;

namespace UnityCpp
{
    using static NativeBridge.NativeDelegates;
    
    public class NativeEntryPoint : MonoBehaviour
    {
        private static SetUnityDebugLogDelegate _setDebugLog;
        private static NativeVoidMethod _initializeNative;
        private static NativeVoidMethod _nativeInitialized;
        
        private IntPtr _nativeAssemblyHandle = IntPtr.Zero;
        
        private void Awake()
        {
            const string assemblyName = NativeConstants.nativeCodeAssemblyName;
            
            _nativeAssemblyHandle = NativeAssembly.Load(assemblyName);
            if (_nativeAssemblyHandle == IntPtr.Zero)
            {
                Debug.Log($"Failed to load native assembly {assemblyName}");
                return;
            }
            _setDebugLog = NativeAssembly.GetMethod<SetUnityDebugLogDelegate>(_nativeAssemblyHandle, "SetUnityDebugLogMethod");
            _initializeNative = NativeAssembly.GetMethod<NativeVoidMethod>(_nativeAssemblyHandle, "InitializeNative");
            _nativeInitialized = NativeAssembly.GetMethod<NativeVoidMethod>(_nativeAssemblyHandle, "NativeInitialized");

            _setDebugLog.Invoke(DebugLog);
            _initializeNative.Invoke();
            NativeMethods.Initialize(_nativeAssemblyHandle);
            _nativeInitialized.Invoke();
        }

        private void OnDestroy()
        {
            if (!NativeAssembly.Unload(_nativeAssemblyHandle))
            {
                Debug.Log("Something went wrong unloading native code handle.");
            }
        }
        
        private static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string message)
        {
            Debug.Log(message);
        }
    }
}