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
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27();
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		
		char _0x008[0x38];//0x008
		char m_Name[0x10]; //0x0040 
		char _0x0050[0x8f8];//0x0050 
		VeniceSoldierCustimizationAsset* m_pCustomization; //0x0948 
		char _0x0950[0xa7c];
		__int32 m_TeamId; //0x13CC 
		char _0x13D0[0xd0];//0x13d0
		void* m_soldier;//0x14A0
		void*  m_corpse;		//0x14A8
		void* m_character;	//0x14B0		
		void* m_weakTokenHolder;//0x14B8
		ClientControllableEntity* m_pAttachedControllable; //0x14C0 
		__int32 AttachedEntryId; //0x14C8
		__int32 wha;//0x14CC
		ClientControllableEntity* m_pControlledControllable; //0x14D0 
		__int32 pControlledId; //0x14d8
		char _0x14DC[0xc];
		__int64 m_EntryComponent; //0x14E8 fb::ClientPlayerEntryComponent
		__int64 m_PlayerManager; //0x14F0 
		void* m_ownPlayerView; //0x14F8 
		void* m_PlayerView; //0x1500 
		char _0x1508[0x18];
		__int64 m_InputConfiguration; //0x1520 
		char _0x1528[0x29];
		bool isInVehicle;//0x1551

		inline bool InVehicle11() {

		 return isInVehicle;
		}
		inline	ClientSoldierEntity* GetSoldierEntity()
		{
			__try {
			
				return (ClientSoldierEntity*)((intptr_t)(*(intptr_t*)(this->m_character)) - sizeof(intptr_t));
			
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
			{
				return nullptr;

			}
			


		}
	inline	ClientVehicleEntity* GetVehicleEntity()
		{
			if (this->InVehicle())
				return (ClientVehicleEntity*)m_pAttachedControllable;
			return nullptr;
		}
	};//Size=0x14D8

};

#endif