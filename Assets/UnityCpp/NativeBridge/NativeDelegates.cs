using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridge
{
    internal static class NativeDelegates
    {
        #region Unity Methods

        internal delegate void SendMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string gameObjectName, [MarshalAs(UnmanagedType.LPStr)] string methodName, [MarshalAs(UnmanagedType.LPStr)] string message);

        internal delegate void UnityDebugLogDelegate([MarshalAs(UnmanagedType.LPStr)] string message);

        #endregion

        #region Constructor & Destructor

        internal delegate IntPtr ConstructorDelegate([MarshalAs(UnmanagedType.LPStr)] string typeName);

        internal delegate void DestructorDelegate(IntPtr instance);

        #endregion

        #region Getters & Setters

        internal delegate void NativeVoidMethod();

        internal delegate void SetDelegate<in TDelegate>(TDelegate del);

        internal delegate void SetDelegates<in TDelegate1, in TDelegate2>(TDelegate1 del1, TDelegate2 del2);
        
        internal delegate IntPtr GetMemberPtrDelegate(IntPtr intPtr, [MarshalAs(UnmanagedType.LPStr)] string name);
        
        internal delegate void GetValueDelegate<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value);
        
        internal delegate void SetValueDelegate<in TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value);

        #endregion

        internal enum MemberType
        {
            field = 0,
            property,
            method // will be used later
        }
    }
}