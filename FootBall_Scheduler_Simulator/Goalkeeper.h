#ifndef __GOALKEEPER_H
#define __GOALKEEPER_H

#include <iostream>
#include "Player.h"

class Goalkeeper : Player
{
public:
	// c-tors, d-tors
	Goalkeeper(const char* name, const char* f_name, long id, int pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { }
	// Operators

	// Methods

	// Method Overrides
	const PlayerMovement MakeMove();
	friend std::ostream& operator<<(std::ostream& os, const Goalkeeper& g);
private:

};


#endif