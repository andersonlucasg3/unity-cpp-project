using System;
using System.Runtime.InteropServices;
using UnityCpp.Loader;

namespace UnityCpp.NativeBridge
{
    using static NativeMethodsImpl;
    
    internal enum MemberType
    {
        constructor = 0,
        field,
        property,
        method
    }

    public static class NativeMethods
    {
        #region SendMessage

        private delegate void UnityDebugLogDelegate([MarshalAs(UnmanagedType.LPStr)] string message);
        private delegate void SetUnityDebugLogDelegate(UnityDebugLogDelegate del);
        private static SetUnityDebugLogDelegate _setDebugLog;

        private delegate void SendMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string gameObjectName, [MarshalAs(UnmanagedType.LPStr)] string methodName, [MarshalAs(UnmanagedType.LPStr)] string message);
        private delegate void SetSendMessageDelegate(SendMessageDelegate del);
        private static SetSendMessageDelegate _setUnitySendMessage;
        
        private delegate void NativeVoidMethod();
        private static NativeVoidMethod _initializeNative;

        #endregion
        
        #region Constructor & Destructor

        private delegate void DestructorDelegate(IntPtr instance);
        private delegate void SetDestructorDelegate(DestructorDelegate del);
        private static SetDestructorDelegate _setManagedDestructor;
        
        #endregion
        
        #region Type

        private delegate IntPtr GetTypePtrDelegate([MarshalAs(UnmanagedType.LPStr)] string assemblyName);
        private delegate void SetManagedGetTypePtrDelegate(GetTypePtrDelegate del);
        private static SetManagedGetTypePtrDelegate _setManagedGetTypePtr;

