#ifndef __TRAINER_H
#define __TRAINER_H

#include <iostream>
#include "Person.h"

enum TrainerDecision { CHANGE_PLAYER, MOVE_PLAYER };

class Trainer: public Person
{
public:
	static const char* TrainerDecisionNames[];
	// c-tors, d-tors
	Trainer(const char* name, const char* f_name, long id) 
		: Person(name, f_name, id) { }
	
	// Operators
	
	// Methods
	TrainerDecision MakeDecision();
	
	
	// Methods overrides
	friend std::ostream& operator<<(std::ostream& os, const TrainerDecision& td)
	{os << Trainer::TrainerDecisionNames[td]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Trainer& t)
	{ os << (Person)t; return os; }

private:
	
};

#endif
