#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include <iostream>

namespace game_framework
{
CCharacter::CCharacter()
{
    Initialize();
}

int CCharacter::GetX1()
{
    return x;
}

int CCharacter::GetY1()
{
    return y;
}

int CCharacter::GetX2()
{
    return x + animation.Width();
}

int CCharacter::GetY2()
{
    return y + animation.Height();
}

void CCharacter::Initialize()
{
    const int INITIAL_VELOCITY = 10;	// 初始上升速度

    const int X_POS = 100;		//初始位置
    const int Y_POS = 500;

    x = X_POS;
    y = Y_POS;
    initial_velocity = INITIAL_VELOCITY;
    velocity = 1;
    rising = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
}

void CCharacter::LoadBitmap()
{
    animation.AddBitmap(IDB_character, RGB(255, 255, 255));	//原本不移動
    animation.AddBitmap(IDB_moveright, RGB(255, 255, 255));	//往右
    animation.AddBitmap(IDB_moveleft, RGB(255, 255, 255));	//往左
    animation.AddBitmap(IDB_moveup, RGB(255, 255, 255));
}

void CCharacter::OnMove(Map* map)
{
    const int STEP_SIZE = 10;
    animation.SetDelayCount(1);

    if (isMovingRight || isMovingLeft || isMovingUp)  		//往右
    {
        if (isMovingRight)
        {
            animation.SelectBitmap(1);

            switch (map->IsWhat(x + animation.Width() + 1, animation.Height(), y, 1))
            {
				case 0:	// 空的
					x += STEP_SIZE;
					break;
				case 1:	// 牆壁
					// Do noting;
					break;
				case 2: // Portal 0
					x = map->Find_PortalLoc('x', 3);	// 找Portal 1的x
					y = map->Find_PortalLoc('y', 3);	// 找Portal 1的y
					break;
				case 3:	// Portal 1
					x = map->Find_PortalLoc('x', 2);	// 找Portal 0的x
					y = map->Find_PortalLoc('y', 2);	// 找Portal 0的y
					break;
            }
        }

        if (isMovingLeft)  	//往左
        {
            animation.SelectBitmap(2);

            switch (map->IsWhat(x - 1, animation.Height(), y, 1))
            {
			case 0:	// 空的
				x -= STEP_SIZE;
				break;
			case 1:	// 牆壁
				// Do noting;
				break;
			case 2: // Portal 0
				x = map->Find_PortalLoc('x', 3);	// 找Portal 1的x
				y = map->Find_PortalLoc('y', 3);	// 找Portal 1的y
				break;
			case 3:	// Portal 1
				x = map->Find_PortalLoc('x', 2);	// 找Portal 0的x
				y = map->Find_PortalLoc('y', 2);	// 找Portal 0的y
				break;
            }
        }

		if (isMovingUp) {
			switch (map->IsWhat(x, 1, y + animation.Height() + 1, animation.Width()))  			// 上升狀態
			{
				animation.SelectBitmap(3);

			case 0:	// 空的
				// Do noting;
				break;
			case 1:	// 牆壁
				rising = TRUE;
				break;
			case 2: // Portal 0
				x = map->Find_PortalLoc('x', 3);	// 找Portal 1的x
				y = map->Find_PortalLoc('y', 3);	// 找Portal 1的y
				break;
			case 3:	// Portal 1
				x = map->Find_PortalLoc('x', 2);	// 找Portal 0的x
				y = map->Find_PortalLoc('y', 2);	// 找Portal 0的y
				break;
			}
		}
    }
    else
    {
        animation.Reset();
    }

    jump(map);
}

//animation.Reset();
/*  if (isMovingDown)
      y += STEP_SIZE;*/
void CCharacter::jump(Map* map)
{
    if (rising)  			// 上升狀態
    {
        if (map->IsWhat(x, 1, y + animation.Height() + 1, animation.Width()) == 1)
        {
            velocity = initial_velocity; // 重設上升初始速度
        }

        if (velocity > 0)
        {
            y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
            velocity--;		// 受重力影響，下次的上升速度降低
        }
        else
        {
            rising = false; // 當速度 <= 0，上升終止，下次改為下降
            velocity = 1;	// 下降的初速(velocity)為1
        }
    }
    else  				// 下降狀態
    {
        if (map->IsWhat(x, 1, y + animation.Height() + 1, animation.Width()) == 0)    // 當y座標還沒碰到地板
        {
            y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)

            if (velocity <= 10)	//下降速度最快到10
                velocity++;		// 受重力影響，下次的下降速度增加
            else
                velocity = 10;
        }
        else
        {
            y = y / TIMES;
            y = y * TIMES;
            //velocity = initial_velocity; // 重設上升初始速度
        }
    }
}

void CCharacter::SetMovingDown(bool flag)
{
    isMovingDown = flag;
}

void CCharacter::SetMovingLeft(bool flag)
{
    isMovingLeft = flag;
}

void CCharacter::SetMovingRight(bool flag)
{
    isMovingRight = flag;
}

void CCharacter::SetMovingUp(bool flag)
{
    isMovingUp = flag;
}

void CCharacter::SetXY(int nx, int ny)
{
    x = nx;
    y = ny;
}

void CCharacter::OnShow()
{
    animation.SetTopLeft(x, y);
    animation.OnShow();
}
}
