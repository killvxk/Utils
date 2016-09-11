
#include "stdafx.h"
#include "FB SDK\Frostbite.h"

#include "Functions.h"
#include "VMTHook.h"
//void* g_pOriginalGetRecoil = NULL;
//void* g_pOriginalGetDeviation = NULL;
//void** g_pGetRecoilVTableAddress = (void**)0x20a3acc;
//void** g_pGetDeviationVTableAddress = (void**)0x20a3ac8;
#pragma region
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return malloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	EASTL_ASSERT(alignment <= 8);
	return malloc(size);
}
#pragma endregion EASTL

#pragma region
CVMTHookManager* PreFrameHook = 0;
typedef int(__stdcall* tPreFrameUpdate)(float dt);
tPreFrameUpdate oPreFrameUpdate = 0;

fb::BorderInputNode* g_pBorderInputNode = fb::BorderInputNode::Singleton();

CVMTHookManager* PresentHook = 0;
typedef signed int(__stdcall* tPresent)(int, int, int);
tPresent oPresent;


#pragma endregion Hook

#pragma region
LPCSTR time = __TIME__;
float g_pInputBuffers[123];

DWORD GIVEDAMAGE = 0x00770F40;
DWORD ori_GetRecoil = 0x701a50;//fb__GunSway__getRecoil .text 00701A50 
DWORD ori_getDispersion = 0x701a00;//fb__GunSway__getDispersion

bool bDrawMenu = false;

bool bAutoSpot = false;

bool bPerfectJet = false;

bool bAutoStandUp = false;

bool bNoRecoil = true;
bool bNoBreath = true;
bool bNoSpread = true;
bool bNoSway = true;
bool bInstantKill = false;
bool bInstantBullet = true;

std::map<int, fb::WeaponModifier*> oldModifier;


FILE * m_log;
bool bAimbot = true;
bool bAimHead = false;
bool bVisibilityChecks = false;



bool bMinimapHack = true;
bool bForceSquadSpawn = false;
bool bSpottedExplosive = true;



int cl_SoldierWeapon = 0xffff;

bool AimKeyPressed = false;
bool LockOnEme = false;
fb::ClientSoldierEntity* LockOn_pEnemySoldier;

#pragma endregion Global Vars



DWORD WINAPI PBSSThread(LPVOID a)
{
	while (true)
	{
		*(PDWORD)0x233D978 = 0;
		//*(DWORD*)0x0235DB14 = 0;
	}
	return 1;
};


#pragma region HookRecoil

void _stdcall Aimbot()
{
	float flBulletGrav;
	float flbulletspeed;
	fb::ClientSoldierAimingSimulation* aimer;
	fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
	if (!POINTERCHK(g_pGameContext))
		return;

	fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
	if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty())
		return;

	fb::ClientPlayer* pLocalPlayer = pPlayerManager->m_localPlayer;
	if (!POINTERCHK(pLocalPlayer))
		return;

	fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->getSoldierEnt();
	if (!POINTERCHK(pMySoldier))
		return;

	if (!pMySoldier->IsAlive()) return;

	//int iWeaponID = GetWeaponID(pMySoldier);


	if (pMySoldier->isInVehicle())return;

	fb::ClientSoldierWeapon* MyCSW = pMySoldier->GetCSW();
	//valid checks on Weapons
	if (!POINTERCHK(MyCSW)
		|| !POINTERCHK(MyCSW->m_weapon)
		|| !POINTERCHK(MyCSW->m_predictedFiring)
		|| !POINTERCHK(MyCSW->m_predictedFiring->m_data->m_primaryFire)) return;

	fb::FiringFunctionData* pFFD = pMySoldier->getCurrentWeaponFiringData()->m_primaryFire;
	if (!POINTERCHK(pFFD)) return;

	//weaponmodifier only active if its your mainweapon
	fb::BulletEntityData* pBED;
	if (POINTERCHK(MyCSW)
		&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier)
		&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData))
	{
		pBED = reinterpret_cast<fb::BulletEntityData*>(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData);
	
		if (!POINTERCHK(pBED)) pBED = pFFD->m_shot.m_projectileData;
	}
	else
		pBED = pFFD->m_shot.m_projectileData;
	if (!POINTERCHK(pBED)) {

		return;
	}


	if (POINTERCHK(MyCSW)
		&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponShotModifier)	)
	{
		flbulletspeed = MyCSW->m_weaponModifier.m_weaponShotModifier->m_initialSpeed.z;
		
	
	}
	else{
		flbulletspeed = pFFD->m_shot.m_initialSpeed.z;
	}
		



	 flBulletGrav = pBED->m_gravity;
	
	//check weapon modifier

