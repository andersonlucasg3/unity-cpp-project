using System;
using UnityEngine;

namespace UnityCpp.NativeBridge.NativeMonoBehaviour
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

            _nativeInstance = NativeMethods.createNativeMonoBehaviour.Invoke(_nativeClassName);
            if (_nativeInstance == IntPtr.Zero)
            {
                Destroy(this);
                return;
            }
            
            NativeMethods.callMonoBehaviourAwake.Invoke(_nativeInstance);
        }

        private void OnDestroy()
        {
            
        }

        private void Start()
        {
            
        }
    }
}