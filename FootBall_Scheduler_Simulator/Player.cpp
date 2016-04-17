#include "Player.h"

const char* Player::LevelNames[] = { "Low", "Medium", "High" };
const char* Player::MovementsNames[] = { "Steal Ball", "Pass Ball", "Catch Ball", "Make Goal", "Tackle ball", "Run To Open Space", "Make Foul" };

bool Player::IsEqual(const Player* p) const
{
	return (
		Person::operator == (*(p)) &&
		this->GetPLevel() == p->GetPLevel() &&
		this->GetTeam() == p->GetTeam()
		);
}
