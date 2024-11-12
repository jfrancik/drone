#pragma once

class CSpritePanel : public CSprite
{
	CGraphics m_im, m_imLT, m_imRT, m_imUP, m_imDN;
	CSoundPlayer m_player;
public:
	bool front, back, left, right;
	int distance;

public:
	CSpritePanel(Sint16 x, Sint16 y, Uint32 time);
	~CSpritePanel(void);

	// Called to draw the sprite
	void CSpritePanel::OnDraw(CGraphics* g);
};
