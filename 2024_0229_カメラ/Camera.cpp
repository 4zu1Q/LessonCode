//-----------------------------------------------------------------------------
// @brief  カメラクラス.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "Camera.h"


//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Camera::Camera()
{

	////視野角(fov)を60度に　※ラジアン
	//SetupCamera_Perspective(60.0f * (DX_PI_F / 180));
	
 //   //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 20, -20), VGet(0.0f, 10.0f, 0.0f));

    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(5.0f, 1000.0f);

	pos = VGet(0.0, 0.0, 0.0);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	// 処理なし.
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Camera::Update(const Player& player)
{
	

	// TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
	//pos = VGet(player.GetPos().x, player.GetPos().y + 20.0f, player.GetPos().z - 40.0f);

	//// カメラに位置を反映.
	VECTOR aimPos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f); // b
	VECTOR posToAim = VSub(aimPos, pos);	// (b-a)
	VECTOR scaledPosToAim = VScale(posToAim, 0.5f);	// ((b-a) * t)
	pos = VAdd(pos, scaledPosToAim);	// a + ((b-a) * t)

	SetCameraPositionAndTarget_UpVecY(pos, player.GetPos());
}