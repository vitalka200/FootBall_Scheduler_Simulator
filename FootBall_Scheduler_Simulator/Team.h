#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>

// Forward declaration
class  Player;
class  Trainer;
struct PlayerStats;

class Team
{
public:
	// c-tors, d-tors
	Team(const char* name)
		: m_name(NULL),    m_trainers(NULL),
		  m_players(NULL), m_playerStats(NULL)          { SetName(name); }
	Team(const Team& t)
		: m_name(NULL),    m_trainers(NULL),
		  m_players(NULL), m_playerStats(NULL)          { *this = t; }
	~Team()                                             { delete []m_name;     delete []m_players;
                                                          delete []m_trainers; delete []m_playerStats;}
	// Operators
	const Team& operator=(const Team& t);
	const Team& operator+=(Player* p)        { AddPlayer(p);     return *this; }
	const Team& operator-=(const Player* p)  { RemovePlayer(p);  return *this; }
	const Team& operator+=(Trainer* t)       { AddTrainer(t);    return *this; }
	const Team& operator-=(const Trainer* t) { RemoveTrainer(t); return *this; }
	Player& operator[](int index);
	// Methods
	void               AddPlayer(Player* p);
	void               RemovePlayer(const Player* p);
	void               AddTrainer(Trainer* t);
	void               RemoveTrainer(const Trainer* t);
	const PlayerStats* GetStats()                       const { return m_playerStats;};
	void               SetName(const char* name)              { delete []m_name; m_name = strdup(name); }
	const char*        GetName()                        const { return m_name; }

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Team& t);

private:
	Player*  m_players;
	Trainer* m_trainers;
	char* m_name;
	PlayerStats* m_playerStats;
};

#endif