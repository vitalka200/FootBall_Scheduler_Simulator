#ifndef __GOALKEEPER_H
#define __GOALKEEPER_H

#include <iostream>
#include "Player.h"

class Goalkeeper : public Player
{
public:
	// c-tors, d-tors
	Goalkeeper(const char* name, const char* f_name, long id, int pnum, Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, pnum, team, pl) { CreateAllowedMoves(); }
	// Operators

	// Methods

	// Method Overrides
	virtual const PlayerMovement  MakeMove(bool hasBall);

private:
	virtual void                  CreateAllowedMoves();
	virtual void                  show(std::ostream& os)  const;

};


#endif