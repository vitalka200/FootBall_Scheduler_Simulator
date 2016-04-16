#include "Game.h"
#include "Fan.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Team.h"


bool Game::operator==(const Game& g) const
{
	return (m_teams[0] == g.m_teams[0] && m_teams[1] == g.m_teams[1]) ||
		(m_teams[0] == g.m_teams[1] && m_teams[1] == g.m_teams[0]);
}

const Game& Game::operator=(const Game& g)
{
	if (this != &g)
	{
		SetTimeAndDate(*g.GetTimeAndDate());
	}
	return *this;
}

void Game::SetTimeAndDate(const TimeAndDate& tad)
{
	delete m_timeAndDate;
	m_timeAndDate = new TimeAndDate(tad);
}
