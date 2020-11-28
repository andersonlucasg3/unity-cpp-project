using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridges
{
    public static class NativeBridge
    {
        [DllImport(NativeConstants.nativePluginName)]
        private static extern void SetManagedConstructorCallMethod(NativeNewCallDelegate call);

        [DllImport(NativeConstants.nativePluginName)]
        private static extern void SetManagedDestroyCallMethod(NativeDestroyCallDelegate call);

        [DllImport(NativeConstants.nativePluginName)]
        private static extern void SetManagedSetValueMethod(NativeSetValueCallDelegate call);

        public static void Initialize()
        {
            SetManagedConstructorCallMethod(NativeBridgeImpl.ConstructorCallMethod);
            SetManagedDestroyCallMethod(NativeBridgeImpl.DestroyCallMethod);
            SetManagedSetValueMethod(NativeBridgeImpl.SetValueCallMethod);
        }

        private delegate IntPtr NativeNewCallDelegate(
            [MarshalAs(UnmanagedType.LPStr)] string typeName
            );
        
        private delegate void NativeDestroyCallDelegate(IntPtr instance);
        
        private delegate void NativeSetValueCallDelegate(
            IntPtr instance, 
            [MarshalAs(UnmanagedType.LPStr)] string property, 
            [MarshalAs(UnmanagedType.AsAny)] object value
            );
    }
}