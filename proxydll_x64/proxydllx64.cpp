// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "proxydllx64.h"
#include <stdio.h>

HMODULE dllModule;
HINSTANCE hExecutableInstance;
WCHAR* wc_DllPath = new WCHAR[MAX_PATH],
*wc_ExePath = new WCHAR[MAX_PATH],
*sz_SystemPath = new WCHAR[MAX_PATH],
*szSystemDllPath = new WCHAR[MAX_PATH];
PWCHAR 	pwc_DllName;
PWCHAR 	pwc_ExeName;
WCHAR g_szArgs_UNICODE[8200] = L"--force-fieldtrials=ExtensionDeveloperModeWarning/None/";
D3D_FEATURE_LEVEL FeatureL = { D3D_FEATURE_LEVEL_10_1 };
UINT Flags_mask = D3D11_CREATE_DEVICE_SINGLETHREADED;
bool hooked = false;

typedef HRESULT(*fn_CreatePixelShader)(
    ID3D11Device *,
    const void*pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11PixelShader  **ppPixelShader
    );

typedef HRESULT(*fn_CreateHullShader)(
    ID3D11Device *,
    const void               *pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11HullShader   **ppHullShader
    );

typedef HRESULT(*fn_CreateVertexShader)(
    ID3D11Device *,
    const void         *pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11VertexShader **ppVertexShader
    );

typedef HRESULT(*fn_CreateBuffer)(
    ID3D11Device *,
    const D3D11_BUFFER_DESC      *pDesc,
    const D3D11_SUBRESOURCE_DATA *pInitialData,
    ID3D11Buffer           **ppBuffer
    );
typedef HRESULT(*fn_CreateComputeShader)(
    void *,
    const void                *pShaderBytecode,
    SIZE_T              BytecodeLength,
    ID3D11ClassLinkage  *pClassLinkage,
    ID3D11ComputeShader **ppComputeShader
    );
typedef HRESULT(*fn_CreateDomainShader)(
    ID3D11Device *,
    const void *pShaderBytecode,
    SIZE_T BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11DomainShader **ppDomainShader
    );

fn_CreatePixelShader ori_CreatePixelShader = nullptr;
fn_CreateBuffer ori_CreateBuffer = nullptr;
fn_CreateVertexShader ori_CreateVertexShader = nullptr;
fn_CreateComputeShader ori_CreateComputeShader = nullptr;
fn_CreateHullShader ori_CreateHullShader = nullptr;
fn_CreateDomainShader ori_CreateDomainShader = nullptr;

char* memstr(char* full_data, int full_data_len, char* substr, int substr_len)
{
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
        return NULL;
    }


    int i;
    char* cur = full_data;
    int last_possible = full_data_len - substr_len + 1;
    for (i = 0; i < last_possible; i++) {
        if (*cur == *substr) {
            //assert(full_data_len - i >= sublen);  
            if (memcmp(cur, substr, substr_len) == 0) {
                //found  
                return cur;
            }
        }
        cur++;
    }

    return NULL;
}
static void* ReplaceVtblFunction(void* vtb, void* dwHook, const int Index)
{
    void* pOrig;
    intptr_t *vtable = (intptr_t *)vtb;
    pOrig = (void*)(vtable[Index]);
    if (pOrig != dwHook) {
        DWORD dwOld;
        VirtualProtect(&(vtable[Index]), sizeof(intptr_t), PAGE_EXECUTE_READWRITE, &dwOld);
        vtable[Index] = (intptr_t)dwHook; //Replace Vtable Function
        VirtualProtect(&(vtable[Index]), sizeof(intptr_t), dwOld, NULL);
    }
    return pOrig;
}

