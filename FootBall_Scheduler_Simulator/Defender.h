#ifndef __DEFENDER_H
#define __DEFENDER_H

#include <iostream>
#include "Player.h"

class Defender : public Player
{
public:
	// c-tors, d-tors
	Defender(const char* name, const char* f_name, long id, size_t pnum, Team* team, PlayerLevel pl = LOW) 
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
