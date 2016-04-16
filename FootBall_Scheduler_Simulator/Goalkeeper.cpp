#include "Goalkeeper.h"

const PlayerMovement Goalkeeper::MakeMove(bool hasBall)
{
	return PlayerMovement::CATCH_BALL;
}

void Goalkeeper::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = 3;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	m_allowed_moves.moves[0] = PlayerMovement::CATCH_BALL;
	m_allowed_moves.moves[1] = PlayerMovement::PASS_BALL;
	m_allowed_moves.moves[2] = PlayerMovement::TACKLE_BALL;
}

void Goalkeeper::show(std::ostream & os) const
{
	os << std::endl << "Type: Defender";
}
