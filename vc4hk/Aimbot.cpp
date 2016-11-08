
#include "stdafx.h"

#include "Aimbot.h"
#include "poly34.h"

#include "hkheader.h"

Aimbot::Aimbot()
{
	this->mp_ClosestSoldier = (fb::ClientSoldierEntity*)malloc(sizeof(fb::ClientSoldierEntity));
	this->mp_ClosestPlayer = (fb::ClientPlayer*)malloc(sizeof(fb::ClientPlayer));
	this->VecOfClosestSoldier = new fb::Vec4;
	this->bAimHead = false;
	this->LockOnEnemyFlags = 0;
	this->LockOn_pEnemySoldier = nullptr;
}

fb::Vec4  Aimbot::GetOriginAndUpdateCurrentAngle(fb::ClientPlayer* pLocalPlayer ,fb::ClientWeapon* MyCSW, fb::FiringFunctionData* pFFD,bool b_InVeh) {


	if (b_InVeh) {
		
		fb::MainVarPtr* turrent = fb::MainVarPtr::Singleton();

		SM::Matrix mTransform = turrent->m_turretTransform;

		this->v_curAngle.x = -atan2(mTransform._31, mTransform._33);

		if (this->v_curAngle.x < 0) 
		{
			this->v_curAngle.x = this->v_curAngle.x + Twice_PI;
		}

	
		this->v_curAngle.y = atan2(mTransform._32,
			sqrt(mTransform._33* mTransform._33 + mTransform._31* mTransform._31));

		this->vOrigin.x = mTransform.Translation().x + pFFD->m_ShotConfigData.m_InitialPosition.x;
		this->vOrigin.y = mTransform.Translation().y + pFFD->m_ShotConfigData.m_InitialPosition.y;
		this->vOrigin.z = mTransform.Translation().z + pFFD->m_ShotConfigData.m_InitialPosition.z;
	}
	else {
		SM::Matrix ShootSpaceMat = MyCSW->m_ShootSpace;

		this->v_curAngle.x = -atan2(ShootSpaceMat._31, ShootSpaceMat._33);

		if (this->v_curAngle.x < 0) { this->v_curAngle.x = this->v_curAngle.x + Twice_PI; }

		this->v_curAngle.y = atan2(ShootSpaceMat._32, sqrt(ShootSpaceMat._33* ShootSpaceMat._33 + ShootSpaceMat._31* ShootSpaceMat._31));

		this->vOrigin.x = ShootSpaceMat.Translation().x + pFFD->m_ShotConfigData.m_InitialPosition.x;
		this->vOrigin.y = ShootSpaceMat.Translation().y + pFFD->m_ShotConfigData.m_InitialPosition.y;
		this->vOrigin.z = ShootSpaceMat.Translation().z + pFFD->m_ShotConfigData.m_InitialPosition.z;
	}
	this->vOrigin.w = 0;
	return this->vOrigin;


}




