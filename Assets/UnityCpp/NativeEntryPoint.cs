using System;
using UnityCpp.Loader;
using UnityCpp.NativeBridge;
using UnityEngine;

namespace UnityCpp
{
    public class NativeEntryPoint : MonoBehaviour
    {
        private IntPtr _nativeAssemblyHandle = IntPtr.Zero;
        
        private void Awake()
        {
            const string assemblyName =  NativeConstants.nativeCodeAssemblyPath;

            _nativeAssemblyHandle = NativeAssembly.Load(assemblyName);
            if (_nativeAssemblyHandle == IntPtr.Zero)
            {
                Debug.Log($"Failed to load native assembly {assemblyName}");
                return;
            }
            
            NativeMethods.Initialize(_nativeAssemblyHandle);
        }

        private void OnDestroy()
        {
            if (!NativeAssembly.Unload(_nativeAssemblyHandle))
            {
                Debug.Log("Something went wrong unloading native code handle.");
            }
        }
    }
}