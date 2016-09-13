#pragma once

#define M_PI 3.14159265359f

DWORD  AimCorrection2(fb::Vec3 MyPosition, 
	const fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, fb::Vec3  v1, float Gravity, fb::Vec3* out)
{
	try {
		float v0 = sqrt(v1.y*v1.y + v1.z*v1.z);
			
		Gravity = -Gravity;

		fb::Vec3 Driection, EnemyPosition = EnemyP;
		float x, tmp, flPitch, flYaw, time;
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
		//max 0x40002f55
		//min 

		flPitch = flPitch - atan2(v1.y,v1.z);

		if (flPitch > 1.48350f || flPitch < -1.2217f || _isnanf(flPitch))return 0x2;



		flYaw = -atan2(Driection.x, Driection.z);  //y
	


		if (flYaw < 0)flYaw = flYaw + 6.2831f;


		if (flYaw < 0|| flYaw >6.2831f||_isnanf(flYaw))return 0x3;



		out->x = flYaw;

		out->y = flPitch;


		return 0x0;
	}
	catch (int) {
		return 0x4;
	}
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

	if (m_dist0 <= 5.f && fYawDifference < 3.0f)return 409600.f;else


	if (fYawDifference < 0||fYawDifference > 0.125f || _isnanf(fYawDifference))return -2.f;



	flPitchDifference = atan2(vDir.y, vDir.VectorLength2());

	if (_isnanf(flPitchDifference))return -2.f;

	flPitchDifference = abs(flPitchDifference - aimer->m_AimAngles.y);

	if (flPitchDifference > 1.48350f || flPitchDifference < -1.2217f || _isnanf(flPitchDifference))return -2.f;
	x = abs(m_dist1*cos(flPitchDifference)*sin(fYawDifference));
    y= abs(m_dist1*sin(flPitchDifference));
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
		if ((pemeHealthComponent->m_Health > 0||_isnanf(pemeHealthComponent->m_Health))) { return true; }
		else
		{
			return false;
		}
	};

	return false;
}

