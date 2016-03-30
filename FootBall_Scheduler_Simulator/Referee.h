#ifndef __REFEREE_H
#define __REFEREE_H

#include <iostream>
#include "Person.h"

class Referee : Person
{
public:
	enum CardType {YELLOW, RED};
	static const char* CardNames[];
	// c-tors, d-tors
	
	Referee(const char* name, const char* f_name, long id) 
		: Person(name, f_name, id) { }
	
	~Referee()			{delete []name;}
	// Operators
	
	// Methods
	GiveCardAccordigntoAction(Player::Action Act)	{}    //Needed?
	GiveCardonRandom()				{}
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const CardType& ct)
	{os << Referee::CardNames[ct]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Referee& r);
private:
};
const char* Referee::CardNames[] = {"Yellow", "Red"};

#endif
