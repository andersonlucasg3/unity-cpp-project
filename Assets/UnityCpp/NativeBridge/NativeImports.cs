using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridge
{
    using static NativeDelegates;
    
    internal static class NativeImports
    {
        #region SendMessage
        
        internal static SetDelegate<SendMessageDelegate> _setUnitySendMessage;
        
        #endregion
        
        #region Constructor & Destructor
        
        internal static SetDelegate<ConstructorDelegate> _setManagedConstructor;
        
        internal static SetDelegate<DestructorDelegate> _setManagedDestructor;
        
        #endregion

        #region Getters & Setters

        internal static SetDelegate<GetMemberPtrDelegate> _setManagedGetMemberPtr;

        internal static SetDelegates<GetValueDelegate<string>, SetValueDelegate<string>> _setManagedGetSetString;

        internal static SetDelegates<GetValueDelegate<int>, SetValueDelegate<int>> _setManagedGetSetInt;

        internal static SetDelegates<GetValueDelegate<long>, SetValueDelegate<long>> _setManagedGetSetLong;

        internal static SetDelegates<GetValueDelegate<float>, SetValueDelegate<float>> _setManagedGetSetFloat;

        internal static SetDelegates<GetValueDelegate<double>, SetValueDelegate<double>> _setManagedGetSetDouble;

        internal static SetDelegates<GetValueDelegate<IntPtr>, SetValueDelegate<IntPtr>> _setManagedGetSetObject;

        #endregion
    }
}