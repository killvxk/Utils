// proxydll.cpp
#include "stdafx.h"
#include "proxydll.h"
// global variables
#pragma data_seg (".d3d9_shared")
myIDirect3DDevice9* gl_pmyIDirect3DDevice9;
myIDirect3D9*       gl_pmyIDirect3D9;
HINSTANCE           gl_hThisInstance;
#pragma data_seg ()

BYTE 					originalCode[5];
BYTE* 					originalEP = 0;
HMODULE dllModule;
HINSTANCE hExecutableInstance;
WCHAR *DllPath = new WCHAR[MAX_PATH],
*szSystemPath = new WCHAR[MAX_PATH],
*szSystemDllPath = new WCHAR[MAX_PATH];



void Redirect(PWCHAR);
BOOL CALLBACK FindHwndFromPID(HWND hwnd, LPARAM lParam);
void LoadPlugins(PWCHAR dllname)
{
	Redirect(dllname);
}

void InitInstance(HANDLE hModule)
{
//	OutputDebugString("PROXYDLL: InitInstance called.\r\n");

	// Initialisation
	gl_hThisInstance = NULL;
	gl_pmyIDirect3D9 = NULL;
	gl_pmyIDirect3DDevice9 = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)hModule;
}


BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		dllModule = hInst;
		InitInstance(hInst);
		hExecutableInstance = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)
		GetModuleFileName(dllModule, DllPath, MAX_PATH);

		WCHAR	*DllName = _tcsrchr(DllPath, '\\');

		SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &szSystemPath);

		//_tcscat(szSystemPath, DllName);
	//	_tcscat(szSystemDllPath,L"d3d11.dll");

		//int nForceEPHook = GetPrivateProfileInt("globalsets", "forceentrypointhook", 
		//	FALSE, "scripts\\global.ini");

		LoadPlugins(DllName);
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(dsound.dll);
		FreeLibrary(dinput8.dll);
		FreeLibrary(ddraw.dll);
		FreeLibrary(d3d8.dll);
		FreeLibrary(d3d9.dll);
		FreeLibrary(d3d11.dll);
		FreeLibrary(winmmbase.dll);
		FreeLibrary(msacm32.dll);
	}

	return TRUE;
}

