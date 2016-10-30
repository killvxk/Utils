#pragma once
#ifndef __HK_HEAD_H__
#define __HK_HEAD_H__
#include "FB_SDK\Frostbite.h"

double FindMinPos(double a[2]);
double FindMinPosRoot(double *a, int n);double TimeToHit(fb::Vec3 p, fb::Vec3 u, double v_pow2);
bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root);



float DistanceToAimRay(fb::Vec3 MyPosition, fb::Vec3 EnemyPosition,
	const fb::Vec3 vAngle);
fb::Vec3 getVehicleSpeed(fb::ClientSoldierEntity * soldier);
bool IsAlive(fb::ClientControllableEntity* pPlayer);
DWORD GetVectorFromeVehicle(fb::ClientPlayer* pLocalPlayer, fb::Vec3* vector);
#endif 