using System;
using System.Reflection;
using System.Runtime.InteropServices;
using UnityEngine;
using static UnityCpp.NativeBridge.NativeDelegates;

namespace UnityCpp.NativeBridge
{
    internal static class NativeMethodsImpl
    {
        #region Unity methods

        internal static void UnitySendMessageMethod(string gameObjectName, string methodName, string message)
        {
            GameObject.Find(gameObjectName).SendMessage(methodName, message, SendMessageOptions.RequireReceiver);
        }
        
        internal static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string message)
        {
            Debug.Log(message);
        }

        #endregion

        #region Constructor & Destructor

        internal static IntPtr ConstructorMethod(string typeName)
        {
            Type managedType = Type.GetType(typeName);
            if (managedType == null)
            {
                return IntPtr.Zero;
            }

            object instance = Activator.CreateInstance(managedType);
            return (IntPtr) GCHandle.Alloc(instance);
        }

        internal static void DestructorMethod(IntPtr intPtr)
        {
            GCHandle handle = (GCHandle) intPtr;
            handle.Free();
        }

        #endregion

        #region Getters & Setters

        internal static void GetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, NativeDelegates.MemberType type, out TValue value)
        {
            object objectInstance = null;
            switch (type)
            {
                case NativeDelegates.MemberType.field:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    object valueInstance = fieldInfo.GetValue(objectInstance);
                    if (typeof(TValue) != typeof(IntPtr))
                    {
                        value = (TValue) valueInstance;
                        return;
                    }
                    value = (TValue) (object) AllocObjectPtr(valueInstance);
                    return;
                case NativeDelegates.MemberType.property:
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    if (typeof(TValue) != typeof(IntPtr))
                    {
                        value = (TValue) propertyInfo.GetValue(objectInstance);
                        return;
                    }
                    value = (TValue) (object) AllocObjectPtr(propertyInfo.GetValue(objectInstance));
                    return;
                case NativeDelegates.MemberType.method:
                    throw new MissingMethodException();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }

        internal static void SetMemberValue<TValue>(IntPtr intPtr, IntPtr memberPtr, NativeDelegates.MemberType type, TValue value)
        {
            object objectInstance = null;
            switch (type)
            {
                case NativeDelegates.MemberType.field:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out FieldInfo fieldInfo);
                    switch (value)
                    {
                        case IntPtr valuePtr: fieldInfo.SetValue(objectInstance, ConvertPtrTo<object>(valuePtr)); break;
                        default: fieldInfo.SetValue(objectInstance, value); break;
                    }
                }
                    break;

                case NativeDelegates.MemberType.property:
                {
                    GetObjectAndInfo(intPtr, memberPtr, out objectInstance, out PropertyInfo propertyInfo);
                    switch (value)
                    {
                        case IntPtr valuePtr: propertyInfo.SetValue(objectInstance, ConvertPtrTo<object>(valuePtr)); break;
                        default: propertyInfo.SetValue(objectInstance, value); break;
                    }
                }
                    break;
                case NativeDelegates.MemberType.method:
                    throw new MissingMethodException();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }

        internal static IntPtr GetMemberPtr(IntPtr intPtr, string name)
        {
            return AllocMemberPtr(intPtr, name);
        }

        #endregion

        #region Private methods

        private static IntPtr AllocMemberPtr(IntPtr intPtr, string name)
        {
            if (TryGetMember(intPtr, name, out MemberInfo info))
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