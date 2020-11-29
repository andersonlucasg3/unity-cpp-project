using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridge
{
    internal static class NativeDelegates
    {
        #region Unity Methods

        internal delegate void SendMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string gameObjectName, [MarshalAs(UnmanagedType.LPStr)] string methodName, [MarshalAs(UnmanagedType.LPStr)] string message);
        
        internal delegate void SetSendMessageDelegate(SendMessageDelegate del);

        internal delegate void UnityDebugLogDelegate([MarshalAs(UnmanagedType.LPStr)] string message);
        
        internal delegate void SetUnityDebugLogDelegate(UnityDebugLogDelegate del);

        #endregion

        #region Constructor & Destructor

        internal delegate IntPtr ConstructorDelegate([MarshalAs(UnmanagedType.LPStr)] string typeName);

        internal delegate void SetConstructorDelegate(ConstructorDelegate del);

        internal delegate void DestructorDelegate(IntPtr instance);

        internal delegate void SetDestructorDelegate(DestructorDelegate del);
        
        #endregion

        #region Getters & Setters

        internal delegate void NativeVoidMethod();

        internal delegate IntPtr GetMemberPtrDelegate(IntPtr intPtr, [MarshalAs(UnmanagedType.LPStr)] string name);

        internal delegate void SetGetMemberPtrDelegate(GetMemberPtrDelegate del);
        
        internal delegate void GetValueDelegate<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value);

        internal delegate void SetValueDelegate<in TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value);

        internal delegate void SetGetSetStringDelegate(GetValueDelegate<string> get, SetValueDelegate<string> set);

        internal delegate void SetGetSetIntDelegate(GetValueDelegate<int> get, SetValueDelegate<int> set);

        internal delegate void SetGetSetLongDelegate(GetValueDelegate<long> get, SetValueDelegate<long> set);

        internal delegate void SetGetSetFloatDelegate(GetValueDelegate<float> get, SetValueDelegate<float> set);

        internal delegate void SetGetSetDoubleDelegate(GetValueDelegate<double> get, SetValueDelegate<double> set);

        internal delegate void SetGetSetObjectDelegate(GetValueDelegate<IntPtr> get, SetValueDelegate<IntPtr> set);

        #endregion

        internal enum MemberType
        {
            field = 0,
            property,
            method // will be used later
        }
    }
}