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

double TimeToHit(fb::Vec3 p, fb::Vec3 u, double v_pow2)
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






bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root) {

	double p = (8 * a*c - 3 * b*b) / (8 * a*a);
	double q = (b*b*b - 4 * a*b*c + 8 * a*a*d) / (8 * a*a*a);

	double delta_0 = c*c - 3 * b*d + 12 * a*e;
	double delta_1 = 2 * c*c*c - 9 * b*c*d + 27 * b*b*e + 27 * a*d*d - 72 * a*c*e;



}

DWORD GetVectorFromeVehicle(fb::ClientPlayer* pLocalPlayer, fb::Vec3* vector) {

	SM::Matrix* mTransform = new SM::Matrix;
	fb::Vec3  tmp;

	fb::ClientVehicleEntity *veh = pLocalPlayer->GetVehicleEntity();

	if (!POINTERCHK(veh))return 0x1;

	veh->GetTransform(mTransform);

	if (!POINTERCHK(mTransform))return 0x1;

	fb::AxisAlignedBox AABB = *(fb::AxisAlignedBox *) ((intptr_t)veh + 0x250);



	vector->x = mTransform->_41;
	vector->y = mTransform->_42;
	vector->z = mTransform->_43;
	vector->w = 1;

	tmp = (AABB.m_Max + AABB.m_Min)*0.5f;//model martix

	vector->x = vector->x + tmp.x*mTransform->_11 + tmp.y*mTransform->_21 + tmp.z*mTransform->_31;
	vector->y = vector->y + tmp.x*mTransform->_12 + tmp.y*mTransform->_22 + tmp.z*mTransform->_32;
	vector->z = vector->z + tmp.x*mTransform->_13 + tmp.y*mTransform->_23 + tmp.z*mTransform->_33;
	//vector->w = vector->w + tmp.x*mTransform->_14 + tmp.y*mTransform->_24 + tmp.z*mTransform->_34 + tmp.w*mTransform->_44;

	return 0x0;
}


bool IsAlive(fb::ClientControllableEntity* pPlayer)
{

	fb::HealthComponent* pEmeHealthComponent = *((fb::HealthComponent**)((intptr_t)pPlayer + 0x140));

	if (POINTERCHK(pEmeHealthComponent)) {
		if (pEmeHealthComponent->m_Health > 0 ) { return true; }
		else
		{
			return false;
		}
	};

	return false;
}



fb::Vec3 getVehicleSpeed(fb::ClientSoldierEntity * soldier)
{
	fb::Vec3 tempvec;
	tempvec.x = 0.0f;
	tempvec.y = 0.0f;
	tempvec.z = 0.0f;
	fb::ClientPlayer* p_ClientPlayer = soldier->m_pPlayer;
	if (POINTERCHK(p_ClientPlayer))
	{
		fb::ClientVehicleEntity* p_veh = (fb::ClientVehicleEntity*)soldier->m_pPlayer ->m_pAttachedControllable;


		if (POINTERCHK(p_veh)) {
			tempvec = p_veh->getVehicleSpeed();
		

	}

	}
	
	return tempvec;
}
float DistanceToAimRay(fb::Vec3 MyPosition, fb::Vec3 EnemyPosition,
	const fb::Vec3 vAngle) {

	float fYawDifference, flPitchDifference;

	fb::Vec3 vDir = EnemyPosition - MyPosition;
	float m_dist0 = vDir.len();
	float x, y;
	vDir.normalize();

	float m_dist1 = vDir.len();


	fYawDifference = -atan2(vDir.x, vDir.z);

	if (fYawDifference < 0)fYawDifference = fYawDifference + Twice_PI;


	fYawDifference = abs(fYawDifference - vAngle.x);

	if (m_dist0 <= 5.f && fYawDifference < 3.0f)return 0.00025f; else
	{


		if (fYawDifference < 0 || fYawDifference > 0.125f || _isnanf(fYawDifference))return -2.f;

	}

	flPitchDifference = atan2(vDir.y, vDir.VectorLength2());

	if (_isnanf(flPitchDifference))return -2.f;

	flPitchDifference = abs(flPitchDifference - vAngle.y);

	if (flPitchDifference > 1.48350f || flPitchDifference < -1.2217f || _isnanf(flPitchDifference))return -2.f;

	x = abs(m_dist1*cos(flPitchDifference)*sin(fYawDifference));

	y = abs(m_dist1*sin(flPitchDifference));

	return x*x + y*y;
}