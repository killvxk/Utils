
#pragma once

HRESULT WINAPI mod_D3D11CreateDevice(
	_In_opt_ IDXGIAdapter *,
	D3D_DRIVER_TYPE,
	HMODULE,
	UINT,
	_In_opt_ D3D_FEATURE_LEVEL*,
	UINT,
	UINT, 
	_Out_opt_ ID3D11Device        **,
	_Out_opt_ D3D_FEATURE_LEVEL   *,
	_Out_opt_ ID3D11DeviceContext **
);

IDirect3D9* WINAPI mod_Direct3DCreate9(UINT);


struct dinput8_dll
{
	HMODULE dll;
	FARPROC DirectInput8Create;
	FARPROC DllCanUnloadNow;
	FARPROC DllGetClassObject;
	FARPROC DllRegisterServer;
	FARPROC DllUnregisterServer;
} dinput8;

struct dsound_dll
{
	HMODULE dll;
	FARPROC DirectSoundCaptureCreate;
	FARPROC DirectSoundCaptureCreate8;
	FARPROC DirectSoundCaptureEnumerateA;
	FARPROC DirectSoundCaptureEnumerateW;
	FARPROC DirectSoundCreate;
	FARPROC DirectSoundCreate8;
	FARPROC DirectSoundEnumerateA;
	FARPROC DirectSoundEnumerateW;
	FARPROC DirectSoundFullDuplexCreate;
	FARPROC DllCanUnloadNow_dsound;
	FARPROC DllGetClassObject_dsound;
	FARPROC GetDeviceID;
} dsound;

struct ddraw_dll
{
	HMODULE dll;
	FARPROC	AcquireDDThreadLock;
	FARPROC	CheckFullscreen;
	FARPROC	CompleteCreateSysmemSurface;
	FARPROC	D3DParseUnknownCommand;
	FARPROC	DDGetAttachedSurfaceLcl;
	FARPROC	DDInternalLock;
	FARPROC	DDInternalUnlock;
	FARPROC	DSoundHelp;
	FARPROC	DirectDrawCreate;
	FARPROC	DirectDrawCreateClipper;
	FARPROC	DirectDrawCreateEx;
	FARPROC	DirectDrawEnumerateA;
	FARPROC	DirectDrawEnumerateExA;
	FARPROC	DirectDrawEnumerateExW;
	FARPROC	DirectDrawEnumerateW;
	FARPROC	DllCanUnloadNow;
	FARPROC	DllGetClassObject;
	FARPROC	GetDDSurfaceLocal;
	FARPROC	GetOLEThunkData;
	FARPROC	GetSurfaceFromDC;
	FARPROC	RegisterSpecialCase;
	FARPROC	ReleaseDDThreadLock;
} ddraw;

struct d3d8_dll
{
	HMODULE dll;
	FARPROC DebugSetMute_d3d8;
	FARPROC Direct3DCreate8;
	FARPROC ValidatePixelShader;
	FARPROC ValidateVertexShader;
} d3d8;

struct d3d9_dll
{
	HMODULE dll;
	FARPROC D3DPERF_BeginEvent;
	FARPROC D3DPERF_EndEvent;
	FARPROC D3DPERF_GetStatus;
	FARPROC D3DPERF_QueryRepeatFrame;
	FARPROC D3DPERF_SetMarker;
	FARPROC D3DPERF_SetOptions;
	FARPROC D3DPERF_SetRegion;
	FARPROC DebugSetLevel;
	FARPROC DebugSetMute;
	FARPROC Direct3D9EnableMaximizedWindowedModeShim;
	FARPROC Direct3DCreate9;
	FARPROC Direct3DCreate9Ex;
	FARPROC Direct3DShaderValidatorCreate9;
	FARPROC PSGPError;
	FARPROC PSGPSampleTexture;
} d3d9;

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

struct winmmbase_dll
{
	HMODULE dll;
	FARPROC CloseDriver;
	FARPROC DefDriverProc;
	FARPROC DriverCallback;
	FARPROC DrvGetModuleHandle;
	FARPROC GetDriverModuleHandle;
	FARPROC OpenDriver;
	FARPROC SendDriverMessage;
	FARPROC auxGetDevCapsA;
	FARPROC auxGetDevCapsW;
	FARPROC auxGetNumDevs;
	FARPROC auxGetVolume;
	FARPROC auxOutMessage;
	FARPROC auxSetVolume;
	FARPROC joyConfigChanged;
	FARPROC joyGetDevCapsA;
	FARPROC joyGetDevCapsW;
	FARPROC joyGetNumDevs;
	FARPROC joyGetPos;
	FARPROC joyGetPosEx;
	FARPROC joyGetThreshold;
	FARPROC joyReleaseCapture;
	FARPROC joySetCapture;
	FARPROC joySetThreshold;
	FARPROC midiConnect;
	FARPROC midiDisconnect;
	FARPROC midiInAddBuffer;
	FARPROC midiInClose;
	FARPROC midiInGetDevCapsA;
	FARPROC midiInGetDevCapsW;
	FARPROC midiInGetErrorTextA;
	FARPROC midiInGetErrorTextW;
	FARPROC midiInGetID;
	FARPROC midiInGetNumDevs;
	FARPROC midiInMessage;
	FARPROC midiInOpen;
	FARPROC midiInPrepareHeader;
	FARPROC midiInReset;
	FARPROC midiInStart;
	FARPROC midiInStop;
	FARPROC midiInUnprepareHeader;
	FARPROC midiOutCacheDrumPatches;
	FARPROC midiOutCachePatches;
	FARPROC midiOutClose;
	FARPROC midiOutGetDevCapsA;
	FARPROC midiOutGetDevCapsW;
	FARPROC midiOutGetErrorTextA;
	FARPROC midiOutGetErrorTextW;
	FARPROC midiOutGetID;
	FARPROC midiOutGetNumDevs;
	FARPROC midiOutGetVolume;
	FARPROC midiOutLongMsg;
	FARPROC midiOutMessage;
	FARPROC midiOutOpen;
	FARPROC midiOutPrepareHeader;
	FARPROC midiOutReset;
	FARPROC midiOutSetVolume;
	FARPROC midiOutShortMsg;
	FARPROC midiOutUnprepareHeader;
	FARPROC midiStreamClose;
	FARPROC midiStreamOpen;
	FARPROC midiStreamOut;
	FARPROC midiStreamPause;
	FARPROC midiStreamPosition;
	FARPROC midiStreamProperty;
	FARPROC midiStreamRestart;
	FARPROC midiStreamStop;
	FARPROC mixerClose;
	FARPROC mixerGetControlDetailsA;
	FARPROC mixerGetControlDetailsW;
	FARPROC mixerGetDevCapsA;
	FARPROC mixerGetDevCapsW;
	FARPROC mixerGetID;
	FARPROC mixerGetLineControlsA;
	FARPROC mixerGetLineControlsW;
	FARPROC mixerGetLineInfoA;
	FARPROC mixerGetLineInfoW;
	FARPROC mixerGetNumDevs;
	FARPROC mixerMessage;
	FARPROC mixerOpen;
	FARPROC mixerSetControlDetails;
	FARPROC mmDrvInstall;
	FARPROC mmGetCurrentTask;
	FARPROC mmTaskBlock;
	FARPROC mmTaskCreate;
	FARPROC mmTaskSignal;
	FARPROC mmTaskYield;
	FARPROC mmioAdvance;
	FARPROC mmioAscend;
	FARPROC mmioClose;
	FARPROC mmioCreateChunk;
	FARPROC mmioDescend;
	FARPROC mmioFlush;
	FARPROC mmioGetInfo;
	FARPROC mmioInstallIOProcA;
	FARPROC mmioInstallIOProcW;
	FARPROC mmioOpenA;
	FARPROC mmioOpenW;
	FARPROC mmioRead;
	FARPROC mmioRenameA;
	FARPROC mmioRenameW;
	FARPROC mmioSeek;
	FARPROC mmioSendMessage;
	FARPROC mmioSetBuffer;
	FARPROC mmioSetInfo;
	FARPROC mmioStringToFOURCCA;
	FARPROC mmioStringToFOURCCW;
	FARPROC mmioWrite;
	FARPROC sndOpenSound;
	FARPROC waveInAddBuffer;
	FARPROC waveInClose;
	FARPROC waveInGetDevCapsA;
	FARPROC waveInGetDevCapsW;
	FARPROC waveInGetErrorTextA;
	FARPROC waveInGetErrorTextW;
	FARPROC waveInGetID;
	FARPROC waveInGetNumDevs;
	FARPROC waveInGetPosition;
	FARPROC waveInMessage;
	FARPROC waveInOpen;
	FARPROC waveInPrepareHeader;
	FARPROC waveInReset;
	FARPROC waveInStart;
	FARPROC waveInStop;
	FARPROC waveInUnprepareHeader;
	FARPROC waveOutBreakLoop;
	FARPROC waveOutClose;
	FARPROC waveOutGetDevCapsA;
	FARPROC waveOutGetDevCapsW;
	FARPROC waveOutGetErrorTextA;
	FARPROC waveOutGetErrorTextW;
	FARPROC waveOutGetID;
	FARPROC waveOutGetNumDevs;
	FARPROC waveOutGetPitch;
	FARPROC waveOutGetPlaybackRate;
	FARPROC waveOutGetPosition;
	FARPROC waveOutGetVolume;
	FARPROC waveOutMessage;
	FARPROC waveOutOpen;
	FARPROC waveOutPause;
	FARPROC waveOutPrepareHeader;
	FARPROC waveOutReset;
	FARPROC waveOutRestart;
	FARPROC waveOutSetPitch;
	FARPROC waveOutSetPlaybackRate;
	FARPROC waveOutSetVolume;
	FARPROC waveOutUnprepareHeader;
	FARPROC waveOutWrite;
	FARPROC winmmbaseFreeMMEHandles;
	FARPROC winmmbaseGetWOWHandle;
	FARPROC winmmbaseHandle32FromHandle16;
	FARPROC winmmbaseSetWOWHandle;
} winmmbase;

struct msacm32_dll
{
	HMODULE dll;
	FARPROC acmDriverAddA;
	FARPROC acmDriverAddW;
	FARPROC acmDriverClose;
	FARPROC acmDriverDetailsA;
	FARPROC acmDriverDetailsW;
	FARPROC acmDriverEnum;
	FARPROC acmDriverID;
	FARPROC acmDriverMessage;
	FARPROC acmDriverOpen;
	FARPROC acmDriverPriority;
	FARPROC acmDriverRemove;
	FARPROC acmFilterChooseA;
	FARPROC acmFilterChooseW;
	FARPROC acmFilterDetailsA;
	FARPROC acmFilterDetailsW;
	FARPROC acmFilterEnumA;
	FARPROC acmFilterEnumW;
	FARPROC acmFilterTagDetailsA;
	FARPROC acmFilterTagDetailsW;
	FARPROC acmFilterTagEnumA;
	FARPROC acmFilterTagEnumW;
	FARPROC acmFormatChooseA;
	FARPROC acmFormatChooseW;
	FARPROC acmFormatDetailsA;
	FARPROC acmFormatDetailsW;
	FARPROC acmFormatEnumA;
	FARPROC acmFormatEnumW;
	FARPROC acmFormatSuggest;
	FARPROC acmFormatTagDetailsA;
	FARPROC acmFormatTagDetailsW;
	FARPROC acmFormatTagEnumA;
	FARPROC acmFormatTagEnumW;
	FARPROC acmGetVersion;
	FARPROC acmMetrics;
	FARPROC acmStreamClose;
	FARPROC acmStreamConvert;
	FARPROC acmStreamMessage;
	FARPROC acmStreamOpen;
	FARPROC acmStreamPrepareHeader;
	FARPROC acmStreamReset;
	FARPROC acmStreamSize;
	FARPROC acmStreamUnprepareHeader;
} msacm32;

struct ole32_dll
{
	HMODULE dll;
	FARPROC exp[484];
} ole32;

//export
__declspec(naked) void _DirectInput8Create() { _asm { jmp[dinput8.DirectInput8Create] } }
__declspec(naked) void _DllCanUnloadNow() { _asm { jmp[dinput8.DllCanUnloadNow] } }
__declspec(naked) void _DllGetClassObject() { _asm { jmp[dinput8.DllGetClassObject] } }
__declspec(naked) void _DllRegisterServer() { _asm { jmp[dinput8.DllRegisterServer] } }
__declspec(naked) void _DllUnregisterServer() { _asm { jmp[dinput8.DllUnregisterServer] } }

