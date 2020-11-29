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

            SetManagedGetSetStringMethod(GetMemberValue, SetMemberValue);
            SetManagedGetSetIntMethod(GetMemberValue, SetMemberValue);
            SetManagedGetSetLongMethod(GetMemberValue, SetMemberValue);
            SetManagedGetSetFloatMethod(GetMemberValue, SetMemberValue);
            SetManagedGetSetDoubleMethod(GetMemberValue, SetMemberValue);
            SetManagedGetSetObjectMethod(GetMemberValue, SetMemberValue);
        }
    }
}