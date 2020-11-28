using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace UnityCpp.UnityEngineFacade
{
    public class GameObjectFacade
    {
        private GameObject _gameObject;
        private TransformFacade _transform;
        
        public GameObjectFacade(GameObject gameObject)
        {
            _gameObject = gameObject;
            _transform = new TransformFacade(gameObject.transform);
        }
    }
}