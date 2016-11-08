#ifndef __BF4Classes__H_
#define __BF4Classes__H_

#include "FB_SDK/Includes.h"
#include "FB_SDK/Offsets.h"
//#include "FB_SDK/EASTL_Includes.h"
#include "FB_SDK/Enumerations.h"
//#include "FB_SDK/EA.h"
//#include "FB_SDK/Juice.h"
#include "FB_SDK/Frostbite_Classes.h"
#include "FB_SDK/ClassT.h"
#include "FB_SDK/Vec2.h"
#include "FB_SDK/Vec4.h"

#include "FB_SDK/Mat4.h"
#include "FB_SDK/Main.h"






















//#include "FB_SDK/AxisAlignedBox.h"
//#include "FB_SDK/Plane.h"
//#include "FB_SDK/Frustum.h"
//#include "FB_SDK/Color32.h"
//#include "FB_SDK/Havok.h"
//#include "FB_SDK/ScreenshotModule.h"
//#include "FB_SDK/ISocket.h"
//#include "FB_SDK/BitArray.h"
//#include "FB_SDK/MessageListener.h"
//#include "FB_SDK/eastl_arena_allocator.h"
//#include "FB_SDK/InBitStream.h"
//#include "FB_SDK/OutBitStream.h"
//#include "FB_SDK/Timer.h"
//#include "FB_SDK/network.h"
//#include "FB_SDK/online.h"
//#include "FB_SDK/ant.h"
//#include "FB_SDK/PlayerManager.h"
//#include "FB_SDK/ControlObjectState.h"
//#include "FB_SDK/MemoryArena.h"
//#include "FB_SDK/String.h"
#include "FB_SDK/ITypedObject.h"
#include "FB_SDK/DataContainer.h"
//#include "FB_SDK/Asset.h"
//#include "FB_SDK/Score.h"
//#include "FB_SDK/DebugRender.h"
//#include "FB_SDK/Pad.h"
//#include "FB_SDK/MotionController.h"
//#include "FB_SDK/Device.h"
//#include "FB_SDK/Keyboard.h"
//#include "FB_SDK/Mouse.h"
//#include "FB_SDK/BorderInputNode.h"
//#include "FB_SDK/System.h"
//#include "FB_SDK/PropertyModificationListener.h"
//#include "FB_SDK/SupportsWeakPtr.h"
//#include "FB_SDK/PlayerData.h"
//#include "FB_SDK/GameTime.h"
//#include "FB_SDK/WorldRenderer.h"
//#include "FB_SDK/Level.h"
//#include "FB_SDK/DataBusData.h"
//#include "FB_SDK/EntityBusData.h"
//#include "FB_SDK/EventConnection.h"
//#include "FB_SDK/Blueprint.h"
//#include "FB_SDK/DebrisManager.h"
//#include "FB_SDK/PhysicsEntityUserData.h"
//#include "FB_SDK/IPhantom.h"
//#include "FB_SDK/IMoving.h"
//#include "FB_SDK/IRotation.h"
//#include "FB_SDK/IPhysics.h"
//#include "FB_SDK/IHavok.h"
//#include "FB_SDK/PhysicsRenderParams.h"
//#include "FB_SDK/Hook.h"
//#include "FB_SDK/MaterialGridManager.h"
//#include "FB_SDK/EntityEvent.h"
//#include "FB_SDK/DataContext.h"
//#include "FB_SDK/EntityBus.h"
//
//
//#include "FB_SDK/MaterialGridData.h"
//#include "FB_SDK/MaterialContainerPair.h"
//#include "FB_SDK/MaterialRelationPropertyPair.h"
//#include "FB_SDK/MaterialInteractionGridRow.h"
//#include "FB_SDK/PhysicsEntityBaseRayCast.h"
//#include "FB_SDK/PhysicsEntityContainer.h"
//#include "FB_SDK/EntityGridQueryJobData.h"
//
//
//#include "FB_SDK/IPhysicsRayCaster.h"
//#include "FB_SDK/HavokPhysicsManager.h"
//#include "FB_SDK/WeakTokenHolder.h"
//#include "FB_SDK/OnlineID.h"
//#include "FB_SDK/Player.h"
//#include "FB_SDK/EntryInput.h"
//#include "FB_SDK/EntityCollection.h"
//#include "FB_SDK/SpottingComponentData.h"
//#include "FB_SDK/GameObjectData.h"
//#include "FB_SDK/TeamInfo.h"
//#include "FB_SDK/GameEntityData.h"
//#include "FB_SDK/TeamEntityData.h"
//#include "FB_SDK/GameRenderer.h"
//#include "FB_SDK/WeaponComponent.h"
//#include "FB_SDK/EntryComponent.h"
//#include "FB_SDK/CameraComponent.h"
//#include "FB_SDK/CacheData.h"
//#include "FB_SDK/PropertyWriter.h"
//

