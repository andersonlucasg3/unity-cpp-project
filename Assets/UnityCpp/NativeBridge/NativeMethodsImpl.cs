using System;
using System.Reflection;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp.NativeBridge
{
    internal static class NativeMethodsImpl
    {
        #region Unity methods

        internal static void UnitySendMessageMethod(string gameObjectName, string methodName, string message)
        {
            GameObject.Find(gameObjectName).SendMessage(methodName, message, SendMessageOptions.RequireReceiver);
        }
        
        internal static void DebugLog(string message)
        {
            Debug.Log(message);
        }

        #endregion
        
        #region Types methods

        internal static IntPtr GetTypePtr(string assemblyName)
        {
            Type type = Type.GetType(assemblyName);
            return (IntPtr)GCHandle.Alloc(type);
        }

        internal static IntPtr GetTypeConstructorPtr(IntPtr typePtr, IntPtr[] parameterTypes, int paramCount)
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
        
        internal static IntPtr GetTypeMemberPtr(IntPtr typePtr, string name)
        {
            return AllocMemberPtr(typePtr, name);
        }

        internal static IntPtr Constructor(IntPtr constructorPtr, IntPtr[] parameters, int paramCount)
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
        
        #endregion

        #region Constructor & Destructor
        
        internal static void DestructorMethod(IntPtr intPtr)
        {
            GCHandle handle = (GCHandle) intPtr;
            handle.Free();
        }

        #endregion

        #region Getters & Setters

        internal static void GetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, out TValue value)
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

        internal static void SetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, MemberType type, TValue value)
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

        private static IntPtr AllocMemberPtr(IntPtr typePtr, string name)
        {
            if (TryGetMember(typePtr, name, out MemberInfo info))
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

        private static bool TryGetMember(IntPtr intPtr, string name, out MemberInfo memberInfo)
        {
            object objectInstance = ConvertPtrTo<object>(intPtr);
            Type objectType = objectInstance.GetType();
            memberInfo = objectType.GetProperty(name);
            if (memberInfo != null) return true;
            Debug.Log($"Unmanaged code trying to get {memberInfo} of object {objectInstance} that does not exists.");
            return false;
        }

        private static void GetObjectAndInfo<TInfo>(IntPtr objectPtr, IntPtr infoPtr, out object objectInstance, out TInfo info)
        {
            objectInstance = ConvertPtrTo<object>(objectPtr);
            info = ConvertPtrTo<TInfo>(infoPtr);
        }

        #endregion
    }
}