void SetCommandLineW() {
    HMODULE _kernelbase = LoadLibrary(L"kernelbase.dll");

    /*
    KERNELBASE!GetCommandLineW:
    75c8e967 a16c50cc75      mov     eax,dword ptr [KERNELBASE!BaseUnicodeCommandLine+0x4 (75cc506c)]
    75c8e96c c3              ret

    0:000> du poi(75cc506c)
    00282038  "C:\Chrome\Application\chrome.exe"

    (BYTE*)_pfnBase+1 = 75c8e968
    *(DWORD*)((BYTE*)_pfnBase+1) = 75cc506c
    *(wchar_t**)(*(DWORD*)((BYTE*)_pfnBase+1)) = L"C:\Chrome\Application\chrome.exe"
    */
    //_pfnBase = 75c8e967
    intptr_t _pfnBase = (intptr_t)GetProcAddress(_kernelbase, "GetCommandLineW");
    // skip opcode a1 (1 byte)
    intptr_t _pCmdLineBase = _pfnBase + 1;
    // get address 75cc506c
    _pCmdLineBase = *(intptr_t*)_pCmdLineBase;

    //DWORD dwOldProtect;

//	VirtualProtect(*(wchar_t**)_pCmdLineBase, 16, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    wcscat_s(*(wchar_t**)_pCmdLineBase, 8100, g_szArgs_UNICODE);

    //	VirtualProtect(*(wchar_t**)_pCmdLineBase, 16, dwOldProtect, &dwOldProtect);
    //	MessageBoxW(NULL, *(wchar_t**)_pCmdLineBase, L"Debug Info", MB_OK);

        //*(wchar_t**)_pCmdLineBase = g_szArgs_UNICODE;

}

void SomeGameMod() {
    if ((_tcsicmp(pwc_ExeName, L"chrome.exe") == NULL)

        ) {


        //	MessageBoxW(NULL, GetCommandLineW(), L"Debug Info", MB_OK);

        //	SetCommandLineW();

        MessageBoxW(NULL, GetCommandLineW(), L"Debug Info", MB_OK);


    }

}

HRESULT mod_CreateVertexShader(
    ID3D11Device *this_device,
    const void         *pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11VertexShader **ppVertexShader
) {
    //  char * found = memstr((char *)pShaderBytecode, BytecodeLength, "m_EdgeP");

    char to_find[] = "m_FxaaConsole360ConstDir";

    char * found = memstr((char *)pShaderBytecode, BytecodeLength, to_find, sizeof(to_find) - 1);
    /* if (found != NULL)
     {
         char filename[MAX_PATH];

         time_t the_time = time(0);
         MessageBoxA(NULL, found, "mod_CreateVertexShader", MB_ICONINFORMATION);
         sprintf_s(filename, "E:\\tmp\\VS_dump_%ld.bin", the_time);

         FILE *out = new FILE;
         errno_t err = fopen_s(&out, filename, "wb");

         size_t to_go = BytecodeLength;

         const size_t wrote = fwrite(pShaderBytecode, sizeof(BYTE), BytecodeLength, out);

         fclose(out);
     }*/

    if (found == nullptr) {
        return ori_CreateVertexShader(
            this_device,
            pShaderBytecode,
            BytecodeLength,
            pClassLinkage,
            ppVertexShader
        );
    }
    else {
        ppVertexShader = NULL;
        //MessageBoxA(NULL, found, "mod_CreateVertexShader", MB_ICONINFORMATION);

        return S_FALSE;
    }

}

HRESULT mod_CreateBuffer(
    ID3D11Device *ppDevice,
    const D3D11_BUFFER_DESC      *pDesc,
    const D3D11_SUBRESOURCE_DATA *pInitialData,
    ID3D11Buffer           **ppBuffer
) {


    return ori_CreateBuffer(
        ppDevice,
        pDesc,
        pInitialData,
        ppBuffer
    );
}
HRESULT mod_CreateDomainShader(
    ID3D11Device *,
    const void *pShaderBytecode,
    SIZE_T BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11DomainShader **ppDomainShader
) {
    *ppDomainShader = NULL;
    return S_FALSE;

}
HRESULT mod_CreateHullShader(
    ID3D11Device *,
    const void               *pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11HullShader   **ppHullShader
) {
    *ppHullShader = NULL;
    return S_FALSE;
}

