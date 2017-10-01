#pragma once
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
struct version_dll
{
	HMODULE dll;
	FARPROC GetFileVersionInfoSizeA;
	FARPROC VerQueryValueA;
	FARPROC VerQueryValueW;
	FARPROC GetFileVersionInfoExW;
	FARPROC GetFileVersionInfoSizeExW;
	FARPROC GetFileVersionInfoSizeW;
	FARPROC GetFileVersionInfoW;
	FARPROC GetFileVersionInfoA;
	FARPROC GetFileVersionInfoExA;
	FARPROC GetFileVersionInfoSizeExA;
	FARPROC VerFindFileA;
	FARPROC VerInstallFileA;
	FARPROC GetFileVersionInfoByHandle;
	FARPROC VerFindFileW;
	FARPROC VerInstallFileW;
	FARPROC VerLanguageNameA;
	FARPROC VerLanguageNameW;

} version;



void _D3D11CreateDevice() {
	d3d11.D3D11CreateDevice();
}
void _D3D11CoreCreateDevice() {
	d3d11.D3D11CoreCreateDevice();
}
void _D3D11CoreCreateLayeredDevice() { d3d11.D3D11CoreCreateLayeredDevice(); }
void _D3D11CoreGetLayeredDeviceSize() { d3d11.D3D11CoreGetLayeredDeviceSize(); }
void _D3D11CoreRegisterLayers() { d3d11.D3D11CoreRegisterLayers(); }
void _D3D11CreateDeviceAndSwapChain() { d3d11.D3D11CreateDeviceAndSwapChain(); }
void _D3DKMTCloseAdapter() { d3d11.D3DKMTCloseAdapter(); }
void _D3DKMTCreateAllocation() { d3d11.D3DKMTCreateAllocation(); }
void _D3DKMTCreateContext() { d3d11.D3DKMTCreateContext(); }
void _D3DKMTCreateDevice() { d3d11.D3DKMTCreateDevice(); }
void _D3DKMTCreateSynchronizationObject() { d3d11.D3DKMTCreateSynchronizationObject(); }
void _D3DKMTDestroyAllocation() { d3d11.D3DKMTDestroyAllocation(); }
void _D3DKMTDestroyContext() { d3d11.D3DKMTDestroyContext(); }
void _D3DKMTDestroyDevice() { d3d11.D3DKMTDestroyDevice(); }
void _D3DKMTDestroySynchronizationObject() { d3d11.D3DKMTDestroySynchronizationObject(); }
void _D3DKMTEscape() { d3d11.D3DKMTEscape(); }
void _D3DKMTGetContextSchedulingPriority() { d3d11.D3DKMTGetContextSchedulingPriority(); }
void _D3DKMTGetDeviceState() { d3d11.D3DKMTGetDeviceState(); }
void _D3DKMTGetDisplayModeList() { d3d11.D3DKMTGetDisplayModeList(); }
void _D3DKMTGetMultisampleMethodList() { d3d11.D3DKMTGetMultisampleMethodList(); }
void _D3DKMTGetRuntimeData() { d3d11.D3DKMTGetRuntimeData(); }
void _D3DKMTGetSharedPrimaryHandle() { d3d11.D3DKMTGetSharedPrimaryHandle(); }
void _D3DKMTLock() { d3d11.D3DKMTLock(); }
void _D3DKMTOpenAdapterFromHdc() { d3d11.D3DKMTOpenAdapterFromHdc(); }
void _D3DKMTOpenResource() { d3d11.D3DKMTOpenResource(); }
void _D3DKMTPresent() { d3d11.D3DKMTPresent(); }
void _D3DKMTQueryAdapterInfo() { d3d11.D3DKMTQueryAdapterInfo(); }
void _D3DKMTQueryAllocationResidency() { d3d11.D3DKMTQueryAllocationResidency(); }
void _D3DKMTQueryResourceInfo() { d3d11.D3DKMTQueryResourceInfo(); }
void _D3DKMTRender() { d3d11.D3DKMTRender(); }
void _D3DKMTSetAllocationPriority() { d3d11.D3DKMTSetAllocationPriority(); }
void _D3DKMTSetContextSchedulingPriority() { d3d11.D3DKMTSetContextSchedulingPriority(); }
void _D3DKMTSetDisplayMode() { d3d11.D3DKMTSetDisplayMode(); }
void _D3DKMTSetDisplayPrivateDriverFormat() { d3d11.D3DKMTSetDisplayPrivateDriverFormat(); }
void _D3DKMTSetGammaRamp() { d3d11.D3DKMTSetGammaRamp(); }
void _D3DKMTSetVidPnSourceOwner() { d3d11.D3DKMTSetVidPnSourceOwner(); }
void _D3DKMTSignalSynchronizationObject() { d3d11.D3DKMTSignalSynchronizationObject(); }
void _D3DKMTUnlock() { d3d11.D3DKMTUnlock(); }
void _D3DKMTWaitForSynchronizationObject() { d3d11.D3DKMTWaitForSynchronizationObject(); }
void _D3DKMTWaitForVerticalBlankEvent() { d3d11.D3DKMTWaitForVerticalBlankEvent(); }
void _D3DPerformance_BeginEvent() { d3d11.D3DPerformance_BeginEvent(); }
void _D3DPerformance_EndEvent() { d3d11.D3DPerformance_EndEvent(); }
void _D3DPerformance_GetStatus() { d3d11.D3DPerformance_GetStatus(); }
void _D3DPerformance_SetMarker() { d3d11.D3DPerformance_SetMarker(); }
void _EnableFeatureLevelUpgrade() { d3d11.EnableFeatureLevelUpgrade(); }
void _OpenAdapter10() { d3d11.OpenAdapter10(); }
void _OpenAdapter10_2() { d3d11.OpenAdapter10_2(); }

void Proxy_GetFileVersionInfoSizeA() {version.GetFileVersionInfoSizeA(); }
void Proxy_VerQueryValueA() { version.VerQueryValueA(); }
void Proxy_VerQueryValueW() { version.VerQueryValueW(); }
void Proxy_GetFileVersionInfoExW() { version.GetFileVersionInfoExW(); }
void Proxy_GetFileVersionInfoSizeExW() { version.GetFileVersionInfoSizeExW(); }
void Proxy_GetFileVersionInfoSizeW() { version.GetFileVersionInfoSizeW(); }
void Proxy_GetFileVersionInfoW() { version.GetFileVersionInfoW(); }
void Proxy_GetFileVersionInfoA() { version.GetFileVersionInfoA(); }
void Proxy_GetFileVersionInfoExA() { version.GetFileVersionInfoExA(); }
void Proxy_GetFileVersionInfoSizeExA() { version.GetFileVersionInfoSizeExA(); }
void Proxy_VerFindFileA() { version.VerFindFileA(); }
void Proxy_VerInstallFileA() { version.VerInstallFileA(); }
void Proxy_GetFileVersionInfoByHandle() { version.GetFileVersionInfoByHandle(); }
void Proxy_VerFindFileW() { version.VerFindFileW(); }
void Proxy_VerInstallFileW() { version.VerInstallFileW(); }
void Proxy_VerLanguageNameA() { version.VerLanguageNameA(); }
void Proxy_VerLanguageNameW() { version.VerLanguageNameW(); }
