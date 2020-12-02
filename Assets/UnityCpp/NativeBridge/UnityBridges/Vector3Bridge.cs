using System.Runtime.InteropServices;
using JetBrains.Annotations;
using UnityEngine;

namespace UnityCpp.NativeBridge.UnityBridges
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3Bridge
    {
        public Vector3 vector3;
        
        [UsedImplicitly] public float x
        {
            get => vector3.x;
            set => vector3.x = value;
        }

        [UsedImplicitly] public float y
        {
            get => vector3.y;
            set => vector3.y = value;
        }

        [UsedImplicitly] public float z
        {
            get => vector3.z;
            set => vector3.z = value;
        }

        [UsedImplicitly] public float magnitude => vector3.magnitude;
        [UsedImplicitly] public float sqrMagnitude => vector3.sqrMagnitude;

        [UsedImplicitly] public static Vector3Bridge back => Vector3.back;
        [UsedImplicitly] public static Vector3Bridge down => Vector3.down;
        [UsedImplicitly] public static Vector3Bridge forward => Vector3.forward;
        [UsedImplicitly] public static Vector3Bridge left => Vector3.left;
        [UsedImplicitly] public static Vector3Bridge negativeInfinity => Vector3.negativeInfinity;
        [UsedImplicitly] public static Vector3Bridge one => Vector3.one;
        [UsedImplicitly] public static Vector3Bridge positiveInfinity => Vector3.positiveInfinity;
        [UsedImplicitly] public static Vector3Bridge right => Vector3.right;
        [UsedImplicitly] public static Vector3Bridge up => Vector3.up;
        [UsedImplicitly] public static Vector3Bridge zero => Vector3.zero;
        
        [UsedImplicitly] public Vector3Bridge normalized
        {
            get
            {
                vector3 = vector3.normalized;
                return this;
            }
        }

        private Vector3Bridge(Vector3 vector3) => this.vector3 = vector3;
        public Vector3Bridge(float x, float y) => vector3 = new Vector3(x, y);
        public Vector3Bridge(float x, float y, float z) => vector3 = new Vector3(x, y, z);
        
        public void Normalize() => vector3.Normalize();
        public void Scale(Vector3Bridge scale) => vector3.Scale(scale);

        public static float Angle(Vector3Bridge from, Vector3Bridge to) => Vector3.Angle(from, to);
        public static Vector3Bridge ClampMagnitude(Vector3Bridge vector, float maxLength) => Vector3.ClampMagnitude(vector, maxLength);
        public static Vector3Bridge Cross(Vector3Bridge lhs, Vector3Bridge rhs) => Vector3.Cross(lhs, rhs);
        public static float Distance(Vector3Bridge a, Vector3Bridge b) => Vector3.Distance(a, b);
        public static float Dot(Vector3Bridge lhs, Vector3Bridge rhs) => Vector3.Dot(lhs, rhs);
        public static Vector3Bridge Lerp(Vector3Bridge a, Vector3Bridge b, float t) => Vector3.Lerp(a, b, t);
        public static Vector3Bridge LerpUnclamped(Vector3Bridge a, Vector3Bridge b, float t) => Vector3.LerpUnclamped(a, b, t);
        public static Vector3Bridge Max(Vector3Bridge lhs, Vector3Bridge rhs) => Vector3.Max(lhs, rhs);
        public static Vector3Bridge Min(Vector3Bridge lhs, Vector3Bridge rhs) => Vector3.Min(lhs, rhs);
        public static Vector3Bridge MoveTowards(Vector3Bridge current, Vector3Bridge target, float maxDistanceDelta) => Vector3.MoveTowards(current, target, maxDistanceDelta);
        public static Vector3Bridge Normalize(Vector3Bridge value) => Vector3.Normalize(value);
        public static void OrthoNormalize(ref Vector3Bridge normal, ref Vector3Bridge tangent) => Vector3.OrthoNormalize(ref normal.vector3, ref tangent.vector3);
        public static Vector3Bridge Project(Vector3Bridge vector, Vector3Bridge onNormal) => Vector3.Project(vector, onNormal);
        public static Vector3Bridge ProjectOnPlane(Vector3Bridge vector, Vector3Bridge planeNormal) => Vector3.ProjectOnPlane(vector, planeNormal);
        public static Vector3Bridge Reflect(Vector3Bridge inDirection, Vector3Bridge inNormal) => Vector3.Reflect(inDirection, inNormal);
        public static Vector3Bridge RotateTowards(Vector3Bridge current, Vector3Bridge target, float maxRadiansDelta, float maxMagnitudeDelta) => Vector3.RotateTowards(current, target, maxRadiansDelta, maxMagnitudeDelta);
        public static Vector3Bridge Scale(Vector3Bridge a, Vector3Bridge b) => Vector3.Scale(a, b);
        public static float SignedAngle(Vector3Bridge from, Vector3Bridge to, Vector3Bridge axis) => Vector3.SignedAngle(from, to, axis);
        public static Vector3Bridge Slerp(Vector3Bridge a, Vector3Bridge b, float t) => Vector3.Slerp(a, b, t);
        public static Vector3Bridge SlerpUnclamped(Vector3Bridge a, Vector3Bridge b, float t) => Vector3.SlerpUnclamped(a, b, t);
        public static Vector3Bridge SmoothDamp(Vector3Bridge current, Vector3Bridge target, ref Vector3Bridge currentVelocity, float smoothTime, float maxSpeed, float deltaTime) 
            => Vector3.SmoothDamp(current, target, ref currentVelocity.vector3, smoothTime, maxSpeed, deltaTime);
        
        public static implicit operator Vector3Bridge(Vector3 vector3) => new Vector3Bridge(vector3);
        public static implicit operator Vector3(Vector3Bridge vector3Bridge) => vector3Bridge.vector3;
    }
}