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
	//Player** newPList       = new Player*[m_numOfPlayers+1];
	//PlayerStats** newPSList = new PlayerStats*[m_numOfPlayers+1];

	//for (int i = 0; i < m_numOfPlayers; i++)
	//{ 
	//	newPList[i] = m_players[i];
	//	newPSList[i] = m_playerStats[i];
	//    if (typeid(*(newPSList[i])) == typeid(Goalkeeper))
	//    { m_goalkeeper = newPList[i]; m_goalkeeperNum = i;}
	//}

	//p->SetTeam(this);
	//newPList[m_numOfPlayers] = p;
	//newPSList[m_numOfPlayers] = new PlayerStats(p);

	//if (typeid(*p) == typeid(Goalkeeper))
	//{ m_goalkeeper = p; m_goalkeeperNum = m_numOfPlayers;}

	//delete []m_players; delete []m_playerStats;
	//m_players = newPList;
	//m_playerStats = newPSList;

	//m_numOfPlayers++;
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
	//if (playerPosition >= 0)
	//{
	//	Player* playerToRemove  = m_players[playerPosition];
	//	Player** newPList       = new Player*[m_numOfPlayers-1];
	//	PlayerStats** newPSList = new PlayerStats*[m_numOfPlayers-1];

	//	for (int i = playerPosition+1; i < m_numOfPlayers; i++)
	//	{ 
	//		newPList[i-1]  = m_players[i];
	//		newPSList[i-1] = m_playerStats[i];
	//	}
	//	// Release memory and assign new arrays
	//	//DeletePlayers(m_players); DeletePlayerStats(m_playerStats);
	//	delete []m_players;       delete []m_playerStats;
	//	m_players = newPList;     m_playerStats = newPSList;
	//	// Decrement counter
	//	m_numOfPlayers--;
	//}

	if (typeid(*p) == typeid(Goalkeeper))
	{
		m_goalkeeper = NULL; m_goalkeeperNum = -1;
	}

}

void Team::AddTrainer(Trainer* t)
{
	//Trainer* newList = new Trainer[m_numOfTrainers+1];
	//for (int i = 0; i < m_numOfTrainers; i++)
	//{
	//	newList[i] = Trainer(m_trainers[i]);
	//}
	//newList[m_numOfTrainers]        = Trainer(*t);
	//delete []m_trainers; m_trainers = newList;
	//m_numOfTrainers++;
	m_trainers.push_back(*t);
}

void Team::RemoveTrainer(const Trainer* t)
{
	//Trainer* newList = new Trainer[m_numOfTrainers-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_trainers.size(); i++)
	{
		if (m_trainers[i] == (*(t)))
		{ idxToRemove = i; }
	}
	if (idxToRemove > -1)
	{ m_trainers.erase(m_trainers.begin() + idxToRemove); }

	//if (idxToRemove >= 0)
	//{
	//	for (int i = 0; i < idxToRemove; i++)
	//	{ newList[i] = Trainer(m_trainers[i]);}
	//	for (int i = idxToRemove+1; i < m_numOfTrainers; i++)
	//	{ newList[i-1] = Trainer(m_trainers[i]); }
	//	delete []m_trainers; m_trainers = newList;
	//	m_numOfTrainers--;
	//}
	//else 
	//{ delete []newList; }
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
	DeletePlayers(m_players); //delete []m_players;
	m_players.clear();
	//m_numOfPlayers = count;
	//m_players = new Player*[m_numOfPlayers];

	//for (int i = 0; i < count; i++)
	//{
	//	if (typeid(*players[i]) == typeid(Defender))
	//	{ m_players[i] = new Defender(*dynamic_cast<Defender*>(players[i])); }
	//	else if (typeid(*players[i]) == typeid(Forwarder))
	//	{ m_players[i] = new Forwarder(*dynamic_cast<Forwarder*>(players[i])); }
	//	else if (typeid(*players[i]) == typeid(Goalkeeper))
	//	{ m_players[i] = new Goalkeeper(*dynamic_cast<Goalkeeper*>(players[i])); }

	//	m_players[i]->SetTeam(this);
	//}
	for (int i = 0; i < players.size(); i++)
	{
		m_players.push_back(players[i]);
		m_players[i]->SetTeam(this);
	}
}

void Team::SetTrainers(std::vector<Trainer> trainers)
{
	//delete []m_trainers;
	//m_numOfTrainers = count;
	//m_trainers = new Trainer[m_numOfTrainers];
	//
	//for (int i = 0; i < m_numOfTrainers; i++)
	//{ m_trainers[i] = Trainer(trainers[i]); }
	m_trainers.clear();
	m_trainers = trainers;

}

void Team::SetPlayerStats(std::vector<PlayerStats*> ps)
{
	DeletePlayerStats(m_playerStats); //delete[]m_playerStats;
	m_playerStats.clear();
	m_playerStats = ps;
	//m_playerStats = new PlayerStats*[count];

	//for (int i = 0; i < count; i++)
	//{ m_playerStats[i] = new PlayerStats(*(ps[i])); }
}

void Team::DeletePlayers(std::vector<Player*> players)
{
	//if (players)
	//{
		for (int i = 0; i < players.size(); i++)
		{ delete players[i]; }
	//}
}

void Team::DeletePlayerStats(std::vector<PlayerStats*> pStats)
{
	//if (pStats)
	//{
		for (int i = 0; i < pStats.size(); i++)
		{ delete pStats[i]; }
	//}
}

const PlayerStats& PlayerStats::operator=(const PlayerStats& ps)
{
	if (this != &ps)
	{
		m_moves       = ps.m_moves;
		m_pl          = ps.m_pl;
	}
	return *this;
}

void PlayerStats::AddMove(const PlayerMovement move)
{
	//PlayerMovement* newList = new PlayerMovement[m_movesNumber+1];

	//for (int i = 0; i < m_movesNumber; i++)
	//{ newList[i] = m_moves[i]; }

	//newList[m_movesNumber] = move;

	//delete []m_moves; m_moves = newList;
	//m_movesNumber++;
	m_moves.push_back(move);
}

void PlayerStats::AddCard(const CardType card)
{
	if (card == CardType::RED) { m_redCards++; }
	else if (card == CardType::YELLOW) { m_yellowCards++; }
}
