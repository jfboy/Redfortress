#include"LessonX.h"
#include "List.h"
#include <stdio.h>
extern int			GList_GetListSize();
// 根据名字获取Sprite
SGameSprite	*GList_GetSpriteByName( const char *szName );	
// 根据索引获取Sprite，如果要遍历链表并删除其中的某个元素，请从后面往前面遍历(即索引初始化为链表大小然后递减)，否则必然出错
 SGameSprite	*GList_GetSpriteByIndex( const int iIndex );	
// 添加一个Sprite到链表里
 SpriteStruct	*GList_AddSprite( SGameSprite *pSprite );	
// 根据名字删除Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
void	GList_DeleteSprite( const char *szName, bool bDeleteImage = true );	
// 根据指针删除Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
void	GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage = true );
// 删除所有Sprite. bDeleteImage : 是否删除该Sprite在地图上的图片显示
void	GList_DeleteAllSprite( bool bDeleteImage = true );	

//=============================================================
SpriteStruct	*g_pListHeader	=	NULL;
int	g_iListSize  =	 0;					
// 链表元素个数
/////////////////////////////////////////////////////////////////////////////////
int	GList_GetListSize()
{
	return g_iListSize;
}
//=========================================================================
// 根据名字获取Sprite
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
// 任务：根据索引获取Sprite
// 提示：参考“根据名字获取Sprite”
// 提示：如果要遍历链表并删除其中的某个元素，请从后面往前面遍历(即索引初始化为链表大小然后递减)，否则必然出错
SGameSprite *GList_GetSpriteByIndex( const int iIndex )
{
// 通过循环从链表头开始查找，当循环次数达到iIndex次时，得到该索引对应的元素
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
// 添加一个Sprite到链表里
SpriteStruct *GList_AddSprite( SGameSprite *pSprite )
{
	if( NULL == pSprite )
		return NULL;
	SpriteStruct	*pPtr	=	(SpriteStruct*)malloc( sizeof(SpriteStruct) );
	pPtr->pSprite	=	pSprite;
	pPtr->pNext		=	NULL;
	pPtr->pPrev		=	NULL;
	// 插入链表表尾
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
// 根据名字删除Sprite
void GList_DeleteSprite( const char *szName, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	g_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( strcmp( szName, pPtr->pSprite->szName ) == 0 )
		{
			// 将本指针从链表中取出(即将链表中的前后指针重新指定)
			// 假设目前链表如下：有ABC三个值，A <-> B <-> C，需要删除B
			// 则需要将A的Next指向C，C的Prev指向A，删除之后结果为 A <-> C
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			// 如果是表头
			if( pPtr == g_pListHeader )
			{
				g_pListHeader	=	g_pListHeader->pNext;
			}
			// 删除Sprite
			if( bDeleteImage )
				dDeleteSprite(pPtr->pSprite->szName);
			// 释放内存
			free( pPtr );
			//
			g_iListSize--;
			return;
		}
	}
}
//=========================================================================
// 任务：根据指针删除Sprite
// 提示：参考“根据名字删除Sprite”
void GList_DeleteSprite( SGameSprite *pSprite, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	g_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( pPtr->pSprite == pSprite )
		{
			// 将本指针从链表中取出(即将链表中的前后指针重新指定)
			// 假设目前链表如下：有ABC三个值，A <-> B <-> C，需要删除B
			// 则需要将A的Next指向C，C的Prev指向A，删除之后结果为 A <-> C
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			// 如果是表头
			if( pPtr == g_pListHeader )
			{
				g_pListHeader	=	g_pListHeader->pNext;
			}
			// 删除Sprite
			if( bDeleteImage )
				dDeleteSprite(pPtr->pSprite->szName);
			// 释放内存
			free( pPtr );
			g_iListSize--;
			return;
		}
	}
}
//=========================================================================
// 删除所有Sprite
void GList_DeleteAllSprite( bool bDeleteImage )
{
	SpriteStruct	*pPtr				=	NULL;
	SpriteStruct	*pPtrhNext	=	g_pListHeader;
	while( NULL != pPtrhNext )
	{
		pPtr			=	pPtrhNext;
		pPtrhNext	=	pPtrhNext->pNext;
		// 删除Sprite显示
		if( bDeleteImage )
			dDeleteSprite(pPtr->pSprite->szName);
		// 释放内存
		free( pPtr );
	};
	g_pListHeader	=	NULL;
	g_iListSize		=	0;
}