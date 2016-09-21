// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"




HMODULE dllModule;
HINSTANCE hExecutableInstance;
WCHAR *DllPath = new WCHAR[MAX_PATH],
*szSystemPath = new WCHAR[MAX_PATH],
*szSystemDllPath = new WCHAR[MAX_PATH];




struct d3d11_dll
{
	HMODULE dll;
	FARPROC D3D11CoreCreateDevice;
	FARPROC D3D11CoreCreateLayeredDevice;
	FARPROC D3D11CoreGetLayeredDeviceSize;
	FARPROC D3D11CoreRegisterLayers;
	FARPROC D3D11CreateDevice;
	FARPROC D3D11CreateDeviceAndSwapChain;
	FARPROC D3DKMTCloseAdapter;
	FARPROC D3DKMTCreateAllocation;
	FARPROC D3DKMTCreateContext;
	FARPROC D3DKMTCreateDevice;
	FARPROC D3DKMTCreateSynchronizationObject;
	FARPROC D3DKMTDestroyAllocation;
	FARPROC D3DKMTDestroyContext;
	FARPROC D3DKMTDestroyDevice;
	FARPROC D3DKMTDestroySynchronizationObject;
	FARPROC D3DKMTEscape;
	FARPROC D3DKMTGetContextSchedulingPriority;
	FARPROC D3DKMTGetDeviceState;
	FARPROC D3DKMTGetDisplayModeList;
	FARPROC D3DKMTGetMultisampleMethodList;
	FARPROC D3DKMTGetRuntimeData;
	FARPROC D3DKMTGetSharedPrimaryHandle;
	FARPROC D3DKMTLock;
	FARPROC D3DKMTOpenAdapterFromHdc;
	FARPROC D3DKMTOpenResource;
	FARPROC D3DKMTPresent;
	FARPROC D3DKMTQueryAdapterInfo;
	FARPROC D3DKMTQueryAllocationResidency;
	FARPROC D3DKMTQueryResourceInfo;
	FARPROC D3DKMTRender;
	FARPROC D3DKMTSetAllocationPriority;
	FARPROC D3DKMTSetContextSchedulingPriority;
	FARPROC D3DKMTSetDisplayMode;
	FARPROC D3DKMTSetDisplayPrivateDriverFormat;
	FARPROC D3DKMTSetGammaRamp;
	FARPROC D3DKMTSetVidPnSourceOwner;
	FARPROC D3DKMTSignalSynchronizationObject;
	FARPROC D3DKMTUnlock;
	FARPROC D3DKMTWaitForSynchronizationObject;
	FARPROC D3DKMTWaitForVerticalBlankEvent;
	FARPROC D3DPerformance_BeginEvent;
	FARPROC D3DPerformance_EndEvent;
	FARPROC D3DPerformance_GetStatus;
	FARPROC D3DPerformance_SetMarker;
	FARPROC EnableFeatureLevelUpgrade;
	FARPROC OpenAdapter10;
	FARPROC OpenAdapter10_2;
} d3d11;

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

