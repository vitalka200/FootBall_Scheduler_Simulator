#include "Player.h"
#include "Team.h"
#include <string>
#include <vector>

const std::string Player::LevelNames[]     = { "Low", "Medium", "High" };
const std::string Player::MovementsNames[] = { "No Move", "Steal Ball", "Pass Ball", "Catch Ball", "Make Goal", "Tackle ball", "Run To Open Space", "Make Foul", "Miss Ball" };

bool Player::IsEqual(const Player* p) const
{
	return (
		((Person&)*this) == ((Person&)*p) &&
		this->GetPLevel() == p->GetPLevel()
		);
}

const Player& Player::operator=(const Player& p)
{
	if (*this != p)
	{
		Person::operator=(p);
		m_plevel = p.m_plevel;

		m_allowed_moves = p.m_allowed_moves;
	}
	return *this;
}

void Player::SetLevel(PlayerLevel pl)
{
	if (pl < LOW || pl > HIGH)
	{ m_plevel = LOW; }
	else
	{ m_plevel = pl; }
}

//void Player::SetAllowedMoves(AllowedMoves allowedMoves)
//{
//	//if (m_allowed_moves.numberOfMoves > 0) 
//	//{ delete[] m_allowed_moves.moves; }
//	m_allowed_moves.moves = std::vector<PlayerMovement>(allowedMoves.numberOfMoves);
//	m_allowed_moves.moves = new PlayerMovement[allowedMoves.numberOfMoves];
//	m_allowed_moves.numberOfMoves = allowedMoves.numberOfMoves;
//
//	for (int i = 0; i < allowedMoves.numberOfMoves; i++)
//	{ m_allowed_moves.moves[i] = allowedMoves.moves[i]; }
//}

std::ostream & operator<<(std::ostream& os, const Player& p)
{
	os << (Person)p;
	os << " Level: " << p.LevelNames[p.m_plevel];
	p.show(os);
	os << ". Team: " << *(p.GetTeam());
	return os;
}
