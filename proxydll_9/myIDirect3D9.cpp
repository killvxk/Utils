#include"stdafx.h"
namespace MyInterface {
#pragma warning(push)
#define CINTERFACE                  // Windows SDK : BaseTypes.h
#pragma warning(disable : 4005)
#define STDMETHOD_(type,method)     type (STDMETHODCALLTYPE * method)
#define STDMETHOD(method)           STDMETHOD_(HRESULT,method)
#define PURE
#define THIS                        INTERFACE FAR* This
#define THIS_                       THIS,
#define DECLARE_INTERFACE(iface)    typedef interface iface { struct iface##Vtbl FAR* lpVtbl; } iface; \
                                        typedef struct iface##Vtbl iface##Vtbl; struct iface##Vtbl
#define DECLARE_INTERFACE_(iface,b) DECLARE_INTERFACE(iface)
#undef _D3D9_H_
#include <d3d9.h>
#pragma warning(pop)
} // namespace MyInterface
HRESULT(WINAPI *o_IDirect3DDevice9_Reset)( D3DPRESENT_PARAMETERS*);
HRESULT(WINAPI *o_IDirect3DDevice9_Present)( const RECT    *pSourceRect,
	 const RECT    *pDestRect,
	     HWND    hDestWindowOverride,
	 const RGNDATA *pDirtyRegion);


HRESULT WINAPI my_IDirect3DDevice9_Present( const RECT    *pSourceRect,
	 const RECT    *pDestRect,
	       HWND    hDestWindowOverride,
	 const RGNDATA *pDirtyRegion) {

	return o_IDirect3DDevice9_Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
HRESULT WINAPI my_IDirect3DDevice9_Reset( D3DPRESENT_PARAMETERS* pPresentationParameters) {
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	return o_IDirect3DDevice9_Reset( pPresentationParameters);
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

ULONG    __stdcall myIDirect3D9::AddRef(void)
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
void store_IDirect3DDevice9_function(IDirect3DDevice9* pDevice) {
	MyInterface::IDirect3DDevice9Vtbl* v = ((MyInterface::IDirect3DDevice9*) pDevice)->lpVtbl;
	*(void**)&v->Reset = (void*)my_IDirect3DDevice9_Reset;
}
HRESULT __stdcall myIDirect3D9::CreateDevice(UINT Adapter,
	D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,
	D3DPRESENT_PARAMETERS* pPresentationParameters,
	IDirect3DDevice9** ppReturnedDeviceInterface)
{

	

	

    // global var
	//extern myIDirect3DDevice9* gl_pmyIDirect3DDevice9;
	//pPresentationParameters->BackBufferWidth = 0;
	//pPresentationParameters->BackBufferHeight = 0;

	//pPresentationParameters->MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	//pPresentationParameters->SwapEffect = D3DSWAPEFFECT_FLIP;
	//pPresentationParameters->Windowed = TRUE;
	//pPresentationParameters->FullScreen_RefreshRateInHz = 0;
	//pPresentationParameters->hDeviceWindow = FindExeHwnd::GetHwndFromPID(GetCurrentProcessId());
	pPresentationParameters->BackBufferCount = 2;
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	
	// we intercept this call and provide our own "fake" Device Object
	HRESULT hres = m_pIDirect3D9->CreateDevice( 
		Adapter, DeviceType, hFocusWindow, BehaviorFlags,
		pPresentationParameters, ppReturnedDeviceInterface);

	//HRESULT(WINAPI IDirect3DDevice9::*ori)(D3DPRESENT_PARAMETERS*)= &IDirect3DDevice9::Reset; 
	//IDirect3DDevice9 * v = *ppReturnedDeviceInterface;
	//int ori_reset= reinterpret_cast<int>(*(void**)(&ori)) + reinterpret_cast<int>(v);//ponit to v->reset
	//o_IDirect3DDevice9_Reset =(HRESULT(WINAPI*)(D3DPRESENT_PARAMETERS*))ori_reset;

	//DWORD protect = PAGE_EXECUTE_WRITECOPY;
	//VirtualProtect(v, sizeof(*v), protect, &protect);
	/*if (SUCCEEDED(hres)) {
		MyInterface::IDirect3DDevice9Vtbl* v = ((MyInterface::IDirect3DDevice9*) (*ppReturnedDeviceInterface))->lpVtbl;
		*(void**)&o_IDirect3DDevice9_Reset = (void*)v->Reset;
		*(void**)&o_IDirect3DDevice9_Present = (void*)v->Present;
			store_IDirect3DDevice9_function(*ppReturnedDeviceInterface);
		
	}*/

	return(hres); 
}
  