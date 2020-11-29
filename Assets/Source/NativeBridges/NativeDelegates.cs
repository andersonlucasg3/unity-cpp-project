using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridges
{
    internal static class NativeDelegates
    {
        #region SendMessage

        internal delegate void UnitySendMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string gameObjectName, [MarshalAs(UnmanagedType.LPStr)] string methodName, [MarshalAs(UnmanagedType.LPStr)] string message);

        #endregion

        #region Constructor & Destructor

        internal delegate IntPtr NativeConstructorDelegate([MarshalAs(UnmanagedType.LPStr)] string typeName);

        internal delegate void NativeDestructorDelegate(IntPtr instance);

        #endregion

        #region Getters & Setters

        internal delegate IntPtr NativeGetMemberPtrDelegate(IntPtr intPtr, [MarshalAs(UnmanagedType.LPStr)] string name);
        
        internal delegate TValue NativeGetValuePrimitiveDelegate<out TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type);
        
        internal delegate void NativeSetValuePrimitiveDelegate<in TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value);

        #endregion

        internal enum MemberType : int
        {
            field = 0,
            property,
            method // will be used later
        }
    }
}