        private delegate IntPtr GetTypeConstructorPtrDelegate(IntPtr typePtr, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] IntPtr[] parameterTypes, int paramCount);
        private delegate void SetManagedGetTypeConstructorPtrDelegate(GetTypeConstructorPtrDelegate del);
        private static SetManagedGetTypeConstructorPtrDelegate _setManagedGetConstructorPtr;

        private delegate IntPtr GetTypeMemberPtrDelegate(IntPtr typePtr, [MarshalAs(UnmanagedType.LPStr)] string memberName);
        private delegate void SetManagedGetTypeMemberPtrDelegate(GetTypeMemberPtrDelegate del);
        private static SetManagedGetTypeMemberPtrDelegate _setManagedGetMemberPtr;

        private delegate IntPtr ConstructorDelegate(IntPtr constructorPtr, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] IntPtr[] parameters, int paramCount);
        private delegate void SetManagedConstructorDelegate(ConstructorDelegate del);
        private static SetManagedConstructorDelegate _setManagedConstructor;
        
        #endregion

        #region Getters & Setters

        private delegate void GetValueDelegate<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value);
        private delegate void SetValueDelegate<in TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value);

        private delegate void SetManagedGetSetStringDelegate(GetValueDelegate<string> get, SetValueDelegate<string> set);
        private static SetManagedGetSetStringDelegate _setManagedManagedGetSetString;

        private delegate void SetManagedGetSetIntDelegate(GetValueDelegate<int> get, SetValueDelegate<int> set);
        private static SetManagedGetSetIntDelegate _setManagedManagedGetSetInt;

        private delegate void SetManagedGetSetLongDelegate(GetValueDelegate<long> get, SetValueDelegate<long> set);
        private static SetManagedGetSetLongDelegate _setManagedManagedGetSetLong;

        private delegate void SetManagedGetSetFloatDelegate(GetValueDelegate<float> get, SetValueDelegate<float> set);
        private static SetManagedGetSetFloatDelegate _setManagedManagedGetSetFloat;

        private delegate void SetManagedGetSetDoubleDelegate(GetValueDelegate<double> get, SetValueDelegate<double> set);
        private static SetManagedGetSetDoubleDelegate _setManagedManagedGetSetDouble;

        private delegate void SetManagedGetSetObjectDelegate(GetValueDelegate<IntPtr> get, SetValueDelegate<IntPtr> set);
        private static SetManagedGetSetObjectDelegate _setManagedManagedGetSetObject;

        #endregion

        private static void SetEssentialsMethods(IntPtr assemblyHandle)
        {
            _setDebugLog = NativeAssembly.GetMethod<SetUnityDebugLogDelegate>(assemblyHandle, "SetUnityDebugLogMethod");
            _setDebugLog.Invoke(DebugLog);
            
            _setUnitySendMessage = NativeAssembly.GetMethod<SetSendMessageDelegate>(assemblyHandle, "SetUnitySendMessageMethod");
            _setUnitySendMessage.Invoke(UnitySendMessageMethod);

            _setManagedDestructor = NativeAssembly.GetMethod<SetDestructorDelegate>(assemblyHandle, "SetManagedDestructorMethod");
            _setManagedDestructor.Invoke(DestructorMethod);
        }

        private static void SetTypeMethods(IntPtr assemblyHandle)
        {
            _setManagedGetTypePtr = NativeAssembly.GetMethod<SetManagedGetTypePtrDelegate>(assemblyHandle, "SetManagedGetTypePtrMethod");
            _setManagedGetTypePtr.Invoke(GetTypePtr);

            _setManagedGetConstructorPtr = NativeAssembly.GetMethod<SetManagedGetTypeConstructorPtrDelegate>(assemblyHandle, "SetManagedGetConstructorPtrMethod");
            _setManagedGetConstructorPtr.Invoke(GetTypeConstructorPtr);
            
            _setManagedGetMemberPtr = NativeAssembly.GetMethod<SetManagedGetTypeMemberPtrDelegate>(assemblyHandle, "SetManagedGetMemberPtrMethod");
            _setManagedGetMemberPtr.Invoke(GetTypeMemberPtr);

            _setManagedConstructor = NativeAssembly.GetMethod<SetManagedConstructorDelegate>(assemblyHandle, "SetManagedConstructorMethod");
            _setManagedConstructor.Invoke(Constructor);
        }

        private static void SetGetSetMethods(IntPtr assemblyHandle)
        {
            _setManagedManagedGetSetString = NativeAssembly.GetMethod<SetManagedGetSetStringDelegate>(assemblyHandle, "SetManagedGetSetStringMethod");
            _setManagedManagedGetSetString.Invoke(GetMemberValue, SetMemberValue);

            _setManagedManagedGetSetInt = NativeAssembly.GetMethod<SetManagedGetSetIntDelegate>(assemblyHandle, "SetManagedGetSetIntMethod");
            _setManagedManagedGetSetInt.Invoke(GetMemberValue, SetMemberValue);

            _setManagedManagedGetSetLong = NativeAssembly.GetMethod<SetManagedGetSetLongDelegate>(assemblyHandle, "SetManagedGetSetLongMethod");
            _setManagedManagedGetSetLong.Invoke(GetMemberValue, SetMemberValue);

            _setManagedManagedGetSetFloat = NativeAssembly.GetMethod<SetManagedGetSetFloatDelegate>(assemblyHandle, "SetManagedGetSetFloatMethod");
            _setManagedManagedGetSetFloat.Invoke(GetMemberValue, SetMemberValue);

            _setManagedManagedGetSetDouble = NativeAssembly.GetMethod<SetManagedGetSetDoubleDelegate>(assemblyHandle, "SetManagedGetSetDoubleMethod");
            _setManagedManagedGetSetDouble.Invoke(GetMemberValue, SetMemberValue);

            _setManagedManagedGetSetObject = NativeAssembly.GetMethod<SetManagedGetSetObjectDelegate>(assemblyHandle, "SetManagedGetSetObjectMethod");
            _setManagedManagedGetSetObject.Invoke(GetMemberValue, SetMemberValue);
        }
        
        public static void Initialize(IntPtr assemblyHandle)
        {
            SetEssentialsMethods(assemblyHandle);
            SetTypeMethods(assemblyHandle);
            SetGetSetMethods(assemblyHandle);
            
            _initializeNative = NativeAssembly.GetMethod<NativeVoidMethod>(assemblyHandle, "InitializeNative");
            _initializeNative.Invoke();
        }
    }
}