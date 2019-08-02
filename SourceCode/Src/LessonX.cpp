/////////////////////////////////////////////////////////////////////////////////
float angle[50];
float m,n,p,q;  //玩家坐标
float a[50],b[50];
int g_fCountTime;
int begin,con=1,judge;
int times_1,times_2;
int life1,life2;

const char t[50][10]={"house1","house2","house3","house4","door","m3","m4","m5","m6","m7","m8","m9","m10",
	"m11","m12","m13","m14","m15","m16","m17","m18","m19","m20","m21","m22","m23","m24","m25","boos1","boos2","boos3","boos4",};
const char  zhangai[50][10]={"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10",
	                       "s11","s12","s13","s14","s15","s16","s17","s18","s19","s20",
	                       "s21","s22","s23","s24","s25","s26","s27","s28","s29","s30",
	                       "s31","s32","s33",};
const char paodan[6][10]={"bullet1","rocket1","bullet2","rocket2","bullet3","laser",};
const char bianjie1[4][10]={"top","bottom","left","right",};
const char bianjie2[8][10]={"top1","bottom1","left1","right1","top2","bottom2","left2","right2",};
const char Human[4][10]={"human1","human2","human3","human4",};
const char Q[12][5]={"q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12",};
//
//
//

/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include <math.h>
#include "List.h"

#include "CommonAPI.h"
#include "LessonX.h"

////////////////////////////////////////////////////////////////////////////////

const	float	BULLET_SPEED	=	20.f;	// 子弹速度
const	float	ROCKET_SPEED	=	15.f;	// 火箭速度 
float	fSpeedX, fSpeedY;	// X和Y方向上速度
float	fPosX1, fPosY1;		// 精灵坐标


///
int			g_iGameState		=	1;		// 游戏状态，0 -- 游戏结束等待开始状态；1 -- 按下空格键开始，初始化游戏；2 -- 游戏进行中
///

float       g_mSpeedTop     =   0.f;        //地图移动速度
float       g_mSpeedBottom     =   0.f;
float       g_mSpeedLeft     =   0.f;
float       g_mSpeedRight     =   0.f;

float		g_fSpeedLeft1		=	0.f;  	// 左方向速度
float		g_fSpeedRight1		=	0.f;  	// 右
float		g_fSpeedTop1	=	0.f;  	// 上
float		g_fSpeedBottom1	=	0.f;  	// 下
//
float		g_fSpeedLeft2		=	0.f;  	// 左方向速度
float		g_fSpeedRight2		=	0.f;  	// 右
float		g_fSpeedTop2	=	0.f;  	// 上
float		g_fSpeedBottom2	=	0.f;  	// 下
//

const  float	WORLD_LEFT	     = 	-26.f;	// 游戏场景边界左值
const  float	WORLD_TOP	     = 	-22.f;	// 游戏场景边界左值
const  float	WORLD_RIGHT	 = 	26.f;		// 游戏场景边界左值
const  float	WORLD_BOTTOM  = 	22.f;		// 游戏场景边界左值

//************************链表***************************

//=====================函数声明=============================================
extern int			GList_GetListSize();
// 根据名字获取Sprite
extern SGameSprite	*GList_GetSpriteByName( const char *szName );	
// 根据索引获取Sprite，如果要遍历链表并删除其中的某个元素，请从后面往前面遍历(即索引初始化为链表大小然后递减)，否则必然出错
extern SGameSprite	*GList_GetSpriteByIndex( const int iIndex );	
// 添加一个Sprite到链表里
extern SpriteStruct *GList_AddSprite( SGameSprite *pSprite );	
// 根据名字删除Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
extern void	GList_DeleteSprite( const char *szName, bool bDeleteImage = true );	
// 根据指针删除Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
extern void	GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage = true );
// 删除所有Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
extern void	GList_DeleteAllSprite( bool bDeleteImage = true );	

//======================全局变量====================================
float		g_fVelocityLeft  	=	0.f;	// 控制飞机的上下左右速度
float		g_fVelocityRight  	=  0.f;
float		g_fVelocityUp	 	=	0.f;
float		g_fVelocityDown  	=  0.f;
float		g_fScreenLeft		=	0.f;    // 屏幕左边界值
float		g_fScreenRight	=	0.f;    // 右
float		g_fScreenTop		=	0.f;    // 上
float		g_fScreenBottom	=	0.f;    // 下
int g_iCreatedSpriteCount = 1;
bool g_bControlCanFire = true;//判断是否可以射子弹


