using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp.Loader
{
    public static class NativeAssembly
    {
        [DllImport(NativeConstants.nativeLoaderName, EntryPoint = "LoadLibrary", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr _LoadLibrary([MarshalAs(UnmanagedType.LPStr)] string assemblyName);
        
        [DllImport(NativeConstants.nativeLoaderName, EntryPoint = "FreeLibrary", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool _FreeLibrary(IntPtr handle);

        [DllImport(NativeConstants.nativeLoaderName, EntryPoint = "GetProcAddress")]
        private static extern IntPtr _GetProcAddress(IntPtr handle, [MarshalAs(UnmanagedType.LPStr)] string methodName);

        [DllImport(NativeConstants.nativeLoaderName, EntryPoint = "GetError")]
        [return: MarshalAs(UnmanagedType.LPStr)]
        private static extern string _GetError();
        
        public static IntPtr Load(string fileName) => LoadLibrary(fileName);

        public static bool Unload(IntPtr handle) => FreeLibrary(handle);

        public static TMethod GetMethod<TMethod>(IntPtr handle, string methodName) where TMethod : class
        {
            if (handle == IntPtr.Zero)
            {
                Debug.Log($"NULL handle, cannot get method {methodName}");
                return null;
            }

            IntPtr methodPtr = GetProcAddress(handle, methodName);
            if (methodPtr != IntPtr.Zero) return Marshal.GetDelegateForFunctionPointer<TMethod>(methodPtr);

            Debug.Log($"NULL method handle, could not find method {methodName}");
            return null;
        }
        
        private static IntPtr LoadLibrary(string fileName)
        {
            IntPtr handle = _LoadLibrary(fileName);
            string error = _GetError();
            if (string.IsNullOrEmpty(error)) return handle;
            Debug.Log($"Could not load assembly {fileName}\n{error}");
            return IntPtr.Zero;
        }

        private static bool FreeLibrary(IntPtr module)
        {
            if (module == IntPtr.Zero)
            {
                Debug.Log("NULL module");
                return false;
            }
            if (_FreeLibrary(module))
            {
                return true;
            }

            string error = _GetError();
            Debug.Log($"Failed to free module.\n{error}");
            return false;
        }

        private static IntPtr GetProcAddress(IntPtr module, string methodName)
        {
            if (module == IntPtr.Zero)
            {
                Debug.Log("Could not load method, null module.");
                return IntPtr.Zero;
            }

            IntPtr methodPtr = _GetProcAddress(module, methodName);
            string error = _GetError();
            if (string.IsNullOrEmpty(error)) return methodPtr;
            Debug.Log($"Could not load method symbol {methodName}.\n{error}");
            return IntPtr.Zero;
        }
    }
}