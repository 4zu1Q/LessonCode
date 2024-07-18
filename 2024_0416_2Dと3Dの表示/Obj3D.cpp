#include "Obj3D.h"
#include "WorldSprite.h"

const float Obj3D::ChipSize = 0.725f;
const int Obj3D::ChipPixelSize = 130;

Obj3D::Obj3D():
	sprite(nullptr)
{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("data/model/obstructStatic/obstructStatic.pmd");
	m_pos = VGet(0, 0, 0);
	m_chipGraph = LoadGraph("data/texture/marisa.png");
	sprite = new WorldSprite();


}

Obj3D::~Obj3D()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);

	if (sprite != nullptr) delete sprite;
}

void Obj3D::Load()
{

	sprite->Initialize(m_chipGraph, ChipPixelSize, 0);

}

void Obj3D::Init()
{

}

void Obj3D::Update()
{
	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));


	sprite->SetTransform(VGet(0, 0, 0), 10.0f);
}

void Obj3D::Draw()
{
	MV1DrawModel(m_modelHandle);
	sprite->Draw();
}
