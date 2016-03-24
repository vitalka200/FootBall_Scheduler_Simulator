#ifndef __FAN_H
#define __FAN_H

#include "Person.h"

// Forward declaration
class Team;

class Fan : Person
{
public:
	// c-tors, d-tors
	Fan(const char* name, const char* f_name, long id, Team* team) 
	    : Person(name, f_name, id), m_team(NULL) {SetTeam(team);}
	Fan(const Fan& f);
	// Operators

	// Methods
	void SetTeam(Team* team);

private:
	Team* m_team;

};


#endif