
#include "stdafx.h"

#include "Aimbot.h"
#include "poly34.h"

#include "hkheader.h"

Aimbot::Aimbot()
{
	this->ClosestSoldier = nullptr;
	this->bAimHead = false;
	this->LockOnEnemyFlags = 0;
	this->LockOn_pEnemySoldier = nullptr;
}

fb::Vec3 * Aimbot::GetOriginAndUpdateCurrentAngle(fb::ClientPlayer* pLocalPlayer ,fb::ClientWeapon* MyCSW, fb::FiringFunctionData* pFFD,void* pCurVehicleCam) {
	if (this->v_curAngle == nullptr) {

		this->v_curAngle = new fb::Vec3;

	}


	if (this->vOrigin == nullptr) {

		this->vOrigin = new fb::Vec3;

	}

	if (pLocalPlayer->InVehicle() && POINTERCHK(pCurVehicleCam)) {
		SM::Vector3 tmp;
		fb::CUR_turrent* turrent = fb::CUR_turrent::Singleton();

		SM::Matrix mTransform = turrent->m_turretTransform;

		this->v_curAngle->x = -atan2(mTransform._31, mTransform._33);

		if (this->v_curAngle->x < 0) { this->v_curAngle->x = this->v_curAngle->x + Twice_PI; }

		tmp = mTransform.Backward();
		this->v_curAngle->y = atan2(tmp.y, sqrt(tmp.x*tmp.x + tmp.z*tmp.z));
		this->vOrigin->x = mTransform.Translation().x + pFFD->m_ShotConfigData.m_InitialPosition.x;
		this->vOrigin->y = mTransform.Translation().y + pFFD->m_ShotConfigData.m_InitialPosition.y;
		this->vOrigin->z = mTransform.Translation().z + pFFD->m_ShotConfigData.m_InitialPosition.z;
	}
	else {
		SM::Matrix ShootSpaceMat = MyCSW->m_ShootSpace;

		this->v_curAngle->x = -atan2(ShootSpaceMat._31, ShootSpaceMat._33);

		if (this->v_curAngle->x < 0) { this->v_curAngle->x = this->v_curAngle->x + Twice_PI; }

		this->v_curAngle->y = atan2(ShootSpaceMat._32, sqrt(ShootSpaceMat._33* ShootSpaceMat._33 + ShootSpaceMat._31* ShootSpaceMat._31));

		this->vOrigin->x = ShootSpaceMat.Translation().x + pFFD->m_ShotConfigData.m_InitialPosition.x;
		this->vOrigin->y = ShootSpaceMat.Translation().y + pFFD->m_ShotConfigData.m_InitialPosition.y;
		this->vOrigin->z = ShootSpaceMat.Translation().z + pFFD->m_ShotConfigData.m_InitialPosition.z;
	}

	return this->vOrigin;


}




fb::Vec3 *  Aimbot::GetClosestPlayer(eastl::vector<fb::ClientPlayer*>* pVecCP , fb::ClientPlayer* pLocalPlayer,int BulletClassID){

	if (pVecCP->size() == 0) return nullptr;

	bool found = false;
	fb::Vec3* Enemyvectmp = new fb::Vec3;

	float flScreenDistance;

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
				found = pRagdoll->GetBone(fb::UpdatePoseResultData::Neck, Enemyvectmp);
			}

			else
			{
				found = pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, Enemyvectmp);
			}




			if (!found) {

				if ((pClientPlayer->InVehicle() && BulletClassID == 2441) || pLocalPlayer->InVehicle()) {
					if (GetVectorFromeVehicle(pClientPlayer, Enemyvectmp) != 0)continue;

				}

				else {
					continue;
				}

			}

			if (!POINTERCHK(Enemyvectmp))continue;

			flScreenDistance = DistanceToAimRay(*vOrigin, *Enemyvectmp, *v_curAngle);


			if (flScreenDistance < 0)continue;




			if (flScreenDistance < closestdistance)
			{
				closestdistance = flScreenDistance;
				ClosestSoldier = pEnemySoldier;
			
				VecOfClosestSoldier = Enemyvectmp;

			}

		}


	}
	else if (this->LockOnEnemyFlags != 0) {

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
			found = pRagdoll->GetBone(fb::UpdatePoseResultData::Neck, Enemyvectmp);



		}

		else
		{
			found = pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, Enemyvectmp);



		}




		if (!found) {

			if ((pClientPlayer->InVehicle() && BulletClassID == 2441) || pLocalPlayer->InVehicle()) {


				if (GetVectorFromeVehicle(pClientPlayer, Enemyvectmp) != 0)return nullptr;


			}




			else {
				return nullptr;
			}
		}

		if (!POINTERCHK(Enemyvectmp))	return nullptr;

		ClosestSoldier = pEnemySoldier;
		VecOfClosestSoldier = Enemyvectmp;

	}


	return 	this->VecOfClosestSoldier;




}

void Aimbot::NullTmpVar() {
	delete ClosestSoldier;
	delete VecOfClosestSoldier;

	ClosestSoldier = nullptr;
	VecOfClosestSoldier = nullptr;
};
DWORD  Aimbot::AimCorrection2(fb::Vec3 MyPosition,
	fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, fb::Vec3  v1, float Gravity, fb::Vec3* out) {


	float flPitch, flYaw, time, v0_pow2 = v1.z*v1.z + v1.y + v1.y; // x, tmp,

	fb::Vec3 Driection;





	Driection = EnemyP - MyPosition;

	fb::Vec3 GravityVec;



	if (Gravity != 0.f) {


		GravityVec.x = 0;

		GravityVec.y = Gravity;

		GravityVec.z = 0;




		double res[4];

		double mmm = 0.25*Gravity*Gravity;

		double a = -1 * EnemyVelocity.Dot(GravityVec) / mmm;

		double b = (EnemyVelocity.Dot(EnemyVelocity) - Driection.Dot(GravityVec) - v0_pow2) / mmm;



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





	if (v1.y != 0)flPitch = flPitch - atan2(v1.y, v1.z);

	if (flPitch > 1.48350f || flPitch < -1.2217f || _isnanf(flPitch))return 0x2;



	flYaw = -atan2(Driection.x, Driection.z);  //y



	if (flYaw < 0)flYaw = flYaw + Twice_PI;


	if (flYaw < 0 || flYaw >Twice_PI || _isnanf(flYaw))return 0x3;



	out->x = flYaw;

	out->y = flPitch;


	return 0x0;
	}