struct pSprite
{
	char szName[MAX_NAME_LEN];			// 精灵的名字
	int iHp;								// Health Point生命值
	int iScore;							// 击毁本精灵可以获得的分数值
	int iDamage;							// 自身碰到敌方可以给敌方造成的伤害
	ESpriteType eSpriteType;				// 精灵的类型
	int iBulletType;				// 该子弹类型，通过该类型判断是不是受到伤害
	float fFireAfterCreate;					// 精灵被创建多长时间可以发射子弹
	float fBulletTime;						// 子弹1被发射的时间间隔
	float fBulletTime2;						//子弹2被发射的时间间隔
	float fBulletTime3;	
	float fFloatTime;						// 上下浮动的时间
	bool bFloatUp;						// 是否上下浮动
}g_ControlSprite,g_VerTemplate,g_Bullet1Template,g_VerTemplate1,g_Bullet1Template1,g_VerTemplate2,g_Bullet1Template2,g_VerTemplate3,g_Bullet1Template3,g_VerTemplate4,g_Bullet1Template4,g_VerTemplate5,g_Bullet1Template5,g_Bullet1Template7,g_VerTemplate6,g_VerTemplate7,g_VerTemplate8;

void InitTemplateData()
{
	// 我们控制的Control Sprite
	strcpy( g_ControlSprite.szName, "player1" );
	g_ControlSprite.iHp					=	CONTROL_MAX_HP;
	g_ControlSprite.iScore				=	0;
	g_ControlSprite.eSpriteType			=	SPRITE_CONTROL;
	g_ControlSprite.iBulletType			=	0;		// Unused
	g_ControlSprite.fFireAfterCreate		=	0.f;	// Unused
	g_ControlSprite.fBulletTime			=	2.f;	// 2秒发射一次子弹
	g_ControlSprite.fBulletTime2			=	0.f;	// Unused
	g_ControlSprite.bFloatUp			=	true;
//	敌方战机
	//g_VerTemplate.szName[0]			=	'\0';
	strcpy( g_VerTemplate.szName, "m20" );
	g_VerTemplate.iHp					=	100;	// 生命值100
	g_VerTemplate.iScore				=	50;		// 积分50
	g_VerTemplate.eSpriteType			=	SPRITE_VER;
	g_VerTemplate.iBulletType			=	0;		// Unused
	g_VerTemplate.fFireAfterCreate		=	1.f;	// 出生1s后开始发射子弹
	g_VerTemplate.fBulletTime			=	3.f;	// 3秒发射一次子弹
	g_VerTemplate.bFloatUp			=	true;
	//	子弹
	g_Bullet1Template.szName[0]		=	'\0';	
	//strcpy( g_Bullet1Template.szName, "bullet" );
	g_Bullet1Template.iHp				=	1;		// 生命值1
	g_Bullet1Template.iScore			=	10;		// 积分10
	g_Bullet1Template.iDamage			=	0;		// 伤害值由发射的Sprite决定
	g_Bullet1Template.eSpriteType		=	SPRITE_BULLET1;
	g_Bullet1Template.iBulletType		=	0;		// 类型由发射的Sprite决定
	g_Bullet1Template.fFireAfterCreate	=	0.f;	// Unused
	g_Bullet1Template.fBulletTime		=	0.0f;	// Unused
	g_Bullet1Template.fBulletTime2		=	0.f;	// Unused
	g_Bullet1Template.fFloatTime		=	0.f;	// 飞行中上下浮动控制
	g_Bullet1Template.bFloatUp			=	true;
}
//************************************************************************************************
// 创建普通类型子弹，iBulletType：0为自己发射的子弹，1为敌方发射的子弹；		Pos：发射坐标       //敌方坦克发射
SGameSprite *CreateBullet1( const int iBulletType, const float fPosX, const float fPosY)
{
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// 拷贝子弹数据模板内容，这样不需要一个一个单独赋值
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// 添加到列表管理
	GList_AddSprite( pSprite );
	// 克隆精灵的显示图片
	dCloneSprite( "bullet3", pSprite->szName );
	// 给予坐标及速度
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1是敌方子弹
	if( 1 == iBulletType )
	{
		// 固定速度
		dSpriteMoveTo( pSprite->szName, dGetSpritePositionX( "player1" ), dGetSpritePositionY( "player1"), 6.f, 0 );
		//dSetSpriteLinearVelocityX( pSprite->szName, -30.f );
	}
	
	// 设置世界边界限制，及碰撞模式为NULL,即自行处理
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}
////////////////////////////////////////////////////////////////////////
SGameSprite *CreateBullet3( const int iBulletType, const float fPosX, const float fPosY)
{
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// 拷贝子弹数据模板内容，这样不需要一个一个单独赋值
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// 添加到列表管理
	GList_AddSprite( pSprite );
	// 克隆精灵的显示图片
	dCloneSprite( "laser", pSprite->szName );
	// 给予坐标及速度
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1是敌方子弹
	if( 1 == iBulletType )
	{
		// 固定速度
		dSpriteMoveTo( pSprite->szName, dGetSpritePositionX( "player1" ), dGetSpritePositionY( "player1"), 6.f, 0 );
		//dSetSpriteLinearVelocityX( pSprite->szName, -30.f );
	}
	
	// 设置世界边界限制，及碰撞模式为NULL,即自行处理
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}
                                                                                        //Bullet对应敌方炮弹
