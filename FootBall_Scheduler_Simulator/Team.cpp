#include "Team.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Defender.h"
#include "Forwarder.h"
#include "Goalkeeper.h"
#include <typeinfo.h>


const Team& Team::operator=(const Team& t)
{
	if (this != &t)
	{
		m_numOfPlayers  = t.m_numOfPlayers;
		m_numOfTrainers = t.m_numOfTrainers;
		m_isAttacking   = t.m_isAttacking;
		m_goalkeeperNum = t.m_goalkeeperNum;
		SetName(t.m_name);
		SetPlayers(t.m_players, m_numOfPlayers);
		SetTrainers(t.m_trainers, m_numOfTrainers);
		SetPlayerStats(t.m_playerStats, m_numOfPlayers);
		if (m_goalkeeperNum >= 0 )
		{ m_goalkeeper = m_players[m_goalkeeperNum]; }
	}
	return *this;
}

Team::~Team()
{
	delete []m_name;          delete []m_trainers;
	DeletePlayers(m_players); DeletePlayerStats(m_playerStats);
	delete []m_players;       delete []m_playerStats;
}

Player* Team::operator[](int index)
{
	return m_players[index];
}

void Team::AddPlayer(Player* p)
{
	Player** newPList       = new Player*[m_numOfPlayers+1];
	PlayerStats** newPSList = new PlayerStats*[m_numOfPlayers+1];

	for (int i = 0; i < m_numOfPlayers; i++)
	{ newPList[i] = m_players[i]; newPSList[i] = m_playerStats[i]; }

	newPList[m_numOfPlayers] = p;
	newPSList[m_numOfPlayers] = new PlayerStats(p);

	if (typeid(*p) == typeid(Goalkeeper))
	{ m_goalkeeper = p; m_goalkeeperNum = m_numOfPlayers;}

	m_numOfPlayers++;
}

void Team::RemovePlayer(const Player* p)
{
	int playerPosition = -1;
	for (int i = 0; i < m_numOfPlayers; i++)
	{
		if (strcmp(m_players[i]->GetName(), p->GetName()) &&
			strcmp(m_players[i]->GetFName(), p->GetFName()))
		{ playerPosition = i; break;}
	}
	if (playerPosition >= 0)
	{
		Player* playerToRemove  = m_players[playerPosition];
		Player** newPList       = new Player*[m_numOfPlayers-1];
		PlayerStats** newPSList = new PlayerStats*[m_numOfPlayers-1];

		for (int i = playerPosition; i < m_numOfPlayers; i++)
		{ newPList[i-1]  = m_players[i]; newPSList[i] = m_playerStats[i];	}
		// Release memeory and assign new arrays
		DeletePlayers(m_players); DeletePlayerStats(m_playerStats);
		delete []m_players;       delete []m_playerStats;
		m_players = newPList;     m_playerStats = newPSList;
		// Decrement counter
		m_numOfPlayers--;
	}

	if (typeid(*p) == typeid(Goalkeeper))
	{
		m_goalkeeper = NULL; m_goalkeeperNum = -1;
	}

}

void Team::AddTrainer(Trainer* t)
{
	Trainer* newList = new Trainer[m_numOfTrainers+1];
	for (int i = 0; i < m_numOfTrainers; i++)
	{
		newList[i] = Trainer(m_trainers[i]);
	}
	newList[m_numOfTrainers]        = Trainer(*t);
	delete []m_trainers; m_trainers = newList;
	m_numOfTrainers++;
}

void Team::RemoveTrainer(const Trainer* t)
{
	Trainer* newList = new Trainer[m_numOfTrainers-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_numOfTrainers; i++)
	{
		if (m_trainers[i] == (*(t)))
		{ idxToRemove = i; }
	}
	if (idxToRemove >= 0)
	{
		for (int i = 0; i < idxToRemove; i++)
		{ newList[i] = Trainer(m_trainers[i]);}
		for (int i = idxToRemove+1; i < m_numOfTrainers; i++)
		{ newList[i-1] = Trainer(m_trainers[i]); }
		delete []m_trainers; m_trainers = newList;
		m_numOfTrainers--;
	}
	else 
	{ delete []newList; }
}

PlayerStats* Team::GetPlayerStats(const Player* p) const
{
	PlayerStats* ps = NULL;
	for (int i = 0; i < m_numOfPlayers; i++)
	{
		if (m_playerStats[i]->GetPlayer()->IsEqual(p))
		{ ps = m_playerStats[i]; }
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

void Team::SetPlayers(Player** players, int count)
{
	DeletePlayers(m_players); delete []m_players;
	m_numOfPlayers = count;
	m_players = new Player*[m_numOfPlayers];

	for (int i = 0; i < count; i++)
	{
		if (typeid(*m_players[i]) == typeid(Defender))
		{ m_players[i] = new Defender(*dynamic_cast<Defender*>(m_players[i])); }
		else if (typeid(*m_players[i]) == typeid(Forwarder))
		{ m_players[i] = new Forwarder(*dynamic_cast<Forwarder*>(m_players[i])); }
		else if (typeid(*m_players[i]) == typeid(Goalkeeper))
		{ m_players[i] = new Goalkeeper(*dynamic_cast<Goalkeeper*>(m_players[i])); }
	}
}

void Team::SetTrainers(const Trainer* trainers, int count)
{
	delete []m_trainers;
	m_numOfTrainers = count;
	m_trainers = new Trainer[m_numOfTrainers];
	
	for (int i = 0; i < m_numOfTrainers; i++)
	{ m_trainers[i] = Trainer(trainers[i]); }
}

void Team::SetPlayerStats(PlayerStats** ps, int count)
{
	DeletePlayerStats(m_playerStats); delete[]m_playerStats;
	m_playerStats = new PlayerStats*[m_numOfPlayers];

	for (int i = 0; i < m_numOfPlayers; i++)
	{ m_playerStats[i] = new PlayerStats(*(ps[i])); }
}

void Team::DeletePlayers(Player** players)
{
	for (int i = 0; i < m_numOfPlayers; i++)
	{ delete players[i]; }
}

void Team::DeletePlayerStats(PlayerStats** pStats)
{
	for (int i = 0; i < m_numOfPlayers; i++)
	{ delete pStats[i]; }
}

const PlayerStats& PlayerStats::operator=(const PlayerStats& ps)
{
	if (this != &ps)
	{
		delete []m_moves; 
		m_movesNumber = ps.m_movesNumber;
		m_moves       = new PlayerMovement[m_movesNumber];
		for (int i = 0; i < m_movesNumber; i++)
		{ m_moves[i] = ps.m_moves[i]; }
	}
	return *this;
}

void PlayerStats::AddMove(const PlayerMovement move)
{
	PlayerMovement* newList = new PlayerMovement[m_movesNumber+1];

	for (int i = 0; i < m_movesNumber; i++)
	{ newList[i] = m_moves[i]; }

	newList[m_movesNumber] = move;

	delete []m_moves; m_moves = newList;
	m_movesNumber++;
}

void PlayerStats::AddCard(const CardType card)
{
	if (card == CardType::RED) { m_redCards++; }
	else if (card == CardType::YELLOW) { m_yellowCards++; }
}