void Redirect(PWCHAR name)
{
	

	_tcscpy(szSystemDllPath, szSystemPath);
	_tcscat(szSystemDllPath, name);

	//MessageBox(NULL, szSystemDllPath, L"Proxy Dll", MB_ICONWARNING);

	PWCHAR DllName = name+sizeof('\\');

	if (_tcsicmp(DllName , L"dsound.dll") == NULL) {
		dsound.dll = LoadLibrary(szSystemDllPath);
		dsound.DirectSoundCaptureCreate = GetProcAddress(dsound.dll, "DirectSoundCaptureCreate");
		dsound.DirectSoundCaptureCreate8 = GetProcAddress(dsound.dll, "DirectSoundCaptureCreate8");
		dsound.DirectSoundCaptureEnumerateA = GetProcAddress(dsound.dll, "DirectSoundCaptureEnumerateA");
		dsound.DirectSoundCaptureEnumerateW = GetProcAddress(dsound.dll, "DirectSoundCaptureEnumerateW");
		dsound.DirectSoundCreate = GetProcAddress(dsound.dll, "DirectSoundCreate");
		dsound.DirectSoundCreate8 = GetProcAddress(dsound.dll, "DirectSoundCreate8");
		dsound.DirectSoundEnumerateA = GetProcAddress(dsound.dll, "DirectSoundEnumerateA");
		dsound.DirectSoundEnumerateW = GetProcAddress(dsound.dll, "DirectSoundEnumerateW");
		dsound.DirectSoundFullDuplexCreate = GetProcAddress(dsound.dll, "DirectSoundFullDuplexCreate");
		dsound.DllCanUnloadNow_dsound = GetProcAddress(dsound.dll, "DllCanUnloadNow");
		dsound.DllGetClassObject_dsound = GetProcAddress(dsound.dll, "DllGetClassObject");
		dsound.GetDeviceID = GetProcAddress(dsound.dll, "GetDeviceID");
	}
	else

		if (_tcsicmp(DllName , L"dinput8.dll") == NULL) {
			dinput8.dll = LoadLibrary(szSystemDllPath);
			dinput8.DirectInput8Create = GetProcAddress(dinput8.dll, "DirectInput8Create");
			dinput8.DllCanUnloadNow = GetProcAddress(dinput8.dll, "DllCanUnloadNow");
			dinput8.DllGetClassObject = GetProcAddress(dinput8.dll, "DllGetClassObject");
			dinput8.DllRegisterServer = GetProcAddress(dinput8.dll, "DllRegisterServer");
			dinput8.DllUnregisterServer = GetProcAddress(dinput8.dll, "DllUnregisterServer");
		}
		else

			if (_tcsicmp(DllName , L"ddraw.dll") == NULL) {
				ddraw.dll = LoadLibrary(szSystemDllPath);
				ddraw.AcquireDDThreadLock = GetProcAddress(ddraw.dll, "AcquireDDThreadLock");
				ddraw.CheckFullscreen = GetProcAddress(ddraw.dll, "CheckFullscreen");
				ddraw.CompleteCreateSysmemSurface = GetProcAddress(ddraw.dll, "CompleteCreateSysmemSurface");
				ddraw.D3DParseUnknownCommand = GetProcAddress(ddraw.dll, "D3DParseUnknownCommand");
				ddraw.DDGetAttachedSurfaceLcl = GetProcAddress(ddraw.dll, "DDGetAttachedSurfaceLcl");
				ddraw.DDInternalLock = GetProcAddress(ddraw.dll, "DDInternalLock");
				ddraw.DDInternalUnlock = GetProcAddress(ddraw.dll, "DDInternalUnlock");
				ddraw.DSoundHelp = GetProcAddress(ddraw.dll, "DSoundHelp");
				ddraw.DirectDrawCreate = GetProcAddress(ddraw.dll, "DirectDrawCreate");
				ddraw.DirectDrawCreateClipper = GetProcAddress(ddraw.dll, "DirectDrawCreateClipper");
				ddraw.DirectDrawCreateEx = GetProcAddress(ddraw.dll, "DirectDrawCreateEx");
				ddraw.DirectDrawEnumerateA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateA");
				ddraw.DirectDrawEnumerateExA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExA");
				ddraw.DirectDrawEnumerateExW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExW");
				ddraw.DirectDrawEnumerateW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateW");
				ddraw.DllCanUnloadNow = GetProcAddress(ddraw.dll, "DllCanUnloadNow");
				ddraw.DllGetClassObject = GetProcAddress(ddraw.dll, "DllGetClassObject");
				ddraw.GetDDSurfaceLocal = GetProcAddress(ddraw.dll, "GetDDSurfaceLocal");
				ddraw.GetOLEThunkData = GetProcAddress(ddraw.dll, "GetOLEThunkData");
				ddraw.GetSurfaceFromDC = GetProcAddress(ddraw.dll, "GetSurfaceFromDC");
				ddraw.RegisterSpecialCase = GetProcAddress(ddraw.dll, "RegisterSpecialCase");
				ddraw.ReleaseDDThreadLock = GetProcAddress(ddraw.dll, "ReleaseDDThreadLock");
			}
			else

				if (_tcsicmp(DllName , L"d3d8.dll") == NULL) {
					d3d8.dll = LoadLibrary(szSystemDllPath);
					d3d8.DebugSetMute_d3d8 = GetProcAddress(d3d8.dll, "DebugSetMute_d3d8");
					d3d8.Direct3DCreate8 = GetProcAddress(d3d8.dll, "Direct3DCreate8");
					d3d8.ValidatePixelShader = GetProcAddress(d3d8.dll, "ValidatePixelShader");
					d3d8.ValidateVertexShader = GetProcAddress(d3d8.dll, "ValidateVertexShader");
				}
				else
					if (_tcsicmp(DllName , L"d3d9.dll") == NULL) {
						d3d9.dll = LoadLibrary(szSystemDllPath);
						d3d9.D3DPERF_BeginEvent = GetProcAddress(d3d9.dll, "D3DPERF_BeginEvent");
						d3d9.D3DPERF_EndEvent = GetProcAddress(d3d9.dll, "D3DPERF_EndEvent");
						d3d9.D3DPERF_GetStatus = GetProcAddress(d3d9.dll, "D3DPERF_GetStatus");
						d3d9.D3DPERF_QueryRepeatFrame = GetProcAddress(d3d9.dll, "D3DPERF_QueryRepeatFrame");
						d3d9.D3DPERF_SetMarker = GetProcAddress(d3d9.dll, "D3DPERF_SetMarker");
						d3d9.D3DPERF_SetOptions = GetProcAddress(d3d9.dll, "D3DPERF_SetOptions");
						d3d9.D3DPERF_SetRegion = GetProcAddress(d3d9.dll, "D3DPERF_SetRegion");
						d3d9.DebugSetLevel = GetProcAddress(d3d9.dll, "DebugSetLevel");
						d3d9.DebugSetMute = GetProcAddress(d3d9.dll, "DebugSetMute");
					
						//d3d9.Direct3D9EnableMaximizedWindowedModeShim = GetProcAddress(d3d9.dll, "Direct3D9EnableMaximizedWindowedModeShim");
						//d3d9.Direct3DCreate9 = GetProcAddress(d3d9.dll, "Direct3DCreate9");
						d3d9.Direct3DCreate9 = (FARPROC)mod_Direct3DCreate9;
						d3d9.Direct3DCreate9Ex = GetProcAddress(d3d9.dll, "Direct3DCreate9Ex");
						d3d9.Direct3DShaderValidatorCreate9 = GetProcAddress(d3d9.dll, "Direct3DShaderValidatorCreate9");
						d3d9.PSGPError = GetProcAddress(d3d9.dll, "PSGPError");
						d3d9.PSGPSampleTexture = GetProcAddress(d3d9.dll, "PSGPSampleTexture");
					}
					else

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
						else

							if (_tcsicmp(DllName , L"winmmbase.dll") == NULL) {
								winmmbase.dll = LoadLibrary(szSystemDllPath);
								winmmbase.CloseDriver = GetProcAddress(winmmbase.dll, "CloseDriver");
								winmmbase.DefDriverProc = GetProcAddress(winmmbase.dll, "DefDriverProc");
								winmmbase.DriverCallback = GetProcAddress(winmmbase.dll, "DriverCallback");
								winmmbase.DrvGetModuleHandle = GetProcAddress(winmmbase.dll, "DrvGetModuleHandle");
								winmmbase.GetDriverModuleHandle = GetProcAddress(winmmbase.dll, "GetDriverModuleHandle");
								winmmbase.OpenDriver = GetProcAddress(winmmbase.dll, "OpenDriver");
								winmmbase.SendDriverMessage = GetProcAddress(winmmbase.dll, "SendDriverMessage");
								winmmbase.auxGetDevCapsA = GetProcAddress(winmmbase.dll, "auxGetDevCapsA");
								winmmbase.auxGetDevCapsW = GetProcAddress(winmmbase.dll, "auxGetDevCapsW");
								winmmbase.auxGetNumDevs = GetProcAddress(winmmbase.dll, "auxGetNumDevs");
								winmmbase.auxGetVolume = GetProcAddress(winmmbase.dll, "auxGetVolume");
								winmmbase.auxOutMessage = GetProcAddress(winmmbase.dll, "auxOutMessage");
								winmmbase.auxSetVolume = GetProcAddress(winmmbase.dll, "auxSetVolume");
								winmmbase.joyConfigChanged = GetProcAddress(winmmbase.dll, "joyConfigChanged");
								winmmbase.joyGetDevCapsA = GetProcAddress(winmmbase.dll, "joyGetDevCapsA");
								winmmbase.joyGetDevCapsW = GetProcAddress(winmmbase.dll, "joyGetDevCapsW");
								winmmbase.joyGetNumDevs = GetProcAddress(winmmbase.dll, "joyGetNumDevs");
								winmmbase.joyGetPos = GetProcAddress(winmmbase.dll, "joyGetPos");
								winmmbase.joyGetPosEx = GetProcAddress(winmmbase.dll, "joyGetPosEx");
								winmmbase.joyGetThreshold = GetProcAddress(winmmbase.dll, "joyGetThreshold");
								winmmbase.joyReleaseCapture = GetProcAddress(winmmbase.dll, "joyReleaseCapture");
								winmmbase.joySetCapture = GetProcAddress(winmmbase.dll, "joySetCapture");
								winmmbase.joySetThreshold = GetProcAddress(winmmbase.dll, "joySetThreshold");
								winmmbase.midiConnect = GetProcAddress(winmmbase.dll, "midiConnect");
								winmmbase.midiDisconnect = GetProcAddress(winmmbase.dll, "midiDisconnect");
								winmmbase.midiInAddBuffer = GetProcAddress(winmmbase.dll, "midiInAddBuffer");
								winmmbase.midiInClose = GetProcAddress(winmmbase.dll, "midiInClose");
								winmmbase.midiInGetDevCapsA = GetProcAddress(winmmbase.dll, "midiInGetDevCapsA");
								winmmbase.midiInGetDevCapsW = GetProcAddress(winmmbase.dll, "midiInGetDevCapsW");
								winmmbase.midiInGetErrorTextA = GetProcAddress(winmmbase.dll, "midiInGetErrorTextA");
								winmmbase.midiInGetErrorTextW = GetProcAddress(winmmbase.dll, "midiInGetErrorTextW");
								winmmbase.midiInGetID = GetProcAddress(winmmbase.dll, "midiInGetID");
								winmmbase.midiInGetNumDevs = GetProcAddress(winmmbase.dll, "midiInGetNumDevs");
								winmmbase.midiInMessage = GetProcAddress(winmmbase.dll, "midiInMessage");
								winmmbase.midiInOpen = GetProcAddress(winmmbase.dll, "midiInOpen");
								winmmbase.midiInPrepareHeader = GetProcAddress(winmmbase.dll, "midiInPrepareHeader");
								winmmbase.midiInReset = GetProcAddress(winmmbase.dll, "midiInReset");
								winmmbase.midiInStart = GetProcAddress(winmmbase.dll, "midiInStart");
								winmmbase.midiInStop = GetProcAddress(winmmbase.dll, "midiInStop");
								winmmbase.midiInUnprepareHeader = GetProcAddress(winmmbase.dll, "midiInUnprepareHeader");
								winmmbase.midiOutCacheDrumPatches = GetProcAddress(winmmbase.dll, "midiOutCacheDrumPatches");
								winmmbase.midiOutCachePatches = GetProcAddress(winmmbase.dll, "midiOutCachePatches");
								winmmbase.midiOutClose = GetProcAddress(winmmbase.dll, "midiOutClose");
								winmmbase.midiOutGetDevCapsA = GetProcAddress(winmmbase.dll, "midiOutGetDevCapsA");
								winmmbase.midiOutGetDevCapsW = GetProcAddress(winmmbase.dll, "midiOutGetDevCapsW");
								winmmbase.midiOutGetErrorTextA = GetProcAddress(winmmbase.dll, "midiOutGetErrorTextA");
								winmmbase.midiOutGetErrorTextW = GetProcAddress(winmmbase.dll, "midiOutGetErrorTextW");
								winmmbase.midiOutGetID = GetProcAddress(winmmbase.dll, "midiOutGetID");
								winmmbase.midiOutGetNumDevs = GetProcAddress(winmmbase.dll, "midiOutGetNumDevs");
								winmmbase.midiOutGetVolume = GetProcAddress(winmmbase.dll, "midiOutGetVolume");
								winmmbase.midiOutLongMsg = GetProcAddress(winmmbase.dll, "midiOutLongMsg");
								winmmbase.midiOutMessage = GetProcAddress(winmmbase.dll, "midiOutMessage");
								winmmbase.midiOutOpen = GetProcAddress(winmmbase.dll, "midiOutOpen");
								winmmbase.midiOutPrepareHeader = GetProcAddress(winmmbase.dll, "midiOutPrepareHeader");
								winmmbase.midiOutReset = GetProcAddress(winmmbase.dll, "midiOutReset");
								winmmbase.midiOutSetVolume = GetProcAddress(winmmbase.dll, "midiOutSetVolume");
								winmmbase.midiOutShortMsg = GetProcAddress(winmmbase.dll, "midiOutShortMsg");
								winmmbase.midiOutUnprepareHeader = GetProcAddress(winmmbase.dll, "midiOutUnprepareHeader");
								winmmbase.midiStreamClose = GetProcAddress(winmmbase.dll, "midiStreamClose");
								winmmbase.midiStreamOpen = GetProcAddress(winmmbase.dll, "midiStreamOpen");
								winmmbase.midiStreamOut = GetProcAddress(winmmbase.dll, "midiStreamOut");
								winmmbase.midiStreamPause = GetProcAddress(winmmbase.dll, "midiStreamPause");
								winmmbase.midiStreamPosition = GetProcAddress(winmmbase.dll, "midiStreamPosition");
								winmmbase.midiStreamProperty = GetProcAddress(winmmbase.dll, "midiStreamProperty");
								winmmbase.midiStreamRestart = GetProcAddress(winmmbase.dll, "midiStreamRestart");
								winmmbase.midiStreamStop = GetProcAddress(winmmbase.dll, "midiStreamStop");
								winmmbase.mixerClose = GetProcAddress(winmmbase.dll, "mixerClose");
								winmmbase.mixerGetControlDetailsA = GetProcAddress(winmmbase.dll, "mixerGetControlDetailsA");
								winmmbase.mixerGetControlDetailsW = GetProcAddress(winmmbase.dll, "mixerGetControlDetailsW");
								winmmbase.mixerGetDevCapsA = GetProcAddress(winmmbase.dll, "mixerGetDevCapsA");
								winmmbase.mixerGetDevCapsW = GetProcAddress(winmmbase.dll, "mixerGetDevCapsW");
								winmmbase.mixerGetID = GetProcAddress(winmmbase.dll, "mixerGetID");
								winmmbase.mixerGetLineControlsA = GetProcAddress(winmmbase.dll, "mixerGetLineControlsA");
								winmmbase.mixerGetLineControlsW = GetProcAddress(winmmbase.dll, "mixerGetLineControlsW");
								winmmbase.mixerGetLineInfoA = GetProcAddress(winmmbase.dll, "mixerGetLineInfoA");
								winmmbase.mixerGetLineInfoW = GetProcAddress(winmmbase.dll, "mixerGetLineInfoW");
								winmmbase.mixerGetNumDevs = GetProcAddress(winmmbase.dll, "mixerGetNumDevs");
								winmmbase.mixerMessage = GetProcAddress(winmmbase.dll, "mixerMessage");
								winmmbase.mixerOpen = GetProcAddress(winmmbase.dll, "mixerOpen");
								winmmbase.mixerSetControlDetails = GetProcAddress(winmmbase.dll, "mixerSetControlDetails");
								winmmbase.mmDrvInstall = GetProcAddress(winmmbase.dll, "mmDrvInstall");
								winmmbase.mmGetCurrentTask = GetProcAddress(winmmbase.dll, "mmGetCurrentTask");
								winmmbase.mmTaskBlock = GetProcAddress(winmmbase.dll, "mmTaskBlock");
								winmmbase.mmTaskCreate = GetProcAddress(winmmbase.dll, "mmTaskCreate");
								winmmbase.mmTaskSignal = GetProcAddress(winmmbase.dll, "mmTaskSignal");
								winmmbase.mmTaskYield = GetProcAddress(winmmbase.dll, "mmTaskYield");
								winmmbase.mmioAdvance = GetProcAddress(winmmbase.dll, "mmioAdvance");
								winmmbase.mmioAscend = GetProcAddress(winmmbase.dll, "mmioAscend");
								winmmbase.mmioClose = GetProcAddress(winmmbase.dll, "mmioClose");
								winmmbase.mmioCreateChunk = GetProcAddress(winmmbase.dll, "mmioCreateChunk");
								winmmbase.mmioDescend = GetProcAddress(winmmbase.dll, "mmioDescend");
								winmmbase.mmioFlush = GetProcAddress(winmmbase.dll, "mmioFlush");
								winmmbase.mmioGetInfo = GetProcAddress(winmmbase.dll, "mmioGetInfo");
								winmmbase.mmioInstallIOProcA = GetProcAddress(winmmbase.dll, "mmioInstallIOProcA");
								winmmbase.mmioInstallIOProcW = GetProcAddress(winmmbase.dll, "mmioInstallIOProcW");
								winmmbase.mmioOpenA = GetProcAddress(winmmbase.dll, "mmioOpenA");
								winmmbase.mmioOpenW = GetProcAddress(winmmbase.dll, "mmioOpenW");
								winmmbase.mmioRead = GetProcAddress(winmmbase.dll, "mmioRead");
								winmmbase.mmioRenameA = GetProcAddress(winmmbase.dll, "mmioRenameA");
								winmmbase.mmioRenameW = GetProcAddress(winmmbase.dll, "mmioRenameW");
								winmmbase.mmioSeek = GetProcAddress(winmmbase.dll, "mmioSeek");
								winmmbase.mmioSendMessage = GetProcAddress(winmmbase.dll, "mmioSendMessage");
								winmmbase.mmioSetBuffer = GetProcAddress(winmmbase.dll, "mmioSetBuffer");
								winmmbase.mmioSetInfo = GetProcAddress(winmmbase.dll, "mmioSetInfo");
								winmmbase.mmioStringToFOURCCA = GetProcAddress(winmmbase.dll, "mmioStringToFOURCCA");
								winmmbase.mmioStringToFOURCCW = GetProcAddress(winmmbase.dll, "mmioStringToFOURCCW");
								winmmbase.mmioWrite = GetProcAddress(winmmbase.dll, "mmioWrite");
								winmmbase.sndOpenSound = GetProcAddress(winmmbase.dll, "sndOpenSound");
								winmmbase.waveInAddBuffer = GetProcAddress(winmmbase.dll, "waveInAddBuffer");
								winmmbase.waveInClose = GetProcAddress(winmmbase.dll, "waveInClose");
								winmmbase.waveInGetDevCapsA = GetProcAddress(winmmbase.dll, "waveInGetDevCapsA");
								winmmbase.waveInGetDevCapsW = GetProcAddress(winmmbase.dll, "waveInGetDevCapsW");
								winmmbase.waveInGetErrorTextA = GetProcAddress(winmmbase.dll, "waveInGetErrorTextA");
								winmmbase.waveInGetErrorTextW = GetProcAddress(winmmbase.dll, "waveInGetErrorTextW");
								winmmbase.waveInGetID = GetProcAddress(winmmbase.dll, "waveInGetID");
								winmmbase.waveInGetNumDevs = GetProcAddress(winmmbase.dll, "waveInGetNumDevs");
								winmmbase.waveInGetPosition = GetProcAddress(winmmbase.dll, "waveInGetPosition");
								winmmbase.waveInMessage = GetProcAddress(winmmbase.dll, "waveInMessage");
								winmmbase.waveInOpen = GetProcAddress(winmmbase.dll, "waveInOpen");
								winmmbase.waveInPrepareHeader = GetProcAddress(winmmbase.dll, "waveInPrepareHeader");
								winmmbase.waveInReset = GetProcAddress(winmmbase.dll, "waveInReset");
								winmmbase.waveInStart = GetProcAddress(winmmbase.dll, "waveInStart");
								winmmbase.waveInStop = GetProcAddress(winmmbase.dll, "waveInStop");
								winmmbase.waveInUnprepareHeader = GetProcAddress(winmmbase.dll, "waveInUnprepareHeader");
								winmmbase.waveOutBreakLoop = GetProcAddress(winmmbase.dll, "waveOutBreakLoop");
								winmmbase.waveOutClose = GetProcAddress(winmmbase.dll, "waveOutClose");
								winmmbase.waveOutGetDevCapsA = GetProcAddress(winmmbase.dll, "waveOutGetDevCapsA");
								winmmbase.waveOutGetDevCapsW = GetProcAddress(winmmbase.dll, "waveOutGetDevCapsW");
								winmmbase.waveOutGetErrorTextA = GetProcAddress(winmmbase.dll, "waveOutGetErrorTextA");
								winmmbase.waveOutGetErrorTextW = GetProcAddress(winmmbase.dll, "waveOutGetErrorTextW");
								winmmbase.waveOutGetID = GetProcAddress(winmmbase.dll, "waveOutGetID");
								winmmbase.waveOutGetNumDevs = GetProcAddress(winmmbase.dll, "waveOutGetNumDevs");
								winmmbase.waveOutGetPitch = GetProcAddress(winmmbase.dll, "waveOutGetPitch");
								winmmbase.waveOutGetPlaybackRate = GetProcAddress(winmmbase.dll, "waveOutGetPlaybackRate");
								winmmbase.waveOutGetPosition = GetProcAddress(winmmbase.dll, "waveOutGetPosition");
								winmmbase.waveOutGetVolume = GetProcAddress(winmmbase.dll, "waveOutGetVolume");
								winmmbase.waveOutMessage = GetProcAddress(winmmbase.dll, "waveOutMessage");
								winmmbase.waveOutOpen = GetProcAddress(winmmbase.dll, "waveOutOpen");
								winmmbase.waveOutPause = GetProcAddress(winmmbase.dll, "waveOutPause");
								winmmbase.waveOutPrepareHeader = GetProcAddress(winmmbase.dll, "waveOutPrepareHeader");
								winmmbase.waveOutReset = GetProcAddress(winmmbase.dll, "waveOutReset");
								winmmbase.waveOutRestart = GetProcAddress(winmmbase.dll, "waveOutRestart");
								winmmbase.waveOutSetPitch = GetProcAddress(winmmbase.dll, "waveOutSetPitch");
								winmmbase.waveOutSetPlaybackRate = GetProcAddress(winmmbase.dll, "waveOutSetPlaybackRate");
								winmmbase.waveOutSetVolume = GetProcAddress(winmmbase.dll, "waveOutSetVolume");
								winmmbase.waveOutUnprepareHeader = GetProcAddress(winmmbase.dll, "waveOutUnprepareHeader");
								winmmbase.waveOutWrite = GetProcAddress(winmmbase.dll, "waveOutWrite");
								winmmbase.winmmbaseFreeMMEHandles = GetProcAddress(winmmbase.dll, "winmmbaseFreeMMEHandles");
								winmmbase.winmmbaseGetWOWHandle = GetProcAddress(winmmbase.dll, "winmmbaseGetWOWHandle");
								winmmbase.winmmbaseHandle32FromHandle16 = GetProcAddress(winmmbase.dll, "winmmbaseHandle32FromHandle16");
								winmmbase.winmmbaseSetWOWHandle = GetProcAddress(winmmbase.dll, "winmmbaseSetWOWHandle");
							}
							else

								if (_tcsicmp(DllName , L"msacm32.dll") == NULL) {
									msacm32.dll = LoadLibrary(szSystemDllPath);
									msacm32.acmDriverAddA = GetProcAddress(msacm32.dll, "acmDriverAddA");
									msacm32.acmDriverAddW = GetProcAddress(msacm32.dll, "acmDriverAddW");
									msacm32.acmDriverClose = GetProcAddress(msacm32.dll, "acmDriverClose");
									msacm32.acmDriverDetailsA = GetProcAddress(msacm32.dll, "acmDriverDetailsA");
									msacm32.acmDriverDetailsW = GetProcAddress(msacm32.dll, "acmDriverDetailsW");
									msacm32.acmDriverEnum = GetProcAddress(msacm32.dll, "acmDriverEnum");
									msacm32.acmDriverID = GetProcAddress(msacm32.dll, "acmDriverID");
									msacm32.acmDriverMessage = GetProcAddress(msacm32.dll, "acmDriverMessage");
									msacm32.acmDriverOpen = GetProcAddress(msacm32.dll, "acmDriverOpen");
									msacm32.acmDriverPriority = GetProcAddress(msacm32.dll, "acmDriverPriority");
									msacm32.acmDriverRemove = GetProcAddress(msacm32.dll, "acmDriverRemove");
									msacm32.acmFilterChooseA = GetProcAddress(msacm32.dll, "acmFilterChooseA");
									msacm32.acmFilterChooseW = GetProcAddress(msacm32.dll, "acmFilterChooseW");
									msacm32.acmFilterDetailsA = GetProcAddress(msacm32.dll, "acmFilterDetailsA");
									msacm32.acmFilterDetailsW = GetProcAddress(msacm32.dll, "acmFilterDetailsW");
									msacm32.acmFilterEnumA = GetProcAddress(msacm32.dll, "acmFilterEnumA");
									msacm32.acmFilterEnumW = GetProcAddress(msacm32.dll, "acmFilterEnumW");
									msacm32.acmFilterTagDetailsA = GetProcAddress(msacm32.dll, "acmFilterTagDetailsA");
									msacm32.acmFilterTagDetailsW = GetProcAddress(msacm32.dll, "acmFilterTagDetailsW");
									msacm32.acmFilterTagEnumA = GetProcAddress(msacm32.dll, "acmFilterTagEnumA");
									msacm32.acmFilterTagEnumW = GetProcAddress(msacm32.dll, "acmFilterTagEnumW");
									msacm32.acmFormatChooseA = GetProcAddress(msacm32.dll, "acmFormatChooseA");
									msacm32.acmFormatChooseW = GetProcAddress(msacm32.dll, "acmFormatChooseW");
									msacm32.acmFormatDetailsA = GetProcAddress(msacm32.dll, "acmFormatDetailsA");
									msacm32.acmFormatDetailsW = GetProcAddress(msacm32.dll, "acmFormatDetailsW");
									msacm32.acmFormatEnumA = GetProcAddress(msacm32.dll, "acmFormatEnumA");
									msacm32.acmFormatEnumW = GetProcAddress(msacm32.dll, "acmFormatEnumW");
									msacm32.acmFormatSuggest = GetProcAddress(msacm32.dll, "acmFormatSuggest");
									msacm32.acmFormatTagDetailsA = GetProcAddress(msacm32.dll, "acmFormatTagDetailsA");
									msacm32.acmFormatTagDetailsW = GetProcAddress(msacm32.dll, "acmFormatTagDetailsW");
									msacm32.acmFormatTagEnumA = GetProcAddress(msacm32.dll, "acmFormatTagEnumA");
									msacm32.acmFormatTagEnumW = GetProcAddress(msacm32.dll, "acmFormatTagEnumW");
									msacm32.acmGetVersion = GetProcAddress(msacm32.dll, "acmGetVersion");
									msacm32.acmMetrics = GetProcAddress(msacm32.dll, "acmMetrics");
									msacm32.acmStreamClose = GetProcAddress(msacm32.dll, "acmStreamClose");
									msacm32.acmStreamConvert = GetProcAddress(msacm32.dll, "acmStreamConvert");
									msacm32.acmStreamMessage = GetProcAddress(msacm32.dll, "acmStreamMessage");
									msacm32.acmStreamOpen = GetProcAddress(msacm32.dll, "acmStreamOpen");
									msacm32.acmStreamPrepareHeader = GetProcAddress(msacm32.dll, "acmStreamPrepareHeader");
									msacm32.acmStreamReset = GetProcAddress(msacm32.dll, "acmStreamReset");
									msacm32.acmStreamSize = GetProcAddress(msacm32.dll, "acmStreamSize");
									msacm32.acmStreamUnprepareHeader = GetProcAddress(msacm32.dll, "acmStreamUnprepareHeader");
								}
								else
								{
									MessageBox(0, L"This library isn't supported. Try to rename it to d3d8.dll, d3d9.dll, d3d11.dll, winmmbase.dll, msacm32.dll, dinput8.dll, dsound.dll, vorbisFile.dll or ddraw.dll.",
										L"ASI Loader", MB_ICONERROR);
									ExitProcess(0);
								}







}

