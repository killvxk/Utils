#ifndef _Main_H
#define _Main_H
#include "Frostbite_Classes.h"
namespace fb
{
	class ServerJobData
	{
	public:
		char _0x0000[136];
		Server* m_pServer; //0x0088 
		ClientGameContext* m_pGameContext; //0x0090 
		__int64 m_pParams; //0x0098 
	};//Size=0x00A0
	class Main
	{
	public:
		char _0x0000[32];
		unsigned char m_IsDedicatedServer; //0x0020 
		unsigned char m_IsDedicatedServerData; //0x0021 
		unsigned char m_IsPaused; //0x0022 
		char _0x0023[5]; //0x0023 
		char _0x0028[32];
		Server* m_pServer; //0x0048 
		Client* m_pClient; //0x0050 
		FileSystem* m_pFileSystem; //0x0058 
		GameTimer* m_pSimulationGameTimer; //0x0060 
		GameTimer* m_pUIGameTimer; //0x0068 
		char _0x0070[8];
		ServerJobData m_ServerJobData; //0x0078 

		static Main* GetInstance()
		{
			return *(Main**)OFFSET_MAIN;
		}
	};//Size=0x0118
};
#endif