
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
int nWeaponExchange = -1;

bool bMagicBullets = false;

bool bAimbot = false;
bool bAimHead = false;
bool bVisibilityChecks = false;

bool bBoxESP = false;
bool bBones = false;
bool bHealthbar = false;
bool bNames = false;
bool bDistance = false;
bool bSnaplines = false;

bool bMinimapHack = true;
bool bForceSquadSpawn = true;
bool bSpottedExplosive =true;

int nMenuindex = 0;
int nMenuelements = 21;

int cl_SoldierWeapon = 0xffff;
float ori_startdamage = 0.0f;
float ori_enddamage = 0.0f;
#pragma endregion Global Vars
/*push ebp
mov ebp, esp
and esp, FFFFFFF0
sub esp, 48
cmp byte ptr ss : [ebp + C], 0
push esi
push edi
push ecx
je bf3.701A72
fld dword ptr ds : [ecx + 140]
lea eax, dword ptr ss : [esp + 14]
fstp dword ptr ss : [esp]
push eax
jmp bf3.701A80
fld dword ptr ds : [ecx + 13C]
lea edx, dword ptr ss : [esp + 14]
fstp dword ptr ss : [esp]
push edx
add ecx, AC
call bf3.6FFE90
mov edi, dword ptr ss : [ebp + 8]
mov ecx, 10
mov esi, eax
rep movsd dword ptr es : [edi], dword ptr ds : [esi]
pop edi
pop esi
mov esp, ebp
pop ebp
ret 8
void __declspec(naked) hkGetRecoil(void)
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
push eax
xor eax, eax

pop eax
jmp dword ptr[g_pOriginalGetRecoil]
}
}*/

/*push ebp
mov ebp, esp
and esp, FFFFFFF0
sub esp, 48
cmp byte ptr ss : [ebp + C], 0
push esi
push edi
push ecx
je bf3.701A22
fld dword ptr ds : [ecx + 140]
lea eax, dword ptr ss : [esp + 14]
fstp dword ptr ss : [esp]
push eax
jmp bf3.701A30
fld dword ptr ds : [ecx + 13C]
lea edx, dword ptr ss : [esp + 14]
fstp dword ptr ss : [esp]
push edx
add ecx, 12C
call bf3.6FFE90
mov edi, dword ptr ss : [ebp + 8]
mov ecx, 10
mov esi, eax
rep movsd dword ptr es : [edi], dword ptr ds : [esi]
pop edi
pop esi
mov esp, ebp
pop ebp
ret 8
void __declspec(naked) hkGetDeviation(void)
{
__asm
{
push esi
push edi
xor edi, edi
mov esi, ecx
mov[esi + 0x140], edi
mov[esi + 0x13C], edi
pop edi
pop esi
push eax
xor eax, eax

pop eax
jmp dword ptr[g_pOriginalGetDeviation]
}
}*/
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
//Source: http://dumpz.org/398889/