//	if ((iWeaponID == -1) ||  pFFD->m_shot.m_initialSpeed.z <= 20.0f)return;


	aimer = MyCSW->m_authorativeAiming;
	if (!POINTERCHK(aimer))
		return;




	if (pMySoldier->isInVehicle())return;
	eastl::vector<fb::ClientPlayer*> pVecCP = pPlayerManager->m_players;

	if (pVecCP.empty())
		return;

	int size = pVecCP.size();

	fb::GameRenderer::Singleton()->m_viewParams.view.Update();//matrix not filled by default
	fb::Vec3 Origin = fb::GameRenderer::Singleton()->m_viewParams.view.m_viewMatrixInverse.trans;


	fb::ClientPlayer* ClosestClient = NULL;
	fb::ClientSoldierEntity* ClosestSold = NULL;
	fb::Vec3 EnemyAimVec;
	fb::ClientSoldierEntity* pEnemySoldier;
	int index = 0;
	fb::Vec3 Enemyvectmp;

	if (LockOnEme == false
		|| !POINTERCHK(LockOn_pEnemySoldier)) {
		//float closestdistanceworld = 9999.0f;
		float flScreenDistance;
		float closestdistance = 9999.0f;
		for (int i = 0; i < size; i++)
		{
			fb::ClientPlayer* pClientPlayer = pVecCP.at(i);
			if (pMySoldier->m_teamId == pClientPlayer->m_teamId)
				continue;

			pEnemySoldier = pClientPlayer->getSoldierEnt();
			if (!POINTERCHK(pEnemySoldier))
				continue;

			if (!isalive(pEnemySoldier->isAlive()))
				continue;

			fb::WeakPtr<fb::ClientSoldierEntity>* corpse = &pClientPlayer->m_corpse;
			if (corpse->GetData()) continue;


			if (bAimHead)
			{
				if (!GetBonePos(pEnemySoldier, fb::Neck, &Enemyvectmp)) continue;

			}
			else
			{
				if (!GetBonePos(pEnemySoldier, fb::Spine2, &Enemyvectmp)) continue;
			}

			if (bVisibilityChecks)
			{
				if (!IsVisible(&Enemyvectmp, pMySoldier, pEnemySoldier)) {
					if (bAimHead)
					{
						if (!GetBonePos(pEnemySoldier, fb::Spine2, &Enemyvectmp)) continue;
					}
					else {
						if (!GetBonePos(pEnemySoldier, fb::Neck, &Enemyvectmp)) continue;
					}

					if (!IsVisible(&Enemyvectmp, pMySoldier, pEnemySoldier))continue;
				}
			}

			flScreenDistance = DistanceToCrosshair(Origin, Enemyvectmp, aimer);
			if (flScreenDistance < 0)continue;
			/*float ScreenY = fb::DxRenderer::Singleton()->m_screenInfo.m_nHeight / 2;
			float ScreenX = fb::DxRenderer::Singleton()->m_screenInfo.m_nWidth / 2;
			fb::Vec3 EnemyScreen;
			ProjectToScreen(&Enemyvectmp, &EnemyScreen);

			float PosX = fabs(ScreenX - EnemyScreen.x);
			float PosY = fabs(ScreenY - EnemyScreen.y);

			 =PosX*PosX + PosY*PosY;*/

			if (flScreenDistance < closestdistance)
			{
				ClosestClient = pClientPlayer;
				ClosestSold = pEnemySoldier;
				closestdistance = flScreenDistance;
				EnemyAimVec = Enemyvectmp;
				index = i;
			}
		}
		if (!POINTERCHK(ClosestClient))
			return;

		if (!POINTERCHK(ClosestSold))
			return;

	}
	else {
		if (!POINTERCHK(LockOn_pEnemySoldier))return;
		pEnemySoldier = LockOn_pEnemySoldier;
		if (!POINTERCHK(pEnemySoldier))return;


		if (!isalive(pEnemySoldier->isAlive()))return;



		if (bAimHead)
		{
			if (!GetBonePos(pEnemySoldier, fb::Neck, &Enemyvectmp)) return;

		}
		else
		{
			if (!GetBonePos(pEnemySoldier, fb::Spine2, &Enemyvectmp)) return;
		}

		if (bVisibilityChecks)
		{
			if (!IsVisible(&Enemyvectmp, pMySoldier, pEnemySoldier)) {
				if (bAimHead)
				{
					if (!GetBonePos(pEnemySoldier, fb::Spine2, &Enemyvectmp)) return;
				}
				else {
					if (!GetBonePos(pEnemySoldier, fb::Neck, &Enemyvectmp)) return;
				}

				if (!IsVisible(&Enemyvectmp, pMySoldier, pEnemySoldier))return;
			}
		}

		ClosestSold = pEnemySoldier;
		EnemyAimVec = Enemyvectmp;
		if (!POINTERCHK(ClosestSold))
			return;
	}








	fb::Vec3 * vDir = new fb::Vec3;
	DWORD rc;


	if (ClosestSold->isInVehicle())
	{
		fb::Vec3 myspeed = pMySoldier->linearVelocity();
		fb::Vec3 enemyspeed = getVehicleSpeed(ClosestSold);

		rc = AimCorrection2(Origin, myspeed, EnemyAimVec, enemyspeed, flbulletspeed, flBulletGrav, vDir);
	}
	else
	{
		fb::Vec3 myspeed = pMySoldier->linearVelocity();
		fb::Vec3 enemyspeed = ClosestSold->linearVelocity();

		rc = AimCorrection2(Origin, myspeed, EnemyAimVec, enemyspeed, flbulletspeed, flBulletGrav, vDir);
	}

	if (!POINTERCHK(vDir)) return;
	if (rc != 0x0)return;

	//	if (!pMySoldier->isInVehicle()) { 



	aimer->m_fpsAimer->m_pitch = vDir->x;


	aimer->m_fpsAimer->m_yaw = vDir->y;

	LockOnEme = true;
	LockOn_pEnemySoldier = ClosestSold;
	//	}
}



