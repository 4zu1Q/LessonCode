#include "FrontGround2D.h"

FrontGround2D::FrontGround2D():
	m_handle(LoadGraph("data/texture/FancyBG_front.png")),
	m_pos(VGet(0, 0, 0))
{
}

FrontGround2D::~FrontGround2D()
{
	DeleteGraph(m_handle);
}

void FrontGround2D::Init()
{
}

void FrontGround2D::Update()
{
}

void FrontGround2D::Draw()
{
	DrawGraph(0, 0, m_handle, true);
}
