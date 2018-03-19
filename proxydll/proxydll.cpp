// proxydll.cpp
#include "stdafx.h"
#include <stdio.h>
#include "myIDirect3D9.h"
#include "proxydll.h"
// global variables
#pragma data_seg (".d3d9_shared")
//myIDirect3DDevice9* gl_pmyIDirect3DDevice9;
myIDirect3D9* gl_pmyIDirect3D9;
HINSTANCE gl_hThisInstance;
#pragma data_seg ()


HMODULE dllModule;
HINSTANCE hExecutableInstance;
WCHAR* wc_DllPath = new WCHAR[MAX_PATH],
*wc_ExePath = new WCHAR[MAX_PATH],
*sz_SystemPath = new WCHAR[MAX_PATH],
*szSystemDllPath = new WCHAR[MAX_PATH];
PWCHAR 	pwc_dllName;
PWCHAR 	pwc_ExeName;

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

BYTE* memstr(BYTE * full_data, int full_data_len, BYTE * substr, int substr_len)
{
	//__try
	//{
	if (full_data == nullptr || full_data_len <= 0 || substr == nullptr || full_data_len<substr_len || substr_len>full_data_len) {
		return nullptr;
	}
	//DWORD dwOld;
	//VirtualProtect(full_data, full_data_len, PAGE_EXECUTE_READWRITE, &dwOld);


	int i;
	BYTE * cur = full_data;
	int last_possible = full_data_len - substr_len + 1;
	for (i = 0; i < last_possible; i++) {
		if (*cur == *substr) {
			//assert(full_data_len - i >= sublen);  
			if (!memcmp(cur, substr, substr_len)) {
				//found  
				return cur;
			}
		}
		cur++;
	}
	//VirtualProtect(full_data, full_data_len, dwOld, NULL);
	//}
	//__except (EXCEPTION_EXECUTE_HANDLER)
	//{
	//	return nullptr;
	//}
	return nullptr;
}

void SomeGameMod() {
	//L.A.Noire 60 fps unlock
	if (_tcsicmp(pwc_ExeName, L"LANoire.exe") == NULL) {
		//	int *a =(int*) 0x1957d4;
		//		*a = 0x1;
		;

		BYTE *pAddress = (BYTE *)0x00DF4AB7;

		DWORD dwOld;
		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		BYTE Hijack_spoof_2[7] = { 0xc6,0x40,0x04,0x01 ,0xc2,0x04,0x00 };

		memcpy_s(pAddress, 7, Hijack_spoof_2, 7);

		VirtualProtect(pAddress, 7, dwOld, NULL);

	}
	else if (_tcsicmp(pwc_ExeName, L"AC4BFSP.exe") == NULL) {


		BYTE *pAddress = (BYTE *)((size_t)GetModuleHandle(pwc_ExeName) + 0x35272);
		DWORD dwOld;
		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		*pAddress = 0x86;

		VirtualProtect(pAddress, 7, dwOld, NULL);
		pAddress = (BYTE *)((size_t)GetModuleHandle(pwc_ExeName) + 0x0006540);

		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		BYTE Hijack_spoof_2[6] = { 0xbe,0x00,0x00,0x00 ,0x80,0x90 };

		memcpy_s(pAddress, 6, Hijack_spoof_2, 6);

		VirtualProtect(pAddress, 7, dwOld, NULL);
	}
	else if (_tcsicmp(pwc_ExeName, L"AC3SP.exe") == NULL) {


		BYTE *pAddress = (BYTE *)((size_t)GetModuleHandle(pwc_ExeName) + (size_t)0x825FC);
		DWORD dwOld;
		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		*pAddress = 0x86;

		VirtualProtect(pAddress, 7, dwOld, NULL);

		pAddress = (BYTE *)((size_t)GetModuleHandle(pwc_ExeName) + (size_t)0x06440);

		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		BYTE Hijack_spoof_2[6] = { 0xbe,0x00,0x00,0x00 ,0x80,0x90 };

		memcpy_s(pAddress, 6, Hijack_spoof_2, 6);

		VirtualProtect(pAddress, 7, dwOld, NULL);
	}
	else if (_tcsicmp(pwc_ExeName, L"ACRSP.exe") == NULL) {

		DWORD dwOld;
		BYTE *pAddress = (BYTE *)((size_t)GetModuleHandle(pwc_ExeName) + (size_t)0xAFD7F);

		VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		BYTE Hijack_spoof_2[6] = { 0xe9,0x6c,0x02,0x00 ,0x00,0x90 };

		memcpy_s(pAddress, 6, Hijack_spoof_2, 6);

		VirtualProtect(pAddress, 7, dwOld, NULL);

		// pAddress = (BYTE *)0xE4FDDA;

		//VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		//*pAddress = 0xEB;
		//*(pAddress + 1) = 0x2C;

		//VirtualProtect(pAddress, 7, dwOld, NULL);

		//pAddress = (BYTE *)0xE4FEEF;

		//VirtualProtect(pAddress, 7, PAGE_EXECUTE_READWRITE, &dwOld);

		//*pAddress = 0xEB;
		//*(pAddress + 1) = 0x4D;

		//VirtualProtect(pAddress, 7, dwOld, NULL);
	}
	else {

		return;

	}

}


void InitInstance(HANDLE hModule)
{
	//	OutputDebugString("PROXYDLL: InitInstance called.\r\n");

		// Initialisation
	gl_hThisInstance = NULL;
	gl_pmyIDirect3D9 = NULL;
	//gl_pmyIDirect3DDevice9 = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)hModule;
}

HRESULT mod_CreatePixelShader(
	ID3D11Device *ppDevice,
	const void*pShaderBytecode,
	SIZE_T             BytecodeLength,
	ID3D11ClassLinkage *pClassLinkage,
	ID3D11PixelShader  **ppPixelShader
) {
	bool enableFxaa = true;
	if (!_tcsicmp(pwc_ExeName, L"AC3SP.exe")) {
		BYTE to_find[200];
		strcpy_s((char*)to_find, 15, "FxaaConsoleRcp");
		BYTE * found = memstr((BYTE*)pShaderBytecode, BytecodeLength, to_find, strlen((char*)to_find));
		if (found != nullptr&&
			BytecodeLength <= 5732
			) {
			enableFxaa = false;

		}

	}
	if (enableFxaa) {
		return ori_CreatePixelShader(
			ppDevice,
			pShaderBytecode,
			BytecodeLength,
			pClassLinkage,
			ppPixelShader);
	}
	else {

		if (false)
		{
			MessageBox(0, L"fxaa found",
				L"ASI Loader", MB_ICONINFORMATION);
			char* filename = new char[200];

			sprintf_s(filename, 200, "d:\\tmp\\PixelShader_dump_%d_size_%ld.bin", GetTickCount(), BytecodeLength);
			FILE *out;
			fopen_s(&out, filename, "wb");
			if (out != NULL)
			{
				size_t to_go = BytecodeLength;
				while (to_go > 0)
				{
					const size_t wrote = fwrite(pShaderBytecode, to_go, 1, out);
					if (wrote == 0)
						break;
					to_go -= wrote;
				}
				fclose(out);
			}
		}
		*ppPixelShader = NULL;
		return S_OK;
	}
}

