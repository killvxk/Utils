#ifndef _WeaponProjectileModifier_H
#define _WeaponProjectileModifier_H
#include "FB_SDK/Frostbite_Classes.h"
#include "FB_SDK/WeaponModifierBase.h"
namespace fb
{
	class WeaponProjectileModifier
		: public WeaponModifierBase				// 0x00
	{
	public:
		ProjectileEntityData* m_projectileData;	// 0x08
	}; // 0x0C
};

#endif