#include "stdafx.h"
#include "FB_SDK/Frostbite.h"
#include "../vc3hk/VMTHook.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#include "Aimbot.h"
#include "hkheader.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

//#define LOGGG
char *buffer = new char[0xff];
std::ofstream log_file(
	"E:\\log\\hk.log", std::ios_base::out | std::ios_base::trunc);
void logxxx(const std::string &text)
{

	log_file << text << std::endl;
}

#pragma region

CVMTHookManager* PresentHook = 0;
typedef HRESULT(__stdcall* tPresent)(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags);
tPresent oPresent;


CVMTHookManager* PreFrameHook = 0;
typedef  int(__stdcall* tPreFrameUpdate)(void*, float);
tPreFrameUpdate oPreFrameUpdate = 0;

fb::BorderInputNode* g_pBorderInputNode = fb::BorderInputNode::GetInstance();


CVMTHookManager* updateHook = 0;
typedef DWORD_PTR(__stdcall* tUpdate)(DWORD_PTR a1, DWORD_PTR a2, DWORD_PTR a3);
tUpdate oUpdate;

intptr_t* pAntVtable = *(intptr_t**)OFFSET_ANTVTABLE;
intptr_t* pInputNodeVtable = (intptr_t*)fb::BorderInputNode::GetInstance()->m_Vtable;
#pragma endregion Hook
#pragma region

intptr_t last_weaponFiring = 0;


LARGE_INTEGER l_cur_time;

LARGE_INTEGER l_last_time;





float last_yaw_InputBuffer = 0;
float last_pitch_InputBuffer = 0;
float last_roll_InputBuffer = 0;

float g_pInputBuffers[123] = { 0.f };



bool bAimbot = true;
bool AimKeyPressed = false;
bool bAmmoBox = false;
bool b_Unlcok = false;
intptr_t* slotG1_list[4][15] = { 0 };
//intptr_t* slotG2_list[4][15] = { 0 };

Aimbot hkAimbot;







#pragma endregion Global Vars

	std::vector<void*>* GetClientComponentByID(void* p_List,int Id, bool CheckUnderUsing,
	
		bool bGetClientWeaponComponent)

{
	void* offset = p_List;


	int size = *(BYTE*)((intptr_t)offset + 0x8);

	fb::CompTuple* trashclass1 = (fb::CompTuple*)((intptr_t)offset + 0x10);

	std::vector<void*>* vector = new std::vector<void*>;

	for (int obj_index = 0; obj_index < size; obj_index++)

	{
		if (CheckUnderUsing) {
			__int32 flag = trashclass1[obj_index].flags >> 0xA;

			flag = flag & trashclass1[obj_index].flags;

			if (!(flag & 0x2))continue;
		}

		if (bGetClientWeaponComponent) {

			__int32 flag = trashclass1[obj_index].flags;

			

			if (!((flag & 0x8)&&(flag & 0x800)))continue;

		}

		fb::ClassInfo* pType = (fb::ClassInfo*)trashclass1[obj_index].Object->GetType();

		if (IsValidPtr(pType)) {


			if (pType->m_ClassId == Id) {

				vector->push_back((void*)(trashclass1[obj_index].Object));


			}
		}





	}

	if (vector->size()>0) {
		return	vector;
	}
	else {
		delete vector;
		vector = nullptr;
		return nullptr;
	}
}
	