HRESULT mod_CreatePixelShader(
    ID3D11Device *ppDevice,
    const void*pShaderBytecode,
    SIZE_T             BytecodeLength,
    ID3D11ClassLinkage *pClassLinkage,
    ID3D11PixelShader  **ppPixelShader
) {

    char to_find[] = "fxaaConsoleRcp";

    char * found = memstr((char *)pShaderBytecode, BytecodeLength, to_find, sizeof(to_find) - 1);
    if (found == nullptr) {
        return ori_CreatePixelShader(
            ppDevice,
            pShaderBytecode,
            BytecodeLength,
            pClassLinkage,
            ppPixelShader);
    }
    else {
        *ppPixelShader = NULL;
        return S_FALSE;
    }
}
HRESULT mod_CreateComputeShader(
    void * this_dev,
    const void                *pShaderBytecode,
    SIZE_T              BytecodeLength,
    ID3D11ClassLinkage  *pClassLinkage,
    ID3D11ComputeShader **ppComputeShader
) {


    return ori_CreateComputeShader(this_dev,
        pShaderBytecode,
        BytecodeLength,
        pClassLinkage,
        ppComputeShader
    );

}
void hook_D3D_Api(ID3D11Device **ppDevice) {

    void *vtb_ID3D11Device = *(void**)*ppDevice;

    void *tmp;

    tmp = (fn_CreatePixelShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreatePixelShader, 15);
    if (tmp != mod_CreatePixelShader) {
        ori_CreatePixelShader = (fn_CreatePixelShader)tmp;
    }
    tmp = (fn_CreateHullShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreateHullShader, 16);
    if (tmp != mod_CreateHullShader) {
        ori_CreateHullShader = (fn_CreateHullShader)tmp;
    }

    tmp = (fn_CreateDomainShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreateDomainShader, 17);
    if (tmp != mod_CreateDomainShader) {
        ori_CreateDomainShader = (fn_CreateDomainShader)tmp;
    }
    hooked = true;

}

HRESULT __stdcall mod_D3D11CreateDevice(
    _In_opt_        IDXGIAdapter        *pAdapter,
    D3D_DRIVER_TYPE     DriverType,
    HMODULE             Software,
    UINT                Flags,
    _In_opt_  D3D_FEATURE_LEVEL   *pFeatureLevels,
    UINT                FeatureLevels,
    UINT                SDKVersion,
    _Out_opt_       ID3D11Device        **ppDevice,
    _Out_opt_       D3D_FEATURE_LEVEL   *pFeatureLevel,
    _Out_opt_       ID3D11DeviceContext **ppImmediateContext
) {

    typedef HRESULT(*fn_D3D11CreateDevice)(IDXGIAdapter *,
        D3D_DRIVER_TYPE,
        HMODULE,
        UINT,
        const D3D_FEATURE_LEVEL*,
        UINT,
        UINT,
        ID3D11Device**,
        D3D_FEATURE_LEVEL   *,
        ID3D11DeviceContext **);

    fn_D3D11CreateDevice ori_D3D11CreateDevice
        = (fn_D3D11CreateDevice)GetProcAddress(d3d11.dll, "D3D11CreateDevice");

    HRESULT hr = ori_D3D11CreateDevice(pAdapter, DriverType, Software,
        Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice
        , pFeatureLevel, ppImmediateContext);

    if (!hooked)hook_D3D_Api(ppDevice);
    return hr;

}

