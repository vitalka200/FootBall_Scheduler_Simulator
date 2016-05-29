#include "Team.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Defender.h"
#include "Forwarder.h"
#include "Goalkeeper.h"
#include <string>
#include <vector>
#include <typeinfo.h>


const Team& Team::operator=(const Team& t)
{
	if (this != &t)
	{
		m_isAttacking   = t.m_isAttacking;
		m_goalkeeperNum = t.m_goalkeeperNum;
		SetName(t.m_name);
		SetPlayers(t.m_players);
		SetTrainers(t.m_trainers);
		SetPlayerStats(t.m_playerStats);
		if (m_goalkeeperNum >= 0 )
		{ m_goalkeeper = m_players[m_goalkeeperNum]; }
	}
	return *this;
}

Team::~Team()
{
	DeletePlayers(m_players); DeletePlayerStats(m_playerStats);
}

Player* Team::operator[](int index)
{
	return m_players[index];
}

void Team::AddPlayer(Player* p)
{
	p->SetTeam(this);
	m_players.push_back(p);
	m_playerStats.push_back(new PlayerStats(p));
	if (typeid(*p) == typeid(Goalkeeper))
	{ m_goalkeeper = p; m_goalkeeperNum = m_players.size() - 1; }
}

void Team::RemovePlayer(const Player* p)
{
	
	int playerPosition = -1;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i]->IsEqual(p))
		{ playerPosition = i; break;}
	}
	if (playerPosition > -1)
	{
		m_players.erase(m_players.begin() + playerPosition);
		m_playerStats.erase(m_playerStats.begin() + playerPosition);
	}

	if (typeid(*p) == typeid(Goalkeeper))
	{
		m_goalkeeper = NULL; m_goalkeeperNum = -1;
	}

}

void Team::AddTrainer(Trainer* t)
{ m_trainers.push_back(*t); }

void Team::RemoveTrainer(const Trainer* t)
{
	int idxToRemove = -1;
	for (int i = 0; i < m_trainers.size(); i++)
	{
		if (m_trainers[i] == (*(t)))
		{ idxToRemove = i; }
	}
	if (idxToRemove > -1)
	{ m_trainers.erase(m_trainers.begin() + idxToRemove); }
}

PlayerStats* Team::GetPlayerStats(const Player* p) const
{

	PlayerStats* ps = NULL;
	for (int i = 0; i < m_playerStats.size(); i++)
	{
		if (m_playerStats[i]->GetPlayer()->IsEqual(p))
		{ ps = m_playerStats[i]; break; }
	}
	return ps;
}

void Team::AddPlayerStat(const Player* p, const PlayerMovement move, bool isActualGoal)
{
	PlayerStats* ps = GetPlayerStats(p);
	ps->AddMove(move);
	if (isActualGoal)
	{ ps->AddGoals(); }
}

void Team::SetPlayers(std::vector<Player*> players)
{
	DeletePlayers(m_players); m_players.clear();

	for (int i = 0; i < players.size(); i++)
	{
		m_players.push_back(players[i]);
		m_players[i]->SetTeam(this);
	}
}

void Team::SetTrainers(std::vector<Trainer> trainers)
{
	m_trainers.clear();
	m_trainers = trainers;

}

void Team::SetPlayerStats(std::vector<PlayerStats*> ps)
{
	DeletePlayerStats(m_playerStats); m_playerStats.clear();
	m_playerStats = ps;
}

void Team::DeletePlayers(std::vector<Player*> players)
{
	for (int i = 0; i < players.size(); i++)
	{ delete players[i]; }
}

void Team::DeletePlayerStats(std::vector<PlayerStats*> pStats)
{
	for (int i = 0; i < pStats.size(); i++)
	{ delete pStats[i]; }
}

const PlayerStats& PlayerStats::operator=(const PlayerStats& ps)
{
	if (this != &ps)
	{
		m_moves = ps.m_moves;
		m_pl    = ps.m_pl;
	}
	return *this;
}

void PlayerStats::AddMove(const PlayerMovement move)
{ m_moves.push_back(move); }

void PlayerStats::AddCard(const CardType card)
{
	if (card == CardType::RED) { m_redCards++; }
	else if (card == CardType::YELLOW) { m_yellowCards++; }
}