HRESULT WINAPI mod_D3D11CreateDevice(
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
	typedef HRESULT(*ori_Create_fn)(IDXGIAdapter *,
		D3D_DRIVER_TYPE,
		HMODULE,
		UINT,
		const D3D_FEATURE_LEVEL*,
		UINT,
		UINT,
		ID3D11Device**,
		D3D_FEATURE_LEVEL   *,
		ID3D11DeviceContext **);

	//D3D_FEATURE_LEVEL
	//	d3d10_1 = { D3D_FEATURE_LEVEL_11_0 };

	

	ori_Create_fn ori_D3D11CreateDevice= (ori_Create_fn)GetProcAddress(d3d11.dll, "D3D11CreateDevice");

	HRESULT hr=

	 ori_D3D11CreateDevice(pAdapter, DriverType, Software,
		Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice
		, pFeatureLevel, ppImmediateContext);

	//*pFeatureLevel = { D3D_FEATURE_LEVEL_10_1 };

	return hr;
	//d3d11.D3D11CreateDevice = GetProcAddress(d3d11.dll, "D3D11CreateDevice")

}

IDirect3D9* WINAPI mod_Direct3DCreate9(UINT SDKVersion)
{
	 // looking for the "right d3d9.dll"
//	MessageBox(NULL, L"OK", L"mod_Direct3DCreate9", MB_ICONWARNING);
											 // Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT );

	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(d3d9.dll, "Direct3DCreate9");

	// Debug
//	if (!D3DCreate9_fn)
//{
	//	::ExitProcess(0); // exit the hard way
	//}

	// Request pointer from Original Dll. 
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	// Create my IDirect3D8 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	myIDirect3D9* gl_pmyIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);

	// Return pointer to hooking Object instead of "real one"
	return (gl_pmyIDirect3D9);
}

