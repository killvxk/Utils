#pragma once
#ifndef __AIMBOT_H__
#define __AIMBOT_H__
#include "FB_SDK\Frostbite.h"





class Aimbot
{
public:
	Aimbot();
	DWORD  AimCorrection2(fb::Vec4 MyPosition,
	fb::Vec4  EnemyP, fb::Vec4 EnemyVelocity, fb::Vec4  v1, float Gravity, fb::Vec4* out);
	fb::Vec4 * GetClosestPlayer(eastl::vector<fb::ClientPlayer*>*, fb::ClientPlayer*, int, bool);
	fb::Vec4  GetVecOfPlayer(bool, fb::RagdollComponent*);
	fb::Vec4 	GetOriginAndUpdateCurrentAngle(fb::ClientPlayer* , fb::ClientWeapon* , fb::FiringFunctionData* ,bool );
	void NullTmpVar();
	DWORD GetVectorFromVehicle(fb::ClientPlayer* , fb::Vec4* );
	float DistanceToAimRay(fb::Vec4 , fb::Vec4 ,
		const fb::Vec4 );

	fb::Vec4 vOrigin;
	fb::Vec4 v_curAngle;
	fb::Vec4 v_lastAngle;
	bool bAimHead;
	fb::ClientSoldierEntity* LockOn_pEnemySoldier;
	int LockOnEnemyFlags;
	fb::ClientSoldierEntity* mp_ClosestSoldier;
	fb::ClientPlayer* mp_ClosestPlayer;
	fb::Vec4*  VecOfClosestSoldier;

private:

};




#endif 