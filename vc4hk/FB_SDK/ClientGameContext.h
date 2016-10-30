#ifndef _ClientGameContext_H
#define _ClientGameContext_H

#include "Frostbite_Classes.h"

namespace fb
{

	class ClientGameContext
	{
	public:
		char _0x0000[0x20];
		GameTime* m_pGameTime; //0x0020 
		Level* m_pLevel; //0x0028 
		char _0x0030[48];
		PlayerManager* m_pPlayerManager; //0x0060 
		Online* m_pOnline; //0x0068 
		GameView* m_pGameView; //0x0070 
		InterpolationManager* m_pInterpolationManager; //0x0078 
		char _0x0080[960];
		static ClientGameContext* GetInstance()
		{
			return *(ClientGameContext**)OFFSET_CLIENTGAMECONTEXT;
		}
	};//Size=0x0440
};

#endif