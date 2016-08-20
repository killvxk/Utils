#pragma once

#define OFFSET_CLIENTGAMECONTEXT    0x1424abd20
#define OFFSET_DXRENDERER           0x142572fa0 
#define OFFSET_GAMERENDERER         0x1424ad330
#define OFFSET_ANGLES				0x1421caee0
#define OFFSET_WORLDRENDERSETTINGS  0x1424ad460

namespace fb {
	class Screen
	{
	public:
		BYTE pad00[0x58];				//0x00
		unsigned int m_Width;			//0x58
		unsigned int m_Height;			//0x5C
		unsigned int m_WindowWidth;			//0x60
		unsigned int m_WindowHeight;		//0x64
		BYTE pad01[0x88];				//0x68
		IDXGISwapChain* m_pSwapChain;		//0xF0
	};
	class DxRenderer
	{
	public:
		BYTE pad00[0x38];                    // 0x00
		Screen* m_pScreen;                    // 0x38
		BYTE pad78[0xC0];                    // 0x40
		ID3D11Device* m_pDevice;            // 0x100
		ID3D11DeviceContext* m_pContext;    // 0x108
		char _0x0110[192];
		void* m_settings; //0x01D0

		static DxRenderer* GetInstance()
		{
			return *(DxRenderer**)OFFSET_DXRENDERER;
		}
	};//Size=0x0110



}