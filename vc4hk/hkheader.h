#pragma once
#ifndef __HK_HEAD_H__
#define __HK_HEAD_H__
#include "FB_SDK\Frostbite.h"


struct VehcileAimingData {
	PCHAR mcz_WeaponName;
	float mf_YawMultiplier;
	float mf_PitchMultiplier;


};

class HackKev {
public:
	fb::ClientGameContext* mp_GameContext;
	fb::PlayerManager* mp_PlayerMngr;
	fb::ClientPlayer* mp_LocalPlayer;
	fb::ClientSoldierEntity*mp_LocalSoldier;
	bool mb_Unlcok;
	bool	mb_AmmoBox;
	void* mp_CurVehicleCamera;
	float g_pInputBuffers[123];
	intptr_t* slotG1_list[4][15];
	HackKev();

	void AmmoBox();
	size_t GetClientComponentByID(void*, std::vector<void*>*, unsigned int, bool,
		bool);
	void VehicleWeaponUpgrade();
	void MiniMap();
	void VarsUpdate();
	void WeaponUpgrade();

private:


	bool IsAlive(fb::ClientControllableEntity* pPlayer);
};


#endif 