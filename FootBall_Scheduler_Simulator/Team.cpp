#include "Team.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"

Player* Team::operator[](int index)
{
	if (index > 0 && index < m_numOfPlayers)
	{
		return &m_players[index];
	}
	return NULL;
}

void Team::AddPlayer(Player* p)
{
	m_players = (Player*)realloc(m_players, m_numOfPlayers * sizeof(Player*) + 1);
	m_numOfPlayers++;
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
		}
		m_numOfPlayers--;
		m_players = (Player*)realloc(m_players, m_numOfPlayers * sizeof(Player*));
	}
}

void Team::AddTrainer(Trainer* t)
{
	m_trainers = (Trainer*)realloc(m_trainers, m_numOfTrainers * sizeof(Trainer*) + 1);
	m_numOfTrainers++;
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
		m_trainers = (Trainer*)realloc(m_trainers, m_numOfTrainers * sizeof(Trainer*));
	}
}

void PlayerStats::AddMove(const PlayerMovement* move)
{
	m_moves = (PlayerMovement*)realloc(m_moves, m_movesNumber * sizeof(PlayerMovement)+1);
	m_moves[m_movesNumber] = *move;
	m_movesNumber++;
}
