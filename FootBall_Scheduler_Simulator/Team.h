#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>
#include <string>
#include <vector>

#include "Trainer.h"
#include "Referee.h"
// Forward declaration
//class  Trainer;
//class  Referee;
enum   CardType;
class  Player;
class  Goalkeeper;
class  Game;
enum   PlayerMovement;

class  PlayerStats
{
public:
	PlayerStats(Player* pl)
		: m_pl(NULL)                                  { m_redCards = 0;  m_yellowCards = 0;
	                                                    m_numOfGoal = 0; m_pl = pl; }
	PlayerStats(const PlayerStats& ps)
		: m_pl(NULL)                                   { *this = ps; }
	const PlayerStats& operator=(const PlayerStats& ps);

	~PlayerStats()                                      {  }
	// Methods
	void AddMove(const PlayerMovement move);
	void AddCard(const CardType card);
	void AddGoals()                                      { m_numOfGoal++; }

	int                   GetYellowCards()         const { return m_yellowCards; }
	int                   GetRedCards()            const { return m_redCards; }
	int                   GetGoals()               const { return m_numOfGoal; }
	const std::vector<PlayerMovement> GetMoves()   const { return m_moves; }
	const Player*                     GetPlayer()  const { return m_pl; }
private:
	// Data Members
	Player*                      m_pl;
	std::vector<PlayerMovement>  m_moves;
	int                          m_yellowCards;
	int                          m_redCards;
	int                          m_numOfGoal;
};

class Team
{
public:
	// c-tors, d-tors
	Team(const std::string name = " ")
		: m_goalkeeper(NULL), m_name(name)     { SetName(name); m_goalkeeperNum = -1;
	                                             m_isAttacking = false; }
	// Disable Copy and assigment
	Team(const Team& t)
		: m_goalkeeper(NULL), m_name(t.m_name) { *this = t; }
	const Team& Team::operator=(const Team& t);

	~Team();
	// Operators
	const Team&   operator+=(Player* p)        { AddPlayer(p);     return *this; }
	const Team&   operator-=(const Player* p)  { RemovePlayer(p);  return *this; }
	const Team&   operator+=(Trainer* t)       { AddTrainer(t);    return *this; }
	const Team&   operator-=(const Trainer* t) { RemoveTrainer(t); return *this; }

	bool          operator==(const Team& t)    { return this->GetName() == t.GetName(); }
	bool          operator!=(const Team& t)    { return !(*this == t); }

	Player*       operator[](int index);
	// Methods
	void                AddPlayer(Player* p);
	void                RemovePlayer(const Player* p);
	int                 GetPlayerNum()                   const { return m_players.size(); }
	void                AddTrainer(Trainer* t);
	void                RemoveTrainer(const Trainer* t);
	int                 GetTrainersNum()                 const { return m_trainers.size(); }
	const std::vector<Trainer>      GetTrainers()                    const { return m_trainers; }
	std::vector<PlayerStats*>       GetStats()                       const { return m_playerStats;}
	PlayerStats*         GetPlayerStats(const Player* p)  const ;
	Player*             GetGoalkeeper()                  const { return m_goalkeeper; }
	int                 GetGoalKeeperIndex()             const { return m_goalkeeperNum; }
	const std::string         GetName()                        const { return m_name; }
	bool                IsAttacking()                    const { return m_isAttacking; }
	void                SetIsAtacking(bool isAtacking)         { m_isAttacking = isAtacking; }

	void                AddPlayerStat(const Player* p, const PlayerMovement move, bool isActualGoal = false);

	void                SetName(const std::string name)              { m_name = name; }

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Team& t)
	{
		os << "Name: " << t.GetName() << " PlayerNum: " << t.GetPlayerNum();
		return os;
	}

private:
	// Members
	std::vector<Player*>      m_players;
	Player*       m_goalkeeper;
	int           m_goalkeeperNum;
	std::vector<Trainer>      m_trainers;
	std::string         m_name;
	std::vector<PlayerStats*> m_playerStats;
	bool          m_isAttacking;

	// Methods
	void SetPlayers(std::vector<Player*> players);
	void SetTrainers(const std::vector<Trainer> trainers);
	void SetPlayerStats(std::vector<PlayerStats*> ps);
	void DeletePlayers(std::vector<Player*> players);
	void DeletePlayerStats(std::vector<PlayerStats*> pStats);
};

#endif