DWORD dwDispersionRetAddr;
DWORD dwRecoilRetAddress;
fb::WeaponSway* recoilThisPtr;

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

		//	pop dwRecoilRetAddress
		//	mov recoilThisPtr, ecx
		//	push eax
		//	mov eax, [esp + 0x4]
		//	mov arg1, eax
		//	pop eax
		//	pushad
		//	pushfd
		//}
		//D3DXMatrixIdentity(&mtx);
		//memcpy(arg1, mtx, 0x40);
		//hookedRecoil(recoilThisPtr, arg1, false);
		//__asm
		//{
		//	popfd
		//	popad
		//	//call originalGetRecoil
		//	add esp, 0x8
		//	push dwRecoilRetAddress
		//	ret
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
	if ( bNoSpread)
	{
		if ((void*)hkGetDispersion != HookVtblFunction(pWps, hkGetDispersion, 24, 64))
		{
			HookVtblFunction(pWps, hkGetDispersion, 24, 64);
		}
	
	}
	if (bNoRecoil) {
		if ((void*)hkGetRecoil != HookVtblFunction(pWps, hkGetRecoil, 25, 64))
		{
			HookVtblFunction(pWps, hkGetRecoil, 25, 64);
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
				if (POINTERCHK(pCSTC))
					pCSTC->m_spotType = fb::SpotType_Active;
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
					if (vehicle.firstSegment->m_Collection.size() > 0)
					{
						fb::ClientVehicleEntity* pEntity = reinterpret_cast<fb::ClientVehicleEntity*>(vehicle.firstSegment->m_Collection.at(i));
						if (POINTERCHK(pEntity))
						{
							fb::ClientSpottingTargetComponent* vehicleSpotting = pEntity->getComponent<fb::ClientSpottingTargetComponent>("ClientSpottingTargetComponent");
							if (POINTERCHK(vehicleSpotting))
								vehicleSpotting->m_spotType = fb::SpotType_Active;
						}
					}
				}
			}
		}

		if (bSpottedExplosive)
		{
			fb::EntityWorld::EntityCollection explosive = g_pGameWorld->m_collections.at(ENTITY_CLIENT_EXPLOSIVE);
			if (explosive.firstSegment)
			{
				for (int i = 0; i < (int)explosive.firstSegment->m_Collection.size(); i++)
				{
					if (explosive.firstSegment->m_Collection.size() > 0)
					{
						fb::ClientExplosionPackEntity* pEntity = reinterpret_cast<fb::ClientExplosionPackEntity*>(explosive.firstSegment->m_Collection.at(i));
						if (POINTERCHK(pEntity))
						{
							pEntity->m_isSpotted = 1; // 1 is spotted on map, 2 is spotted map and HUD (3D)
						}
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
				fb::WeaponSway* thisptr = pWeaponFiring->m_weaponSway;
				if (POINTERCHK(thisptr)) //
				{

					thisptr->m_currentDispersionDeviation.m_pitch = 0.0f;
					thisptr->m_currentDispersionDeviation.m_yaw = 0.0f;
					thisptr->m_currentDispersionDeviation.m_roll = 0.0f;
					thisptr->m_currentDispersionDeviation.m_transY = 0.0f;

					thisptr->m_currentLagDeviation.m_pitch = 0.0f;
					thisptr->m_currentLagDeviation.m_yaw = 0.0f;
					thisptr->m_currentLagDeviation.m_roll = 0.0f;
					thisptr->m_currentLagDeviation.m_transY = 0.0f;
				

			thisptr->m_dispersionAngle = 0.0f; //small crosshair



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
		if (bMagicBullets)
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
		pBreath->m_breathControlMultiplier = 0;
		pBreath->m_breathControlTimer = 0;
		pBreath->m_breathControlPenaltyMultiplier = 0;
		pBreath->m_breathControlPenaltyTimer = 0;
	}

	//disable sway multiplier on weapons with acogs ... this needs to be executed always
	fb::ClientSoldierWeaponsComponent::ClientWeaponSwayCallbackImpl* pCWSCI = pMySoldier->m_soldierWeaponsComponent->m_weaponSwayCallback;
	if (bNoSway && POINTERCHK(pCWSCI))
	{
		fb::SoldierAimingSimulationData* pSASD = MyCSW->m_authorativeAiming->m_data;
	//	MyCSW->m_authorativeAiming->m_sway.x = 0.f;
	


		if (POINTERCHK(pSASD->m_zoomLevels[0]))
		{
			pSASD->m_zoomLevels.At(0)->m_swayPitchMultiplier = 0.001f;
			pSASD->m_zoomLevels.At(0)->m_swayYawMultiplier = 0.001f;
		

			if (pCWSCI->m_isSupported)
			{
				pSASD->m_zoomLevels.At(0)->m_supportedSwayPitchMultiplier = 0.001f;
				pSASD->m_zoomLevels.At(0)->m_supportedSwayYawMultiplier = 0.001f;
			}
		}
		if (MyCSW->m_authorativeAiming->m_zoomLevel > 0)
		{
			if (POINTERCHK(pSASD->m_zoomLevels[1]))
			{
				printf_s("x:%x,y:%x\n", &MyCSW->m_authorativeAiming->m_sway.x, &MyCSW->m_authorativeAiming->m_sway.y);
				printf_s("%x\n", &pSASD->m_zoomLevels.At(1)->m_swayYawMultiplier);
				printf_s("pCWSCI->m_isSupported addr:%x\n", &pCWSCI->m_isSupported);
			//	pSASD->m_zoomLevels.At(1)->m_swayPitchMultiplier = 0.001f;
			//	pSASD->m_zoomLevels.At(1)->m_swayYawMultiplier = 0.001f;
				//	printf_s("%x\n", &pSASD->m_zoomLevels.At(1)->m_swayPitchMultiplier);
				//	printf_s("fov:%f", pSASD->m_zoomLevels.At(1)->m_fieldOfView);
				if (pSASD->m_zoomLevels.At(1)->m_fieldOfView ==20.f) {
					pSASD->m_zoomLevels.At(1)->m_lookSpeedMultiplier = 0.09f;
					pSASD->m_zoomLevels.At(1)->m_fieldOfView = 5.f;

				}
				else if (pSASD->m_zoomLevels.At(1)->m_fieldOfView > 8.0f&&pSASD->m_zoomLevels.At(1)->m_fieldOfView < 9.0f
					
					) {
					pSASD->m_zoomLevels.At(1)->m_lookSpeedMultiplier = 0.05f;
					pSASD->m_zoomLevels.At(1)->m_fieldOfView = 2.8f;
				}

			
				if (pCWSCI->m_isSupported)
				{
					pSASD->m_zoomLevels.At(1)->m_supportedSwayPitchMultiplier = 0.0f;
					pSASD->m_zoomLevels.At(1)->m_supportedSwayYawMultiplier = 0.0f;
				}
			}
		}

		/*	fb::WeaponSway* pCurWps = MyCSW->m_correctedFiring->m_weaponSway;
		if (POINTERCHK(pCurWps)){
		pCurWps->m_currentRecoilDeviation.m_pitch = 0;
		pCurWps->m_currentRecoilDeviation.m_yaw = 0;
		pCurWps->m_currentRecoilDeviation.m_roll = 0;
		pCurWps->m_currentLagDeviation.m_pitch = 0;
		pCurWps->m_currentLagDeviation.m_yaw = 0;
		pCurWps->m_currentLagDeviation.m_roll = 0;
		pCurWps->m_currentDispersionDeviation.m_pitch = 0;
		pCurWps->m_currentDispersionDeviation.m_yaw = 0;
		pCurWps->m_currentDispersionDeviation.m_roll = 0;
		pCurWps->m_randomRadius = 0.0f;
		pCurWps->m_randomAngle = 0.f;
		pCurWps->m_fireShot = 0;
		}*/
	}

	// disable recoil and spread ... this needs to be executed always

	fb::WeaponSway* pWps = pMySoldier->getWeaponSway();
	if (POINTERCHK(pWps)) //
	{

		HookRecoil(pWps);





	}
	fb::WeaponFiring* pWeaponFiring = pMySoldier->getCurrentWeaponFiring();
	if (!POINTERCHK(pWeaponFiring)) { return;
	} else if(POINTERCHK(pWeaponFiring))
	{
		pWeaponFiring->m_overheatDropMultiplier = 500;
		pWeaponFiring->m_primaryFire.isOverheated = false;
		pWeaponFiring->m_autoReplenishTime = 0.00001f;
		pWeaponFiring->m_primaryFire.heat = 0.0f;
	
	}


	fb::FiringFunctionData* pFFD = pMySoldier->getCurrentWeaponFiringData()->m_primaryFire;
	if (!POINTERCHK(pFFD)) return; else {

	}
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


	

		if (iWeaponID != -1 && bInstantBullet&&pBED->m_endDamage > 2.00 && pFFD->m_shot.m_initialSpeed.z > 40.1f) {

			//	printf_s("addr: %x",(UINT)& pBED->m_gravity);


			cl_SoldierWeapon = iWeaponID;
			//	pBED->m_gravity = 0.f;

			if (pBED->m_startDamage > 79.5f&&pBED->m_startDamage < 80.5f) {
				pBED->m_startDamage = 110.10f;
				pBED->m_endDamage = 74.f;
				pBED->m_damageFalloffStartDistance = 52.f;
				pBED->m_damageFalloffEndDistance = 52.001f;
			}
			else if (pBED->m_startDamage == 95.f) {
				pBED->m_startDamage = 110.1f;
				pBED->m_endDamage = 87.f;
				pBED->m_damageFalloffStartDistance = 52.f;
				pBED->m_damageFalloffEndDistance = 52.001f;
			}
			else if (pBED->m_startDamage == 43.f||pBED->m_startDamage == 50.0f) {
				pBED->m_startDamage = 60.f;
				pBED->m_endDamage = 46.f;
			}
			else if (pBED->m_startDamage == 16.7f)
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

			if (pBED->m_gravity== (-9.8100f))
			{
				//pBED->m_gravity =(- 5.f);
			}

				pBED->m_timeToLive = 10.f;

			//		pBED->m_firstFrameTravelDistance = 50.f;
					pBED->m_initialSpeed=750.f;
		//			pFFD->m_shot.m_initialSpeed.z = 710.f;
		//			pBED->m_damageFalloffEndDistance = 9000.1f;


			if (pBED->m_endDamage != 46.f&&pBED->m_startDamage < 79.6f&&pBED->m_endDamage < 74.f&&
				pBED->m_startDamage > pBED->m_endDamage)
			{
				pBED->m_endDamage = pBED->m_startDamage;
			}



			//	pBED->m_damageFalloffStartDistance = 9999.0f;
			//	pBED->m_damageFalloffEndDistance = 9999.1f;
				//	if (pFFD->m_shot.m_numberOfBulletsPerShell == 1)pFFD->m_shot.m_numberOfBulletsPerShell = 5;


		//	pFFD->m_shot.m_initialSpeed.z = 900.0f;
			////	pFFD->m_shot.m_initialSpeed.z = 99999.0f;
			//////	if(pFFD->m_shot.m_numberOfBulletsPerShell ==1)pFFD->m_shot.m_numberOfBulletsPerShell = 5;
			////	pBED->m_instantHit = true;
			////	pBED->m_timeToLive = 10.0f;
			////	pBED->m_gravity = 0.0f;



		}



		else 		{
			cl_SoldierWeapon = 0xffff;
		}
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
void CreateConsole()
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
}
DWORD WINAPI BF3HookThread(LPVOID)
{

	CreateConsole();


	printf("[Battlefield 3]\n");
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, unsigned long ulReason, void* param)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		//CreateThread(NULL, NULL, PBSSThread, NULL, NULL, NULL);

#ifdef _DEBUG
		CreateThread(NULL, NULL, BF3HookThread, NULL, NULL, NULL);
#endif // DEBUG

		//CloseHandle(CreateThread(NULL, 0, &HookThread, (void*)1, 0, NULL)); //Enable hook
		PresentHook = new CVMTHookManager((DWORD**)fb::DxRenderer::Singleton()->pSwapChain);
		oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
		PresentHook->dwHookMethod((DWORD)hkPresent, 8);
	}
	else if (ulReason == DLL_PROCESS_DETACH)
	{

		if (PresentHook != nullptr)PresentHook->UnHook();
		//CloseHandle(CreateThread(NULL, 0, &HookThread, NULL, 0, NULL)); //Disable hook
	}
	return 1;
}