fb::Vec4 * Aimbot::GetClosestPlayer(eastl::vector<fb::ClientPlayer*>* pVecCP, fb::ClientPlayer* pLocalPlayer,
	int BulletClassID, bool InVeh) {

	if (pVecCP->size() < 1) return nullptr;

	bool found = false;
	fb::Vec4 v_EnemyVecTmp;

	float flScreenDistance=-1.f;

	fb::ClientPlayer* pClientPlayer = nullptr;
	fb::ClientSoldierEntity* pEnemySoldier = nullptr;
	fb::ClientSoldierEntity* ClosestSold = nullptr;


	float closestdistance = 9999.0f;

	if (!POINTERCHK(this->LockOn_pEnemySoldier)) {


		for (int i = 0; i < pVecCP->size(); i++)
		{

			pClientPlayer = pVecCP->at(i);


			if (!POINTERCHK(pClientPlayer))
				continue;

			if (pLocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;


			pEnemySoldier = pClientPlayer->GetSoldierEntity();


			if (!POINTERCHK(pEnemySoldier))continue;

			if (!IsAlive(pEnemySoldier))continue;

			if (!pClientPlayer->InVehicle() && pEnemySoldier->m_Occluded)continue;

			fb::RagdollComponent* pRagdoll = *(fb::RagdollComponent**)((intptr_t)pEnemySoldier + 0x580);

			if (!POINTERCHK(pRagdoll))continue;

			if (bAimHead)
			{
				found = pRagdoll->GetBone(fb::UpdatePoseResultData::Head, &v_EnemyVecTmp);
			}

			else
			{
				found = pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, &v_EnemyVecTmp);
			}




			if (!found) {

				if ((pClientPlayer->InVehicle() && BulletClassID == 2441) || InVeh) {
					if (GetVectorFromVehicle(pClientPlayer, &v_EnemyVecTmp) != 0)continue;

				}

				else {
					continue;
				}

			}



			flScreenDistance = DistanceToAimRay(vOrigin, v_EnemyVecTmp, v_curAngle);


			if (flScreenDistance < 0)continue;




			if (flScreenDistance < closestdistance)
			{
				closestdistance = flScreenDistance;
				mp_ClosestSoldier = pEnemySoldier;
				mp_ClosestPlayer = pClientPlayer;
				*VecOfClosestSoldier = v_EnemyVecTmp;

			}

		}


	}
	else {

		pEnemySoldier = this->LockOn_pEnemySoldier;

		if (!POINTERCHK(pEnemySoldier))return nullptr;

		if (!IsAlive(pEnemySoldier))return nullptr;

		pClientPlayer = pEnemySoldier->m_pPlayer;

		if (!POINTERCHK(pClientPlayer))return nullptr;

		if (!pClientPlayer->InVehicle() && pEnemySoldier->m_Occluded)return nullptr;

		fb::RagdollComponent* pRagdoll = *(fb::RagdollComponent**)((intptr_t)pEnemySoldier + 0x580);

		if (!POINTERCHK(pRagdoll))return nullptr;

		if (bAimHead)
		{
			found = pRagdoll->GetBone(fb::UpdatePoseResultData::Head, &v_EnemyVecTmp);



		}

		else
		{
			found = pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, &v_EnemyVecTmp);



		}




		if (!found) {

			if ((pClientPlayer->InVehicle() && BulletClassID == 2441) || InVeh) {


				if (GetVectorFromVehicle(pClientPlayer, &v_EnemyVecTmp) != 0)return nullptr;


			}




			else {
				return nullptr;
			}
		}


		mp_ClosestPlayer = pClientPlayer;
		mp_ClosestSoldier = pEnemySoldier;
		*VecOfClosestSoldier = v_EnemyVecTmp;

	}

	if (POINTERCHK(mp_ClosestPlayer) && POINTERCHK(mp_ClosestSoldier)) {
		return 	VecOfClosestSoldier;
	}
	else { return nullptr; }

}






void Aimbot::NullTmpVar() {
	

};
DWORD  Aimbot::AimCorrection2(fb::Vec4 MyPosition,
	fb::Vec4  EnemyP, fb::Vec4 EnemyVelocity, fb::Vec4  v1, float Gravity, fb::Vec4* out) {


	float flPitch, flYaw, f_time, v0_pow2 = v1.z*v1.z + v1.y + v1.y; // x, tmp,

	fb::Vec4 v_Driection;

	EnemyP = EnemyP - MyPosition;
	MyPosition.w = 0;
	EnemyP.w = 0;
	EnemyVelocity.w = 0;

	

	fb::Vec4 GravityVec;



	if (Gravity != 0.f) {


		GravityVec.x = 0;

		GravityVec.y = Gravity;

		GravityVec.z = 0;
		GravityVec.w = 0;



		double res[4];

		double mmm = 0.25*Gravity*Gravity;

		double a = -1 * EnemyVelocity.Dot(GravityVec) / mmm;

		double b = (EnemyVelocity.Dot(EnemyVelocity) - EnemyP.Dot(GravityVec) - v0_pow2) / mmm;



		double c = (2.0f*(EnemyP.Dot(EnemyVelocity))) / mmm;

		double d = EnemyP.Dot(EnemyP) / mmm;



		int res1 = SolveP4(res, a, b, c, d);



		if (res1 == 0) { return 0x1; }

		else {
			//sprintf_s(buffer, 0xff, "root:%f,%f,%f,%f", res[0], res[1], res[2], res[3]); log(buffer);
			f_time = (float)FindMinPosRoot(res, res1);
			//sprintf_s(buffer, 0xff, "time:%f,", time); log(buffer);
		}




		if (f_time <= 0)return 0x1;



		v_Driection = EnemyP + EnemyVelocity*f_time;





		flPitch = asinf((v_Driection.y - 0.5f*Gravity*f_time*f_time) / (f_time*sqrt(v0_pow2)));


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
	

		f_time = (float)TimeToHit(EnemyP, EnemyVelocity, v0_pow2);

		if (f_time < 0)return 0x1;



		v_Driection = EnemyP + EnemyVelocity*f_time;
		



		flPitch = atan2(v_Driection.y, v_Driection.VectorLength2());



	}


	flPitch = flPitch - atan2(v1.y, v1.z);

	if (flPitch > 1.48350f || flPitch < -1.2217f || _isnanf(flPitch))return 0x2;



	flYaw = -atan2(v_Driection.x, v_Driection.z);  //y



	if (flYaw < 0)flYaw = flYaw + Twice_PI;


	if (flYaw < 0 || flYaw >Twice_PI || _isnanf(flYaw))return 0x3;



	out->x = flYaw;

	out->y = flPitch;


	return 0x0;
	}