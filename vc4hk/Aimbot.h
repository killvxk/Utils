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
	fb::Vec4* GetClosestPlayer(eastl::vector<fb::ClientPlayer*>*, fb::ClientPlayer*, bool, bool);
	fb::Vec4 GetVecOfPlayer(bool, fb::RagdollComponent*);
	fb::Vec4 GetOriginAndUpdateCurrentAngle(fb::ClientPlayer*, fb::ClientWeapon*, fb::FiringFunctionData*, bool);

	DWORD GetVectorFromVehicle(fb::ClientPlayer*, fb::Vec4*);


	bool mb_AimKeyPressed;
	fb::Vec4 vOrigin;
	fb::Vec4 v_curAngle;
	fb::Vec4 v_lastAngle;
	bool bAimHead;
	fb::ClientSoldierEntity* m_LockOn_pEnemySoldier;
	fb::ClientPlayer* m_LockOn_pEnemyPlayer;
	int LockOnEnemyFlags;

	fb::ClientSoldierEntity* mp_ClosestSoldier;
	fb::ClientPlayer* mp_ClosestPlayer;
	fb::Vec4*  VecOfClosestSoldier;

private:

	double FindMinPos(double a[2]);
	double FindMinPosRoot(double *a, int n);
	double TimeToHit(fb::Vec4 p, fb::Vec4 u, double v_pow2);

	void NullTmpVar();
	float DistanceToAimRay(fb::Vec4, fb::Vec4,
		const fb::Vec4);
};




#endif 