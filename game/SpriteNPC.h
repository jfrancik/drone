#pragma once

class CSpriteNPC : public CSprite
{
	CVector m_target;
public:
	CSpriteNPC(CVector pos, Uint32 time);
	CSpriteNPC(Sint16 x, Sint16 y, Uint32 time);
	~CSpriteNPC(void);

	// Called 60 times every second to update the position of the NPC
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};
