#include "stdafx.h"
#include "FB_SDK/Frostbite.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <limits>
#include "Aimbot.h"
#include "hkheader.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma data_seg (".vc4hk_shared")

Aimbot hkAimbot;
HackKev hke;
HANDLE hMutex = CreateMutex(NULL, false, (LPCWSTR)"vc4Mutex");
#pragma data_seg ()

//#define LOGGG
char *buffer = new char[0xff];
std::ofstream log_file(
	"d:\\log\\hk.log", std::ios_base::out | std::ios_base::trunc);

void logxxx(const std::string &text)
{

	log_file << text << std::endl;
}

namespace Vtb {
	class CVMTHookManager
	{
	public:
		CVMTHookManager(void)
		{
			memset(this, 0, sizeof(CVMTHookManager));
		}

		CVMTHookManager(intptr_t** ppdwClassBase)
		{
			bInitialize(ppdwClassBase);
		}

		~CVMTHookManager(void)
		{
			UnHook();
		}
		bool bInitialize(intptr_t** ppdwClassBase)
		{
			m_ppdwClassBase = ppdwClassBase;
			m_pdwOldVMT = *ppdwClassBase;
			m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
			m_pdwNewVMT = new intptr_t[m_dwVMTSize];
			memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(intptr_t) * m_dwVMTSize);
			*ppdwClassBase = m_pdwNewVMT;
			return true;
		}



		bool bInitialize(intptr_t*** pppdwClassBase) // fix for pp
		{
			return bInitialize(*pppdwClassBase);
		}

		void UnHook(void)
		{
			dwHookMethod(oFunction, unhookindex);
		}

		void ReHook(void)
		{
			if (m_ppdwClassBase)
			{
				*m_ppdwClassBase = m_pdwNewVMT;
			}
		}

		int iGetFuncCount(void)
		{
			return (int)m_dwVMTSize;
		}

		intptr_t dwGetMethodAddress(int Index)
		{
			if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
			{
				unhookindex = Index;
				oFunction = m_pdwOldVMT[Index];
				return m_pdwOldVMT[Index];
			}
			return NULL;
		}

		intptr_t* pdwGetOldVMT(void)
		{
			return m_pdwOldVMT;
		}

		intptr_t dwHookMethod(intptr_t dwNewFunc, intptr_t iIndex)
		{
			if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
			{
				m_pdwNewVMT[iIndex] = dwNewFunc;
				return m_pdwOldVMT[iIndex];
			}

			return NULL;
		}

		static	void* ReplaceVtblFunction(void* vtb, void* dwHook, const int Index)
		{
			void* pOrig;
			intptr_t *vtable = (intptr_t *)vtb;
			pOrig = (void*)(vtable[Index]);
			if (pOrig != dwHook) {

				DWORD dwOld;

				VirtualProtect(&(vtable[Index]), sizeof(intptr_t), PAGE_EXECUTE_READWRITE, &dwOld);

				vtable[Index] = (intptr_t)dwHook; //Replace Vtable Function

				VirtualProtect(&(vtable[Index]), sizeof(intptr_t), dwOld, NULL);

			}

			return pOrig;
		}

	private:
		intptr_t * *	m_ppdwClassBase;
		intptr_t*	m_pdwNewVMT;
		intptr_t*	m_pdwOldVMT;
		intptr_t	m_dwVMTSize, oFunction;
		int unhookindex;
		intptr_t dwGetVMTCount(intptr_t* pdwVMT)
		{
			intptr_t dwIndex = 0;

			for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
			{
				if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
				{
					break;
				}
			}
			return dwIndex;
		}
	};

	intptr_t dwGetVMTCount2(intptr_t* pdwVMT)
	{
		intptr_t dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
			{
				break;
			}
		}
		return dwIndex;
	}

}



#pragma region

Vtb::CVMTHookManager* PresentHook = 0;
typedef HRESULT(__stdcall* tPresent)(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags);
tPresent oPresent;

Vtb::CVMTHookManager* PreFrameHook = 0;
typedef  int(__stdcall* tPreFrameUpdate)(void*, float);
tPreFrameUpdate oPreFrameUpdate = 0;

