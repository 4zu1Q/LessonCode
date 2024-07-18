#include "BackGround2D.h"

BackGround2D::BackGround2D():
m_handle(LoadGraph("data/texture/FancyBG_back.png")),
m_pos(VGet(0,0,0))
{

}

BackGround2D::~BackGround2D()
{
	DeleteGraph(m_handle);
}

void BackGround2D::Init()
{
}

void BackGround2D::Update()
{
}

void BackGround2D::Draw()
{
	DrawGraph(0, 0, m_handle, true);
}