__declspec(naked) void hkGetRecoil(void)
{
	__asm
	{
		push esi
		push edi
		xor edi, edi
		mov esi, ecx
		mov[esi + 0x164], edi
		mov[esi + 0x16C], edi
		pop edi
		pop esi
		jmp dword ptr[ori_GetRecoil]


	}
}
__declspec(naked) void hkGetDispersion(void)
{
	__asm {
		push esi
		push edi
		xor edi, edi
		mov esi, ecx
		mov[esi + 0x140], edi

		mov[esi + 0x13C], edi

		pop edi
		pop esi

		jmp dword ptr[ori_getDispersion]
	}
}




void _stdcall HookRecoil(fb::WeaponSway* pWps)
{
	if (bNoSpread)
	{
		if ((void*)hkGetDispersion != HookVtblFunction(pWps, hkGetDispersion, 24))
		{
			HookVtblFunction(pWps, hkGetDispersion, 24);
		}

	}
	if (bNoRecoil) {
		if ((void*)hkGetRecoil != HookVtblFunction(pWps, hkGetRecoil, 25))
		{
			HookVtblFunction(pWps, hkGetRecoil, 25);
		}

	}
}

#pragma endregion HookRecoil
void _stdcall PlayerIteration()
{
	if (bMinimapHack || bForceSquadSpawn)
	{
		fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
		if (!POINTERCHK(g_pGameContext)) return;

		fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
		if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;

		eastl::vector<fb::ClientPlayer*> pVecCP = pPlayerManager->m_players;
		if (pVecCP.empty()) return;

		//fb::ClientSoldierEntity* pMySoldier = pPlayerManager->m_localPlayer->getSoldierEnt();

		//if (!POINTERCHK(pMySoldier))
		//	return;
	//	if (!isalive(pMySoldier->Alive())) return;
		int size = pVecCP.size();
		for (int i = 0; i < size; i++)
		{
			fb::ClientPlayer* pClientPlayer = pVecCP.at(i);
			fb::ClientSoldierEntity* pSoldier = pClientPlayer->getSoldierEnt();
			if (!POINTERCHK(pSoldier)) continue;

			if (pSoldier->isInVehicle()) continue;

			if (bForceSquadSpawn)
				pClientPlayer->m_isAllowedToSpawnOn = true;

			if (bMinimapHack)
			{
				fb::ClientSpottingTargetComponent* pCSTC = pSoldier->getComponent<fb::ClientSpottingTargetComponent>("ClientSpottingTargetComponent");
				if (POINTERCHK(pCSTC)) {
					if (pCSTC->m_spotType == fb::SpotType_None) { pCSTC->m_spotType = fb::SpotType_Passive; }
					else
					{
						continue;
					}
				}
			}
		}
	}
}
void _stdcall EntityWorld()
{
	if (bMinimapHack || bSpottedExplosive)
	{
		fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
		if (!POINTERCHK(g_pGameContext)) return;

		fb::ClientLevel* g_pLevel = g_pGameContext->m_level;
		if (!POINTERCHK(g_pLevel)) return;

		fb::GameWorld* g_pGameWorld = g_pLevel->m_gameWorld;
		if (!POINTERCHK(g_pGameWorld)) return;

		if (bMinimapHack)
		{
			fb::EntityWorld::EntityCollection vehicle = g_pGameWorld->m_collections.at(ENTITY_CLIENT_VEHICLE);
			if (vehicle.firstSegment)
			{
				for (int i = 0; i < (int)vehicle.firstSegment->m_Collection.size(); i++)
				{

					fb::ClientVehicleEntity* pEntity = reinterpret_cast<fb::ClientVehicleEntity*>(vehicle.firstSegment->m_Collection.at(i));
					if (POINTERCHK(pEntity))
					{
						fb::ClientSpottingTargetComponent* vehicleSpotting = pEntity->getComponent<fb::ClientSpottingTargetComponent>("ClientSpottingTargetComponent");
						if (POINTERCHK(vehicleSpotting)) {
							
							
							if (vehicleSpotting->m_spotType == fb::SpotType_None) {
								vehicleSpotting->m_spotType = fb::SpotType_Passive;
							}
							else { continue; }
						}
					
				}}
			}
		}

		if (bSpottedExplosive)
		{
			fb::EntityWorld::EntityCollection explosive = g_pGameWorld->m_collections.at(ENTITY_CLIENT_EXPLOSIVE);
			if (explosive.firstSegment)
			{
				for (int i = 0; i < (int)explosive.firstSegment->m_Collection.size(); i++)
				{

					fb::ClientExplosionPackEntity* pEntity = reinterpret_cast<fb::ClientExplosionPackEntity*>(explosive.firstSegment->m_Collection.at(i));
					if (POINTERCHK(pEntity))
					{
						pEntity->m_isSpotted = 1; // 1 is spotted on map, 2 is spotted map and HUD (3D)
					}

				}
			}
		}
		return;
		//fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
		//if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;

		//fb::ClientPlayer* pLocalPlayer = pPlayerManager->m_localPlayer;
		//if (!POINTERCHK(pLocalPlayer)) return;

		//fb::EntityWorld::EntityCollection supplybox = g_pGameWorld->m_collections.at(ENTITY_CLIENT_SUPPLYBOX);
		//if (supplybox.firstSegment)
		//{
		//	for (int i = 0; i < (int)supplybox.firstSegment->m_Collection.size(); i++)
		//	{
		//		if (supplybox.firstSegment->m_Collection.size() > 0)
		//		{
		//			fb::ClientSupplySphereEntity* pEntity = reinterpret_cast<fb::ClientSupplySphereEntity*>(supplybox.firstSegment->m_Collection.at(i));
		//			if (POINTERCHK(pEntity))
		//			{
		//				pEntity->m_teamId = pLocalPlayer->m_teamId;
		//			}
		//		}
		//	}
		//}
	}
}
void _stdcall VehicleWeaponUpgrade()
{
	fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
	if (!POINTERCHK(g_pGameContext)) return;

	fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
	if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;

	fb::ClientPlayer* pLocalPlayer = pPlayerManager->m_localPlayer;
	if (!POINTERCHK(pLocalPlayer)) return;

	fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->getSoldierEnt();
	if (!POINTERCHK(pMySoldier)) return;

	if (!pMySoldier->isInVehicle()) return;

	char* name = GetVehicleName(pLocalPlayer);
	if (GetVehicleValues(name) == 0) return;

	int seat = 0;
	if (pLocalPlayer->m_attachedEntryId) seat = pLocalPlayer->m_attachedEntryId;

	bool bSeatHasWeapon = GetVehicleValues(name)->m_SeatHasWeapon[seat];
	bool bOpenSeat = GetVehicleValues(name)->m_OpenSeat[seat];

	if (bSeatHasWeapon)
	{
		fb::WeaponFiring* pWeaponFiring = GetVehicleWeapon(pLocalPlayer);
		if (POINTERCHK(pWeaponFiring))
		{
			if (bNoRecoil)
			{
				fb::WeaponSway* pWps = pWeaponFiring->m_weaponSway;
				if (POINTERCHK(pWps)) //
				{

					pWps->m_currentRecoilDeviation.m_pitch = 0.0f;
					pWps->m_currentRecoilDeviation.m_yaw = 0.0f;
					pWps->m_currentRecoilDeviation.m_roll = 0.0f;
					pWps->m_currentRecoilDeviation.m_transY = 0.0f;

					pWps->m_dispersionAngle = 0.0f;
					pWps->m_DeviationPitch = 0.0f;

					pWps->m_currentGameplayDeviationScaleFactor = 0.00001f;
					pWps->m_currentVisualDeviationScaleFactor = 0.00001f;

					pWps->m_randomAngle = 0.00001f;
					pWps->m_randomRadius = 0.00001f;

					pWps->m_currentDispersionDeviation.m_pitch = 0.0f;
					pWps->m_currentDispersionDeviation.m_yaw = 0.0f;
					pWps->m_currentDispersionDeviation.m_roll = 0.0f;
					pWps->m_currentDispersionDeviation.m_transY = 0.0f;

					pWps->m_currentLagDeviation.m_pitch = 0.0f;
					pWps->m_currentLagDeviation.m_yaw = 0.0f;
					pWps->m_currentLagDeviation.m_roll = 0.0f;
					pWps->m_currentLagDeviation.m_transY = 0.0f;

					pWps->m_dispersionAngle = 0.00001f;//small crosshair
				}

				pWeaponFiring->m_recoilAngleX = 0.0f;
				pWeaponFiring->m_recoilAngleY = 0.0f;
				pWeaponFiring->m_recoilAngleZ = 0.0f;

				pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_endDamage = pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_startDamage;
				//pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_damageFalloffStartDistance = 99999.0f;
			//	pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_damageFalloffEndDistance = 99999.1f;

			}
			if (bInstantKill)
			{
				pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_startDamage = 999.0f;
				pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_endDamage = 999.0f;
				pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_damageFalloffStartDistance = 99999.0f;
				pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_damageFalloffEndDistance = 99999.0f;
			}
			if (bInstantBullet)
			{
				pWeaponFiring->m_data->m_primaryFire->m_shot.m_initialSpeed.z = 1000.4f;
				//	pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_instantHit = true;
				//	pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_timeToLive = 10.0f;
				//	pWeaponFiring->m_data->m_primaryFire->m_shot.m_projectileData->m_gravity = 0.0f;
			}
		}
	}
	else if (bOpenSeat)
	{
		if (false)
		{
			fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
			if (!POINTERCHK(g_pGameContext)) return;

			fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
			if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;

			fb::ClientPlayer* pLocalPlayer = pPlayerManager->m_localPlayer;
			if (!POINTERCHK(pLocalPlayer)) return;

			fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->getSoldierEnt();
			if (!POINTERCHK(pMySoldier)) return;

			if (pMySoldier->isInVehicle()) return;

			if (!pMySoldier->IsAlive()) return;

			if (GetWeaponID(pMySoldier) != 0 && GetWeaponID(pMySoldier) != 1) return;

			eastl::vector<fb::ClientPlayer*> pVecCP = pPlayerManager->m_players;
			if (pVecCP.empty()) return;

			int size = pVecCP.size();
			for (int i = 0; i < size; i++)
			{
				fb::ClientPlayer* pClientPlayer = pVecCP.at(i);
				if (!POINTERCHK(pClientPlayer)) continue;

				if (pLocalPlayer->m_teamId == pClientPlayer->m_teamId) continue;

				fb::ClientSoldierEntity* pEnemySoldier = pClientPlayer->getSoldierEnt();
				if (!POINTERCHK(pEnemySoldier)) continue;

				if (!isalive(pEnemySoldier->Alive())) continue;

				int iWeaponID = GetWeaponID(pMySoldier);
				if (iWeaponID == -1) return;

				fb::ClientSoldierWeapon* MyCSW = pMySoldier->GetCSW();
				//valid checks on Weapons
				if (!POINTERCHK(MyCSW)
					|| !POINTERCHK(MyCSW->m_weapon)
					|| !POINTERCHK(MyCSW->m_predictedFiring)
					|| !POINTERCHK(MyCSW->m_predictedFiring->m_data->m_primaryFire)) return;

				fb::FiringFunctionData* pFFD = pMySoldier->getCurrentWeaponFiringData()->m_primaryFire;
				if (!POINTERCHK(pFFD)) return;

				//weaponmodifier only active if its your mainweapon
				fb::BulletEntityData* pBED;
				if (POINTERCHK(MyCSW)
					&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier)
					&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData))
				{
					pBED = reinterpret_cast<fb::BulletEntityData*>(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData);
					if (!POINTERCHK(pBED)) pBED = pFFD->m_shot.m_projectileData;
				}
				else
					pBED = pFFD->m_shot.m_projectileData;
				if (!POINTERCHK(pBED)) return;

				float flBulletspeed = pFFD->m_shot.m_initialSpeed.z;
				float flBulletdamage = pBED->m_endDamage;

				if (flBulletdamage > 2.00 && flBulletspeed > 40.0f)
				{
					fb::ClientWeapon* clWeapon = MyCSW->m_weapon;
					if (POINTERCHK(clWeapon))
					{
						__asm
						{
							push ecx
							mov ecx, clWeapon
							push pEnemySoldier
							call GIVEDAMAGE
							pop ecx
						}
					}
				}
			}
		}
	}
}
void _stdcall SoldierWeaponUpgrade()

