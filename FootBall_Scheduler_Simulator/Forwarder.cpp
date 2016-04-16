#include "Forwarder.h"

const PlayerMovement Forwarder::MakeMove(bool hasBall)
{
	return PlayerMovement::CATCH_BALL;
}

void Forwarder::CreateAllowedMoves()
{
	m_allowed_moves.numberOfMoves = 6;
	m_allowed_moves.moves = new PlayerMovement[m_allowed_moves.numberOfMoves];

	m_allowed_moves.moves[0] = PlayerMovement::PASS_BALL;
	m_allowed_moves.moves[1] = PlayerMovement::TACKLE_BALL;
	m_allowed_moves.moves[2] = PlayerMovement::RUN_TO_OPEN_SPACE;
	m_allowed_moves.moves[3] = PlayerMovement::STEAL_BALL;
	m_allowed_moves.moves[4] = PlayerMovement::MAKE_GOAL;
	m_allowed_moves.moves[5] = PlayerMovement::MAKE_FOUL;
}

void Forwarder::show(std::ostream & os) const
{
	os << std::endl << "Type: Forwarder";
}