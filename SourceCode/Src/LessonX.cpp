/////////////////////////////////////////////////////////////////////////////////
float angle[50];
float m,n,p,q;  //�������
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

const	float	BULLET_SPEED	=	20.f;	// �ӵ��ٶ�
const	float	ROCKET_SPEED	=	15.f;	// ����ٶ� 
float	fSpeedX, fSpeedY;	// X��Y�������ٶ�
float	fPosX1, fPosY1;		// ��������


///
int			g_iGameState		=	1;		// ��Ϸ״̬��0 -- ��Ϸ�����ȴ���ʼ״̬��1 -- ���¿ո����ʼ����ʼ����Ϸ��2 -- ��Ϸ������
///

float       g_mSpeedTop     =   0.f;        //��ͼ�ƶ��ٶ�
float       g_mSpeedBottom     =   0.f;
float       g_mSpeedLeft     =   0.f;
float       g_mSpeedRight     =   0.f;

float		g_fSpeedLeft1		=	0.f;  	// �����ٶ�
float		g_fSpeedRight1		=	0.f;  	// ��
float		g_fSpeedTop1	=	0.f;  	// ��
float		g_fSpeedBottom1	=	0.f;  	// ��
//
float		g_fSpeedLeft2		=	0.f;  	// �����ٶ�
float		g_fSpeedRight2		=	0.f;  	// ��
float		g_fSpeedTop2	=	0.f;  	// ��
float		g_fSpeedBottom2	=	0.f;  	// ��
//

const  float	WORLD_LEFT	     = 	-26.f;	// ��Ϸ�����߽���ֵ
const  float	WORLD_TOP	     = 	-22.f;	// ��Ϸ�����߽���ֵ
const  float	WORLD_RIGHT	 = 	26.f;		// ��Ϸ�����߽���ֵ
const  float	WORLD_BOTTOM  = 	22.f;		// ��Ϸ�����߽���ֵ

//************************����***************************

//=====================��������=============================================
extern int			GList_GetListSize();
// �������ֻ�ȡSprite
extern SGameSprite	*GList_GetSpriteByName( const char *szName );	
// ����������ȡSprite�����Ҫ��������ɾ�����е�ĳ��Ԫ�أ���Ӻ�����ǰ�����(��������ʼ��Ϊ�����СȻ��ݼ�)�������Ȼ����
extern SGameSprite	*GList_GetSpriteByIndex( const int iIndex );	
// ���һ��Sprite��������
extern SpriteStruct *GList_AddSprite( SGameSprite *pSprite );	
// ��������ɾ��Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
extern void	GList_DeleteSprite( const char *szName, bool bDeleteImage = true );	
// ����ָ��ɾ��Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
extern void	GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage = true );
// ɾ������Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
extern void	GList_DeleteAllSprite( bool bDeleteImage = true );	

//======================ȫ�ֱ���====================================
float		g_fVelocityLeft  	=	0.f;	// ���Ʒɻ������������ٶ�
float		g_fVelocityRight  	=  0.f;
float		g_fVelocityUp	 	=	0.f;
float		g_fVelocityDown  	=  0.f;
float		g_fScreenLeft		=	0.f;    // ��Ļ��߽�ֵ
float		g_fScreenRight	=	0.f;    // ��
float		g_fScreenTop		=	0.f;    // ��
float		g_fScreenBottom	=	0.f;    // ��
int g_iCreatedSpriteCount = 1;
bool g_bControlCanFire = true;//�ж��Ƿ�������ӵ�


struct pSprite
{
	char szName[MAX_NAME_LEN];			// ���������
	int iHp;								// Health Point����ֵ
	int iScore;							// ���ٱ�������Ի�õķ���ֵ
	int iDamage;							// ���������з����Ը��з���ɵ��˺�
	ESpriteType eSpriteType;				// ���������
	int iBulletType;				// ���ӵ����ͣ�ͨ���������ж��ǲ����ܵ��˺�
	float fFireAfterCreate;					// ���鱻�����೤ʱ����Է����ӵ�
	float fBulletTime;						// �ӵ�1�������ʱ����
	float fBulletTime2;						//�ӵ�2�������ʱ����
	float fBulletTime3;	
	float fFloatTime;						// ���¸�����ʱ��
	bool bFloatUp;						// �Ƿ����¸���
}g_ControlSprite,g_VerTemplate,g_Bullet1Template,g_VerTemplate1,g_Bullet1Template1,g_VerTemplate2,g_Bullet1Template2,g_VerTemplate3,g_Bullet1Template3,g_VerTemplate4,g_Bullet1Template4,g_VerTemplate5,g_Bullet1Template5,g_Bullet1Template7,g_VerTemplate6,g_VerTemplate7,g_VerTemplate8;