typedef  intptr_t(__stdcall* tWeaponFiring)(void*, intptr_t, intptr_t);
tWeaponFiring oWeaponFiring_Function_1 = 0;

fb::BorderInputNode* g_pBorderInputNode = fb::BorderInputNode::GetInstance();


Vtb::CVMTHookManager* updateHook = 0;
typedef DWORD_PTR(__stdcall* tUpdate)(DWORD_PTR a1, DWORD_PTR a2, DWORD_PTR a3);
tUpdate oUpdate;

intptr_t* pAntVtable = *(intptr_t**)OFFSET_ANTVTABLE;
intptr_t* pInputNodeVtable = (intptr_t*)fb::BorderInputNode::GetInstance()->m_Vtable;
#pragma endregion Hook

void _stdcall DoAimPrediction() {

	float fl_BulletGrav = 0.f;
	float fl_ZeroAngle = 0.f;


	fb::Vec4 v_bulletspeed;
	fb::ClassInfo* pType;
	v_bulletspeed.z = 100.f;
	v_bulletspeed.y = 0.f;
	int bulletId = 0;
	bool b_InVehWithWeapon = false;
	bool b_HasTurret = false;

	fb::ChildRotationBodyData * p_turrentData = nullptr;
	fb::Vec4 v_Origin;
	fb::Vec4 * curVecOfClosestSoldier;
	fb::ClientSoldierEntity* p_ClosestSoldier;
	fb::ClientPlayer* p_ClosestPlayer;
	fb::ClientSoldierEntity* pEnemySoldier = nullptr;
	float fl_YawMultiplier = 10000000000000000000.f;
	float fl_PitchMultiplier = 10000000000000000000.f;


	fb::GameRenderer * pGameRenderer = fb::GameRenderer::GetInstance();
	if (!IsValidPtr(pGameRenderer))return;

#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pGameRenderer:%p", pGameRenderer); logxxx(buffer);
#endif // LOGGG

	fb::RenderView* pRenderView = pGameRenderer->m_pRenderView;

	if (!IsValidPtr(pRenderView))return;

#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pRenderView:%p", pRenderView); logxxx(buffer);
#endif // LOGGG

	float fl_FovX = pRenderView->m_FovX;
	float fl_FovY = pRenderView->m_FovY;

	fb::PlayerManager* pPlayerMngr = hke.mp_PlayerMngr;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pPlayerMngr:%p", pPlayerMngr); logxxx(buffer);;
#endif // LOGGG


	fb::ClientPlayer* pLocalPlayer = hke.mp_LocalPlayer;
	if (pLocalPlayer == nullptr)return;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pLocalPlayer:%p", pLocalPlayer); logxxx(buffer);;
#endif // LOGGG


	fb::ClientSoldierEntity* pMySoldier = hke.mp_LocalSoldier;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pMySoldier:%p", pMySoldier); logxxx(buffer);;
#endif // LOGGG
	//if (!IsAlive(pMySoldier))return;

	void* pCurVehicleCam = hke.mp_CurVehicleCamera;

	//sprintf_s(buffer, 0xff, "	???b_InVehWithWeapon "); logxxx(buffer);

	if (pLocalPlayer->InVehicle() && pCurVehicleCam) {
		b_InVehWithWeapon = true;
#ifdef LOGGG
		sprintf_s(buffer, 0xff, "b_InVehWithWeapon = true"); logxxx(buffer);
#endif // LOGGG

	}

	fb::ClientWeapon* MyCSW = nullptr;
	fb::WeaponFiring* pWepFiring = *(fb::WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;

	if (!b_InVehWithWeapon) {
		fb::ClientSoldierWeaponsComponent* pWepComp = fb::MainVarPtr::Singleton()->pWeaponComp;

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

#ifdef LOGGG
	sprintf_s(buffer, 0xff, "v_bulletspeed.z:%f", v_bulletspeed.z); logxxx(buffer);
#endif // LOGGG

	if (b_InVehWithWeapon) {
		fb::ClientVehicleEntity* pVehivle = fb::MainVarPtr::Singleton()->pVehicleEntry;



		std::vector<void*>* v_pChildRota = new std::vector<void*>();

#ifdef LOGGG
		sprintf_s(buffer, 0xff, "pVehivle:%p", pVehivle); logxxx(buffer);
#endif // LOGG
		size_t i_ChildRotationBodyData = hke.GetClientComponentByID(pVehivle->m_Complist, v_pChildRota, 366, true, false);
#ifdef LOGGG
		sprintf_s(buffer, 0xff, " hke.GetClientComponentByName"); logxxx(buffer);
#endif // LOGGG

		if (i_ChildRotationBodyData > 0) {
			b_HasTurret = true;


			for (size_t index = 0; index < 2; index++)
			{
				fb::ChildRotationBodyData*	p_ChildRotationBodyData =
					((fb::ClientChildComponent*)v_pChildRota->at(index))->m_ClientChildBarrelComponent
					.m_ChildRotationBodyData;


				if (IsValidPtr(p_ChildRotationBodyData)) {
					if (p_ChildRotationBodyData->m_RotationAxis == 1) {

						fl_YawMultiplier = p_ChildRotationBodyData->m_AngularMomentumMultiplier;

					}
					else if (p_ChildRotationBodyData->m_RotationAxis == 0) {

						fl_PitchMultiplier = p_ChildRotationBodyData->m_AngularMomentumMultiplier;

					}


				}
			}
#ifdef LOGGG
			sprintf_s(buffer, 0xff, "fl_PitchMultiplier:%f,fl_YawMultiplier:%f", fl_PitchMultiplier, fl_YawMultiplier); logxxx(buffer);
#endif 
		}

		std::vector<void*>* v_pClientWeaponComponent = new std::vector<void*>;
		size_t i_ClientWeaponComponent = hke.GetClientComponentByID(pVehivle->m_Complist, v_pClientWeaponComponent, 370, false, true);

		if (i_ClientWeaponComponent > 0) {
#ifdef LOGGG
			sprintf_s(buffer, 0xff, " hke.GetClientComponentByName---ClientWeaponComponent"); logxxx(buffer);
#endif // LOGGG
			size_t size = v_pClientWeaponComponent->size();

			for (size_t index = 0; index < size; index++)
			{
				fb::ClientWeaponComponent*	p_ClientWeaponComponent =
					((fb::ClientWeaponComponent*)v_pClientWeaponComponent->at(index))
					;


				if (IsValidPtr(p_ClientWeaponComponent)) {
					if (pWepFiring == p_ClientWeaponComponent->m_pWeaponInfo->GetWeaponFiring()) {
						MyCSW = p_ClientWeaponComponent->m_pWeapon;
						break;
					}
				}
			}
		}
	}

	if (IsValidPtr(MyCSW->m_pWeaponModifier))
	{

		if (IsValidPtr(MyCSW->m_pWeaponModifier->m_ShotModifier)) {

			v_bulletspeed.z = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.z;
			v_bulletspeed.y = MyCSW->m_pWeaponModifier->m_ShotModifier->m_InitialSpeed.y;


		}
	}
	float fl_CSWZeroAngle = *(float*)((intptr_t)MyCSW + 0xb70);

	if (fl_CSWZeroAngle > 0.1f&&fl_CSWZeroAngle < 15.f&&pFFD->m_FireLogic.m_FireLogicType == fb::FireLogicType::fltSingleFireWithBoltAction)
	{
		fl_ZeroAngle = fl_CSWZeroAngle;
	}

	void* pBED = pFFD->m_ShotConfigData.m_ProjectileData;

	//check bullet or missile

	pType = (fb::ClassInfo*)(((fb::ITypedObject*)(pBED))->GetType());

	bulletId = pType->m_ClassId;

	switch (bulletId)
	{
	case 2487: {//missile
		v_bulletspeed.z = 50000.f;
		v_bulletspeed.y = 0.f;
		fl_BulletGrav = 0.f;// *(float*)((intptr_t)pBED + 0x170);
		break;
	};
			   //	case 2480: 
	default: {
		fl_BulletGrav = *(float*)((intptr_t)pBED + 0x130); break; };
	}

	if (v_bulletspeed.z <= 5.f)return;

#ifdef LOGGG
	sprintf_s(buffer, 0xff, "GetBulletInfo ok  %d ", bulletId); logxxx(buffer);
#endif // LOGGG
	if (b_InVehWithWeapon && !b_HasTurret)
		return;

	//get origin


	v_Origin = hkAimbot.GetOriginAndUpdateCurrentAngle(pLocalPlayer, MyCSW, pFFD, b_InVehWithWeapon);
#ifdef LOGGG	
	sprintf_s(buffer, 0xff, "GetOriginAndUpdateCurrentAngle ok"); logxxx(buffer);
#endif // LOGGG

	//find closest player
	eastl::vector<fb::ClientPlayer*>* pVecCP = pPlayerMngr->getPlayers();

	curVecOfClosestSoldier = hkAimbot.GetClosestPlayer(pVecCP, pLocalPlayer, bulletId == 2487, b_InVehWithWeapon);
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

		fb::Vec4 * v = p_ClosestSoldier->GetVelocity();
		if (IsValidPtr(v)) {
			Vec_Enemyspeed = *v;
			//	sprintf_s(buffer, 0xff, "sol_Vec_Enemyspeed.x:%f\tVec_Enemyspeed.y:%f\tVec_Enemyspeed.z:%f",
			//		Vec_Enemyspeed.x, Vec_Enemyspeed.y, Vec_Enemyspeed.z); logxxx(buffer);
		}
	}

	if (Vec_Enemyspeed.len() < 20.f)
	{
		Vec_Enemyspeed.x = Vec_Enemyspeed.x*1.15f;
		Vec_Enemyspeed.y = Vec_Enemyspeed.y*1.15f;
		Vec_Enemyspeed.z = Vec_Enemyspeed.z*1.15f;
		Vec_Enemyspeed.w = 0.f;
	}


	//sprintf_s(buffer, 0xff, "GetVec ok\tG:%f", flBulletGrav); logxxx(buffer);

	fb::Vec4  vDir;

	DWORD n_ReturnCode = hkAimbot.AimCorrection2(v_Origin, *curVecOfClosestSoldier, Vec_Enemyspeed, v_bulletspeed, fl_BulletGrav, &vDir);


	if (n_ReturnCode != 0x0) {
		return;
	}

	//sprintf_s(buffer, 0xff, "AimCorrection2_OK"); logxxx(buffer);

	vDir.y = vDir.y - fl_ZeroAngle * DegToRad; //approx
	float vInitialDirection = -atan2(pFFD->m_ShotConfigData.m_InitialPosition.x, pFFD->m_ShotConfigData.m_InitialPosition.z);
	if (vInitialDirection < 0) { vInitialDirection += Twice_PI; }
	vDir.y -= vInitialDirection;
	float yawDiff = vDir.x - hkAimbot.v_curAngle.x;
	float pitchDiff = vDir.y - hkAimbot.v_curAngle.y;



	if (abs(yawDiff) > 1.0f || abs(pitchDiff) > 0.9f)return;


	if (!b_InVehWithWeapon) {

		hke.g_pInputBuffers[fb::ConceptYaw] = (0.04f / fl_FovX)*yawDiff;

		hke.g_pInputBuffers[fb::ConceptPitch] = (0.03f / fl_FovY)*pitchDiff;


	}
	else if (b_HasTurret) {

		//	m_AngularMomentumThreshold_Pitch
		//3x^3-6x^2+4x ,2.5 x - 1.5625 x^2

		if (yawDiff > 0.1f)yawDiff = 0.1f;
		else if (yawDiff < -0.1f) {
			yawDiff = -0.1f;
		}



		if (pitchDiff > 0.1f)pitchDiff = 0.1f;
		else if (pitchDiff < -0.1f) {
			pitchDiff = -0.1f;
		}


		if (abs(yawDiff) < 0.008f)fl_YawMultiplier = 0.4f*fl_YawMultiplier;


		if (abs(pitchDiff) < 0.005f)fl_PitchMultiplier = 0.4f*fl_PitchMultiplier;


		hke.g_pInputBuffers[fb::ConceptRoll] =
			(5600.f / (fl_YawMultiplier*fl_FovX))*(yawDiff);



		hke.g_pInputBuffers[fb::ConceptPitch] =
			(4500.f / (fl_FovY*fl_PitchMultiplier))*(pitchDiff);

		//	sprintf_s(buffer, 0xff, "fl_PitchMultiplier:%f,fl_YawMultiplier:%f", fl_PitchMultiplier, fl_YawMultiplier); logxxx(buffer);

	}
	else { return; }

	hkAimbot.LockOnEnemyFlags = 1;
	hkAimbot.m_LockOn_pEnemyPlayer = p_ClosestPlayer;
	hkAimbot.m_LockOn_pEnemySoldier = p_ClosestSoldier;
	return;


}
void dump(void* p_List
) {

	//	sprintf_s(buffer0, 0xff, "GetClientComponentByName"); logxxx0(buffer0);

	void* offset = p_List;

	unsigned int size = *(BYTE*)((intptr_t)offset + 0x9);

	//	sprintf_s(buffer0, 0xff, "size:%d", size); logxxx0(buffer0);

	fb::CompTuple* trashclass1 = (fb::CompTuple*)((intptr_t)offset + 0x10);
	for (unsigned int obj_index = 0; obj_index < size; obj_index++)

	{
		fb::ClassInfo* pType = (fb::ClassInfo*)trashclass1[obj_index].Object->GetType();
		sprintf_s(buffer, 0xff, "index:%d---id:%d---cid:%d---name:%s---size:%d", obj_index,
			trashclass1[obj_index].classid, pType->m_ClassId, pType->GetTypeInfoData()->m_Name, size); logxxx(buffer);
	}



}



void MiniMap() {
	if (!IsValidPtr(hke.mp_PlayerMngr))return;
	if (!IsValidPtr(hke.mp_LocalPlayer))return;
	dump(hke.mp_LocalPlayer->m_pControlledControllable->m_Complist);

	eastl::vector<fb::ClientPlayer*>* pVecCP = hke.mp_PlayerMngr->getPlayers();

	if (pVecCP->size() == 0) return;


	for (int i = 0; i < pVecCP->size(); i++)
	{
		fb::ClientPlayer* pClientPlayer = pVecCP->at(i);

		if (!IsValidPtr(pClientPlayer))continue;

		//	if (hke.mp_LocalPlayer->m_TeamId == pClientPlayer->m_TeamId)continue;

		fb::ClientControllableEntity* pControllable;

		pControllable = pClientPlayer->m_pControlledControllable;


		dump(pControllable->m_Complist);



	};

}
int  __stdcall  hkPreFrame(void* ptr, float DeltaTime)
{
	__try
	{
		hke.VarsUpdate();
		hke.WeaponUpgrade();
		hke.VehicleWeaponUpgrade();
		hke.AmmoBox();
		hke.MiniMap();

	}
	__except (EXCEPTION_EXECUTE_HANDLER) {};

	__try
	{
		if (GetAsyncKeyState(0x56) & 0x8000) {
			hkAimbot.bAimHead = true;

		}
		else { hkAimbot.bAimHead = false; }

		if ((GetAsyncKeyState(VK_LMENU) & 0x8000) || hkAimbot.bAimHead) {
			hkAimbot.mb_AimKeyPressed = true;
		}
		else {
			hkAimbot.mb_AimKeyPressed = false;
		}


		if (hkAimbot.mb_AimKeyPressed) {

			DoAimPrediction();
		}
		else {
			hkAimbot.LockOnEnemyFlags = 0;

		}

		for (int i = 0; i < 60; i++) {

			if (isnormal(hke.g_pInputBuffers[i])) {

				g_pBorderInputNode->m_InputCache->m_Event[i] += hke.g_pInputBuffers[i];
			}
			hke.g_pInputBuffers[i] = 0.f;
		}


	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{


	}


	return  oPreFrameUpdate(ptr, DeltaTime);
}
void writeJMP(BYTE* src, BYTE* dst, const int len)
{
	intptr_t dwRelAddr;
	DWORD dwOldProtect;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	dwRelAddr = (intptr_t)(dst - src) - 5;

	src[0] = 0xE9;

	*((intptr_t*)(src + 0x1)) = dwRelAddr;

	for (intptr_t c = 0x5; c < len; c++)
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


	WaitForSingleObject(hMutex, INFINITE);
	IPAddr hkDestinationAddress = 0x0101017f;
	DWORD ret = IcmpSendEcho2(IcmpHandle, NULL, NULL, NULL,
		hkDestinationAddress,
		RequestData,
		RequestSize,
		RequestOptions, ReplyBuffer, ReplySize, Timeout
	);

	PICMP_ECHO_REPLY ms = (PICMP_ECHO_REPLY)ReplyBuffer;
	fb::ClientGameContext* p = hke.mp_GameContext;
	fb::Level* pLevel = p->m_pLevel;

	if (ms != nullptr&&pLevel != nullptr) {
		//if (ms->RoundTripTime > 99) {
		srand((unsigned)time(NULL));
		ms->RoundTripTime = rand() & 0xf;
		ms->RoundTripTime += 83;
		//}
	}

	ReleaseMutex(hMutex);
	//CloseHandle(hMutex);
	return ret;
}


intptr_t __stdcall hkWeaponFiring_Function_1(void *p0, intptr_t p1, intptr_t p2) {

	intptr_t ret = oWeaponFiring_Function_1(p0, p1, p2);

	__try {

		fb::WeaponFiring* pWepFiring = (fb::WeaponFiring*)p0;

		if (!IsValidPtr(pWepFiring)) {
			goto ret0;
		}

		if (!IsValidPtr(pWepFiring->m_pPrimaryFire)) {
			goto ret0;
		}

		fb::FiringFunctionData* pFFD = pWepFiring->m_pPrimaryFire->m_FiringData;

		if (!IsValidPtr(pFFD)) {
			goto ret0;
		}


		hke.WeaponUpgrade();

		if (!IsValidPtr(pWepFiring->m_FireModes)) {
			goto ret0;
		}

		if (*pWepFiring->m_FireModes == 1) {
			VirtualProtect(pWepFiring->m_FireModes, 4, PAGE_EXECUTE_READWRITE, 0);
			*pWepFiring->m_FireModes = 0;

			VirtualProtect(pWepFiring->m_FireModes, 4, PAGE_READONLY, 0);
		}

	}
	__except (1) {

		goto ret0;
	}

ret0:
	return ret;
}

HRESULT __stdcall hkPresent(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags) {
	//hke.WeaponUpgrade();
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

		PreFrameHook = new Vtb::CVMTHookManager((intptr_t**)fb::BorderInputNode::GetInstance()->m_Vtable);
		oPreFrameUpdate = (tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(3);
		PreFrameHook->dwHookMethod((intptr_t)hkPreFrame, 3);

		//oWeaponFiring_Function_1 = (tWeaponFiring)Vtb::CVMTHookManager::ReplaceVtblFunction(
		//	(void*)OFFSET_WEAPONFIRING_VTB, (void*)hkWeaponFiring_Function_1, 1
		//);


		//PresentHook = new  Vtb::CVMTHookManager((intptr_t**)fb::DxRenderer::GetInstance()->m_pScreen->m_pSwapChain);
		//oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
		//PresentHook->dwHookMethod((intptr_t)hkPresent, 8);

		//	VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
		//	VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), old, nullptr);

		//	printf_s("hook!");
		//	sprintf_s(buffer, 0xff, "Hook"); logxxx(buffer);

		LPVOID pfn_IcmpSendEcho = (LPVOID)((intptr_t)GetProcAddress(GetModuleHandleW(L"iphlpapi.dll"), "IcmpSendEcho"));


		//	if (IsValidPtr(pfn_IcmpSendEcho)) {

		writeJMP((BYTE*)pfn_IcmpSendEcho, (BYTE*)hkIcmpSendEcho, 9);


		//};


	}; break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH: {

		//if (PresentHook != nullptr)PresentHook->UnHook();
		//if (PreFrameHook != nullptr)PreFrameHook->UnHook();
		//log_file.close();
	}
							 break;
	}
	return TRUE;
}
