#ifndef __DEFENDER_H
#define __DEFENDER_H

#include <iostream>
#include "Player.h"

class Defender : Player
{
public:
	// c-tors, d-tors
	Defender(const char* name, const char* f_name, long id, size_t pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { }
	// Operators
	const Defender& operator>=(Player& other);
	// Methods
	
	// Method Overrides
	const PlayerMovement MakeMove();
	friend std::ostream& operator<<(std::ostream& os, const Defender& def);
private:

};

#endif
