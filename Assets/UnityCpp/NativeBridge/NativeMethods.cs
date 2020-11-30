using System;
using UnityCpp.Loader;
using UnityEditor.Profiling.Memory.Experimental;

namespace UnityCpp.NativeBridge
{
    using static NativeFunctions;
    using static NativeMethodsImpl;
    using static NativeDelegates;
    
    public static class NativeMethods
    {
        public static void Initialize(IntPtr assemblyHandle)
        {
            _setUnitySendMessage = NativeAssembly.GetMethod<SetSendMessageDelegate>(assemblyHandle, "SetUnitySendMessageMethod");
            _setUnitySendMessage.Invoke(UnitySendMessageMethod);

            _setManagedConstructor = NativeAssembly.GetMethod<SetConstructorDelegate>(assemblyHandle, "SetManagedConstructorMethod");
            _setManagedConstructor.Invoke(ConstructorMethod);
            _setManagedDestructor = NativeAssembly.GetMethod<SetDestructorDelegate>(assemblyHandle, "SetManagedDestructorMethod");
            _setManagedDestructor.Invoke(DestructorMethod);

            _setManagedGetMemberPtr = NativeAssembly.GetMethod<SetGetMemberPtrDelegate>(assemblyHandle, "SetManagedGetMemberPtrMethod");
            _setManagedGetMemberPtr.Invoke(GetMemberPtr);

            _setManagedGetSetString = NativeAssembly.GetMethod<SetGetSetStringDelegate>(assemblyHandle, "SetManagedGetSetStringMethod");
            _setManagedGetSetString.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetInt = NativeAssembly.GetMethod<SetGetSetIntDelegate>(assemblyHandle, "SetManagedGetSetIntMethod");
            _setManagedGetSetInt.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetLong = NativeAssembly.GetMethod<SetGetSetLongDelegate>(assemblyHandle, "SetManagedGetSetLongMethod");
            _setManagedGetSetLong.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetFloat = NativeAssembly.GetMethod<SetGetSetFloatDelegate>(assemblyHandle, "SetManagedGetSetFloatMethod");
            _setManagedGetSetFloat.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetDouble = NativeAssembly.GetMethod<SetGetSetDoubleDelegate>(assemblyHandle, "SetManagedGetSetDoubleMethod");
            _setManagedGetSetDouble.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetObject = NativeAssembly.GetMethod<SetGetSetObjectDelegate>(assemblyHandle, "SetManagedGetSetObjectMethod");
            _setManagedGetSetObject.Invoke(GetMemberValue, SetMemberValue);
        }
    }
}