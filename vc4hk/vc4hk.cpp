#include "stdafx.h"
#include "FB_SDK/Frostbite.h"
//#include "../vc3hk/VMTHook.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <limits>
#include "Aimbot.h"
#include "hkheader.h"

#pragma comment(lib, "iphlpapi.lib")

//#define LOGGG
char *buffer = new char[0xff];
std::ofstream log_file(
	"e:\\log\\hk.log", std::ios_base::out | std::ios_base::trunc);

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

	private:
		intptr_t**	m_ppdwClassBase;
		intptr_t*	m_pdwNewVMT;
		intptr_t*		m_pdwOldVMT;
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
	void* HookVtblFunction(void* pClassInstance, void* dwHook, const int Index)
	{
		void* pOrig;
		intptr_t *vtable = (intptr_t *)*(intptr_t *)pClassInstance;
		pOrig = (void*)(vtable[Index]);
		if (pOrig != dwHook) {
			intptr_t newVtableSize = dwGetVMTCount2(vtable);
			intptr_t* newVtable = new intptr_t[newVtableSize]; //leave some space
			memcpy(newVtable, vtable, newVtableSize * sizeof(intptr_t));
			newVtable[Index] = (intptr_t)dwHook;

			DWORD dwOld;

			VirtualProtect(pClassInstance, sizeof(intptr_t), PAGE_EXECUTE_READWRITE, &dwOld);

			*(intptr_t *)pClassInstance = (intptr_t)newVtable; //Replace Vtable

			VirtualProtect(pClassInstance, sizeof(intptr_t), dwOld, NULL);

		}

		return pOrig;
	}

}

