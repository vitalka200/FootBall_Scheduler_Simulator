#ifndef __TRAINER_H
#define __TRAINER_H

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

enum TrainerDecision { NO_DECISION, CHANGE_PLAYER };

class Trainer: public Person
{
public:
	static const std::string TrainerDecisionNames[];
	// c-tors, d-tors
	Trainer(const std::string& name = " ", const std::string& f_name = " ", long id = -1) 
		: Person(name, f_name, id) { }
	
	// Operators
	
	// Methods
	TrainerDecision MakeDecision(bool isTeamAttacking) const;
	
	
	// Methods overrides
	friend std::ostream& operator<<(std::ostream& os, const TrainerDecision& td)
	{os << Trainer::TrainerDecisionNames[td]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Trainer& t)
	{ os << (Person)t; return os; }

private:
	
};

#endif