void AmmoBox(fb::ClientGameContext* p) {
	if (bAmmoBox)return;
	fb::Level* pLevel = p->m_pLevel;

	// POINTERCHK
	if (!IsValidPtr(pLevel)) {

		bAmmoBox = false;	return;
	}

	if (!IsValidPtr(pLevel->m_TeamEntity[1])) {

		bAmmoBox = false;	return;
	};




	intptr_t EndOfArray = 0;

	fb::TeamEntityData* m_teamEntity;

	fb::TeamData* Team;







	for (int i = 1; i <= 2; i++) {

		m_teamEntity = pLevel->m_TeamEntity[i];

		if (!IsValidPtr(m_teamEntity))
			return;

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

	bAmmoBox = true;
}




void _stdcall DoAim() {

	float flBulletGrav=0.f;
	float zero_angle = 0.f;
	int zero_index = -2;

	fb::Vec4 v_bulletspeed;
	fb::ClassInfo* pType;
	v_bulletspeed.z = 100.f;
	v_bulletspeed.y = 0.f;
	int bulletId = 0;
	bool b_InVehWithWeapon = false;
	bool b_HasTurret = false;
	bool b_Zoom = false;
	fb::ChildRotationBodyData * p_turrentData = nullptr;
	fb::Vec4 v_Origin;
	fb::Vec4 * curVecOfClosestSoldier;
	fb::ClientSoldierEntity* p_ClosestSoldier;
	fb::ClientPlayer* p_ClosestPlayer;
	fb::ClientSoldierEntity* pEnemySoldier = nullptr;
	float fl_YawMultiplier = 400.0f;
	float fl_PitchMultiplier = 400.0f;



	fb::PlayerManager* pPlayerMngr = fb::ClientGameContext::GetInstance()->m_pPlayerManager;

	fb::ClientPlayer* pLocalPlayer = pPlayerMngr->m_pLocalPlayer;

	fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->GetSoldierEntity();

	//if (!IsAlive(pMySoldier))return;

	void* pCurVehicleCam = *(void**)(OFFSET_PPCURRENTWEAPONFIRING + 0x10);

	//sprintf_s(buffer, 0xff, "	???b_InVehWithWeapon "); logxxx(buffer);

	if (pLocalPlayer->InVehicle() && pCurVehicleCam) {
		b_InVehWithWeapon = true;
		//	sprintf_s(buffer, 0xff, "	b_InVehWithWeapon = true"); logxxx(buffer);
		b_Zoom = *(bool*)((intptr_t)pCurVehicleCam + 0xa8);

	}

	fb::ClientWeapon* MyCSW = nullptr;
	fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;


	if (!b_InVehWithWeapon) {
		fb::ClientSoldierWeaponsComponent* pWepComp = fb::MainVarPtr::Singleton()->pWeaponComp;
		if (!IsValidPtr(pWepComp))
			return; else {
			zero_index = pWepComp->m_ZeroingDistanceLevel;

		}

		fb::ClientSoldierWeapon* MySW = pWepComp->GetActiveSoldierWeapon();
		if (!IsValidPtr(MySW))
			return;



		MyCSW = MySW->m_pWeapon;
		pWepFiring = MySW->m_pPrimary;
	}



	fb::WeaponFiringData* pFiring = pWepFiring->m_pPrimaryFire;



	fb::FiringFunctionData* pFFD = pFiring->m_FiringData;

	v_bulletspeed.z = pFFD->m_ShotConfigData.m_InitialSpeed.z;
	v_bulletspeed.y = pFFD->m_ShotConfigData.m_InitialSpeed.y;




	if (b_InVehWithWeapon) {
		fb::ClientVehicleEntity*	pVehivle = fb::MainVarPtr::Singleton()->pVehicleEntry;

		std::vector<void*>* v_pChildRota
			= GetClientComponentByID(pVehivle->m_Complist,354, true, false);


		if (v_pChildRota) {
			b_HasTurret = true;


			size_t size = v_pChildRota->size() < 2 ? v_pChildRota->size() : 2;


			for (size_t index = 0; index < size; index++)
			{
				fb::ChildRotationBodyData*	p_ChildRotationBodyData =
					((fb::ClientChildComponent*)v_pChildRota->at(index))
					->m_ClientChildBarrelComponent.m_ChildRotationBodyData;

			
				if (IsValidPtr(p_ChildRotationBodyData)) {
					if (p_ChildRotationBodyData->m_RotationAxis == 1) {

						fl_YawMultiplier = p_ChildRotationBodyData->m_AngularMomentumMultiplier;

					}
					else	if (p_ChildRotationBodyData->m_RotationAxis == 0) {

						fl_PitchMultiplier = p_ChildRotationBodyData->m_AngularMomentumMultiplier;

					}
				

				}




			}

			delete v_pChildRota;
			v_pChildRota = nullptr;

		}
		

		
		std::vector<void*>* v_pClientWeaponComponent
			= GetClientComponentByID(pVehivle->m_Complist,358, false,true);
	
		if (v_pClientWeaponComponent) {
		
			size_t size = v_pClientWeaponComponent->size();

			for (size_t index = 0; index < size; index++)
			{
				fb::ClientWeaponComponent*	p_ClientWeaponComponent =
					((fb::ClientWeaponComponent*)v_pClientWeaponComponent->at(index))
					;

				
					if (IsValidPtr(p_ClientWeaponComponent)) {
						if(pWepFiring== p_ClientWeaponComponent->m_pWeaponInfo->GetWeaponFiring()){
							MyCSW = p_ClientWeaponComponent->m_pWeapon;
							break;
						}

					}

			}
			
			

				delete v_pClientWeaponComponent;
				v_pClientWeaponComponent = nullptr;

		

			//sprintf_s(buffer, 0xff, "fl_PitchMultiplier:%f,fl_YawMultiplier:%f",
			//				fl_PitchMultiplier, fl_YawMultiplier); logxxx(buffer);

		}



		
	

	}




		if (IsValidPtr(MyCSW->m_pWeaponModifier))
		{
			if (IsValidPtr(MyCSW->m_pWeaponModifier->m_ZeroingModifier) && zero_index >= 0) {

				zero_angle = MyCSW->m_pWeaponModifier->m_ZeroingModifier->GetZeroLevelAt(zero_index).m_Angle;
			}
			if (IsValidPtr(MyCSW->m_pWeaponModifier->m_ShotModifier)) {

				v_bulletspeed.z = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.z;
				v_bulletspeed.y = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.y;


		}
	}


	void* pBED = pFFD->m_ShotConfigData.m_ProjectileData;



	//check bullet or missile

	pType = (fb::ClassInfo*)(((fb::ITypedObject*)(pBED))->GetType());



	bulletId = pType->m_ClassId;

	switch (bulletId)
	{
	case 2441: {//missile
		v_bulletspeed.z = 1000.f;
		v_bulletspeed.y = 0.f;
		flBulletGrav = 0.f;// *(float*)((intptr_t)pBED + 0x170);
		break;
	};
			   //	case 2434: 
	default: {flBulletGrav = *(float*)((intptr_t)pBED + 0x130); break; };
	}



	if (v_bulletspeed.z <= 5.f)return;
	//sprintf_s(buffer, 0xff, "GetInfo ok"); logxxx(buffer);



	//get origin


	v_Origin = hkAimbot.GetOriginAndUpdateCurrentAngle(pLocalPlayer, MyCSW, pFFD,b_InVehWithWeapon);
//	sprintf_s(buffer, 0xff, "GetOriginAndUpdateCurrentAngle ok"); logxxx(buffer);


	//find closest player


	eastl::vector<fb::ClientPlayer*>* pVecCP = pPlayerMngr->getPlayers();

	curVecOfClosestSoldier = hkAimbot.GetClosestPlayer(pVecCP, pLocalPlayer, bulletId, b_InVehWithWeapon);
	if (curVecOfClosestSoldier == nullptr)return;

	p_ClosestSoldier = hkAimbot.mp_ClosestSoldier;
	p_ClosestPlayer = hkAimbot.mp_ClosestPlayer;


	

	if (p_ClosestSoldier == nullptr)return;
	if (p_ClosestPlayer == nullptr)return;

	fb::Vec4 Vec_Enemyspeed;
	

	

	

	//sprintf_s(buffer, 0xff, "Get Closest Player:%Ix",p_ClosestPlayer); logxxx(buffer);
	//
	//fb::HealthComponent* pHealthComponent = p_ClosestPlayer->m_pControlledControllable->m_pHealthComp;
	//sprintf_s(buffer, 0xff, "Get Closest pHealthComponent:%Ix", pHealthComponent); logxxx(buffer);
	//if (!IsValidPtr(pHealthComponent)) {
	//	return;
	//}

	//sprintf_s(buffer, 0xff, "find vec"); logxxx(buffer);

	//if (pHealthComponent->m_Health == 0.f
	//	&&
	//	pHealthComponent->m_MaxHealth == 0.f&&
	//	pHealthComponent->m_VehicleHealth != 0.f
	//	) {
	//	b_EmenyInVeh = true;
	//	sprintf_s(buffer, 0xff, "Enemy In Veh"); logxxx(buffer);
	//}

	////	sprintf_s(buffer, 0xff, "find closest soldier ok"); logxxx(buffer);
	
	if (p_ClosestPlayer->InVehicle_v()) {

		fb::Vec4 * v = ((fb::ClientVehicleEntity *)p_ClosestPlayer->m_pControlledControllable)->GetVehicleVelocity();
		if (IsValidPtr(v)) {
			Vec_Enemyspeed = *v;
		//	sprintf_s(buffer, 0xff, "v_eh_Vec_Enemyspeed.x:%f\tVec_Enemyspeed.y:%f\tVec_Enemyspeed.z:%f",
			//	Vec_Enemyspeed.x, Vec_Enemyspeed.y, Vec_Enemyspeed.z); logxxx(buffer);
		}
	}
	else
	{
	
		fb::Vec4 * v = p_ClosestSoldier->GetSoldierVelocity();
		if (IsValidPtr(v)) {
			Vec_Enemyspeed = *v;
		//	sprintf_s(buffer, 0xff, "sol_Vec_Enemyspeed.x:%f\tVec_Enemyspeed.y:%f\tVec_Enemyspeed.z:%f",
		//		Vec_Enemyspeed.x, Vec_Enemyspeed.y, Vec_Enemyspeed.z); logxxx(buffer);
		}
	}
	
	
//	Vec_Enemyspeed = Vec_Enemyspeed*1.2f;

		//sprintf_s(buffer, 0xff, "GetVec ok\tG:%f", flBulletGrav); logxxx(buffer);

		fb::Vec4  vDir;



		DWORD n_ReturnCode = hkAimbot.AimCorrection2(v_Origin, *curVecOfClosestSoldier, Vec_Enemyspeed, v_bulletspeed, flBulletGrav, &vDir);


		if (n_ReturnCode != 0x0) {
			return;
		}

		//sprintf_s(buffer, 0xff, "AimCorrection2_OK"); logxxx(buffer);

		if (zero_index > -1)vDir.y = vDir.y - zero_angle*DegToRad; //appo

		float yawDiff = vDir.x - hkAimbot.v_curAngle.x;
		float pitchDiff = vDir.y - hkAimbot.v_curAngle.y;



		if (abs(yawDiff) > 0.8f || abs(pitchDiff) > 0.8f)return;

		if (abs(yawDiff) > 0.8f || abs(pitchDiff) > 0.8f)return;



		if (!b_InVehWithWeapon) {

			g_pInputBuffers[fb::ConceptYaw] = 0.03f*yawDiff;

			g_pInputBuffers[fb::ConceptPitch] = 0.02f*pitchDiff;


		}
		else if (b_HasTurret) {

			if (b_Zoom) {
				yawDiff = yawDiff * 3.f;
				pitchDiff = pitchDiff*3.f;
			}
			if (abs(yawDiff) > 0.10f) {
				if (yawDiff > 0)yawDiff = 0.10f;
				else {
					yawDiff = -0.10f;
				}

				
			}
			else	if (abs(yawDiff) < 0.01f) {
				if (yawDiff > 0)yawDiff = 0.01f;
				else {
					yawDiff = -0.01f;
				}


			}
			g_pInputBuffers[fb::ConceptRoll] = 4000.f/fl_YawMultiplier*yawDiff;

			

			if (abs(pitchDiff) > 0.10f) {
				if (pitchDiff > 0)pitchDiff = 0.10f;
				else {
					pitchDiff = -0.10f;
				}

			}
			else	if (abs(pitchDiff) < 0.01f) {
				if (pitchDiff > 0)pitchDiff = 0.01f;
				else {
					pitchDiff = -0.01f;
				}


			}

			g_pInputBuffers[fb::ConceptPitch] = 3800.f / fl_PitchMultiplier*pitchDiff;



		}
		else { return; }

		hkAimbot.LockOnEnemyFlags = 1;
		hkAimbot.m_LockOn_pEnemyPlayer = p_ClosestPlayer;
		hkAimbot.m_LockOn_pEnemySoldier = p_ClosestSoldier;
		return;


	}





	//minimap spot 
	void _stdcall MiniMap(fb::PlayerManager* pPlayerMngr) {

		fb::ClientSoldierWeaponsComponent* pWepComp = fb::MainVarPtr::Singleton()->pWeaponComp;




		fb::ClientPlayer* pLocalPlayer = pPlayerMngr->m_pLocalPlayer;




		fb::ClientSoldierEntity* pLocalSoldier = pLocalPlayer->GetSoldierEntity();

		if (!IsValidPtr(pLocalSoldier)) return;



		eastl::vector<fb::ClientPlayer*>* pVecCP = pPlayerMngr->getPlayers();
		if (pVecCP->size() == 0) return;



		for (int i = 0; i < pVecCP->size(); i++)
		{
			__try {

				fb::ClientPlayer* pClientPlayer = pVecCP->at(i);

				//if (!IsValidPtr(pClientPlayer)) continue;

				if (pLocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;

				fb::ClientControllableEntity* pControllable;

				pControllable = pClientPlayer->m_pControlledControllable;




				//if (!IsValidPtr(pControllable)) continue;





				std::vector<void*> *
					v_pCSTC = GetClientComponentByID(pControllable->m_Complist,366, false,false);


				if (!v_pCSTC) continue;




				fb::ClientSpottingTargetComponent* pCSTC;


				for (int index = 0; index < v_pCSTC->size(); index++)
				{
					pCSTC = (fb::ClientSpottingTargetComponent*)v_pCSTC->at(index);


					if (pCSTC->activeSpotType == fb::SpotType_None) { pCSTC->activeSpotType = fb::SpotType_Passive; }




				}

				delete v_pCSTC;

				v_pCSTC = nullptr;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				continue;
			}
		};





	}

	void _stdcall VehWeaponUpgrade() {

		__try{
		fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;
		fb::WeaponFiringData* pFiring = pWepFiring->m_pPrimaryFire;



		fb::FiringFunctionData* pFFD = pFiring->m_FiringData;
		pFFD->m_Dispersion->MaxAngle = 0.f;
		pFFD->m_Dispersion->MinAngle = 0.f;
		pFFD->m_Dispersion->IncreasePerShot = 0.f;
		pFFD->m_Dispersion->DecreasePerSecond = 1000.f;

		pFFD->m_FireLogic.MaxRecoilAngleX = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleX = 0.f;
		pFFD->m_FireLogic.MaxRecoilAngleY = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleY = 0.f;
		pFFD->m_FireLogic.MaxRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleZ = 0.f;

		pFFD->m_OverHeat.HeatDropPerSecond = 1000.f;
		pFFD->m_OverHeat.HeatPerBullet = 0.f;
		pFFD->m_OverHeat.OverHeatPenaltyTime = 0.f;
		pFFD->m_OverHeat.OverHeatThreshold = 1000000.f;

		auto veh = fb::MainVarPtr::Singleton()->pVehicleEntry;
		auto vec = veh->GetVehicleVelocity();
		float speed = vec->len();
		if (speed>65.f) {
			speed = speed*3.6f;
	
			if (speed < 310.f) {
				g_pInputBuffers[fb::ConceptMoveForward] = 1.f;
			
				g_pInputBuffers[fb::ConceptMoveFB] = 1.f;
			}
		else if(speed>312.5f)
		{
			g_pInputBuffers[fb::ConceptMoveFB] = -1.f;
			g_pInputBuffers[fb::ConceptMoveBackward] = 1.f;
			g_pInputBuffers[fb::ConceptCrawl] = 1.f;
			g_pInputBuffers[fb::ConceptBrake] = 1.f;
		}
		}
if(	pFFD->m_FireLogic.RateOfFire > 540.f)	pFFD->m_FireLogic.RateOfFire = 4000.f;

	}
		__except (1) {

			return;
		}
	}

	void _stdcall WeaponUpgrade() {
		__try {

		//unlock

		if (!b_Unlcok) {
			LPVOID unlock = *(LPVOID*)OFFSET_SYNCEDBFSETTINGS;

			if (IsValidPtr(unlock)) {

				*(bool*)((intptr_t)unlock + 0x54) = true;
				b_Unlcok = true;
			}
			else {

				b_Unlcok = false;
			}

		}


		fb::ClientGameContext* pGameContext = fb::ClientGameContext::GetInstance();


		fb::PlayerManager* pPlayerMngr = pGameContext->m_pPlayerManager;


		MiniMap(pPlayerMngr);



		fb::ClientPlayer* pLocalPlayer = pGameContext->m_pPlayerManager->m_pLocalPlayer;



		void* pCurVehicleCam = *(void**)(OFFSET_PPCURRENTWEAPONFIRING + 0x10);

		if ((pLocalPlayer->InVehicle() && pCurVehicleCam)) {
			VehWeaponUpgrade();
		
			return;
		
		}


		AmmoBox(pGameContext);


		fb::ClientSoldierEntity* pLocalSoldier = pLocalPlayer->GetSoldierEntity();

		if (!IsValidPtr(pLocalSoldier)) {
			bAmmoBox = false;	b_Unlcok = false;	return;
		}

		//if (!IsAlive(pLocalSoldier))return;

		fb::ClientSoldierWeaponsComponent* pWepComp = fb::MainVarPtr::Singleton()->pWeaponComp;



		fb::ClientSoldierWeapon* MySW = pWepComp->GetActiveSoldierWeapon();

		if (!IsValidPtr(MySW)) {
			return;
		}
	

		 fb::WeaponFiring*	pWepFiring = MySW->m_pPrimary;

		 if (!IsValidPtr(pWepFiring)) {
			 return;
		 }


		fb::FiringFunctionData* pFFD = pWepFiring->m_pPrimaryFire->m_FiringData;

		

		if (pFFD->m_ShotConfigData.m_InitialSpeed.z < 10.f)return;


		pFFD->m_Dispersion->MaxAngle = 0.f;
		pFFD->m_Dispersion->MinAngle = 0.f;
		pFFD->m_Dispersion->IncreasePerShot = 0.f;
		pFFD->m_Dispersion->DecreasePerSecond = 1000.f;

		pFFD->m_FireLogic.MaxRecoilAngleX = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleX = 0.f;
		pFFD->m_FireLogic.MaxRecoilAngleY = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleY = 0.f;
		pFFD->m_FireLogic.MaxRecoilAngleZ = 0.f;
		pFFD->m_FireLogic.MinRecoilAngleZ = 0.f;

		pFFD->m_OverHeat.HeatDropPerSecond = 1000.f;
		pFFD->m_OverHeat.HeatPerBullet = 0.f;


		fb::WeaponSway* pSway = pWepFiring->m_Sway;


		fb::GunSwayData* pSwayData = pSway->m_Data;


		fb::BreathControlHandler *pBreath = *(fb::BreathControlHandler **)((intptr_t)pLocalSoldier + 0x588);


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
		pSwayData->m_ShootingRecoilDecreaseScale = 1000.f;	}
		__except (1) {

			return;
		}

	}



	DWORD_PTR hkUpdate(DWORD_PTR a1, DWORD_PTR a2, DWORD_PTR a3)//ICY
	{

		/*if (a1)
			*(bool*)(a1 + 0xEC) = true;

		if (a2)
			*(bool*)(a2 + 0x8A) = true;*/

		return oUpdate(a1, a2, a3);
	}
	int  __stdcall  hkPreFrame(void* ptr, float DeltaTime)
	{
		__try
		{
			WeaponUpgrade();
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {};
		__try
		{




			if (GetAsyncKeyState(0x56) & 0x8000) {
				hkAimbot.bAimHead = true;

			}
			else { hkAimbot.bAimHead = false; }

			if ((GetAsyncKeyState(VK_LMENU) & 0x8000) || hkAimbot.bAimHead) {
				AimKeyPressed = true;
			}
			else {
				AimKeyPressed = false;
			}


			if (bAimbot &&  AimKeyPressed) {

				DoAim();
			}
			else {
				hkAimbot.LockOnEnemyFlags = 0;

			}


			for (int i = 0; i < 60; i++) {
			
			
			if(	isnormal(g_pInputBuffers[i]))g_pBorderInputNode->m_InputCache->m_Event[i] = g_pInputBuffers[i];
				g_pInputBuffers[i] = 0.f;
			}


				
			
		}


		__except (EXCEPTION_EXECUTE_HANDLER)
		{


		}
		return  oPreFrameUpdate(ptr, DeltaTime);
	}




	void writeJMP(BYTE* src, BYTE* dst, const int len)
	{
		DWORD64 dwRelAddr;
		DWORD dwOldProtect;

		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);

		dwRelAddr = (DWORD64)(dst - src) - 5;

		src[0] = 0xE9;

		*((DWORD64*)(src + 0x1)) = dwRelAddr;

		for (DWORD64 c = 0x5; c < len; c++)
			*(src + c) = 0x90;

		VirtualProtect(src, len, dwOldProtect, &dwOldProtect);
	}
	DWORD hkIcmpSendEcho(
		    HANDLE                 IcmpHandle,
	    IPAddr                 DestinationAddress,
		     LPVOID                 RequestData,
		     WORD                   RequestSize,
	 PIP_OPTION_INFORMATION RequestOptions,
		    LPVOID                 ReplyBuffer,
		    DWORD                  ReplySize,
		     DWORD                  Timeout
	) {


		IPAddr		hkDestinationAddress = 0x0101370A;


		
		return IcmpSendEcho2(IcmpHandle,NULL,NULL, NULL,
			hkDestinationAddress,
			RequestData,
			RequestSize,
			RequestOptions, ReplyBuffer, ReplySize, Timeout
			);
	}
	

	HRESULT __stdcall hkPresent(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags) {




		return oPresent(thisptr, SyncInterval, Flags);
	}


	BOOL APIENTRY DllMain(HMODULE hModule,
		DWORD  ul_reason_for_call,
		LPVOID lpReserved
	)
	{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH: {

			DisableThreadLibraryCalls(hModule);
			DWORD old;
			PreFrameHook = new CVMTHookManager((intptr_t**)fb::BorderInputNode::GetInstance()->m_Vtable);
			oPreFrameUpdate = (tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(3);
			PreFrameHook->dwHookMethod((intptr_t)hkPreFrame, 3);

			




			PresentHook = new CVMTHookManager((intptr_t**)fb::DxRenderer::GetInstance()->m_pScreen->m_pSwapChain);
			oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
			PresentHook->dwHookMethod((intptr_t)hkPresent, 8);



			VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);

			//	*(intptr_t*)((intptr_t)pAntVtable + 11 * 8) = (intptr_t)hkUpdate;

			VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), old, nullptr);

			printf_s("hook!");
			sprintf_s(buffer, 0xff, "Hook"); logxxx(buffer);


				LPVOID pfn_IcmpSendEcho = (LPVOID)((intptr_t)GetProcAddress(GetModuleHandleW(L"iphlpapi.dll"), "IcmpSendEcho"));

				



					
				if (IsValidPtr(pfn_IcmpSendEcho)
					) {

					writeJMP((BYTE*)pfn_IcmpSendEcho, (BYTE*)hkIcmpSendEcho,9);

					//DWORD dwOld;



					//IcmpCreateFile = (LPVOID)((intptr_t)IcmpCreateFile + 0x85);

					//VirtualProtect((LPVOID)IcmpCreateFile, 13, PAGE_EXECUTE_READWRITE, &dwOld);


					//memset((LPVOID)IcmpCreateFile, 0xb8, 1);

					//memset((LPVOID)((intptr_t)IcmpCreateFile + 1), 0x11, 1);//ping ms

					//memset((LPVOID)((intptr_t)IcmpCreateFile + 2), 0x00, 3);//



					//memset((LPVOID)((intptr_t)IcmpCreateFile + 5), 0x89, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 6), 0x43, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 7), 0x08, 1);


					//memset((LPVOID)((intptr_t)IcmpCreateFile + 8), 0xe9, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 9), 0x74, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 10), 0xff, 3);


					//VirtualProtect((LPVOID)IcmpCreateFile, 13, dwOld, NULL);



					//IcmpCreateFile = (LPVOID)((intptr_t)IcmpCreateFile - 0x85);


					//VirtualProtect((LPVOID)IcmpCreateFile, 6, PAGE_EXECUTE_READWRITE, &dwOld);

					//memset((LPVOID)IcmpCreateFile, 0xe9, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 1), 0x80, 1);
					//memset((LPVOID)((intptr_t)IcmpCreateFile + 2), 0x00, 3);

					//memset((LPVOID)((intptr_t)IcmpCreateFile + 5), 0x90, 1);


					//VirtualProtect((LPVOID)IcmpCreateFile, 6, dwOld, NULL);
				};


		}; break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH: {

			if (PresentHook != nullptr)PresentHook->UnHook();
			if (PreFrameHook != nullptr)PreFrameHook->UnHook();
			log_file.close();
		}
								 break;
		}
		return TRUE;
	}