__declspec(naked) void _DirectSoundCaptureCreate() { _asm { jmp[dsound.DirectSoundCaptureCreate] } }
__declspec(naked) void _DirectSoundCaptureCreate8() { _asm { jmp[dsound.DirectSoundCaptureCreate8] } }
__declspec(naked) void _DirectSoundCaptureEnumerateA() { _asm { jmp[dsound.DirectSoundCaptureEnumerateA] } }
__declspec(naked) void _DirectSoundCaptureEnumerateW() { _asm { jmp[dsound.DirectSoundCaptureEnumerateW] } }
__declspec(naked) void _DirectSoundCreate() { _asm { jmp[dsound.DirectSoundCreate] } }
__declspec(naked) void _DirectSoundCreate8() { _asm { jmp[dsound.DirectSoundCreate8] } }
__declspec(naked) void _DirectSoundEnumerateA() { _asm { jmp[dsound.DirectSoundEnumerateA] } }
__declspec(naked) void _DirectSoundEnumerateW() { _asm { jmp[dsound.DirectSoundEnumerateW] } }
__declspec(naked) void _DirectSoundFullDuplexCreate() { _asm { jmp[dsound.DirectSoundFullDuplexCreate] } }
__declspec(naked) void _DllCanUnloadNow_dsound() { _asm { jmp[dsound.DllCanUnloadNow_dsound] } }
__declspec(naked) void _DllGetClassObject_dsound() { _asm { jmp[dsound.DllGetClassObject_dsound] } }
__declspec(naked) void _GetDeviceID() { _asm { jmp[dsound.GetDeviceID] } }

__declspec(naked) void FakeAcquireDDThreadLock() { _asm { jmp[ddraw.AcquireDDThreadLock] } }
__declspec(naked) void FakeCheckFullscreen() { _asm { jmp[ddraw.CheckFullscreen] } }
__declspec(naked) void FakeCompleteCreateSysmemSurface() { _asm { jmp[ddraw.CompleteCreateSysmemSurface] } }
__declspec(naked) void FakeD3DParseUnknownCommand() { _asm { jmp[ddraw.D3DParseUnknownCommand] } }
__declspec(naked) void FakeDDGetAttachedSurfaceLcl() { _asm { jmp[ddraw.DDGetAttachedSurfaceLcl] } }
__declspec(naked) void FakeDDInternalLock() { _asm { jmp[ddraw.DDInternalLock] } }
__declspec(naked) void FakeDDInternalUnlock() { _asm { jmp[ddraw.DDInternalUnlock] } }
__declspec(naked) void FakeDSoundHelp() { _asm { jmp[ddraw.DSoundHelp] } }
// HRESULT WINAPI DirectDrawCreate( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
__declspec(naked) void FakeDirectDrawCreate() { _asm { jmp[ddraw.DirectDrawCreate] } }
// HRESULT WINAPI DirectDrawCreateClipper( DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter );
__declspec(naked) void FakeDirectDrawCreateClipper() { _asm { jmp[ddraw.DirectDrawCreateClipper] } }
// HRESULT WINAPI DirectDrawCreateEx( GUID FAR * lpGuid, LPVOID *lplpDD, REFIID iid,IUnknown FAR *pUnkOuter );
__declspec(naked) void FakeDirectDrawCreateEx() { _asm { jmp[ddraw.DirectDrawCreateEx] } }
// HRESULT WINAPI DirectDrawEnumerateA( LPDDENUMCALLBACKA lpCallback, LPVOID lpContext );
__declspec(naked) void FakeDirectDrawEnumerateA() { _asm { jmp[ddraw.DirectDrawEnumerateA] } }
// HRESULT WINAPI DirectDrawEnumerateExA( LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags );
__declspec(naked) void FakeDirectDrawEnumerateExA() { _asm { jmp[ddraw.DirectDrawEnumerateExA] } }
// HRESULT WINAPI DirectDrawEnumerateExW( LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags );
__declspec(naked) void FakeDirectDrawEnumerateExW() { _asm { jmp[ddraw.DirectDrawEnumerateExW] } }
// HRESULT WINAPI DirectDrawEnumerateW( LPDDENUMCALLBACKW lpCallback, LPVOID lpContext );
__declspec(naked) void FakeDirectDrawEnumerateW() { _asm { jmp[ddraw.DirectDrawEnumerateW] } }
__declspec(naked) void FakeDllCanUnloadNow() { _asm { jmp[ddraw.DllCanUnloadNow] } }
__declspec(naked) void FakeDllGetClassObject() { _asm { jmp[ddraw.DllGetClassObject] } }
__declspec(naked) void FakeGetDDSurfaceLocal() { _asm { jmp[ddraw.GetDDSurfaceLocal] } }
__declspec(naked) void FakeGetOLEThunkData() { _asm { jmp[ddraw.GetOLEThunkData] } }
__declspec(naked) void FakeGetSurfaceFromDC() { _asm { jmp[ddraw.GetSurfaceFromDC] } }
__declspec(naked) void FakeRegisterSpecialCase() { _asm { jmp[ddraw.RegisterSpecialCase] } }
__declspec(naked) void FakeReleaseDDThreadLock() { _asm { jmp[ddraw.ReleaseDDThreadLock] } }

__declspec(naked) void _DebugSetMute_d3d8() { _asm { jmp[d3d8.DebugSetMute_d3d8] } }
__declspec(naked) void _Direct3DCreate8() { _asm { jmp[d3d8.Direct3DCreate8] } }
__declspec(naked) void _ValidatePixelShader() { _asm { jmp[d3d8.ValidatePixelShader] } }
__declspec(naked) void _ValidateVertexShader() { _asm { jmp[d3d8.ValidateVertexShader] } }

__declspec(naked) void _D3DPERF_BeginEvent() { _asm { jmp[d3d9.D3DPERF_BeginEvent] } }
__declspec(naked) void _D3DPERF_EndEvent() { _asm { jmp[d3d9.D3DPERF_EndEvent] } }
__declspec(naked) void _D3DPERF_GetStatus() { _asm { jmp[d3d9.D3DPERF_GetStatus] } }
__declspec(naked) void _D3DPERF_QueryRepeatFrame() { _asm { jmp[d3d9.D3DPERF_QueryRepeatFrame] } }
__declspec(naked) void _D3DPERF_SetMarker() { _asm { jmp[d3d9.D3DPERF_SetMarker] } }
__declspec(naked) void _D3DPERF_SetOptions() { _asm { jmp[d3d9.D3DPERF_SetOptions] } }
__declspec(naked) void _D3DPERF_SetRegion() { _asm { jmp[d3d9.D3DPERF_SetRegion] } }
__declspec(naked) void _DebugSetLevel() { _asm { jmp[d3d9.DebugSetLevel] } }
__declspec(naked) void _DebugSetMute() { _asm { jmp[d3d9.DebugSetMute] } }
__declspec(naked) void _Direct3D9EnableMaximizedWindowedModeShim() { _asm { jmp [d3d9.Direct3D9EnableMaximizedWindowedModeShim] } }
__declspec(naked) void _Direct3DCreate9() { _asm { jmp[d3d9.Direct3DCreate9] } }
__declspec(naked) void _Direct3DCreate9Ex() { _asm { jmp[d3d9.Direct3DCreate9Ex] } }
__declspec(naked) void _Direct3DShaderValidatorCreate9() { _asm { jmp[d3d9.Direct3DShaderValidatorCreate9] } }
__declspec(naked) void _PSGPError() { _asm { jmp[d3d9.PSGPError] } }
__declspec(naked) void _PSGPSampleTexture() { _asm { jmp[d3d9.PSGPSampleTexture] } }

__declspec(naked) void _D3D11CoreCreateDevice() { _asm { jmp[d3d11.D3D11CoreCreateDevice] } }
__declspec(naked) void _D3D11CoreCreateLayeredDevice() { _asm { jmp[d3d11.D3D11CoreCreateLayeredDevice] } }
__declspec(naked) void _D3D11CoreGetLayeredDeviceSize() { _asm { jmp[d3d11.D3D11CoreGetLayeredDeviceSize] } }
__declspec(naked) void _D3D11CoreRegisterLayers() { _asm { jmp[d3d11.D3D11CoreRegisterLayers] } }
__declspec(naked) void _D3D11CreateDevice() { _asm { jmp[d3d11.D3D11CreateDevice] } }
__declspec(naked) void _D3D11CreateDeviceAndSwapChain() { _asm { jmp[d3d11.D3D11CreateDeviceAndSwapChain] } }
__declspec(naked) void _D3DKMTCloseAdapter() { _asm { jmp[d3d11.D3DKMTCloseAdapter] } }
__declspec(naked) void _D3DKMTCreateAllocation() { _asm { jmp[d3d11.D3DKMTCreateAllocation] } }
__declspec(naked) void _D3DKMTCreateContext() { _asm { jmp[d3d11.D3DKMTCreateContext] } }
__declspec(naked) void _D3DKMTCreateDevice() { _asm { jmp[d3d11.D3DKMTCreateDevice] } }
__declspec(naked) void _D3DKMTCreateSynchronizationObject() { _asm { jmp[d3d11.D3DKMTCreateSynchronizationObject] } }
__declspec(naked) void _D3DKMTDestroyAllocation() { _asm { jmp[d3d11.D3DKMTDestroyAllocation] } }
__declspec(naked) void _D3DKMTDestroyContext() { _asm { jmp[d3d11.D3DKMTDestroyContext] } }
__declspec(naked) void _D3DKMTDestroyDevice() { _asm { jmp[d3d11.D3DKMTDestroyDevice] } }
__declspec(naked) void _D3DKMTDestroySynchronizationObject() { _asm { jmp[d3d11.D3DKMTDestroySynchronizationObject] } }
__declspec(naked) void _D3DKMTEscape() { _asm { jmp[d3d11.D3DKMTEscape] } }
__declspec(naked) void _D3DKMTGetContextSchedulingPriority() { _asm { jmp[d3d11.D3DKMTGetContextSchedulingPriority] } }
__declspec(naked) void _D3DKMTGetDeviceState() { _asm { jmp[d3d11.D3DKMTGetDeviceState] } }
__declspec(naked) void _D3DKMTGetDisplayModeList() { _asm { jmp[d3d11.D3DKMTGetDisplayModeList] } }
__declspec(naked) void _D3DKMTGetMultisampleMethodList() { _asm { jmp[d3d11.D3DKMTGetMultisampleMethodList] } }
__declspec(naked) void _D3DKMTGetRuntimeData() { _asm { jmp[d3d11.D3DKMTGetRuntimeData] } }
__declspec(naked) void _D3DKMTGetSharedPrimaryHandle() { _asm { jmp[d3d11.D3DKMTGetSharedPrimaryHandle] } }
__declspec(naked) void _D3DKMTLock() { _asm { jmp[d3d11.D3DKMTLock] } }
__declspec(naked) void _D3DKMTOpenAdapterFromHdc() { _asm { jmp[d3d11.D3DKMTOpenAdapterFromHdc] } }
__declspec(naked) void _D3DKMTOpenResource() { _asm { jmp[d3d11.D3DKMTOpenResource] } }
__declspec(naked) void _D3DKMTPresent() { _asm { jmp[d3d11.D3DKMTPresent] } }
__declspec(naked) void _D3DKMTQueryAdapterInfo() { _asm { jmp[d3d11.D3DKMTQueryAdapterInfo] } }
__declspec(naked) void _D3DKMTQueryAllocationResidency() { _asm { jmp[d3d11.D3DKMTQueryAllocationResidency] } }
__declspec(naked) void _D3DKMTQueryResourceInfo() { _asm { jmp[d3d11.D3DKMTQueryResourceInfo] } }
__declspec(naked) void _D3DKMTRender() { _asm { jmp[d3d11.D3DKMTRender] } }
__declspec(naked) void _D3DKMTSetAllocationPriority() { _asm { jmp[d3d11.D3DKMTSetAllocationPriority] } }
__declspec(naked) void _D3DKMTSetContextSchedulingPriority() { _asm { jmp[d3d11.D3DKMTSetContextSchedulingPriority] } }
__declspec(naked) void _D3DKMTSetDisplayMode() { _asm { jmp[d3d11.D3DKMTSetDisplayMode] } }
__declspec(naked) void _D3DKMTSetDisplayPrivateDriverFormat() { _asm { jmp[d3d11.D3DKMTSetDisplayPrivateDriverFormat] } }
__declspec(naked) void _D3DKMTSetGammaRamp() { _asm { jmp[d3d11.D3DKMTSetGammaRamp] } }
__declspec(naked) void _D3DKMTSetVidPnSourceOwner() { _asm { jmp[d3d11.D3DKMTSetVidPnSourceOwner] } }
__declspec(naked) void _D3DKMTSignalSynchronizationObject() { _asm { jmp[d3d11.D3DKMTSignalSynchronizationObject] } }
__declspec(naked) void _D3DKMTUnlock() { _asm { jmp[d3d11.D3DKMTUnlock] } }
__declspec(naked) void _D3DKMTWaitForSynchronizationObject() { _asm { jmp[d3d11.D3DKMTWaitForSynchronizationObject] } }
__declspec(naked) void _D3DKMTWaitForVerticalBlankEvent() { _asm { jmp[d3d11.D3DKMTWaitForVerticalBlankEvent] } }
__declspec(naked) void _D3DPerformance_BeginEvent() { _asm { jmp[d3d11.D3DPerformance_BeginEvent] } }
__declspec(naked) void _D3DPerformance_EndEvent() { _asm { jmp[d3d11.D3DPerformance_EndEvent] } }
__declspec(naked) void _D3DPerformance_GetStatus() { _asm { jmp[d3d11.D3DPerformance_GetStatus] } }
__declspec(naked) void _D3DPerformance_SetMarker() { _asm { jmp[d3d11.D3DPerformance_SetMarker] } }
__declspec(naked) void _EnableFeatureLevelUpgrade() { _asm { jmp[d3d11.EnableFeatureLevelUpgrade] } }
__declspec(naked) void _OpenAdapter10() { _asm { jmp[d3d11.OpenAdapter10] } }
__declspec(naked) void _OpenAdapter10_2() { _asm { jmp[d3d11.OpenAdapter10_2] } }

