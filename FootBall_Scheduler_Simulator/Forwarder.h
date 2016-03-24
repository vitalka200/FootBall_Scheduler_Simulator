#ifndef __FORWARDER_H
#define __FORWARDER_H

#include "Player.h"

class Forwarder : Player
{
public:
	// c-tors, d-tors
	Forwarder(const char* name, const char* f_name, long id, int pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { }
	Forwarder(const Forwarder& fr);
	// Operators

	// Methods

private:
};


#endif