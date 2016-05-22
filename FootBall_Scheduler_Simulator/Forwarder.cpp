#include "Forwarder.h"

#include <time.h>
#include <stdlib.h>
#define GOAL_FACTOR 5000

const PlayerMovement Forwarder::MakeMove(bool hasBall)
{
	srand(time(NULL));
	PlayerMovement pm;
	if (hasBall)
	{
		// When we have ball we can do anything
		pm = m_allowed_moves.moves[rand() % (m_allowed_moves.numberOfMoves)];
	}
	else
	{
		int wrongActions = (m_plevel*GOAL_FACTOR + GOAL_FACTOR)*MAKE_GOAL;
		wrongActions += (m_plevel + 1)*PASS_BALL;
		pm = m_allowed_moves.moves[rand() % (m_allowed_moves.numberOfMoves - wrongActions)];
	}
	return pm;
}

void Forwarder::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = (m_plevel + 1)*PASS_BALL + (m_plevel + 1)*TACKLE_BALL + (m_plevel + 1)*RUN_TO_OPEN_SPACE;
	m_allowed_moves.numberOfMoves += (m_plevel*GOAL_FACTOR+ GOAL_FACTOR)*MAKE_GOAL;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	int j = 0, i;
	for (i = 0; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::TACKLE_BALL; }

	for (i = 0; i < (m_plevel + 1)*RUN_TO_OPEN_SPACE; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::RUN_TO_OPEN_SPACE; }

	for (i = 0; i < (m_plevel*GOAL_FACTOR + GOAL_FACTOR)*MAKE_GOAL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::MAKE_GOAL; }

	for (i = 0; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::PASS_BALL; }
}

void Forwarder::show(std::ostream & os) const
{
	os << " Type: Forwarder";
}

