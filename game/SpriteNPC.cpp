#include "stdafx.h"
#include "SpriteNPC.h"

CSpriteNPC::CSpriteNPC(Sint16 x, Sint16 y, Uint32 time)
	: CSprite(x, y, "npc.png", CColor::White(), time)
{
	m_target = CVector(0, 1);
}

CSpriteNPC::CSpriteNPC(CVector pos, Uint32 time)
	: CSprite(pos, "npc.png", CColor::White(), time)
{
	m_target = CVector(0, 1);
}

CSpriteNPC::~CSpriteNPC()
{
}

void CSpriteNPC::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	// speed
	float v = 200;

	// wandering behaviour
	static const float RandMax = static_cast<float>(RAND_MAX);
	m_target += CVector(static_cast<float>(rand()) / RandMax - 0.5f,  static_cast<float>(rand()) / RandMax - 0.5f);
	m_target.Normalise();
	m_target *= 1;
	CVector target = GetPos() + 0.1f * GetVelocity() + m_target;
	SetVelocity(Normalize(target - GetPos()) * v);

	// turns
	float dir = GetDirection();
	SetRotation(dir);

	CSprite::OnUpdate(time, deltaTime);
}
