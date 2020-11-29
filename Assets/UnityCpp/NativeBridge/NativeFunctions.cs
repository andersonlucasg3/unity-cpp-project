using System;
using System.Runtime.InteropServices;

namespace UnityCpp.NativeBridge
{
    using static NativeDelegates;
    
    internal static class NativeFunctions
    {
        #region SendMessage
        
        internal static SetSendMessageDelegate _setUnitySendMessage;
        
        #endregion
        
        #region Constructor & Destructor
        
        internal static SetConstructorDelegate _setManagedConstructor;
        
        internal static SetDestructorDelegate _setManagedDestructor;
        
        #endregion

        #region Getters & Setters

        internal static SetGetMemberPtrDelegate _setManagedGetMemberPtr;

        internal static SetGetSetStringDelegate _setManagedGetSetString;

        internal static SetGetSetIntDelegate _setManagedGetSetInt;

        internal static SetGetSetLongDelegate _setManagedGetSetLong;

        internal static SetGetSetFloatDelegate _setManagedGetSetFloat;

        internal static SetGetSetDoubleDelegate _setManagedGetSetDouble;

        internal static SetGetSetObjectDelegate _setManagedGetSetObject;

        #endregion
    }
}