// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "proxydllx64.h"



HMODULE dllModule;
HINSTANCE hExecutableInstance;
WCHAR* wc_DllPath = new WCHAR[MAX_PATH],
*wc_ExePath = new WCHAR[MAX_PATH],
*sz_SystemPath = new WCHAR[MAX_PATH],
*szSystemDllPath = new WCHAR[MAX_PATH];
PWCHAR 	pwc_DllName;
PWCHAR 	pwc_ExeName;
WCHAR g_szArgs_UNICODE[8200] = L"--force-fieldtrials=ExtensionDeveloperModeWarning/None/";


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

		SetCommandLineW();

		MessageBoxW(NULL, GetCommandLineW(), L"Debug Info", MB_OK);
	
	
	}

}


typedef HRESULT(*CreateD3D_fn)(IDXGIAdapter *,
	D3D_DRIVER_TYPE,
	HMODULE,
	UINT,
	const D3D_FEATURE_LEVEL*,
	UINT,
	UINT,
	ID3D11Device**,
	D3D_FEATURE_LEVEL   *,
	ID3D11DeviceContext **);


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




	 CreateD3D_fn ori_D3D11CreateDevice

		 = (CreateD3D_fn)GetProcAddress(d3d11.dll, "D3D11CreateDevice");

	 HRESULT hr =

		 ori_D3D11CreateDevice(pAdapter, DriverType, Software,
			 Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice
			 , pFeatureLevel, ppImmediateContext);

	 //*pFeatureLevel = { D3D_FEATURE_LEVEL_10_1 };

	 return hr;
	 //d3d11.D3D11CreateDevice = GetProcAddress(d3d11.dll, "D3D11CreateDevice")

 }


 void Redirect(PWCHAR name) {

	 wcscpy_s(szSystemDllPath, MAX_PATH, sz_SystemPath);

	 wcscat_s(szSystemDllPath, MAX_PATH, L"\\");

	 wcscat_s(szSystemDllPath, MAX_PATH, name);


	 PWCHAR DllName = name;

	 if (_tcsicmp(DllName , L"d3d11.dll") == NULL) {
		 d3d11.dll = LoadLibrary(szSystemDllPath);

		 d3d11.D3D11CoreCreateDevice = GetProcAddress(d3d11.dll, "D3D11CoreCreateDevice");
		 d3d11.D3D11CoreCreateLayeredDevice = GetProcAddress(d3d11.dll, "D3D11CoreCreateLayeredDevice");
		 d3d11.D3D11CoreGetLayeredDeviceSize = GetProcAddress(d3d11.dll, "D3D11CoreGetLayeredDeviceSize");
		 d3d11.D3D11CoreRegisterLayers = GetProcAddress(d3d11.dll, "D3D11CoreRegisterLayers");
		 d3d11.D3D11CreateDevice = (FARPROC)mod_D3D11CreateDevice;
		 //d3d11.D3D11CreateDevice = GetProcAddress(d3d11.dll, "D3D11CreateDevice");
		 d3d11.D3D11CreateDeviceAndSwapChain = GetProcAddress(d3d11.dll, "D3D11CreateDeviceAndSwapChain");
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


BOOL APIENTRY DllMain( HMODULE hInst,
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


		pwc_DllName = _tcsrchr(wc_DllPath, L'\\');

		pwc_DllName = &pwc_DllName[1];

		GetSystemDirectory(sz_SystemPath, MAX_PATH);


		Redirect(pwc_DllName);

		pwc_ExeName = _tcsrchr(wc_ExePath, L'\\');

		pwc_ExeName = &pwc_ExeName[1];


		SomeGameMod();
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