////////////////////////////////////////////////////////////////////////
/******************************************************我方坦克发射函数*****************************************/
SGameSprite *CreateBullet2( const int iBulletType,const float fPosX, const float fPosY,const char *name ,const char *bullet_name)
{
	int iDir;//坦克朝向
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// 拷贝子弹数据模板内容，这样不需要一个一个单独赋值
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet1_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// 添加到列表管理
	GList_AddSprite( pSprite );
	// 克隆精灵的显示图片
	dCloneSprite( bullet_name, pSprite->szName );
	// 给予坐标及速度
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1是敌方子弹
	if( 1 == iBulletType )
	{
		// 固定速度
		 iDir= dGetSpriteRotation(name)/45;
		 switch(iDir)
{
case 0:
	
	fSpeedX = 0;
	fSpeedY =-BULLET_SPEED;
	break;
case 1:

	fSpeedX = BULLET_SPEED;
	fSpeedY = -BULLET_SPEED;		
	break;
case 2:

	fSpeedX = BULLET_SPEED;
	fSpeedY = 0;		
	break;
case 3:
	
	fSpeedX =  BULLET_SPEED;
	fSpeedY = BULLET_SPEED;	
	break;
case 4:

	fSpeedX = 0;
	fSpeedY =BULLET_SPEED;
	break;
case 5:

	fSpeedX = -BULLET_SPEED;
	fSpeedY =BULLET_SPEED;
	break;
case 6:
	
	fSpeedX = -BULLET_SPEED;
	fSpeedY = 0;
	break;
case 7:

	fSpeedX = -BULLET_SPEED;
	fSpeedY =-BULLET_SPEED;
	break;
}
		
          dSetSpriteRotation(pSprite->szName, iDir*45);
          dSetSpriteLinearVelocity(pSprite->szName, fSpeedX, fSpeedY);


	}
	
	// 设置世界边界限制，及碰撞模式为NULL,即自行处理
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}
                                                                                                                //Bullet1对应我方子弹
SGameSprite *CreateBullet4( const int iBulletType,const float fPosX, const float fPosY,const char *name ,const char *bullet_name)
{
	int iDir;//坦克朝向
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// 拷贝子弹数据模板内容，这样不需要一个一个单独赋值
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet2_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// 添加到列表管理
	GList_AddSprite( pSprite );
	// 克隆精灵的显示图片
	dCloneSprite( bullet_name, pSprite->szName );
	// 给予坐标及速度
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1是敌方子弹
	if( 1 == iBulletType )
	{
		// 固定速度
		 iDir= dGetSpriteRotation(name)/45;
		 switch(iDir)
{
case 0:
	
	fSpeedX = 0;
	fSpeedY =-BULLET_SPEED;
	break;
case 1:

	fSpeedX = BULLET_SPEED;
	fSpeedY = -BULLET_SPEED;		
	break;
case 2:

	fSpeedX = BULLET_SPEED;
	fSpeedY = 0;		
	break;
case 3:
	
	fSpeedX =  BULLET_SPEED;
	fSpeedY = BULLET_SPEED;	
	break;
case 4:

	fSpeedX = 0;
	fSpeedY =BULLET_SPEED;
	break;
case 5:

	fSpeedX = -BULLET_SPEED;
	fSpeedY =BULLET_SPEED;
	break;
case 6:
	
	fSpeedX = -BULLET_SPEED;
	fSpeedY = 0;
	break;
case 7:

	fSpeedX = -BULLET_SPEED;
	fSpeedY =-BULLET_SPEED;
	break;
}
		
          dSetSpriteRotation(pSprite->szName, iDir*45);
          dSetSpriteLinearVelocity(pSprite->szName, fSpeedX, fSpeedY);


	}
	
	// 设置世界边界限制，及碰撞模式为NULL,即自行处理
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}    //Bullet2对应炮弹
                                                                                                               //Bullet2对应我方炮弹
//=====================================================================
// 已经创建的Ver Sprite，每个游戏循环都执行此函数。进行子弹的发射等
void VerLoopTick( SGameSprite *pSprite, float fDeltaTime )
{
	pSprite->fFireAfterCreate -= fDeltaTime;
	if( pSprite->fFireAfterCreate <= 0.f )
	{
		// 子弹1的创建
		pSprite->fBulletTime -= fDeltaTime;
		if( pSprite->fBulletTime <= 0.f )
		{
			// 子弹时间固定，不需要随机
			pSprite->fBulletTime = g_VerTemplate.fBulletTime;
			CreateBullet1(1,dGetSpritePositionX(pSprite->szName), 								dGetSpritePositionY(pSprite->szName) );
		}
	}
}

//
void		GameInit();
void		GameRun( float fDeltaTime );
void		GameEnd();
void		dOnSpriteColSprite( const char *szSrcName, const char *szTarName );

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。


