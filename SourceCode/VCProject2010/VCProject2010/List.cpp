#include"LessonX.h"
#include "List.h"
#include <stdio.h>
extern int			GList_GetListSize();
// �������ֻ�ȡSprite
SGameSprite	*GList_GetSpriteByName( const char *szName );	
// ����������ȡSprite�����Ҫ��������ɾ�����е�ĳ��Ԫ�أ���Ӻ�����ǰ�����(��������ʼ��Ϊ�����СȻ��ݼ�)�������Ȼ����
 SGameSprite	*GList_GetSpriteByIndex( const int iIndex );	
// ���һ��Sprite��������
 SpriteStruct	*GList_AddSprite( SGameSprite *pSprite );	
// ��������ɾ��Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
void	GList_DeleteSprite( const char *szName, bool bDeleteImage = true );	
// ����ָ��ɾ��Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
void	GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage = true );
// ɾ������Sprite. bDeleteImage : �Ƿ�ɾ����Sprite�ڵ�ͼ�ϵ�ͼƬ��ʾ
void	GList_DeleteAllSprite( bool bDeleteImage = true );	

//=============================================================
SpriteStruct	*g_pListHeader	=	NULL;
int	g_iListSize  =	 0;					
// ����Ԫ�ظ���
/////////////////////////////////////////////////////////////////////////////////
int	GList_GetListSize()
{
	return g_iListSize;
}
//=========================================================================
// �������ֻ�ȡSprite
SGameSprite* GList_GetSpriteByName( const char *szName )
{
	SpriteStruct	*pPtr	=	g_pListHeader;
	while( NULL != pPtr )
	{
		if( strcmp( pPtr->pSprite->szName, szName ) == 0 )
			return pPtr->pSprite;
		pPtr	=	pPtr->pNext;
	}
	return NULL;
}
//=========================================================================
// ���񣺸���������ȡSprite
// ��ʾ���ο����������ֻ�ȡSprite��
// ��ʾ�����Ҫ��������ɾ�����е�ĳ��Ԫ�أ���Ӻ�����ǰ�����(��������ʼ��Ϊ�����СȻ��ݼ�)�������Ȼ����
SGameSprite *GList_GetSpriteByIndex( const int iIndex )
{
// ͨ��ѭ��������ͷ��ʼ���ң���ѭ�������ﵽiIndex��ʱ���õ���������Ӧ��Ԫ��
	int	iLoop	=	0;
	SpriteStruct	*pPtr	=	g_pListHeader;
	while( NULL != pPtr )
	{
		if( iLoop == iIndex )
			return pPtr->pSprite;

		iLoop++;
		pPtr	=	pPtr->pNext;
	}
return NULL;
}
//=========================================================================
// ���һ��Sprite��������
SpriteStruct *GList_AddSprite( SGameSprite *pSprite )
{
	if( NULL == pSprite )
		return NULL;
	SpriteStruct	*pPtr	=	(SpriteStruct*)malloc( sizeof(SpriteStruct) );
	pPtr->pSprite	=	pSprite;
	pPtr->pNext		=	NULL;
	pPtr->pPrev		=	NULL;
	// ���������β
	if( NULL == g_pListHeader )
		g_pListHeader	=	pPtr;
	else
	{
		SpriteStruct	*pTemp	=	g_pListHeader;
		while( NULL != pTemp->pNext )
			pTemp	=	pTemp->pNext;

		pPtr->pPrev		=	pTemp;
		pTemp->pNext	=	pPtr;
	}
	g_iListSize++;
	return pPtr;
}
//=========================================================================
// ��������ɾ��Sprite
void GList_DeleteSprite( const char *szName, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	g_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( strcmp( szName, pPtr->pSprite->szName ) == 0 )
		{
			// ����ָ���������ȡ��(���������е�ǰ��ָ������ָ��)
			// ����Ŀǰ�������£���ABC����ֵ��A <-> B <-> C����Ҫɾ��B
			// ����Ҫ��A��Nextָ��C��C��Prevָ��A��ɾ��֮����Ϊ A <-> C
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			// ����Ǳ�ͷ
			if( pPtr == g_pListHeader )
			{
				g_pListHeader	=	g_pListHeader->pNext;
			}
			// ɾ��Sprite
			if( bDeleteImage )
				dDeleteSprite(pPtr->pSprite->szName);
			// �ͷ��ڴ�
			free( pPtr );
			//
			g_iListSize--;
			return;
		}
	}
}
//=========================================================================
// ���񣺸���ָ��ɾ��Sprite
// ��ʾ���ο�����������ɾ��Sprite��
void GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	g_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( pPtr->pSprite == pSprite )
		{
			// ����ָ���������ȡ��(���������е�ǰ��ָ������ָ��)
			// ����Ŀǰ�������£���ABC����ֵ��A <-> B <-> C����Ҫɾ��B
			// ����Ҫ��A��Nextָ��C��C��Prevָ��A��ɾ��֮����Ϊ A <-> C
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			// ����Ǳ�ͷ
			if( pPtr == g_pListHeader )
			{
				g_pListHeader	=	g_pListHeader->pNext;
			}
			// ɾ��Sprite
			if( bDeleteImage )
				dDeleteSprite(pPtr->pSprite->szName);
			// �ͷ��ڴ�
			free( pPtr );
			g_iListSize--;
			return;
		}
	}
}
//=========================================================================
// ɾ������Sprite
void GList_DeleteAllSprite( bool bDeleteImage )
{
	SpriteStruct	*pPtr				=	NULL;
	SpriteStruct	*pPtrhNext	=	g_pListHeader;
	while( NULL != pPtrhNext )
	{
		pPtr			=	pPtrhNext;
		pPtrhNext	=	pPtrhNext->pNext;
		// ɾ��Sprite��ʾ
		if( bDeleteImage )
			dDeleteSprite(pPtr->pSprite->szName);
		// �ͷ��ڴ�
		free( pPtr );
	};
	g_pListHeader	=	NULL;
	g_iListSize		=	0;
}