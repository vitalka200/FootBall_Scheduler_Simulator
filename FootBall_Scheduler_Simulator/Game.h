#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include "TimeAndDate.h"
// Forward declaration
class Team;
class Referee;
class Player;

struct PlayerStats
{
public:
	Player*                 pl;
	Player::PlayerMovement* moves;
	int                     yellowCards;
	int                     redCards;
	int                     moves_number;
	~PlayerStats()          {delete []moves;}
private:
};

class Game
{
public:
	// c-tors, d-tors
	Game(Team* team, Referee* ref, int maxFans)
		: m_teams(NULL), m_referees(NULL),
		  m_maxFans(maxFans), m_timeAndDate(NULL)   { }
	Game(const Game& g)
		: m_teams(NULL), m_referees(NULL),
		  m_timeAndDate(NULL)                       { *this = g; }
	~Game()                                         { delete []m_playerStats; delete []m_referees; }
	// Operators
	const Game& operator=(const Game& g);
	const Game& operator+=(Team* t)                 { AddTeam(t);         return *this; }
	const Game& operator-=(const Team* t)           { RemoveTeam(t);      return *this; }
	const Game& operator+=(Trainer* t)              { AddTrainer(t);      return *this; }
	const Game& operator-=(const Trainer* t)        { RemoveTrainer(t);   return *this; }
	const Game& operator+=(Referee* ref)            { AddReferee(ref);    return *this; }
	const Game& operator-=(const Referee* ref)      { RemoveReferee(ref); return *this; }

	const Game& operator<<(const Time& t)           { AddTime(t);             return *this; }
	const Game& operator>>(const Time& t)           { RemoveTime(t);          return *this; }
	const Game& operator<<(const Date& d)           { AddDate(d);             return *this; }
	const Game& operator>>(const Date& d)           { RemoveDate(d);          return *this; }
	const Game& operator<<(const TimeAndDate& tad)  { AddTimeAndDate(tad);    return *this; }
	const Game& operator>>(const TimeAndDate& tad)  { RemoveTimeAndDate(tad); return *this; }

	// Methods
	const int  GetMaxFans()              const;
	void       StartGame()               const;

	void       AddTeam(Team* t);
	void       RemoveTeam(const Team* t);	
	void       AddReferee(Referee* ref);
	void       RemoveReferee(const Referee* ref);
	void       AddTrainer(Trainer* t);
	void       RemoveTrainer(const Trainer* t);

	void       AddTime(const Time& t);
	void       RemoveTime(const Time& t);
	void       AddDate(const Date& d);
	void       RemoveDate(const Date& d);
	void       AddTimeAndDate(const TimeAndDate& tad);
	void       RemoveTimeAndDate(const TimeAndDate& tad);

	const PlayerStats* GetGameStats()    const { return m_playerStats; }
	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
	Team*         m_teams;
	Referee*      m_referees;
	int           m_maxFans;
	PlayerStats*  m_playerStats;
	TimeAndDate*  m_timeAndDate;
};


#endif