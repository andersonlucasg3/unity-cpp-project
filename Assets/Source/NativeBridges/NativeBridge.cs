using System;

namespace UnityCpp.NativeBridges
{
    using static NativeImports;
    using static NativeBridgeImpl;
    
    public static class NativeBridge
    {
        public static void Initialize()
        {
            SetUnitySendMessageMethod(UnitySendMessageMethod);
            
            SetManagedConstructorMethod(ConstructorMethod);
            SetManagedDestructorMethod(DestructorMethod);
            
            SetManagedGetMemberPtrMethod(GetMemberPtr);

            SetManagedGetSetStringMethod(GetMemberValue<string>, SetMemberValue);
            SetManagedGetSetIntMethod(GetMemberValue<int>, SetMemberValue);
            SetManagedGetSetLongMethod(GetMemberValue<long>, SetMemberValue);
            SetManagedGetSetFloatMethod(GetMemberValue<float>, SetMemberValue);
            SetManagedGetSetDoubleMethod(GetMemberValue<double>, SetMemberValue);
        }
    }
}