#ifndef __OFFSETS__H_
#define __OFFSETS__H_

//Offsets 17.03.2017
#define OFFSET_ANGLES				0x1423b2ec0
#define OFFSET_WORLDRENDERSETTINGS   0x1426724a0 
#define OFFSET_DXRENDERER           0x142738080
#define OFFSET_MAIN  0x142364b78
#define OFFSET_GAMERENDERER				0x142672378 
#define OFFSET_CLIENTGAMECONTEXT     0x142670d80 
#define OFFSET_BORDERINPUTNODE  0x142671fb0 
#define OFFSET_SYNCEDBFSETTINGS  0x1423717C0
#define OFFSET_PPCURRENTWEAPONFIRING   0x1423B2EC8
#define OFFSET_TURRENT 0x1423B2E78
#define OFFSET_WEAPONFIRING_VTB 0x141D53F18

#define OFFSET_SERVERSOLDIERENTITY0 0x142311D88
#define OFFSET_SERVERSOLDIERENTITY1 0x14237f390
#define OFFSET_SERVERSOLDIERENTITY2 0x142724688
		

//old

#define OFFSET_FIRSTTYPEINFO 0x14221f4a8
#define OFFSET_GETENTITYLIST 0x1407b54d0


#define OFFSET_ANTVTABLE 0x141D48670 



#define CLASSINFO_CLIENTGRENADEENTITY        0x1428693B0 
#define CLASSINFO_CLIENTEXPLOSIONENTITY        0x1428694F0 
#define CLASSINFO_CLIENTPICKUPENTITY        0x142868950 
#define CLASSINFO_CLIENTINTERATIONENTITY    0x1427A1F40 
#define ClASSINFO_CLIENTSUPPLERSPHEREENTITY 0x142869130 
#define CLASSINFO_VENICECLIENTMISSILEENTITY 0x1427A0E70 
#define CLASSINFO_CLIENTBULLETENTITY        0x1427A10F0 
#define CLASSINFO_PICKUPENTITY                0x142868950 
#define CLASSINFO_STATIC_MODEL                0x142816450 
#define DEPLOYED                            0x1421D842E  
#define CALCU_VEC_FORWARD					0x14098CD30

#endif



/*thispointer for ClientPlayerScoreManager:
Code:
*(ClientPlayerScoreManager**)((*(DWORD*)0x023BD8AC)+0x40)	*/
//0073E071 addy in ida
//007E2A60 addy in ida									     0x400000
//offset call in func from ida 20C9CEC this maybe it at addy 0x00BE5A65  


/*
//not working
#define OFFSET_GETCLIENTPLAYERSCORE		0x11566A0//0x11566A0 // 0x00AF0508;//0x0A115F0;

// all old Working Offsets for Armored Kill
#define BF3_MP							"bf3.exe"
#define BF3_MP_BASE						0x400000
#define BF3_MP_SIZE						0x2053000
#define OFFSET_MAIN						0x22B67C0
#define OFFSET_CLIENTGAMECONTEXT		0x233FC74
#define OFFSET_GAMERENDERER				0x2343A44
#define OFFSET_DXRENDERER				0x2323D94
//										002B8610 -> update matrices
//										00752B70 -> visual update clientcomp
									  //0x00400000
									  //0x0207AA08
#define MINIMAP			0x6FBCA0//0x0040D9AE
#define OFFSET_VISUALUPDATE				0x01152B70 //seg000:00B52B70 fb__ClientComponent__visualUpdate
#define OFFSET_UPDATEMATRICES			0x6B8610
#define OFFSET_UPDATEBONES				0xC32BE0
#define OFFSET_BORDERINPUTNODE			0x2343A80
#define OFFSET_GIVEDAMAGE				0x99F800
#define OFFSET_DBGRENDERER2				0x04B28E0
#define OFFSET_DBGRENDRAWTEXT			0x004B7070
#define OFFSET_DBGRENDRAW2DLINE			0x004B92D0
#define OFFSET_DBGRENDRAWRECTLINE		0x004B9BA0
#define OFFSET_DBGRENDRAWRECT			0x004B9DB0
#define	OFFSET_DBGRENDRAWSPHERE			0x004B7240
#define	OFFSET_DBGRENDRAWTRIANGLE		0x004B9AE0
//my simple blocker
#define OFFSET_BLOCKSCREENSHOT			0x2380EE0
//zoomgods blocker of addy2380EE0
#define OFFSET_PBRECEIVESS				0x2334418

#define OFFSET_SCREENPROJECT            0x0947090
#define OFFSET_PLAYERSCOREMANAGER		0x20C9CEC
#define OFFSET_CLIENTSCOREMANAGER		0x023BD8AC +0x40
#define OFFSET_GETRECOILVTABLE			0x209BA34
 sub_7638F0+31p

 #define OFFSET_SCREENPROJECT            0x0947090
 #define OFFSET_UPDATEBONES                0x0C32BE0

 GetRecoil 0x008C73A0
GetRecoil RDATA Reference 0x0209BA34


  add     edi, 4
seg000:000136EC                 cmp     edi, ebx
seg000:000136EE                 jnz     short loc_136E0
*/
