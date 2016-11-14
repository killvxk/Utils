#pragma once
#ifndef __X64_SDK_H__
#define __X64_SDK_H__
#include "FB_SDK/Frostbite_Classes.h"

namespace fb {

	class CompTuple
	{
	public:
		__int64 a;//0x00
		__int32 flags;//0x08
		__int32 cc;//0x0c
		ITypedObject* Object;//0x10
		char b[0x8];


	};//Size=0x0020




	class DxRenderer
	{
	public:
		BYTE pad00[0x38];                    // 0x00
		Screen* m_pScreen;                    // 0x38
		BYTE pad78[0xC0];                    // 0x40
		ID3D11Device* m_pDevice;            // 0x100
		ID3D11DeviceContext* m_pContext;    // 0x108
		char _0x0110[192];
		void* m_settings; //0x01D0 

		static DxRenderer* GetInstance()
		{
			return *(DxRenderer**)OFFSET_DXRENDERER;
		}
	};//Size=0x0110

	class Screen
	{
	public:
		BYTE pad00[0x58];				//0x00
		unsigned int m_Width;			//0x58
		unsigned int m_Height;			//0x5C
		unsigned int m_WindowWidth;			//0x60
		unsigned int m_WindowHeight;		//0x64
		BYTE pad01[0x88];				//0x68
		IDXGISwapChain* m_pSwapChain;		//0xF0
	};

	class DxDisplaySettings
	{
	public:
		char _0x0000[40];
		__int32 m_FullscreenHeight; //0x0028 
		__int32 m_FullscreenWidth; //0x002C 
		float m_RefreshRate; //0x0030 
		__int32 m_FullscreenOutputIndex; //0x0034 
		__int32 m_PresentInterval; //0x0038 
		__int32 m_PresentImmediateThreshold; //0x003C 
		__int32 m_RenderAheadLimit; //0x0040 
		float m_StereoDepth; //0x0044 
		float m_StereoConvergeanceScale; //0x0048 
		float m_StereoSeparationScale; //0x004C 
		float m_StereoSoldierZoomConvergeanceScale; //0x0050 
		__int32 m_NVIDIAMinDriverVersion; //0x0054 
		char* m_AMDMinDriverVersion; //0x0058 
		float m_LowResDisplayPlaneScale; //0x0060 
		char _0x0064[52];

	};//Size=0x0098

	class GameRenderer
	{
	public:
		char _0x0000[72];
		GameRenderSettings* m_RenderSettings; //0x0048 
		char _0x0050[16];
		RenderView* m_pRenderView; //0x0060 

		static GameRenderer* GetInstance()
		{
			return *(GameRenderer**)OFFSET_GAMERENDERER;
		}
	};//Size=0x0068

	class GameRenderSettings
	{
	public:
		char _0x0000[16];
		__int32 m_InactiveSkipFrameCount; //0x0010 
		float m_ResolutionScale; //0x0014 
		__int32 m_XenonRingBufferSize; //0x0018 
		char _0x001C[36];
	};//Size=0x0040

	class RenderView
	{
	public:
		char _0x0000[64];
		SM::Matrix m_Transform; //0x0040 
		char _0x0080[52];
		float m_FovY; //0x00B4 
		float m_DefaultFovY; //0x00B8 
		float m_NearPlane; //0x00BC 
		float m_FarPlane; //0x00C0 
		float m_AspectRatio; //0x00C4 
		float m_OrthoWidth; //0x00C8 
		float m_OrthoHeight; //0x00CC 
		char _0x00D0[384];
		float m_FovX; //0x0250 
		float m_DepthHeightRatio; //0x0254 
		float m_FovScale; //0x0258 
		float m_FovScaleSquared; //0x025C 
		SM::Matrix m_View; //0x0260 
		SM::Matrix m_ViewTranspose; //0x02A0 
		SM::Matrix m_ViewInverse; //0x02E0 
		SM::Matrix m_Projection; //0x0320 
		SM::Matrix m_ViewAtOrigin; //0x0360 
		SM::Matrix m_ProjectionTranspose; //0x03A0 
		SM::Matrix m_ProjectionInverse; //0x03E0 
		SM::Matrix m_ViewProjection; //0x0420 
		SM::Matrix m_ViewProjectionTranspose; //0x0460 
		SM::Matrix m_ViewProjectionInverse; //0x04A0 

	};//Size=0x04E0

	class BorderInputNode
	{
	public:
		char _0x0000[8];
		InputCache* m_InputCache; //0x0008 
		char _0x0010[48];
		intptr_t m_Vtable; //0x0040 
		char _0x0048[8];
		Keyboard* m_pKeyboard; //0x0050 
		Mouse* m_pMouse; //0x0058 
		char _0x0060[40];

		static BorderInputNode* GetInstance()
		{
			return *(BorderInputNode**)OFFSET_BORDERINPUTNODE;
		}
	};//Size=0x0088

	class InputCache
	{
	public:
		char _0x0000[4];
		float m_Event[223]; //0x0004 
	};//Size=0x0008

	class Keyboard
	{
	public:
		char _0x0000[8];
		KeyboardDevice* m_pDevice; //0x0008 
	};//Size=0x0010

	class KeyboardDevice
	{
	public:
		virtual void Function0(); // 0x0000 
		virtual void Read(float SampleTime, bool VisualFrame); //0x0008  
		virtual const char* Name(unsigned int); //0x0010  
		virtual const char* Name(void); // 0x0018  
		virtual unsigned int ControlCount(); // 0x0020  
		virtual bool IsConnected(); // 0x0028 
		virtual bool IsAnalogue(unsigned int); // 0x0030 
		virtual float GetValue(unsigned int);    // 0x0038 

		char _0x0008[48];

	};//Size=0x0038

	class Mouse
	{
	public:
		char _0x0000[16];
		MouseDevice* m_pDevice; //0x0010 
		char _0x0018[40];

	};//Size=0x0040

	class MouseDevice
	{
	public:
		class MouseState
		{
		public:
			__int64 X; //0x0000 
			__int64 Y; //0x0008 
			__int64 Z; //0x0010 
			char m_Buttons[10]; //0x0018 
		};//Size=0x0022

		char _0x0000[208];
		unsigned char m_EnableCursor; //0x00D0 
		unsigned char m_UIOwnsInput; //0x00D1 
		unsigned char m_ShowCursor; //0x00D2 
		unsigned char m_CursorConfined; //0x00D3 
		unsigned char m_HasOverFlowed; //0x00D4 
		unsigned char m_UseRawInput; //0x00D5 
		unsigned char m_WindowActive; //0x00D6 
		char _0x00D7[1];
		unsigned char m_MouseOverWindow; //0x00D8 
		char _0x00D9[23];
		MouseState m_Current; //0x00F0 
		MouseState m_Buffer; //0x0112 

	};//Size=0x0134







	class GameSettings
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class ServerSettings
	{
	public:
		char _0x0000[64];

	};//Size=0x0040


	class ClientSettings
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class FileSystem
	{
	public:
		char _0x0000[56];

	};//Size=0x0038

	class GameTimer
	{
	public:
		__int64 m_Count; //0x0000 
		__int64 m_Counts; //0x0008 
		double m_DeltaTime; //0x0010 
		double m_Time; //0x0018 
		double m_TargetDelta; //0x0020 
		__int64 m_SleepMode; //0x0028 
		GameTimeSettings* m_pGameTimeSettings; //0x0030 
		__int32 m_TickFrequency; //0x0038 
		__int32 m_Ticks; //0x003C 
		__int32 m_OldTicks; //0x0040 
		__int32 m_Frames; //0x0044 
		__int32 N00000498; //0x0048 
		__int32 N000004A2; //0x004C 
		__int32 N00000499; //0x0050 
		__int32 N000004A5; //0x0054 
		double m_DeltaTime2; //0x0058 
		double m_ActualDelta; //0x0060 
		double m_OldActualDelta; //0x0068 
		double m_ExpectedTotalTime; //0x0070 
		double m_RealTotalTime; //0x0078 
		double m_SleptTime; //0x0080 
		double m_LostTime; //0x0088 
		double m_WorstFrameTime; //0x0090 
		double m_LogTime; //0x0098 
		double m_LatestDeltaTime; //0x00A0 
		double m_TimeInTick; //0x00A8 
		double m_BaseTicks; //0x00B0 
		double m_BaseTime; //0x00B8 
		unsigned char m_HitVSync; //0x00C0 

	};//Size=0x00C1

	class GameTimeSettings
	{
	public:
		char _0x0000[56];

	};//Size=0x0038



	class GameView
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class Online
	{
	public:
		char _0x0000[56];
		Connection* m_pConnection; //0x0038 

	};//Size=0x0040

