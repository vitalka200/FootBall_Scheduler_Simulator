#include "Goalkeeper.h"

#include <time.h>
#include <stdlib.h>
#define MISSING_FACTOR 400

const PlayerMovement Goalkeeper::MakeMove(bool hasBall)
{
	srand(time(NULL));
	
	if (hasBall)
	{
		// If we have ball, we pass it
		return PlayerMovement::PASS_BALL;
	}
	int moveNum = rand() % m_allowed_moves.numberOfMoves;
	return m_allowed_moves.moves[moveNum];
}

void Goalkeeper::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves =  (m_plevel + 1)*CATCH_BALL + (m_plevel*MISSING_FACTOR+ MISSING_FACTOR)*MISS_BALL;
	m_allowed_moves.numberOfMoves += (m_plevel + 1)*PASS_BALL  + (m_plevel + 1)*TACKLE_BALL;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	int i = 0;
	int j = 0;
	for (i = 0; i < (m_plevel + 1)*CATCH_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::CATCH_BALL; }
	for (i = 0; i < (m_plevel*MISSING_FACTOR + MISSING_FACTOR)*MISS_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::MISS_BALL; }
	for (i = 0; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::PASS_BALL; }
	for (i = 0; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves.moves[j++] = PlayerMovement::TACKLE_BALL; }
}

void Goalkeeper::show(std::ostream & os) const
{
	os << " Type: Goalkeeper";
}
