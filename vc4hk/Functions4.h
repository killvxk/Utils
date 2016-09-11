#pragma once

#define M_PI 3.14159265359f

DWORD  AimCorrection2(fb::Vec3 MyPosition, fb::Vec3 MyVelocity,
	const fb::Vec3  EnemyP, fb::Vec3 EnemyVelocity, float  v0, float Gravity, fb::Vec3* out)
{
	try {
		Gravity = -Gravity;

		fb::Vec3 Driection, EnemyPosition = EnemyP;
		double x, tmp, flPitch, flYaw, time;
		int i = 0;
		flPitch = 0;
		x = MyPosition.DistanceToVector(EnemyPosition);
		out->z = 0;
		
			
		for (; i <= 5; i++) {



			time = abs(x / (v0));
			
			EnemyPosition.x = EnemyP.x + EnemyVelocity.x*time;
			EnemyPosition.y = EnemyP.y + EnemyVelocity.y*time;
			EnemyPosition.z = EnemyP.z + EnemyVelocity.z*time;

			Driection = EnemyPosition - MyPosition;

			x = abs(Driection.VectorLength2());

			tmp = pow(v0, 4) - (Gravity*((Gravity*(x)*(x)) + 2 * (Driection.y)*v0*v0));
			
			if (tmp <= 0)return 0x1;

			flPitch = atan((v0*v0 - sqrt(tmp)) / (Gravity*x));

			return 100;
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
	
		if (flPitch > 1.4830 || flPitch < -1.221 || _isnan(flPitch))return 0x2;

		//if (flPitch > 1.48350 || flPitch < -1.02200)return 0x2;

		flYaw = -atan2(Driection.x, Driection.z);  //y




		

		if (flYaw> 2 * M_PI ||  _isnan(flYaw))return 0x3;



		out->x = flYaw ;

		out->y = flPitch;


		return 0x0;
	}
	catch (int) {
		return 0x4;
	}
}
float DistanceToCrosshair(fb::Vec3 MyPosition, fb::Vec3 EnemyPosition, const fb::SoldierAimingSimulation* aimer) {

	float fYawDifference, flPitchDifference;

	fb::Vec3 vDir = EnemyPosition - MyPosition;

	float dist = vDir.VectorLength();



	fYawDifference = -atan2(vDir.x, vDir.z);

	if (fYawDifference < 0)fYawDifference = fYawDifference + 2 * M_PI;

	fYawDifference = abs(fYawDifference - aimer->m_Yaw);

	//if (dist < 10 && fYawDifference < 3.0f)return 0.001;else


	if (fYawDifference > 0.125)return -1;



	flPitchDifference = atan2(vDir.y, vDir.VectorLength2());
	if (flPitchDifference >= 1.48350f)return -1;
	else if (flPitchDifference <= -1.2217f)return -1;



	flPitchDifference = abs(flPitchDifference - aimer->m_Pitch);

	return abs(dist*cos(flPitchDifference)*sin(fYawDifference));
}