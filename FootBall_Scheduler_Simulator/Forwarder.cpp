#include "Forwarder.h"

#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define GOAL_FACTOR 1

const PlayerMovement Forwarder::MakeMove(bool hasBall)
{
	PlayerMovement pm;
	if (hasBall)
	{
		// When we have ball we can do anything
		pm = m_allowed_moves[rand() % (m_allowed_moves.size())];
	}
	else
	{
		int wrongActions = (m_plevel*GOAL_FACTOR + GOAL_FACTOR)*MAKE_GOAL;
		wrongActions += (m_plevel + 1)*PASS_BALL;
		pm = m_allowed_moves[rand() % (m_allowed_moves.size() - wrongActions)];
	}
	return pm;
}

void Forwarder::CreateAllowedMoves()
{
	int numberOfMoves = (m_plevel + 1)*PASS_BALL + (m_plevel + 1)*TACKLE_BALL + (m_plevel + 1)*RUN_TO_OPEN_SPACE;
	numberOfMoves += (m_plevel*GOAL_FACTOR+ GOAL_FACTOR)*MAKE_GOAL;
	//m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];
	m_allowed_moves = std::vector<PlayerMovement>(numberOfMoves);

	int j = 0, i;
	for (i = 0; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::TACKLE_BALL; }

	for (i = 0; i < (m_plevel + 1)*RUN_TO_OPEN_SPACE; i++)
	{ m_allowed_moves[j++] = PlayerMovement::RUN_TO_OPEN_SPACE; }

	for (i = 0; i < (m_plevel*GOAL_FACTOR + GOAL_FACTOR)*MAKE_GOAL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::MAKE_GOAL; }

	for (i = 0; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::PASS_BALL; }
}

void Forwarder::show(std::ostream & os) const
{
	os << " Type: Forwarder";
}

