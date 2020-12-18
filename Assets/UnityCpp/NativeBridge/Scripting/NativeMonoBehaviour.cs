using System;
using UnityCpp.NativeBridge.Reflection;
using UnityCpp.NativeBridge.UnityBridges;
using UnityEngine;

namespace UnityCpp.NativeBridge.Scripting
{
    public class NativeMonoBehaviour : MonoBehaviour
    {
        [SerializeField] private string _nativeClassName = default;
        private IntPtr _nativeInstance = IntPtr.Zero;
        
        private void Awake()
        {
            if (string.IsNullOrEmpty(_nativeClassName))
            {
                Destroy(this);
                return;
            }

            MonoBehaviourBridge bridge = this;
            IntPtr ptr = ReflectionHelpers.AllocObjectPtr(bridge);
            _nativeInstance = NativeMethods.createNativeMonoBehaviour.Invoke(_nativeClassName, ptr);
            if (_nativeInstance == IntPtr.Zero)
            {
                Destroy(this);
                return;
            }
            
            NativeMethods.monoBehaviourAwake.Invoke(_nativeInstance);
        }

        private void OnDestroy()
        {
            NativeMethods.monoBehaviourOnDestroy.Invoke(_nativeInstance);
            ReflectionHelpers.DeallocPtr(_nativeInstance);
        }

        private void Start()
        {
            NativeMethods.monoBehaviourStart.Invoke(_nativeInstance);
        }

        private void Stop()
        {
            NativeMethods.monoBehaviourStop.Invoke(_nativeInstance);
        }

        private void OnEnable()
        {
            NativeMethods.monoBehaviourOnEnable.Invoke(_nativeInstance);
        }

        private void OnDisable()
        {
            NativeMethods.monoBehaviourOnDisable.Invoke(_nativeInstance);
        }

        private void FixedUpdate()
        {
            NativeMethods.monoBehaviourFixedUpdate.Invoke(_nativeInstance);
        }

        private void Update()
        {
            NativeMethods.monoBehaviourUpdate.Invoke(_nativeInstance);
        }

        private void LateUpdate()
        {
            NativeMethods.monoBehaviourLateUpdate.Invoke(_nativeInstance);
        }
    }
}