void _D3D11CreateDevice() {
	d3d11.D3D11CreateDevice();
}
void _D3D11CoreCreateDevice() {
	d3d11.D3D11CoreCreateDevice();
}
 void _D3D11CoreCreateLayeredDevice() { d3d11.D3D11CoreCreateLayeredDevice();}
 void _D3D11CoreGetLayeredDeviceSize() { d3d11.D3D11CoreGetLayeredDeviceSize();}
 void _D3D11CoreRegisterLayers() { d3d11.D3D11CoreRegisterLayers();}
 void _D3D11CreateDeviceAndSwapChain() { d3d11.D3D11CreateDeviceAndSwapChain();}
 void _D3DKMTCloseAdapter() { d3d11.D3DKMTCloseAdapter();}
 void _D3DKMTCreateAllocation() { d3d11.D3DKMTCreateAllocation();}
 void _D3DKMTCreateContext() { d3d11.D3DKMTCreateContext();}
 void _D3DKMTCreateDevice() { d3d11.D3DKMTCreateDevice();}
 void _D3DKMTCreateSynchronizationObject() { d3d11.D3DKMTCreateSynchronizationObject();}
 void _D3DKMTDestroyAllocation() { d3d11.D3DKMTDestroyAllocation();}
 void _D3DKMTDestroyContext() { d3d11.D3DKMTDestroyContext();}
 void _D3DKMTDestroyDevice() { d3d11.D3DKMTDestroyDevice();}
 void _D3DKMTDestroySynchronizationObject() { d3d11.D3DKMTDestroySynchronizationObject();}
 void _D3DKMTEscape() { d3d11.D3DKMTEscape();}
 void _D3DKMTGetContextSchedulingPriority() { d3d11.D3DKMTGetContextSchedulingPriority();}
 void _D3DKMTGetDeviceState() { d3d11.D3DKMTGetDeviceState();}
 void _D3DKMTGetDisplayModeList() { d3d11.D3DKMTGetDisplayModeList();}
 void _D3DKMTGetMultisampleMethodList() { d3d11.D3DKMTGetMultisampleMethodList();}
 void _D3DKMTGetRuntimeData() { d3d11.D3DKMTGetRuntimeData();}
 void _D3DKMTGetSharedPrimaryHandle() { d3d11.D3DKMTGetSharedPrimaryHandle();}
 void _D3DKMTLock() { d3d11.D3DKMTLock();}
 void _D3DKMTOpenAdapterFromHdc() { d3d11.D3DKMTOpenAdapterFromHdc();}
 void _D3DKMTOpenResource() { d3d11.D3DKMTOpenResource();}
 void _D3DKMTPresent() { d3d11.D3DKMTPresent();}
 void _D3DKMTQueryAdapterInfo() { d3d11.D3DKMTQueryAdapterInfo();}
 void _D3DKMTQueryAllocationResidency() { d3d11.D3DKMTQueryAllocationResidency();}
 void _D3DKMTQueryResourceInfo() { d3d11.D3DKMTQueryResourceInfo();}
 void _D3DKMTRender() { d3d11.D3DKMTRender();}
 void _D3DKMTSetAllocationPriority() { d3d11.D3DKMTSetAllocationPriority();}
 void _D3DKMTSetContextSchedulingPriority() { d3d11.D3DKMTSetContextSchedulingPriority();}
 void _D3DKMTSetDisplayMode() { d3d11.D3DKMTSetDisplayMode();}
 void _D3DKMTSetDisplayPrivateDriverFormat() { d3d11.D3DKMTSetDisplayPrivateDriverFormat();}
 void _D3DKMTSetGammaRamp() { d3d11.D3DKMTSetGammaRamp();}
 void _D3DKMTSetVidPnSourceOwner() { d3d11.D3DKMTSetVidPnSourceOwner();}
 void _D3DKMTSignalSynchronizationObject() { d3d11.D3DKMTSignalSynchronizationObject();}
 void _D3DKMTUnlock() { d3d11.D3DKMTUnlock();}
 void _D3DKMTWaitForSynchronizationObject() { d3d11.D3DKMTWaitForSynchronizationObject();}
 void _D3DKMTWaitForVerticalBlankEvent() { d3d11.D3DKMTWaitForVerticalBlankEvent();}
 void _D3DPerformance_BeginEvent() { d3d11.D3DPerformance_BeginEvent();}
 void _D3DPerformance_EndEvent() { d3d11.D3DPerformance_EndEvent();}
 void _D3DPerformance_GetStatus() { d3d11.D3DPerformance_GetStatus();}
 void _D3DPerformance_SetMarker() { d3d11.D3DPerformance_SetMarker();}
 void _EnableFeatureLevelUpgrade() { d3d11.EnableFeatureLevelUpgrade();}
 void _OpenAdapter10() { d3d11.OpenAdapter10();}
 void _OpenAdapter10_2() { d3d11.OpenAdapter10_2();}
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

	 PWCHAR DllName = name;
	 wcscpy_s(szSystemDllPath,sizeof(szSystemDllPath), szSystemPath);
	 wcscat_s(szSystemDllPath, sizeof(szSystemDllPath), DllName);

	 if (_tcsicmp(DllName + 1, L"d3d11.dll") == NULL) {
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
	 else
	 {
		 MessageBox(0, L"This library isn't supported. Try to rename it to d3d8.dll, d3d9.dll, d3d11.dll, winmmbase.dll, msacm32.dll, dinput8.dll, dsound.dll, vorbisFile.dll or ddraw.dll.", L"ASI Loader", MB_ICONERROR);
		 ExitProcess(0);
	 }



 }

void LoadPlugins(PWCHAR dllname)
{
	Redirect(dllname);
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
		GetModuleFileName(dllModule, DllPath, MAX_PATH);

		WCHAR	*DllName = _tcsrchr(DllPath, '\\');

		SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &szSystemPath);

		//_tcscat(szSystemPath, DllName);
		//	_tcscat(szSystemDllPath,L"d3d11.dll");

		//int nForceEPHook = GetPrivateProfileInt("globalsets", "forceentrypointhook", 
		//	FALSE, "scripts\\global.ini");

		LoadPlugins(DllName);
	}; break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:	FreeLibrary(d3d11.dll);
		break;
	}
	return TRUE;
}





