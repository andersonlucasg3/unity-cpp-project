#pragma once

enum HideFlags : int {
    none = 0,
    hideInHierarchy = 1,
    hideInInspector = 2,
    dontSaveInEditor = 4,
    notEditable = 8,
    dontSaveInBuild = 16, // 0x00000010
    dontUnloadUnusedAsset = 32, // 0x00000020
    dontSave = dontUnloadUnusedAsset | dontSaveInBuild | dontSaveInEditor, // 0x00000034
    hideAndDontSave = dontSave | notEditable | hideInHierarchy
};