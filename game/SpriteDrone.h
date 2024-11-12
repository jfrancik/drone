#pragma once

class CSpriteDrone : public CSprite
{
	int turn;						// Steering: turn < 0 is left;  turn == 0 is straight on;  turn > 0 is right
	bool bShootLeft, bShootRight;	// Shooting flags - setting them will generate a shot at the next update
	
	CSpriteList m_missiles;
	CSoundPlayer m_player, m_player2;

public:
	CSpriteDrone(Sint16 x, Sint16 y, Uint32 time);
	~CSpriteDrone(void);

	void turnLeft();
	void turnRight();
	void goStraight();
	void shootLeft();
	void shootRight();

	// special functions
	bool HitTestMissiles(CSprite* pEnemy);	// return true if enemy hit with the missiles
	void DrawMissiles(CGraphics* g);		// draws the missiles
	void DrawVector(CVector v, CGraphics* g, CColor color, float fArrowLen = 18.f);

	// Called 60 times every second to update the position of the drone
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};
