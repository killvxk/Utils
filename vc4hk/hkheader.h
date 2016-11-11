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




fb::Vec4 * GetControllableSpeed(fb::ClientControllableEntity* * soldier);
bool IsAlive(fb::ClientControllableEntity* pPlayer);

#endif 