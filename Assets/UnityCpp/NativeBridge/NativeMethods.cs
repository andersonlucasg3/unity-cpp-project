using System;
using UnityCpp.Loader;
using UnityEditor.Profiling.Memory.Experimental;

namespace UnityCpp.NativeBridge
{
    using static NativeImports;
    using static NativeMethodsImpl;
    using static NativeDelegates;
    
    public static class NativeMethods
    {
        public static void Initialize(IntPtr assemblyHandle)
        {
            _setUnitySendMessage = NativeAssembly.GetMethod<SetDelegate<SendMessageDelegate>>(assemblyHandle, "SetUnitySendMessageMethod");
            _setUnitySendMessage.Invoke(UnitySendMessageMethod);

            _setManagedConstructor = NativeAssembly.GetMethod<SetDelegate<ConstructorDelegate>>(assemblyHandle, "SetManagedConstructorMethod");
            _setManagedConstructor.Invoke(ConstructorMethod);
            _setManagedDestructor = NativeAssembly.GetMethod<SetDelegate<DestructorDelegate>>(assemblyHandle, "SetManagedDestructorMethod");
            _setManagedDestructor.Invoke(DestructorMethod);

            _setManagedGetMemberPtr = NativeAssembly.GetMethod<SetDelegate<GetMemberPtrDelegate>>(assemblyHandle, "SetManagedGetMemberPtrMethod");
            _setManagedGetMemberPtr.Invoke(GetMemberPtr);

            _setManagedGetSetString = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<string>, SetValueDelegate<string>>>(assemblyHandle, "SetManagedGetSetStringMethod");
            _setManagedGetSetString.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetInt = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<int>, SetValueDelegate<int>>>(assemblyHandle, "SetManagedGetSetIntMethod");
            _setManagedGetSetInt.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetLong = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<long>, SetValueDelegate<long>>>(assemblyHandle, "SetManagedGetSetLongMethod");
            _setManagedGetSetLong.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetFloat = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<float>, SetValueDelegate<float>>>(assemblyHandle, "SetManagedGetSetFloatMethod");
            _setManagedGetSetFloat.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetDouble = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<double>, SetValueDelegate<double>>>(assemblyHandle, "SetManagedGetSetDoubleMethod");
            _setManagedGetSetDouble.Invoke(GetMemberValue, SetMemberValue);

            _setManagedGetSetObject = NativeAssembly.GetMethod<SetDelegates<GetValueDelegate<IntPtr>, SetValueDelegate<IntPtr>>>(assemblyHandle, "SetManagedGetSetObjectMethod");
            _setManagedGetSetObject.Invoke(GetMemberValue, SetMemberValue);
        }
    }
}