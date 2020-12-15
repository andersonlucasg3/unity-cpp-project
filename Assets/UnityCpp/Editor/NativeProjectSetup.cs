using System;
using System.IO;
using UnityEditor;
using UnityEngine;
using UnityEngine.Networking;

namespace UnityCpp.Editor
{
    public static class NativeProjectSetup
    {
        private const string _githubRepoUri = "https://github.com/andersonlucasg3/unity-cpp-project/archive/main.zip";
        
        [MenuItem("Assets/UnityCpp/Setup Project")]
        public static void SetupProject()
        {
            Debug.Log("---->>> Beginning project setup");
            Debug.Log($"Downloading Cpp Project from repository path: {_githubRepoUri}");
            DownloadRepository();
        }

        private static void DownloadRepository()
        {
            using (UnityWebRequest request = UnityWebRequest.Get(_githubRepoUri))
            {
                UnityWebRequestAsyncOperation operation = request.SendWebRequest();
                while (!operation.isDone)
                {
                    if (!EditorUtility.DisplayCancelableProgressBar("Downloading from GitHub", null, operation.progress)) continue;
                    request.Abort();
                    EditorUtility.ClearProgressBar();
                    return;
                }
                
                WriteDownloadedData(request.downloadHandler.data);
            }
            
            EditorUtility.ClearProgressBar();
        }

        private static void WriteDownloadedData(byte[] data)
        {
            string cachesPath = Path.Combine(Application.temporaryCachePath, "CppProject");
            
            if (Directory.Exists(cachesPath)) Directory.Delete(cachesPath, true);
            Directory.CreateDirectory(cachesPath);
            
            cachesPath = Path.Combine(cachesPath, "github.zip");
            
            Debug.Log($"Writing downloaded content to file at: {cachesPath}");
            
            EditorUtility.DisplayProgressBar("Writing to file", null, 0F);
            
            File.WriteAllBytes(cachesPath, data);
            
            EditorUtility.DisplayProgressBar("Written to file", null, 1F);
            
            Application.OpenURL("C:/Users/ander/AppData/Local/Temp/DefaultCompany/unity-cpp-project/CppProject/");
        }
    }
}