#include "Team.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"

Player* Team::operator[](int index)
{
	Player* p = NULL;
	for (int i = 0; i < m_numOfPlayers; i++)
	{
		if (m_players[i].GetId() == index)
		{ p = &m_players[i]; }
	}
	return p;
}

void Team::AddPlayer(Player* p)
{
	m_numOfPlayers++;
	m_players = (Player*)realloc(m_players, m_numOfPlayers * sizeof(Player));
	m_playerStats = (PlayerStats*)realloc(m_playerStats, m_numOfPlayers * sizeof(PlayerStats));
	m_playerStats[m_numOfPlayers-1].m_pl = p;
}

void Team::RemovePlayer(const Player* p)
{
	int playerPosition = -1;
	for (int i = 0; i < m_numOfPlayers; i++)
	{
		if (strcmp(m_players[i].GetName(), p->GetName()) &&
			strcmp(m_players[i].GetFName(), p->GetFName()))
		{ playerPosition = i; break;}
	}
	if (playerPosition >= 0)
	{
		for (int i = playerPosition; i < m_numOfPlayers-1; i++)
		{
			m_players[i] = m_players[i+1];
			m_playerStats[i] = m_playerStats[i - 1];
		}
		m_numOfPlayers--;
		m_players = (Player*)realloc(m_players, m_numOfPlayers * sizeof(Player));
		m_playerStats = (PlayerStats*)realloc(m_players, m_numOfPlayers * sizeof(PlayerStats));
	}
}

void Team::AddTrainer(Trainer* t)
{
	m_numOfTrainers++;
	m_trainers = (Trainer*)realloc(m_trainers, m_numOfTrainers * sizeof(Trainer));

}

void Team::RemoveTrainer(const Trainer* t)
{
	int trainerPosition = -1;

	for (int i = 0; i < m_numOfTrainers; i++)
	{
		if (strcmp(m_trainers[i].GetName(), t->GetName()) &&
			strcmp(m_trainers[i].GetFName(), t->GetFName()))
		{ trainerPosition = i; break; }
	}
	if (trainerPosition >= 0)
	{
		for (int i = trainerPosition; i < m_numOfTrainers - 1; i++)
		{
			m_trainers[i] = m_trainers[i + 1];
		}
		m_numOfPlayers--;
		m_trainers = (Trainer*)realloc(m_trainers, m_numOfTrainers * sizeof(Trainer));
	}
}

PlayerStats* Team::GetPlayerStats(const Player* p) const
{
	PlayerStats* ps = NULL;
	for (int i = 0; i < m_numOfPlayers; i++)
	{
		if (m_playerStats[i].GetPlayer()->IsEqual(p))
		{ ps = &m_playerStats[i]; }
	}
	return ps;
}

void Team::AddPlayerStat(const Player* p, const PlayerMovement* move, bool isActualGoal)
{
	PlayerStats* ps = GetPlayerStats(p);
	ps->AddMove(move);
	if (isActualGoal)
	{ ps->AddGoals(); }
}

const PlayerStats& PlayerStats::operator=(const PlayerStats& ps)
{
	if (this != &ps)
	{
		m_moves = (PlayerMovement*)malloc(m_movesNumber * sizeof(PlayerMovement));
	}
	return *this;
}

void PlayerStats::AddMove(const PlayerMovement* move)
{
	m_movesNumber++;
	m_moves = (PlayerMovement*)realloc(m_moves, m_movesNumber * sizeof(PlayerMovement));
	m_moves[m_movesNumber-1] = *move;
}