__declspec(naked) void _CloseDriver() { _asm { jmp[winmmbase.CloseDriver] } }
__declspec(naked) void _DefDriverProc() { _asm { jmp[winmmbase.DefDriverProc] } }
__declspec(naked) void _DriverCallback() { _asm { jmp[winmmbase.DriverCallback] } }
__declspec(naked) void _DrvGetModuleHandle() { _asm { jmp[winmmbase.DrvGetModuleHandle] } }
__declspec(naked) void _GetDriverModuleHandle() { _asm { jmp[winmmbase.GetDriverModuleHandle] } }
__declspec(naked) void _OpenDriver() { _asm { jmp[winmmbase.OpenDriver] } }
__declspec(naked) void _SendDriverMessage() { _asm { jmp[winmmbase.SendDriverMessage] } }
__declspec(naked) void _auxGetDevCapsA() { _asm { jmp[winmmbase.auxGetDevCapsA] } }
__declspec(naked) void _auxGetDevCapsW() { _asm { jmp[winmmbase.auxGetDevCapsW] } }
__declspec(naked) void _auxGetNumDevs() { _asm { jmp[winmmbase.auxGetNumDevs] } }
__declspec(naked) void _auxGetVolume() { _asm { jmp[winmmbase.auxGetVolume] } }
__declspec(naked) void _auxOutMessage() { _asm { jmp[winmmbase.auxOutMessage] } }
__declspec(naked) void _auxSetVolume() { _asm { jmp[winmmbase.auxSetVolume] } }
__declspec(naked) void _joyConfigChanged() { _asm { jmp[winmmbase.joyConfigChanged] } }
__declspec(naked) void _joyGetDevCapsA() { _asm { jmp[winmmbase.joyGetDevCapsA] } }
__declspec(naked) void _joyGetDevCapsW() { _asm { jmp[winmmbase.joyGetDevCapsW] } }
__declspec(naked) void _joyGetNumDevs() { _asm { jmp[winmmbase.joyGetNumDevs] } }
__declspec(naked) void _joyGetPos() { _asm { jmp[winmmbase.joyGetPos] } }
__declspec(naked) void _joyGetPosEx() { _asm { jmp[winmmbase.joyGetPosEx] } }
__declspec(naked) void _joyGetThreshold() { _asm { jmp[winmmbase.joyGetThreshold] } }
__declspec(naked) void _joyReleaseCapture() { _asm { jmp[winmmbase.joyReleaseCapture] } }
__declspec(naked) void _joySetCapture() { _asm { jmp[winmmbase.joySetCapture] } }
__declspec(naked) void _joySetThreshold() { _asm { jmp[winmmbase.joySetThreshold] } }
__declspec(naked) void _midiConnect() { _asm { jmp[winmmbase.midiConnect] } }
__declspec(naked) void _midiDisconnect() { _asm { jmp[winmmbase.midiDisconnect] } }
__declspec(naked) void _midiInAddBuffer() { _asm { jmp[winmmbase.midiInAddBuffer] } }
__declspec(naked) void _midiInClose() { _asm { jmp[winmmbase.midiInClose] } }
__declspec(naked) void _midiInGetDevCapsA() { _asm { jmp[winmmbase.midiInGetDevCapsA] } }
__declspec(naked) void _midiInGetDevCapsW() { _asm { jmp[winmmbase.midiInGetDevCapsW] } }
__declspec(naked) void _midiInGetErrorTextA() { _asm { jmp[winmmbase.midiInGetErrorTextA] } }
__declspec(naked) void _midiInGetErrorTextW() { _asm { jmp[winmmbase.midiInGetErrorTextW] } }
__declspec(naked) void _midiInGetID() { _asm { jmp[winmmbase.midiInGetID] } }
__declspec(naked) void _midiInGetNumDevs() { _asm { jmp[winmmbase.midiInGetNumDevs] } }
__declspec(naked) void _midiInMessage() { _asm { jmp[winmmbase.midiInMessage] } }
__declspec(naked) void _midiInOpen() { _asm { jmp[winmmbase.midiInOpen] } }
__declspec(naked) void _midiInPrepareHeader() { _asm { jmp[winmmbase.midiInPrepareHeader] } }
__declspec(naked) void _midiInReset() { _asm { jmp[winmmbase.midiInReset] } }
__declspec(naked) void _midiInStart() { _asm { jmp[winmmbase.midiInStart] } }
__declspec(naked) void _midiInStop() { _asm { jmp[winmmbase.midiInStop] } }
__declspec(naked) void _midiInUnprepareHeader() { _asm { jmp[winmmbase.midiInUnprepareHeader] } }
__declspec(naked) void _midiOutCacheDrumPatches() { _asm { jmp[winmmbase.midiOutCacheDrumPatches] } }
__declspec(naked) void _midiOutCachePatches() { _asm { jmp[winmmbase.midiOutCachePatches] } }
__declspec(naked) void _midiOutClose() { _asm { jmp[winmmbase.midiOutClose] } }
__declspec(naked) void _midiOutGetDevCapsA() { _asm { jmp[winmmbase.midiOutGetDevCapsA] } }
__declspec(naked) void _midiOutGetDevCapsW() { _asm { jmp[winmmbase.midiOutGetDevCapsW] } }
__declspec(naked) void _midiOutGetErrorTextA() { _asm { jmp[winmmbase.midiOutGetErrorTextA] } }
__declspec(naked) void _midiOutGetErrorTextW() { _asm { jmp[winmmbase.midiOutGetErrorTextW] } }
__declspec(naked) void _midiOutGetID() { _asm { jmp[winmmbase.midiOutGetID] } }
__declspec(naked) void _midiOutGetNumDevs() { _asm { jmp[winmmbase.midiOutGetNumDevs] } }
__declspec(naked) void _midiOutGetVolume() { _asm { jmp[winmmbase.midiOutGetVolume] } }
__declspec(naked) void _midiOutLongMsg() { _asm { jmp[winmmbase.midiOutLongMsg] } }
__declspec(naked) void _midiOutMessage() { _asm { jmp[winmmbase.midiOutMessage] } }
__declspec(naked) void _midiOutOpen() { _asm { jmp[winmmbase.midiOutOpen] } }
__declspec(naked) void _midiOutPrepareHeader() { _asm { jmp[winmmbase.midiOutPrepareHeader] } }
__declspec(naked) void _midiOutReset() { _asm { jmp[winmmbase.midiOutReset] } }
__declspec(naked) void _midiOutSetVolume() { _asm { jmp[winmmbase.midiOutSetVolume] } }
__declspec(naked) void _midiOutShortMsg() { _asm { jmp[winmmbase.midiOutShortMsg] } }
__declspec(naked) void _midiOutUnprepareHeader() { _asm { jmp[winmmbase.midiOutUnprepareHeader] } }
__declspec(naked) void _midiStreamClose() { _asm { jmp[winmmbase.midiStreamClose] } }
__declspec(naked) void _midiStreamOpen() { _asm { jmp[winmmbase.midiStreamOpen] } }
__declspec(naked) void _midiStreamOut() { _asm { jmp[winmmbase.midiStreamOut] } }
__declspec(naked) void _midiStreamPause() { _asm { jmp[winmmbase.midiStreamPause] } }
__declspec(naked) void _midiStreamPosition() { _asm { jmp[winmmbase.midiStreamPosition] } }
__declspec(naked) void _midiStreamProperty() { _asm { jmp[winmmbase.midiStreamProperty] } }
__declspec(naked) void _midiStreamRestart() { _asm { jmp[winmmbase.midiStreamRestart] } }
__declspec(naked) void _midiStreamStop() { _asm { jmp[winmmbase.midiStreamStop] } }
__declspec(naked) void _mixerClose() { _asm { jmp[winmmbase.mixerClose] } }
__declspec(naked) void _mixerGetControlDetailsA() { _asm { jmp[winmmbase.mixerGetControlDetailsA] } }
__declspec(naked) void _mixerGetControlDetailsW() { _asm { jmp[winmmbase.mixerGetControlDetailsW] } }
__declspec(naked) void _mixerGetDevCapsA() { _asm { jmp[winmmbase.mixerGetDevCapsA] } }
__declspec(naked) void _mixerGetDevCapsW() { _asm { jmp[winmmbase.mixerGetDevCapsW] } }
__declspec(naked) void _mixerGetID() { _asm { jmp[winmmbase.mixerGetID] } }
__declspec(naked) void _mixerGetLineControlsA() { _asm { jmp[winmmbase.mixerGetLineControlsA] } }
__declspec(naked) void _mixerGetLineControlsW() { _asm { jmp[winmmbase.mixerGetLineControlsW] } }
__declspec(naked) void _mixerGetLineInfoA() { _asm { jmp[winmmbase.mixerGetLineInfoA] } }
__declspec(naked) void _mixerGetLineInfoW() { _asm { jmp[winmmbase.mixerGetLineInfoW] } }
__declspec(naked) void _mixerGetNumDevs() { _asm { jmp[winmmbase.mixerGetNumDevs] } }
__declspec(naked) void _mixerMessage() { _asm { jmp[winmmbase.mixerMessage] } }
__declspec(naked) void _mixerOpen() { _asm { jmp[winmmbase.mixerOpen] } }
__declspec(naked) void _mixerSetControlDetails() { _asm { jmp[winmmbase.mixerSetControlDetails] } }
__declspec(naked) void _mmDrvInstall() { _asm { jmp[winmmbase.mmDrvInstall] } }
__declspec(naked) void _mmGetCurrentTask() { _asm { jmp[winmmbase.mmGetCurrentTask] } }
__declspec(naked) void _mmTaskBlock() { _asm { jmp[winmmbase.mmTaskBlock] } }
__declspec(naked) void _mmTaskCreate() { _asm { jmp[winmmbase.mmTaskCreate] } }
__declspec(naked) void _mmTaskSignal() { _asm { jmp[winmmbase.mmTaskSignal] } }
__declspec(naked) void _mmTaskYield() { _asm { jmp[winmmbase.mmTaskYield] } }
__declspec(naked) void _mmioAdvance() { _asm { jmp[winmmbase.mmioAdvance] } }
__declspec(naked) void _mmioAscend() { _asm { jmp[winmmbase.mmioAscend] } }
__declspec(naked) void _mmioClose() { _asm { jmp[winmmbase.mmioClose] } }
__declspec(naked) void _mmioCreateChunk() { _asm { jmp[winmmbase.mmioCreateChunk] } }
__declspec(naked) void _mmioDescend() { _asm { jmp[winmmbase.mmioDescend] } }
__declspec(naked) void _mmioFlush() { _asm { jmp[winmmbase.mmioFlush] } }
__declspec(naked) void _mmioGetInfo() { _asm { jmp[winmmbase.mmioGetInfo] } }
__declspec(naked) void _mmioInstallIOProcA() { _asm { jmp[winmmbase.mmioInstallIOProcA] } }
__declspec(naked) void _mmioInstallIOProcW() { _asm { jmp[winmmbase.mmioInstallIOProcW] } }
__declspec(naked) void _mmioOpenA() { _asm { jmp[winmmbase.mmioOpenA] } }
__declspec(naked) void _mmioOpenW() { _asm { jmp[winmmbase.mmioOpenW] } }
__declspec(naked) void _mmioRead() { _asm { jmp[winmmbase.mmioRead] } }
__declspec(naked) void _mmioRenameA() { _asm { jmp[winmmbase.mmioRenameA] } }
__declspec(naked) void _mmioRenameW() { _asm { jmp[winmmbase.mmioRenameW] } }
__declspec(naked) void _mmioSeek() { _asm { jmp[winmmbase.mmioSeek] } }
__declspec(naked) void _mmioSendMessage() { _asm { jmp[winmmbase.mmioSendMessage] } }
__declspec(naked) void _mmioSetBuffer() { _asm { jmp[winmmbase.mmioSetBuffer] } }
__declspec(naked) void _mmioSetInfo() { _asm { jmp[winmmbase.mmioSetInfo] } }
__declspec(naked) void _mmioStringToFOURCCA() { _asm { jmp[winmmbase.mmioStringToFOURCCA] } }
__declspec(naked) void _mmioStringToFOURCCW() { _asm { jmp[winmmbase.mmioStringToFOURCCW] } }
__declspec(naked) void _mmioWrite() { _asm { jmp[winmmbase.mmioWrite] } }
__declspec(naked) void _sndOpenSound() { _asm { jmp[winmmbase.sndOpenSound] } }
__declspec(naked) void _waveInAddBuffer() { _asm { jmp[winmmbase.waveInAddBuffer] } }
__declspec(naked) void _waveInClose() { _asm { jmp[winmmbase.waveInClose] } }
__declspec(naked) void _waveInGetDevCapsA() { _asm { jmp[winmmbase.waveInGetDevCapsA] } }
__declspec(naked) void _waveInGetDevCapsW() { _asm { jmp[winmmbase.waveInGetDevCapsW] } }
__declspec(naked) void _waveInGetErrorTextA() { _asm { jmp[winmmbase.waveInGetErrorTextA] } }
__declspec(naked) void _waveInGetErrorTextW() { _asm { jmp[winmmbase.waveInGetErrorTextW] } }
__declspec(naked) void _waveInGetID() { _asm { jmp[winmmbase.waveInGetID] } }
__declspec(naked) void _waveInGetNumDevs() { _asm { jmp[winmmbase.waveInGetNumDevs] } }
__declspec(naked) void _waveInGetPosition() { _asm { jmp[winmmbase.waveInGetPosition] } }
__declspec(naked) void _waveInMessage() { _asm { jmp[winmmbase.waveInMessage] } }
__declspec(naked) void _waveInOpen() { _asm { jmp[winmmbase.waveInOpen] } }
__declspec(naked) void _waveInPrepareHeader() { _asm { jmp[winmmbase.waveInPrepareHeader] } }
__declspec(naked) void _waveInReset() { _asm { jmp[winmmbase.waveInReset] } }
__declspec(naked) void _waveInStart() { _asm { jmp[winmmbase.waveInStart] } }
__declspec(naked) void _waveInStop() { _asm { jmp[winmmbase.waveInStop] } }
__declspec(naked) void _waveInUnprepareHeader() { _asm { jmp[winmmbase.waveInUnprepareHeader] } }
__declspec(naked) void _waveOutBreakLoop() { _asm { jmp[winmmbase.waveOutBreakLoop] } }
__declspec(naked) void _waveOutClose() { _asm { jmp[winmmbase.waveOutClose] } }
__declspec(naked) void _waveOutGetDevCapsA() { _asm { jmp[winmmbase.waveOutGetDevCapsA] } }
__declspec(naked) void _waveOutGetDevCapsW() { _asm { jmp[winmmbase.waveOutGetDevCapsW] } }
__declspec(naked) void _waveOutGetErrorTextA() { _asm { jmp[winmmbase.waveOutGetErrorTextA] } }
__declspec(naked) void _waveOutGetErrorTextW() { _asm { jmp[winmmbase.waveOutGetErrorTextW] } }
__declspec(naked) void _waveOutGetID() { _asm { jmp[winmmbase.waveOutGetID] } }
__declspec(naked) void _waveOutGetNumDevs() { _asm { jmp[winmmbase.waveOutGetNumDevs] } }
__declspec(naked) void _waveOutGetPitch() { _asm { jmp[winmmbase.waveOutGetPitch] } }
__declspec(naked) void _waveOutGetPlaybackRate() { _asm { jmp[winmmbase.waveOutGetPlaybackRate] } }
__declspec(naked) void _waveOutGetPosition() { _asm { jmp[winmmbase.waveOutGetPosition] } }
__declspec(naked) void _waveOutGetVolume() { _asm { jmp[winmmbase.waveOutGetVolume] } }
__declspec(naked) void _waveOutMessage() { _asm { jmp[winmmbase.waveOutMessage] } }
__declspec(naked) void _waveOutOpen() { _asm { jmp[winmmbase.waveOutOpen] } }
__declspec(naked) void _waveOutPause() { _asm { jmp[winmmbase.waveOutPause] } }
__declspec(naked) void _waveOutPrepareHeader() { _asm { jmp[winmmbase.waveOutPrepareHeader] } }
__declspec(naked) void _waveOutReset() { _asm { jmp[winmmbase.waveOutReset] } }
__declspec(naked) void _waveOutRestart() { _asm { jmp[winmmbase.waveOutRestart] } }
__declspec(naked) void _waveOutSetPitch() { _asm { jmp[winmmbase.waveOutSetPitch] } }
__declspec(naked) void _waveOutSetPlaybackRate() { _asm { jmp[winmmbase.waveOutSetPlaybackRate] } }
__declspec(naked) void _waveOutSetVolume() { _asm { jmp[winmmbase.waveOutSetVolume] } }
__declspec(naked) void _waveOutUnprepareHeader() { _asm { jmp[winmmbase.waveOutUnprepareHeader] } }
__declspec(naked) void _waveOutWrite() { _asm { jmp[winmmbase.waveOutWrite] } }
__declspec(naked) void _winmmbaseFreeMMEHandles() { _asm { jmp[winmmbase.winmmbaseFreeMMEHandles] } }
__declspec(naked) void _winmmbaseGetWOWHandle() { _asm { jmp[winmmbase.winmmbaseGetWOWHandle] } }
__declspec(naked) void _winmmbaseHandle32FromHandle16() { _asm { jmp[winmmbase.winmmbaseHandle32FromHandle16] } }
__declspec(naked) void _winmmbaseSetWOWHandle() { _asm { jmp[winmmbase.winmmbaseSetWOWHandle] } }

