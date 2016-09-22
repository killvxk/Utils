#pragma once

#define M_PI 3.1415926535897932384626433832795f
#define Twice_PI  6.283185307179586476925286766559f
#define DegToRad 0.01745329251994329576923690768489f

#include "poly34.h"




char *buffer = new char[0xff];
std::ofstream log_file(
	"E:\\log\\hk.log", std::ios_base::out | std::ios_base::trunc);

double FindMinPos(double a[2]) {
	if (a[0] <= 0 && a[1] <= 0)return 0.0;

	else if (a[0] <= 0)return a[1];

	else if (a[1] <= 0)return a[0];

	else return a[0] < a[1] ? a[0] : a[1];
}

void log(const std::string &text)
{

	log_file << text << std::endl;
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
	double a = v_pow2 - u.Dot(u) ;
	double b = -2 * p.Dot(u);
	double c =-1* p.Dot(p);


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
DWORD  AimCorrection2(fb::Vec3 MyPosition,
	fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, fb::Vec3  v1, float Gravity, fb::Vec3* out)
{


	float flPitch, flYaw, time, v0_pow2 =v1.z*v1.z+v1.y+v1.y; // x, tmp,
	fb::Vec3 Driection ;


	


	Driection = EnemyP - MyPosition;

	fb::Vec3 GravityVec;

	

	if (Gravity != 0.f) {


		GravityVec.x = 0;

		GravityVec.y = Gravity;

		GravityVec.z = 0;




		double res[4];

		double mmm = 0.25*Gravity*Gravity;

		double a = -1*EnemyVelocity.Dot(GravityVec) / mmm;

		double b = (EnemyVelocity.Dot(EnemyVelocity)- Driection.Dot(GravityVec) - v0_pow2) / mmm;
			
			

		double c = (2.0f*(Driection.Dot(EnemyVelocity))) / mmm;

		double d = Driection.Dot(Driection) / mmm;



		int res1 = SolveP4(res, a, b, c, d);



		if (res1 == 0) { return 0x1; }

		else {
			//sprintf_s(buffer, 0xff, "root:%f,%f,%f,%f", res[0], res[1], res[2], res[3]); log(buffer);
			time = (float)FindMinPosRoot(res, res1);
			//sprintf_s(buffer, 0xff, "time:%f,", time); log(buffer);
		}




		if (time <= 0)return 0x1;



		Driection = Driection + EnemyVelocity*time;
	

		

		
		flPitch = asinf((Driection.y - 0.5f*Gravity*time*time) / (time*sqrt(v0_pow2)));


		//int i = 0;

		//flPitch = 0;
		//x = MyPosition.DistanceToVector(EnemyPosition);



		//for (; i <= 5; i++) {



		//	time = abs(x / (v0));

		//	EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
		//	EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
		//	EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

		//	Driection = EnemyPosition - MyPosition;

		//	x = abs(Driection.VectorLength2());

		//	tmp = pow(v0, 4) - (Gravity*((Gravity*(x)*(x)) + 2 * (Driection.y)*v0*v0));

		//	if (tmp < 0)return 0x1;

		//	tmp = (v0*v0 - sqrt(tmp)) / (Gravity*x);

		//	if (_isnanf(tmp))return 0x1;

		//	flPitch = atanf(tmp);

		//	if (_isnanf(flPitch))return 0x1;

		//	if (EnemyVelocity.x == 0.f&& EnemyVelocity.y == 0.f&&EnemyVelocity.z == 0.f)break;

		//	if (x <= 5)break;



		//};

		//time = abs(x / (v0*cos(flPitch)));

		//EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
		//EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
		//EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

		//Driection = EnemyPosition - MyPosition;



	}
	else {
		return 0x1;

		time = (float)TimeToHit(Driection, EnemyVelocity, v0_pow2);
		if (time < 0)return 0x1;



		Driection.x = Driection.x + EnemyVelocity.x*time;
		Driection.y = Driection.y + EnemyVelocity.y*time;
		Driection.z = Driection.z + EnemyVelocity.z*time;

		

		flPitch = atan2(Driection.y, Driection.VectorLength2());



	}



	

	if(v1.y!=0)flPitch = flPitch - atan2(v1.y, v1.z);

	if (flPitch > 1.48350f || flPitch < -1.2217f || _isnanf(flPitch))return 0x2;



	flYaw = -atan2(Driection.x, Driection.z);  //y



	if (flYaw < 0)flYaw = flYaw + Twice_PI;


	if (flYaw < 0 || flYaw >Twice_PI || _isnanf(flYaw))return 0x3;



	out->x = flYaw;

	out->y = flPitch;


	return 0x0;
}

fb::ClientPlayer* GetLocalPlayer()
{
	fb::Main* pMain = fb::Main::GetInstance();
	if (!POINTERCHK(pMain))
		return nullptr;

	fb::Client* pClient = pMain->m_pClient;
	if (!POINTERCHK(pClient))
		return nullptr;

	fb::ClientGameContext* pGameContext = pClient->m_pGameContext;
	if (!POINTERCHK(pGameContext))
		return nullptr;

	fb::PlayerManager* pPlayerMngr = pGameContext->m_pPlayerManager;
	if (!POINTERCHK(pPlayerMngr))
		return nullptr;

	return pPlayerMngr->m_pLocalPlayer;
}

float DistanceToCrosshair(fb::Vec3 MyPosition, fb::Vec3 EnemyPosition, 
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




fb::Vec3 getVehicleSpeed(fb::ClientSoldierEntity * soldier)
{
	fb::Vec3 tempvec;
	if (soldier->m_pPlayer->m_pAttachedControllable)
	{
		tempvec = soldier->m_pPlayer->GetVehicleEntity()->GetVelocity();
	}
	else {
		tempvec.x = 0.0f;
		tempvec.y = 0.0f;
		tempvec.z = 0.0f;
	}
	return tempvec;
}



bool IsAlive(fb::ClientControllableEntity* pPlayer)
{

	fb::HealthComponent* pemeHealthComponent = *((fb::HealthComponent**)((intptr_t)pPlayer + 0x140));

	if (POINTERCHK(pemeHealthComponent)) {
		if ((pemeHealthComponent->m_Health > 0 || _isnanf(pemeHealthComponent->m_Health))) { return true; }
		else
		{
			return false;
		}
	};

	return false;
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

	vector->x = vector->x + tmp.x*mTransform->_11 + tmp.y*mTransform->_21 + tmp.z*mTransform->_31  ;
	vector->y = vector->y + tmp.x*mTransform->_12 + tmp.y*mTransform->_22 + tmp.z*mTransform->_32 ;
	vector->z = vector->z + tmp.x*mTransform->_13 + tmp.y*mTransform->_23 + tmp.z*mTransform->_33;
	//vector->w = vector->w + tmp.x*mTransform->_14 + tmp.y*mTransform->_24 + tmp.z*mTransform->_34 + tmp.w*mTransform->_44;

	return 0x0;
}


bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root) {

	double p = (8 * a*c - 3 * b*b) / (8 * a*a);
	double q = (b*b*b - 4 * a*b*c + 8 * a*a*d) / (8 * a*a*a);

	double delta_0 = c*c - 3 * b*d + 12 * a*e;
	double delta_1 = 2 * c*c*c - 9 * b*c*d + 27 * b*b*e + 27 * a*d*d - 72 * a*c*e;



}