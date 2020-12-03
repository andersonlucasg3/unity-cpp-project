using System;
using System.Reflection;
using System.Runtime.InteropServices;
using AOT;
using UnityCpp.Loader;
using UnityEngine;

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

        private delegate IntPtr UnityConstructorDelegate(IntPtr constructorPtr, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] IntPtr[] parameters, int paramCount);
        private delegate void SetManagedConstructorDelegate([MarshalAs(UnmanagedType.FunctionPtr)] UnityConstructorDelegate del);
        private static SetManagedConstructorDelegate _setManagedConstructor;
        
        #endregion

        #region Getters & Setters

        private delegate void GetValueDelegate<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value);
        private delegate void SetValueDelegate<in TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value);
        
        private delegate void SetManagedGetSetStringDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<string> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<string> set);
        private static SetManagedGetSetStringDelegate _setManagedGetSetString;

        private delegate void SetManagedGetSetBoolDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<bool> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<bool> set);

        private static SetManagedGetSetBoolDelegate _setManagedGetSetBool;

        private delegate void SetManagedGetSetIntDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<int> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<int> set);
        private static SetManagedGetSetIntDelegate _setManagedGetSetInt;

        private delegate void SetManagedGetSetUIntDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<uint> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<uint> set);
        private static SetManagedGetSetUIntDelegate _setManagedGetSetUInt;

        private delegate void SetManagedGetSetLongDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<long> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<long> set);
        private static SetManagedGetSetLongDelegate _setManagedGetSetLong;

        private delegate void SetManagedGetSetULongDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<ulong> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<ulong> set);
        private static SetManagedGetSetULongDelegate _setManagedGetSetULong;

        private delegate void SetManagedGetSetFloatDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<float> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<float> set);
        private static SetManagedGetSetFloatDelegate _setManagedGetSetFloat;

        private delegate void SetManagedGetSetDoubleDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<double> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<double> set);
        private static SetManagedGetSetDoubleDelegate _setManagedGetSetDouble;

        private delegate void SetManagedGetSetObjectDelegate([MarshalAs(UnmanagedType.FunctionPtr)] GetValueDelegate<IntPtr> get, [MarshalAs(UnmanagedType.FunctionPtr)] SetValueDelegate<IntPtr> set);
        private static SetManagedGetSetObjectDelegate _setManagedGetSetObject;

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
            _setManagedGetSetString = NativeAssembly.GetMethod<SetManagedGetSetStringDelegate>(assemblyHandle, "SetManagedGetSetStringMethod");
            _setManagedGetSetString.Invoke(GetValueString, SetValueString);

            _setManagedGetSetBool = NativeAssembly.GetMethod<SetManagedGetSetBoolDelegate>(assemblyHandle, "SetManagedGetSetBoolMethod");
            _setManagedGetSetBool.Invoke(GetValueBool, SetValueBool);

            _setManagedGetSetInt = NativeAssembly.GetMethod<SetManagedGetSetIntDelegate>(assemblyHandle, "SetManagedGetSetIntMethod");
            _setManagedGetSetInt.Invoke(GetValueInt, SetValueInt);

            _setManagedGetSetUInt = NativeAssembly.GetMethod<SetManagedGetSetUIntDelegate>(assemblyHandle, "SetManagedGetSetUIntMethod");
            _setManagedGetSetUInt.Invoke(GetValueUInt, SetValueUInt);

            _setManagedGetSetLong = NativeAssembly.GetMethod<SetManagedGetSetLongDelegate>(assemblyHandle, "SetManagedGetSetLongMethod");
            _setManagedGetSetLong.Invoke(GetValueLong, SetValueLong);

            _setManagedGetSetULong = NativeAssembly.GetMethod<SetManagedGetSetULongDelegate>(assemblyHandle, "SetManagedGetSetULongMethod");
            _setManagedGetSetULong.Invoke(GetValueULong, SetValueULong);

            _setManagedGetSetFloat = NativeAssembly.GetMethod<SetManagedGetSetFloatDelegate>(assemblyHandle, "SetManagedGetSetFloatMethod");
            _setManagedGetSetFloat.Invoke(GetValueFloat, SetValueFloat);

            _setManagedGetSetDouble = NativeAssembly.GetMethod<SetManagedGetSetDoubleDelegate>(assemblyHandle, "SetManagedGetSetDoubleMethod");
            _setManagedGetSetDouble.Invoke(GetValueDouble, SetValueDouble);

            _setManagedGetSetObject = NativeAssembly.GetMethod<SetManagedGetSetObjectDelegate>(assemblyHandle, "SetManagedGetSetObjectMethod");
            _setManagedGetSetObject.Invoke(GetValuePointer, SetValuePointer);
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
        private static IntPtr Constructor(IntPtr constructorPtr, IntPtr[] parameters, int paramCount)
        {
            ConstructorInfo info = ConvertPtrTo<ConstructorInfo>(constructorPtr);
            object[] objects = new object[paramCount];
            for (int index = 0; index < paramCount; index++)
            {
                objects[index] = ConvertPtrTo<object>(parameters[index]);
            }

            object instance = info.Invoke(objects);
            return AllocObjectPtr(instance);
        }

        [MonoPInvokeCallback(typeof(UnityDestructorDelegate))]
        private static void DestructorMethod(IntPtr intPtr)
        {
            GCHandle handle = (GCHandle) intPtr;
            handle.Free();
        }
        
        #endregion

        #region Getters

        [MonoPInvokeCallback(typeof(GetValueDelegate<string>))]
        private static void GetValueString(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out string value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<bool>))]
        private static void GetValueBool(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out bool value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<int>))]
        private static void GetValueInt(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out int value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<uint>))]
        private static void GetValueUInt(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out uint value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<long>))]
        private static void GetValueLong(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out long value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<ulong>))]
        private static void GetValueULong(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out ulong value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<float>))]
        private static void GetValueFloat(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out float value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<double>))]
        private static void GetValueDouble(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out double value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        [MonoPInvokeCallback(typeof(GetValueDelegate<IntPtr>))]
        private static void GetValuePointer(IntPtr instancePtr, IntPtr memberPtr, MemberType type, out IntPtr value) => GetMemberValue(instancePtr, memberPtr, type, out value);
        
        private static void GetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value)
        {
            object objectInstance;
            switch (type)
            {
                case MemberType.field:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    object valueInstance = fieldInfo.GetValue(objectInstance);
                    if (typeof(TValue) != typeof(IntPtr))
                    {
                        value = (TValue) valueInstance;
                        return;
                    }
                    value = (TValue) (object) AllocObjectPtr(valueInstance);
                    return;
                case MemberType.property:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    if (typeof(TValue) != typeof(IntPtr))
                    {
                        value = (TValue) propertyInfo.GetValue(objectInstance);
                        return;
                    }
                    value = (TValue) (object) AllocObjectPtr(propertyInfo.GetValue(objectInstance));
                    return;
                case MemberType.method:
                    throw new MissingMethodException();
                case MemberType.constructor:
                    throw new MissingMemberException();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }
        
        #endregion

        #region Setters

        [MonoPInvokeCallback(typeof(SetValueDelegate<string>))]
        private static void SetValueString(IntPtr instancePtr, IntPtr memberPtr, MemberType type, string value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<bool>))]
        private static void SetValueBool(IntPtr instancePtr, IntPtr memberPtr, MemberType type, bool value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<int>))]
        private static void SetValueInt(IntPtr instancePtr, IntPtr memberPtr, MemberType type, int value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<uint>))]
        private static void SetValueUInt(IntPtr instancePtr, IntPtr memberPtr, MemberType type, uint value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<long>))]
        private static void SetValueLong(IntPtr instancePtr, IntPtr memberPtr, MemberType type, long value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<ulong>))]
        private static void SetValueULong(IntPtr instancePtr, IntPtr memberPtr, MemberType type, ulong value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<float>))]
        private static void SetValueFloat(IntPtr instancePtr, IntPtr memberPtr, MemberType type, float value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<double>))]
        private static void SetValueDouble(IntPtr instancePtr, IntPtr memberPtr, MemberType type, double value) => SetMemberValue(instancePtr, memberPtr, type, value);
        [MonoPInvokeCallback(typeof(SetValueDelegate<IntPtr>))]
        private static void SetValuePointer(IntPtr instancePtr, IntPtr memberPtr, MemberType type, IntPtr value) => SetMemberValue(instancePtr, memberPtr, type, value);
        
        private static void SetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value)
        {
            object objectInstance;
            switch (type)
            {
                case MemberType.field:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    switch (value)
                    {
                        case IntPtr valuePtr: fieldInfo.SetValue(objectInstance, ConvertPtrTo<object>(valuePtr)); break;
                        default: fieldInfo.SetValue(objectInstance, value); break;
                    }
                }
                    break;

                case MemberType.property:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    switch (value)
                    {
                        case IntPtr valuePtr: propertyInfo.SetValue(objectInstance, ConvertPtrTo<object>(valuePtr)); break;
                        default: propertyInfo.SetValue(objectInstance, value); break;
                    }
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