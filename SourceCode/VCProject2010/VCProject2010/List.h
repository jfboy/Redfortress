///////////////////////////////////////////////////////////////////////
//
// 链表管理
//
///////////////////////////////////////////////////////////////////
#ifndef _LIST_H_
#define _LIST_H_
#include <Windows.h>
#include "CommonAPI.h"

extern void	GameMainLoop( float	fDeltaTime );
//*************************太空战机链表实验*********************
struct	SpriteStruct
{
	struct SGameSprite	*pSprite;
	SpriteStruct	*pNext;
	SpriteStruct	*pPrev;
};
#endif  _LIST_H_

