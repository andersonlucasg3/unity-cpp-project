using System;
using System.Runtime.InteropServices;
using JetBrains.Annotations;

namespace UnityCpp.NativeBridge
{
    [StructLayout(LayoutKind.Sequential)]
    public readonly struct UnmanagedValue
    {
        private static readonly bool[] boolBuffer = new bool[1];
        private static readonly byte[] byteBuffer = new byte[1];
        private static readonly short[] shortBuffer = new short[1];
        private static readonly int[] intBuffer = new int[1];
        private static readonly long[] longBuffer = new long[1];
        private static readonly float[] floatBuffer = new float[1];
        private static readonly double[] doubleBuffer = new double[1];
        
        [UsedImplicitly]
        public readonly IntPtr value;
        [UsedImplicitly]
        public readonly Type type;

        public UnmanagedValue(IntPtr value, Type type)
        {
            this.value = value;
            this.type = type;
        }

        [UsedImplicitly]
        public object ToManaged()
        {
            switch (type)
            {
                case Type.boolType: 
                    Marshal.Copy(value, byteBuffer, 0, 1);
                    return byteBuffer[0] != 0;
                
                case Type.byteType:
                    Marshal.Copy(value, byteBuffer, 0, 1);
                    return byteBuffer[0];
                
                case Type.shortType:
                case Type.ushortType:
                    Marshal.Copy(value, shortBuffer, 0, 1);
                    return shortBuffer[0];
                
                case Type.intType:
                case Type.uintType:
                    Marshal.Copy(value, intBuffer, 0, 1);
                    return intBuffer[0];
                    
                case Type.longType:
                case Type.ulongType:
                    Marshal.Copy(value, longBuffer, 0, 1);
                    return longBuffer[0];
                    
                case Type.floatType:
                    Marshal.Copy(value, floatBuffer, 0, 1);
                    return floatBuffer[0];
                
                case Type.doubleType:
                    Marshal.Copy(value, doubleBuffer, 0, 1);
                    return doubleBuffer[0];
                
                case Type.stringType:
                    return Marshal.PtrToStringAnsi(value);
                
                case Type.intPtrType:
                    return value;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }
            
        [UsedImplicitly]
        public enum Type : int
        {
            [UsedImplicitly] boolType = 0,
            [UsedImplicitly] byteType,
            [UsedImplicitly] shortType,
            [UsedImplicitly] ushortType,
            [UsedImplicitly] intType,
            [UsedImplicitly] uintType,
            [UsedImplicitly] longType,
            [UsedImplicitly] ulongType,
            [UsedImplicitly] floatType,
            [UsedImplicitly] doubleType,
            [UsedImplicitly] stringType,
            [UsedImplicitly] intPtrType
        }
    }
}