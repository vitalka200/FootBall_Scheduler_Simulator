#include "Forwarder.h"

#include <time.h>
#include <stdlib.h>

const PlayerMovement Forwarder::MakeMove(bool hasBall)
{
	srand(time(NULL));
	if (hasBall)
	{
		// When we have ball we can do anything
		return m_allowed_moves.moves[rand() % (m_allowed_moves.numberOfMoves];
	}
	return m_allowed_moves.moves[rand() % (m_allowed_moves.numberOfMoves - (m_plevel + 1)*MAKE_GOAL)];
}

void Forwarder::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = (m_plevel + 1)*PASS_BALL + (m_plevel + 1)*TACKLE_BALL + (m_plevel + 1)*RUN_TO_OPEN_SPACE;
	m_allowed_moves.numberOfMoves += (m_plevel + 1)*MAKE_GOAL;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	int i = 0;
	for (; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::PASS_BALL; }
	for (; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::TACKLE_BALL; }
	for (; i < (m_plevel + 1)*RUN_TO_OPEN_SPACE; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::RUN_TO_OPEN_SPACE; }
	for (; i < (m_plevel + 1)*MAKE_GOAL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::MAKE_GOAL; }
}

void Forwarder::show(std::ostream & os) const
{
	os << " Type: Forwarder";
}