	class InterpolationManager
	{
	public:
		char _0x0000[64];

	};//Size=0x0040
	class GameDataContainer : public DataContainer
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 2154;
		}
	};//Size=0x0010
	class DataBusPeer : public GameDataContainer
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 2156;
		}
		__int32 m_Flags; //0x0010
		char _0x0014[4];
	};//Size=0x0018

	class Asset : public DataContainer
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1469;
		}
		char* m_Name; //0x0010
	};//Size=0x0018

	class DataContainerPolicyAsset : public Asset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1786;
		}
	};//Size=0x0018


	class DataBusData : public Asset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1823;
		}
		Array<void*> m_PropertyConnections; //0x0018
		Array<void*> m_LinkConnections; //0x0020
		void* m_Interface; //0x0028
		__int16 m_Flags; //0x0030
		char _0x0032[6];
	};//Size=0x0038
	class EntityBusData : public DataBusData
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1824;
		}
		Array<void*> m_EventConnections; //0x0038
	};//Size=0x0040

	class Blueprint : public EntityBusData
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1825;
		}
	};//Size=0x0040

	class GameObjectData : public DataBusPeer
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 2157;
		}
	};//Size=0x0018
	class EntityData : public GameObjectData
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 2190;
		}
	};//Size=0x0018

	class ObjectBlueprint : public Blueprint
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1833;
		}
		GameObjectData* m_Object; //0x0040
	};//Size=0x0048





	class EffectBlueprint : public ObjectBlueprint
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1845;
		}
	};//Size=0x0048
	class CharacterBlueprint : public ObjectBlueprint
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1839;
		}
	};//Size=0x0048

	class VehicleCustomizationAsset : public DataContainerPolicyAsset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1813;
		}
		CustomizationTable* m_Customization; //0x0018
	};//Size=0x0020

	class CharacterCustomizationAsset : public DataContainerPolicyAsset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1816;
		}
		UIHudIcon m_UIHudIcon; //0x0018
		char _0x001C[4];
		char* m_UIKitIconName; //0x0020
		char* m_LabelSid; //0x0028
		CustomizationTable* m_VisualTable; //0x0030
		CustomizationTable* m_SpecializationTable; //0x0038
		Array<void*> m_VoiceOverLabels; //0x0040
	};//Size=0x0048
	class TeamAsset : public DataContainerPolicyAsset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1811;
		}
	};//Size=0x0018

	class TeamData : public TeamAsset
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 1812;
		}
		CharacterBlueprint* m_Soldier; //0x0018
		FactionId m_Faction; //0x0020
		char _0x0024[4];
		Array<VeniceSoldierCustimizationAsset*> m_SoldierCustomization; //0x0028
		Array<VehicleCustomizationAsset*> m_VehicleCustomization; //0x0030
	};//Size=0x0038

	class TeamEntityData : public EntityData
	{
	public:

		static __inline unsigned int ClassId()
		{
			return 2550;
		}
		TeamData* m_Team; //0x0018
		TeamId m_Id; //0x0020
		char _0x0024[4];
	};//Size=0x0028

	class PlayerManager
	{
	public:
		virtual void function();
		virtual eastl::vector<ClientPlayer*>* getPlayers();
		virtual eastl::vector<ClientPlayer*>* getSpectators();

		char _0x0008[1336];
		ClientPlayer* m_pLocalPlayer; //0x0540 
		ClientPlayer** m_ppPlayers; //0x0548 
		ClientPlayer* GetPlayerById(unsigned int id)
		{
			if (id < 70)
				return this->m_ppPlayers[id];
			return nullptr;
		}
	};//Size=0x0550

	class GameTime
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class Level
	{
	public:
		char _0x0000[56];
		LevelData* m_pLevelData; //0x0038 
		Array<TeamEntityData *> m_TeamEntity;
		char _0x0040[216];
		HavokPhysicsManager* m_pHavokPhysics;
		char _0x0128[8];
		__int64 m_pGameWorld;

	};//Size=0x0138

	class HavokPhysicsManager
	{
	public:
		char _0x0000[80];
		HavokManager* m_pHavokManager; //0x0050 
		IPhysicsRayCaster* m_pRayCaster; //0x0058 
		char _0x0060[60];
		float m_MaxVehicleHeight; //0x009C 
		char _0x00A0[16];
		TerrainPhysicsEntity* m_pTerrainPhysicsEntity; //0x00B0 
		char _0x00B8[248];
		Physics* m_pPhysics; //0x01B0 
		char _0x01B8[8];
		PhysicsSettings* m_pPhysicsSettings; //0x01C0 
		PhysicsRenderSettings* m_pPhysicsRenderSettings; //0x01C8 

	};//Size=0x01D0

	class TerrainPhysicsEntity
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class Physics
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class PhysicsSettings
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class PhysicsRenderSettings
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class Material
	{
	public:
		enum MaterialFlag
		{
			MFSeeThrough = 0x1,
			MFClientDestructable = 0x40000000,
			MFPenetrable = 0x8
		};
		UINT32 m_flagsAndIndex;
		__forceinline UINT32 isPenetrable()
		{
			return (m_flagsAndIndex & MFPenetrable);
		};
		__forceinline UINT32 isSeeThrough()
		{
			return (m_flagsAndIndex & MFSeeThrough);
		};
	};

	class RayCastHit
	{
	public:
		Vec4 m_Position;  // 0x00
		Vec4 m_Normal;  // 0x10
		void*  m_RigidBody; // 0x20
		Material m_Material;  // 0x28
		DWORD  m_Part;   // 0x30
		FLOAT  m_Lambda;  // 0x34
		char  _pad[200];  // 0x38
	}; //Size = 0x0070

	class IPhysicsRayCaster
	{
	public:
		enum RayCastFlags
		{
			NoCheck = 0,
			CheckDetailMesh = 0x0DB,
			IsAsyncRaycast = 0x2,
			DontCheckWater = 0x0FD,
			DontCheckTerrain = 0x07A,
			DontCheckRagdoll = 0x10,
			DontCheckCharacter = 0x20,
			DontCheckGroup = 0x40,
			DontCheckPhantoms = 0x80,
		};
		virtual bool PhysicsRayQuery(const char* identifier, Vec4* from, Vec4* to, RayCastHit* hit, int flag, eastl::fixed_vector<void const*, 8, 0>* PhysicsEntityList);
	};//Size=0x0008

	class HavokManager
	{
	public:
		char _0x0000[56];
		__int64 m_pHKPWorld; //0x0038 

	};//Size=0x0040

	class LevelData
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class Connection
	{
	public:
		char _0x0000[64];

	};//Size=0x0040



	class VeniceSoldierCustimizationAsset
	{
	public:
		char _0x0000[32];
		char* m_pUIKitIconName; //0x0020 
		char* m_pUIHudIcon; //0x0028 
		CustomizationTable* m_pAppearance; //0x0030 
		char _0x0038[16];
		CustomizationTable* m_pWeaponTable; //0x0048 

	};//Size=0x0050

	class CustomizationTable
	{
	public:
		char _0x0000[16];
		Array<	CustomizationUnlockParts*> m_ppList; //0x0010 
		char _0x0018[40];

	};//Size=0x0040

	class CustomizationUnlockParts
	{
	public:
		char _0x0000[16];
		char* m_UICategorySid;//ID_M_SOLDIER_GADGET1
		char _0x0018[8];
		intptr_t** m_SelectableUnlocks; //0x0020 
		char _0x0028[16];

	};//Size=0x0038

	class LinearTransform
	{
	public:
		union
		{
			struct
			{
				SM::Vector3 left;
				SM::Vector3 up;
				SM::Vector3 forward;
				SM::Vector3 trans;
			};
			FLOAT data[4][4];
		};
		LinearTransform()
		{}
	};

	class AxisAlignedBox
	{
	public:
		Vec4 m_Min; //0x0000 
		Vec4 m_Max; //0x0010 

	
	};//Size=0x0020

	struct TransformAABBStruct {
		LinearTransform Transform;
		AxisAlignedBox AABB;
		SM::Matrix pad;

		TransformAABBStruct()
		{}
	};
	class BreathControlHandler
	{
	public:
		char _0x0000[56];
		float m_breathControlTimer; //0x0038 
		float m_breathControlMultiplier; //0x003C 
		float m_breathControlPenaltyTimer; //0x0040 
		float m_breathControlpenaltyMultiplier; //0x0044 
		float m_breathControlActive; //0x0048 
		float m_breathControlInput; //0x004C 
		float m_breathActive; //0x0050 
		char _0x0054[4];
		float m_Enabled; //0x0058 
	};
	
	class ClientChassisComponent
	{
	public:
		char _0x0000[448];
		Vec4 m_Velocity; //0x01C0 
		char _0x01D0[0x2d0];
	};//Size=0x04A0


	class ClientVehicleEntity : public ClientControllableEntity
	{
	public:
		char _0x0148[0xF0];//0x148
		void* m_pPhysicsEntity;//0x238
		float m_waterLevel; //0x0240 
		float m_terrainLevel; //0x0244 
		float m_waterLevelUpdateTimer; //0x0248 
		float m_terrainLevelUpdateTime; //0x024C 
		AxisAlignedBox m_childrenAABB; //0x0250 
		char _0x0250[0x10];//0x0270 
		Vec4 m_Velocity; //0x0280 
		Vec4 m_prevVelocity; //0x0290 
		char _0x029C[0x150];
		ClientChassisComponent* m_Chassis; //0x03E0 


		inline ClientChassisComponent* GetClientChassisComponent(){

			return this->m_Chassis;
		}
		inline Vec4 *GetVehicleVelocity()
		{
			
				return &(this->m_Velocity);
			
		
		}
	};//Size=0x0520
	class ClientSoldierPrediction
	{
	public:
		virtual void            function_0();
		virtual Vec4        getPosition();
		virtual void            setPosition(Vec4 pos);

		CharacterPhysicsEntity* m_characterPhyEntity; //0x0008  
		char _0x0010[16];
		Vec4 m_ParachuteRotation; //0x0020  
		Vec4 m_Position; //0x0030  
		
		Vec4 surfaceVelocity; //0x0040  
		
		Vec4 m_Velocity; //0x0050  
	
		Vec4 groundNormal; //0x0060  
		
		__int32 groundSupported; //0x0070  
		__int32 groundMaterialIndex; //0x0074  
		__int32 m_state; //0x0078  
		BYTE m_Pose; //0x007C  
		char _0x007D[3];
		BYTE m_ChangingToPose; //0x0080  
		char _0x0081[23];
		__int32 Event; //0x0098  
		BYTE PlayerState; //0x009C  
	};//Size=0x009D 
	class ClientSoldierEntity : public ClientControllableEntity
	{
	public:
		enum ePoseType
		{
			Pose_Standing = 0,
			Pose_Crouching,
			Pose_Prone
		};






		//	char _paddddddddp[0x568];
			//char _0x0148[160];
			//AntAnimatableComponent* m_pAnimatable; //0x01E8 
			//AntAnimatableComponent* m_pAnimatable2; //0x01F0 
			//char _0x01F8[760];
			//__int32 m_PoseType; //0x04F0 
			//__int32 m_EngineChams; //0x04F4 
			//char _0x04F8[120];

			//vtb
		char aa[0x98];                              //0x00                
		ClientPlayer*                  m_pPlayer;                  // 0x1E0
		AntAnimatableComponent* m_pAnimatable; //0x01E8 
		AntAnimatableComponent* m_pAnimatable2; //0x01F0 
		char a[0x490 - 0x1f8];
		ClientSoldierPrediction* m_pPredictedController; //0x0490  
		char pad_0x0498[0x4d8 - 0x490];
		float m_authorativeYaw; //0x04D8  
		float m_authorativePitch; //0x04DC  
		__int32 m_aimingEnabled; //0x04E0  
		float m_cachedPitch; //0x04E4  
		__int64 m_soldierSound; //0x04E8  
		__int32 m_poseType; //0x04F0  
		char aaa[0x570 - 0x4f4];
		ClientSoldierWeaponsComponent* m_pWeaponComponent; //0x0570 
		ClientSoldierBodyComponent* m_pBodyComponent; //0x0578 
		RagdollComponent* m_pRagdollComponent; //0x0580 
		BreathControlHandler* m_breathControlHandler; //0x0588
		char pad_0x0570[0x10];//0x590
		void* m_sprintInputHandler; //0x0580  + 20
		__int32 padThis; //0x0588  + 20
		float m_timeSinceLastSprinted; //0x058C  + 20
		BYTE m_sprinting; //0x0590  + 20
		BYTE m_Occluded; //0x05b1

		char N00001BCE[6]; //0x05B2 
		char _0x05B8[1432];
		ParachuteComponent* m_pParachute; //0x0B50 
		char _0x0B58[152];
		ClientSpottingTargetComponent* m_pSpottingComp; //0x0BF0 
		char _0x0BF8[24];
		intptr_t m_pSpottingTargetComp; //0x0C10 
		char _0x0C18[88];
		SoldierSuppressionComponent* m_pSuppressionComp; //0x0C70 
		char _0x0C78[184];
		VaultComponent* m_pVaultComp; //0x0D30 
		char _0x0D38[1264];

		inline	 Vec4* GetSoldierVelocity() {
			void* a = *(void**)((intptr_t)this + 0x490);

			if (IsValidPtr(a)) {
				return (Vec4*)((intptr_t)a + 0x50);
			}
			else {
			return nullptr;
		}
	}


	};//Size=0x1228


	class AntAnimatableComponent
	{
	public:
		char _0x0000[104];
		GameAnimatable* m_Handler; //0x0068 
		char _0x0070[16];

	};//Size=0x0080

	class GameAnimatable
	{
	public:
		char _0x0000[212];
		unsigned char m_HadVisualUpdate; //0x00D4 

	};//Size=0x00D5

	class AnimatedSoldierWeaponHandler
	{
	public:
		ClientSoldierWeapon* m_pWeaponList[7]; //0x0000 
	};//Size=0x0040

	class ClientSoldierWeaponsComponent
	{
	public:
		char _0x0000[208];
		SM::Matrix m_WeaponTransform; //0x00D0 
		char _0x0110[1920];
		AnimatedSoldierWeaponHandler* m_Handler; //0x0890 
		char _0x0898[48];
		ClientSoldierEntity* m_pOwner; //0x08C8 
		char _0x08D0[456];
		__int32 m_CurrentWeaponIndex; //0x0A98 
		__int32 m_LastWeaponIndex; //0x0A9C 
		__int32 m_LastGunIndex; //0x0AA0 
		char _0x0AA4[28];
		__int32 m_CurrentZoomLevel; //0x0AC0 
		__int32 m_ZoomLevelMax; //0x0AC4 
		__int32 m_ZeroingDistanceLevel; //0x0AC8 

	inline	ClientSoldierWeapon* GetActiveSoldierWeapon()
		{
			
		__try{
			
				return m_Handler->m_pWeaponList[m_CurrentWeaponIndex];
		}
		__except (1) {
			return nullptr;
		}

		};
		int GetSlot()
		{
			return m_CurrentWeaponIndex;
			//0 or 1 is primary or secondary
		}
	};//Size=0x0ACC

	class ClientSoldierWeapon
	{
	public:
		char _0x0000[18824];
		SoldierAimingSimulation* m_authorativeAiming; //0x4988 
		char _0x4990[24];
		ClientWeapon* m_pWeapon; //0x49A8 
		char _0x49B0[16];
		WeaponFiring* m_pPrimary; //0x49C0 
		char _0x49C8[696];
	};//Size=0x4C80
	class SoldierAimingSimulation {
	public:
		SoldierAimingSimulationData* m_data;//0x0000 
		ClientSoldierAimingEnvironment* m_environment; //0x0008 
		AimAssist* m_pFPSAimer; //0x0010 
		float m_Yaw; //0x0018 
		float m_Pitch; //0x001C 
		float m_AimYawTimer; //0x0020 
		float m_AimPitchTimer; //0x0024 
		SM::Vector2 m_Sway; //0x0028 
		float m_DeltaTime; //0x0030 
		char _0x0034[8];
		SM::Vector2 m_ViewDelta; //0x003C 
		char _0x0044[40];
		int m_zoomLevel; //0x0068 
		SM::Matrix m_Transform; //0x0070 
		Vec4 m_Position; //0x00B0 
		Vec4 m_View; //0x00C0 
		Vec4 m_Velocity; //0x00D0 
		char _0x00E0[88];
		float m_Fov; //0x0138 
		char _0x013C[28];
		TypeInfo* m_RayResult; //0x0158 
		Vec4 m_RayHitPoint; //0x0160 
		__int32 m_RayLength; //0x0170 
	};//Size=0x0174



	class AimAssist
	{
	public:
		char _0x0000[20];
		SM::Vector2 m_AimAngles;
	};//Size=0x001C

	class ClientWeapon
	{
	public:
		char N000018B4[24]; //0x0000 
		WeaponFiringData* m_pWeaponFiring; //0x0018 
		WeaponModifier* m_pWeaponModifier; //0x0020 
		char _0x0028[8];
		Vec4 m_MoveSpeed; //0x0030 
		SM::Matrix m_ShootSpace; //0x0040 
		SM::Matrix m_ShootSpaceIdentity; //0x0080 
		char _0x00C0[464];
		float m_CameraFOV; //0x0290 
		float m_WeaponFOV; //0x0294 
		float m_FOVScaleFactor; //0x0298 
		char _0x029C[20];
		__int32 m_ZoomLevel; //0x02B0 

	};//Size=0x0B70

	class WeaponFiringData
	{
		class RumbleFiringData
		{
		public:
			float LowRumble; //0x0000 
			float HighRumble; //0x0004 
			float RumbleDuration; //0x0008 

		}; //Size=0x000C
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //

		__int32 Flag00; //0x0008 
		__int32 Flag01; //0x000C 
		FiringFunctionData* m_FiringData; //0x0010 
		float m_DeployTime; //0x0018 
		float m_ReactivateCooldownTime; //0x001C 
		float m_DisableZoomOnDeployTime; //0x0020 
		float AltDeployTime; //0x0024 
		__int32 AltDeployId; //0x0028 
		char pad_0x002C[0x4]; //0x002C
		GunSwayData* m_WeaponSway; //0x0030 
		RumbleFiringData m_Rumble; //0x0038 
		float m_SupportDelayStand; //0x0044 
		float m_SupportDelayProne; //0x0048 
		unsigned char m_UseAutoAiming; //0x004C 
		unsigned char m_InflictSelfDamage; //0x004D 
		unsigned char m_ShowEnemyNametagOnAim; //0x004E 
		unsigned char m_ReloadWholeMags; //0x004F 
		unsigned char m_DisableReloadWhileSprinting; //0x0050 
		unsigned char m_AbortReloadOnSprint; //0x0051 
		char pad_0x0052[0x6]; //0x0052

	}; //Size=0x0058

	class OverheatData
	{
	public:
		char _0x0000[80];
		float m_HeatPerBullet; //0x0050 
		float m_HeatDropPerSecond; //0x0054 
		float m_OverheatPenaltyTime; //0x0058 
		float m_OverheatThreshold; //0x005C 
	};//Size=0x0060


	class ShotConfigData
	{
	public:
		Vec4 m_InitialPosition; //0x0000 
		Vec4 m_InitialDirection; //0x0010 
		Vec4 m_InitialSpeed; //0x0020 
		void* InitialDirectionScaleByPitch; //0x0030 
		void* InitialSpeedScaleByPitch; //0x0038 
		float InheritWeaponSpeedAmount; //0x0040 
		char pad_0x0044[0xC]; //0x0044
		ProjectileEntityData* m_ProjectileData; //0x0050 
		void* SecondaryProjectileData; //0x0058 
		void* Projectile; //0x0060 
		void* SecondaryProjectile; //0x0068 
		float SpawnDelay; //0x0070 
		float SpawnDelayZoomed; //0x0074 
		__int32 NumberOfBulletsPerShell; //0x0078 
		__int32 NumberOfBulletsPerShot; //0x007C 
		__int32 NumberOfBulletsPerBurst; //0x0080 
		unsigned char RelativeTargetAiming; //0x0084 
		unsigned char ForceSpawnToCamera; //0x0085 
		unsigned char SpawnVisualAtWeaponBone; //0x0086 
		unsigned char ActiveForceSpawnToCamera; //0x0087 
		char pad_0x0088[0x8]; //0x0088

	}; //Size=0x0090

	class FiringFunctionData
	{
		class OverHeatData
		{
		public:
			char pad_0x0000[0x50]; //0x0000
			float HeatPerBullet; //0x0050 
			float HeatDropPerSecond; //0x0054 
			float OverHeatPenaltyTime; //0x0058 
			float OverHeatThreshold; //0x005C 

		}; //Size=0x0060
		class FiringDispersionData
		{
		public:
			float MinAngle; //0x0000 
			float MaxAngle; //0x0004 
			float IncreasePerShot; //0x0008 
			float DecreasePerSecond; //0x000C 

		}; //Size=0x0010
		class WeaponDispersion 
		{
		public:
			FiringDispersionData StandDispersion;
			FiringDispersionData CrouchDispersion; //0x0010 
			FiringDispersionData ProneDispersion; //0x0020 
			float JumpDispersionAngle; //0x0030 
			float ProneTransitionDispersionAngle; //0x0034 
			float MoveDispersionAngle; //0x0038 
			float MoveZoomedDispersionAngle; //0x003C 
			float DecreasePerSecond; //0x0040 

		}; //Size=0x0044
		class FireLogicData
		{
		public:
			float MaxHoldTime; //0x0000 
			float MinPowerModifier; //0x0004 
			float MaxPowerModifier; //0x0008 
			float PowerIncreasePerSecond; //0x000C 
			float Delay; //0x0010 
			float KilledHoldingPowerModifier; //0x0014 
			unsigned char ForceFireWhenKilledHolding; //0x0018 
			char pad_0x0019[0x3]; //0x0019
			float BoltActionDelay; //0x001C 
			float BoltActionTime; //0x0020 
			unsigned char HoldBoltActionUntilFireRelease; //0x0024 
			unsigned char HoldBoltActionUntilZoomRelease; //0x0025 
			unsigned char ForceBoltActionOnFireTrigger; //0x0026 
			unsigned char UnZoomOnBoltAction; //0x0027 
			unsigned char ReturnToZoomAfterBoltAction; //0x0028 
			char pad_0x0029[0x3]; //0x0029
			float MaxRecoilAngleX; //0x002C 
			float MinRecoilAngleX; //0x0030 
			float MaxRecoilAngleY; //0x0034 
			float MinRecoilAngleY; //0x0038 
			float MaxRecoilAngleZ; //0x003C 
			float MinRecoilAngleZ; //0x0040 
			float MaxRecoilFov; //0x0044 
			float MinRecoilFov; //0x0048 
			unsigned char RecoilFollowsDispersion; //0x004C 
			char pad_0x004D[0x3]; //0x004D
			__int32 FireInputAction; //0x0050 
			__int32 ReloadInputAction; //0x0054 
			__int32 CycleFireModeInputAction; //0x0058 
			float TriggerPullWeight; //0x005C 
			float RateOfFire; //0x0060 
			float RateOfFireForBurst; //0x0064 
			float DelayBetweenBursts; //0x0068 
			float ClientFireRateMultiplier; //0x006C 
			float ReloadDelay; //0x0070 
			float ReloadTime; //0x0074 
			void* ReloadTimerArray; //0x0078 
			float ReloadTimeBulletsLeft; //0x0080 
			float ReloadThreshold; //0x0084 
			float PreFireDelay; //0x0088 
			float PreFireDelayZoomed; //0x008C 
			float PreFireRequireHold; //0x0090 
			float AutomaticDelay; //0x0094 
			__int32 ReloadLogic; //0x0098 
			__int32 ReloadType; //0x009C 
			__int32 FireLogicType; //0x00A0 
			char pad_0x00A4[0x4]; //0x00A4
			void* FireLogicTypeArray; //0x00A8 
			unsigned char HoldOffReloadUntilFireRelease; //0x00B0 
			unsigned char HoldOffReloadUntilZoomRelease; //0x00B1 
			unsigned char ForceReloadActionOnFireTrigger; //0x00B2 
			unsigned char AlwaysAutoReload; //0x00B3 
			unsigned char ZoomTransitionDisableFire; //0x00B4 
			char pad_0x00B5[0x3]; //0x00B5

		}; //Size=0x00B8

		class AmmoConfigData
		{
		public:
			__int32 MagazineCapacity; //0x0000 
			__int32 NumberOfMagazines; //0x0004 
			__int32 TraceFrequency; //0x0008 
			__int32 AmmoPickupMinAmount; //0x000C 
			__int32 AmmoPickupMaxAmount; //0x0010 
			float AutoReplenishDelay; //0x0014 
			float AmmoBagPickupDelayMultiplier; //0x0018 
			__int32 AmmoBagPickupAmount; //0x001C 
			unsigned char AutoReplenishMagazine; //0x0020 
			unsigned char StartUnloaded; //0x0021 
			char pad_0x0022[0x2]; //0x0022

		}; //Size=0x0024
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //

		__int32 Flag00; //0x0008 
		__int32 Flag01; //0x000C 
		FiringDispersionData* m_Dispersion; //0x0010 
		WeaponDispersion m_WeaponDispersion; //0x0018 
		char pad_0x005C[0x4]; //0x005C
		ShotConfigData m_ShotConfigData; //0x0060 
		OverHeatData m_OverHeat; //0x00F0 
		void* m_FireEffects1p; //0x0150 
		void* m_FireEffects3p; //0x0158 
		void* m_Sound; //0x0160 
		FireLogicData m_FireLogic; //0x0168 
		AmmoConfigData m_Ammo; //0x0220 
		float m_SelfHealTimeWhenDeployed; //0x0244 
		unsigned char m_UsePrimaryAmmo; //0x0248 
		unsigned char m_UnlimitedAmmoForAI; //0x0249 
		char pad_0x024A[0x6]; //0x024A

	}; //Size=0x0250

	class ProjectileEntityData
	{
	public:
		char _0x0000[96];
		char* m_Name; //0x0060 
		char _0x0068[40];
		float m_InitialSpeed; //0x0090 
		float m_TimeToLive; //0x0094 
		__int32 m_MaxCount; //0x0098 
		float m_InitMeshHideTime; //0x009C 
		float m_VisualConvergeDistance; //0x00A0 
		float m_VisualConvergeDelay; //0x00A4 
		float m_ProxyVisualConvergeDelay; //0x00A8 
		float m_ProxyVisualConvergeDuration; //0x00AC 
		char _0x00B0[16];
		WeaponSuppressionData* m_pSuppressionData; //0x00C0 
		char* m_AmmunitionType; //0x00C8 
		char _0x00D0[4];
		AntHitReactionWeaponType m_HitReactionWeaponType; //0x00D4
		unsigned char m_DetonateOnTimeout; //0x00D8 
		unsigned char m_ServerProjectileDisabled; //0x00D9 
		char N0000197A[6]; //0x00DA 

	};//Size=0x00E0

	class MessProjectileEntityData
	{
	public:
		Vec4 m_AngularVelocity; //0x0000 
		char _0x0010[16]; //0x0010 
		float m_InstantAttachableTestDistance; //0x0020 
		float m_InstantAttachableVisualConvergenceDelay; //0x0024 
		float m_InstantAttachableVisualConvergenceDuration; //0x0028 
		float m_MaxAttachableInclination; //0x002C 
		float m_UnspawnAfterDetonationDelay; //0x0030 
		unsigned char m_IsAttachable; //0x0034 
		unsigned char m_InstantAttachableTestUnderReticle; //0x0035 
		unsigned char m_ExtraDamping; //0x0036 
		char N000019B5[9]; //0x0037 
	};//Size=0x0040

	class BulletEntityData : public ProjectileEntityData
	{
	public:
		MessProjectileEntityData m_MeshProjectileEntityData; //0x00E0 
		SoundAsset* m_FlyBySound; //0x0120 
		__int64 m_DudExplosion; //0x0128 
		float m_Gravity; //0x0130 
		float m_ImpactImpulse; //0x0134 
		float m_DetionationTimeVariation; //0x0138 
		float m_VehicleDetonationRadius; //0x013C 
		float m_VehicleDetonationActivationDelay; //0x0140 
		float m_FlyBySoundRadius; //0x0144 
		float m_FlyBySoundSpeed; //0x0148 
		float m_Stamina; //0x014C 
		float m_DistributeDamageOverTime; //0x0150 
		float m_StartDamage; //0x0154 
		float m_EndDamage; //0x0158 
		float m_DamageFalloffStartDist; //0x015C 
		float m_DamageFalloffEndDist; //0x0160 
		float m_TimeToArmExplosion; //0x0164 
		float m_FirstFrameTravelDistance; //0x0168 
		unsigned char m_HasVehicleDetonation; //0x016C 
		unsigned char m_InstantHit; //0x016D 
		unsigned char m_StopTrailEffectOnUnspawn; //0x016E 
		char _0x016F[1];

	};//Size=0x0170

	class WeaponSuppressionData
	{
	public:
		char _0x0000[16];
		float m_MinMultiplier; //0x0010 
		float m_MaxMultiplier; //0x0014 
		float m_MinDistance; //0x0018 
		float m_MaxDistance; //0x001C 

	};//Size=0x0020

	class SoundAsset
	{
	public:
		char _0x0000[24];
		SoundScopeData* m_Scope; //0x0018 
		SoundScopeData* m_ReferencedData; //0x0020 

	};//Size=0x0028

	class SoundScopeData
	{
	public:
		char _0x0000[16];
		char* m_Name; //0x0010 
		SoundScopeStrategyData* m_ScopeStrategyData; //0x0018 

	};//Size=0x0020

	class SoundScopeStrategyData
	{
	public:
		char _0x0000[16];
		char* m_Name; //0x0010 
		char* m_Stages; //0x0018 
		char N000019E8[32]; //0x0020 

	};//Size=0x0040

	class WeaponModifier
	{
	public:
		char _0x0000[64];
		unsigned char m_BreathControl; //0x0040 
		unsigned char m_SupportedShooting; //0x0041 
		unsigned char m_UnZoomOnBoltAction; //0x0042 
		unsigned char m_HoldBoltActionUntilZoomRelease; //0x0043 
		char _0x0044[12];
		FiringDataModifier* m_FiringDataModifier; //0x0050 
		FiringEffectsModifier* m_FiringEffectsModifier; //0x0058 
		SoundModifier* m_SoundModifier; //0x0060 
		WeaponShotModifier* m_ShotModifier; //0x0068 
		char _0x0070[56];
		AimingSimulationModifier* m_AimingSimulationModifier; //0x00A8 
		char _0x00B0[16];
		ZeroingModifier* m_ZeroingModifier; //0x00C0 
		char _0x00C8[48];
	};//Size=0x0044

	class WeaponFiring
	{
	public:
		char _0x0000[120];
		WeaponSway* m_Sway; //0x0078 
		char _0x0080[168];
		WeaponFiringData* m_pPrimaryFire; //0x0128 
		char _0x0130[24];
		__int32 m_WeaponState; //0x0148 
		__int32 m_LastWeaponState; //0x014C 
		__int32 m_NextWeaponState; //0x0150 
		char _0x0154[8];
		float m_TimeToWait; //0x015C 
		float m_ReloadTimer; //0x0160 
		float m_HoldReleaseMinDelay; //0x0164 
		float m_RecoilTimer; //0x0168 
		float m_RecoilAngleX; //0x016C 
		float m_RecoilAngleY; //0x0170 
		float m_RecoilAngleZ; //0x0174 
		float m_RecoilFOVAngle; //0x0178 
		float m_RecoilTimeMultiplier; //0x017C 
		float m_OverheatDropMultiplier; //0x0180 
		char _0x0184[40];
		unsigned char m_IsNotFiring; //0x01AC 
		unsigned char m_JustShot; //0x01AD 
		unsigned char m_IsOverheated; //0x01AE 
	};//Size=0x01AF

	class ClientSoldierBodyComponent
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class SkeletonAsset
	{
	public:
		char _0x0000[24];
		char** m_ppBoneNames; //0x0018
	};//Size=0x0020

	class AnimationSkeleton
	{
	public:
		SkeletonAsset* m_SkeletonAsset; //0x0000 
		__int32 m_BoneCount; //0x0008 
		char* GetBoneNameAt(int i)
		{
			if (i <= m_BoneCount)
				return m_SkeletonAsset->m_ppBoneNames[i];
			return "";
		}
	};//Size=0x000C

	class QuatTransform
	{
	public:
		Vec4 m_TransAndScale; //0x0000 
		Vec4 m_Rotation; //0x0010 
	};//Size=0x0020

	class UpdatePoseResultData
	{
	public:
		enum BONES
		{
			Reference = 0,
			AITrajectory = 1,
			Trajectory = 2,
			TrajectoryEnd = 3,
			Hips = 4,
			Spine = 5,
			Spine1 = 6,
			Spine2 = 7,
			LeftShoulder = 8,
			LeftArm = 9,
			LeftArmRoll = 10,
			LeftForeArm = 11,
			LeftForeArmRoll = 12,
			LeftForeArmRoll1 = 13,
			LeftHand = 14,
			LeftHandMiddle0 = 15,
			LeftHandMiddle1 = 16,
			LeftHandMiddle2 = 17,
			LeftHandMiddle3 = 18,
			LeftHandMiddle4 = 19,
			LeftHandRing0 = 20,
			LeftHandRing1 = 21,
			LeftHandRing2 = 22,
			LeftHandRing3 = 23,
			LeftHandRing4 = 24,
			LeftHandPinky0 = 25,
			LeftHandPinky1 = 26,
			LeftHandPinky2 = 27,
			LeftHandPinky3 = 28,
			LeftHandPinky4 = 29,
			LeftHandIndex0 = 30,
			LeftHandIndex1 = 31,
			LeftHandIndex2 = 32,
			LeftHandIndex3 = 33,
			LeftHandIndex4 = 34,
			LeftHandThumb1 = 35,
			LeftHandThumb2 = 36,
			LeftHandThumb3 = 37,
			LeftHandThumb4 = 38,
			LeftHandProp1 = 39,
			LeftElbowRoll = 40,
			LeftArmCloth = 41,
			LeftShoulderPhys1 = 42,
			Neck = 43,
			Neck1 = 44,
			Head = 45,
			HeadEnd = 46,
			Face = 47,
			Jaw = 48,
			LeftLowerLip = 49,
			LeftLowerInnerLip = 50,
			LowerLip = 51,
			LowerInnerLip = 52,
			RightLowerLip = 53,
			RightLowerInnerLip = 54,
			Tongue = 55,
			TongueTip = 56,
			Chin = 57,
			LeftLowCheek = 58,
			RightLowCheek = 59,
			LeftEye = 60,
			LeftIris = 61,
			RightEye = 62,
			RightIris = 63,
			LeftUpCheek = 64,
			LeftUpInnerCheek = 65,
			RightUpInnerCheek = 66,
			RightUpCheek = 67,
			LeftCheek = 68,
			RightCheek = 69,
			LeftMouth = 70,
			LeftInnerMouth = 71,
			LeftMiddleCrease = 72,
			LeftUpperLip = 73,
			LeftUpperInnerLip = 74,
			UpperLip = 75,
			UpperInnerLip = 76,
			RightUpperLip = 77,
			RightUpperInnerLip = 78,
			RightMouth = 79,
			RightInnerMouth = 80,
			RightMiddleCrease = 81,
			LeftUpEyelid = 82,
			RightUpEyelid = 83,
			LeftLowEyelid = 84,
			RightLowEyelid = 85,
			LeftInnerEyebrow = 86,
			LeftOuterEyebrow = 87,
			RightInnerEyebrow = 88,
			RightOuterEyebrow = 89,
			LeftNose = 90,
			RightNose = 91,
			LeftCrease = 92,
			RightCrease = 93,
			LeftLowMiddleEyebrow = 94,
			RightMiddleEyebrow = 95,
			LeftLowEyelidCrease = 96,
			LeftLowOuterEyebrow = 97,
			NoseTip = 98,
			RightLowOuterEyebrow = 99,
			LeftMiddleEyebrow = 100,
			RightLowMiddleEyebrow = 101,
			RightLowEyelidCrease = 102,
			LowNose = 103,
			HeadCloth = 104,
			Throat = 105,
			Spine2Phys1 = 106,
			Spine2Prop1 = 107,
			RightShoulder = 108,
			RightArm = 109,
			RightArmRoll = 110,
			RightForeArm = 111,
			RightForeArmRoll = 112,
			RightForeArmRoll1 = 113,
			RightHand = 114,
			RightHandMiddle0 = 115,
			RightHandMiddle1 = 116,
			RightHandMiddle2 = 117,
			RightHandMiddle3 = 118,
			RightHandMiddle4 = 119,
			RightHandRing0 = 120,
			RightHandRing1 = 121,
			RightHandRing2 = 122,
			RightHandRing3 = 123,
			RightHandRing4 = 124,
			RightHandPinky0 = 125,
			RightHandPinky1 = 126,
			RightHandPinky2 = 127,
			RightHandPinky3 = 128,
			RightHandPinky4 = 129,
			RightHandIndex0 = 130,
			RightHandIndex1 = 131,
			RightHandIndex2 = 132,
			RightHandIndex3 = 133,
			RightHandIndex4 = 134,
			RightHandThumb1 = 135,
			RightHandThumb2 = 136,
			RightHandThumb3 = 137,
			RightHandThumb4 = 138,
			RightHandProp1 = 139,
			RightElbowRoll = 140,
			RightArmCloth = 141,
			RightShoulderPhys1 = 142,
			Wep_Root = 143,
			Wep_Trigger = 144,
			Wep_Slide = 145,
			Wep_Grenade1 = 146,
			Wep_Grenade2 = 147,
			Wep_Mag = 148,
			Wep_Mag_Ammo = 149,
			Wep_Mag_Extra1 = 150,
			Wep_Scope1 = 151,
			Wep_Scope2 = 152,
			Wep_Belt1 = 153,
			Wep_Belt2 = 154,
			Wep_Belt3 = 155,
			Wep_Belt4 = 156,
			Wep_Belt5 = 157,
			Wep_Belt6 = 158,
			Wep_Belt7 = 159,
			Wep_Belt8 = 160,
			Wep_Belt9 = 161,
			Wep_Belt10 = 162,
			Wep_Bipod1 = 163,
			Wep_Bipod2 = 164,
			Wep_Bipod3 = 165,
			IK_Joint_LeftHand = 166,
			IK_Joint_RightHand = 167,
			Wep_Physic1 = 168,
			Wep_Physic2 = 169,
			Wep_Physic3 = 170,
			Wep_Physic4 = 171,
			Wep_Physic5 = 172,
			Wep_Extra1 = 173,
			Wep_Extra2 = 174,
			Wep_Extra3 = 175,
			Wep_Extra4 = 176,
			Wep_Extra5 = 177,
			Wep_Aim = 178,
			LeftSpine1Phys1 = 179,
			RightSpine1Phys1 = 180,
			LeftUpLeg = 181,
			LeftUpLegRoll = 182,
			LeftLeg = 183,
			LeftFoot = 184,
			LeftToeBase = 185,
			LeftToe = 186,
			LeftLegCloth = 187,
			LeftKneeRoll = 188,
			LeftHipsRoll = 189,
			LeftUpLegCloth = 190,
			HipsCloth = 191,
			LeftHipsFrontPhys = 192,
			LeftHipsBackPhys = 193,
			LeftHipsSidePhys = 194,
			RightUpLeg = 195,
			RightUpLegRoll = 196,
			RightLeg = 197,
			RightFoot = 198,
			RightToeBase = 199,
			RightToe = 200,
			RightLegCloth = 201,
			RightKneeRoll = 202,
			RightHipsRoll = 203,
			RightUpLegCloth = 204,
			RightHipsFrontPhys = 205,
			RightHipsBackPhys = 206,
			RightHipsSidePhys = 207,
			CameraBase = 208,
			CameraJoint = 209,
			Connect = 210,
			ConnectEnd = 211,
			FacePosesAnimation = 212
		};
		QuatTransform* m_LocalTransform; //0x0000 
		QuatTransform* m_WorldTransform; //0x0008 
		QuatTransform* m_Unk; //0x0010 
		QuatTransform* m_Unk1; //0x0018 
		QuatTransform* m_Unk2; //0x0020 
		QuatTransform* m_ActiveWorldTransforms; //0x0028 
		QuatTransform* m_ActiveLocalTransforms; //0x0030 
		__int32 m_Slot; //0x0038 
		__int32 m_ReaderIndex; //0x003C 
		unsigned char m_ValidTransforms; //0x0040 
		unsigned char m_PoseUpdateEnabled; //0x0041 
		unsigned char m_PoseNeeded; //0x0042 
		char _0x0043[1];
	};//Size=0x0044

	class RagdollComponent
	{
	public:

		char _0x0000[16];
		__int64 m_pData; //0x0010 
		char _0x0018[8];
		__int64 m_pEntry; //0x0020 
		char _0x0028[32];
		__int64 m_RagdollCompData; //0x0048 
		char _0x0050[8];
		AnimationSkeleton* m_AnimationSkeleton; //0x0058 
		char _0x0060[40];
		UpdatePoseResultData m_PoseResultData; //0x0088 
		char _0x00CC[56];

		bool GetBone(const UpdatePoseResultData::BONES BoneId, Vec4* BoneOut)
		{
			UpdatePoseResultData PoseResult = this->m_PoseResultData;

			if (PoseResult.m_ValidTransforms)
			{
				QuatTransform* pQuat = PoseResult.m_ActiveWorldTransforms;
				if (!IsValidPtr(pQuat))
					return false;

				Vec4 Bone = pQuat[BoneId].m_TransAndScale;

				BoneOut->x = Bone.x;
				BoneOut->z = Bone.z;

				BoneOut->y = Bone.y;
				return true;
			}
			return false;
		}
	};//Size=0x0104

	class ParachuteComponent
	{
	public:
		char _0x0000[64];

	};//Size=0x0040



	class VaultComponent
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class SoldierSuppressionComponent
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class HealthComponent
	{
	public:
		char _0x0000[0x20];
		float m_Health; //0x0020 
		float m_MaxHealth; //0x0024 
		char _0x0028[16];
		float m_VehicleHealth; //0x0038 

	};//Size=0x003C

	template <class T> class EntityIterator
	{
	public:
		class Element
		{
		public:

			Element* m_pFlink;
			Element* m_pBlink;
			__int32  m_Unk1;
			__int32  m_Unk2;

			T* getObject()
			{
				intptr_t pObject = reinterpret_cast<intptr_t>(this);
				pObject -= 0x40;

				return reinterpret_cast<T*>(pObject);
			}
		};

		Element* m_pFirst;
		Element* m_pCurrent;

		EntityIterator(void* pGameWorld, void* pClassInfo)
		{
			typedef Element* (__thiscall* tGetEntityList)(void* pClassInfo, void* pThis);
			tGetEntityList lpGetEntityList = reinterpret_cast<tGetEntityList>(OFFSET_GETENTITYLIST);

			this->m_pFirst = lpGetEntityList(pClassInfo, pGameWorld);
			this->m_pCurrent = this->m_pFirst;
		}

		bool hasNext()
		{
			if (m_pCurrent && m_pCurrent->m_pFlink)
				return true;

			return false;
		}

		Element* first() { return m_pFirst; }
		Element* front() { return m_pCurrent; }
		Element* next()
		{
			if (!m_pFirst)
				return nullptr;

			m_pCurrent = m_pCurrent->m_pFlink;

			return m_pCurrent;
		}
	};

	class WeaponShotModifier
	{
	public:
		char _0x0000[24];
		__int32 m_NumberOfBulletsPerShell; //0x0018
		char _0x001C[4];
		Vec4 m_InitialSpeed; //0x0020

	};//Size=0x002C

	class SoundModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class FiringEffectsModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class FiringDataModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class ProjectileModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class m_AimingSimulationModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class AimingSimulationModifier
	{
	public:
		char _0x0000[64];

	};//Size=0x0040

	class WeaponZeroingEntry
	{
	public:
		float m_ZeroDistance; //0x0000 
		float m_Angle; //0x0004 

		WeaponZeroingEntry(float Dist, float Angle)
		{
			m_ZeroDistance = Dist;
			m_Angle = Angle;
		}
	};//Size=0x0008

	class ZeroingModifier
	{
	public:
		char _0x0000[24];
		WeaponZeroingEntry* m_ppZeroLevels;
		float m_DefaultZeroingDistance; //0x0020 

		WeaponZeroingEntry GetZeroLevelAt(int index)
		{
			if (index > -1)
				return m_ppZeroLevels[index];
			else
				return WeaponZeroingEntry(m_DefaultZeroingDistance, 0.0f);
		}
	};//Size=0x0038

	class WeaponSway
	{
	public:
		char _0x0000[8];
		GunSwayData* m_Data; //0x0008 
	};//Size=0x0010

	class GunSwayData
	{
	public:
		char _0x0000[1072];
		float m_DeviationScaleFactorZoom;           // 0x430
		float m_GameplayDeviationScaleFactorZoom;   // FLOAT 
		float m_DeviationScaleFactorNoZoom;         // FLOAT 
		float m_GameplayDeviationScaleFactorNoZoom; // FLOAT 
		float m_ShootingRecoilDecreaseScale; //0x0440 
		float m_FirstShotRecoilMultiplier; //0x0444 
		__int64 m_CamerRecoilData; //0x0448 
	};//Size=0x0450

	class ClientSpottingTargetComponent
	{
	public:



		class SpottingTargetComponentData
		{
		public:
			char pad_0x0[0x70];
			float m_ActiveSpottedTime; //+0x70
			float m_PassiveSpottedTime; //+0x74
			float m_ActiveSpottedTimeMultiplier; //+0x78
			float m_PassiveSpottedTimeMultiplier;//+0x7C
			float m_SpotOnFireMultiplier; //+0x80
			float m_RadarSpottedSpeedThresholdOverride; //+0x84
			bool m_TargetBoundingBoxCenter; //+0x88
			bool m_CalculateAngleOutsideBoundingSphere; //+0x89
		};

		char _0x0[0x10];
		SpottingTargetComponentData* m_spottingTargetData; //0x10 
		char _0x18[0x38];
		SpotType activeSpotType; //0x50
	};

	class ClientSoldierAimingEnvironment
	{
	public:
		char _0x0000[8];
		ClientSoldierEntity* m_soldier; //0x0008 
	};//Size=0x0010
	class FOVTransitionData
	{
	public:
		enum FOVTransitionType
		{
			FOVTransitionType_Linear = 0,
			FOVTransitionType_Smooth = 1,
			FOVTransitionType_Count = 2,
		};

		char aDataContainer[16]; //+0x00 Inherited
		FOVTransitionType m_TransitionType; //+0x10
		float m_Shape; //+0x14
		float m_StartDelay; //+0x18
		float m_StartJump; //+0x1C    
		float m_EndEarly; //+0x20
		bool m_Invert; //+0x24
	};
	class ZoomLevelData
	{
	public:
		enum ZoomLevelActivateEventType
		{
			ZoomLevelActivateEventType_Disable = 0,
			ZoomLevelActivateEventType_Enable = 1,
			ZoomLevelActivateEventType_ToggleOnLightSwitch = 2,
		};
		char aDataContainer[16]; //+0x00 Inherited
		float m_FieldOfView; //+0x10
		float m_FieldOfViewSP; //+0x14
		FOVTransitionData m_FieldOfViewTransition; //+0x18
		float m_LookSpeedMultiplier; //+0x20
		float m_SprintLookSpeedMultiplier; //+0x24
		float m_MoveSpeedMultiplier; //+0x28
		float m_SwayPitchMagnitude; //+0x2C
		float m_SwayYawMagnitude; //+0x30
		float m_SupportedSwayPitchMagnitude; //+0x34
		float m_SupportedSwayYawMagnitude; //+0x38
		float m_SuppressedSwayPitchMagnitude; //+0x3C
		float m_SuppressedSwayYawMagnitude; //+0x40
		float m_SuppressedSwayMinFactor; //+0x44
		float m_TimePitchMultiplier; //+0x48
		float m_TimeYawMultiplier; //+0x4C
		float m_DispersionMultiplier; //+0x50
		float m_DispersionRotation; //+0x54
		float m_RecoilMultiplier; //+0x58
		float m_RecoilFovMultiplier; //+0x5C
		float m_CameraImpulseMultiplier; //+0x60
		float m_StartFadeToBlackAtTime; //+0x64
		float m_FadeToBlackDuration; //+0x68
		float m_StartFadeFromBlackAtTime; //+0x6C
		float m_FadeFromBlackDuration; //+0x70
		float m_ScreenExposureAreaScale; //+0x74
		ZoomLevelActivateEventType m_OnActivateEventType; //+0x78
		float m_AttractYawStrength; //+0x7C
		float m_AttractPitchStrength; //+0x80
		bool m_AllowFieldOfViewScaling; //+0x84
		bool m_FadeToBlackInZoomTransition; //+0x85
		bool m_UseFovSpecialisation; //+0x86
		bool m_UseWeaponMeshZoom1p; //+0x87
	};

	class AimingPoseData
	{
	public:
		float m_MinimumPitch; //+0x0
		float m_MaximumPitch; //+0x4
		float m_TargetingFov; //+0x8
		float m_AimSteadiness; //+0xC
		float m_SpeedMultiplier; //+0x10
		float m_RecoilMultiplier; //+0x14
	};

	class SoldierAimAssistData
	{
	public:
		char pad_0x00[0x10]; //+0x00
		__int64 m_InputPolynomial; //+0x10
		__int64 m_ZoomedInputPolynomial; //+0x18
		D3DXVECTOR3 m_StickyBoxScale; //+0x20
		D3DXVECTOR3 m_StickyDistanceScale; //+0x30
		D3DXVECTOR3 m_SnapBoxScale; //+0x40
		D3DXVECTOR3 m_SnapDistanceScale; //+0x50
		D3DXVECTOR3 m_EyePosOffset; //+0x60
		float m_AccelerationInputThreshold; //+0x70
		float m_AccelerationMultiplier; //+0x74
		float m_AccelerationDamping; //+0x78
		float m_AccelerationTimeThreshold; //+0x7C
		float m_SquaredAcceleration; //+0x80
		D3DXVECTOR2 m_MaxAcceleration; //+0x84
		float m_YawSpeedStrength; //+0x8C
		float m_PitchSpeedStrength; //+0x90
		D3DXVECTOR2 m_AttractDistanceFallOffs; //+0x94
		float m_AttractSoftZone; //+0x9C
		float m_AttractUserInputMultiplier; //+0xA0
		float m_AttractUserInputMultiplier_NoZoom; //+0xA4
		float m_AttractOwnSpeedInfluence; //+0xA8
		float m_AttractTargetSpeedInfluence; //+0xAC
		float m_AttractOwnRequiredMovementForMaximumAttract; //+0xB0
		float m_AttractStartInputThreshold; //+0xB4
		float m_AttractMoveInputCap; //+0xB8
		float m_AttractYawStrength; //+0xBC
		float m_AttractPitchStrength; //+0xC0
		float m_MaxToTargetAngle; //+0xC4
		float m_MaxToTargetXZAngle; //+0xC8
		float m_ViewObstructedKeepTime; //+0xCC
		float m_SnapZoomLateralSpeedLimit; //+0xD0
		float m_SnapZoomTime; //+0xD4
		float m_SnapZoomPostTimeNoInput; //+0xD8
		float m_SnapZoomPostTime; //+0xDC
		unsigned __int32 m_SnapZoomReticlePointPriority; //+0xE0
		float m_SnapZoomAutoEngageTime; //+0xE4
		float m_SnapZoomBreakTimeAtMaxInput; //+0xE8
		float m_SnapZoomBreakMaxInput; //+0xEC
		float m_SnapZoomBreakMinAngle; //+0xF0
		float m_SnapZoomSpamGuardTime; //+0xF4
		__int64 m_SoldierBackupSkeletonCollisionData; //+0xF8
		float m_CheckBoneCenterOnlyDistance; //+0x100
		float m_DisableForcedTargetRecalcDistance; //+0x104
		float m_OverrideAimingRange; //+0x108
		float m_OverrideAimingRangeCrouch; //+0x10C
		float m_OverrideAimingRangeProne; //+0x110
		bool m_UseYawAcceleration; //+0x114
		bool m_UsePitchAcceleration; //+0x115
		bool m_SnapZoomUserShorterWeaponTime; //+0x116
		bool m_SnapZoomPostTimeDynamicPoint; //+0x117
		bool m_ForceSoldierBackupSkeletonCollisionUse; //+0x118
	};
	class SoldierAimingSimulationData
	{
	public:
		char aGameDataContainer[16]; //+0x00 Inherited
		ZoomLevelData** m_ZoomLevels; //+0x10

		SoldierAimAssistData* m_AimAssist; //+0x18
		AimingPoseData m_StandPose; //+0x20
		AimingPoseData m_CrouchPose; //+0x38
		AimingPoseData m_PronePose; //+0x50
		float m_ZoomTransitionTime; //+0x68
		float m_ZoomTransitionTimeArray; //+0x70
		float m_FovDelayTime; //+0x78
		float m_FovTransitionTime; //+0x7C
		float m_AimingRange; //+0x80
		float m_LockAimToTargetSpeed; //+0x84
		float m_Modifiers; //+0x88
		bool m_ReturnToZoomAfterReload; //+0x90
		char _0x0091[7];
	};
	class LockingControllerData
	{
	public:
		char  a0111[0x10];
		void* m_ZoomLevelLock; //0x0010
		FLOAT m_LockTime; //0x0018
		FLOAT m_UnLockTime; //0x001C
		FLOAT m_ReleaseTime; //0x0020
		FLOAT m_ReleaseOnNewTargetTime; //0x0024
		FLOAT m_SampleRate; //0x0028
		FLOAT m_HoldStillThreshold; //0x002C
		FLOAT m_CheckVisibilityLength; //0x0030
		FLOAT m_RayLength; //0x0034
		FLOAT m_AcceptanceAngle; //0x0038
		FLOAT m_AngleConstant; //0x003C
		FLOAT m_DistanceConstant; //0x0040
		FLOAT m_Sensitivity; //0x0044
		FLOAT m_MinimumLockTime; //0x0048
		char m_LockingWeaponData[0xc]; //0x004C
		BYTE m_LockOnVisibleTargetsOnly; //0x0058
		BYTE m_RequireAmmoToLock; //0x0059
		BYTE m_PositionOnly; //0x005A
		BYTE m_LockOnWorldSpacePos; //0x005B
		BYTE m_LockOnEmptyVehicles; //0x005C
		BYTE m_LockOnCharacters; //0x005D
		BYTE m_IgnoreHeigthLockDistance; //0x005E
		BYTE m_LockInCombatAreaOnly; //0x005F
	};//Size=0x0060
	class MissileEntityData
	{
	public:


		char a[0x130];
		void* m_EngineEffect; //0x0130
		void* m_DudExplosion; //0x0138
		SoundAsset* m_FlyBySound; //0x0140
		FLOAT m_EngineStrength; //0x0148
		FLOAT m_MaxSpeed; //0x014C
		FLOAT m_EngineTimeToIgnition; //0x0150
		FLOAT m_EngineTimeToLive; //0x0154
		FLOAT m_TimeToActivateGuidingSystem; //0x0158
		FLOAT m_TimeToArm; //0x015C
		FLOAT m_MaxTurnAngle; //0x0160
		FLOAT m_MinTurnAngle; //0x0164
		FLOAT m_TurnAngleMultiplier; //0x0168
		FLOAT m_Drag; //0x016C
		FLOAT m_Gravity; //0x0170
		FLOAT m_FlyBySoundRadius; //0x0174
		FLOAT m_FlyBySoundSpeed; //0x0178
		FLOAT m_ImpactImpulse; //0x017C
		FLOAT m_Damage; //0x0180
		FLOAT m_DefaultTeam; //0x0184
		FLOAT m_WarnTarget; //0x0188
		char _0x018C[4];
		LockingControllerData* m_LockingController; //0x0190
		char m_LockableInfo[8]; //0x0198
		char m_UnguidedData[0x14]; //0x01A0
		char m_NearTargetDetonation[0x10]; //0x01B4
		FLOAT m_MaxBankAngle; //0x01C4
		FLOAT m_BankingSpeed; //0x01C8
		char _0x01CC[4];
		void* m_Icon; //0x01D0
		void* m_TargetIcon; //0x01D8
		void* m_TargetIconEnemy; //0x01E0
		FLOAT m_MinGhostFrequency; //0x01E8
		BYTE m_ApplyGravityWhenGuided; //0x01EC
		BYTE m_WarnOnPointingMissile; //0x01ED
		BYTE m_EnableBanking; //0x01EE
		char _0x01EF[1];
	};//Size=0x01F0
	class PlayerEntryComponentData
	{
	public:
		class AntEnumeration
		{
		public:
			char _0x000[0x24];
			int m_Value; //+0x24
		};
		char aEntryComponentData[240]; //+0x00 Inherited
		Vec4 m_AnimationAccelerationMultiplier; //+0xF0
		char* m_AntEntryIDStr; //+0x100
		AntEntryIdEnum m_AntEntryId; //+0x108
		AntEnumeration m_AntEntryEnumeration; //+0x110
	};
	class ClientPlayerEntryComponent
	{
	public:
		char _0x000[0x008];
		intptr_t m_pSomeComponentList;//0x008
		PlayerEntryComponentData* m_pPlayerEntryComponentData;//0x010;
		char _0x018[0x270 - 0x018];
		ClientPlayer* m_pClientPlayer; //0x270
	};//0x640
	class WeaponInfo
	{public:
		virtual void WorldTransfrom(D3DXMATRIX&);
		virtual void GetState(int&);
		virtual void AddWeaponFiringCallbcks(void*);
		virtual void RemoveWeaponFiringCallbcks(void*);
		virtual WeaponFiring* GetWeaponFiring();
		virtual ClientWeapon* GetWeapon();
		virtual bool ActiveInStance(int);
		virtual void* GetWeaponComponent();

		ClientWeaponComponent* m_pWeaponComponent; //0x0008

	};