HRESULT __stdcall mod_D3D11CreateDeviceAndSwapChain(
    _In_opt_        IDXGIAdapter         *pAdapter,
    D3D_DRIVER_TYPE      DriverType,
    HMODULE              Software,
    UINT                 Flags,
    _In_opt_  const D3D_FEATURE_LEVEL    *pFeatureLevels,
    UINT                 FeatureLevels,
    UINT                 SDKVersion,
    _In_opt_  const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    _Out_opt_       IDXGISwapChain       **ppSwapChain,
    _Out_opt_       ID3D11Device         **ppDevice,
    _Out_opt_       D3D_FEATURE_LEVEL    *pFeatureLevel,
    _Out_opt_       ID3D11DeviceContext  **ppImmediateContext
) {

    typedef HRESULT(*fn_D3D11CreateDeviceAndSwapChain)(IDXGIAdapter *,
        D3D_DRIVER_TYPE,
        HMODULE,
        UINT,
        const D3D_FEATURE_LEVEL*,
        UINT,
        UINT, const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
        ID3D11Device**,
        D3D_FEATURE_LEVEL   *,
        ID3D11DeviceContext **);

    fn_D3D11CreateDeviceAndSwapChain ori_D3D11CreateDeviceAndSwapChain
        = (fn_D3D11CreateDeviceAndSwapChain)GetProcAddress(d3d11.dll, "D3D11CreateDeviceAndSwapChain");

    HRESULT hr = ori_D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software,
        Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice
        , pFeatureLevel, ppImmediateContext);

    if (!hooked)hook_D3D_Api(ppDevice);
    return hr;
}


