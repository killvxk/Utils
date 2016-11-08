#pragma once
#ifndef __HK_HEAD_H__
#define __HK_HEAD_H__
#include "FB_SDK\Frostbite.h"


struct VehcileAimingData {
	PCHAR mcz_WeaponName;
	float mf_YawMultiplier;
	float mf_PitchMultiplier;


};


double FindMinPos(double a[2]);
double FindMinPosRoot(double *a, int n);double TimeToHit(fb::Vec4 p, fb::Vec4 u, double v_pow2);
bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root);



float DistanceToAimRay(fb::Vec4 MyPosition, fb::Vec4 EnemyPosition,
	const fb::Vec4 vAngle);
fb::Vec4 getVehicleSpeed(fb::ClientSoldierEntity * soldier);
bool IsAlive(fb::ClientControllableEntity* pPlayer);
DWORD GetVectorFromVehicle(fb::ClientPlayer* pLocalPlayer, fb::Vec4* vector);
#endif 