void InitTemplateData()
{
	// ���ǿ��Ƶ�Control Sprite
	strcpy( g_ControlSprite.szName, "player1" );
	g_ControlSprite.iHp					=	CONTROL_MAX_HP;
	g_ControlSprite.iScore				=	0;
	g_ControlSprite.eSpriteType			=	SPRITE_CONTROL;
	g_ControlSprite.iBulletType			=	0;		// Unused
	g_ControlSprite.fFireAfterCreate		=	0.f;	// Unused
	g_ControlSprite.fBulletTime			=	2.f;	// 2�뷢��һ���ӵ�
	g_ControlSprite.fBulletTime2			=	0.f;	// Unused
	g_ControlSprite.bFloatUp			=	true;
//	�з�ս��
	//g_VerTemplate.szName[0]			=	'\0';
	strcpy( g_VerTemplate.szName, "m20" );
	g_VerTemplate.iHp					=	100;	// ����ֵ100
	g_VerTemplate.iScore				=	50;		// ����50
	g_VerTemplate.eSpriteType			=	SPRITE_VER;
	g_VerTemplate.iBulletType			=	0;		// Unused
	g_VerTemplate.fFireAfterCreate		=	1.f;	// ����1s��ʼ�����ӵ�
	g_VerTemplate.fBulletTime			=	3.f;	// 3�뷢��һ���ӵ�
	g_VerTemplate.bFloatUp			=	true;
	//	�ӵ�
	g_Bullet1Template.szName[0]		=	'\0';	
	//strcpy( g_Bullet1Template.szName, "bullet" );
	g_Bullet1Template.iHp				=	1;		// ����ֵ1
	g_Bullet1Template.iScore			=	10;		// ����10
	g_Bullet1Template.iDamage			=	0;		// �˺�ֵ�ɷ����Sprite����
	g_Bullet1Template.eSpriteType		=	SPRITE_BULLET1;
	g_Bullet1Template.iBulletType		=	0;		// �����ɷ����Sprite����
	g_Bullet1Template.fFireAfterCreate	=	0.f;	// Unused
	g_Bullet1Template.fBulletTime		=	0.0f;	// Unused
	g_Bullet1Template.fBulletTime2		=	0.f;	// Unused
	g_Bullet1Template.fFloatTime		=	0.f;	// ���������¸�������
	g_Bullet1Template.bFloatUp			=	true;
}
//************************************************************************************************
// ������ͨ�����ӵ���iBulletType��0Ϊ�Լ�������ӵ���1Ϊ�з�������ӵ���		Pos����������       //�з�̹�˷���
SGameSprite *CreateBullet1( const int iBulletType, const float fPosX, const float fPosY)
{
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// �����ӵ�����ģ�����ݣ���������Ҫһ��һ��������ֵ
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// ��ӵ��б����
	GList_AddSprite( pSprite );
	// ��¡�������ʾͼƬ
	dCloneSprite( "bullet3", pSprite->szName );
	// �������꼰�ٶ�
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1�ǵз��ӵ�
	if( 1 == iBulletType )
	{
		// �̶��ٶ�
		dSpriteMoveTo( pSprite->szName, dGetSpritePositionX( "player1" ), dGetSpritePositionY( "player1"), 6.f, 0 );
		//dSetSpriteLinearVelocityX( pSprite->szName, -30.f );
	}
	
	// ��������߽����ƣ�����ײģʽΪNULL,�����д���
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
	// �����ӵ�����ģ�����ݣ���������Ҫһ��һ��������ֵ
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// ��ӵ��б����
	GList_AddSprite( pSprite );
	// ��¡�������ʾͼƬ
	dCloneSprite( "laser", pSprite->szName );
	// �������꼰�ٶ�
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1�ǵз��ӵ�
	if( 1 == iBulletType )
	{
		// �̶��ٶ�
		dSpriteMoveTo( pSprite->szName, dGetSpritePositionX( "player1" ), dGetSpritePositionY( "player1"), 6.f, 0 );
		//dSetSpriteLinearVelocityX( pSprite->szName, -30.f );
	}
	
	// ��������߽����ƣ�����ײģʽΪNULL,�����д���
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}
                                                                                        //Bullet��Ӧ�з��ڵ�
