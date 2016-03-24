#ifndef __GOALKEEPER_H
#define __GOALKEEPER_H

#include "Player.h"

class Goalkeeper : Player
{
public:
	// c-tors, d-tors
	Goalkeeper(const char* name, const char* f_name, long id, int pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { }
	Goalkeeper(const Goalkeeper& gk);
	// Operators

	// Methods
private:

};


#endif