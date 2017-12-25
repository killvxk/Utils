#ifndef _WeaponInfo_H
#define _WeaponInfo_H
#include "FB_SDK/Frostbite_Classes.h"
#include "FB_SDK/EntryComponent.h"
#include "FB_SDK/ClientWeaponComponentPrediction.h"
#include "FB_SDK/ClientWeaponComponentReplication.h"
namespace fb
{
		class WeaponInfo
		:public EntryComponent::WeaponInfo
    {
	public:
        ClientWeaponComponent &  m_weapon;                     // this+0x4
        ClientWeaponComponentReplication & m_replicated;                     // this+0x8
        ClientWeaponComponentPrediction & m_predicted;                     // this+0xC
        ClientStanceFilterComponent * m_stanceFilterComponent;                     // this+0x10

    }; // WeaponInfo 

};

#endif