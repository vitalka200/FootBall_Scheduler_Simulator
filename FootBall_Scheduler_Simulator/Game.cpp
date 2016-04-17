#include "Game.h"
#include "Fan.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Team.h"

const Time MAX_GAME_LEN = Time(2, 0);

Game::~Game()
{
	delete[]m_fans; delete m_timeAndDate;
	DeletePlayerStats(m_playerStats); delete []m_playerStats;
}

bool Game::operator==(const Game& g) const
{
	return (m_teams[0] == g.m_teams[0] && m_teams[1] == g.m_teams[1]) ||
		(m_teams[0] == g.m_teams[1] && m_teams[1] == g.m_teams[0]);
}

const Game& Game::operator=(const Game& g)
{
	if (this != &g)
	{
		m_gameScore[0]  = g.m_gameScore[0]; 
		m_gameScore[1]  = g.m_gameScore[1];
		m_maxFans       = g.m_maxFans;

		SetTeams(g.m_teams);
		SetReferees(g.m_referees, g.m_refereesCount);
		SetTimeAndDate(g.GetTimeAndDate());
		SetPlayerStats(g.GetGameStats(), GetActualFans());
		SetFans(g.GetFans(), g.m_actualFans);
	}
	return *this;
}

void Game::SetTimeAndDate(const TimeAndDate* tad)
{
	delete m_timeAndDate;
	m_timeAndDate = new TimeAndDate(*tad);
}

void Game::SetPlayerStats(PlayerStats** ps, int count)
{
	DeletePlayerStats(m_playerStats); delete[]m_playerStats;

	int totalPlayers = GetTotalPlayers();
	m_playerStats    = new PlayerStats*[totalPlayers];

	for (int i = 0; i < totalPlayers; i++)
	{ m_playerStats[i] = new PlayerStats(*(ps[i])); }
}

void Game::SetFans(const Fan* fans, int count)
{
	delete []m_fans;
	m_actualFans = count;
	m_fans       = new Fan[m_actualFans];
}

void Game::SetReferees(const Referee* referees, int count)
{
	delete []m_referees;
	m_referees      = new Referee[count];
	m_refereesCount = count;
	for (int i = 0; i < count; i++)
	{ m_referees[i] = Referee(referees[i]); }
}

void Game::SetTeams(const Team* teams)
{
	delete []m_teams;
	m_teams    = new Team[2];
	m_teams[0] = Team(teams[0]);
	m_teams[1] = Team(teams[1]);
}

void Game::DeletePlayerStats(PlayerStats** pStats)
{
	int totalPlayers = GetTotalPlayers();
	for (int i = 0; i < totalPlayers; i++)
	{ delete pStats[i]; }
}

const Team* Game::GetWinner() const
{
	if (m_gameScore[0] >= 0)
	{ 
		if      (m_gameScore[0] > m_gameScore[1]) return &(m_teams[0]);
		else if (m_gameScore[1] > m_gameScore[0]) return &(m_teams[1]);
	}
	// There is no winner if score even or game not started
	return NULL;
}

int Game::GetTotalPlayers() const
{
	return m_teams[0].GetPlayerNum() + m_teams[1].GetPlayerNum();
}

void Game::AddReferee(const Referee& ref)
{
	Referee* newList = new Referee[m_refereesCount + 1];
	for (int i = 0; i < m_refereesCount; i++)
	{ newList[i] = m_referees[i]; }
	newList[m_refereesCount] = ref;
	delete[] m_referees; m_referees = newList;
	m_refereesCount++;
}

void Game::RemoveReferee(const Referee& ref)
{
	Referee* newList = new Referee[m_refereesCount-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_refereesCount; i++)
	{
		if (m_referees[i] == ref)
		{ idxToRemove = i; }
	}
	if (idxToRemove >= 0)
	{
		for (int i = 0; i < idxToRemove; i++)
		{ newList[i] = m_referees[i];}
		for (int i = idxToRemove+1; i < m_refereesCount; i++)
		{ newList[i-1] = m_referees[i]; }
		delete []m_referees; m_referees = newList;
		m_refereesCount--;
	}
	else 
	{ delete []newList; }
}

void Game::AddFan(const Fan& fan)
{
	Fan* newList = new Fan[m_actualFans+1];
	for (int i = 0; i < m_actualFans; i++)
	{ newList[i] = m_fans[i]; }
	newList[m_actualFans] = fan;
	delete []m_fans; m_actualFans++;
}

void Game::RemoveFan(const Fan& fan)
{
	Fan* newList = new Fan[m_actualFans-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_actualFans; i++)
	{
		if (m_fans[i] == fan)
		{ idxToRemove = i; }
	}
	if (idxToRemove >= 0)
	{
		for (int i = 0; i < idxToRemove; i++)
		{ newList[i] = m_fans[i];}
		for (int i = idxToRemove+1; i < m_actualFans; i++)
		{ newList[i-1] = m_fans[i]; }
		delete []m_fans; m_fans = newList;
		m_actualFans--;
	}
	else 
	{ delete []newList; }
}

void Game::SetTime(const TimeAndDate& tad)
{
	delete []m_timeAndDate;
	m_timeAndDate = new TimeAndDate(tad);
}

std::ostream & operator<<(std::ostream & os, const Game & g)
{
	os << "Game between '" << g.GetTeams()[0] << "' and '" << g.GetTeams()[1] << "'" << std::endl;
	os << "Score: '" << g.GetGameScore()[0] << "':'" << g.GetGameScore()[0] << "'";
	os << "Fans comming: " << g.GetActualFans();
	return os;
}
