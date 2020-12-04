using System;
using System.Reflection;
using System.Runtime.InteropServices;
using AOT;
using UnityCpp.Loader;
using UnityEngine;
using Object = System.Object;

namespace UnityCpp.NativeBridge
{
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
        private delegate void SetUnityDebugLogDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityDebugLogDelegate del);
        private static SetUnityDebugLogDelegate _setDebugLog;

        private delegate void UnitySendMessageDelegate([MarshalAs(UnmanagedType.LPStr)] string gameObjectName, [MarshalAs(UnmanagedType.LPStr)] string methodName, [MarshalAs(UnmanagedType.LPStr)] string message);
        private delegate void SetSendMessageDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnitySendMessageDelegate del);
        private static SetSendMessageDelegate _setUnitySendMessage;
        
        private delegate void NativeVoidMethod();
        private static NativeVoidMethod _initializeNative;

        #endregion
        
        #region Constructor & Destructor

        private delegate void UnityDestructorDelegate(IntPtr instance);
        private delegate void SetDestructorDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityDestructorDelegate del);
        private static SetDestructorDelegate _setManagedDestructor;
        
        #endregion
        
        #region Type

        private delegate IntPtr UnityGetTypePtrDelegate([MarshalAs(UnmanagedType.LPStr)] string assemblyName);
        private delegate void SetManagedGetTypePtrDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityGetTypePtrDelegate del);
        private static SetManagedGetTypePtrDelegate _setManagedGetTypePtr;

        private delegate IntPtr UnityGetTypeConstructorPtrDelegate(IntPtr typePtr, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] IntPtr[] parameterTypes, int paramCount);
        private delegate void SetManagedGetTypeConstructorPtrDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityGetTypeConstructorPtrDelegate del);
        private static SetManagedGetTypeConstructorPtrDelegate _setManagedGetConstructorPtr;

        private delegate IntPtr UnityGetTypeMemberPtrDelegate(IntPtr typePtr, [MarshalAs(UnmanagedType.LPStr)] string memberName, MemberType memberType);
        private delegate void SetManagedGetTypeMemberPtrDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityGetTypeMemberPtrDelegate del);
        private static SetManagedGetTypeMemberPtrDelegate _setManagedGetMemberPtr;

        private delegate IntPtr UnityConstructorDelegate(IntPtr constructorPtr, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] UnmanagedValue[] parameters, int paramCount);
        private delegate void SetManagedConstructorDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityConstructorDelegate del);
        private static SetManagedConstructorDelegate _setManagedConstructor;
        
        #endregion

        #region Getters & Setters

        private delegate void GetValueDelegate(IntPtr intPtr, IntPtr memberPtr, MemberType type, ref UnmanagedValue value);
        private delegate void SetValueDelegate(IntPtr intPtr, IntPtr memberPtr, MemberType type, UnmanagedValue value);
        
        private delegate void SetManagedGetSetValueDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate set);
        private static SetManagedGetSetValueDelegate _setManagedGetSetValue;

        #endregion

        private static void SetEssentialsMethods(IntPtr assemblyHandle)
        {
            _setDebugLog = NativeAssembly.GetMethod<SetUnityDebugLogDelegate>(assemblyHandle, "SetUnityDebugLogMethod");
            _setDebugLog.Invoke(DebugLog);
            
            _setUnitySendMessage = NativeAssembly.GetMethod<SetSendMessageDelegate>(assemblyHandle, "SetUnitySendMessageMethod");
            _setUnitySendMessage.Invoke(UnitySendMessageMethod);
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
            
            _setManagedDestructor = NativeAssembly.GetMethod<SetDestructorDelegate>(assemblyHandle, "SetManagedDestructorMethod");
            _setManagedDestructor.Invoke(Destructor);
        }

        private static void SetGetSetMethods(IntPtr assemblyHandle)
        {
            _setManagedGetSetValue = NativeAssembly.GetMethod<SetManagedGetSetValueDelegate>(assemblyHandle, "SetManagedGetSetValueMethod");
            _setManagedGetSetValue.Invoke(GetMemberValue, SetMemberValue);
        }
        
        public static void Initialize(IntPtr assemblyHandle)
        {
            SetEssentialsMethods(assemblyHandle);
            SetTypeMethods(assemblyHandle);
            SetGetSetMethods(assemblyHandle);
            
            _initializeNative = NativeAssembly.GetMethod<NativeVoidMethod>(assemblyHandle, "InitializeNative");
            _initializeNative.Invoke();
        }
        
        #region Implementations
        
        #region Unity methods

        [MonoPInvokeCallback(typeof(UnityDebugLogDelegate))]
        internal static void DebugLog(string message)
        {
            Debug.Log(message);
        }
        
        [MonoPInvokeCallback(typeof(UnitySendMessageDelegate))]
        private static void UnitySendMessageMethod(string gameObjectName, string methodName, string message)
        {
            GameObject.Find(gameObjectName).SendMessage(methodName, message, SendMessageOptions.RequireReceiver);
        }

        #endregion
        
        #region Types methods

        [MonoPInvokeCallback(typeof(UnityGetTypePtrDelegate))]
        private static IntPtr GetTypePtr(string assemblyName)
        {
            Type type = Type.GetType(assemblyName);
            return (IntPtr)GCHandle.Alloc(type);
        }

        [MonoPInvokeCallback(typeof(UnityGetTypeConstructorPtrDelegate))]
        private static IntPtr GetTypeConstructorPtr(IntPtr typePtr, IntPtr[] parameterTypes, int paramCount)
        {
            Type type = ConvertPtrTo<Type>(typePtr);
            Type[] types = new Type[paramCount];
            for (int index = 0; index < paramCount; index++)
            {
                types[index] = ConvertPtrTo<Type>(parameterTypes[index]);
            }
            ConstructorInfo info = type.GetConstructor(types);
            return AllocObjectPtr(info);
        }

        [MonoPInvokeCallback(typeof(UnityGetTypeMemberPtrDelegate))]
        private static IntPtr GetTypeMemberPtr(IntPtr typePtr, string name, MemberType memberType)
        {
            return AllocMemberPtr(typePtr, name, memberType);
        }

        [MonoPInvokeCallback(typeof(UnityConstructorDelegate))]
        private static IntPtr Constructor(IntPtr constructorPtr, UnmanagedValue[] parameters, int paramCount)
        {
            ConstructorInfo info = ConvertPtrTo<ConstructorInfo>(constructorPtr);
            object[] objects = new object[paramCount];
            for (int index = 0; index < paramCount; index++)
            {
                objects[index] = parameters[index].ToManaged();
            }

            object instance = info.Invoke(objects);
            return AllocObjectPtr(instance);
        }

        [MonoPInvokeCallback(typeof(UnityDestructorDelegate))]
        private static void Destructor(IntPtr intPtr)
        {
            GCHandle handle = (GCHandle) intPtr;
            handle.Free();
        }
        
        #endregion

        #region Getter & Setter

        private static void GetMemberValue(IntPtr intPtr, IntPtr memberPtr, MemberType type, ref UnmanagedValue value)
        {
            object objectInstance;
            object valueInstance;
            switch (type)
            {
                case MemberType.field:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    valueInstance = fieldInfo.GetValue(objectInstance);
                    value.FromManaged(valueInstance);
                    break;
                case MemberType.property:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    valueInstance = propertyInfo.GetValue(objectInstance);
                    value.FromManaged(valueInstance);
                    return;
                case MemberType.method:
                    throw new MissingMethodException();
                case MemberType.constructor:
                    throw new MissingMemberException();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }
        
        private static void SetMemberValue(IntPtr intPtr, IntPtr memberPtr, MemberType type, UnmanagedValue value)
        {
            object objectInstance;
            switch (type)
            {
                case MemberType.field:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    fieldInfo.SetValue(objectInstance, value.ToManaged());
                }
                    break;

                case MemberType.property:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    propertyInfo.SetValue(objectInstance, value.ToManaged());
                }
                    break;
                case MemberType.method:
                    throw new MissingMethodException();
                case MemberType.constructor:
                    throw new MissingMemberException();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }

        #endregion

        #region Private methods

        private static IntPtr AllocMemberPtr(IntPtr typePtr, string name, MemberType memberType)
        {
            if (TryGetMember(typePtr, name, memberType, out MemberInfo info))
            {
                return (IntPtr) GCHandle.Alloc(info);
            }

            return IntPtr.Zero;
        }

        private static IntPtr AllocObjectPtr(object objectInstance)
        {
            if (objectInstance == null)
            {
                return IntPtr.Zero;
            }
            return (IntPtr) GCHandle.Alloc(objectInstance);
        }

        private static TOutput ConvertPtrTo<TOutput>(IntPtr intPtr)
        {
            GCHandle handle = (GCHandle) intPtr;
            return (TOutput) handle.Target;
        }

        private static bool TryGetMember(IntPtr typePtr, string name, MemberType memberType, out MemberInfo memberInfo)
        {
            Type type = ConvertPtrTo<Type>(typePtr);
            const BindingFlags flags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance;
            switch (memberType)
            {
                case MemberType.field: memberInfo = type.GetField(name, flags); break;
                case MemberType.property: memberInfo = type.GetProperty(name, flags); break;
                case MemberType.method: memberInfo = type.GetMethod(name, flags); break;
                default:
                    throw new MissingMemberException();
            }
            if (memberInfo != null) return true;
#if DEBUG
            Debug.Log($"Available members: {string.Join(", ", Array.ConvertAll(type.GetMembers(flags), each => $"{each.Name}: {each.GetType()}"))}");
#endif
            Debug.LogError($"Unmanaged code trying to get member {name} of type {type} that does not exists.");
            return false;
        }

        private static void GetObjectAndInfo<TInfo>(IntPtr objectPtr, IntPtr infoPtr, out object objectInstance, out TInfo info)
        {
            objectInstance = ConvertPtrTo<object>(objectPtr);
            info = ConvertPtrTo<TInfo>(infoPtr);
        }

        #endregion
        
        #endregion
    }
}