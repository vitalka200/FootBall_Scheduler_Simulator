#include "Player.h"

const char* Player::LevelNames[] = { "Low", "Medium", "High" };
const char* Player::MovementsNames[] = { "Steal Ball", "Pass Ball", "Catch Ball", "Make Goal", "Tackle ball", "Run To Open Space", "Make Foul" };

bool Player::IsEqual(const Player* p) const
{
	return (
		this->GetId() == p->GetId() &&
		this->GetPLevel() == p->GetPLevel() &&
		strcmp(this->GetName(), p->GetName()) == 0 &&
		strcmp(this->GetFName(), p->GetFName()) == 0 &&
		this->GetTeam() == p->GetTeam()
		);
}
