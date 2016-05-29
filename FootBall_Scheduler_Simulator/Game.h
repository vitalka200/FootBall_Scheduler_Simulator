#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <string>
#include <vector>
#include "TimeAndDate.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Fan.h"
// Forward declaration
class Team;
class PlayerStats;

class Game
{
public:
	// Constants
	static const Time MAX_GAME_LEN;

	// c-tors, d-tors
	Game() : m_wasStarted(false), m_maxFans(0), m_timeAndDate(NULL), m_gameScore(NULL)
	{ CreateGameScore(); }

	Game(std::vector<Team*> teams, const TimeAndDate& tad, int maxFans)
		: m_maxFans(maxFans), m_timeAndDate(NULL),
		m_wasStarted(false), m_gameScore(NULL)
	                                                               { SetTimeAndDate(&tad); SetTeams(teams);
	                                                                 CreateGameScore(); }
	Game(const Game& g)
		: m_timeAndDate(NULL), m_gameScore(NULL) { *this = g; }
	~Game();
	// Operators
	bool        operator==(const Game& g)     const ;
	const Game& operator=(const Game& g);
	const Game& operator+=(const Referee& ref)      { AddReferee(ref);    return *this; }
	const Game& operator-=(const Referee& ref)      { RemoveReferee(ref); return *this; }
	const Game& operator+=(const Fan& fan)          { AddFan(fan);        return *this; }
	const Game& operator-=(const Fan& fan)          { RemoveFan(fan);     return *this; }


	// Methods
	int                        GetMaxFans()           const { return m_maxFans; }
	int                        GetActualFans()        const { return m_fans.size(); }
	const std::vector<Fan>     GetFans()              const { return m_fans; }
	int                        GetRefereesCount()     const { return m_referees.size(); }
	std::vector<Referee>       GetReferees()          const { return m_referees; }
	std::vector<PlayerStats*>  GetGameStats()         const { return m_playerStats; }
	std::vector<Team*>         GetTeams()             const { return m_teams; }
	Team*                      GetWinner()            const ;
	const TimeAndDate*         GetTimeAndDate()       const { return m_timeAndDate; }
	const int*                 GetGameScore()         const { return m_gameScore; }
	int                        GetTotalPlayers()      const ;

	void       StartGame();

	void       AddReferee(const Referee& ref);
	void       RemoveReferee(const Referee& ref);
	void       AddFan(const Fan& fan);
	void       RemoveFan(const Fan& fan);
	void       SetTime(const TimeAndDate& tad);

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
	int*                      m_gameScore;
	bool                      m_wasStarted;
	std::vector<Team*>        m_teams;
	std::vector<Referee>      m_referees;
	int                       m_maxFans;
	std::vector<PlayerStats*> m_playerStats;
	TimeAndDate*              m_timeAndDate;
	std::vector<Fan>          m_fans;

	// Methods
	PlayerStats* GetPlayerStats(const Player* p);
	void         SetTimeAndDate(const TimeAndDate* tad);
	void         SetPlayerStats(const std::vector<PlayerStats*>& ps);
	void         SetFans(const std::vector<Fan>& fans);
	void         SetReferees(const std::vector<Referee>& referees);
	void         SetTeams(std::vector<Team*> teams);
	void         CreateGameScore();
	void         SetGameScore(int* gameScore);
	void         DeletePlayerStats(std::vector<PlayerStats*> pStats);
	bool         CanStartGame();

};

#endif