using namespace Vtb;

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
Aimbot hkAimbot;
HackKev hke;
#pragma endregion Global Vars
void _stdcall DoAimPrediction() {

	float flBulletGrav = 0.f;
	float zero_angle = 0.f;
	int zero_index = -2;

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
	sprintf_s(buffer, 0xff, "pGameRenderer:%x", pGameRenderer); logxxx(buffer);
#endif // LOGGG

	fb::RenderView* pRenderView = pGameRenderer->m_pRenderView;

	if (!IsValidPtr(pRenderView))return;

#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pRenderView:%x", pRenderView); logxxx(buffer);
#endif // LOGGG

	float fl_FovX = pRenderView->m_FovX;
	float fl_FovY = pRenderView->m_FovY;

	fb::PlayerManager* pPlayerMngr = hke.mp_PlayerMngr;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pPlayerMngr:%x", pPlayerMngr); logxxx(buffer);;
#endif // LOGGG


	fb::ClientPlayer* pLocalPlayer = hke.mp_LocalPlayer;
	if (pLocalPlayer == nullptr)return;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pLocalPlayer:%x", pLocalPlayer); logxxx(buffer);;
#endif // LOGGG


	fb::ClientSoldierEntity* pMySoldier = hke.mp_LocalSoldier;
#ifdef LOGGG
	sprintf_s(buffer, 0xff, "pMySoldier:%x", pMySoldier); logxxx(buffer);;
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


#ifdef LOGGG
	sprintf_s(buffer, 0xff, "v_bulletspeed.z:%f", v_bulletspeed.z); logxxx(buffer);
#endif // LOGGG

	if (b_InVehWithWeapon) {
		fb::ClientVehicleEntity*	pVehivle = fb::MainVarPtr::Singleton()->pVehicleEntry;



		std::vector<void*>* v_pChildRota = new std::vector<void*>();

#ifdef LOGGG
		sprintf_s(buffer, 0xff, "pVehivle:%x", pVehivle); logxxx(buffer);
#endif // LOGG
		size_t nnn = hke.GetClientComponentByID(pVehivle->m_Complist, v_pChildRota, 366, true, false);
#ifdef LOGGG
		sprintf_s(buffer, 0xff, " hke.GetClientComponentByName"); logxxx(buffer);
#endif // LOGGG

		if (nnn > 0) {
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
					else	if (p_ChildRotationBodyData->m_RotationAxis == 0) {

						fl_PitchMultiplier = p_ChildRotationBodyData->m_AngularMomentumMultiplier;

					}


				}
			}
#ifdef LOGGG
			sprintf_s(buffer, 0xff, "fl_PitchMultiplier:%f,fl_YawMultiplier:%f", fl_PitchMultiplier, fl_YawMultiplier); logxxx(buffer);
#endif 
		}

		std::vector<void*>* v_pClientWeaponComponent = new std::vector<void*>;
		size_t aaa = hke.GetClientComponentByID(pVehivle->m_Complist, v_pClientWeaponComponent, 370, false, true);

		if (aaa > 0) {
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
	case 2487: {//missile
		v_bulletspeed.z = 50000.f;
		v_bulletspeed.y = 0.f;
		flBulletGrav = 0.f;// *(float*)((intptr_t)pBED + 0x170);
		break;
	};
			   //	case 2480: 
	default: {flBulletGrav = *(float*)((intptr_t)pBED + 0x130); break; };
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


	Vec_Enemyspeed.x = Vec_Enemyspeed.x*1.08f;
	Vec_Enemyspeed.y = Vec_Enemyspeed.y*1.08f;
	Vec_Enemyspeed.z = Vec_Enemyspeed.z*1.08f;
	Vec_Enemyspeed.w = 0.f;
	//sprintf_s(buffer, 0xff, "GetVec ok\tG:%f", flBulletGrav); logxxx(buffer);

	fb::Vec4  vDir;



	DWORD n_ReturnCode = hkAimbot.AimCorrection2(v_Origin, *curVecOfClosestSoldier, Vec_Enemyspeed, v_bulletspeed, flBulletGrav, &vDir);


	if (n_ReturnCode != 0x0) {
		return;
	}

	//sprintf_s(buffer, 0xff, "AimCorrection2_OK"); logxxx(buffer);

	if (zero_index > -1)vDir.y = vDir.y - zero_angle*DegToRad; //approx

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


		if (abs(yawDiff) < 0.008f)fl_YawMultiplier = 0.5f*fl_YawMultiplier;


		if (abs(pitchDiff) < 0.005f)fl_PitchMultiplier = 0.5f*fl_PitchMultiplier;


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



	DWORD ret = IcmpSendEcho2(IcmpHandle, NULL, NULL, NULL,
		DestinationAddress,
		RequestData,
		RequestSize,
		RequestOptions, ReplyBuffer, ReplySize, Timeout
	);

	PICMP_ECHO_REPLY ms = (PICMP_ECHO_REPLY)ReplyBuffer;

	if (IsValidPtr(ms)) {
		ms->RoundTripTime = ms->RoundTripTime & 0x3f;
		if (0 == ms->RoundTripTime) {
			ms->RoundTripTime = 0x3f;
		}
	}

	return ret;
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

		PreFrameHook = new CVMTHookManager((intptr_t**)fb::BorderInputNode::GetInstance()->m_Vtable);
		oPreFrameUpdate = (tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(3);
		PreFrameHook->dwHookMethod((intptr_t)hkPreFrame, 3);


		//	PresentHook = new CVMTHookManager((intptr_t**)fb::DxRenderer::GetInstance()->m_pScreen->m_pSwapChain);
		//	oPresent = (tPresent)PresentHook->dwGetMethodAddress(8);
		//	PresentHook->dwHookMethod((intptr_t)hkPresent, 8);

			//	VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
		//		VirtualProtect((void*)((intptr_t)pAntVtable + 11 * 8), sizeof(void*), old, nullptr);

		//		printf_s("hook!");
		//		sprintf_s(buffer, 0xff, "Hook"); logxxx(buffer);
		LPVOID pfn_IcmpSendEcho = (LPVOID)((intptr_t)GetProcAddress(GetModuleHandleW(L"iphlpapi.dll"), "IcmpSendEcho"));


		if (IsValidPtr(pfn_IcmpSendEcho)) {

			writeJMP((BYTE*)pfn_IcmpSendEcho, (BYTE*)hkIcmpSendEcho, 9);


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
