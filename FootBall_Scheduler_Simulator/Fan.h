#ifndef __FAN_H
#define __FAN_H

#include <iostream>
#include "Person.h"

// Forward declaration
class Team;

class Fan : Person
{
public:
	// c-tors, d-tors
	Fan(const char* name, const char* f_name, long id, Team* team) 
	    : Person(name, f_name, id), m_team(NULL) {SetTeam(team);}
	// Operators

	// Methods
	void         SetTeam(Team* team) { m_team = team; }
	const Team*  GetTeam()           { return m_team; }
	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Fan& f);
private:
	Team* m_team;

};


#endif