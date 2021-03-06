#include "Defender.h"

#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>

const PlayerMovement Defender::MakeMove(bool hasBall)
{
	if (hasBall)
	{
		// If we have ball, we pass it
		return PlayerMovement::PASS_BALL;
	}
	return m_allowed_moves[rand() % (m_allowed_moves.size() - (m_plevel + 1)*PASS_BALL)];
}

void Defender::CreateAllowedMoves()
{
	int numberOfMoves = (m_plevel+1)*PASS_BALL + (m_plevel+1)*TACKLE_BALL + (m_plevel+1)*RUN_TO_OPEN_SPACE;
	m_allowed_moves = std::vector<PlayerMovement>(numberOfMoves);

	int i = 0;
	int j = 0;
	for (i = 0; i < (m_plevel + 1)*RUN_TO_OPEN_SPACE; i++)
	{ m_allowed_moves[j++] = PlayerMovement::RUN_TO_OPEN_SPACE; }

	for (i = 0; i < (m_plevel + 1)*TACKLE_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::TACKLE_BALL; }

	for (i = 0; i < (m_plevel + 1)*PASS_BALL; i++)
	{ m_allowed_moves[j++] = PlayerMovement::PASS_BALL; }
}

void Defender::show(std::ostream & os) const
{
	os << " Type: Defender";
}