#ifndef __TRAINER_H
#define __TRAINER_H

#include <iostream>
#include "Person.h"
#include "Team"
class Trainer: Person
{
public:
	enum TrainerDecision {CHANGE_PLAYER, MOVE_PLAYER};
	static const char* TrainerDecisionNames[];
	Team	m_team;
	// c-tors, d-tors
	Trainer(const char* name, const char* f_name, long id) 
		: Person(name, f_name, id) { }
	~Trainer()			{delete name;}
	
	// Operators
	const Trainer operator+=()	{MakeDecision();}
	
	// Methods
	TrainerDecision MakeDecision();
	addTeam(Team& team);
	
	
	// Methods overrides
	friend std::ostream& operator<<(std::ostream& os, const TrainerDecision& td)
	{os << Trainer::TrainerDecisionNames[td]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Trainer& t);

private:
	
};
const char* Trainer::TrainerDecisionNames[] = {"Change Player", "Move Player"};

#endif
