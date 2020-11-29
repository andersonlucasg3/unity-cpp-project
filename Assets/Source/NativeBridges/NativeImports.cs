using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridges
{
    using static NativeDelegates;
    
    internal static class NativeImports
    {
        #region SendMessage
        
        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetUnitySendMessageMethod(UnitySendMessageDelegate func);
        
        #endregion
        
        #region Constructor & Destructor
        
        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedConstructorMethod(NativeConstructorDelegate call);

        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedDestructorMethod(NativeDestructorDelegate call);
        
        #endregion

        #region Getters & Setters

        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetMemberPtrMethod(NativeGetMemberPtrDelegate call);
        
        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetStringMethod(
            NativeGetValuePrimitiveDelegate<string> getCall, 
            NativeSetValuePrimitiveDelegate<string> setCall);

        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetIntMethod(
            NativeGetValuePrimitiveDelegate<int> getCall, 
            NativeSetValuePrimitiveDelegate<int> setCall);
        
        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetLongMethod(
            NativeGetValuePrimitiveDelegate<long> getCall, 
            NativeSetValuePrimitiveDelegate<long> setCall);
        
        
        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetFloatMethod(
            NativeGetValuePrimitiveDelegate<float> getCall, 
            NativeSetValuePrimitiveDelegate<float> setCall);

        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetDoubleMethod(
            NativeGetValuePrimitiveDelegate<double> getCall,
            NativeSetValuePrimitiveDelegate<double> setCall);

        [DllImport(NativeConstants.nativePluginName)]
        internal static extern void SetManagedGetSetObjectMethod(
            NativeGetValuePrimitiveDelegate<IntPtr> getCall,
            NativeSetValuePrimitiveDelegate<IntPtr> setCall);

        #endregion
    }
}