#include "stdafx.h"
#include "SpriteDrone.h"

CSpriteDrone::CSpriteDrone(Sint16 x, Sint16 y, Uint32 time)
	: CSprite(x, y, "drone.png", CColor::Green(), time)
{
	turn = 0;
	bShootLeft = bShootRight = false;
}

CSpriteDrone::~CSpriteDrone()
{
}

void CSpriteDrone::turnLeft()
{
	turn = -1;
}

void CSpriteDrone::turnRight()
{
	turn = 1;
}

void CSpriteDrone::goStraight()
{
	turn = 0;
}

void CSpriteDrone::shootLeft()
{
	bShootLeft = true;
}

void CSpriteDrone::shootRight()
{
	bShootRight = true;
}

bool CSpriteDrone::HitTestMissiles(CSprite* pEnemy)
{
	for each (CSprite * pMissile in m_missiles)
	{
		if (pMissile->HitTest(pEnemy))
		{
			m_player.Play("explode.wav");
			m_player2.Play("yes.wav");
			pMissile->Delete();
			m_missiles.remove_if(deleted);
			return true;
		}
	}
	return false;
}

void CSpriteDrone::DrawMissiles(CGraphics *g)
{
	for each (CSprite * pMissile in m_missiles)
		pMissile->Draw(g);
}

void CSpriteDrone::DrawVector(CVector v, CGraphics* g, CColor color, float fArrowLen)
{
	CVector arr = Normalise(v) * fArrowLen;
	CVector arp(arr.m_y, -arr.m_x);
	
	g->DrawLine(GetPos(), GetPos() + v, 3, color);
	g->DrawLine(GetPos() + v, GetPos() + v - arr + 0.5 * arp, 3, color);
	g->DrawLine(GetPos() + v, GetPos() + v - arr - 0.5 * arp, 3, color);

}

void CSpriteDrone::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	// speed
	float v = 250;

	// set speed
	SetSpeed(v);
	
	// turn...
	float dir = GetDirection();
	if (turn > 0)
		dir += deltaTime * v / 4000;
	else
	if (turn < 0)
		dir -= deltaTime * v / 4000;
	SetDirection(dir);
	SetRotation(dir);

	// shooting
	if (bShootLeft || bShootRight)
	{
		CSprite* pMissile = new CSprite(GetPos(), bShootLeft ? "lmissile.png" : "rmissile.png", CColor::White(), time);
		pMissile->SetVelocity(GetVelocity() * 2);
		pMissile->SetRotation(GetRotation());
		m_missiles.push_back(pMissile);
		m_player.Play("shot.wav");
	}
	bShootLeft = bShootRight = false;

	// update missiles
	for each (CSprite * pMissile in m_missiles)
	{
		pMissile->Update(time);
		if (Distance(pMissile->GetPos(), GetPos()) > 300)
			pMissile->Delete();
	}
	m_missiles.remove_if(deleted);


	CSprite::OnUpdate(time, deltaTime);
}