__declspec(naked) void _acmDriverAddA() { _asm { jmp[msacm32.acmDriverAddA] } }
__declspec(naked) void _acmDriverAddW() { _asm { jmp[msacm32.acmDriverAddW] } }
__declspec(naked) void _acmDriverClose() { _asm { jmp[msacm32.acmDriverClose] } }
__declspec(naked) void _acmDriverDetailsA() { _asm { jmp[msacm32.acmDriverDetailsA] } }
__declspec(naked) void _acmDriverDetailsW() { _asm { jmp[msacm32.acmDriverDetailsW] } }
__declspec(naked) void _acmDriverEnum() { _asm { jmp[msacm32.acmDriverEnum] } }
__declspec(naked) void _acmDriverID() { _asm { jmp[msacm32.acmDriverID] } }
__declspec(naked) void _acmDriverMessage() { _asm { jmp[msacm32.acmDriverMessage] } }
__declspec(naked) void _acmDriverOpen() { _asm { jmp[msacm32.acmDriverOpen] } }
__declspec(naked) void _acmDriverPriority() { _asm { jmp[msacm32.acmDriverPriority] } }
__declspec(naked) void _acmDriverRemove() { _asm { jmp[msacm32.acmDriverRemove] } }
__declspec(naked) void _acmFilterChooseA() { _asm { jmp[msacm32.acmFilterChooseA] } }
__declspec(naked) void _acmFilterChooseW() { _asm { jmp[msacm32.acmFilterChooseW] } }
__declspec(naked) void _acmFilterDetailsA() { _asm { jmp[msacm32.acmFilterDetailsA] } }
__declspec(naked) void _acmFilterDetailsW() { _asm { jmp[msacm32.acmFilterDetailsW] } }
__declspec(naked) void _acmFilterEnumA() { _asm { jmp[msacm32.acmFilterEnumA] } }
__declspec(naked) void _acmFilterEnumW() { _asm { jmp[msacm32.acmFilterEnumW] } }
__declspec(naked) void _acmFilterTagDetailsA() { _asm { jmp[msacm32.acmFilterTagDetailsA] } }
__declspec(naked) void _acmFilterTagDetailsW() { _asm { jmp[msacm32.acmFilterTagDetailsW] } }
__declspec(naked) void _acmFilterTagEnumA() { _asm { jmp[msacm32.acmFilterTagEnumA] } }
__declspec(naked) void _acmFilterTagEnumW() { _asm { jmp[msacm32.acmFilterTagEnumW] } }
__declspec(naked) void _acmFormatChooseA() { _asm { jmp[msacm32.acmFormatChooseA] } }
__declspec(naked) void _acmFormatChooseW() { _asm { jmp[msacm32.acmFormatChooseW] } }
__declspec(naked) void _acmFormatDetailsA() { _asm { jmp[msacm32.acmFormatDetailsA] } }
__declspec(naked) void _acmFormatDetailsW() { _asm { jmp[msacm32.acmFormatDetailsW] } }
__declspec(naked) void _acmFormatEnumA() { _asm { jmp[msacm32.acmFormatEnumA] } }
__declspec(naked) void _acmFormatEnumW() { _asm { jmp[msacm32.acmFormatEnumW] } }
__declspec(naked) void _acmFormatSuggest() { _asm { jmp[msacm32.acmFormatSuggest] } }
__declspec(naked) void _acmFormatTagDetailsA() { _asm { jmp[msacm32.acmFormatTagDetailsA] } }
__declspec(naked) void _acmFormatTagDetailsW() { _asm { jmp[msacm32.acmFormatTagDetailsW] } }
__declspec(naked) void _acmFormatTagEnumA() { _asm { jmp[msacm32.acmFormatTagEnumA] } }
__declspec(naked) void _acmFormatTagEnumW() { _asm { jmp[msacm32.acmFormatTagEnumW] } }
__declspec(naked) void _acmGetVersion() { _asm { jmp[msacm32.acmGetVersion] } }
__declspec(naked) void _acmMetrics() { _asm { jmp[msacm32.acmMetrics] } }
__declspec(naked) void _acmStreamClose() { _asm { jmp[msacm32.acmStreamClose] } }
__declspec(naked) void _acmStreamConvert() { _asm { jmp[msacm32.acmStreamConvert] } }
__declspec(naked) void _acmStreamMessage() { _asm { jmp[msacm32.acmStreamMessage] } }
__declspec(naked) void _acmStreamOpen() { _asm { jmp[msacm32.acmStreamOpen] } }
__declspec(naked) void _acmStreamPrepareHeader() { _asm { jmp[msacm32.acmStreamPrepareHeader] } }
__declspec(naked) void _acmStreamReset() { _asm { jmp[msacm32.acmStreamReset] } }
__declspec(naked) void _acmStreamSize() { _asm { jmp[msacm32.acmStreamSize] } }
__declspec(naked) void _acmStreamUnprepareHeader() { _asm { jmp[msacm32.acmStreamUnprepareHeader] } }

