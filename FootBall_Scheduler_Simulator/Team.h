#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>

// Forward declaration
class  Trainer;
class  Referee;
enum   CardType;
class  Player;
class  Goalkeeper;
enum   PlayerMovement;

class  PlayerStats
{
friend class Team;
public:
	PlayerStats(Player* pl)
		: m_pl(NULL), m_moves(NULL)                   { m_redCards = 0; m_yellowCards = 0;
	                                                    m_numOfGoal = 0; m_movesNumber = 0;
														m_pl = pl; }
	PlayerStats(const PlayerStats& ps)
		: m_pl(NULL), m_moves(NULL)                   { *this = ps; }
	const PlayerStats& operator=(const PlayerStats& ps);

	~PlayerStats()                                    { delete []m_moves; }
	// Methods
	void AddMove(const PlayerMovement move);
	void AddCard(const CardType card);
	void AddGoals()                                   { m_numOfGoal++; }

	int                   GetYellowCards()      const { return m_yellowCards; }
	int                   GetRedCards()         const { return m_redCards; }
	int                   GetGoals()            const { return m_numOfGoal; }
	const PlayerMovement* GetMoves()            const { return m_moves; }
	const Player*         GetPlayer()           const { return m_pl; }
private:
	// Data Members
	Player*                 m_pl;
	PlayerMovement*         m_moves;
	int                     m_yellowCards;
	int                     m_redCards;
	int                     m_numOfGoal;
	int                     m_movesNumber;
};

class Team
{
public:
	// c-tors, d-tors
	Team(const char* name = " ")
		: m_name(NULL), m_trainers(NULL),
		m_players(NULL), m_playerStats(NULL),
		m_goalkeeper(NULL)                    { SetName(name); m_numOfPlayers = 0; m_goalkeeperNum = -1;
	                                             m_numOfTrainers = 0; m_isAttacking = false; }
	// Disable Copy and assigment
	Team(const Team& t)
		: m_name(NULL), m_trainers(NULL),
		m_players(NULL), m_playerStats(NULL),
		m_goalkeeper(NULL)                    { *this = t; }
	const Team& Team::operator=(const Team& t);

	~Team();
	// Operators
	const Team&   operator+=(Player* p)        { AddPlayer(p);     return *this; }
	const Team&   operator-=(const Player* p)  { RemovePlayer(p);  return *this; }
	const Team&   operator+=(Trainer* t)       { AddTrainer(t);    return *this; }
	const Team&   operator-=(const Trainer* t) { RemoveTrainer(t); return *this; }

	bool          operator==(const Team& t)    { return strcmp(this->GetName(), t.GetName()) == 0; }
	bool          operator!=(const Team& t)    { return !(*this == t); }

	Player*       operator[](int index);
	// Methods
	void                AddPlayer(Player* p);
	void                RemovePlayer(const Player* p);
	int                 GetPlayerNum()                   const { return m_numOfPlayers; }
	void                AddTrainer(Trainer* t);
	void                RemoveTrainer(const Trainer* t);
	int                 GetTrainersNum()                 const { return m_numOfTrainers; }
	const Trainer*      GetTrainers()                    const { return m_trainers; }
	PlayerStats**       GetStats()                       const { return m_playerStats;}
	PlayerStats*        GetPlayerStats(const Player* p)  const ;
	const Player*       GetGoalkeeper()                  const { return m_goalkeeper; }
	int                 GetGoalKeeperIndex()             const { return m_goalkeeperNum; }
	const char*         GetName()                        const { return m_name; }
	bool                IsAttacking()                    const { return m_isAttacking; }
	void                SetIsAtacking(bool isAtacking)         { m_isAttacking = isAtacking; }

	void                AddPlayerStat(const Player* p, const PlayerMovement move, bool isActualGoal = false);

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Team& t)
	{
		os << "Name: " << t.GetName() << " PlayerNum: " << t.GetPlayerNum();
		return os;
	}

private:
	// Members
	Player**      m_players;
	Player*       m_goalkeeper;
	int           m_goalkeeperNum;
	int           m_numOfPlayers;
	Trainer*      m_trainers;
	int           m_numOfTrainers;
	char*         m_name;
	PlayerStats** m_playerStats;
	bool          m_isAttacking;

	// Methods
	void SetName(const char* name)                       { delete m_name; m_name = strdup(name); }
	void SetPlayers(Player** players, int count);
	void SetTrainers(const Trainer* trainers, int count);
	void SetPlayerStats(PlayerStats** ps, int count);
	void DeletePlayers(Player** players);
	void DeletePlayerStats(PlayerStats** pStats);
};

#endif