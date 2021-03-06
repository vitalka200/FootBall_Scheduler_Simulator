#ifndef __DEFENDER_H
#define __DEFENDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

class Defender : public Player
{
public:
	// c-tors, d-tors
	Defender(const std::string& name, const std::string& f_name, long id,  Team* team, PlayerLevel pl = LOW) 
		: Player(name, f_name, id, team, pl) { CreateAllowedMoves(); }
	// Operators
	
	// Methods
	
	// Method Overrides
	virtual const PlayerMovement  MakeMove(bool hasBall);
	
private:
	virtual void                  CreateAllowedMoves();
	virtual void                  show(std::ostream& os)  const;

};

#endif