//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void	GameMainLoop( float	fDeltaTime )
{
	switch( g_iGameState )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			g_iGameState	=	2; // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else
			{
				// 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
				g_iGameState	=	0;
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}

//==============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void	GameInit()
{
	times_1=times_2=life1=life2=0;
	judge=0;

	dSetSpritePosition( "flash1", 0, 0 );
	dSetSpritePosition( "flash2", 0, 0 );
	dSetSpritePosition( "k3", -14.52, 12.432 );
	                                     //禁用或启用
	      dSetSpriteEnable( "flash3", 0);
	      dSetSpriteEnable( "bullet3", 1);


	//****************************太空战机链表实验*************************
	g_ControlSprite.iHp			=	CONTROL_MAX_HP;
	g_ControlSprite.iScore		=	0;
	g_ControlSprite.fBulletTime	=	3.f;
	InitTemplateData();
	g_bControlCanFire = false;
	///////////////////////////////////////////////////////////////////////设置接收还是发送碰撞
	
	 dSetSpriteCollisionActive( "player1", 1, 1 );
	 dSetSpriteCollisionActive( "player2", 1, 1 );
	 for(int i=0;i<4;i++)
		  dSetSpriteCollisionActive( Human[i], 1, 0 );
	 for(int j=14;j<28;j++)
		 dSetSpriteCollisionActive( t[j], 1, 1 );
	 for(int i=0;i<14;i++)
		 dSetSpriteCollisionActive( t[i], 0, 1 );
	 for(int i=28;i<50;i++)
		 dSetSpriteCollisionActive( t[i], 0, 1 );
	for(int i=0;i<50;i++)
	{ 
	dSetSpriteCollisionActive( zhangai[i], 0, 1 );
	}
	for(int i=0;i<6;i++)
		dSetSpriteCollisionActive( paodan[i], 1, 0 );
	for(int i=0;i<4;i++)
		dSetSpriteCollisionActive( bianjie1[i], 0, 1 );
	for(int i=0;i<8;i++)
		dSetSpriteCollisionActive( bianjie2[i], 0, 1 );

	/////////////////////////////////////////////////////////////////////////////

}


//========================================================================================
//

//
//=====================================================================

//==============================================================================
//
// 每局游戏进行中
void	GameRun( float fDeltaTime )
{
	g_fCountTime += fDeltaTime; 

	for(int i=0;i<32;i++)
	{a[i]=dGetSpritePositionX(t[i]); b[i]=dGetSpritePositionY(t[i]);}  //存储物体坐标



	//初始化射程圈
	dSetSpritePosition("top1",dGetSpritePositionX("player1"),dGetSpritePositionY("player1")-14.5);
	dSetSpritePosition("bottom1",dGetSpritePositionX("player1"),dGetSpritePositionY("player1")+14.5);
	dSetSpritePosition("left1",dGetSpritePositionX("player1")-14.5,dGetSpritePositionY("player1"));
	dSetSpritePosition("right1",dGetSpritePositionX("player1")+14.5,dGetSpritePositionY("player1"));


	dSetSpritePosition("top2",dGetSpritePositionX("player2"),dGetSpritePositionY("player2")-14.5);
	dSetSpritePosition("bottom2",dGetSpritePositionX("player2"),dGetSpritePositionY("player2")+14.5);
	dSetSpritePosition("left2",dGetSpritePositionX("player2")-14.5,dGetSpritePositionY("player2"));
	dSetSpritePosition("right2",dGetSpritePositionX("player2")+14.5,dGetSpritePositionY("player2"));


		  //设置地图移动
	
	m=dGetSpritePositionX("player1"); n=dGetSpritePositionY("player1");
	p=dGetSpritePositionX("player2"); q=dGetSpritePositionY("player2");

	if(p<=-27&&g_fSpeedLeft2==-6.f)  g_mSpeedRight=4.f;  else g_mSpeedRight=0.f;
	if(p>= 27&&g_fSpeedRight2==6.f)  g_mSpeedLeft=-4.f;  else g_mSpeedLeft=0.f;
	if(q<=-17&&g_fSpeedTop2==-6.f)   g_mSpeedBottom=4.f; else g_mSpeedBottom=0.f;
	if(q>= 17&&g_fSpeedBottom2==6.f) g_mSpeedTop=-4.f;   else g_mSpeedTop=0.f;


	if(m<=-27&&g_fSpeedLeft1==-6.f)  g_mSpeedRight=4.f;
	if(m>= 27&&g_fSpeedRight1==6.f)  g_mSpeedLeft=-4.f;
	if(n<=-17&&g_fSpeedTop1==-6.f)   g_mSpeedBottom=4.f;
	if(n>= 17&&g_fSpeedBottom1==6.f) g_mSpeedTop=-4.f;

	dSetSpriteLinearVelocity ("map", g_mSpeedLeft + g_mSpeedRight, g_mSpeedTop + g_mSpeedBottom);

	for(int i=0;i<50;i++)
		 dSetSpriteLinearVelocity (zhangai[i], dGetSpriteLinearVelocityX( "map" ) ,dGetSpriteLinearVelocityY( "map" ));

	//设置物体随地图移动
	for(int i=0;i<32;i++)
	   dSetSpriteLinearVelocity (t[i],  dGetSpriteLinearVelocityX( "map" ) ,dGetSpriteLinearVelocityY( "map" ));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	      	 dSetSpriteLinearVelocity ("left1", dGetSpriteLinearVelocityX("player1"), dGetSpriteLinearVelocityY("player1"));
         dSetSpriteLinearVelocity ("right1", dGetSpriteLinearVelocityX("player1"), dGetSpriteLinearVelocityY("player1"));
		 dSetSpriteLinearVelocity ("top1", dGetSpriteLinearVelocityX("player1"), dGetSpriteLinearVelocityY("player1"));
		 dSetSpriteLinearVelocity ("bottom1", dGetSpriteLinearVelocityX("player1"), dGetSpriteLinearVelocityY("player1"));

      		 dSetSpriteLinearVelocity ("left2", dGetSpriteLinearVelocityX("player2"), dGetSpriteLinearVelocityY("player2"));
         dSetSpriteLinearVelocity ("right2", dGetSpriteLinearVelocityX("player2"), dGetSpriteLinearVelocityY("player2"));
		 dSetSpriteLinearVelocity ("top2", dGetSpriteLinearVelocityX("player2"), dGetSpriteLinearVelocityY("player2"));
		 dSetSpriteLinearVelocity ("bottom2", dGetSpriteLinearVelocityX("player2"), dGetSpriteLinearVelocityY("player2"));
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//====================================================================================================

		 for(int i=3;i<26;i++)
	{
		  if(m-a[i+2]>3&&fabs(n-b[i+2])<3) angle[i]=0;        //精灵的旋转
	  if(m-a[i+2]>3&&n-b[i+2]>3) angle[i]=45;
	  if(fabs(m-a[i+2])<3&&n-b[i+2]>3) angle[i]=90;
	  if(a[i+2]-m>3&&n-b[i+2]>3) angle[i]=135;
	  if(a[i+2]-m>3&&fabs(n-b[i+2])<3) angle[i]=180;
	  if(a[i+2]-m>3&&b[i+2]-n>3) angle[i]=225;
	  if(fabs(m-a[i+2])<3&&b[i+2]-n>3) angle[i]=270;
	  if(m-a[i+2]>3&&b[i+2]-n>3) angle[i]=315;
	}
		 for(int i=5;i<28;i++)
	  dSetSpriteRotation( t[i],angle[i-2]-90);  //设置敌方单位旋转角度
	  

	//设置敌方可移动单位的移动

	if(begin) 
 {     for(int j=14;j<28;j++)
		 {
			  if(fabs(m-a[j])<=45&&fabs(n-b[j])<=45)
	              {
					  if(angle[j-2]==0) dSetSpriteLinearVelocity (t[j], 2, 0);
	                  if(angle[j-2]==45) dSetSpriteLinearVelocity (t[j], 2, 2);
	                  if(angle[j-2]==90) dSetSpriteLinearVelocity (t[j], 0, 2);
	                  if(angle[j-2]==135) dSetSpriteLinearVelocity (t[j], -2, 2);
                      if(angle[j-2]==180) dSetSpriteLinearVelocity (t[j], -2, 0);
                      if(angle[j-2]==225) dSetSpriteLinearVelocity (t[j], -2, -2);
                      if(angle[j-2]==270) dSetSpriteLinearVelocity (t[j], 0, -2);
	                  if(angle[j-2]==315) dSetSpriteLinearVelocity (t[j], 2, -2);}
		 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////敌方坦克打炮

g_bControlCanFire = true;
g_ControlSprite.fBulletTime -= fDeltaTime;
g_ControlSprite.fBulletTime3-= fDeltaTime;

if(g_ControlSprite.fBulletTime < 0 && g_bControlCanFire)
	            {
		             g_ControlSprite.fBulletTime = 5;
					 if(begin)
					    for(int i=5;i<32;i++)
						 {  if(fabs(m-a[i])<=45&&fabs(n-b[i])<=45)
						          if( dGetSpritePositionX( t[i])!=0|| dGetSpritePositionY(t[i])!=0)
		                             CreateBullet1( 1, dGetSpritePositionX( t[i]), dGetSpritePositionY(t[i] ));
					      }
					 
	              }
if(g_ControlSprite.fBulletTime < 0 && g_bControlCanFire)
	            {
		             g_ControlSprite.fBulletTime =3;
					 if(begin)
					    for(int i=28;i<32;i++)
						 {  if(fabs(m-a[i])<=45&&fabs(n-b[i])<=45)
		                     CreateBullet3( 1, dGetSpritePositionX( t[i]), dGetSpritePositionY(t[i] ) );
					      }
					 
	              }

 }
//////////////////胜利时
if(judge==4)
   {dSetSpriteEnable( "flash3", 1);dSetSpritePosition( "flash3",0, 0); dSetSpritePosition( "flash5",0, 0);judge=0;}



}
//==============================================================================
//
// 本局游戏结束
void	GameEnd()
{
}
//==========================================================================

//////////////////////////////////////////////////////////////////

///////////


// 引擎捕捉鼠标移动消息后，将调用到本函数
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// iAltPress iShiftPress iCtrlPress 分别为判断Shift，Alt，Ctrl当前是否也处于按下状态。比如可以判断Ctrl+E组合键
void dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{

	if(iKey==KEY_Z)
	{dSetSpritePosition( "k3", -14.520, 12.432 );con=1;}
	if(iKey==KEY_X)
	{dSetSpritePosition( "k3", -14.520, 17.498 );con=2;}
	if(iKey==KEY_C)
	{
		begin=1;
		if(con==1)
		    {dDeleteSprite("player2");for(int i=6;i<12;i++) dDeleteSprite(Q[i]);}
		dDeleteSprite("k3");
		dDeleteSprite("flash2");
		dPlaySound("2 00_00_05-00_02_26.ogg", 1, 1);
	}

//=============================================================================

///////////////////////////////////////////////////////////////////////////////////**
	
			if(iKey==KEY_G)     //按下G,发射子弹
				     {dPlaySound("paizi.ogg", 0, 1);
			          CreateBullet2( 1 ,dGetSpritePositionX( "player1"), dGetSpritePositionY("player1"),"player1","bullet1");}	   
			if(iKey==KEY_H)     //按下H,发射导弹
				{
					 dPlaySound("paizi.ogg", 0, 1);
			         CreateBullet4( 1 ,dGetSpritePositionX( "player1"), dGetSpritePositionY("player1"),"player1","rocket1");
		     	}
		if(con==2)
			{if(iKey==KEY_O)     //按下O,发射子弹
				{dPlaySound("paizi.ogg", 0, 1);
			     CreateBullet2( 1 ,dGetSpritePositionX( "player2"), dGetSpritePositionY("player2"),"player2","bullet2");}
			if(iKey==KEY_P)     //按下P,发射导弹
				{dPlaySound("paizi.ogg", 0, 1);
			     CreateBullet4( 1 ,dGetSpritePositionX( "player2"), dGetSpritePositionY("player2"),"player2","rocket2");  }   
			}

	    
	  	
///////////////////////////////////////////////////////////////////////////////**
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
		switch(iKey)
{

case KEY_W:	
		g_fSpeedTop1 = -6.f;
		break;
		
case KEY_A:
		g_fSpeedLeft1 = -6.f;
		break;
case KEY_S:	
		g_fSpeedBottom1 = 6.f;
		break;
case KEY_D:
		g_fSpeedRight1 = 6.f;
		break;
default:
break;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		switch(iKey)
{ 
case KEY_UP:	
	    g_fSpeedTop2 = -6.f;
		break;
		
case KEY_LEFT:
		g_fSpeedLeft2 = -6.f;
		break;
case KEY_DOWN:	
		g_fSpeedBottom2 = 6.f;
		break;
case KEY_RIGHT:
		g_fSpeedRight2 = 6.f;
		break;
default:
break;
}


  dSetSpriteLinearVelocity ("player1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
      dSetSpriteLinearVelocity ("top1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
      dSetSpriteLinearVelocity ("bottom1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
	  dSetSpriteLinearVelocity ("left1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
	  dSetSpriteLinearVelocity ("right1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);

  dSetSpriteLinearVelocity ("player2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
      dSetSpriteLinearVelocity ("top2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
      dSetSpriteLinearVelocity ("bottom2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
      dSetSpriteLinearVelocity ("left2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
	  dSetSpriteLinearVelocity ("right2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);


if(g_fSpeedTop1<0&&g_fSpeedRight1==0&&g_fSpeedLeft1==0) angle[1]=270;        //精灵的旋转
	  if(g_fSpeedTop1<0&&g_fSpeedRight1>0&&g_fSpeedLeft1==0) angle[1]=315;
	  if(g_fSpeedTop1<0&&g_fSpeedLeft1<0&&g_fSpeedRight1==0) angle[1]=225;
	  if(g_fSpeedBottom1>0&&g_fSpeedRight1==0&&g_fSpeedLeft1==0) angle[1]=90;
	  if(g_fSpeedBottom1>0&&g_fSpeedRight1>0&&g_fSpeedLeft1==0) angle[1]=45;
	  if(g_fSpeedBottom1>0&&g_fSpeedRight1==0&&g_fSpeedLeft1<0) angle[1]=135;
	  if(g_fSpeedLeft1<0&&g_fSpeedTop1==0&&g_fSpeedBottom1==0) angle[1]=180;
	  if(g_fSpeedRight1>0&&g_fSpeedTop1==0&&g_fSpeedBottom1==0) angle[1]=0;

/////////////////////////////////////////////////////////////////////////////////
	  if(g_fSpeedTop2<0&&g_fSpeedRight2==0&&g_fSpeedLeft2==0) angle[2]=270;
	  if(g_fSpeedTop2<0&&g_fSpeedRight2>0&&g_fSpeedLeft2==0) angle[2]=315;
	  if(g_fSpeedTop2<0&&g_fSpeedLeft2<0&&g_fSpeedRight2==0) angle[2]=225;
	  if(g_fSpeedBottom2>0&&g_fSpeedRight2==0&&g_fSpeedLeft2==0) angle[2]=90;
	  if(g_fSpeedBottom2>0&&g_fSpeedRight2>0&&g_fSpeedLeft2==0) angle[2]=45;
	  if(g_fSpeedBottom2>0&&g_fSpeedRight2==0&&g_fSpeedLeft2<0) angle[2]=135;
	  if(g_fSpeedLeft2<0&&g_fSpeedTop2==0&&g_fSpeedBottom2==0) angle[2]=180;
	  if(g_fSpeedRight2>0&&g_fSpeedTop2==0&&g_fSpeedBottom2==0) angle[2]=0;


      dSetSpriteRotation( "player1",angle[1]+90);
	  dSetSpriteRotation( "player2",angle[2]+90);
}



//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
void dOnKeyUp( const int iKey )
{
	// 可以在此添加游戏需要的响应函数
	switch(iKey)
{
	case KEY_W:		
		g_fSpeedTop1 = 0.f;
		break;
	case KEY_A:
		g_fSpeedLeft1 = 0.f;		
		break;
	case KEY_S:	
		g_fSpeedBottom1 = 0.f;
		break;
	case KEY_D:
		g_fSpeedRight1 = 0.f;		
		break;		
}
dSetSpriteLinearVelocity ("player1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
     dSetSpriteLinearVelocity ("top1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
     dSetSpriteLinearVelocity ("bottom1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
     dSetSpriteLinearVelocity ("left1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);
     dSetSpriteLinearVelocity ("right1", g_fSpeedLeft1 + g_fSpeedRight1, g_fSpeedTop1 + g_fSpeedBottom1);

if(g_fSpeedTop1+g_fSpeedBottom1>0&&g_fSpeedLeft1+g_fSpeedRight1==0) dSetSpriteRotation( "player1",180);
if(g_fSpeedTop1+g_fSpeedBottom1<0&&g_fSpeedLeft1+g_fSpeedRight1==0) dSetSpriteRotation( "player1",0);
if(g_fSpeedTop1+g_fSpeedBottom1==0&&g_fSpeedLeft1+g_fSpeedRight1>0) dSetSpriteRotation( "player1",90);
if(g_fSpeedTop1+g_fSpeedBottom1==0&&g_fSpeedLeft1+g_fSpeedRight1<0) dSetSpriteRotation( "player1",270);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
switch(iKey)
{
	case KEY_UP:		
		g_fSpeedTop2 = 0.f;
		break;
	case KEY_LEFT:
		g_fSpeedLeft2 = 0.f;		
		break;
	case KEY_DOWN:	
		g_fSpeedBottom2 = 0.f;
		break;
	case KEY_RIGHT:
		g_fSpeedRight2 = 0.f;		
		break;		
}
dSetSpriteLinearVelocity ("player2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
     dSetSpriteLinearVelocity ("top2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
     dSetSpriteLinearVelocity ("bottom2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
     dSetSpriteLinearVelocity ("left2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
	 dSetSpriteLinearVelocity ("right2", g_fSpeedLeft2 + g_fSpeedRight2, g_fSpeedTop2 + g_fSpeedBottom2);
    

if(g_fSpeedTop2+g_fSpeedBottom2>0&&g_fSpeedLeft2+g_fSpeedRight2==0) dSetSpriteRotation( "player2",180);
if(g_fSpeedTop2+g_fSpeedBottom2<0&&g_fSpeedLeft2+g_fSpeedRight2==0) dSetSpriteRotation( "player2",0);
if(g_fSpeedTop2+g_fSpeedBottom2==0&&g_fSpeedLeft2+g_fSpeedRight2>0) dSetSpriteRotation( "player2",90);
if(g_fSpeedTop2+g_fSpeedBottom2==0&&g_fSpeedLeft2+g_fSpeedRight2<0) dSetSpriteRotation( "player2",270);

}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{	
                                                                         ////////////////////玩家.敌探碰障碍物
	for(int i=0;i<50;i++)
	{   
		if(strstr(szTarName,zhangai[i])!=NULL && strstr(szSrcName,"player1")!=NULL) 
			{dSetSpriteLinearVelocity ("player1", 0, 0);
		    }


	     if(strstr(szTarName,zhangai[i])!=NULL && strstr(szSrcName,"player2")!=NULL) 
		 {dSetSpriteLinearVelocity ("player2", 0, 0);
		 }



		 for(int j=14;j<28;j++)
		  if(strstr(szTarName,zhangai[i])!=NULL && strstr(szSrcName,t[j])!=NULL)
			  dSetSpriteLinearVelocity (t[j], 0, 0);
	                                                                            
		
   } 
//////////////////////////////////////////////////////////////////////////////////////////////////我方炮弹碰到敌方
	for(int i=0;i<4;i++)
	  if(strstr(szTarName,t[i])!=NULL && strstr(szSrcName,"Bullet2")!=NULL) 
			{
				dSetSpritePosition( Human[i],  dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName));
				dSpriteMoveTo( Human[i], dGetSpritePositionX( "player1" ), dGetSpritePositionY( "player1"), 3.f, 0 );
				dPlayEffect( "boom2", 3 , dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName), 0 );dPlaySound("kaipao.ogg", 0, 1 );
				dDeleteSprite( szTarName ); dDeleteSprite( szSrcName ); 
	        }
    if((strstr(szTarName,"player1")!=NULL||strstr(szTarName,"player2")!=NULL)&& strstr(szSrcName,"human")!=NULL)
		dDeleteSprite( szSrcName );

  if(strstr(szTarName,"door")!=NULL && strstr(szSrcName,"Bullet2")!=NULL)
  { 
	  dPlayEffect( "boom2", 3 , dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName), 0 );dPlaySound("kaipao.ogg", 0, 1 );
	  dDeleteSprite( szTarName ); dDeleteSprite( szSrcName ); 
  }

	for(int i=5;i<28;i++)
     {
		 if(strstr(szTarName,t[i])!=NULL && strstr(szSrcName,"Bullet2")!=NULL) 
			{dDeleteSprite( szTarName );dDeleteSprite( szSrcName );  dPlayEffect( "boom1", 3 , a[i] , b[i] , 0 );dPlaySound("kaipao.ogg", 0, 1 );}
	     if(strstr(szTarName,t[i])!=NULL && strstr(szSrcName,"Bullet1")!=NULL) 
		 {
			 dDeleteSprite( szSrcName );times_1+=1;
			 if(times_1==3) {dPlayEffect( "boom1", 3 , dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName), 0 );dPlaySound("kaipao.ogg", 0, 1 );dDeleteSprite( szTarName );times_1=0;}
		 }
	}

	for(int i=28;i<32;i++)
	{
		 if(strstr(szTarName,t[i])!=NULL && strstr(szSrcName,"Bullet1")!=NULL) 
		 {
			 dDeleteSprite( szSrcName );times_1+=1;
			 if(times_1==50) {dDeleteSprite( szTarName ); dPlayEffect( "boom2", 3 , a[i] , b[i] , 0 );dPlaySound("kaipao.ogg", 0, 1 );times_1=0;judge+=1;}
		 }
		 if(strstr(szTarName,t[i])!=NULL && strstr(szSrcName,"Bullet2")!=NULL) 
		 {
			 dDeleteSprite( szSrcName ); dPlayEffect( "boom1", 3 , a[i] , b[i] , 0 );dPlaySound("kaipao.ogg", 0, 1 );times_2+=1;
			 if(times_2==15) {dDeleteSprite( szTarName ); dPlayEffect( "boom2", 3 , a[i] , b[i] , 0 );dPlaySound("kaipao.ogg", 0, 1 );times_2=0;judge+=1;}
		 }
	}
////////////////////////////////////***********************************************敌方炮弹碰到我方坦克and失败时
	if(strstr(szTarName,"player1")!=NULL && strstr(szSrcName,"Bullet"))
	   {
   
			dDeleteSprite( szSrcName );dDeleteSprite( Q[life1] );life1+=1;
           	if(life1==6)
			           { dDeleteSprite( "player1" );dDeleteSprite( szSrcName ); 
			             dPlayEffect( "boom1", 3 , dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName), 0 );dPlaySound("kaipao.ogg", 0, 1 );
						 if(con==2)
						     if(life2==6)      
						        {dSetSpriteEnable( "flash3", 1 );
						           dSetSpritePosition( "flash3",0, 0);
						        dSetSpritePosition( "flash4",0, 0);
							     dSetSpriteEnable( "bullet3", 0);}
							 else;
						 else
							 {dSetSpriteEnable( "flash3", 1 );
						           dSetSpritePosition( "flash3",0, 0);
						        dSetSpritePosition( "flash4",0, 0);
							     dSetSpriteEnable( "bullet3", 0);}

			               
			           }
	   }
	if(strstr(szTarName,"player2")!=NULL && strstr(szSrcName,"Bullet"))
	   {
   
			dDeleteSprite( szSrcName );dDeleteSprite( Q[life2+6] );life2+=1;
           	if(life2==6)
			           { dDeleteSprite( "player2" );dDeleteSprite( szSrcName ); 
			             dPlayEffect( "boom1", 3 , dGetSpritePositionX( szTarName),dGetSpritePositionY( szTarName), 0 );dPlaySound("kaipao.ogg", 0, 1 );
						 if(life1==6)
						       { dSetSpriteEnable( "flash3", 1 );
						          dSetSpritePosition( "flash3",0, 0);
						         dSetSpritePosition( "flash4",0, 0);
						        dSetSpriteEnable( "bullet3", 0);}
			            
			           }
	   }

//////////////////////////子弹碰即消失//////////////////////////////////////////////////////////
		if(strstr(szSrcName,"Bullet")!=NULL)  dDeleteSprite( szSrcName ); 
		if(strstr(szSrcName,"Bullet1")!=NULL)  dDeleteSprite( szSrcName ); 
		if(strstr(szSrcName,"Bullet2")!=NULL)  dDeleteSprite( szSrcName ); 
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// iColSide : 0 左边，1 右边，2 上边，3 下边
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}