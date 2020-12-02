using JetBrains.Annotations;
using UnityEngine;

namespace UnityCpp.NativeBridge.UnityBridges
{
    public struct QuaternionBridge
    {
        private Quaternion _quaternion;

        [UsedImplicitly]
        public Vector3Bridge eulerAngles
        {
            get => _quaternion.eulerAngles;
            set => _quaternion.eulerAngles = value;
        }

        [UsedImplicitly] public QuaternionBridge normalized => _quaternion.normalized;
        [UsedImplicitly] public float w
        {
            get => _quaternion.w;
            set => _quaternion.w = value;
        }

        [UsedImplicitly] public float x
        {
            get => _quaternion.x;
            set => _quaternion.x = value;
        }

        [UsedImplicitly] public float y
        {
            get => _quaternion.y;
            set => _quaternion.y = value;
        }

        [UsedImplicitly] public float z
        {
            get => _quaternion.z;
            set => _quaternion.z = value;
        }

        public static QuaternionBridge identify = Quaternion.identity;

        private QuaternionBridge(Quaternion quaternion) => _quaternion = quaternion;
        public QuaternionBridge(float x, float y, float z, float w) => _quaternion = new Quaternion(x, y, z, w);

        public void Set(float newX, float newY, float newZ, float newW) => _quaternion.Set(newX, newY, newZ, newW);
        public void SetFromToRotation(Vector3Bridge fromDirection, Vector3Bridge toDirection) => _quaternion.SetFromToRotation(fromDirection, toDirection);
        public void SetLookRotation(Vector3Bridge view, Vector3Bridge up) => _quaternion.SetLookRotation(view, up);
        public void ToAngleAxis(out float angle, out Vector3Bridge axis) => _quaternion.ToAngleAxis(out angle, out axis.vector3);

        public static float Angle(QuaternionBridge a, QuaternionBridge b) => Quaternion.Angle(a, b);
        public static QuaternionBridge AngleAxis(float angle, Vector3Bridge axis) => Quaternion.AngleAxis(angle, axis);
        public static float Dot(QuaternionBridge a, QuaternionBridge b) => Quaternion.Dot(a, b);
        public static QuaternionBridge Euler(float x, float y, float z) => Quaternion.Euler(x, y, z);
        public static QuaternionBridge FromToRotation(Vector3Bridge fromDirection, Vector3Bridge toDirection) => Quaternion.FromToRotation(fromDirection, toDirection);
        public static QuaternionBridge Inverse(QuaternionBridge rotation) => Quaternion.Inverse(rotation);
        public static QuaternionBridge Lerp(QuaternionBridge a, QuaternionBridge b, float t) => Quaternion.Lerp(a, b, t);
        public static QuaternionBridge LerpUnclamped(QuaternionBridge a, QuaternionBridge b, float t) => Quaternion.LerpUnclamped(a, b, t);
        public static QuaternionBridge LookRotation(Vector3Bridge forward, Vector3Bridge upwards) => Quaternion.LookRotation(forward, upwards);
        public static QuaternionBridge Normalize(QuaternionBridge q) => Quaternion.Normalize(q);
        public static QuaternionBridge RotateTowards(QuaternionBridge from, QuaternionBridge to, float maxDegreesDelta) => Quaternion.RotateTowards(from, to, maxDegreesDelta);
        public static QuaternionBridge Slerp(QuaternionBridge a, QuaternionBridge b, float t) => Quaternion.Slerp(a, b, t);
        public static QuaternionBridge SlerpUnclamped(QuaternionBridge a, QuaternionBridge b, float t) => Quaternion.SlerpUnclamped(a, b, t);
        
        public static implicit operator QuaternionBridge(Quaternion quaternion) => new QuaternionBridge(quaternion);
        public static implicit operator Quaternion(QuaternionBridge quaternionBridge) => quaternionBridge._quaternion;
    }
}