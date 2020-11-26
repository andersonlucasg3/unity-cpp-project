using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp
{
    public abstract class NativeComponent : MonoBehaviour
    {
        [DllImport("__Internal", EntryPoint = "CreateCustomClassHandle")]
        private static extern IntPtr CreateCustomClassHandle(string className);
        [DllImport("__Internal", EntryPoint = "InvokeNativeAwake")]
        private static extern void InvokeNativeAwake(IntPtr handle);
        [DllImport("__Internal", EntryPoint = "InvokeNativeStart")]
        private static extern void InvokeNativeStart(IntPtr handle);

        private readonly IntPtr _nativeHandle;

        protected NativeComponent() : base()
        {
            _nativeHandle = CreateCustomClassHandle(GetType().Name);
        }

        private void Awake()
        {
            InvokeNativeAwake(_nativeHandle);            
        }

        private void Start()
        {
            InvokeNativeStart(_nativeHandle);
        }
    }
}
