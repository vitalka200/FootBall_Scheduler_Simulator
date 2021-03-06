#ifndef __FAN_H
#define __FAN_H

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

// Forward declaration
class Team;

class Fan : public Person
{
public:
	// c-tors, d-tors
	Fan(const std::string& name = " ", const std::string& f_name = " ", long id = -1, Team* team = NULL) 
	    : Person(name, f_name, id), m_team(NULL) {SetTeam(team);}
	// Operators

	// Methods
	void         SetTeam(Team* team) { m_team = team; }
	void         Cheer();
	const Team*  GetTeam()           { return m_team; }
	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Fan& f)
	{ os << "Fan " << (Person)f; return os; }

private:
	Team* m_team;

};


#endif