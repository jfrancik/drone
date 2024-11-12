#include "stdafx.h"
#include "SpritePanel.h"

CSpritePanel::CSpritePanel(Sint16 x, Sint16 y, Uint32 time)
	: CSprite(x, y, "panel.png", CColor::White(), time),
	  m_im("panel.png", CColor::White()),
	  m_imLT("panelLT.bmp", CColor::White()),
	  m_imRT("panelRT.bmp", CColor::White()),
	  m_imUP("panelUP.bmp", CColor::White()),
	  m_imDN("panelDN.bmp", CColor::White())
{
}

CSpritePanel::~CSpritePanel()
{
}

void CSpritePanel::OnDraw(CGraphics* g)
{
	SetImage(&m_im);
	if (front) m_pGraphics->Blit(CVector(0, 0), m_imUP);
	if (back) m_pGraphics->Blit(CVector(0, 0), m_imDN);
	if (left) m_pGraphics->Blit(CVector(0, 0), m_imLT);
	if (right) m_pGraphics->Blit(CVector(0, 0), m_imRT);
	*m_pGraphics << font(24) << center << bottom << vcenter << distance << endl;

	if (distance < 1000)
		if (!m_player.IsPlaying()) m_player.Play("beeper.wav");
}

