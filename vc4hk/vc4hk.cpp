// vc4hk.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "../vc3hk/VMTHook.h"

#include "x64_sdk.h"
#include "Functions4.h"
#include<stdio.h>
#include <fstream>



//#define LOGGG

#ifdef LOGGG
#define PRINT(code) code
#else
#define PRINT(code) 
#endif


#pragma region

CVMTHookManager* PresentHook = 0;
typedef HRESULT(__stdcall* tPresent)(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags);
tPresent oPresent;


CVMTHookManager* PreFrameHook = 0;
typedef int(__stdcall* tPreFrameUpdate)(float dt);
tPreFrameUpdate oPreFrameUpdate = 0;

fb::BorderInputNode* g_pBorderInputNode = fb::BorderInputNode::GetInstance();

#pragma endregion Hook
#pragma region

char *buffer = new char[0xff];

float g_pInputBuffers[123];

bool bAimbot = true;
bool AimKeyPressed = false;
bool bAimHead = false;
bool LockOnEme = false;
std::ofstream log_file(
	"E:\\log\\hk.log", std::ios_base::out | std::ios_base::trunc);

int count = 0;
fb::ClientSoldierEntity* LockOn_pEnemySoldier = nullptr;
#pragma endregion Global Vars

void log(const std::string &text)
{

	log_file << text << std::endl;
}
//void _stdcall PlayerIteration()
//{
//	
//		fb::ClientGameContext* g_pGameContext = (fb::ClientGameContext*)OFFSET_CLIENTGAMECONTEXT;
//		if (!POINTERCHK(g_pGameContext)) return;
//
//		fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_pPlayerManager;
//		if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;
//
//		eastl::vector<fb::ClientPlayer*> pVecCP = pPlayerManager->m_players;
//		if (pVecCP.empty()) return;
//
//		//fb::ClientSoldierEntity* pMySoldier = pPlayerManager->m_localPlayer->getSoldierEnt();
//
//		//if (!POINTERCHK(pMySoldier))
//		//	return;
//		//	if (!isalive(pMySoldier->Alive())) return;
//		int size = pVecCP.size();
//		for (int i = 0; i < size; i++)
//		{
//			fb::ClientPlayer* pClientPlayer = pVecCP.at(i);
//			fb::ClientSoldierEntity* pSoldier = pClientPlayer->getSoldierEnt();
//			if (!POINTERCHK(pSoldier)) continue;
//
//			if (pSoldier->isInVehicle()) continue;
//
//			
//
//			
//				fb::ClientSpottingTargetComponent* pCSTC = pSoldier->getComponent<fb::ClientSpottingTargetComponent>("ClientSpottingTargetComponent");
//				if (POINTERCHK(pCSTC)) {
//					if (pCSTC->m_spotType == fb::SpotType_None) { pCSTC->m_spotType = fb::SpotType_Passive; }
//					else
//					{
//						continue;
//					}
//				}
//			
//		}
//	}