//
//#include "FB_SDK/CharacterPhysicsEntity.h"
//#include "FB_SDK/RayCastHit.h"
//#include "FB_SDK/RayCastResult.h"
//#include "FB_SDK/SoldierEntity.h"
//#include "FB_SDK/BulletEntityData.h"
//
//#include "FB_SDK/CtrRefBase.h"
//#include "FB_SDK/ComponentInfo.h"
//#include "FB_SDK/ComponentCollection.h"
//#include "FB_SDK/FieldInfo.h"
//#include "FB_SDK/TypeInfo.h"
//#include "FB_SDK/TypeManager.h"
//#include "FB_SDK/ClassInfo.h"
//#include "FB_SDK/ModuleManager.h"
//#include "FB_SDK/KindOfEntityIterator.h"
//
//
//
//
//
//
//#include "FB_SDK/Mesh.h"
//#include "FB_SDK/Ragdoll.h"
//#include "FB_SDK/CameraShakeManager.h"
//
#include "FB_SDK/Client.h"
#include "FB_SDK/ClientGameContext.h"
//#include "FB_SDK/ClientComponent.h"
//#include "FB_SDK/ClientSpottingComponent.h"
//#include "FB_SDK/ClientSpottingTargetComponent.h"
//#include "FB_SDK/ClientCameraComponent.h"
//#include "FB_SDK/ClientPlayerView.h"
//#include "FB_SDK/ClientCameraContext.h"
//#include "FB_SDK/ClientGameEntity.h"
#include "FB_SDK/ClientChildBarrelComponent.h"
#include "FB_SDK/ClientChildComponent.h"
#include "FB_SDK/ClientPlayer.h"
//#include "FB_SDK/ClientPhysicsEntity.h"
#include "FB_SDK/ClientControllableEntity.h"
//#include "FB_SDK/ClientCharacterEntity.h"
//#include "FB_SDK/ClientAntAnimatableComponent.h"
//#include "FB_SDK/ClientProximityHookImpl.h"
//#include "FB_SDK/ClientEntryComponentSound.h"
//#include "FB_SDK/ClientGameWorld.h"
//#include "FB_SDK/ClientSoldierWeapon.h"
//#include "FB_SDK/ClientBoneCollisionComponent.h"
//#include "FB_SDK/ClientSoldierAimingSimulation.h"
//#include "FB_SDK/ClientEntryComponent.h"
//#include "FB_SDK/ClientAnimatedSoldierWeaponHandler.h"
//#include "FB_SDK/ClientSoldierWeaponsComponent.h"
//#include "FB_SDK/ClientWeapon.h"	
//#include "FB_SDK/ClientSoldierEntity.h"
//#include "FB_SDK/ClientVehicleEntity.h"
//#include "FB_SDK/ClientStanceFilterComponent.h"
//
//
//#include "FB_SDK/Entity.h"
//#include "FB_SDK/EntityStuff.h"
//
//#include "FB_SDK/PhysicsEntity.h"
//#include "FB_SDK/PhysicsEntityData.h"
//
//#include "FB_SDK/Vehicle.h"
//	
//#include "FB_SDK/AnimatedSoldierWeapon.h"
//#include "FB_SDK/WeaponFiringShooter.h"
//#include "FB_SDK/WeaponSwayCallbackImpl.h"
//#include "FB_SDK/WeaponModifier.h"	
//#include "FB_SDK/WeaponProjectileModifier.h"	
//#include "FB_SDK/WeaponShotModifier.h"
//#include "FB_SDK/WeaponEntityData.h"
//#include "FB_SDK/WeaponInfo.h"
//#include "FB_SDK/WeaponOffsetData.h"
//#include "FB_SDK/WeaponSwitching.h"
//#include "FB_SDK/ClientSoldierReplication.h"
//
//
//#include "FB_SDK/Rumble.h"
//#include "FB_SDK/Level.h" //
//#include "FB_SDK/UI.h"    //
//#include "FB_SDK/GameTime.h"
//#include "FB_SDK/WorldRenderer.h"	//
//
//#include "FB_SDK/IRender.h"	//
//#include "FB_SDK/IStateRenderer.h"	//
//#include "FB_SDK/ScreenRenderer.h"	//
//
//#include "FB_SDK/Snowroller.h"
#include "FB_SDK/Server.h"	//
#include "FB_SDK/x64_sdk.hpp"
#endif // __BF3Classes__H_
