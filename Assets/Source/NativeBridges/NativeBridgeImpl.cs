using System;
using System.Reflection;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp.NativeBridges
{
    internal static class NativeBridgeImpl
    {
        internal static IntPtr ConstructorCallMethod(string typeName)
        {
            Type managedType = Type.GetType(typeName);
            if (managedType == null)
            {
                return IntPtr.Zero;
            }
            object instance = Activator.CreateInstance(managedType);
            return (IntPtr)GCHandle.Alloc(instance);
        }

        internal static void DestroyCallMethod(IntPtr instance)
        {
            Marshal.Release(instance);
        }

        internal static void SetValueCallMethod(IntPtr instance, string property, object value)
        {
            object objectInstance = instance;
            Type type = objectInstance.GetType();
            PropertyInfo propertyInfo = type.GetProperty(property);
            if (propertyInfo == null)
            {
                Debug.Log($"Unmanaged code trying to set property ({property}) of object ({objectInstance}) that does not exists.");
            }
            else
            {
                propertyInfo.SetValue(objectInstance, value);                
            }
        }
    }
}