// Exported function (faking d3d9.dll's one-and-only export)
//IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
//{
//	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right d3d9.dll"
//	
//	// Hooking IDirect3D Object from Original Library
//	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
//	D3D9_Type D3DCreate9_fn = (D3D9_Type) GetProcAddress( gl_hOriginalDll, "Direct3DCreate9");
//    
//    // Debug
//	if (!D3DCreate9_fn) 
//    {
//        OutputDebugString(L"PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
//        ::ExitProcess(0); // exit the hard way
//    }
//	
//	// Request pointer from Original Dll. 
//	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);
//	
//	// Create my IDirect3D8 object and store pointer to original object there.
//	// note: the object will delete itself once Ref count is zero (similar to COM objects)
//	gl_pmyIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);
//	
//	// Return pointer to hooking Object instead of "real one"
//	return (gl_pmyIDirect3D9);
//}
//
//void InitInstance(HANDLE hModule) 
//{
//	OutputDebugString(L"PROXYDLL: InitInstance called.\r\n");
//	
//	// Initialisation
//	gl_hOriginalDll        = NULL;
//	gl_hThisInstance       = NULL;
//	gl_pmyIDirect3D9       = NULL;
//	gl_pmyIDirect3DDevice9 = NULL;	
//	
//	// Storing Instance handle into global var
//	gl_hThisInstance = (HINSTANCE)  hModule;
//}

//void LoadOriginalDll(void)
//{
//    char buffer[MAX_PATH];
//    
//    // Getting path to system dir and to d3d8.dll
//	::GetSystemDirectory(buffer,MAX_PATH);
//
//	// Append dll name
//	strcat(buffer,"\\d3d9.dll");
//	
//	// try to load the system's d3d9.dll, if pointer empty
//	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);
//
//	// Debug
//	if (!gl_hOriginalDll)
//	{
//


