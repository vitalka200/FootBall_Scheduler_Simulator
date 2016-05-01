#ifndef __REFEREE_H
#define __REFEREE_H

#include <iostream>
#include "Person.h"

enum CardType { NO_CARD, YELLOW, RED };

class Referee : public Person
{
public:
	static const char* CardNames[];
	// c-tors, d-tors
	
	Referee(const char* name = " ", const char* f_name = " ", long id = -1) 
		: Person(name, f_name, id) { }
	
	// Operators
	
	// Methods
	CardType MakeDecision();
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const CardType& ct)
	{os << Referee::CardNames[ct]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Referee& r)
	{ os << "Referee " << (Person)r; return os; }
private:
};

#endif