{

	fb::ClientGameContext* g_pGameContext = fb::ClientGameContext::Singleton();
	if (!POINTERCHK(g_pGameContext)) return;

	fb::ClientPlayerManager* pPlayerManager = g_pGameContext->m_clientPlayerManager;
	if (!POINTERCHK(pPlayerManager) || pPlayerManager->m_players.empty()) return;

	fb::ClientPlayer* pLocalPlayer = pPlayerManager->m_localPlayer;//[0x2380b58]fb::ClientPlayer*
	if (!POINTERCHK(pLocalPlayer)) return;
	//hook isUnlocked()
	//HookUnlock( pLocalPlayer);


	fb::ClientSoldierEntity* pMySoldier = pLocalPlayer->getSoldierEnt();
	if (!POINTERCHK(pMySoldier)) return;

	if (pMySoldier->isInVehicle())
	{
		char* name = GetVehicleName(pLocalPlayer);
		if (GetVehicleValues(name) == 0) return;
	}

	int iWeaponID = GetWeaponID(pMySoldier);
	if (iWeaponID == -1) return;


	fb::Vec3 myspeed = pMySoldier->linearVelocity();




	fb::ClientSoldierWeapon* MyCSW = pMySoldier->GetCSW();
	//valid checks on Weapons
	if (!POINTERCHK(MyCSW)
		|| !POINTERCHK(MyCSW->m_weapon)
		|| !POINTERCHK(MyCSW->m_predictedFiring)
		|| !POINTERCHK(MyCSW->m_predictedFiring->m_data->m_primaryFire)) return;

	//disable breath sway this needs to be executed always
	fb::ClientSoldierEntity::BreathControlHandler* pBreath = pMySoldier->m_breathControlHandler;
	if (bNoBreath && POINTERCHK(pBreath))
	{
		pBreath->m_breathControlMultiplier = 0.0001;
		pBreath->m_breathControlTimer = 0.0001;
		pBreath->m_breathControlPenaltyMultiplier = 0.0001;
		pBreath->m_breathControlPenaltyTimer = 0.0001;
		//		pBreath->m_Enabled = false;
	}

	//disable sway multiplier on weapons with acogs ... this needs to be executed always
	fb::ClientSoldierWeaponsComponent::ClientWeaponSwayCallbackImpl* pCWSCI = pMySoldier->m_soldierWeaponsComponent->m_weaponSwayCallback;



	if (bNoSway && POINTERCHK(pCWSCI))
	{
		fb::SoldierAimingSimulationData* pSASD = MyCSW->m_authorativeAiming->m_data;
		//	MyCSW->m_authorativeAiming->m_sway.x = 0.f;

		if (POINTERCHK(pSASD->m_zoomLevels[0]))
		{
			pSASD->m_zoomLevels.At(0)->m_swayPitchMultiplier = 0.0000001f;
			pSASD->m_zoomLevels.At(0)->m_swayYawMultiplier = 0.0000001f;
			//	pSASD->m_zoomLevels.At(0)->m_timeYawMultiplier = 0.0000001f;

			if (pCWSCI->m_isSupported)
			{
				pSASD->m_zoomLevels.At(0)->m_supportedSwayPitchMultiplier = 0.0000001f;
				pSASD->m_zoomLevels.At(0)->m_supportedSwayYawMultiplier = 0.0000001f;
			}
		}
		if (MyCSW->m_authorativeAiming->m_zoomLevel > 0)
		{
			if (POINTERCHK(pSASD->m_zoomLevels[1]))
			{

				pSASD->m_zoomLevels.At(1)->m_swayPitchMultiplier = 0.0000001f;
				pSASD->m_zoomLevels.At(1)->m_swayYawMultiplier = 0.0000001f;

				if (pSASD->m_zoomLevels.At(1)->m_fieldOfView == 20.f) {
					pSASD->m_zoomLevels.At(1)->m_lookSpeedMultiplier = 0.08f;
					pSASD->m_zoomLevels.At(1)->m_fieldOfView = 5.4f;

				}
				else if (pSASD->m_zoomLevels.At(1)->m_fieldOfView > 8.0f&&pSASD->m_zoomLevels.At(1)->m_fieldOfView < 9.0f

					) {
					pSASD->m_zoomLevels.At(1)->m_lookSpeedMultiplier = 0.04f;
					pSASD->m_zoomLevels.At(1)->m_fieldOfView = 2.7f;
				}


				if (pCWSCI->m_isSupported)
				{
					pSASD->m_zoomLevels.At(1)->m_supportedSwayPitchMultiplier = 0.0000001f;
					pSASD->m_zoomLevels.At(1)->m_supportedSwayYawMultiplier = 0.0000001f;
				}
			}
		}

	}

	// disable recoil and spread ... this needs to be executed always

	fb::WeaponSway* pWps = pMySoldier->getWeaponSway();
	if (POINTERCHK(pWps)) //
	{

		HookRecoil(pWps);


		pWps->m_currentDispersionDeviation.m_pitch = 0.0f;
		pWps->m_currentDispersionDeviation.m_yaw = 0.0f;
		pWps->m_currentDispersionDeviation.m_roll = 0.0f;
		pWps->m_currentDispersionDeviation.m_transY = 0.0f;

		pWps->m_currentLagDeviation.m_pitch = 0.0f;
		pWps->m_currentLagDeviation.m_yaw = 0.0f;
		pWps->m_currentLagDeviation.m_roll = 0.0f;
		pWps->m_currentLagDeviation.m_transY = 0.0f;









	}
	fb::WeaponFiring* pWeaponFiring = pMySoldier->getCurrentWeaponFiring();
	if (!POINTERCHK(pWeaponFiring)) {
		return;
	}
	else if (POINTERCHK(pWeaponFiring))
	{
		pWeaponFiring->m_overheatDropMultiplier = 500;
		pWeaponFiring->m_primaryFire.isOverheated = false;
		pWeaponFiring->m_autoReplenishTime = 0.00001f;
		pWeaponFiring->m_primaryFire.heat = 0.0f;

	}


	fb::FiringFunctionData* pFFD = pMySoldier->getCurrentWeaponFiringData()->m_primaryFire;
	if (!POINTERCHK(pFFD)) return; else {
	
	}	
	
		
	
	fb::BulletEntityData* pBED;
	if (POINTERCHK(MyCSW)
		&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier)
		&& POINTERCHK(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData))
	{
		pBED = reinterpret_cast<fb::BulletEntityData*>(MyCSW->m_weaponModifier.m_weaponProjectileModifier->m_projectileData);

		if (!POINTERCHK(pBED)) pBED = pFFD->m_shot.m_projectileData;
	}
	else
		pBED = pFFD->m_shot.m_projectileData;
	if (!POINTERCHK(pBED)) return;




	if (iWeaponID != -1 && pBED->m_endDamage > 2.00 && pFFD->m_shot.m_initialSpeed.z > 40.1f) {




		cl_SoldierWeapon = iWeaponID;


	/*	if (pBED->m_startDamage > 79.5f&&pBED->m_startDamage < 80.5f) {
			pBED->m_startDamage = 110.10f;
			pBED->m_endDamage = 74.f;
			pBED->m_damageFalloffStartDistance = 42.f;
			pBED->m_damageFalloffEndDistance = 42.001f;
		}
		else if (pBED->m_startDamage == 95.f) {
			pBED->m_startDamage = 110.1f;
			pBED->m_endDamage = 87.f;
			pBED->m_damageFalloffStartDistance = 62.f;
			pBED->m_damageFalloffEndDistance = 62.001f;
		}
		else */
			
			if (pBED->m_startDamage > 42.f&&pBED->m_startDamage < 51.0f) {
			pBED->m_startDamage = 60.f;
			pBED->m_endDamage = 46.f;
			pBED->m_damageFalloffStartDistance = 35.f;
			pBED->m_damageFalloffEndDistance = 35.001f;
		}
		else if (pBED->m_startDamage <= 17.0f)
		{
			pBED->m_startDamage = 26.7f;
		}
		else if (pBED->m_startDamage == 20.f)
		{
			pBED->m_startDamage = 30.5f;
		}
		else if (pBED->m_startDamage == 25.f)
		{
			pBED->m_startDamage = 36.5f;
		}

		else if (pBED->m_startDamage == 34.f)
		{
			pBED->m_startDamage = 41.5f;
		}

		if (pBED->m_endDamage != 46.f&&pBED->m_startDamage < 79.6f&&pBED->m_endDamage < 74.f&&
			pBED->m_startDamage > pBED->m_endDamage)
		{
			pBED->m_endDamage = pBED->m_startDamage;
		}



		pBED->m_timeToLive = 50.f;


	}



	else {
		cl_SoldierWeapon = 0xffff;
	}
}
int WINAPI hkPreFrame(float DeltaTime)
{
	_asm pushad
	int returnval = oPreFrameUpdate(DeltaTime);

	if (GetAsyncKeyState(VK_RMENU) & 0x8000) {
		bAimHead = !bAimHead;

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
		g_pBorderInputNode->m_inputCache->flInputBuffer[i] += g_pInputBuffers[i];
		g_pInputBuffers[i] = 0.0f;
	}

	_asm popad

	return returnval;
}
signed int __stdcall hkPresent(int a1, int a2, int a3) {
	__asm pushad;

	//ButtonMenu();


	SoldierWeaponUpgrade();
	VehicleWeaponUpgrade();

	PlayerIteration();
	EntityWorld();


	__asm popad;

	return oPresent(a1, a2, a3);
}
DWORD WINAPI CreateConsole(LPVOID lpArgs)
{
	int hConHandle = 0;
	HANDLE lStdHandle = 0;
	FILE *fp = 0;
	AllocConsole();
	// redirect unbuffered STDOUT to the console
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);

	// redirect unbuffered STDIN to the console
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	freopen_s(&fp, "CONOUT$", "r", stdin);

	// redirect unbuffered STDERR to the console
	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	freopen_s(&fp, "CONOUT$", "w", stderr);
	return 1;
}


