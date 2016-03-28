#ifndef __STADIUM_H
#define __STADIUM_H

#include <iostream>

class Game;
class TimeAndDate;
class Time;
class Date;

class Stadium
{
public:
	// c-tors, d-tors
	Stadium(const char* name, int maxFans)
		: m_name(NULL),  m_maxFans(maxFans),
		  m_games(NULL), m_schedule(NULL)      { SetName(name); };
	Stadium(const Stadium& s)
		: m_name(NULL), m_games(NULL),
		  m_schedule(NULL)                     { *this = s; }
	~Stadium()                                 { delete []m_name; delete[] m_schedule; }
	// Operators
	const Stadium& operator=(const Stadium& s);
	// Methods
	void        SetName(const char* name)      { delete []m_name; m_name = strdup(name); }
	void        SetMaxFans(int maxFans)        { m_maxFans = maxFans; }
	const char* GetName()                const { return m_name; }
	const int   GetMaxFans()             const { return m_maxFans; }
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Stadium& s);
private:
	char* m_name;
	int   m_maxFans;
	
	TimeAndDate* m_schedule;
	Game*        m_games;
};


#endif