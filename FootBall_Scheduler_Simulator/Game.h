#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include "TimeAndDate.h"
// Forward declaration
class Team;
class Referee;
class Player;
class PlayerStats;
class Trainer;
class Fan;

class Game
{
public:
	// c-tors, d-tors
	Game(Team* team, const TimeAndDate& tad, int maxFans)
		: m_teams(NULL), m_referees(NULL), 
		m_maxFans(maxFans), m_timeAndDate(NULL),
	    m_fans(NULL)                                { m_refereesCount = 0; SetTimeAndDate(tad);
	                                                  m_gameScore[0] = 0; m_gameScore[1] = 0; }
	Game(const Game& g)
		: m_teams(NULL), m_referees(NULL),
		  m_timeAndDate(NULL), m_fans(NULL)         { *this = g; }
	~Game()                                         { delete []m_playerStats; delete []m_referees; }
	// Operators
	bool        operator==(const Game& g)     const ;
	const Game& operator=(const Game& g);
	const Game& operator+=(Team* t)                 { AddTeam(t);         return *this; }
	const Game& operator-=(const Team* t)           { RemoveTeam(t);      return *this; }
	const Game& operator+=(Trainer* t)              { AddTrainer(t);      return *this; }
	const Game& operator-=(const Trainer* t)        { RemoveTrainer(t);   return *this; }
	const Game& operator+=(Referee* ref)            { AddReferee(ref);    return *this; }
	const Game& operator-=(const Referee* ref)      { RemoveReferee(ref); return *this; }
	const Game& operator+=(Fan* fan)                { AddFan(fan);        return *this; }
	const Game& operator-=(const Fan* fan)          { RemoveFan(fan);     return *this; }

	const Game& operator<<(const Time& t)           { AddTime(t);             return *this; }
	const Game& operator>>(const Time& t)           { RemoveTime(t);          return *this; }
	const Game& operator<<(const Date& d)           { AddDate(d);             return *this; }
	const Game& operator>>(const Date& d)           { RemoveDate(d);          return *this; }
	const Game& operator<<(const TimeAndDate& tad)  { AddTimeAndDate(tad);    return *this; }
	const Game& operator>>(const TimeAndDate& tad)  { RemoveTimeAndDate(tad); return *this; }

	// Methods
	int                GetMaxFans()                   const { return m_maxFans; }
	const Fan*         GetFans()                      const { return m_fans; }
	int                GetRefereesCount()             const { return m_refereesCount; }
	const Referee*     GetReferees()                  const { return m_referees; }
	const PlayerStats* GetGameStats()                 const { return m_playerStats; }
	const Team*        GetWinner()                    const ;
	const TimeAndDate* GetTimeAndDate()               const { return m_timeAndDate; }

	void       StartGame()                    const;

	void       AddTeam(Team* t);
	void       RemoveTeam(const Team* t);	
	void       AddReferee(Referee* ref);
	void       RemoveReferee(const Referee* ref);
	void       AddTrainer(Trainer* t);
	void       RemoveTrainer(const Trainer* t);
	void       AddFan(Fan* fan);
	void       RemoveFan(const Fan* fan);


	void       AddTime(const Time& t);
	void       RemoveTime(const Time& t);
	void       AddDate(const Date& d);
	void       RemoveDate(const Date& d);
	void       AddTimeAndDate(const TimeAndDate& tad);
	void       RemoveTimeAndDate(const TimeAndDate& tad);

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
	int           m_gameScore[2];
	Team*         m_teams;
	Referee*      m_referees;
	int           m_refereesCount;
	int           m_maxFans;
	PlayerStats*  m_playerStats;
	TimeAndDate*  m_timeAndDate;
	Fan*          m_fans;

	void SetTimeAndDate(const TimeAndDate& tad);
};

#endif