void _stdcall Aimbot() {

	float flBulletGrav;
	float zero_angle = 0.f;
	int zero_index = -2;
	float closestdistance = 9999.0f;
	fb::Vec3 flbulletspeed;
	fb::ClassInfo* pType;
	flbulletspeed.z = -2.f;

	fb::ClientSoldierEntity* ClosestSold = nullptr;
	fb::Vec3 EnemyAimVec;
	fb::ClientSoldierEntity* pEnemySoldier = nullptr;

	fb::Main* pMain = fb::Main::GetInstance();
	if (!POINTERCHK(pMain))
		return;

	fb::Client* pClient = pMain->m_pClient;
	if (!POINTERCHK(pClient))
		return;

	fb::ClientGameContext* pGameContext = pClient->m_pGameContext;
	if (!POINTERCHK(pGameContext))
		return;

	fb::PlayerManager* pPlayerMngr = pGameContext->m_pPlayerManager;

	if (!POINTERCHK(pPlayerMngr))
		return;

	fb::ClientPlayer* pLocalPlayer = pPlayerMngr->m_pLocalPlayer;
	if (!POINTERCHK(pLocalPlayer))
		return;

	if (pLocalPlayer->InVehicle())
		return;

	fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->GetSoldierEntity();

	if (!POINTERCHK(pMySoldier))
		return;


	if (!IsAlive(pMySoldier))return;


	fb::SoldierWeaponComponent* pWepComp = *(fb::SoldierWeaponComponent **)((intptr_t)pMySoldier + 0x570);
	if (!POINTERCHK(pWepComp))
		return; else {
		zero_index = pWepComp->m_ZeroingDistanceLevel;

	}

	fb::SoldierWeapon* MySW = pWepComp->GetActiveSoldierWeapon();
	if (!POINTERCHK(MySW))
		return;

	fb::SoldierAimingSimulation* aimer
		= MySW->m_authorativeAiming;


	if (!POINTERCHK(aimer))
		return;


	fb::ClientWeapon* MyCSW = MySW->m_pWeapon;
	if (!POINTERCHK(MyCSW))
		return;



	fb::AimAssist* pAimAssist = aimer->m_pFPSAimer;
	if (!POINTERCHK(pAimAssist))
		return;



	fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;

	if (!POINTERCHK(pWepFiring))
		return;

	fb::PrimaryFire* pFiring = pWepFiring->m_pPrimaryFire;
	if (!POINTERCHK(pFiring))
		return;

	fb::FiringFunctionData* pFFD = pFiring->m_FiringData;
	if (!POINTERCHK(pFFD)) {
		return;
	}
	else {
		flbulletspeed.z = pFFD->m_ShotConfigData.m_InitialSpeed.z;
		flbulletspeed.y = pFFD->m_ShotConfigData.m_InitialSpeed.y;



	}




	void* pBED = pFFD->m_ShotConfigData.m_ProjectileData;
	if (!POINTERCHK(pBED))return;

	//check bullet or missile
	pType = (fb::ClassInfo*)( ((fb::ITypedObject*)(pBED))->GetType());
	if (!POINTERCHK(pType))return;
	switch (pType->m_ClassId)
	{
	case 2441: {
		flBulletGrav = *(float*)((intptr_t)pBED+0x170);

	}; break;
	case 2434: {

		flBulletGrav = *(float*)((intptr_t)pBED + 0x130);

	}; break;


	default:return;
	
	}
	

	



	if (POINTERCHK(MyCSW->m_pWeaponModifier))
	{
		if (POINTERCHK(MyCSW->m_pWeaponModifier->m_ShotModifier)) {

			flbulletspeed.z = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.z;
			flbulletspeed.y = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.y;


		}

		if (POINTERCHK(MyCSW->m_pWeaponModifier->m_ZeroingModifier) && zero_index >= 0) {

			zero_angle = MyCSW->m_pWeaponModifier->m_ZeroingModifier->GetZeroLevelAt(zero_index).m_Angle;
		}
	}


//	sprintf_s(buffer, 0xff, "G:%f", flBulletGrav); log(buffer);

	eastl::vector<fb::ClientPlayer*>* pVecCP = pPlayerMngr->getPlayers();
	if (pVecCP->size() == 0) return;


	SM::Matrix ShootSpaceMat = MyCSW->m_ShootSpace;

	fb::Vec3 Origin;
	Origin.x = ShootSpaceMat.Translation().x + pFFD->m_ShotConfigData.m_InitialPosition.x;
	Origin.y = ShootSpaceMat.Translation().y + pFFD->m_ShotConfigData.m_InitialPosition.y;
	Origin.z = ShootSpaceMat.Translation().z + pFFD->m_ShotConfigData.m_InitialPosition.z;

	if (flbulletspeed.z == -2.f)return;
	fb::Vec3* Enemyvectmp = new fb::Vec3;

	float flScreenDistance;
	fb::ClientPlayer* pClientPlayer=nullptr;
	if (LockOnEme == false || !POINTERCHK(LockOn_pEnemySoldier)) {


		for (int i = 0; i < pVecCP->size(); i++)
		{

			pClientPlayer = pVecCP->at(i);


			if (!POINTERCHK(pClientPlayer))
				continue;

			if (pLocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;


			pEnemySoldier = pClientPlayer->GetSoldierEntity();
			

			if (!POINTERCHK(pEnemySoldier))continue;

			if (!IsAlive(pEnemySoldier))continue;
			if (!pClientPlayer->InVehicle())continue;

			fb::RagdollComponent* pRagdoll = *(fb::RagdollComponent**)((intptr_t)pEnemySoldier + 0x580);

			if (!POINTERCHK(pRagdoll))continue;

			if (bAimHead)
			{
				if (!pRagdoll->GetBone(fb::UpdatePoseResultData::Neck, Enemyvectmp)) {
					if (pClientPlayer->InVehicle()) {
						if (GetVectorFromeVehicle(pClientPlayer, Enemyvectmp) != 0)continue;

					sprintf_s(buffer, 0xff, "G:%f", Enemyvectmp->x); log(buffer);
					


				}
					else{continue; }
				
				} 

			}
			else
			{
				if (!pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, Enemyvectmp)) {
					if (pClientPlayer->InVehicle()) {
						if (GetVectorFromeVehicle(pClientPlayer, Enemyvectmp) != 0)continue;


						sprintf_s(buffer, 0xff, "G:%f", Enemyvectmp->x); log(buffer);


					}
					else { continue; }

				}
			}




			flScreenDistance = DistanceToCrosshair(Origin, *Enemyvectmp, pAimAssist);


			if (flScreenDistance < 0)continue;
			if (flScreenDistance == 0.00025f) {
				ClosestSold = pEnemySoldier;
				closestdistance = flScreenDistance;
				EnemyAimVec = *Enemyvectmp;

			}


			if (flScreenDistance < closestdistance)
			{

				ClosestSold = pEnemySoldier;
				closestdistance = flScreenDistance;
				EnemyAimVec = *Enemyvectmp;

			}

		}


	}
	else {

		pEnemySoldier = LockOn_pEnemySoldier;

		if (!POINTERCHK(pEnemySoldier
		))return;

		if (!IsAlive(pEnemySoldier))return;

		if (!pEnemySoldier->m_pPlayer->InVehicle())return;

		fb::RagdollComponent* pRagdoll = *(fb::RagdollComponent**)((intptr_t)pEnemySoldier + 0x580);

		if (!POINTERCHK(pRagdoll))return;
		if (bAimHead)
		{
			if (!pRagdoll->GetBone(fb::UpdatePoseResultData::Neck, Enemyvectmp)) {
				if (pEnemySoldier->m_pPlayer->InVehicle()) {
					if (GetVectorFromeVehicle(pEnemySoldier->m_pPlayer, Enemyvectmp) != 0)return;





				}
				else { return; }

			}

		}
		else
		{
			if (!pRagdoll->GetBone(fb::UpdatePoseResultData::Spine2, Enemyvectmp)) {
				if (pEnemySoldier->m_pPlayer->InVehicle()) {
					if (GetVectorFromeVehicle(pEnemySoldier->m_pPlayer, Enemyvectmp) != 0)return;





				}
				else { return; }

			}
		}


		if (!POINTERCHK(Enemyvectmp))return;
		ClosestSold = pEnemySoldier;
		EnemyAimVec = *Enemyvectmp;

	}

	if (!POINTERCHK(ClosestSold))return;

	fb::Vec3 * vDir = new fb::Vec3;
	DWORD rc;

	fb::Vec3 enemyspeed;

	enemyspeed.x = 0.f;
	enemyspeed.y = 0.f;
	enemyspeed.z = 0.f;


	if (!IsAlive(ClosestSold))return;
	if (ClosestSold->m_pPlayer->InVehicle()) {
		enemyspeed = getVehicleSpeed(ClosestSold);
	}
		
	else {
		enemyspeed = ClosestSold->GetVelocity(); 
	};

	rc = AimCorrection2(Origin, EnemyAimVec, enemyspeed, flbulletspeed, flBulletGrav, vDir);



	if (!POINTERCHK(vDir)) return;

	if (rc != 0x0) {
		return;
	}

//	sprintf_s(buffer, 0xff, " ori y:%f pit %f aimming,yaw:%f , pitch :%f", pAimAssist->m_AimAngles.x, pAimAssist->m_AimAngles.y,vDir->x,vDir->y); log(buffer);


	if (abs(vDir->x - pAimAssist->m_AimAngles.x) > 2.f)return;

	pAimAssist->m_AimAngles.x = vDir->x;

	if (std::isnormal(aimer->m_Sway.x))pAimAssist->m_AimAngles.x = pAimAssist->m_AimAngles.x - aimer->m_Sway.x;

	pAimAssist->m_AimAngles.y = vDir->y - zero_angle*0.017453295f;

	if (std::isnormal(aimer->m_Sway.y))pAimAssist->m_AimAngles.y = pAimAssist->m_AimAngles.y - aimer->m_Sway.y;

	LockOnEme = true;

	LockOn_pEnemySoldier = ClosestSold;

}





