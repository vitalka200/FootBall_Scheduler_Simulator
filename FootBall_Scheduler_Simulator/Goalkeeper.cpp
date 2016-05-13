#include "Goalkeeper.h"

#include <time.h>
#include <stdlib.h>

const PlayerMovement Goalkeeper::MakeMove(bool hasBall)
{
	srand(time(NULL));
	
	if (hasBall)
	{
		// If we have ball, we pass it
		return PlayerMovement::PASS_BALL;
	}
	return m_allowed_moves.moves[rand() % m_allowed_moves.numberOfMoves];
}

void Goalkeeper::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = (m_plevel + 1)*CATCH_BALL + (m_plevel + 1)*PASS_BALL + (m_plevel + 1)*TACKLE_BALL;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	int i = 0;
	for (; i < (m_plevel + 1)*CATCH_BALL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::CATCH_BALL; }
	for (; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::PASS_BALL; }
	for (; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves.moves[i] = PlayerMovement::TACKLE_BALL; }
}

void Goalkeeper::show(std::ostream & os) const
{
	os << " Type: Goalkeeper";
}