BOOL APIENTRY DllMain(HMODULE hModule, unsigned long ulReason, void* param)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

#ifdef _DEBUG
		CreateThread(NULL, NULL, &CreateConsole, NULL, NULL, NULL);
#endif // DEBUG
		printf_s(time);
		PresentHook = new CVMTHookManager((intptr_t**)fb::DxRenderer::Singleton()->pSwapChain);
		oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
		PresentHook->dwHookMethod((intptr_t)hkPresent, 8);
#ifndef _DEBUG
		PreFrameHook = new CVMTHookManager((intptr_t**)g_pBorderInputNode);
		oPreFrameUpdate = (tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(27);
		PreFrameHook->dwHookMethod((intptr_t)hkPreFrame, 27);
#endif // DEBUG
		//	  fopen_s(&m_log,"e:\log.txt", "a+" );

			//ping proof
		intptr_t IcmpCreateFile = (intptr_t)GetProcAddress(GetModuleHandleW(L"iphlpapi.dll"), "IcmpCreateFile") + 0x289;

		DWORD dwOld;
		//ping spoof
		if (POINTERCHK(IcmpCreateFile)) {
			VirtualProtect((LPVOID)IcmpCreateFile, 3 * sizeof(BYTE), PAGE_EXECUTE_READWRITE, &dwOld);

			memset((LPVOID)IcmpCreateFile, 0x31, 1);
			memset((LPVOID)(IcmpCreateFile + 1), 0xc0, 1);//xor eax,eax
			memset((LPVOID)(IcmpCreateFile + 2), 0x40, 1);//inc eax

			VirtualProtect((LPVOID)IcmpCreateFile, 3 * sizeof(BYTE), dwOld, NULL);
		}


	}
	else if (ulReason == DLL_PROCESS_DETACH)
	{

		if (PresentHook != nullptr)PresentHook->UnHook();
		//CloseHandle(CreateThread(NULL, 0, &HookThread, NULL, 0, NULL)); //Disable hook
	}
	return 1;
}