#include "Goalkeeper.h"

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>

#define MISSING_FACTOR 1

const PlayerMovement Goalkeeper::MakeMove(bool hasBall)
{
	if (hasBall)
	{
		// If we have ball, we pass it
		return PlayerMovement::PASS_BALL;
	}
	int moveNum = rand() % m_allowed_moves.size();
	return m_allowed_moves[moveNum];
}

void Goalkeeper::CreateAllowedMoves()
{
	int numberOfMoves =  (m_plevel + 1)*CATCH_BALL + (m_plevel*MISSING_FACTOR+ MISSING_FACTOR)*MISS_BALL;
	numberOfMoves += (m_plevel + 1)*PASS_BALL  + (m_plevel + 1)*TACKLE_BALL;
	m_allowed_moves = std::vector<PlayerMovement>(numberOfMoves);

	int i = 0;
	int j = 0;
	for (i = 0; i < (m_plevel + 1)*CATCH_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::CATCH_BALL; }

	for (i = 0; i < (m_plevel*MISSING_FACTOR + MISSING_FACTOR)*MISS_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::MISS_BALL; }

	for (i = 0; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::PASS_BALL; }

	for (i = 0; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::TACKLE_BALL; }
}

void Goalkeeper::show(std::ostream & os) const
{
	os << " Type: Goalkeeper";
}
