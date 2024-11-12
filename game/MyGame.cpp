#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : m_BackTile(0, 0, "water.png", 0),
	m_panel(896, 384, 0)
{
	m_pDrone = NULL;
	m_pNPC = NULL;
}

CMyGame::~CMyGame(void)
{
}

// This functions controls the panel based on drone's and enemy's relational position
// Could also implement simple AI for the drone (auto-pilot + auto-shoot)
void ControlObjects(CSpriteDrone& drone, CSprite& enemy, CSpritePanel& panel)
{
	// TO DO: Insert your code here

}


/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	if (m_pDrone) m_pDrone->Update(t);
	if (m_pNPC) m_pNPC->Update(t);

	// test for crash
	if (m_pNPC && m_pDrone && m_pDrone->HitTest(m_pNPC))
	{
		m_playerEngine.Stop();
		m_player.Play("explode.wav");
		delete m_pNPC;
		m_pNPC = NULL;
		delete m_pDrone;
		m_pDrone = NULL;
		GameOver();
	}

	// test for shooting
	if (m_pNPC && m_pDrone && m_pDrone->HitTestMissiles(m_pNPC))
	{
		delete m_pNPC;
		m_pNPC = NULL;
		GameOver();
	}

	// The main control function
	if (m_pDrone && m_pNPC)
		ControlObjects(*m_pDrone, *m_pNPC, m_panel);
}

void CMyGame::OnDraw(CGraphics* g)
{
	// engine sound
	if (m_pDrone && !m_playerEngine.IsPlaying()) m_playerEngine.Play("engine.wav");

	// setup screen scroll
	CVector offs = m_pDrone ? m_pDrone->GetPos() : CVector(0, 0);
	offs -= CVector(384, 384);
	g->SetScrollPos(-offs);

	// draw background tiles
	CVectorI pos = offs;
	pos /= 256; pos *= 256;
	for (int i = -1; i <= 5; i++)
		for (int j = -1; j <= 4; j++)
		{
			m_BackTile.SetPos(pos + CVectorI(256 * i, 256 * j));
			m_BackTile.Draw(g);
		}

	// Draw the NPC
	if (m_pNPC)
		m_pNPC->Draw(g);


	// Draw the Drone
	if (m_pDrone)
	{
		m_pDrone->DrawMissiles(g);
		m_pDrone->Draw(g);

		if (IsKeyDown(SDLK_z) && IsKeyDown(SDLK_LALT))
			m_pDrone->DrawVector(m_pDrone->GetVelocity(), g, CColor::Red());
		if (m_pNPC && IsKeyDown(SDLK_x) && IsKeyDown(SDLK_LALT))
			m_pDrone->DrawVector(m_pNPC->GetPos() - m_pDrone->GetPos(), g, CColor::Green());
	}

	g->ResetScrollPos();

	// texts
	//*g << "Coords: " << (int)m_pDrone->GetPos().m_x << ", " << (int)m_pDrone->GetPos().m_y << endl;
	//*g << "Coords: " << (int)m_pNPC->GetPos().m_x << ", " << (int)m_pNPC->GetPos().m_y << endl;

	if (m_pDrone && m_pNPC)
		m_panel.Draw(g);
	else if (m_pDrone)
		// Victory Message
		*g << font(48) << color(CColor::Red()) << center << bottom << endl << endl << down << "VICTORY!!!" << endl
		   << font(24) << color(CColor::DarkBlue()) << "press F2 to restart the game";
	else
		// Drone Lost message
		*g << font(48) << color(CColor::Black()) << center << bottom << endl << endl << down << "DRONE LOST" << endl 
		   << font(24) << "You were supposed to shoot the enemy not to crash into it!" << endl 
		   << font(24) << color(CColor::DarkBlue()) << "press F2 to restart the game";

	*g << color(CColor::Black()) << font(10) << bottom << left << "Imagery from http://docs.garagegames.com/torquex/official" << endl;
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	if (m_pDrone) delete m_pDrone;
	m_pDrone = new CSpriteDrone(0, 0, GetTime());
	if (m_pNPC) delete m_pNPC;
	
	CVector npc(rand() % 12000 - 6000.f, rand() % 12000 - 6000.f);
	m_pNPC = new CSpriteNPC(6000 * Normalise(npc), GetTime());
	
	StartGame();
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
	m_playerEngine.Stop();
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_F2)
		NewGame();
	if (sym == SDLK_SPACE)
		PauseGame();

	// Steer the Drone
	if (!m_pDrone) return;
	if (sym == SDLK_RIGHT || sym == SDLK_d)
		m_pDrone->turnRight();
	if (sym == SDLK_LEFT || sym == SDLK_a)
		m_pDrone->turnLeft();

	// Shoot
	if (sym == SDLK_LCTRL)
		m_pDrone->shootLeft();
	if (sym == SDLK_RCTRL)
		m_pDrone->shootRight();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (!m_pDrone) return;
	if (sym == SDLK_RIGHT || sym == SDLK_LEFT || sym == SDLK_d || sym == SDLK_a)
		m_pDrone->goStraight();
}

/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
