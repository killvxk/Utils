#include "stdafx.h"
#include "hkheader.h"
#include "poly34.h"



double FindMinPos(double a[2]) {
	if (a[0] <= 0 && a[1] <= 0)return 0.0;

	else if (a[0] <= 0)return a[1];

	else if (a[1] <= 0)return a[0];

	else return a[0] < a[1] ? a[0] : a[1];
}


double FindMinPosRoot(double *a, int n) {

	if (n == 2) {

		return FindMinPos(a);

	}
	else {

		double tmp[2];

		tmp[0] = FindMinPos(a);

		tmp[1] = FindMinPos(&(a[2]));

		return FindMinPos(tmp);

	}


	return 0.0;

}

double TimeToHit(fb::Vec4 p, fb::Vec4 u, double v_pow2)
{
	double a = v_pow2 - u.Dot(u);
	double b = -2 * p.Dot(u);
	double c = -1 * p.Dot(p);


	double t0[2] = { 0 };


	double de = b*b - 4 * a*c;



	if (de >= 0)
	{
		t0[0] = (-b + sqrt(de)) / (2 * a);

		t0[1] = (-b - sqrt(de)) / (2 * a);
	}
	else
	{
		return -2.0f;
	}

	return FindMinPos(t0);

}


fb::Vec4* GetControllableSpeed(fb::ClientSoldierEntity * soldier){

	__try {
		fb::Vec4* v= soldier->GetVelocity();

		return v;

	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

		return nullptr;
	}

}



bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root) {

	double p = (8 * a*c - 3 * b*b) / (8 * a*a);
	double q = (b*b*b - 4 * a*b*c + 8 * a*a*d) / (8 * a*a*a);

	double delta_0 = c*c - 3 * b*d + 12 * a*e;
	double delta_1 = 2 * c*c*c - 9 * b*c*d + 27 * b*b*e + 27 * a*d*d - 72 * a*c*e;



}

bool IsAlive212(fb::ClientControllableEntity* pPlayer)
{

	fb::HealthComponent* pEmeHealthComponent = *((fb::HealthComponent**)((intptr_t)pPlayer + 0x140));

	if (IsValidPtr(pEmeHealthComponent)) {
		if (pEmeHealthComponent->m_Health > 0) { return true; }
		else
		{
			return false;
		}
	};

	return false;
}
bool IsAlive(fb::ClientControllableEntity* pPlayer)
{
	bool b_isVeh = false;


	fb::HealthComponent* pEmeHealthComponent = *((fb::HealthComponent**)((intptr_t)pPlayer + 0x140));

	if (!IsValidPtr(pEmeHealthComponent))return false;

	__try{
	fb::ClassInfo *pT = (fb::ClassInfo*)(((fb::ITypedObject*)(pPlayer))->GetType());


	if (IsValidPtr(pT)) {

		int Id = pT->m_ClassId;

		if (Id == 695) {
			b_isVeh = true;
		}
	}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

	}


	if (!b_isVeh) {
		return (pEmeHealthComponent->m_Health > 0) ? true : false;
	
	}
	else
	{
		return (pEmeHealthComponent->m_VehicleHealth > 0) ? true : false;
	}

	return false;
}


