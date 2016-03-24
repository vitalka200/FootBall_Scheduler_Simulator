#ifndef __DEFENDER_H
#define __DEFENDER_H

#include "Player.h"

class Defender : Player
{
public:
	// c-tors, d-tors
	Defender(const char* name, const char* f_name, long id, size_t pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { }
	Defender(const Defender& def);
	// Operators

	// Methods
private:

};

#endif