#include "Camera.h"
#include "DxLib.h"
#include "Obj3D.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define USE_LERP_CAMERA 1

Camera::Camera():
	m_pos(VGet(0,0,0)),
	m_frame(0),
	m_isFlag(false)
{
	//カメラ
	SetCameraNearFar(0.1f, 1000.0f);

	// FOV(視野角)を60度に
	SetupCamera_Perspective(60.0f * (static_cast<float>(M_PI) / 180.0f));
}

Camera::~Camera()
{

}

void Camera::Update(const Obj3D& obj)
{
	//m_frame++;

	VECTOR aimPos = VGet(0, obj.GetPos().y + 20.0f, obj.GetPos().z - 30.0f); // b
	VECTOR posToAim = VSub(aimPos, m_pos);	// (b-a)
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);	// ((b-a) * t)
	m_pos = VAdd(m_pos, scaledPosToAim);	// a + ((b-a) * t)

	if (m_frame <= 0)m_isFlag = true;
	else if (m_frame >= 120)m_isFlag = false;

	if (m_isFlag)m_frame++;
	else m_frame--;


	SetupCamera_Perspective(m_frame * (static_cast<float>(M_PI) / 180.0f));


	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(m_pos, obj.GetPos());
}