void hook_D3D_Api(ID3D11Device **ppDevice) {

	void *vtb_ID3D11Device = *(void**)*ppDevice;

	void *tmp;

	tmp = (fn_CreatePixelShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreatePixelShader, 15);
	if (tmp != mod_CreatePixelShader) {

		//MessageBox(0, L"hook api",
		//	L"ASI Loader", MB_ICONINFORMATION);
		ori_CreatePixelShader = (fn_CreatePixelShader)tmp;
	}
	//tmp = (fn_CreateHullShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreateHullShader, 16);
	//if (tmp != mod_CreateHullShader) {
	//    ori_CreateHullShader = (fn_CreateHullShader)tmp;
	//}

	//tmp = (fn_CreateDomainShader)ReplaceVtblFunction(vtb_ID3D11Device, mod_CreateDomainShader, 17);
	//if (tmp != mod_CreateDomainShader) {
	//    ori_CreateDomainShader = (fn_CreateDomainShader)tmp;
	//}
	//hooked = true;

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

	HRESULT hr


		= ori_D3D11CreateDevice(pAdapter, DriverType, Software,
			Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice
			, pFeatureLevel, ppImmediateContext);

	hook_D3D_Api(ppDevice);
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

	hook_D3D_Api(ppDevice);
	return hr;
}

HRESULT mod_DirectInput8Create(
	HINSTANCE hinst,
	DWORD dwVersion,
	REFIID riidltf,
	LPVOID * ppvOut,
	LPUNKNOWN punkOuter
) {

	typedef HRESULT(*fn_DirectInput8Create)(
		HINSTANCE,
		DWORD,
		REFIID,
		LPVOID *,
		LPUNKNOWN);
	fn_DirectInput8Create ori_DirectInput8Create
		= (fn_DirectInput8Create)GetProcAddress(dinput8.dll, "DirectInput8Create");

	HRESULT hr = ori_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	if (_tcsicmp(pwc_ExeName, L"Conviction_game.exe") == NULL) {
		//MessageBox(0, L"Conviction_game found",
		//	L"ASI Loader", MB_ICONINFORMATION);
		SetWindowLongPtr(NULL, GWL_STYLE, WS_POPUP | WS_DISABLED);
	}

	return hr;
}

