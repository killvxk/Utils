#include "stdafx.h"
#include "hkheader.h"
#include "poly34.h"



//char *buffer0= new char[0xff];
//std::ofstream log_file0(
//	"e:\\log\\hk0.log", std::ios_base::out | std::ios_base::trunc);
//
//void logxxx0(const std::string &text)
//{
//
//	log_file0 << text << std::endl;
//}
//




bool MinRealRootOfQuarticFunction(double a, double b, double c, double d, double e, double& root) {

	double p = (8 * a*c - 3 * b*b) / (8 * a*a);
	double q = (b*b*b - 4 * a*b*c + 8 * a*a*d) / (8 * a*a*a);

	double delta_0 = c*c - 3 * b*d + 12 * a*e;
	double delta_1 = 2 * c*c*c - 9 * b*c*d + 27 * b*b*e + 27 * a*d*d - 72 * a*c*e;

}

bool HackKev::IsAlive(fb::ClientControllableEntity* pPlayer)
{
	bool b_isVeh = false;


	fb::HealthComponent* pEmeHealthComponent = *((fb::HealthComponent**)((intptr_t)pPlayer + 0x140));

	if (!IsValidPtr(pEmeHealthComponent))return false;

	__try {
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
HackKev::HackKev() {
	mb_Unlcok = false;
	mb_AmmoBox = false;
	slotG1_list[4][15] = { 0 };
	g_pInputBuffers[123] = { 0.f };
}

void HackKev::VarsUpdate() {

	this->mp_GameContext = fb::ClientGameContext::GetInstance();

	if (IsValidPtr(this->mp_GameContext)) {
		this->mp_PlayerMngr = mp_GameContext->m_pPlayerManager;
	}
	else {
		this->mp_PlayerMngr = nullptr;
	//	this->mp_GameContext = nullptr;
	}

	if (IsValidPtr(this->mp_PlayerMngr)) {

		this->mp_LocalPlayer = mp_PlayerMngr->m_pLocalPlayer;
	}
	else {
		this->mp_LocalPlayer = nullptr;
	}


	mp_CurVehicleCamera = *(void**)(OFFSET_PPCURRENTWEAPONFIRING + 0x10);


	if (IsValidPtr(this->mp_LocalPlayer)) {
		this->mp_LocalSoldier = mp_LocalPlayer->GetSoldierEntity();
	}
	else {
		this->mp_LocalSoldier = nullptr;
	}





}
void  HackKev::AmmoBox() {

	fb::ClientGameContext* p = mp_GameContext;

	if (mb_AmmoBox)return;
	fb::Level* pLevel = p->m_pLevel;


	if (!IsValidPtr(pLevel)) {

		mb_AmmoBox = false;	return;
	}

	if (!IsValidPtr(pLevel->m_TeamEntity[1])) {

		mb_AmmoBox = false;	return;
	};


	intptr_t EndOfArray = 0;

	fb::TeamEntityData* m_teamEntity;

	fb::TeamData* Team;

	for (int i = 1; i <= 2; i++) {

		m_teamEntity = pLevel->m_TeamEntity[i];

		if (!IsValidPtr(m_teamEntity))
			continue;

		Team = m_teamEntity->m_Team;

		slotG1_list[0][0] = Team->m_SoldierCustomization[0]->m_pWeaponTable->m_ppList[2]->m_SelectableUnlocks[0];
		//	slotG2_list[0][0] = Team->m_SoldierCustomization[0]->m_pWeaponTable->m_ppList[3]->m_SelectableUnlocks[0];
		for (int j = 0; j < 4; j++) {

			int index = 1;

			while (index < 15)
			{
				slotG1_list[j][index] = Team->m_SoldierCustomization[j]->m_pWeaponTable->m_ppList[2]->m_SelectableUnlocks[index];
				//	slotG2_list[j][index] = Team->m_SoldierCustomization[j]->m_pWeaponTable->m_ppList[3]->m_SelectableUnlocks[index];
				index++;
			}

		}
		slotG1_list[3][15] = &EndOfArray;
		//slotG2_list[3][15] = &EndOfArray;      //0  //1  //2 //5 //6 //7
		for (int k = 0; k < 4; k++) {

			Team->m_SoldierCustomization[k]->m_pWeaponTable->m_ppList[7]->m_SelectableUnlocks[2] = slotG1_list[2][6]; //ammobox

			Team->m_SoldierCustomization[k]->m_pWeaponTable->m_ppList[2]->m_SelectableUnlocks[0] = slotG1_list[0][11]; //U_Medkit

			Team->m_SoldierCustomization[k]->m_pWeaponTable->m_ppList[5]->m_SelectableUnlocks[0] = slotG1_list[3][2]; //C4
		}
	}

	mb_AmmoBox = true;
}
void HackKev::MiniMap() {

	if (!IsValidPtr(mp_LocalPlayer))return;
	if (!IsValidPtr(mp_PlayerMngr))return;

	eastl::vector<fb::ClientPlayer*>* pVecCP = mp_PlayerMngr->getPlayers();
	if (pVecCP->size() == 0) return;

	for (int i = 0; i < pVecCP->size(); i++)
	{
		__try {

			fb::ClientPlayer* pClientPlayer = pVecCP->at(i);

			if (mp_LocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;

			fb::ClientControllableEntity* pControllable;

			pControllable = pClientPlayer->m_pControlledControllable;
			std::vector<void*> *
				v_pCSTC = new  std::vector<void*>();


			size_t size = GetClientComponentByID(pControllable->m_Complist, v_pCSTC, 378, false, false);


			if (!(size > 0)) {
				continue;
				delete v_pCSTC;
			}
			fb::ClientSpottingTargetComponent* pCSTC;


			for (int index = 0; index < v_pCSTC->size(); index++)
			{
				pCSTC = (fb::ClientSpottingTargetComponent*)v_pCSTC->at(index);

				if (pCSTC->activeSpotType == fb::SpotType_None) { pCSTC->activeSpotType = fb::SpotType_Passive; }
			}


		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

			continue;
		}
	};



}
void  HackKev::VehicleWeaponUpgrade() {


	if (!(mp_LocalPlayer->InVehicle() && mp_CurVehicleCamera)) {
		return;
	}

	__try {
		fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;
		fb::WeaponFiringData* pFiring = pWepFiring->m_pPrimaryFire;
		if (pWepFiring->m_NextWeaponState == 7 || pWepFiring->m_NextWeaponState == 4 ||
			pWepFiring->m_NextWeaponState == 8 || pWepFiring->m_NextWeaponState == 10 ||
			pWepFiring->m_NextWeaponState == 11) {
			pWepFiring->m_NextWeaponState = 3;

		}

		fb::FiringFunctionData* pFFD = pFiring->m_FiringData;
		pFFD->m_Dispersion->MaxAngle = 0.f;
		pFFD->m_Dispersion->MinAngle = 0.f;
		pFFD->m_Dispersion->IncreasePerShot = 0.f;
		pFFD->m_Dispersion->DecreasePerSecond = INFINITY;

		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleX = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleX = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleY = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleY = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilFov = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilFov = 0.f;

		pFFD->m_OverHeat.HeatDropPerSecond = INFINITY;
		pFFD->m_OverHeat.HeatPerBullet = 0.f;
		pFFD->m_OverHeat.OverHeatPenaltyTime = 0.f;
		pFFD->m_OverHeat.OverHeatThreshold = INFINITY;

		pFFD->m_FireLogic.m_BoltAction.m_BoltActionDelay = 0.f;
		pFFD->m_FireLogic.m_BoltAction.m_BoltActionTime = 0.f;


		pFFD->m_FireLogic.ReloadDelay = 0.f;
		pFFD->m_FireLogic.ReloadTime = 0.f;

		float(*a)[4] = (pFFD->m_FireLogic.ReloadTimerArray);

		(*a)[0] = 0.f;
		(*a)[1] = 0.f;
		(*a)[2] = 0.f;
		(*a)[3] = 0.f;


		pFFD->m_FireLogic.ReloadTimeBulletsLeft = 0.f;
		pFFD->m_FireLogic.PreFireDelay = 0.f;
		pFFD->m_FireLogic.PreFireDelayZoomed = 0.f;
		pFFD->m_FireLogic.PreFireRequireHold = 0.f;
		pFFD->m_FireLogic.AutomaticDelay = 0.f;


		float f_AutoReplenishDelay = pFFD->m_Ammo.AutoReplenishDelay;
		if (f_AutoReplenishDelay > 0.1f)pFFD->m_Ammo.AutoReplenishDelay = 0.1f;




		auto veh = fb::MainVarPtr::Singleton()->pVehicleEntry;
		auto vec = veh->GetVehicleVelocity();
		float speed = vec->len();
		if (speed > 65.f) {
			speed = speed*3.6f;

			if (speed < 310.f) {
				g_pInputBuffers[fb::ConceptMoveForward] = 1.f;

				g_pInputBuffers[fb::ConceptMoveFB] = 1.f;
			}
			else if (speed > 312.5f)
			{
				g_pInputBuffers[fb::ConceptMoveFB] = -1.f;
				g_pInputBuffers[fb::ConceptMoveBackward] = 1.f;
				g_pInputBuffers[fb::ConceptCrawl] = 1.f;
				g_pInputBuffers[fb::ConceptBrake] = 1.f;
			}
		}
		//if(	pFFD->m_FireLogic.RateOfFire > 540.f)	pFFD->m_FireLogic.RateOfFire = 4000.f;

	}
	__except (1) {

		return;
	}
}
void  HackKev::WeaponUpgrade() {



	__try {

		//unlock

		if (!mb_Unlcok) {
			LPVOID unlock = *(LPVOID*)OFFSET_SYNCEDBFSETTINGS;

			if (IsValidPtr(unlock)) {

				*(bool*)((intptr_t)unlock + 0x54) = true;
				mb_Unlcok = true;
			}
			else {

				mb_Unlcok = false;
			}

		}


		if (!IsValidPtr(mp_LocalSoldier)) {
			mb_AmmoBox = false;
			mb_Unlcok = false;	return;
		}


		//if (!IsAlive(pLocalSoldier))return;

		fb::ClientSoldierWeaponsComponent* pWepComp = fb::MainVarPtr::Singleton()->pWeaponComp;

		fb::ClientSoldierWeapon* MySW = pWepComp->GetActiveSoldierWeapon();

		if (!IsValidPtr(MySW)) {
			return;
		}


		fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;

		if (!IsValidPtr(pWepFiring)) {
			return;
		}

		fb::FiringFunctionData* pFFD = pWepFiring->m_pPrimaryFire->m_FiringData;

		if (pFFD->m_ShotConfigData.m_InitialSpeed.z < 10.f)return;

		//if (pWepFiring->m_TimeToWait > 0.1f)pWepFiring ->m_TimeToWait= 0.1f;

	//	pWepFiring->m_HoldReleaseMinDelay = 0.f;
	//	pWepFiring->m_hasStoppedFiring = 1;
	//	pWepFiring->m_primaryFireTriggeredLastFrame = 0;

	



		if (pWepFiring->m_NextWeaponState == 7 || pWepFiring->m_NextWeaponState == 4 ||
			pWepFiring->m_NextWeaponState == 8) {
			pWepFiring->m_NextWeaponState = 3;


		}

	


		pFFD->m_Dispersion->MaxAngle = 0.f;
		pFFD->m_Dispersion->MinAngle = 0.f;
		pFFD->m_Dispersion->IncreasePerShot = 0.f;
		pFFD->m_Dispersion->DecreasePerSecond = INFINITY;

		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleX = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleX = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleY = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleY = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MaxRecoilFov = 0.f;
		pFFD->m_FireLogic.m_Recoil.m_MinRecoilFov = 0.f;

		pFFD->m_FireLogic.m_BoltAction.m_BoltActionDelay =0.f;
		pFFD->m_FireLogic.m_BoltAction.m_BoltActionTime = 0.f;

	/*	if (pFFD->m_FireLogic.m_FireLogicType == fb::FireLogicType::fltSingleFireWithBoltAction)
		{
			pFFD->m_FireLogic.RateOfFire = 400.f;

		}*/

		pFFD->m_FireLogic.ReloadDelay = 0.f;
		//pFFD->m_FireLogic.ReloadTime = 0.f;

	//	float(*a)[4] = (pFFD->m_FireLogic.ReloadTimerArray);

		//(*a)[0] = 0.f;
		//(*a)[1] = 0.f;
		//(*a)[2] = 0.f;
		//(*a)[3] = 0.f;

		//pFFD->m_FireLogic.ReloadTimeBulletsLeft = 0.f;
		pFFD->m_FireLogic.PreFireDelay = 0.f;
		pFFD->m_FireLogic.PreFireDelayZoomed = 0.f;
//		pFFD->m_FireLogic.PreFireRequireHold = 0.f;
//		pFFD->m_FireLogic.AutomaticDelay = 0.f;

		pFFD->m_Ammo.AmmoBagPickupDelayMultiplier = 0.001f;
		pFFD->m_Ammo.AmmoBagPickupAmount = -1;
		pFFD->m_Ammo.AutoReplenishDelay = 0.f;

		pFFD->m_OverHeat.HeatDropPerSecond = INFINITY;
		pFFD->m_OverHeat.HeatPerBullet = 0.f;
		pFFD->m_OverHeat.OverHeatPenaltyTime = 0.f;
		pFFD->m_OverHeat.OverHeatThreshold = INFINITY;




		fb::WeaponSway* pSway = pWepFiring->m_Sway;


		fb::GunSwayData* pSwayData = pSway->m_Data;


		fb::BreathControlHandler *pBreath = *(fb::BreathControlHandler **)((intptr_t)mp_LocalSoldier + 0x588);


		pBreath->m_breathControlTimer = 0.f;
		pBreath->m_breathControlMultiplier = 0.f;
		pBreath->m_breathControlPenaltyTimer = 0.f;
		pBreath->m_breathControlpenaltyMultiplier = 0.f;

		pBreath->m_Enabled = 0;


		pSwayData->m_DeviationScaleFactorZoom = 0.f;
		pSwayData->m_GameplayDeviationScaleFactorZoom = 0.f;
		pSwayData->m_DeviationScaleFactorNoZoom = 0.f;
		pSwayData->m_GameplayDeviationScaleFactorNoZoom = 0.f;
		pSwayData->m_FirstShotRecoilMultiplier = 0.f;
		pSwayData->m_ShootingRecoilDecreaseScale = 1000.f;
	}
	__except (1) {

		return;
	}


}

size_t HackKev::GetClientComponentByID(void* p_List,
	std::vector<void*>* ret,
	unsigned int Id, bool CheckUnderUsing,
	bool bGetClientWeaponComponent) {

	//	sprintf_s(buffer0, 0xff, "GetClientComponentByName"); logxxx0(buffer0);

	void* offset = p_List;

	unsigned int size = *(BYTE*)((intptr_t)offset + 0x9);

	//	sprintf_s(buffer0, 0xff, "size:%d", size); logxxx0(buffer0);

	fb::CompTuple* trashclass1 = (fb::CompTuple*)((intptr_t)offset + 0x10);

	std::vector<void*>* vector = ret;

	for (unsigned int obj_index = 0; obj_index < size; obj_index++)

	{
		if (CheckUnderUsing) {
			__int32 flag = trashclass1[obj_index].flags >> 0xA;

			flag = flag & trashclass1[obj_index].flags;

			if (!(flag & 0x2))continue;
		}

		if (bGetClientWeaponComponent) {

			__int32 flag = trashclass1[obj_index].flags;

			if (!((flag & 0x8) && (flag & 0x800)))continue;

		}




		if (trashclass1[obj_index].classid == Id) {

			vector->push_back((void*)(trashclass1[obj_index].Object));



		}

	}




	return vector->size();
}


