#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>

// Forward declaration
class  Player;
class  Trainer;
class  Referee;

class  PlayerStats
{
public:
	PlayerStats(Player* pl)
		: m_pl(NULL), m_moves(NULL)                   { m_redCards = 0; m_yellowCards = 0;
	                                                    m_numOfGoal = 0; m_movesNumber = 0;
														m_pl = pl; }
	~PlayerStats()                                    { delete []m_moves; }
	// Methods
	void AddMove(const Player::PlayerMovement* move)  ;
	void AddCard(const Referee::CardType* card)       { (&card) ? m_redCards++: m_yellowCards++; }
	void AddGoals()                                   { m_numOfGoal++; }

	int  GetYellowCards()                       const { return m_yellowCards; }
	int  GetRedCards()                          const { return m_redCards; }
	int  GetGoals()                             const { return m_numOfGoal; }
private:
	// Disable copy and equality
	PlayerStats(const PlayerStats& ps);
	const PlayerStats& operator=(const PlayerStats& ps);

	// Data Members
	Player*                 m_pl;
	Player::PlayerMovement* m_moves;
	int                     m_yellowCards;
	int                     m_redCards;
	int                     m_numOfGoal;
	int                     m_movesNumber;
};

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
	// Change mode of team: Attacking or Defending
	const Team& operator++()                 { m_isAttacking = !m_isAttacking;    return *this; }

	Player&     operator[](int index);
	// Methods
	void               AddPlayer(Player* p);
	void               RemovePlayer(const Player* p);
	void               AddTrainer(Trainer* t);
	void               RemoveTrainer(const Trainer* t);
	const PlayerStats* GetStats()                       const { return m_playerStats;};
	void               SetName(const char* name)              { delete []m_name; m_name = strdup(name); }
	const char*        GetName()                        const { return m_name; }
	bool               IsAttacking()                    const { return m_isAttacking; }

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Team& t);

private:
	Player*      m_players;
	Trainer*     m_trainers;
	char*        m_name;
	PlayerStats* m_playerStats;
	bool         m_isAttacking;
};

#endif