__declspec(naked) void Proxy_CreateFileMoniker() { __asm { jmp ole32.exp[0 * 4]} }
__declspec(naked) void Proxy_DestroyRunningObjectTable() { __asm { jmp ole32.exp[1 * 4]} }
__declspec(naked) void Proxy_Ordinal800() { __asm { jmp ole32.exp[2 * 4]} }
__declspec(naked) void Proxy_OleFlushClipboard() { __asm { jmp ole32.exp[3 * 4]} }
__declspec(naked) void Proxy_OleSetClipboard() { __asm { jmp ole32.exp[4 * 4]} }
__declspec(naked) void Proxy_OleQueryLinkFromData() { __asm { jmp ole32.exp[5 * 4]} }
__declspec(naked) void Proxy_OleGetClipboard() { __asm { jmp ole32.exp[6 * 4]} }
__declspec(naked) void Proxy_OleIsCurrentClipboard() { __asm { jmp ole32.exp[7 * 4]} }
__declspec(naked) void Proxy_OleCreateFontIndirectExt() { __asm { jmp ole32.exp[8 * 4]} }
__declspec(naked) void Proxy_ReadFmtUserTypeStg() { __asm { jmp ole32.exp[9 * 4]} }
__declspec(naked) void Proxy_WriteFmtUserTypeStg() { __asm { jmp ole32.exp[10 * 4]} }
__declspec(naked) void Proxy_WriteStringStream() { __asm { jmp ole32.exp[11 * 4]} }
__declspec(naked) void Proxy_RegisterActiveObjectExt() { __asm { jmp ole32.exp[12 * 4]} }
__declspec(naked) void Proxy_GetActiveObjectExt() { __asm { jmp ole32.exp[13 * 4]} }
__declspec(naked) void Proxy_CoAllowSetForegroundWindow() { __asm { jmp ole32.exp[14 * 4]} }
__declspec(naked) void Proxy_OleRun() { __asm { jmp ole32.exp[15 * 4]} }
__declspec(naked) void Proxy_CreateClassMoniker() { __asm { jmp ole32.exp[16 * 4]} }
__declspec(naked) void Proxy_OleSave() { __asm { jmp ole32.exp[17 * 4]} }
__declspec(naked) void Proxy_RevokeActiveObjectExt() { __asm { jmp ole32.exp[18 * 4]} }
__declspec(naked) void Proxy_StgCreateStorageEx() { __asm { jmp ole32.exp[19 * 4]} }
__declspec(naked) void Proxy_StgCreateDocfileOnILockBytes() { __asm { jmp ole32.exp[20 * 4]} }
__declspec(naked) void Proxy_StgIsStorageFile() { __asm { jmp ole32.exp[21 * 4]} }
__declspec(naked) void Proxy_StgOpenStorageEx() { __asm { jmp ole32.exp[22 * 4]} }
__declspec(naked) void Proxy_StgOpenStorageOnILockBytes() { __asm { jmp ole32.exp[23 * 4]} }
__declspec(naked) void Proxy_WriteClassStg() { __asm { jmp ole32.exp[24 * 4]} }
__declspec(naked) void Proxy_StgCreateDocfile() { __asm { jmp ole32.exp[25 * 4]} }
__declspec(naked) void Proxy_CoBuildVersion() { __asm { jmp ole32.exp[26 * 4]} }
__declspec(naked) void Proxy_OleBuildVersion() { __asm { jmp ole32.exp[27 * 4]} }
__declspec(naked) void Proxy_Ordinal801() { __asm { jmp ole32.exp[28 * 4]} }
__declspec(naked) void Proxy_Ordinal803() { __asm { jmp ole32.exp[29 * 4]} }
__declspec(naked) void Proxy_CreateItemMoniker() { __asm { jmp ole32.exp[30 * 4]} }
__declspec(naked) void Proxy_RevokeDragDrop() { __asm { jmp ole32.exp[31 * 4]} }
__declspec(naked) void Proxy_CreateDataAdviseHolder() { __asm { jmp ole32.exp[32 * 4]} }
__declspec(naked) void Proxy_OleUninitialize() { __asm { jmp ole32.exp[33 * 4]} }
__declspec(naked) void Proxy_RegisterDragDrop() { __asm { jmp ole32.exp[34 * 4]} }
__declspec(naked) void Proxy_CheckInitDde() { __asm { jmp ole32.exp[35 * 4]} }
__declspec(naked) void Proxy_ClipboardProcessUninitialize() { __asm { jmp ole32.exp[36 * 4]} }
__declspec(naked) void Proxy_OleInitialize() { __asm { jmp ole32.exp[37 * 4]} }
__declspec(naked) void Proxy_CleanROTForApartment() { __asm { jmp ole32.exp[38 * 4]} }
__declspec(naked) void Proxy_CoGetObject() { __asm { jmp ole32.exp[39 * 4]} }
__declspec(naked) void Proxy_Ole32DllGetClassObject() { __asm { jmp ole32.exp[40 * 4]} }
__declspec(naked) void Proxy_DllGetClassObject() { __asm { jmp ole32.exp[41 * 4]} }
__declspec(naked) void Proxy_DllGetClassObjectWOW() { __asm { jmp ole32.exp[42 * 4]} }
__declspec(naked) void Proxy_CreateGenericComposite() { __asm { jmp ole32.exp[43 * 4]} }
__declspec(naked) void Proxy_MkParseDisplayName() { __asm { jmp ole32.exp[44 * 4]} }
__declspec(naked) void Proxy_IsEqualGUID() { __asm { jmp ole32.exp[45 * 4]} }
__declspec(naked) void Proxy_CoGetInterceptorForOle32() { __asm { jmp ole32.exp[46 * 4]} }
__declspec(naked) void Proxy_CreateBindCtx() { __asm { jmp ole32.exp[47 * 4]} }
__declspec(naked) void Proxy_IsValidInterface() { __asm { jmp ole32.exp[48 * 4]} }
__declspec(naked) void Proxy_GetRunningObjectTable() { __asm { jmp ole32.exp[49 * 4]} }
__declspec(naked) void Proxy_ReleaseStgMedium() { __asm { jmp ole32.exp[50 * 4]} }
__declspec(naked) void Proxy_OleRegGetMiscStatus() { __asm { jmp ole32.exp[51 * 4]} }
__declspec(naked) void Proxy_CoInitialize() { __asm { jmp ole32.exp[52 * 4]} }
__declspec(naked) void Proxy_StgOpenStorage() { __asm { jmp ole32.exp[53 * 4]} }
__declspec(naked) void Proxy_OleTranslateColorExt() { __asm { jmp ole32.exp[54 * 4]} }
__declspec(naked) void Proxy_SetOleautModule() { __asm { jmp ole32.exp[55 * 4]} }
__declspec(naked) void Proxy_OleReleaseEnumVerbCache() { __asm { jmp ole32.exp[56 * 4]} }
__declspec(naked) void Proxy_CreatePointerMoniker() { __asm { jmp ole32.exp[57 * 4]} }
__declspec(naked) void Proxy_BindMoniker() { __asm { jmp ole32.exp[58 * 4]} }
__declspec(naked) void Proxy_StoreQITableEntry() { __asm { jmp ole32.exp[59 * 4]} }
__declspec(naked) void Proxy_OleSaveToStream() { __asm { jmp ole32.exp[60 * 4]} }
__declspec(naked) void Proxy_ClearQITableEntry() { __asm { jmp ole32.exp[61 * 4]} }
__declspec(naked) void Proxy_ComPs_NdrDllCanUnloadNow() { __asm { jmp ole32.exp[62 * 4]} }
__declspec(naked) void Proxy_IsValidIid() { __asm { jmp ole32.exp[63 * 4]} }
__declspec(naked) void Proxy_CoSetState() { __asm { jmp ole32.exp[64 * 4]} }
__declspec(naked) void Proxy_HWND_UserFreeExt() { __asm { jmp ole32.exp[65 * 4]} }
__declspec(naked) void Proxy_CoFreeAllLibraries() { __asm { jmp ole32.exp[66 * 4]} }
__declspec(naked) void Proxy_CreateStdProgressIndicator() { __asm { jmp ole32.exp[67 * 4]} }
__declspec(naked) void Proxy_CoGetInterceptorFromTypeInfo() { __asm { jmp ole32.exp[68 * 4]} }
__declspec(naked) void Proxy_OleLockRunning() { __asm { jmp ole32.exp[69 * 4]} }
__declspec(naked) void Proxy_CreateOleAdviseHolder() { __asm { jmp ole32.exp[70 * 4]} }
__declspec(naked) void Proxy_ReadClassStm() { __asm { jmp ole32.exp[71 * 4]} }
__declspec(naked) void Proxy_FreePropVariantArray() { __asm { jmp ole32.exp[72 * 4]} }
__declspec(naked) void Proxy_PropVariantClear() { __asm { jmp ole32.exp[73 * 4]} }
__declspec(naked) void Proxy_PropVariantCopy() { __asm { jmp ole32.exp[74 * 4]} }
__declspec(naked) void Proxy_CoInitializeWOW() { __asm { jmp ole32.exp[75 * 4]} }
__declspec(naked) void Proxy_CoRegisterMessageFilter() { __asm { jmp ole32.exp[76 * 4]} }
__declspec(naked) void Proxy_CoRegisterSurrogateEx() { __asm { jmp ole32.exp[77 * 4]} }
__declspec(naked) void Proxy_CoUnloadingWOW() { __asm { jmp ole32.exp[78 * 4]} }
__declspec(naked) void Proxy_DllRegisterServer() { __asm { jmp ole32.exp[79 * 4]} }
__declspec(naked) void Proxy_CoAicGetTokenForCOM() { __asm { jmp ole32.exp[80 * 4]} }
__declspec(naked) void Proxy_CoCheckElevationEnabled() { __asm { jmp ole32.exp[81 * 4]} }
__declspec(naked) void Proxy_CoGetSystemWow64DirectoryW() { __asm { jmp ole32.exp[82 * 4]} }
__declspec(naked) void Proxy_DeletePatternAndExtensionTables() { __asm { jmp ole32.exp[83 * 4]} }
__declspec(naked) void Proxy_SetWOWThunkGlobalPtr() { __asm { jmp ole32.exp[84 * 4]} }
__declspec(naked) void Proxy_CreateILockBytesOnHGlobal() { __asm { jmp ole32.exp[85 * 4]} }
__declspec(naked) void Proxy_FmtIdToPropStgName() { __asm { jmp ole32.exp[86 * 4]} }
__declspec(naked) void Proxy_GetConvertStg() { __asm { jmp ole32.exp[87 * 4]} }
__declspec(naked) void Proxy_GetDocumentBitStg() { __asm { jmp ole32.exp[88 * 4]} }
__declspec(naked) void Proxy_GetHGlobalFromILockBytes() { __asm { jmp ole32.exp[89 * 4]} }
__declspec(naked) void Proxy_PropStgNameToFmtId() { __asm { jmp ole32.exp[90 * 4]} }
__declspec(naked) void Proxy_PropSysAllocString() { __asm { jmp ole32.exp[91 * 4]} }
__declspec(naked) void Proxy_PropSysFreeString() { __asm { jmp ole32.exp[92 * 4]} }
__declspec(naked) void Proxy_PropVariantChangeType() { __asm { jmp ole32.exp[93 * 4]} }
__declspec(naked) void Proxy_StgConvertPropertyToVariant() { __asm { jmp ole32.exp[94 * 4]} }
__declspec(naked) void Proxy_StgConvertVariantToProperty() { __asm { jmp ole32.exp[95 * 4]} }
__declspec(naked) void Proxy_StgCreatePropSetStg() { __asm { jmp ole32.exp[96 * 4]} }
__declspec(naked) void Proxy_StgCreatePropStg() { __asm { jmp ole32.exp[97 * 4]} }
__declspec(naked) void Proxy_StgGetIFillLockBytesOnFile() { __asm { jmp ole32.exp[98 * 4]} }
__declspec(naked) void Proxy_StgGetIFillLockBytesOnILockBytes() { __asm { jmp ole32.exp[99 * 4]} }
__declspec(naked) void Proxy_StgIsStorageILockBytes() { __asm { jmp ole32.exp[100 * 4]} }
__declspec(naked) void Proxy_StgOpenAsyncDocfileOnIFillLockBytes() { __asm { jmp ole32.exp[101 * 4]} }
__declspec(naked) void Proxy_StgOpenPropStg() { __asm { jmp ole32.exp[102 * 4]} }
__declspec(naked) void Proxy_StgOpenStorageOnHandle() { __asm { jmp ole32.exp[103 * 4]} }
__declspec(naked) void Proxy_StgPropertyLengthAsVariant() { __asm { jmp ole32.exp[104 * 4]} }
__declspec(naked) void Proxy_StgSetTimes() { __asm { jmp ole32.exp[105 * 4]} }
__declspec(naked) void Proxy_WriteClassStm() { __asm { jmp ole32.exp[106 * 4]} }
__declspec(naked) void Proxy_CreateAntiMoniker() { __asm { jmp ole32.exp[107 * 4]} }
__declspec(naked) void Proxy_CreateObjrefMoniker() { __asm { jmp ole32.exp[108 * 4]} }
__declspec(naked) void Proxy_OleLoadFromStream() { __asm { jmp ole32.exp[109 * 4]} }
__declspec(naked) void Proxy_MonikerCommonPrefixWith() { __asm { jmp ole32.exp[110 * 4]} }
__declspec(naked) void Proxy_MonikerRelativePathTo() { __asm { jmp ole32.exp[111 * 4]} }
__declspec(naked) void Proxy_FindExt() { __asm { jmp ole32.exp[112 * 4]} }
__declspec(naked) void Proxy_GetClassFile() { __asm { jmp ole32.exp[113 * 4]} }
__declspec(naked) void Proxy_CoFreeLibrary() { __asm { jmp ole32.exp[114 * 4]} }
__declspec(naked) void Proxy_CoInstall() { __asm { jmp ole32.exp[115 * 4]} }
__declspec(naked) void Proxy_CoLoadLibrary() { __asm { jmp ole32.exp[116 * 4]} }
__declspec(naked) void Proxy_CoQueryReleaseObject() { __asm { jmp ole32.exp[117 * 4]} }
__declspec(naked) void Proxy_IsRoInitializeASTAAllowedInDesktop() { __asm { jmp ole32.exp[118 * 4]} }
__declspec(naked) void Proxy_CoIsOle1Class() { __asm { jmp ole32.exp[119 * 4]} }
__declspec(naked) void Proxy_CoTreatAsClass() { __asm { jmp ole32.exp[120 * 4]} }
__declspec(naked) void Proxy_IsValidPtrIn() { __asm { jmp ole32.exp[121 * 4]} }
__declspec(naked) void Proxy_IsValidPtrOut() { __asm { jmp ole32.exp[122 * 4]} }
__declspec(naked) void Proxy_CoDosDateTimeToFileTime() { __asm { jmp ole32.exp[123 * 4]} }
__declspec(naked) void Proxy_CoFileTimeToDosDateTime() { __asm { jmp ole32.exp[124 * 4]} }
__declspec(naked) void Proxy_HENHMETAFILE_UserFree() { __asm { jmp ole32.exp[125 * 4]} }
__declspec(naked) void Proxy_HENHMETAFILE_UserMarshal() { __asm { jmp ole32.exp[126 * 4]} }
__declspec(naked) void Proxy_HENHMETAFILE_UserSize() { __asm { jmp ole32.exp[127 * 4]} }
__declspec(naked) void Proxy_HENHMETAFILE_UserUnmarshal() { __asm { jmp ole32.exp[128 * 4]} }
__declspec(naked) void Proxy_HMETAFILEPICT_UserFree() { __asm { jmp ole32.exp[129 * 4]} }
__declspec(naked) void Proxy_HMETAFILEPICT_UserMarshal() { __asm { jmp ole32.exp[130 * 4]} }
__declspec(naked) void Proxy_HMETAFILEPICT_UserSize() { __asm { jmp ole32.exp[131 * 4]} }
__declspec(naked) void Proxy_HMETAFILEPICT_UserUnmarshal() { __asm { jmp ole32.exp[132 * 4]} }
__declspec(naked) void Proxy_HMETAFILE_UserFree() { __asm { jmp ole32.exp[133 * 4]} }
__declspec(naked) void Proxy_HMETAFILE_UserMarshal() { __asm { jmp ole32.exp[134 * 4]} }
__declspec(naked) void Proxy_HMETAFILE_UserSize() { __asm { jmp ole32.exp[135 * 4]} }
__declspec(naked) void Proxy_HMETAFILE_UserUnmarshal() { __asm { jmp ole32.exp[136 * 4]} }
__declspec(naked) void Proxy_SNB_UserFree() { __asm { jmp ole32.exp[137 * 4]} }
__declspec(naked) void Proxy_SNB_UserMarshal() { __asm { jmp ole32.exp[138 * 4]} }
__declspec(naked) void Proxy_SNB_UserSize() { __asm { jmp ole32.exp[139 * 4]} }
__declspec(naked) void Proxy_SNB_UserUnmarshal() { __asm { jmp ole32.exp[140 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserFree() { __asm { jmp ole32.exp[141 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserMarshal() { __asm { jmp ole32.exp[142 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserSize() { __asm { jmp ole32.exp[143 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserUnmarshal() { __asm { jmp ole32.exp[144 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserFreeExt() { __asm { jmp ole32.exp[145 * 4]} }
__declspec(naked) void Proxy_HWND_UserUnmarshalExt() { __asm { jmp ole32.exp[146 * 4]} }
__declspec(naked) void Proxy_HWND_UserMarshalExt() { __asm { jmp ole32.exp[147 * 4]} }
__declspec(naked) void Proxy_HWND_UserSizeExt() { __asm { jmp ole32.exp[148 * 4]} }
__declspec(naked) void Proxy_CoGetInterceptor() { __asm { jmp ole32.exp[149 * 4]} }
__declspec(naked) void Proxy_ComPs_NdrDllGetClassObject() { __asm { jmp ole32.exp[150 * 4]} }
__declspec(naked) void Proxy_ComPs_NdrDllRegisterProxy() { __asm { jmp ole32.exp[151 * 4]} }
__declspec(naked) void Proxy_ComPs_NdrDllUnregisterProxy() { __asm { jmp ole32.exp[152 * 4]} }
__declspec(naked) void Proxy_GetObjectFromRotByPath() { __asm { jmp ole32.exp[153 * 4]} }
__declspec(naked) void Proxy_DdeBindToObject() { __asm { jmp ole32.exp[154 * 4]} }
__declspec(naked) void Proxy_OleCreate() { __asm { jmp ole32.exp[155 * 4]} }
__declspec(naked) void Proxy_OleCreateEx() { __asm { jmp ole32.exp[156 * 4]} }
__declspec(naked) void Proxy_OleCreateFromData() { __asm { jmp ole32.exp[157 * 4]} }
__declspec(naked) void Proxy_OleCreateFromDataEx() { __asm { jmp ole32.exp[158 * 4]} }
__declspec(naked) void Proxy_OleCreateFromFile() { __asm { jmp ole32.exp[159 * 4]} }
__declspec(naked) void Proxy_OleCreateFromFileEx() { __asm { jmp ole32.exp[160 * 4]} }
__declspec(naked) void Proxy_OleCreateLink() { __asm { jmp ole32.exp[161 * 4]} }
__declspec(naked) void Proxy_OleCreateLinkEx() { __asm { jmp ole32.exp[162 * 4]} }
__declspec(naked) void Proxy_OleCreateLinkFromData() { __asm { jmp ole32.exp[163 * 4]} }
__declspec(naked) void Proxy_OleCreateLinkFromDataEx() { __asm { jmp ole32.exp[164 * 4]} }
__declspec(naked) void Proxy_OleCreateLinkToFile() { __asm { jmp ole32.exp[165 * 4]} }
__declspec(naked) void Proxy_OleCreateLinkToFileEx() { __asm { jmp ole32.exp[166 * 4]} }
__declspec(naked) void Proxy_OleCreateStaticFromData() { __asm { jmp ole32.exp[167 * 4]} }
__declspec(naked) void Proxy_OleDoAutoConvert() { __asm { jmp ole32.exp[168 * 4]} }
__declspec(naked) void Proxy_OleLoad() { __asm { jmp ole32.exp[169 * 4]} }
__declspec(naked) void Proxy_OleQueryCreateFromData() { __asm { jmp ole32.exp[170 * 4]} }
__declspec(naked) void Proxy_OleDraw() { __asm { jmp ole32.exp[171 * 4]} }
__declspec(naked) void Proxy_OleDuplicateData() { __asm { jmp ole32.exp[172 * 4]} }
__declspec(naked) void Proxy_OleIsRunning() { __asm { jmp ole32.exp[173 * 4]} }
__declspec(naked) void Proxy_OleNoteObjectVisible() { __asm { jmp ole32.exp[174 * 4]} }
__declspec(naked) void Proxy_OleSetContainedObject() { __asm { jmp ole32.exp[175 * 4]} }
__declspec(naked) void Proxy_ReadOleStg() { __asm { jmp ole32.exp[176 * 4]} }
__declspec(naked) void Proxy_SetConvertStg() { __asm { jmp ole32.exp[177 * 4]} }
__declspec(naked) void Proxy_SetDocumentBitStg() { __asm { jmp ole32.exp[178 * 4]} }
__declspec(naked) void Proxy_WriteOleStg() { __asm { jmp ole32.exp[179 * 4]} }
__declspec(naked) void Proxy_OleInitializeWOW() { __asm { jmp ole32.exp[180 * 4]} }
__declspec(naked) void Proxy_CreateDataCache() { __asm { jmp ole32.exp[181 * 4]} }
__declspec(naked) void Proxy_OleGetClipboardWithEnterpriseInfo() { __asm { jmp ole32.exp[182 * 4]} }
__declspec(naked) void Proxy_Ordinal804() { __asm { jmp ole32.exp[183 * 4]} }
__declspec(naked) void Proxy_OleGetPackageClipboardOwner() { __asm { jmp ole32.exp[184 * 4]} }
__declspec(naked) void Proxy_DoDragDrop() { __asm { jmp ole32.exp[185 * 4]} }
__declspec(naked) void Proxy_DragDropSetFDT() { __asm { jmp ole32.exp[186 * 4]} }
__declspec(naked) void Proxy_Ordinal822() { __asm { jmp ole32.exp[187 * 4]} }
__declspec(naked) void Proxy_Ordinal820() { __asm { jmp ole32.exp[188 * 4]} }
__declspec(naked) void Proxy_Ordinal821() { __asm { jmp ole32.exp[189 * 4]} }
__declspec(naked) void Proxy_Ordinal823() { __asm { jmp ole32.exp[190 * 4]} }
__declspec(naked) void Proxy_IsAccelerator() { __asm { jmp ole32.exp[191 * 4]} }
__declspec(naked) void Proxy_OleCreateMenuDescriptor() { __asm { jmp ole32.exp[192 * 4]} }
__declspec(naked) void Proxy_OleDestroyMenuDescriptor() { __asm { jmp ole32.exp[193 * 4]} }
__declspec(naked) void Proxy_OleSetMenuDescriptor() { __asm { jmp ole32.exp[194 * 4]} }
__declspec(naked) void Proxy_OleTranslateAccelerator() { __asm { jmp ole32.exp[195 * 4]} }
__declspec(naked) void Proxy_OleCreateDefaultHandler() { __asm { jmp ole32.exp[196 * 4]} }
__declspec(naked) void Proxy_OleCreateEmbeddingHelper() { __asm { jmp ole32.exp[197 * 4]} }
__declspec(naked) void Proxy_OleGetAutoConvert() { __asm { jmp ole32.exp[198 * 4]} }
__declspec(naked) void Proxy_OleRegGetUserType() { __asm { jmp ole32.exp[199 * 4]} }
__declspec(naked) void Proxy_OleSetAutoConvert() { __asm { jmp ole32.exp[200 * 4]} }
__declspec(naked) void Proxy_OleGetIconOfClass() { __asm { jmp ole32.exp[201 * 4]} }
__declspec(naked) void Proxy_OleGetIconOfFile() { __asm { jmp ole32.exp[202 * 4]} }
__declspec(naked) void Proxy_OleMetafilePictFromIconAndLabel() { __asm { jmp ole32.exp[203 * 4]} }
__declspec(naked) void Proxy_OleRegEnumFormatEtc() { __asm { jmp ole32.exp[204 * 4]} }
__declspec(naked) void Proxy_OleRegEnumVerbs() { __asm { jmp ole32.exp[205 * 4]} }
__declspec(naked) void Proxy_OleConvertIStorageToOLESTREAM() { __asm { jmp ole32.exp[206 * 4]} }
__declspec(naked) void Proxy_OleConvertIStorageToOLESTREAMEx() { __asm { jmp ole32.exp[207 * 4]} }
__declspec(naked) void Proxy_OleConvertOLESTREAMToIStorage() { __asm { jmp ole32.exp[208 * 4]} }
__declspec(naked) void Proxy_OleConvertOLESTREAMToIStorageEx() { __asm { jmp ole32.exp[209 * 4]} }
__declspec(naked) void Proxy_OpenOrCreateStream() { __asm { jmp ole32.exp[210 * 4]} }
__declspec(naked) void Proxy_ReadStringStream() { __asm { jmp ole32.exp[211 * 4]} }
__declspec(naked) void Proxy_UtConvertDvtd16toDvtd32() { __asm { jmp ole32.exp[212 * 4]} }
__declspec(naked) void Proxy_UtConvertDvtd32toDvtd16() { __asm { jmp ole32.exp[213 * 4]} }
__declspec(naked) void Proxy_UtGetDvtd16Info() { __asm { jmp ole32.exp[214 * 4]} }
__declspec(naked) void Proxy_UtGetDvtd32Info() { __asm { jmp ole32.exp[215 * 4]} }
__declspec(naked) void Proxy_StdTypesGetClassObject() { __asm { jmp ole32.exp[216 * 4]} }
__declspec(naked) void Proxy_StdTypesRegisterServer() { __asm { jmp ole32.exp[217 * 4]} }
__declspec(naked) void Proxy_OleCreatePictureIndirectExt() { __asm { jmp ole32.exp[218 * 4]} }
__declspec(naked) void Proxy_OleIconToCursorExt() { __asm { jmp ole32.exp[219 * 4]} }
__declspec(naked) void Proxy_OleLoadPictureExt() { __asm { jmp ole32.exp[220 * 4]} }
__declspec(naked) void Proxy_OleLoadPicturePathExt() { __asm { jmp ole32.exp[221 * 4]} }
__declspec(naked) void Proxy_OleCreatePropertyFrameIndirectExt() { __asm { jmp ole32.exp[222 * 4]} }
__declspec(naked) void Proxy_OleLoadPictureFileExt() { __asm { jmp ole32.exp[223 * 4]} }
__declspec(naked) void Proxy_OleSavePictureFileExt() { __asm { jmp ole32.exp[224 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserMarshalExt() { __asm { jmp ole32.exp[225 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserSizeExt() { __asm { jmp ole32.exp[226 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserUnmarshalExt() { __asm { jmp ole32.exp[227 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserFreeExt() { __asm { jmp ole32.exp[228 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserMarshalExt() { __asm { jmp ole32.exp[229 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserSizeExt() { __asm { jmp ole32.exp[230 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserUnmarshalExt() { __asm { jmp ole32.exp[231 * 4]} }
__declspec(naked) void Proxy_MonikerLoadTypeLib() { __asm { jmp ole32.exp[232 * 4]} }
__declspec(naked) void Proxy_ReadStorageProperties() { __asm { jmp ole32.exp[233 * 4]} }
__declspec(naked) void Proxy_ReadClassStg() { __asm { jmp ole32.exp[234 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserFreeExt() { __asm { jmp ole32.exp[235 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserMarshalExt() { __asm { jmp ole32.exp[236 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserSizeExt() { __asm { jmp ole32.exp[237 * 4]} }
__declspec(naked) void Proxy_STGMEDIUM_UserUnmarshalExt() { __asm { jmp ole32.exp[238 * 4]} }
__declspec(naked) void Proxy_WriteStorageProperties() { __asm { jmp ole32.exp[239 * 4]} }
__declspec(naked) void Proxy_HRGN_UserFree() { __asm { jmp ole32.exp[240 * 4]} }
__declspec(naked) void Proxy_HRGN_UserMarshal() { __asm { jmp ole32.exp[241 * 4]} }
__declspec(naked) void Proxy_HRGN_UserSize() { __asm { jmp ole32.exp[242 * 4]} }
__declspec(naked) void Proxy_HRGN_UserUnmarshal() { __asm { jmp ole32.exp[243 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserFree() { __asm { jmp ole32.exp[244 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserMarshal() { __asm { jmp ole32.exp[245 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserSize() { __asm { jmp ole32.exp[246 * 4]} }
__declspec(naked) void Proxy_CLIPFORMAT_UserUnmarshal() { __asm { jmp ole32.exp[247 * 4]} }
__declspec(naked) void Proxy_CLSIDFromOle1Class() { __asm { jmp ole32.exp[248 * 4]} }
__declspec(naked) void Proxy_CLSIDFromProgID() { __asm { jmp ole32.exp[249 * 4]} }
__declspec(naked) void Proxy_CLSIDFromProgIDEx() { __asm { jmp ole32.exp[250 * 4]} }
__declspec(naked) void Proxy_CLSIDFromString() { __asm { jmp ole32.exp[251 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer2_Connect() { __asm { jmp ole32.exp[252 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer2_Disconnect() { __asm { jmp ole32.exp[253 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer2_Release() { __asm { jmp ole32.exp[254 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_AddRef() { __asm { jmp ole32.exp[255 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_Connect() { __asm { jmp ole32.exp[256 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_Disconnect() { __asm { jmp ole32.exp[257 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_Invoke() { __asm { jmp ole32.exp[258 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_QueryInterface() { __asm { jmp ole32.exp[259 * 4]} }
__declspec(naked) void Proxy_CStdAsyncStubBuffer_Release() { __asm { jmp ole32.exp[260 * 4]} }
__declspec(naked) void Proxy_CStdStubBuffer2_Connect() { __asm { jmp ole32.exp[261 * 4]} }
__declspec(naked) void Proxy_CStdStubBuffer2_CountRefs() { __asm { jmp ole32.exp[262 * 4]} }
__declspec(naked) void Proxy_CStdStubBuffer2_Disconnect() { __asm { jmp ole32.exp[263 * 4]} }
__declspec(naked) void Proxy_CStdStubBuffer2_QueryInterface() { __asm { jmp ole32.exp[264 * 4]} }
__declspec(naked) void Proxy_CoAddRefServerProcess() { __asm { jmp ole32.exp[265 * 4]} }
__declspec(naked) void Proxy_CoAllowUnmarshalerCLSID() { __asm { jmp ole32.exp[266 * 4]} }
__declspec(naked) void Proxy_CoCancelCall() { __asm { jmp ole32.exp[267 * 4]} }
__declspec(naked) void Proxy_CoCopyProxy() { __asm { jmp ole32.exp[268 * 4]} }
__declspec(naked) void Proxy_CoCreateFreeThreadedMarshaler() { __asm { jmp ole32.exp[269 * 4]} }
__declspec(naked) void Proxy_CoCreateGuid() { __asm { jmp ole32.exp[270 * 4]} }
__declspec(naked) void Proxy_CoCreateInstance() { __asm { jmp ole32.exp[271 * 4]} }
__declspec(naked) void Proxy_CoCreateInstanceEx() { __asm { jmp ole32.exp[272 * 4]} }
__declspec(naked) void Proxy_CoCreateInstanceFromApp() { __asm { jmp ole32.exp[273 * 4]} }
__declspec(naked) void Proxy_CoCreateObjectInContext() { __asm { jmp ole32.exp[274 * 4]} }
__declspec(naked) void Proxy_CoDeactivateObject() { __asm { jmp ole32.exp[275 * 4]} }
__declspec(naked) void Proxy_CoDecodeProxy() { __asm { jmp ole32.exp[276 * 4]} }
__declspec(naked) void Proxy_CoDecrementMTAUsage() { __asm { jmp ole32.exp[277 * 4]} }
__declspec(naked) void Proxy_CoDisableCallCancellation() { __asm { jmp ole32.exp[278 * 4]} }
__declspec(naked) void Proxy_CoDisconnectContext() { __asm { jmp ole32.exp[279 * 4]} }
__declspec(naked) void Proxy_CoDisconnectObject() { __asm { jmp ole32.exp[280 * 4]} }
__declspec(naked) void Proxy_CoEnableCallCancellation() { __asm { jmp ole32.exp[281 * 4]} }
__declspec(naked) void Proxy_CoFileTimeNow() { __asm { jmp ole32.exp[282 * 4]} }
__declspec(naked) void Proxy_CoFreeUnusedLibraries() { __asm { jmp ole32.exp[283 * 4]} }
__declspec(naked) void Proxy_CoFreeUnusedLibrariesEx() { __asm { jmp ole32.exp[284 * 4]} }
__declspec(naked) void Proxy_CoGetActivationState() { __asm { jmp ole32.exp[285 * 4]} }
__declspec(naked) void Proxy_CoGetApartmentID() { __asm { jmp ole32.exp[286 * 4]} }
__declspec(naked) void Proxy_CoGetApartmentType() { __asm { jmp ole32.exp[287 * 4]} }
__declspec(naked) void Proxy_CoGetCallContext() { __asm { jmp ole32.exp[288 * 4]} }
__declspec(naked) void Proxy_CoGetCallState() { __asm { jmp ole32.exp[289 * 4]} }
__declspec(naked) void Proxy_CoGetCallerTID() { __asm { jmp ole32.exp[290 * 4]} }
__declspec(naked) void Proxy_CoGetCancelObject() { __asm { jmp ole32.exp[291 * 4]} }
__declspec(naked) void Proxy_CoGetClassObject() { __asm { jmp ole32.exp[292 * 4]} }
__declspec(naked) void Proxy_CoGetClassVersion() { __asm { jmp ole32.exp[293 * 4]} }
__declspec(naked) void Proxy_CoGetComCatalog() { __asm { jmp ole32.exp[294 * 4]} }
__declspec(naked) void Proxy_CoGetContextToken() { __asm { jmp ole32.exp[295 * 4]} }
__declspec(naked) void Proxy_CoGetCurrentLogicalThreadId() { __asm { jmp ole32.exp[296 * 4]} }
__declspec(naked) void Proxy_CoGetCurrentProcess() { __asm { jmp ole32.exp[297 * 4]} }
__declspec(naked) void Proxy_CoGetDefaultContext() { __asm { jmp ole32.exp[298 * 4]} }
__declspec(naked) void Proxy_CoGetInstanceFromFile() { __asm { jmp ole32.exp[299 * 4]} }
__declspec(naked) void Proxy_CoGetInstanceFromIStorage() { __asm { jmp ole32.exp[300 * 4]} }
__declspec(naked) void Proxy_CoGetInterfaceAndReleaseStream() { __asm { jmp ole32.exp[301 * 4]} }
__declspec(naked) void Proxy_CoGetMalloc() { __asm { jmp ole32.exp[302 * 4]} }
__declspec(naked) void Proxy_CoGetMarshalSizeMax() { __asm { jmp ole32.exp[303 * 4]} }
__declspec(naked) void Proxy_CoGetModuleType() { __asm { jmp ole32.exp[304 * 4]} }
__declspec(naked) void Proxy_CoGetObjectContext() { __asm { jmp ole32.exp[305 * 4]} }
__declspec(naked) void Proxy_CoGetPSClsid() { __asm { jmp ole32.exp[306 * 4]} }
__declspec(naked) void Proxy_CoGetProcessIdentifier() { __asm { jmp ole32.exp[307 * 4]} }
__declspec(naked) void Proxy_CoGetStandardMarshal() { __asm { jmp ole32.exp[308 * 4]} }
__declspec(naked) void Proxy_CoGetStdMarshalEx() { __asm { jmp ole32.exp[309 * 4]} }
__declspec(naked) void Proxy_CoGetSystemSecurityPermissions() { __asm { jmp ole32.exp[310 * 4]} }
__declspec(naked) void Proxy_CoGetTreatAsClass() { __asm { jmp ole32.exp[311 * 4]} }
__declspec(naked) void Proxy_CoHandlePriorityEventsFromMessagePump() { __asm { jmp ole32.exp[312 * 4]} }
__declspec(naked) void Proxy_CoImpersonateClient() { __asm { jmp ole32.exp[313 * 4]} }
__declspec(naked) void Proxy_CoIncrementMTAUsage() { __asm { jmp ole32.exp[314 * 4]} }
__declspec(naked) void Proxy_CoInitializeEx() { __asm { jmp ole32.exp[315 * 4]} }
__declspec(naked) void Proxy_CoInitializeSecurity() { __asm { jmp ole32.exp[316 * 4]} }
__declspec(naked) void Proxy_CoInvalidateRemoteMachineBindings() { __asm { jmp ole32.exp[317 * 4]} }
__declspec(naked) void Proxy_CoIsHandlerConnected() { __asm { jmp ole32.exp[318 * 4]} }
__declspec(naked) void Proxy_CoLockObjectExternal() { __asm { jmp ole32.exp[319 * 4]} }
__declspec(naked) void Proxy_CoMarshalHresult() { __asm { jmp ole32.exp[320 * 4]} }
__declspec(naked) void Proxy_CoMarshalInterThreadInterfaceInStream() { __asm { jmp ole32.exp[321 * 4]} }
__declspec(naked) void Proxy_CoMarshalInterface() { __asm { jmp ole32.exp[322 * 4]} }
__declspec(naked) void Proxy_CoPopServiceDomain() { __asm { jmp ole32.exp[323 * 4]} }
__declspec(naked) void Proxy_CoPushServiceDomain() { __asm { jmp ole32.exp[324 * 4]} }
__declspec(naked) void Proxy_CoQueryAuthenticationServices() { __asm { jmp ole32.exp[325 * 4]} }
__declspec(naked) void Proxy_CoQueryClientBlanket() { __asm { jmp ole32.exp[326 * 4]} }
__declspec(naked) void Proxy_CoQueryProxyBlanket() { __asm { jmp ole32.exp[327 * 4]} }
__declspec(naked) void Proxy_CoReactivateObject() { __asm { jmp ole32.exp[328 * 4]} }
__declspec(naked) void Proxy_CoRegisterActivationFilter() { __asm { jmp ole32.exp[329 * 4]} }
__declspec(naked) void Proxy_CoRegisterChannelHook() { __asm { jmp ole32.exp[330 * 4]} }
__declspec(naked) void Proxy_CoRegisterClassObject() { __asm { jmp ole32.exp[331 * 4]} }
__declspec(naked) void Proxy_CoRegisterInitializeSpy() { __asm { jmp ole32.exp[332 * 4]} }
__declspec(naked) void Proxy_CoRegisterMallocSpy() { __asm { jmp ole32.exp[333 * 4]} }
__declspec(naked) void Proxy_CoRegisterPSClsid() { __asm { jmp ole32.exp[334 * 4]} }
__declspec(naked) void Proxy_CoRegisterSurrogate() { __asm { jmp ole32.exp[335 * 4]} }
__declspec(naked) void Proxy_CoReleaseMarshalData() { __asm { jmp ole32.exp[336 * 4]} }
__declspec(naked) void Proxy_CoReleaseServerProcess() { __asm { jmp ole32.exp[337 * 4]} }
__declspec(naked) void Proxy_CoResumeClassObjects() { __asm { jmp ole32.exp[338 * 4]} }
__declspec(naked) void Proxy_CoRetireServer() { __asm { jmp ole32.exp[339 * 4]} }
__declspec(naked) void Proxy_CoRevertToSelf() { __asm { jmp ole32.exp[340 * 4]} }
__declspec(naked) void Proxy_CoRevokeClassObject() { __asm { jmp ole32.exp[341 * 4]} }
__declspec(naked) void Proxy_CoRevokeInitializeSpy() { __asm { jmp ole32.exp[342 * 4]} }
__declspec(naked) void Proxy_CoRevokeMallocSpy() { __asm { jmp ole32.exp[343 * 4]} }
__declspec(naked) void Proxy_CoSetCancelObject() { __asm { jmp ole32.exp[344 * 4]} }
__declspec(naked) void Proxy_CoSetMessageDispatcher() { __asm { jmp ole32.exp[345 * 4]} }
__declspec(naked) void Proxy_CoSetProxyBlanket() { __asm { jmp ole32.exp[346 * 4]} }
__declspec(naked) void Proxy_CoSuspendClassObjects() { __asm { jmp ole32.exp[347 * 4]} }
__declspec(naked) void Proxy_CoSwitchCallContext() { __asm { jmp ole32.exp[348 * 4]} }
__declspec(naked) void Proxy_CoTaskMemAlloc() { __asm { jmp ole32.exp[349 * 4]} }
__declspec(naked) void Proxy_CoTaskMemFree() { __asm { jmp ole32.exp[350 * 4]} }
__declspec(naked) void Proxy_CoTaskMemRealloc() { __asm { jmp ole32.exp[351 * 4]} }
__declspec(naked) void Proxy_CoTestCancel() { __asm { jmp ole32.exp[352 * 4]} }
__declspec(naked) void Proxy_CoUninitialize() { __asm { jmp ole32.exp[353 * 4]} }
__declspec(naked) void Proxy_CoUnmarshalHresult() { __asm { jmp ole32.exp[354 * 4]} }
__declspec(naked) void Proxy_CoUnmarshalInterface() { __asm { jmp ole32.exp[355 * 4]} }
__declspec(naked) void Proxy_CoVrfCheckThreadState() { __asm { jmp ole32.exp[356 * 4]} }
__declspec(naked) void Proxy_CoVrfGetThreadState() { __asm { jmp ole32.exp[357 * 4]} }
__declspec(naked) void Proxy_CoVrfReleaseThreadState() { __asm { jmp ole32.exp[358 * 4]} }
__declspec(naked) void Proxy_CoWaitForMultipleHandles() { __asm { jmp ole32.exp[359 * 4]} }
__declspec(naked) void Proxy_CoWaitForMultipleObjects() { __asm { jmp ole32.exp[360 * 4]} }
__declspec(naked) void Proxy_CreateErrorInfo() { __asm { jmp ole32.exp[361 * 4]} }
__declspec(naked) void Proxy_CreateStreamOnHGlobal() { __asm { jmp ole32.exp[362 * 4]} }
__declspec(naked) void Proxy_DcomChannelSetHResult() { __asm { jmp ole32.exp[363 * 4]} }
__declspec(naked) void Proxy_DllDebugObjectRPCHook() { __asm { jmp ole32.exp[364 * 4]} }
__declspec(naked) void Proxy_EnableHookObject() { __asm { jmp ole32.exp[365 * 4]} }
__declspec(naked) void Proxy_GetErrorInfo() { __asm { jmp ole32.exp[366 * 4]} }
__declspec(naked) void Proxy_GetHGlobalFromStream() { __asm { jmp ole32.exp[367 * 4]} }
__declspec(naked) void Proxy_GetHookInterface() { __asm { jmp ole32.exp[368 * 4]} }
__declspec(naked) void Proxy_HACCEL_UserFree() { __asm { jmp ole32.exp[369 * 4]} }
__declspec(naked) void Proxy_HACCEL_UserMarshal() { __asm { jmp ole32.exp[370 * 4]} }
__declspec(naked) void Proxy_HACCEL_UserSize() { __asm { jmp ole32.exp[371 * 4]} }
__declspec(naked) void Proxy_HACCEL_UserUnmarshal() { __asm { jmp ole32.exp[372 * 4]} }
__declspec(naked) void Proxy_HBITMAP_UserFree() { __asm { jmp ole32.exp[373 * 4]} }
__declspec(naked) void Proxy_HBITMAP_UserMarshal() { __asm { jmp ole32.exp[374 * 4]} }
__declspec(naked) void Proxy_HBITMAP_UserSize() { __asm { jmp ole32.exp[375 * 4]} }
__declspec(naked) void Proxy_HBITMAP_UserUnmarshal() { __asm { jmp ole32.exp[376 * 4]} }
__declspec(naked) void Proxy_HBRUSH_UserFree() { __asm { jmp ole32.exp[377 * 4]} }
__declspec(naked) void Proxy_HBRUSH_UserMarshal() { __asm { jmp ole32.exp[378 * 4]} }
__declspec(naked) void Proxy_HBRUSH_UserSize() { __asm { jmp ole32.exp[379 * 4]} }
__declspec(naked) void Proxy_HBRUSH_UserUnmarshal() { __asm { jmp ole32.exp[380 * 4]} }
__declspec(naked) void Proxy_HDC_UserFree() { __asm { jmp ole32.exp[381 * 4]} }
__declspec(naked) void Proxy_HDC_UserMarshal() { __asm { jmp ole32.exp[382 * 4]} }
__declspec(naked) void Proxy_HDC_UserSize() { __asm { jmp ole32.exp[383 * 4]} }
__declspec(naked) void Proxy_HDC_UserUnmarshal() { __asm { jmp ole32.exp[384 * 4]} }
__declspec(naked) void Proxy_HGLOBAL_UserFree() { __asm { jmp ole32.exp[385 * 4]} }
__declspec(naked) void Proxy_HGLOBAL_UserMarshal() { __asm { jmp ole32.exp[386 * 4]} }
__declspec(naked) void Proxy_HGLOBAL_UserSize() { __asm { jmp ole32.exp[387 * 4]} }
__declspec(naked) void Proxy_HGLOBAL_UserUnmarshal() { __asm { jmp ole32.exp[388 * 4]} }
__declspec(naked) void Proxy_HICON_UserFree() { __asm { jmp ole32.exp[389 * 4]} }
__declspec(naked) void Proxy_HICON_UserMarshal() { __asm { jmp ole32.exp[390 * 4]} }
__declspec(naked) void Proxy_HICON_UserSize() { __asm { jmp ole32.exp[391 * 4]} }
__declspec(naked) void Proxy_HICON_UserUnmarshal() { __asm { jmp ole32.exp[392 * 4]} }
__declspec(naked) void Proxy_HMENU_UserFree() { __asm { jmp ole32.exp[393 * 4]} }
__declspec(naked) void Proxy_HMENU_UserMarshal() { __asm { jmp ole32.exp[394 * 4]} }
__declspec(naked) void Proxy_HMENU_UserSize() { __asm { jmp ole32.exp[395 * 4]} }
__declspec(naked) void Proxy_HMENU_UserUnmarshal() { __asm { jmp ole32.exp[396 * 4]} }
__declspec(naked) void Proxy_HMONITOR_UserFree() { __asm { jmp ole32.exp[397 * 4]} }
__declspec(naked) void Proxy_HMONITOR_UserMarshal() { __asm { jmp ole32.exp[398 * 4]} }
__declspec(naked) void Proxy_HMONITOR_UserSize() { __asm { jmp ole32.exp[399 * 4]} }
__declspec(naked) void Proxy_HMONITOR_UserUnmarshal() { __asm { jmp ole32.exp[400 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserFree() { __asm { jmp ole32.exp[401 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserMarshal() { __asm { jmp ole32.exp[402 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserSize() { __asm { jmp ole32.exp[403 * 4]} }
__declspec(naked) void Proxy_HPALETTE_UserUnmarshal() { __asm { jmp ole32.exp[404 * 4]} }
__declspec(naked) void Proxy_HWND_UserFree() { __asm { jmp ole32.exp[405 * 4]} }
__declspec(naked) void Proxy_HWND_UserMarshal() { __asm { jmp ole32.exp[406 * 4]} }
__declspec(naked) void Proxy_HWND_UserSize() { __asm { jmp ole32.exp[407 * 4]} }
__declspec(naked) void Proxy_HWND_UserUnmarshal() { __asm { jmp ole32.exp[408 * 4]} }
__declspec(naked) void Proxy_HkOleRegisterObject() { __asm { jmp ole32.exp[409 * 4]} }
__declspec(naked) void Proxy_IIDFromString() { __asm { jmp ole32.exp[410 * 4]} }
__declspec(naked) void Proxy_NdrOleInitializeExtension() { __asm { jmp ole32.exp[411 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction10() { __asm { jmp ole32.exp[412 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction11() { __asm { jmp ole32.exp[413 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction12() { __asm { jmp ole32.exp[414 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction13() { __asm { jmp ole32.exp[415 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction14() { __asm { jmp ole32.exp[416 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction15() { __asm { jmp ole32.exp[417 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction16() { __asm { jmp ole32.exp[418 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction17() { __asm { jmp ole32.exp[419 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction18() { __asm { jmp ole32.exp[420 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction19() { __asm { jmp ole32.exp[421 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction20() { __asm { jmp ole32.exp[422 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction21() { __asm { jmp ole32.exp[423 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction22() { __asm { jmp ole32.exp[424 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction23() { __asm { jmp ole32.exp[425 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction24() { __asm { jmp ole32.exp[426 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction25() { __asm { jmp ole32.exp[427 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction26() { __asm { jmp ole32.exp[428 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction27() { __asm { jmp ole32.exp[429 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction28() { __asm { jmp ole32.exp[430 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction29() { __asm { jmp ole32.exp[431 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction30() { __asm { jmp ole32.exp[432 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction31() { __asm { jmp ole32.exp[433 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction32() { __asm { jmp ole32.exp[434 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction3() { __asm { jmp ole32.exp[435 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction4() { __asm { jmp ole32.exp[436 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction5() { __asm { jmp ole32.exp[437 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction6() { __asm { jmp ole32.exp[438 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction7() { __asm { jmp ole32.exp[439 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction8() { __asm { jmp ole32.exp[440 * 4]} }
__declspec(naked) void Proxy_NdrProxyForwardingFunction9() { __asm { jmp ole32.exp[441 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient10() { __asm { jmp ole32.exp[442 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient11() { __asm { jmp ole32.exp[443 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient12() { __asm { jmp ole32.exp[444 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient13() { __asm { jmp ole32.exp[445 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient14() { __asm { jmp ole32.exp[446 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient15() { __asm { jmp ole32.exp[447 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient16() { __asm { jmp ole32.exp[448 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient17() { __asm { jmp ole32.exp[449 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient18() { __asm { jmp ole32.exp[450 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient19() { __asm { jmp ole32.exp[451 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient20() { __asm { jmp ole32.exp[452 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient21() { __asm { jmp ole32.exp[453 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient22() { __asm { jmp ole32.exp[454 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient23() { __asm { jmp ole32.exp[455 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient24() { __asm { jmp ole32.exp[456 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient25() { __asm { jmp ole32.exp[457 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient26() { __asm { jmp ole32.exp[458 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient27() { __asm { jmp ole32.exp[459 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient28() { __asm { jmp ole32.exp[460 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient29() { __asm { jmp ole32.exp[461 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient30() { __asm { jmp ole32.exp[462 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient31() { __asm { jmp ole32.exp[463 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient32() { __asm { jmp ole32.exp[464 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient3() { __asm { jmp ole32.exp[465 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient4() { __asm { jmp ole32.exp[466 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient5() { __asm { jmp ole32.exp[467 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient6() { __asm { jmp ole32.exp[468 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient7() { __asm { jmp ole32.exp[469 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient8() { __asm { jmp ole32.exp[470 * 4]} }
__declspec(naked) void Proxy_ObjectStublessClient9() { __asm { jmp ole32.exp[471 * 4]} }
__declspec(naked) void Proxy_ProgIDFromCLSID() { __asm { jmp ole32.exp[472 * 4]} }
__declspec(naked) void Proxy_RoGetAgileReference() { __asm { jmp ole32.exp[473 * 4]} }
__declspec(naked) void Proxy_SetErrorInfo() { __asm { jmp ole32.exp[474 * 4]} }
__declspec(naked) void Proxy_StringFromCLSID() { __asm { jmp ole32.exp[475 * 4]} }
__declspec(naked) void Proxy_StringFromGUID2() { __asm { jmp ole32.exp[476 * 4]} }
__declspec(naked) void Proxy_StringFromIID() { __asm { jmp ole32.exp[477 * 4]} }
__declspec(naked) void Proxy_UpdateDCOMSettings() { __asm { jmp ole32.exp[478 * 4]} }
__declspec(naked) void Proxy_UpdateProcessTracing() { __asm { jmp ole32.exp[479 * 4]} }
__declspec(naked) void Proxy_WdtpInterfacePointer_UserFree() { __asm { jmp ole32.exp[480 * 4]} }
__declspec(naked) void Proxy_WdtpInterfacePointer_UserMarshal() { __asm { jmp ole32.exp[481 * 4]} }
__declspec(naked) void Proxy_WdtpInterfacePointer_UserSize() { __asm { jmp ole32.exp[482 * 4]} }
__declspec(naked) void Proxy_WdtpInterfacePointer_UserUnmarshal() { __asm { jmp ole32.exp[483 * 4]} }
