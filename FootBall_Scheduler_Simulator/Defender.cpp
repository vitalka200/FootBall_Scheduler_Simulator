#include "Defender.h"

const PlayerMovement Defender::MakeMove(bool hasBall)
{
	return PlayerMovement::STEAL_BALL;
}

void Defender::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = 4;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	m_allowed_moves.moves[0] = PlayerMovement::PASS_BALL;
	m_allowed_moves.moves[1] = PlayerMovement::TACKLE_BALL;
	m_allowed_moves.moves[2] = PlayerMovement::RUN_TO_OPEN_SPACE;
	m_allowed_moves.moves[3] = PlayerMovement::STEAL_BALL;
}

void Defender::show(std::ostream & os) const
{
	os << std::endl << "Type: Forwarder";
}