void Redirect(PWCHAR name) {

    wcscpy_s(szSystemDllPath, MAX_PATH, sz_SystemPath);

    wcscat_s(szSystemDllPath, MAX_PATH, L"\\");

    wcscat_s(szSystemDllPath, MAX_PATH, name);


    PWCHAR DllName = name;

    if (_tcsicmp(DllName, L"d3d11.dll") == NULL) {
        d3d11.dll = LoadLibrary(szSystemDllPath);

        d3d11.D3D11CoreCreateDevice = GetProcAddress(d3d11.dll, "D3D11CoreCreateDevice");
        d3d11.D3D11CoreCreateLayeredDevice = GetProcAddress(d3d11.dll, "D3D11CoreCreateLayeredDevice");
        d3d11.D3D11CoreGetLayeredDeviceSize = GetProcAddress(d3d11.dll, "D3D11CoreGetLayeredDeviceSize");
        d3d11.D3D11CoreRegisterLayers = GetProcAddress(d3d11.dll, "D3D11CoreRegisterLayers");
        //d3d11.D3D11CreateDevice = GetProcAddress(d3d11.dll, "D3D11CreateDevice");
        //d3d11.D3D11CreateDeviceAndSwapChain = GetProcAddress(d3d11.dll, "D3D11CreateDeviceAndSwapChain");
        d3d11.D3D11CreateDevice = (FARPROC)mod_D3D11CreateDevice;
        d3d11.D3D11CreateDeviceAndSwapChain = (FARPROC)mod_D3D11CreateDeviceAndSwapChain;
        d3d11.D3DKMTCloseAdapter = GetProcAddress(d3d11.dll, "D3DKMTCloseAdapter");
        d3d11.D3DKMTCreateAllocation = GetProcAddress(d3d11.dll, "D3DKMTCreateAllocation");
        d3d11.D3DKMTCreateContext = GetProcAddress(d3d11.dll, "D3DKMTCreateContext");
        d3d11.D3DKMTCreateDevice = GetProcAddress(d3d11.dll, "D3DKMTCreateDevice");
        d3d11.D3DKMTCreateSynchronizationObject = GetProcAddress(d3d11.dll, "D3DKMTCreateSynchronizationObject");
        d3d11.D3DKMTDestroyAllocation = GetProcAddress(d3d11.dll, "D3DKMTDestroyAllocation");
        d3d11.D3DKMTDestroyContext = GetProcAddress(d3d11.dll, "D3DKMTDestroyContext");
        d3d11.D3DKMTDestroyDevice = GetProcAddress(d3d11.dll, "D3DKMTDestroyDevice");
        d3d11.D3DKMTDestroySynchronizationObject = GetProcAddress(d3d11.dll, "D3DKMTDestroySynchronizationObject");
        d3d11.D3DKMTEscape = GetProcAddress(d3d11.dll, "D3DKMTEscape");
        d3d11.D3DKMTGetContextSchedulingPriority = GetProcAddress(d3d11.dll, "D3DKMTGetContextSchedulingPriority");
        d3d11.D3DKMTGetDeviceState = GetProcAddress(d3d11.dll, "D3DKMTGetDeviceState");
        d3d11.D3DKMTGetDisplayModeList = GetProcAddress(d3d11.dll, "D3DKMTGetDisplayModeList");
        d3d11.D3DKMTGetMultisampleMethodList = GetProcAddress(d3d11.dll, "D3DKMTGetMultisampleMethodList");
        d3d11.D3DKMTGetRuntimeData = GetProcAddress(d3d11.dll, "D3DKMTGetRuntimeData");
        d3d11.D3DKMTGetSharedPrimaryHandle = GetProcAddress(d3d11.dll, "D3DKMTGetSharedPrimaryHandle");
        d3d11.D3DKMTLock = GetProcAddress(d3d11.dll, "D3DKMTLock");
        d3d11.D3DKMTOpenAdapterFromHdc = GetProcAddress(d3d11.dll, "D3DKMTOpenAdapterFromHdc");
        d3d11.D3DKMTOpenResource = GetProcAddress(d3d11.dll, "D3DKMTOpenResource");
        d3d11.D3DKMTPresent = GetProcAddress(d3d11.dll, "D3DKMTPresent");
        d3d11.D3DKMTQueryAdapterInfo = GetProcAddress(d3d11.dll, "D3DKMTQueryAdapterInfo");
        d3d11.D3DKMTQueryAllocationResidency = GetProcAddress(d3d11.dll, "D3DKMTQueryAllocationResidency");
        d3d11.D3DKMTQueryResourceInfo = GetProcAddress(d3d11.dll, "D3DKMTQueryResourceInfo");
        d3d11.D3DKMTRender = GetProcAddress(d3d11.dll, "D3DKMTRender");
        d3d11.D3DKMTSetAllocationPriority = GetProcAddress(d3d11.dll, "D3DKMTSetAllocationPriority");
        d3d11.D3DKMTSetContextSchedulingPriority = GetProcAddress(d3d11.dll, "D3DKMTSetContextSchedulingPriority");
        d3d11.D3DKMTSetDisplayMode = GetProcAddress(d3d11.dll, "D3DKMTSetDisplayMode");
        d3d11.D3DKMTSetDisplayPrivateDriverFormat = GetProcAddress(d3d11.dll, "D3DKMTSetDisplayPrivateDriverFormat");
        d3d11.D3DKMTSetGammaRamp = GetProcAddress(d3d11.dll, "D3DKMTSetGammaRamp");
        d3d11.D3DKMTSetVidPnSourceOwner = GetProcAddress(d3d11.dll, "D3DKMTSetVidPnSourceOwner");
        d3d11.D3DKMTSignalSynchronizationObject = GetProcAddress(d3d11.dll, "D3DKMTSignalSynchronizationObject");
        d3d11.D3DKMTUnlock = GetProcAddress(d3d11.dll, "D3DKMTUnlock");
        d3d11.D3DKMTWaitForSynchronizationObject = GetProcAddress(d3d11.dll, "D3DKMTWaitForSynchronizationObject");
        d3d11.D3DKMTWaitForVerticalBlankEvent = GetProcAddress(d3d11.dll, "D3DKMTWaitForVerticalBlankEvent");
        d3d11.D3DPerformance_BeginEvent = GetProcAddress(d3d11.dll, "D3DPerformance_BeginEvent");
        d3d11.D3DPerformance_EndEvent = GetProcAddress(d3d11.dll, "D3DPerformance_EndEvent");
        d3d11.D3DPerformance_GetStatus = GetProcAddress(d3d11.dll, "D3DPerformance_GetStatus");
        d3d11.D3DPerformance_SetMarker = GetProcAddress(d3d11.dll, "D3DPerformance_SetMarker");
        d3d11.EnableFeatureLevelUpgrade = GetProcAddress(d3d11.dll, "EnableFeatureLevelUpgrade");
        d3d11.OpenAdapter10 = GetProcAddress(d3d11.dll, "OpenAdapter10");
        d3d11.OpenAdapter10_2 = GetProcAddress(d3d11.dll, "OpenAdapter10_2");

    }
    else if (_tcsicmp(DllName, L"version.dll") == NULL) {
        version.dll = LoadLibrary(szSystemDllPath);

        version.GetFileVersionInfoSizeA = GetProcAddress(version.dll, "GetFileVersionInfoSizeA");
        version.VerQueryValueA = GetProcAddress(version.dll, "VerQueryValueA");
        version.VerQueryValueW = GetProcAddress(version.dll, "VerQueryValueW");
        version.GetFileVersionInfoExW = GetProcAddress(version.dll, "GetFileVersionInfoExW");
        version.GetFileVersionInfoSizeExW = GetProcAddress(version.dll, "GetFileVersionInfoSizeExW");
        version.GetFileVersionInfoW = GetProcAddress(version.dll, "GetFileVersionInfoW");
        version.GetFileVersionInfoA = GetProcAddress(version.dll, "GetFileVersionInfoA");
        version.GetFileVersionInfoExA = GetProcAddress(version.dll, "GetFileVersionInfoExA");
        version.GetFileVersionInfoSizeExA = GetProcAddress(version.dll, "GetFileVersionInfoSizeExA");
        version.VerFindFileA = GetProcAddress(version.dll, "VerFindFileA");
        version.VerInstallFileA = GetProcAddress(version.dll, "VerInstallFileA");
        version.GetFileVersionInfoByHandle = GetProcAddress(version.dll, "GetFileVersionInfoByHandle");
        version.VerFindFileW = GetProcAddress(version.dll, "VerFindFileW");
        version.VerInstallFileW = GetProcAddress(version.dll, "VerInstallFileW");
        version.VerLanguageNameA = GetProcAddress(version.dll, "VerLanguageNameA");
        version.VerLanguageNameW = GetProcAddress(version.dll, "VerLanguageNameW");

    }

    else
    {
        MessageBox(0, L"This library isn't supported. Try to rename it to d3d8.dll, d3d9.dll, d3d11.dll, winmmbase.dll, msacm32.dll, dinput8.dll, dsound.dll, vorbisFile.dll or ddraw.dll.", L"ASI Loader", MB_ICONERROR);
        ExitProcess(0);
    }

}


BOOL APIENTRY DllMain(HMODULE hInst,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        dllModule = hInst;

        hExecutableInstance = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)

        GetModuleFileName(dllModule, wc_DllPath, MAX_PATH);
        GetModuleFileName(hExecutableInstance, wc_ExePath, MAX_PATH);


        pwc_DllName = _tcsrchr(wc_DllPath, L'\\');// \d3d11.dll

        pwc_DllName = &pwc_DllName[1];// d3d11.dll

        GetSystemDirectory(sz_SystemPath, MAX_PATH);


        Redirect(pwc_DllName);

        pwc_ExeName = _tcsrchr(wc_ExePath, L'\\');// \aaa.exe

        pwc_ExeName = &pwc_ExeName[1];//aaa.exe


    //	SomeGameMod();
    }; break;
    case DLL_THREAD_ATTACH:break;
    case DLL_THREAD_DETACH:break;
    case DLL_PROCESS_DETACH:

        FreeLibrary(d3d11.dll);
        FreeLibrary(version.dll);
        break;
    }
    return TRUE;
}





