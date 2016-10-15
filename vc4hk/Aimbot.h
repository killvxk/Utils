#pragma once
#ifndef __AIMBOT_H__
#define __AIMBOT_H__
#include "x64_sdk.hpp"
using namespace fb;




class Aimbot
{
public:
	Aimbot();
	DWORD  AimCorrection2(fb::Vec3 MyPosition,
	fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, fb::Vec3  v1, float Gravity, fb::Vec3* out);
	fb::Vec3 * GetClosestPlayer(eastl::vector<fb::ClientPlayer*>*, fb::ClientPlayer*, int);

	fb::Vec3* 	GetOriginAndUpdateCurrentAngle(fb::ClientPlayer* pLocalPlayer, fb::ClientWeapon* MyCSW, fb::FiringFunctionData* pFFD, void* pCurVehicleCam);
	void NullTmpVar();



	fb::Vec3 *	vOrigin;
	fb::Vec3 *v_curAngle;
	fb::Vec3 v_lastAngle;
	bool bAimHead;
	fb::ClientSoldierEntity* LockOn_pEnemySoldier;
	int LockOnEnemyFlags;
	fb::ClientSoldierEntity* ClosestSoldier;
	fb::Vec3 * VecOfClosestSoldier;

private:

};




#endif 