#ifndef _ClientBoneComponent_
#define _ClientBoneComponent_
	class fb::ClientBoneComponent 
	{
		//public:
		//    static __inline unsigned int ClassId()
		//    {
		//        return 353;
		//    }

		char __0x0[0x38];
	};//Size=0x0038
#endif



	class ClientWeaponComponent
	{
	public:
		char _0x0000[0x10];
		WeaponComponentData* m_pComponentData; //0x0010
		char _0x0018[0x8];
		ClientPlayerEntryComponent* m_pPlayerEntry; //0x0020
		char _0x0028[0x28];
		DynamicPhysicsEntity* m_physicsEntity; //0x0050 Start of WeaponComponent
		char _0x0058[0x30];
		void* m_interpolationObject; //0x0088
		ClientWeapon* m_pWeapon; //0x0090
		void* m_pController; //0x0098 ClientWeaponComponentSimulation
		void* m_pReplicatedWeapon; //0x00A0 ClientWeaponComponentReplication
		void* m_pPredictedWeapon; //0x00A8 ClientWeaponComponentPrediction
		void* m_pLockingController; //0x00B0 ClientLockingController null
		void* m_pSecondaryLockingController; //0x00B8 ClientLockingController null
		ClientPlayer* m_pPlayer; //0x00C0
		WeaponInfo* m_pWeaponInfo; //0x00C8
		void** m_pWeaponFiringCallback; //0x00D0
		void* m_pWeaponMeshModel; //0x00D8 MeshModel null
		void* m_pFiringEntry; //0x00E0 ClientPlayerEntryComponent
		char _0x0098[0x18];
	}; //0x00B0

	class WeaponComponentData
	{
	public:
		char _0x0000[0x70];
		Vec4 m_ProjectileSpawnOffset; //0x0070
		Vec4 m_TargetPositionOverride; //0x0080
		void* m_WeaponMesh; //0x0090
		WeaponFiringData* m_WeaponFiring; //0x0098
		char* m_pDamageGiverName; //0x00A0
		void* m_AIData; //0x00A8
		void* m_CustomWeaponType; //0x00B0
		float m_ImpulseStrength; //0x00B8
		DWORD m_Classification; //0x00BC
		float m_ReloadTimeMultiplier; //0x00C0
		float m_DamageMultiplier; //0x00C4
		float m_ExplosionDamageMultiplier; //0x00C8
		float m_OverheatDropPerSecondMultiplier; //0x00CC
		float m_LockTimeMultiplier; //0x00D0
		float m_LockingAcceptanceAngleMultiplier; //0x00D4
		DWORD m_WeaponItemHash; //0x00D8
		bool m_SequentialFiring; //0x00DC
		char _0x00DD[0x3];
	}; //0x00E0



	

	class MainVarPtr
	{
	public:
		float m_float_1;                                  //+0x0  (= 500.f)  
		char a0x41[0x4];                            //+0x4  
		Vec4 m_playerPos;                          //+0x8  
		float m_float_2;                                  //+0x18 (= 200.f)  
		char a0x412[0x4];                                      //+0x1C  
		float m_body_yaw;                                 //+0x20 ? (Vehicles only)  
		float m_turret_yaw;                               //+0x24 ? (Vehicles only)  
		ClientPlayer*                    pPlayer;         //+0x28  
		ClientSoldierEntity*             pSoldier;        //+0x30  
		ClientVehicleEntity*             pVehicleEntry;   //+0x38 Only in vehicles at any seat, no gadgets  
		ClientSoldierWeaponsComponent*   pWeaponComp;     //+0x40  
		ClientSoldierWeapon*             pCSWeapon;       //+0x48 Current soldier ClientSoldierWeapon
		WeaponFiring*                    pWeaponFiring;   //+0x50 Current WeaponFiring, NULL in passenger seat.  
		ClientPlayerEntryComponent*      pEntryComp;      //+0x58 Current soldier\vehicle ClientPlayerEntryComponent  
		ClientCameraComponent*           pCurVehicleCam;  //+0x60 (Vehicles\Gadgets only, and not in passenger seat with weapon)  
		void*                            pSomeCameraInfo; //+0x68 (Vehicles\Gadgets only, and not in passenger seat with weapon)  
		char a418[0x8];                                          //+0x70  
		SM::Matrix  m_turretTransform;                    //+0x78 ? (Update in vehicles only)  
		SM::Matrix  m_cameraTransform;                    //+0xB8 ?   
		Vec4 m_cameraBodyDegree;                      //+0xF8 (x,y,z [0-360.f]);  
		bool m_bInitialized;                              //+0x108 (= 1 if we spawned on map at least once)  

	public:
		static MainVarPtr* Singleton()
		{
			return (MainVarPtr*)(OFFSET_TURRENT);
		}
	};
}

#endif