//minimap spot 
void _stdcall MiniMap() {
	fb::Main* pMain = fb::Main::GetInstance();
	if (!POINTERCHK(pMain))
		return;

	fb::Client* pClient = pMain->m_pClient;
	if (!POINTERCHK(pClient))
		return;

	fb::ClientGameContext* pGameContext = pClient->m_pGameContext;
	if (!POINTERCHK(pGameContext))
		return;

	fb::PlayerManager* pPlayerMngr = pGameContext->m_pPlayerManager;

	if (!POINTERCHK(pPlayerMngr))
		return;

	fb::ClientPlayer* pLocalPlayer = pPlayerMngr->m_pLocalPlayer;
	if (!POINTERCHK(pLocalPlayer))
		return;



	fb::ClientSoldierEntity* pLocalSoldier = pLocalPlayer->GetSoldierEntity();

	if (!POINTERCHK(pLocalSoldier))
		return;


	if (!IsAlive(pLocalSoldier))return;



	eastl::vector<fb::ClientPlayer*>* pVecCP = pPlayerMngr->getPlayers();
	if (pVecCP->size() == 0) return;

	

	for (int i = 0; i < pVecCP->size(); i++)
	{

		fb::ClientPlayer* pClientPlayer = pVecCP->at(i);

		if (!POINTERCHK(pClientPlayer)) continue;

		if (pLocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;

		fb::ClientSoldierEntity* pSoldier;
		

		if (!pClientPlayer->InVehicle()) { pSoldier = *(fb::ClientSoldierEntity**)((intptr_t)pClientPlayer + 0x14D0); }
		else {
			pSoldier = (fb::ClientSoldierEntity*)pClientPlayer->GetVehicleEntity();
		}

		
	

		if (!POINTERCHK(pSoldier)) continue;


		fb::ClientSpottingTargetComponent* pCSTC = pSoldier->GetClientSpottingTargetComponent();

		if (POINTERCHK(pCSTC)) {
			if (pCSTC->activeSpotType == fb::SpotType_None) { pCSTC->activeSpotType = fb::SpotType_Passive; }
			else
			{
				continue;
			}
		}

	}


}
void _stdcall SoldierWeaponUpgrade() {


	//unlock
	LPVOID unlock = *(LPVOID*)OFFSET_SYNCEDBFSETTINGS;
	if (POINTERCHK(unlock)) {

		if (*(bool*)((intptr_t)unlock + 0x54) != true) {
			*(bool*)((intptr_t)unlock + 0x54) = true;
		}
	}

	fb::ClientPlayer* pLocalPlayer = GetLocalPlayer();
	if (!POINTERCHK(pLocalPlayer))
		return;

	if (pLocalPlayer->InVehicle())
		return;

	fb::ClientSoldierEntity* pLocalSoldier =pLocalPlayer->GetSoldierEntity();
	if (!POINTERCHK(pLocalSoldier))
		return;

	if (!IsAlive(pLocalSoldier))return;

	fb::BreathControlHandler *pBreath = *(fb::BreathControlHandler **)((intptr_t)pLocalSoldier + 0x588);

	if (POINTERCHK(pBreath)) {
		pBreath->m_breathControlTimer = 0.f;
		pBreath->m_breathControlMultiplier =100.f;
		pBreath->m_breathControlPenaltyTimer = 0.f;
		pBreath->m_breathControlpenaltyMultiplier = 0.f;
		pBreath->m_breathControlActive = 0.f;
		pBreath->m_breathControlInput = 0.f;
		pBreath->m_Enabled = 0;

	}


	fb::SoldierWeaponComponent* pWepComp = *(fb::SoldierWeaponComponent **)((intptr_t)pLocalSoldier + 0x570);
	if (!POINTERCHK(pWepComp))
		return;

	fb::SoldierWeapon* pLW = pWepComp->GetActiveSoldierWeapon();
	if (!POINTERCHK(pLW))
		return;

	fb::WeaponFiring* pFiring = pLW->m_pPrimary;
	if (!POINTERCHK(pFiring))
		return;

	fb::WeaponSway* pSway = pFiring->m_Sway;
	if (!POINTERCHK(pSway))
		return;

	fb::GunSwayData* pSwayData = pSway->m_Data;
	if (!POINTERCHK(pSwayData))
		return;

	//	memset((void*)0x1409A5354, 0x90, 4);
	//	memset((void*)0x1409A535C, 0x90, 2);

	pSwayData->m_DeviationScaleFactorZoom = 0.f;
	pSwayData->m_GameplayDeviationScaleFactorZoom = 0.f;
	pSwayData->m_DeviationScaleFactorNoZoom = 0.f;
	pSwayData->m_GameplayDeviationScaleFactorNoZoom = 0.f;
	pSwayData->m_FirstShotRecoilMultiplier = 0.f;
	pSwayData->m_ShootingRecoilDecreaseScale = 100;

}
int WINAPI hkPreFrame(float DeltaTime)
{


	int returnval = oPreFrameUpdate(DeltaTime);
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
	{
		bAimHead = true;

	}
	else {
		bAimHead =false;
	};
	if (GetAsyncKeyState(VK_LMENU) & 0x8000) {
		AimKeyPressed = true;
	}
	else { AimKeyPressed = false; }

	if (bAimbot &&  AimKeyPressed) {
		Aimbot();
	}
	else {
		LockOnEme = false;
		LockOn_pEnemySoldier = nullptr;
	}

	for (int i = 0; i < 123; i++)
	{
		g_pBorderInputNode->m_InputCache->m_Event[i] += g_pInputBuffers[i];
		g_pInputBuffers[i] = 0.0f;
	}



	return returnval;
}
HRESULT __stdcall hkPresent(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags) {


	SoldierWeaponUpgrade();
	MiniMap();





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

		PreFrameHook = new CVMTHookManager((intptr_t**)fb::BorderInputNode::GetInstance()->m_Vtable);
		oPreFrameUpdate = (tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(3);
		PreFrameHook->dwHookMethod((intptr_t)hkPreFrame, 3);



		PresentHook = new CVMTHookManager((intptr_t**)fb::DxRenderer::GetInstance()->m_pScreen->m_pSwapChain);
		oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
		PresentHook->dwHookMethod((intptr_t)hkPresent, 8);




		LPVOID IcmpCreateFile = (LPVOID)((intptr_t)GetProcAddress(GetModuleHandleW(L"iphlpapi.dll"), "IcmpCreateFile") + 0x327);

		DWORD dwOld;
		//ping spoof
		if (POINTERCHK(IcmpCreateFile)) {
			VirtualProtect((LPVOID)IcmpCreateFile, 3 * sizeof(BYTE), PAGE_EXECUTE_READWRITE, &dwOld);

			memset((LPVOID)IcmpCreateFile, 0x31, 1);
			memset((LPVOID)((intptr_t)IcmpCreateFile + 1), 0xc0, 1);//xor eax,eax
			memset((LPVOID)((intptr_t)IcmpCreateFile + 2), 0x90, 1);//inc eax

			VirtualProtect((LPVOID)IcmpCreateFile, 3 * sizeof(BYTE), dwOld, NULL);


		};


	}break;
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
