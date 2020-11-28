using System;
using System.Runtime.InteropServices;
using UnityCpp.UnityEngineFacade;
using UnityEngine;
using UnityEngine.Assertions;

namespace UnityCpp
{
    public abstract class NativeComponent : MonoBehaviour
    {
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "CreateNativeInstance")]
        private static extern IntPtr CreateNativeInstance(
            [MarshalAs(UnmanagedType.LPStr)] string className, 
            [MarshalAs(UnmanagedType.Struct)] GameObjectFacade gameObjectName
        );
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeAwake")]
        private static extern void InvokeNativeAwake(IntPtr handle);
        
        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeStart")]
        private static extern void InvokeNativeStart(IntPtr handle);

        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeUpdate")]
        private static extern void InvokeNativeUpdate(IntPtr handle);

        [DllImport(NativeConstants.nativePluginName, EntryPoint = "InvokeNativeLateUpdate")]
        private static extern void InvokeNativeLateUpdate(IntPtr handle);
        
        private IntPtr _nativeHandle;
        private GameObjectFacade _gameObjectFacade;

        private void Awake()
        {
            string typeName = GetType().Name;
            _gameObjectFacade = new GameObjectFacade(gameObject);
            _nativeHandle = CreateNativeInstance(typeName, _gameObjectFacade);
            InvokeNativeAwake(_nativeHandle);
        }

        private void Start()
        {
            InvokeNativeStart(_nativeHandle);
        }

        private void Update()
        {
            InvokeNativeUpdate(_nativeHandle);
        }

        private void LateUpdate()
        {
            InvokeNativeLateUpdate(_nativeHandle);
        }
    }
}