////////////////////////////////////////////////////////////////////////
/******************************************************�ҷ�̹�˷��亯��*****************************************/
SGameSprite *CreateBullet2( const int iBulletType,const float fPosX, const float fPosY,const char *name ,const char *bullet_name)
{
	int iDir;//̹�˳���
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// �����ӵ�����ģ�����ݣ���������Ҫһ��һ��������ֵ
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet1_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// ��ӵ��б����
	GList_AddSprite( pSprite );
	// ��¡�������ʾͼƬ
	dCloneSprite( bullet_name, pSprite->szName );
	// �������꼰�ٶ�
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1�ǵз��ӵ�
	if( 1 == iBulletType )
	{
		// �̶��ٶ�
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
	
	// ��������߽����ƣ�����ײģʽΪNULL,�����д���
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}
                                                                                                                //Bullet1��Ӧ�ҷ��ӵ�
SGameSprite *CreateBullet4( const int iBulletType,const float fPosX, const float fPosY,const char *name ,const char *bullet_name)
{
	int iDir;//̹�˳���
	SGameSprite	*pSprite	=	(SGameSprite*)malloc( sizeof(SGameSprite) );
	// �����ӵ�����ģ�����ݣ���������Ҫһ��һ��������ֵ
	memcpy( pSprite, &g_Bullet1Template1, sizeof(SGameSprite) );
	sprintf( pSprite->szName, "Bullet2_%d", g_iCreatedSpriteCount++ );
	pSprite->iDamage		=	BULLET_DAMAGE_1;
	pSprite->iBulletType	=	iBulletType;
	// ��ӵ��б����
	GList_AddSprite( pSprite );
	// ��¡�������ʾͼƬ
	dCloneSprite( bullet_name, pSprite->szName );
	// �������꼰�ٶ�
	dSetSpritePosition( pSprite->szName, fPosX, fPosY );
	//1�ǵз��ӵ�
	if( 1 == iBulletType )
	{
		// �̶��ٶ�
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
	
	// ��������߽����ƣ�����ײģʽΪNULL,�����д���
	g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
	dSetSpriteWorldLimit(pSprite->szName, WORLD_LIMIT_NULL, g_fScreenLeft, g_fScreenTop, g_fScreenRight, g_fScreenBottom);
	//dSetSpriteWorldLimit( pSprite->szName, WORLD_LIMIT_NULL, g_fWorldLeft, 				g_fWorldTop, g_fWorldRight, g_fWorldBottom );
	free(pSprite->szName);
	return pSprite;
}    //Bullet2��Ӧ�ڵ�
                                                                                                               //Bullet2��Ӧ�ҷ��ڵ�
//=====================================================================
// �Ѿ�������Ver Sprite��ÿ����Ϸѭ����ִ�д˺����������ӵ��ķ����
void VerLoopTick( SGameSprite *pSprite, float fDeltaTime )
{
	pSprite->fFireAfterCreate -= fDeltaTime;
	if( pSprite->fFireAfterCreate <= 0.f )
	{
		// �ӵ�1�Ĵ���
		pSprite->fBulletTime -= fDeltaTime;
		if( pSprite->fBulletTime <= 0.f )
		{
			// �ӵ�ʱ��̶�������Ҫ���
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
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�


//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void	GameMainLoop( float	fDeltaTime )
{
	switch( g_iGameState )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			g_iGameState	=	2; // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else
			{
				// ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
				g_iGameState	=	0;
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}

//==============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void	GameInit()
{
	times_1=times_2=life1=life2=0;
	judge=0;

	dSetSpritePosition( "flash1", 0, 0 );
	dSetSpritePosition( "flash2", 0, 0 );
	dSetSpritePosition( "k3", -14.52, 12.432 );
	                                     //���û�����
	      dSetSpriteEnable( "flash3", 0);
	      dSetSpriteEnable( "bullet3", 1);


	//****************************̫��ս������ʵ��*************************
	g_ControlSprite.iHp			=	CONTROL_MAX_HP;
	g_ControlSprite.iScore		=	0;
	g_ControlSprite.fBulletTime	=	3.f;
	InitTemplateData();
	g_bControlCanFire = false;
	///////////////////////////////////////////////////////////////////////���ý��ջ��Ƿ�����ײ
	
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
// ÿ����Ϸ������
void	GameRun( float fDeltaTime )
{
	g_fCountTime += fDeltaTime; 

	for(int i=0;i<32;i++)
	{a[i]=dGetSpritePositionX(t[i]); b[i]=dGetSpritePositionY(t[i]);}  //�洢��������



	//��ʼ�����Ȧ
	dSetSpritePosition("top1",dGetSpritePositionX("player1"),dGetSpritePositionY("player1")-14.5);
	dSetSpritePosition("bottom1",dGetSpritePositionX("player1"),dGetSpritePositionY("player1")+14.5);
	dSetSpritePosition("left1",dGetSpritePositionX("player1")-14.5,dGetSpritePositionY("player1"));
	dSetSpritePosition("right1",dGetSpritePositionX("player1")+14.5,dGetSpritePositionY("player1"));


	dSetSpritePosition("top2",dGetSpritePositionX("player2"),dGetSpritePositionY("player2")-14.5);
	dSetSpritePosition("bottom2",dGetSpritePositionX("player2"),dGetSpritePositionY("player2")+14.5);
	dSetSpritePosition("left2",dGetSpritePositionX("player2")-14.5,dGetSpritePositionY("player2"));
	dSetSpritePosition("right2",dGetSpritePositionX("player2")+14.5,dGetSpritePositionY("player2"));


		  //���õ�ͼ�ƶ�
	
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

	//�����������ͼ�ƶ�
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
		  if(m-a[i+2]>3&&fabs(n-b[i+2])<3) angle[i]=0;        //�������ת
	  if(m-a[i+2]>3&&n-b[i+2]>3) angle[i]=45;
	  if(fabs(m-a[i+2])<3&&n-b[i+2]>3) angle[i]=90;
	  if(a[i+2]-m>3&&n-b[i+2]>3) angle[i]=135;
	  if(a[i+2]-m>3&&fabs(n-b[i+2])<3) angle[i]=180;
	  if(a[i+2]-m>3&&b[i+2]-n>3) angle[i]=225;
	  if(fabs(m-a[i+2])<3&&b[i+2]-n>3) angle[i]=270;
	  if(m-a[i+2]>3&&b[i+2]-n>3) angle[i]=315;
	}
		 for(int i=5;i<28;i++)
	  dSetSpriteRotation( t[i],angle[i-2]-90);  //���õз���λ��ת�Ƕ�
	  

	//���õз����ƶ���λ���ƶ�

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�з�̹�˴���

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
//////////////////ʤ��ʱ
if(judge==4)
   {dSetSpriteEnable( "flash3", 1);dSetSpritePosition( "flash3",0, 0); dSetSpritePosition( "flash5",0, 0);judge=0;}



}
//==============================================================================
//
// ������Ϸ����
void	GameEnd()
{
}
//==========================================================================

//////////////////////////////////////////////////////////////////

///////////


// ���沶׽����ƶ���Ϣ�󣬽����õ�������
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// iAltPress iShiftPress iCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
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
	
			if(iKey==KEY_G)     //����G,�����ӵ�
				     {dPlaySound("paizi.ogg", 0, 1);
			          CreateBullet2( 1 ,dGetSpritePositionX( "player1"), dGetSpritePositionY("player1"),"player1","bullet1");}	   
			if(iKey==KEY_H)     //����H,���䵼��
				{
					 dPlaySound("paizi.ogg", 0, 1);
			         CreateBullet4( 1 ,dGetSpritePositionX( "player1"), dGetSpritePositionY("player1"),"player1","rocket1");
		     	}
		if(con==2)
			{if(iKey==KEY_O)     //����O,�����ӵ�
				{dPlaySound("paizi.ogg", 0, 1);
			     CreateBullet2( 1 ,dGetSpritePositionX( "player2"), dGetSpritePositionY("player2"),"player2","bullet2");}
			if(iKey==KEY_P)     //����P,���䵼��
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


if(g_fSpeedTop1<0&&g_fSpeedRight1==0&&g_fSpeedLeft1==0) angle[1]=270;        //�������ת
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
// ���沶׽���̵�����Ϣ�󣬽����õ�������
void dOnKeyUp( const int iKey )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
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
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{	
                                                                         ////////////////////���.��̽���ϰ���
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
//////////////////////////////////////////////////////////////////////////////////////////////////�ҷ��ڵ������з�
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
////////////////////////////////////***********************************************�з��ڵ������ҷ�̹��andʧ��ʱ
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

//////////////////////////�ӵ�������ʧ//////////////////////////////////////////////////////////
		if(strstr(szSrcName,"Bullet")!=NULL)  dDeleteSprite( szSrcName ); 
		if(strstr(szSrcName,"Bullet1")!=NULL)  dDeleteSprite( szSrcName ); 
		if(strstr(szSrcName,"Bullet2")!=NULL)  dDeleteSprite( szSrcName ); 
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}