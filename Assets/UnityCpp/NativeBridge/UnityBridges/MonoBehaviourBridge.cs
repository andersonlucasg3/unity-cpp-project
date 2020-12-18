using JetBrains.Annotations;
using UnityCpp.NativeBridge.Scripting;

namespace UnityCpp.NativeBridge.UnityBridges
{
    public class MonoBehaviourBridge : ComponentBridge
    {
        [UsedImplicitly] public NativeMonoBehaviour monoBehaviour;

        private MonoBehaviourBridge(NativeMonoBehaviour behaviour) : base(behaviour) => monoBehaviour = behaviour;

        public static implicit operator MonoBehaviourBridge(NativeMonoBehaviour behaviour) => new MonoBehaviourBridge(behaviour);
    }
}