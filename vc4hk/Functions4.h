#pragma once

#define M_PI 3.14159265359f
float TimeToHit(fb::Vec3 p, fb::Vec3 v, float s)
{
	float a = v.Dot(v) - s*s;
	float b = 2 * p.Dot(v);
	float c = p.Dot(p);


	float t1 = 0, t2 = 0;


	float de = b*b - 4 * a*c;



	if (de >= 0)
	{
		t1 = (-b + sqrt(de)) / (2 * a);

		t2 = (-b - sqrt(de)) / (2 * a);
	}
	else
	{
		return -2.0f;
	}

	if (t1 <= 0 && t2 <= 0)return -4.f;

	if (t1 <= 0)return t2;

	if (t2 <= 0)return t1;

	return t1 < t2 ? t1 : t2;

}
DWORD  AimCorrection2(fb::Vec3 MyPosition,
	const fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, fb::Vec3  v1, float Gravity, fb::Vec3* out)
{


	float x, tmp, flPitch, flYaw, time, v0 = sqrt(v1.y*v1.y + v1.z*v1.z);
	fb::Vec3 Driection, EnemyPosition;

	if (Gravity != 0.f) {

		EnemyPosition = EnemyP;
		Gravity = -Gravity;



		int i = 0;

		flPitch = 0;
		x = MyPosition.DistanceToVector(EnemyPosition);



		for (; i <= 5; i++) {



			time = abs(x / (v0));

			EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
			EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
			EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

			Driection = EnemyPosition - MyPosition;

			x = abs(Driection.VectorLength2());

			tmp = pow(v0, 4) - (Gravity*((Gravity*(x)*(x)) + 2 * (Driection.y)*v0*v0));

			if (tmp < 0)return 0x1;

			tmp = (v0*v0 - sqrt(tmp)) / (Gravity*x);

			if (_isnanf(tmp))return 0x1;

			flPitch = atanf(tmp);

			if (_isnanf(flPitch))return 0x1;

			if (EnemyVelocity.x == 0.f&& EnemyVelocity.y == 0.f&&EnemyVelocity.z == 0.f)break;

			if (x <= 5)break;



		};

		time = abs(x / (v0*cos(flPitch)));

		EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
		EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
		EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

		Driection = EnemyPosition - MyPosition;



	}
	else {





		time = TimeToHit(EnemyP, EnemyVelocity, v0);
		if (time < 0)return 0x1;



		EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
		EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
		EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

		Driection = EnemyPosition - MyPosition;



		flPitch = atan2(Driection.y, Driection.VectorLength2());

	}





	flPitch = flPitch - atan2(v1.y, v1.z);

	if (flPitch > 1.48350f || flPitch < -1.2217f || _isnanf(flPitch))return 0x2;



	flYaw = -atan2(Driection.x, Driection.z);  //y



	if (flYaw < 0)flYaw = flYaw + 6.2831f;


	if (flYaw < 0 || flYaw >6.2831f || _isnanf(flYaw))return 0x3;



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

float DistanceToCrosshair(fb::Vec3 MyPosition, fb::Vec3 EnemyPosition, const fb::AimAssist* aimer) {

	float fYawDifference, flPitchDifference;

	fb::Vec3 vDir = EnemyPosition - MyPosition;
	float m_dist0 = vDir.len();
	float x, y;
	vDir.normalize();

	float m_dist1 = vDir.len();


	fYawDifference = -atan2(vDir.x, vDir.z);

	if (fYawDifference < 0)fYawDifference = fYawDifference + 6.2831f;


	fYawDifference = abs(fYawDifference - aimer->m_AimAngles.x);

	if (m_dist0 <= 5.f && fYawDifference < 3.0f)return 0.00025f; else


		if (fYawDifference < 0 || fYawDifference > 0.125f || _isnanf(fYawDifference))return -2.f;



	flPitchDifference = atan2(vDir.y, vDir.VectorLength2());

	if (_isnanf(flPitchDifference))return -2.f;

	flPitchDifference = abs(flPitchDifference - aimer->m_AimAngles.y);

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



bool IsAlive(fb::ClientSoldierEntity* pPlayer)
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

DWORD GetVectorFromeVehicle(fb::ClientPlayer* pLocalPlayer,fb::Vec3* vector) {
	
	SM::Matrix* mTransform = nullptr;
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

	tmp = (AABB.m_Max + AABB.m_Min)*0.5f;

	vector->x = vector->x + tmp.x*mTransform->_11 + tmp.y*mTransform->_21 + tmp.z*mTransform->_31 + tmp.w*mTransform->_41;
	vector->y = vector->y + tmp.x*mTransform->_12 + tmp.y*mTransform->_22 + tmp.z*mTransform->_32 + tmp.w*mTransform->_42;
	vector->z = vector->z + tmp.x*mTransform->_13 + tmp.y*mTransform->_23 + tmp.z*mTransform->_33 + tmp.w*mTransform->_43;
	

	return 0x0;
}