void Redirect(PWCHAR name)
{

	wcscpy_s(szSystemDllPath, MAX_PATH, sz_SystemPath);

	wcscat_s(szSystemDllPath, MAX_PATH, L"\\");

	wcscat_s(szSystemDllPath, MAX_PATH, name);


	PWCHAR DllName = name;

	if (_tcsicmp(DllName, L"dsound.dll") == NULL) {
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
	else if (_tcsicmp(DllName, L"dinput8.dll") == NULL) {
		dinput8.dll = LoadLibrary(szSystemDllPath);
		//dinput8.DirectInput8Create = GetProcAddress(dinput8.dll, "DirectInput8Create");
		dinput8.DirectInput8Create = (FARPROC)mod_DirectInput8Create;
		dinput8.DllCanUnloadNow = GetProcAddress(dinput8.dll, "DllCanUnloadNow");
		dinput8.DllGetClassObject = GetProcAddress(dinput8.dll, "DllGetClassObject");
		dinput8.DllRegisterServer = GetProcAddress(dinput8.dll, "DllRegisterServer");
		dinput8.DllUnregisterServer = GetProcAddress(dinput8.dll, "DllUnregisterServer");
	}
	else if (_tcsicmp(DllName, L"ddraw.dll") == NULL) {
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
	else if (_tcsicmp(DllName, L"d3d8.dll") == NULL) {
		d3d8.dll = LoadLibrary(szSystemDllPath);
		d3d8.DebugSetMute_d3d8 = GetProcAddress(d3d8.dll, "DebugSetMute_d3d8");
		d3d8.Direct3DCreate8 = GetProcAddress(d3d8.dll, "Direct3DCreate8");
		d3d8.ValidatePixelShader = GetProcAddress(d3d8.dll, "ValidatePixelShader");
		d3d8.ValidateVertexShader = GetProcAddress(d3d8.dll, "ValidateVertexShader");
	}
	else if (_tcsicmp(DllName, L"ole32.dll") == NULL) {
		ole32.dll = LoadLibrary(szSystemDllPath);
		ole32.exp[0] = GetProcAddress(ole32.dll, "CreateFileMoniker");
		ole32.exp[1] = GetProcAddress(ole32.dll, "DestroyRunningObjectTable");
		ole32.exp[2] = GetProcAddress(ole32.dll, "Ordinal800");
		ole32.exp[3] = GetProcAddress(ole32.dll, "OleFlushClipboard");
		ole32.exp[4] = GetProcAddress(ole32.dll, "OleSetClipboard");
		ole32.exp[5] = GetProcAddress(ole32.dll, "OleQueryLinkFromData");
		ole32.exp[6] = GetProcAddress(ole32.dll, "OleGetClipboard");
		ole32.exp[7] = GetProcAddress(ole32.dll, "OleIsCurrentClipboard");
		ole32.exp[8] = GetProcAddress(ole32.dll, "OleCreateFontIndirectExt");
		ole32.exp[9] = GetProcAddress(ole32.dll, "ReadFmtUserTypeStg");
		ole32.exp[10] = GetProcAddress(ole32.dll, "WriteFmtUserTypeStg");
		ole32.exp[11] = GetProcAddress(ole32.dll, "WriteStringStream");
		ole32.exp[12] = GetProcAddress(ole32.dll, "RegisterActiveObjectExt");
		ole32.exp[13] = GetProcAddress(ole32.dll, "GetActiveObjectExt");
		ole32.exp[14] = GetProcAddress(ole32.dll, "CoAllowSetForegroundWindow");
		ole32.exp[15] = GetProcAddress(ole32.dll, "OleRun");
		ole32.exp[16] = GetProcAddress(ole32.dll, "CreateClassMoniker");
		ole32.exp[17] = GetProcAddress(ole32.dll, "OleSave");
		ole32.exp[18] = GetProcAddress(ole32.dll, "RevokeActiveObjectExt");
		ole32.exp[19] = GetProcAddress(ole32.dll, "StgCreateStorageEx");
		ole32.exp[20] = GetProcAddress(ole32.dll, "StgCreateDocfileOnILockBytes");
		ole32.exp[21] = GetProcAddress(ole32.dll, "StgIsStorageFile");
		ole32.exp[22] = GetProcAddress(ole32.dll, "StgOpenStorageEx");
		ole32.exp[23] = GetProcAddress(ole32.dll, "StgOpenStorageOnILockBytes");
		ole32.exp[24] = GetProcAddress(ole32.dll, "WriteClassStg");
		ole32.exp[25] = GetProcAddress(ole32.dll, "StgCreateDocfile");
		ole32.exp[26] = GetProcAddress(ole32.dll, "CoBuildVersion");
		ole32.exp[27] = GetProcAddress(ole32.dll, "OleBuildVersion");
		ole32.exp[28] = GetProcAddress(ole32.dll, "Ordinal801");
		ole32.exp[29] = GetProcAddress(ole32.dll, "Ordinal803");
		ole32.exp[30] = GetProcAddress(ole32.dll, "CreateItemMoniker");
		ole32.exp[31] = GetProcAddress(ole32.dll, "RevokeDragDrop");
		ole32.exp[32] = GetProcAddress(ole32.dll, "CreateDataAdviseHolder");
		ole32.exp[33] = GetProcAddress(ole32.dll, "OleUninitialize");
		ole32.exp[34] = GetProcAddress(ole32.dll, "RegisterDragDrop");
		ole32.exp[35] = GetProcAddress(ole32.dll, "CheckInitDde");
		ole32.exp[36] = GetProcAddress(ole32.dll, "ClipboardProcessUninitialize");
		ole32.exp[37] = GetProcAddress(ole32.dll, "OleInitialize");
		ole32.exp[38] = GetProcAddress(ole32.dll, "CleanROTForApartment");
		ole32.exp[39] = GetProcAddress(ole32.dll, "CoGetObject");
		ole32.exp[40] = GetProcAddress(ole32.dll, "Ole32DllGetClassObject");
		ole32.exp[41] = GetProcAddress(ole32.dll, "DllGetClassObject");
		ole32.exp[42] = GetProcAddress(ole32.dll, "DllGetClassObjectWOW");
		ole32.exp[43] = GetProcAddress(ole32.dll, "CreateGenericComposite");
		ole32.exp[44] = GetProcAddress(ole32.dll, "MkParseDisplayName");
		ole32.exp[45] = GetProcAddress(ole32.dll, "IsEqualGUID");
		ole32.exp[46] = GetProcAddress(ole32.dll, "CoGetInterceptorForOle32");
		ole32.exp[47] = GetProcAddress(ole32.dll, "CreateBindCtx");
		ole32.exp[48] = GetProcAddress(ole32.dll, "IsValidInterface");
		ole32.exp[49] = GetProcAddress(ole32.dll, "GetRunningObjectTable");
		ole32.exp[50] = GetProcAddress(ole32.dll, "ReleaseStgMedium");
		ole32.exp[51] = GetProcAddress(ole32.dll, "OleRegGetMiscStatus");
		ole32.exp[52] = GetProcAddress(ole32.dll, "CoInitialize");
		ole32.exp[53] = GetProcAddress(ole32.dll, "StgOpenStorage");
		ole32.exp[54] = GetProcAddress(ole32.dll, "OleTranslateColorExt");
		ole32.exp[55] = GetProcAddress(ole32.dll, "SetOleautModule");
		ole32.exp[56] = GetProcAddress(ole32.dll, "OleReleaseEnumVerbCache");
		ole32.exp[57] = GetProcAddress(ole32.dll, "CreatePointerMoniker");
		ole32.exp[58] = GetProcAddress(ole32.dll, "BindMoniker");
		ole32.exp[59] = GetProcAddress(ole32.dll, "StoreQITableEntry");
		ole32.exp[60] = GetProcAddress(ole32.dll, "OleSaveToStream");
		ole32.exp[61] = GetProcAddress(ole32.dll, "ClearQITableEntry");
		ole32.exp[62] = GetProcAddress(ole32.dll, "ComPs_NdrDllCanUnloadNow");
		ole32.exp[63] = GetProcAddress(ole32.dll, "IsValidIid");
		ole32.exp[64] = GetProcAddress(ole32.dll, "CoSetState");
		ole32.exp[65] = GetProcAddress(ole32.dll, "HWND_UserFreeExt");
		ole32.exp[66] = GetProcAddress(ole32.dll, "CoFreeAllLibraries");
		ole32.exp[67] = GetProcAddress(ole32.dll, "CreateStdProgressIndicator");
		ole32.exp[68] = GetProcAddress(ole32.dll, "CoGetInterceptorFromTypeInfo");
		ole32.exp[69] = GetProcAddress(ole32.dll, "OleLockRunning");
		ole32.exp[70] = GetProcAddress(ole32.dll, "CreateOleAdviseHolder");
		ole32.exp[71] = GetProcAddress(ole32.dll, "ReadClassStm");
		ole32.exp[72] = GetProcAddress(ole32.dll, "FreePropVariantArray");
		ole32.exp[73] = GetProcAddress(ole32.dll, "PropVariantClear");
		ole32.exp[74] = GetProcAddress(ole32.dll, "PropVariantCopy");
		ole32.exp[75] = GetProcAddress(ole32.dll, "CoInitializeWOW");
		ole32.exp[76] = GetProcAddress(ole32.dll, "CoRegisterMessageFilter");
		ole32.exp[77] = GetProcAddress(ole32.dll, "CoRegisterSurrogateEx");
		ole32.exp[78] = GetProcAddress(ole32.dll, "CoUnloadingWOW");
		ole32.exp[79] = GetProcAddress(ole32.dll, "DllRegisterServer");
		ole32.exp[80] = GetProcAddress(ole32.dll, "CoAicGetTokenForCOM");
		ole32.exp[81] = GetProcAddress(ole32.dll, "CoCheckElevationEnabled");
		ole32.exp[82] = GetProcAddress(ole32.dll, "CoGetSystemWow64DirectoryW");
		ole32.exp[83] = GetProcAddress(ole32.dll, "DeletePatternAndExtensionTables");
		ole32.exp[84] = GetProcAddress(ole32.dll, "SetWOWThunkGlobalPtr");
		ole32.exp[85] = GetProcAddress(ole32.dll, "CreateILockBytesOnHGlobal");
		ole32.exp[86] = GetProcAddress(ole32.dll, "FmtIdToPropStgName");
		ole32.exp[87] = GetProcAddress(ole32.dll, "GetConvertStg");
		ole32.exp[88] = GetProcAddress(ole32.dll, "GetDocumentBitStg");
		ole32.exp[89] = GetProcAddress(ole32.dll, "GetHGlobalFromILockBytes");
		ole32.exp[90] = GetProcAddress(ole32.dll, "PropStgNameToFmtId");
		ole32.exp[91] = GetProcAddress(ole32.dll, "PropSysAllocString");
		ole32.exp[92] = GetProcAddress(ole32.dll, "PropSysFreeString");
		ole32.exp[93] = GetProcAddress(ole32.dll, "PropVariantChangeType");
		ole32.exp[94] = GetProcAddress(ole32.dll, "StgConvertPropertyToVariant");
		ole32.exp[95] = GetProcAddress(ole32.dll, "StgConvertVariantToProperty");
		ole32.exp[96] = GetProcAddress(ole32.dll, "StgCreatePropSetStg");
		ole32.exp[97] = GetProcAddress(ole32.dll, "StgCreatePropStg");
		ole32.exp[98] = GetProcAddress(ole32.dll, "StgGetIFillLockBytesOnFile");
		ole32.exp[99] = GetProcAddress(ole32.dll, "StgGetIFillLockBytesOnILockBytes");
		ole32.exp[100] = GetProcAddress(ole32.dll, "StgIsStorageILockBytes");
		ole32.exp[101] = GetProcAddress(ole32.dll, "StgOpenAsyncDocfileOnIFillLockBytes");
		ole32.exp[102] = GetProcAddress(ole32.dll, "StgOpenPropStg");
		ole32.exp[103] = GetProcAddress(ole32.dll, "StgOpenStorageOnHandle");
		ole32.exp[104] = GetProcAddress(ole32.dll, "StgPropertyLengthAsVariant");
		ole32.exp[105] = GetProcAddress(ole32.dll, "StgSetTimes");
		ole32.exp[106] = GetProcAddress(ole32.dll, "WriteClassStm");
		ole32.exp[107] = GetProcAddress(ole32.dll, "CreateAntiMoniker");
		ole32.exp[108] = GetProcAddress(ole32.dll, "CreateObjrefMoniker");
		ole32.exp[109] = GetProcAddress(ole32.dll, "OleLoadFromStream");
		ole32.exp[110] = GetProcAddress(ole32.dll, "MonikerCommonPrefixWith");
		ole32.exp[111] = GetProcAddress(ole32.dll, "MonikerRelativePathTo");
		ole32.exp[112] = GetProcAddress(ole32.dll, "FindExt");
		ole32.exp[113] = GetProcAddress(ole32.dll, "GetClassFile");
		ole32.exp[114] = GetProcAddress(ole32.dll, "CoFreeLibrary");
		ole32.exp[115] = GetProcAddress(ole32.dll, "CoInstall");
		ole32.exp[116] = GetProcAddress(ole32.dll, "CoLoadLibrary");
		ole32.exp[117] = GetProcAddress(ole32.dll, "CoQueryReleaseObject");
		ole32.exp[118] = GetProcAddress(ole32.dll, "IsRoInitializeASTAAllowedInDesktop");
		ole32.exp[119] = GetProcAddress(ole32.dll, "CoIsOle1Class");
		ole32.exp[120] = GetProcAddress(ole32.dll, "CoTreatAsClass");
		ole32.exp[121] = GetProcAddress(ole32.dll, "IsValidPtrIn");
		ole32.exp[122] = GetProcAddress(ole32.dll, "IsValidPtrOut");
		ole32.exp[123] = GetProcAddress(ole32.dll, "CoDosDateTimeToFileTime");
		ole32.exp[124] = GetProcAddress(ole32.dll, "CoFileTimeToDosDateTime");
		ole32.exp[125] = GetProcAddress(ole32.dll, "HENHMETAFILE_UserFree");
		ole32.exp[126] = GetProcAddress(ole32.dll, "HENHMETAFILE_UserMarshal");
		ole32.exp[127] = GetProcAddress(ole32.dll, "HENHMETAFILE_UserSize");
		ole32.exp[128] = GetProcAddress(ole32.dll, "HENHMETAFILE_UserUnmarshal");
		ole32.exp[129] = GetProcAddress(ole32.dll, "HMETAFILEPICT_UserFree");
		ole32.exp[130] = GetProcAddress(ole32.dll, "HMETAFILEPICT_UserMarshal");
		ole32.exp[131] = GetProcAddress(ole32.dll, "HMETAFILEPICT_UserSize");
		ole32.exp[132] = GetProcAddress(ole32.dll, "HMETAFILEPICT_UserUnmarshal");
		ole32.exp[133] = GetProcAddress(ole32.dll, "HMETAFILE_UserFree");
		ole32.exp[134] = GetProcAddress(ole32.dll, "HMETAFILE_UserMarshal");
		ole32.exp[135] = GetProcAddress(ole32.dll, "HMETAFILE_UserSize");
		ole32.exp[136] = GetProcAddress(ole32.dll, "HMETAFILE_UserUnmarshal");
		ole32.exp[137] = GetProcAddress(ole32.dll, "SNB_UserFree");
		ole32.exp[138] = GetProcAddress(ole32.dll, "SNB_UserMarshal");
		ole32.exp[139] = GetProcAddress(ole32.dll, "SNB_UserSize");
		ole32.exp[140] = GetProcAddress(ole32.dll, "SNB_UserUnmarshal");
		ole32.exp[141] = GetProcAddress(ole32.dll, "STGMEDIUM_UserFree");
		ole32.exp[142] = GetProcAddress(ole32.dll, "STGMEDIUM_UserMarshal");
		ole32.exp[143] = GetProcAddress(ole32.dll, "STGMEDIUM_UserSize");
		ole32.exp[144] = GetProcAddress(ole32.dll, "STGMEDIUM_UserUnmarshal");
		ole32.exp[145] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserFreeExt");
		ole32.exp[146] = GetProcAddress(ole32.dll, "HWND_UserUnmarshalExt");
		ole32.exp[147] = GetProcAddress(ole32.dll, "HWND_UserMarshalExt");
		ole32.exp[148] = GetProcAddress(ole32.dll, "HWND_UserSizeExt");
		ole32.exp[149] = GetProcAddress(ole32.dll, "CoGetInterceptor");
		ole32.exp[150] = GetProcAddress(ole32.dll, "ComPs_NdrDllGetClassObject");
		ole32.exp[151] = GetProcAddress(ole32.dll, "ComPs_NdrDllRegisterProxy");
		ole32.exp[152] = GetProcAddress(ole32.dll, "ComPs_NdrDllUnregisterProxy");
		ole32.exp[153] = GetProcAddress(ole32.dll, "GetObjectFromRotByPath");
		ole32.exp[154] = GetProcAddress(ole32.dll, "DdeBindToObject");
		ole32.exp[155] = GetProcAddress(ole32.dll, "OleCreate");
		ole32.exp[156] = GetProcAddress(ole32.dll, "OleCreateEx");
		ole32.exp[157] = GetProcAddress(ole32.dll, "OleCreateFromData");
		ole32.exp[158] = GetProcAddress(ole32.dll, "OleCreateFromDataEx");
		ole32.exp[159] = GetProcAddress(ole32.dll, "OleCreateFromFile");
		ole32.exp[160] = GetProcAddress(ole32.dll, "OleCreateFromFileEx");
		ole32.exp[161] = GetProcAddress(ole32.dll, "OleCreateLink");
		ole32.exp[162] = GetProcAddress(ole32.dll, "OleCreateLinkEx");
		ole32.exp[163] = GetProcAddress(ole32.dll, "OleCreateLinkFromData");
		ole32.exp[164] = GetProcAddress(ole32.dll, "OleCreateLinkFromDataEx");
		ole32.exp[165] = GetProcAddress(ole32.dll, "OleCreateLinkToFile");
		ole32.exp[166] = GetProcAddress(ole32.dll, "OleCreateLinkToFileEx");
		ole32.exp[167] = GetProcAddress(ole32.dll, "OleCreateStaticFromData");
		ole32.exp[168] = GetProcAddress(ole32.dll, "OleDoAutoConvert");
		ole32.exp[169] = GetProcAddress(ole32.dll, "OleLoad");
		ole32.exp[170] = GetProcAddress(ole32.dll, "OleQueryCreateFromData");
		ole32.exp[171] = GetProcAddress(ole32.dll, "OleDraw");
		ole32.exp[172] = GetProcAddress(ole32.dll, "OleDuplicateData");
		ole32.exp[173] = GetProcAddress(ole32.dll, "OleIsRunning");
		ole32.exp[174] = GetProcAddress(ole32.dll, "OleNoteObjectVisible");
		ole32.exp[175] = GetProcAddress(ole32.dll, "OleSetContainedObject");
		ole32.exp[176] = GetProcAddress(ole32.dll, "ReadOleStg");
		ole32.exp[177] = GetProcAddress(ole32.dll, "SetConvertStg");
		ole32.exp[178] = GetProcAddress(ole32.dll, "SetDocumentBitStg");
		ole32.exp[179] = GetProcAddress(ole32.dll, "WriteOleStg");
		ole32.exp[180] = GetProcAddress(ole32.dll, "OleInitializeWOW");
		ole32.exp[181] = GetProcAddress(ole32.dll, "CreateDataCache");
		ole32.exp[182] = GetProcAddress(ole32.dll, "OleGetClipboardWithEnterpriseInfo");
		ole32.exp[183] = GetProcAddress(ole32.dll, "Ordinal804");
		ole32.exp[184] = GetProcAddress(ole32.dll, "OleGetPackageClipboardOwner");
		ole32.exp[185] = GetProcAddress(ole32.dll, "DoDragDrop");
		ole32.exp[186] = GetProcAddress(ole32.dll, "DragDropSetFDT");
		ole32.exp[187] = GetProcAddress(ole32.dll, "Ordinal822");
		ole32.exp[188] = GetProcAddress(ole32.dll, "Ordinal820");
		ole32.exp[189] = GetProcAddress(ole32.dll, "Ordinal821");
		ole32.exp[190] = GetProcAddress(ole32.dll, "Ordinal823");
		ole32.exp[191] = GetProcAddress(ole32.dll, "IsAccelerator");
		ole32.exp[192] = GetProcAddress(ole32.dll, "OleCreateMenuDescriptor");
		ole32.exp[193] = GetProcAddress(ole32.dll, "OleDestroyMenuDescriptor");
		ole32.exp[194] = GetProcAddress(ole32.dll, "OleSetMenuDescriptor");
		ole32.exp[195] = GetProcAddress(ole32.dll, "OleTranslateAccelerator");
		ole32.exp[196] = GetProcAddress(ole32.dll, "OleCreateDefaultHandler");
		ole32.exp[197] = GetProcAddress(ole32.dll, "OleCreateEmbeddingHelper");
		ole32.exp[198] = GetProcAddress(ole32.dll, "OleGetAutoConvert");
		ole32.exp[199] = GetProcAddress(ole32.dll, "OleRegGetUserType");
		ole32.exp[200] = GetProcAddress(ole32.dll, "OleSetAutoConvert");
		ole32.exp[201] = GetProcAddress(ole32.dll, "OleGetIconOfClass");
		ole32.exp[202] = GetProcAddress(ole32.dll, "OleGetIconOfFile");
		ole32.exp[203] = GetProcAddress(ole32.dll, "OleMetafilePictFromIconAndLabel");
		ole32.exp[204] = GetProcAddress(ole32.dll, "OleRegEnumFormatEtc");
		ole32.exp[205] = GetProcAddress(ole32.dll, "OleRegEnumVerbs");
		ole32.exp[206] = GetProcAddress(ole32.dll, "OleConvertIStorageToOLESTREAM");
		ole32.exp[207] = GetProcAddress(ole32.dll, "OleConvertIStorageToOLESTREAMEx");
		ole32.exp[208] = GetProcAddress(ole32.dll, "OleConvertOLESTREAMToIStorage");
		ole32.exp[209] = GetProcAddress(ole32.dll, "OleConvertOLESTREAMToIStorageEx");
		ole32.exp[210] = GetProcAddress(ole32.dll, "OpenOrCreateStream");
		ole32.exp[211] = GetProcAddress(ole32.dll, "ReadStringStream");
		ole32.exp[212] = GetProcAddress(ole32.dll, "UtConvertDvtd16toDvtd32");
		ole32.exp[213] = GetProcAddress(ole32.dll, "UtConvertDvtd32toDvtd16");
		ole32.exp[214] = GetProcAddress(ole32.dll, "UtGetDvtd16Info");
		ole32.exp[215] = GetProcAddress(ole32.dll, "UtGetDvtd32Info");
		ole32.exp[216] = GetProcAddress(ole32.dll, "StdTypesGetClassObject");
		ole32.exp[217] = GetProcAddress(ole32.dll, "StdTypesRegisterServer");
		ole32.exp[218] = GetProcAddress(ole32.dll, "OleCreatePictureIndirectExt");
		ole32.exp[219] = GetProcAddress(ole32.dll, "OleIconToCursorExt");
		ole32.exp[220] = GetProcAddress(ole32.dll, "OleLoadPictureExt");
		ole32.exp[221] = GetProcAddress(ole32.dll, "OleLoadPicturePathExt");
		ole32.exp[222] = GetProcAddress(ole32.dll, "OleCreatePropertyFrameIndirectExt");
		ole32.exp[223] = GetProcAddress(ole32.dll, "OleLoadPictureFileExt");
		ole32.exp[224] = GetProcAddress(ole32.dll, "OleSavePictureFileExt");
		ole32.exp[225] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserMarshalExt");
		ole32.exp[226] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserSizeExt");
		ole32.exp[227] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserUnmarshalExt");
		ole32.exp[228] = GetProcAddress(ole32.dll, "HPALETTE_UserFreeExt");
		ole32.exp[229] = GetProcAddress(ole32.dll, "HPALETTE_UserMarshalExt");
		ole32.exp[230] = GetProcAddress(ole32.dll, "HPALETTE_UserSizeExt");
		ole32.exp[231] = GetProcAddress(ole32.dll, "HPALETTE_UserUnmarshalExt");
		ole32.exp[232] = GetProcAddress(ole32.dll, "MonikerLoadTypeLib");
		ole32.exp[233] = GetProcAddress(ole32.dll, "ReadStorageProperties");
		ole32.exp[234] = GetProcAddress(ole32.dll, "ReadClassStg");
		ole32.exp[235] = GetProcAddress(ole32.dll, "STGMEDIUM_UserFreeExt");
		ole32.exp[236] = GetProcAddress(ole32.dll, "STGMEDIUM_UserMarshalExt");
		ole32.exp[237] = GetProcAddress(ole32.dll, "STGMEDIUM_UserSizeExt");
		ole32.exp[238] = GetProcAddress(ole32.dll, "STGMEDIUM_UserUnmarshalExt");
		ole32.exp[239] = GetProcAddress(ole32.dll, "WriteStorageProperties");
		ole32.exp[240] = GetProcAddress(ole32.dll, "HRGN_UserFree");
		ole32.exp[241] = GetProcAddress(ole32.dll, "HRGN_UserMarshal");
		ole32.exp[242] = GetProcAddress(ole32.dll, "HRGN_UserSize");
		ole32.exp[243] = GetProcAddress(ole32.dll, "HRGN_UserUnmarshal");
		ole32.exp[244] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserFree");
		ole32.exp[245] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserMarshal");
		ole32.exp[246] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserSize");
		ole32.exp[247] = GetProcAddress(ole32.dll, "CLIPFORMAT_UserUnmarshal");
		ole32.exp[248] = GetProcAddress(ole32.dll, "CLSIDFromOle1Class");
		ole32.exp[249] = GetProcAddress(ole32.dll, "CLSIDFromProgID");
		ole32.exp[250] = GetProcAddress(ole32.dll, "CLSIDFromProgIDEx");
		ole32.exp[251] = GetProcAddress(ole32.dll, "CLSIDFromString");
		ole32.exp[252] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer2_Connect");
		ole32.exp[253] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer2_Disconnect");
		ole32.exp[254] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer2_Release");
		ole32.exp[255] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_AddRef");
		ole32.exp[256] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_Connect");
		ole32.exp[257] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_Disconnect");
		ole32.exp[258] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_Invoke");
		ole32.exp[259] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_QueryInterface");
		ole32.exp[260] = GetProcAddress(ole32.dll, "CStdAsyncStubBuffer_Release");
		ole32.exp[261] = GetProcAddress(ole32.dll, "CStdStubBuffer2_Connect");
		ole32.exp[262] = GetProcAddress(ole32.dll, "CStdStubBuffer2_CountRefs");
		ole32.exp[263] = GetProcAddress(ole32.dll, "CStdStubBuffer2_Disconnect");
		ole32.exp[264] = GetProcAddress(ole32.dll, "CStdStubBuffer2_QueryInterface");
		ole32.exp[265] = GetProcAddress(ole32.dll, "CoAddRefServerProcess");
		ole32.exp[266] = GetProcAddress(ole32.dll, "CoAllowUnmarshalerCLSID");
		ole32.exp[267] = GetProcAddress(ole32.dll, "CoCancelCall");
		ole32.exp[268] = GetProcAddress(ole32.dll, "CoCopyProxy");
		ole32.exp[269] = GetProcAddress(ole32.dll, "CoCreateFreeThreadedMarshaler");
		ole32.exp[270] = GetProcAddress(ole32.dll, "CoCreateGuid");
		ole32.exp[271] = GetProcAddress(ole32.dll, "CoCreateInstance");
		ole32.exp[272] = GetProcAddress(ole32.dll, "CoCreateInstanceEx");
		ole32.exp[273] = GetProcAddress(ole32.dll, "CoCreateInstanceFromApp");
		ole32.exp[274] = GetProcAddress(ole32.dll, "CoCreateObjectInContext");
		ole32.exp[275] = GetProcAddress(ole32.dll, "CoDeactivateObject");
		ole32.exp[276] = GetProcAddress(ole32.dll, "CoDecodeProxy");
		ole32.exp[277] = GetProcAddress(ole32.dll, "CoDecrementMTAUsage");
		ole32.exp[278] = GetProcAddress(ole32.dll, "CoDisableCallCancellation");
		ole32.exp[279] = GetProcAddress(ole32.dll, "CoDisconnectContext");
		ole32.exp[280] = GetProcAddress(ole32.dll, "CoDisconnectObject");
		ole32.exp[281] = GetProcAddress(ole32.dll, "CoEnableCallCancellation");
		ole32.exp[282] = GetProcAddress(ole32.dll, "CoFileTimeNow");
		ole32.exp[283] = GetProcAddress(ole32.dll, "CoFreeUnusedLibraries");
		ole32.exp[284] = GetProcAddress(ole32.dll, "CoFreeUnusedLibrariesEx");
		ole32.exp[285] = GetProcAddress(ole32.dll, "CoGetActivationState");
		ole32.exp[286] = GetProcAddress(ole32.dll, "CoGetApartmentID");
		ole32.exp[287] = GetProcAddress(ole32.dll, "CoGetApartmentType");
		ole32.exp[288] = GetProcAddress(ole32.dll, "CoGetCallContext");
		ole32.exp[289] = GetProcAddress(ole32.dll, "CoGetCallState");
		ole32.exp[290] = GetProcAddress(ole32.dll, "CoGetCallerTID");
		ole32.exp[291] = GetProcAddress(ole32.dll, "CoGetCancelObject");
		ole32.exp[292] = GetProcAddress(ole32.dll, "CoGetClassObject");
		ole32.exp[293] = GetProcAddress(ole32.dll, "CoGetClassVersion");
		ole32.exp[294] = GetProcAddress(ole32.dll, "CoGetComCatalog");
		ole32.exp[295] = GetProcAddress(ole32.dll, "CoGetContextToken");
		ole32.exp[296] = GetProcAddress(ole32.dll, "CoGetCurrentLogicalThreadId");
		ole32.exp[297] = GetProcAddress(ole32.dll, "CoGetCurrentProcess");
		ole32.exp[298] = GetProcAddress(ole32.dll, "CoGetDefaultContext");
		ole32.exp[299] = GetProcAddress(ole32.dll, "CoGetInstanceFromFile");
		ole32.exp[300] = GetProcAddress(ole32.dll, "CoGetInstanceFromIStorage");
		ole32.exp[301] = GetProcAddress(ole32.dll, "CoGetInterfaceAndReleaseStream");
		ole32.exp[302] = GetProcAddress(ole32.dll, "CoGetMalloc");
		ole32.exp[303] = GetProcAddress(ole32.dll, "CoGetMarshalSizeMax");
		ole32.exp[304] = GetProcAddress(ole32.dll, "CoGetModuleType");
		ole32.exp[305] = GetProcAddress(ole32.dll, "CoGetObjectContext");
		ole32.exp[306] = GetProcAddress(ole32.dll, "CoGetPSClsid");
		ole32.exp[307] = GetProcAddress(ole32.dll, "CoGetProcessIdentifier");
		ole32.exp[308] = GetProcAddress(ole32.dll, "CoGetStandardMarshal");
		ole32.exp[309] = GetProcAddress(ole32.dll, "CoGetStdMarshalEx");
		ole32.exp[310] = GetProcAddress(ole32.dll, "CoGetSystemSecurityPermissions");
		ole32.exp[311] = GetProcAddress(ole32.dll, "CoGetTreatAsClass");
		ole32.exp[312] = GetProcAddress(ole32.dll, "CoHandlePriorityEventsFromMessagePump");
		ole32.exp[313] = GetProcAddress(ole32.dll, "CoImpersonateClient");
		ole32.exp[314] = GetProcAddress(ole32.dll, "CoIncrementMTAUsage");
		ole32.exp[315] = GetProcAddress(ole32.dll, "CoInitializeEx");
		ole32.exp[316] = GetProcAddress(ole32.dll, "CoInitializeSecurity");
		ole32.exp[317] = GetProcAddress(ole32.dll, "CoInvalidateRemoteMachineBindings");
		ole32.exp[318] = GetProcAddress(ole32.dll, "CoIsHandlerConnected");
		ole32.exp[319] = GetProcAddress(ole32.dll, "CoLockObjectExternal");
		ole32.exp[320] = GetProcAddress(ole32.dll, "CoMarshalHresult");
		ole32.exp[321] = GetProcAddress(ole32.dll, "CoMarshalInterThreadInterfaceInStream");
		ole32.exp[322] = GetProcAddress(ole32.dll, "CoMarshalInterface");
		ole32.exp[323] = GetProcAddress(ole32.dll, "CoPopServiceDomain");
		ole32.exp[324] = GetProcAddress(ole32.dll, "CoPushServiceDomain");
		ole32.exp[325] = GetProcAddress(ole32.dll, "CoQueryAuthenticationServices");
		ole32.exp[326] = GetProcAddress(ole32.dll, "CoQueryClientBlanket");
		ole32.exp[327] = GetProcAddress(ole32.dll, "CoQueryProxyBlanket");
		ole32.exp[328] = GetProcAddress(ole32.dll, "CoReactivateObject");
		ole32.exp[329] = GetProcAddress(ole32.dll, "CoRegisterActivationFilter");
		ole32.exp[330] = GetProcAddress(ole32.dll, "CoRegisterChannelHook");
		ole32.exp[331] = GetProcAddress(ole32.dll, "CoRegisterClassObject");
		ole32.exp[332] = GetProcAddress(ole32.dll, "CoRegisterInitializeSpy");
		ole32.exp[333] = GetProcAddress(ole32.dll, "CoRegisterMallocSpy");
		ole32.exp[334] = GetProcAddress(ole32.dll, "CoRegisterPSClsid");
		ole32.exp[335] = GetProcAddress(ole32.dll, "CoRegisterSurrogate");
		ole32.exp[336] = GetProcAddress(ole32.dll, "CoReleaseMarshalData");
		ole32.exp[337] = GetProcAddress(ole32.dll, "CoReleaseServerProcess");
		ole32.exp[338] = GetProcAddress(ole32.dll, "CoResumeClassObjects");
		ole32.exp[339] = GetProcAddress(ole32.dll, "CoRetireServer");
		ole32.exp[340] = GetProcAddress(ole32.dll, "CoRevertToSelf");
		ole32.exp[341] = GetProcAddress(ole32.dll, "CoRevokeClassObject");
		ole32.exp[342] = GetProcAddress(ole32.dll, "CoRevokeInitializeSpy");
		ole32.exp[343] = GetProcAddress(ole32.dll, "CoRevokeMallocSpy");
		ole32.exp[344] = GetProcAddress(ole32.dll, "CoSetCancelObject");
		ole32.exp[345] = GetProcAddress(ole32.dll, "CoSetMessageDispatcher");
		ole32.exp[346] = GetProcAddress(ole32.dll, "CoSetProxyBlanket");
		ole32.exp[347] = GetProcAddress(ole32.dll, "CoSuspendClassObjects");
		ole32.exp[348] = GetProcAddress(ole32.dll, "CoSwitchCallContext");
		ole32.exp[349] = GetProcAddress(ole32.dll, "CoTaskMemAlloc");
		ole32.exp[350] = GetProcAddress(ole32.dll, "CoTaskMemFree");
		ole32.exp[351] = GetProcAddress(ole32.dll, "CoTaskMemRealloc");
		ole32.exp[352] = GetProcAddress(ole32.dll, "CoTestCancel");
		ole32.exp[353] = GetProcAddress(ole32.dll, "CoUninitialize");
		ole32.exp[354] = GetProcAddress(ole32.dll, "CoUnmarshalHresult");
		ole32.exp[355] = GetProcAddress(ole32.dll, "CoUnmarshalInterface");
		ole32.exp[356] = GetProcAddress(ole32.dll, "CoVrfCheckThreadState");
		ole32.exp[357] = GetProcAddress(ole32.dll, "CoVrfGetThreadState");
		ole32.exp[358] = GetProcAddress(ole32.dll, "CoVrfReleaseThreadState");
		ole32.exp[359] = GetProcAddress(ole32.dll, "CoWaitForMultipleHandles");
		ole32.exp[360] = GetProcAddress(ole32.dll, "CoWaitForMultipleObjects");
		ole32.exp[361] = GetProcAddress(ole32.dll, "CreateErrorInfo");
		ole32.exp[362] = GetProcAddress(ole32.dll, "CreateStreamOnHGlobal");
		ole32.exp[363] = GetProcAddress(ole32.dll, "DcomChannelSetHResult");
		ole32.exp[364] = GetProcAddress(ole32.dll, "DllDebugObjectRPCHook");
		ole32.exp[365] = GetProcAddress(ole32.dll, "EnableHookObject");
		ole32.exp[366] = GetProcAddress(ole32.dll, "GetErrorInfo");
		ole32.exp[367] = GetProcAddress(ole32.dll, "GetHGlobalFromStream");
		ole32.exp[368] = GetProcAddress(ole32.dll, "GetHookInterface");
		ole32.exp[369] = GetProcAddress(ole32.dll, "HACCEL_UserFree");
		ole32.exp[370] = GetProcAddress(ole32.dll, "HACCEL_UserMarshal");
		ole32.exp[371] = GetProcAddress(ole32.dll, "HACCEL_UserSize");
		ole32.exp[372] = GetProcAddress(ole32.dll, "HACCEL_UserUnmarshal");
		ole32.exp[373] = GetProcAddress(ole32.dll, "HBITMAP_UserFree");
		ole32.exp[374] = GetProcAddress(ole32.dll, "HBITMAP_UserMarshal");
		ole32.exp[375] = GetProcAddress(ole32.dll, "HBITMAP_UserSize");
		ole32.exp[376] = GetProcAddress(ole32.dll, "HBITMAP_UserUnmarshal");
		ole32.exp[377] = GetProcAddress(ole32.dll, "HBRUSH_UserFree");
		ole32.exp[378] = GetProcAddress(ole32.dll, "HBRUSH_UserMarshal");
		ole32.exp[379] = GetProcAddress(ole32.dll, "HBRUSH_UserSize");
		ole32.exp[380] = GetProcAddress(ole32.dll, "HBRUSH_UserUnmarshal");
		ole32.exp[381] = GetProcAddress(ole32.dll, "HDC_UserFree");
		ole32.exp[382] = GetProcAddress(ole32.dll, "HDC_UserMarshal");
		ole32.exp[383] = GetProcAddress(ole32.dll, "HDC_UserSize");
		ole32.exp[384] = GetProcAddress(ole32.dll, "HDC_UserUnmarshal");
		ole32.exp[385] = GetProcAddress(ole32.dll, "HGLOBAL_UserFree");
		ole32.exp[386] = GetProcAddress(ole32.dll, "HGLOBAL_UserMarshal");
		ole32.exp[387] = GetProcAddress(ole32.dll, "HGLOBAL_UserSize");
		ole32.exp[388] = GetProcAddress(ole32.dll, "HGLOBAL_UserUnmarshal");
		ole32.exp[389] = GetProcAddress(ole32.dll, "HICON_UserFree");
		ole32.exp[390] = GetProcAddress(ole32.dll, "HICON_UserMarshal");
		ole32.exp[391] = GetProcAddress(ole32.dll, "HICON_UserSize");
		ole32.exp[392] = GetProcAddress(ole32.dll, "HICON_UserUnmarshal");
		ole32.exp[393] = GetProcAddress(ole32.dll, "HMENU_UserFree");
		ole32.exp[394] = GetProcAddress(ole32.dll, "HMENU_UserMarshal");
		ole32.exp[395] = GetProcAddress(ole32.dll, "HMENU_UserSize");
		ole32.exp[396] = GetProcAddress(ole32.dll, "HMENU_UserUnmarshal");
		ole32.exp[397] = GetProcAddress(ole32.dll, "HMONITOR_UserFree");
		ole32.exp[398] = GetProcAddress(ole32.dll, "HMONITOR_UserMarshal");
		ole32.exp[399] = GetProcAddress(ole32.dll, "HMONITOR_UserSize");
		ole32.exp[400] = GetProcAddress(ole32.dll, "HMONITOR_UserUnmarshal");
		ole32.exp[401] = GetProcAddress(ole32.dll, "HPALETTE_UserFree");
		ole32.exp[402] = GetProcAddress(ole32.dll, "HPALETTE_UserMarshal");
		ole32.exp[403] = GetProcAddress(ole32.dll, "HPALETTE_UserSize");
		ole32.exp[404] = GetProcAddress(ole32.dll, "HPALETTE_UserUnmarshal");
		ole32.exp[405] = GetProcAddress(ole32.dll, "HWND_UserFree");
		ole32.exp[406] = GetProcAddress(ole32.dll, "HWND_UserMarshal");
		ole32.exp[407] = GetProcAddress(ole32.dll, "HWND_UserSize");
		ole32.exp[408] = GetProcAddress(ole32.dll, "HWND_UserUnmarshal");
		ole32.exp[409] = GetProcAddress(ole32.dll, "HkOleRegisterObject");
		ole32.exp[410] = GetProcAddress(ole32.dll, "IIDFromString");
		ole32.exp[411] = GetProcAddress(ole32.dll, "NdrOleInitializeExtension");
		ole32.exp[412] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction10");
		ole32.exp[413] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction11");
		ole32.exp[414] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction12");
		ole32.exp[415] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction13");
		ole32.exp[416] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction14");
		ole32.exp[417] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction15");
		ole32.exp[418] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction16");
		ole32.exp[419] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction17");
		ole32.exp[420] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction18");
		ole32.exp[421] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction19");
		ole32.exp[422] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction20");
		ole32.exp[423] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction21");
		ole32.exp[424] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction22");
		ole32.exp[425] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction23");
		ole32.exp[426] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction24");
		ole32.exp[427] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction25");
		ole32.exp[428] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction26");
		ole32.exp[429] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction27");
		ole32.exp[430] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction28");
		ole32.exp[431] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction29");
		ole32.exp[432] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction30");
		ole32.exp[433] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction31");
		ole32.exp[434] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction32");
		ole32.exp[435] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction3");
		ole32.exp[436] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction4");
		ole32.exp[437] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction5");
		ole32.exp[438] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction6");
		ole32.exp[439] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction7");
		ole32.exp[440] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction8");
		ole32.exp[441] = GetProcAddress(ole32.dll, "NdrProxyForwardingFunction9");
		ole32.exp[442] = GetProcAddress(ole32.dll, "ObjectStublessClient10");
		ole32.exp[443] = GetProcAddress(ole32.dll, "ObjectStublessClient11");
		ole32.exp[444] = GetProcAddress(ole32.dll, "ObjectStublessClient12");
		ole32.exp[445] = GetProcAddress(ole32.dll, "ObjectStublessClient13");
		ole32.exp[446] = GetProcAddress(ole32.dll, "ObjectStublessClient14");
		ole32.exp[447] = GetProcAddress(ole32.dll, "ObjectStublessClient15");
		ole32.exp[448] = GetProcAddress(ole32.dll, "ObjectStublessClient16");
		ole32.exp[449] = GetProcAddress(ole32.dll, "ObjectStublessClient17");
		ole32.exp[450] = GetProcAddress(ole32.dll, "ObjectStublessClient18");
		ole32.exp[451] = GetProcAddress(ole32.dll, "ObjectStublessClient19");
		ole32.exp[452] = GetProcAddress(ole32.dll, "ObjectStublessClient20");
		ole32.exp[453] = GetProcAddress(ole32.dll, "ObjectStublessClient21");
		ole32.exp[454] = GetProcAddress(ole32.dll, "ObjectStublessClient22");
		ole32.exp[455] = GetProcAddress(ole32.dll, "ObjectStublessClient23");
		ole32.exp[456] = GetProcAddress(ole32.dll, "ObjectStublessClient24");
		ole32.exp[457] = GetProcAddress(ole32.dll, "ObjectStublessClient25");
		ole32.exp[458] = GetProcAddress(ole32.dll, "ObjectStublessClient26");
		ole32.exp[459] = GetProcAddress(ole32.dll, "ObjectStublessClient27");
		ole32.exp[460] = GetProcAddress(ole32.dll, "ObjectStublessClient28");
		ole32.exp[461] = GetProcAddress(ole32.dll, "ObjectStublessClient29");
		ole32.exp[462] = GetProcAddress(ole32.dll, "ObjectStublessClient30");
		ole32.exp[463] = GetProcAddress(ole32.dll, "ObjectStublessClient31");
		ole32.exp[464] = GetProcAddress(ole32.dll, "ObjectStublessClient32");
		ole32.exp[465] = GetProcAddress(ole32.dll, "ObjectStublessClient3");
		ole32.exp[466] = GetProcAddress(ole32.dll, "ObjectStublessClient4");
		ole32.exp[467] = GetProcAddress(ole32.dll, "ObjectStublessClient5");
		ole32.exp[468] = GetProcAddress(ole32.dll, "ObjectStublessClient6");
		ole32.exp[469] = GetProcAddress(ole32.dll, "ObjectStublessClient7");
		ole32.exp[470] = GetProcAddress(ole32.dll, "ObjectStublessClient8");
		ole32.exp[471] = GetProcAddress(ole32.dll, "ObjectStublessClient9");
		ole32.exp[472] = GetProcAddress(ole32.dll, "ProgIDFromCLSID");
		ole32.exp[473] = GetProcAddress(ole32.dll, "RoGetAgileReference");
		ole32.exp[474] = GetProcAddress(ole32.dll, "SetErrorInfo");
		ole32.exp[475] = GetProcAddress(ole32.dll, "StringFromCLSID");
		ole32.exp[476] = GetProcAddress(ole32.dll, "StringFromGUID2");
		ole32.exp[477] = GetProcAddress(ole32.dll, "StringFromIID");
		ole32.exp[478] = GetProcAddress(ole32.dll, "UpdateDCOMSettings");
		ole32.exp[479] = GetProcAddress(ole32.dll, "UpdateProcessTracing");
		ole32.exp[480] = GetProcAddress(ole32.dll, "WdtpInterfacePointer_UserFree");
		ole32.exp[481] = GetProcAddress(ole32.dll, "WdtpInterfacePointer_UserMarshal");
		ole32.exp[482] = GetProcAddress(ole32.dll, "WdtpInterfacePointer_UserSize");
		ole32.exp[483] = GetProcAddress(ole32.dll, "WdtpInterfacePointer_UserUnmarshal");



	}
	else if (_tcsicmp(DllName, L"d3d9.dll") == NULL) {
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
		d3d9.Direct3D9EnableMaximizedWindowedModeShim = GetProcAddress(d3d9.dll, "Direct3D9EnableMaximizedWindowedModeShim");
		//d3d9.Direct3DCreate9 = GetProcAddress(d3d9.dll, "Direct3DCreate9");
		d3d9.Direct3DCreate9 = (FARPROC)mod_Direct3DCreate9;
		d3d9.Direct3DCreate9Ex = GetProcAddress(d3d9.dll, "Direct3DCreate9Ex");
		d3d9.Direct3DShaderValidatorCreate9 = GetProcAddress(d3d9.dll, "Direct3DShaderValidatorCreate9");
		d3d9.PSGPError = GetProcAddress(d3d9.dll, "PSGPError");
		d3d9.PSGPSampleTexture = GetProcAddress(d3d9.dll, "PSGPSampleTexture");
	}
	else if (_tcsicmp(DllName, L"d3d11.dll") == NULL) {
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
	else if (_tcsicmp(DllName, L"winmmbase.dll") == NULL) {
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
	else if (_tcsicmp(DllName, L"msacm32.dll") == NULL) {
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
			L"ASI Loader", MB_ICONINFORMATION);
		ExitProcess(0);
	}
}


// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI mod_Direct3DCreate9(UINT SDKVersion)
{
	// looking for the "right d3d9.dll"
	//MessageBox(NULL, L"OK", L"mod_Direct3DCreate9", MB_ICONWARNING);
	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI *D3D9_Type)(UINT);

	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(d3d9.dll, "Direct3DCreate9");

	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	// Create my IDirect3D8 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	gl_pmyIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);

	// Return pointer to hooking Object instead of "real one"
	return (gl_pmyIDirect3D9);
}

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

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		dllModule = hInst;

		InitInstance(hInst);

		hExecutableInstance = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)

		GetModuleFileName(dllModule, wc_DllPath, MAX_PATH);
		GetModuleFileName(hExecutableInstance, wc_ExePath, MAX_PATH);

		pwc_dllName = _tcsrchr(wc_DllPath, L'\\');

		pwc_dllName = &pwc_dllName[1];

		GetSystemDirectory(sz_SystemPath, MAX_PATH);

		Redirect(pwc_dllName);

		pwc_ExeName = _tcsrchr(wc_ExePath, L'\\');

		pwc_ExeName = &pwc_ExeName[1];

		SomeGameMod();



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