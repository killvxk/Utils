#include "stdafx.h"
#include <string> 
#include "myIDirect3D9.h"
#include <d3d9.h>

typedef HRESULT(WINAPI *fn_IDirect3DDevice9_Present)(const RECT *pSourceRect,
	const RECT    *pDestRect,
	HWND    hDestWindowOverride,
	const RGNDATA *pDirtyRegion);

typedef HRESULT(WINAPI  *fn_IDirect3DDevice9_Reset)(D3DPRESENT_PARAMETERS*);
bool hooked = false;
fn_IDirect3DDevice9_Present o_IDirect3DDevice9_Present;
fn_IDirect3DDevice9_Reset o_Reset;

void setParameter(D3DPRESENT_PARAMETERS* pPresentationParameters) {
	if (!pPresentationParameters->Windowed) pPresentationParameters->SwapEffect = D3DSWAPEFFECT_FLIP;
	if (pPresentationParameters->BackBufferCount < 2)pPresentationParameters->BackBufferCount = 2;
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
}

HRESULT WINAPI my_IDirect3DDevice9_Present(const RECT    *pSourceRect,
	const RECT    *pDestRect,
	HWND    hDestWindowOverride,
	const RGNDATA *pDirtyRegion) {

	return o_IDirect3DDevice9_Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT WINAPI my_IDirect3DDevice9_Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) {

	setParameter(pPresentationParameters);

	return o_Reset(pPresentationParameters);



}
void hook_D3D_Api(IDirect3DDevice9* pDevice) {

	void *vtb_IDirect3DDevice9 = *(void**)pDevice;

	void *tmp;

	tmp = (fn_IDirect3DDevice9_Reset)ReplaceVtblFunction(vtb_IDirect3DDevice9, my_IDirect3DDevice9_Reset, 16);
	if (tmp != my_IDirect3DDevice9_Reset) {
		o_Reset = (fn_IDirect3DDevice9_Reset)tmp;
	}

	hooked = true;

}

myIDirect3D9::myIDirect3D9(IDirect3D9 *pOriginal)
{
    m_pIDirect3D9 = pOriginal;
}

myIDirect3D9::~myIDirect3D9(void)
{
}

HRESULT  __stdcall myIDirect3D9::QueryInterface(REFIID riid, void** ppvObj)
{
    *ppvObj = NULL;

	// call this to increase AddRef at original object
	// and to check if such an interface is there

	HRESULT hRes = m_pIDirect3D9->QueryInterface(riid, ppvObj); 

	if (hRes == NOERROR) // if OK, send our "fake" address
	{
		*ppvObj = this;
	}
	
	return hRes;
}

ULONG  __stdcall myIDirect3D9::AddRef(void)
{
    return(m_pIDirect3D9->AddRef());
}

ULONG    __stdcall myIDirect3D9::Release(void)
{
    extern myIDirect3D9* gl_pmyIDirect3D9;

	// call original routine
	ULONG count = m_pIDirect3D9->Release();
	
    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		gl_pmyIDirect3D9 = NULL;
  	    delete(this); 
	}

	return(count);
}

HRESULT __stdcall myIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return(m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction));
}

UINT __stdcall myIDirect3D9::GetAdapterCount(void)
{
    return(m_pIDirect3D9->GetAdapterCount());
}

HRESULT __stdcall myIDirect3D9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return(m_pIDirect3D9->GetAdapterIdentifier(Adapter,Flags,pIdentifier));
}

UINT __stdcall myIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
    return(m_pIDirect3D9->GetAdapterModeCount(Adapter, Format));
}

HRESULT __stdcall myIDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3D9->EnumAdapterModes(Adapter,Format,Mode,pMode));
}

HRESULT __stdcall myIDirect3D9::GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3D9->GetAdapterDisplayMode(Adapter,pMode));
}

HRESULT __stdcall myIDirect3D9::CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
    return(m_pIDirect3D9->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed));
}

HRESULT __stdcall myIDirect3D9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
    return(m_pIDirect3D9->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat));
}

HRESULT __stdcall myIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
    return(m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels));
}

HRESULT __stdcall myIDirect3D9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
    return(m_pIDirect3D9->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat));
}

HRESULT __stdcall myIDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
    return(m_pIDirect3D9->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat));
}

HRESULT __stdcall myIDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
    return(m_pIDirect3D9->GetDeviceCaps(Adapter,DeviceType,pCaps));
}



HMONITOR __stdcall myIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
    return(m_pIDirect3D9->GetAdapterMonitor(Adapter));
}



HRESULT __stdcall myIDirect3D9::CreateDevice(UINT Adapter,
	D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,
	D3DPRESENT_PARAMETERS* pPresentationParameters,
	IDirect3DDevice9** ppReturnedDeviceInterface)
{
   
	//extern myIDirect3DDevice9* gl_pmyIDirect3DDevice9;

	setParameter(pPresentationParameters);
	
	// we intercept this call and provide our own "fake" Device Object
	HRESULT hres = m_pIDirect3D9->CreateDevice( 
		Adapter, DeviceType, hFocusWindow, BehaviorFlags,
		pPresentationParameters, ppReturnedDeviceInterface);

	//gl_pmyIDirect3DDevice9 = new myIDirect3DDevice9(*ppReturnedDeviceInterface);
	if (!hooked)hook_D3D_Api(*ppReturnedDeviceInterface);
	//*ppReturnedDeviceInterface = gl_pmyIDirect3DDevice9;
	
	return(hres);

}
