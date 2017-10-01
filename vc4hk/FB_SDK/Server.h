#ifndef _Server_H
#define _Server_H

//#include "../Frostbite_classes.h"

namespace fb
{

	class Server
	{
	public:
		char _0x0000[8];
		GameSettings* m_pGameSettings; //0x0008 
		char _0x0010[120];
		ServerSettings* m_pServerSettings; //0x0088 
	};//Size=0x0090



};

#endif