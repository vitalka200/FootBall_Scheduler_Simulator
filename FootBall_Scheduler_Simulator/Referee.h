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

	// Operators

	// Methods

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const CardType& ct)
	{os << Referee::CardNames[ct]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Referee& r);
private:
};
const char* Referee::CardNames[] = {"Yellow", "Red"};

#endif