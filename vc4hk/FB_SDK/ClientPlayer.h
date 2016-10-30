#ifndef _ClientPlayer_H
#define _ClientPlayer_H
#include "Frostbite_Classes.h"
namespace fb
{
	class ClientPlayer
	{
	public:
		virtual ~ClientPlayer();
		virtual void* GetCharacterEntity(); // ClientSoldierEntity + 188 
		virtual void* GetCharacterUserData(); // PlayerCharacterUserData
		virtual void* GetEntryComponent();
		virtual bool InVehicle();
		virtual unsigned int GetId();
		virtual bool hasUnlockAsset(LPVOID, bool);
		virtual void getUnlockAssets(eastl::vector<LPVOID> *);
		virtual bool isUnlocked(LPVOID);

		__int64 m_Data; //0x0008 
		char _0x0010[48];
		char m_Name[16]; //0x0040 
		char _0x0050[2296];
		VeniceSoldierCustimizationAsset* m_pCustomization; //0x0948 
		char _0x0950[2684];
		__int32 m_TeamId; //0x13CC 
		char _0x13D0[0xd0];//0x13d0
		void* m_soldier;
		WeakPtr<ClientSoldierEntity> m_corpse;		//0x14A8
		WeakPtr<ClientSoldierEntity>  m_character;	//0x14B0		
		void* m_weakTokenHolder;//0x14B8
		ClientControllableEntity* m_pAttachedControllable; //0x14C0 
		__int32 AttachedEntryId; //0x14C8
		float wha;
		ClientControllableEntity* m_pControlledControllable; //0x14D0 
		__int32 pControlledId; //0x14d8
		char _0x14BC[44];
		__int64 m_EntryComponent; //0x14E8 fb::ClientPlayerEntryComponent
		__int64 m_PlayerManager; //0x14F0 
		void* m_ownPlayerView; //0x14F8 
		void* m_PlayerView; //0x1500 
		char _0x1508[24];
		__int64 m_InputConfiguration; //0x1520 
		ClientSoldierEntity* GetSoldierEntity()
		{
			if (this->InVehicle())
				return (ClientSoldierEntity*)((intptr_t)this->GetCharacterEntity() - 0x188);

			if (m_pControlledControllable)
				return (ClientSoldierEntity*)m_pControlledControllable;

			return nullptr;


		}
		ClientVehicleEntity* GetVehicleEntity()
		{
			if (this->InVehicle())
				return (ClientVehicleEntity*)m_pAttachedControllable;
			return nullptr;
		}
	};//Size=0x14D8

};

#endif