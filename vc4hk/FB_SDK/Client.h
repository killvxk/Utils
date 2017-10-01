#ifndef _Client_H
#define _Client_H


#include "Frostbite_Classes.h"

namespace fb
{
	class Client
	{
	public:
		char _0x0000[8];
		GameSettings* m_pGameSettings; //0x0008 
		char _0x0010[24];
		ClientGameContext* m_pGameContext; //0x0028 
		ClientSettings* m_pClientSettings; //0x0030 
		char _0x0038[8];

	};//Size=0x0040


};

#endif