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
class GamesByTimeDateNode;

class Game
{
friend class GamesByTimeDateNode;
public:
	// Constants
	static const Time MAX_GAME_LEN;

	// c-tors, d-tors
	Game(Team* team, const TimeAndDate& tad, int maxFans)
		: m_teams(NULL), m_referees(NULL), m_actualFans(0),
		m_maxFans(maxFans), m_timeAndDate(NULL),
	    m_fans(NULL)                                { m_refereesCount = 0; SetTimeAndDate(&tad);
	                                                  m_gameScore[0] = -1; m_gameScore[1] = -1; }
	Game(const Game& g)
		: m_teams(NULL), m_referees(NULL),
		  m_timeAndDate(NULL), m_fans(NULL),
		  m_actualFans(0)                           { *this = g; }
	~Game();
	// Operators
	bool        operator==(const Game& g)     const ;
	const Game& operator=(const Game& g);
	const Game& operator+=(const Referee* ref)      { AddReferee(ref);    return *this; }
	const Game& operator-=(const Referee* ref)      { RemoveReferee(ref); return *this; }
	const Game& operator+=(const Fan* fan)          { AddFan(fan);        return *this; }
	const Game& operator-=(const Fan* fan)          { RemoveFan(fan);     return *this; }


	// Methods
	int                 GetMaxFans()           const { return m_maxFans; }
	int                 GetActualFans()        const { return m_actualFans; }
	const Fan*          GetFans()              const { return m_fans; }
	int                 GetRefereesCount()     const { return m_refereesCount; }
	const Referee*      GetReferees()          const { return m_referees; }
	PlayerStats**       GetGameStats()         const { return m_playerStats; }
	const Team*         GetTeams()             const { return m_teams; }
	const Team*         GetWinner()            const ;
	const TimeAndDate*  GetTimeAndDate()       const { return m_timeAndDate; }
	const int*          GetGameScore()         const { return m_gameScore; }
	int                 GetTotalPlayers()      const ;

	void       StartGame()                    const;

	void       AddReferee(const Referee* ref);
	void       RemoveReferee(const Referee* ref);
	void       AddFan(const Fan* fan);
	void       RemoveFan(const Fan* fan);
	void       SetTime(const TimeAndDate& tad);

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
	int           m_gameScore[2];
	Team*         m_teams;
	Referee*      m_referees;
	int           m_refereesCount;
	int           m_maxFans;
	int           m_actualFans;
	PlayerStats** m_playerStats;
	TimeAndDate*  m_timeAndDate;
	Fan*          m_fans;

	// Methods
	void SetTimeAndDate(const TimeAndDate* tad);
	void SetPlayerStats(PlayerStats** ps, int count);
	void SetFans(const Fan* fans, int count);
	void SetReferees(const Referee* referees, int count);
	void SetTeams(const Team* teams);
	void DeletePlayerStats(PlayerStats** pStats);

	// Methods available to friend classes or disabled
	Game() : m_teams(NULL), m_referees(NULL), m_actualFans(0),
		m_maxFans(0), m_timeAndDate(NULL), m_fans(NULL)
	{ m_refereesCount = 0; m_gameScore[0] = -1; m_gameScore[1] = -1; }

};

#endif
