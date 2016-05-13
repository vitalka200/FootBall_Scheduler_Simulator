#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include "Person.h"

// Forward declaration
class Team;

enum PlayerMovement { NO_MOVE, STEAL_BALL,  TACKLE_BALL, CATCH_BALL, MISS_BALL, MAKE_GOAL, PASS_BALL, RUN_TO_OPEN_SPACE };
enum PlayerLevel    { LOW, MEDIUM, HIGH };

class Player : public Person
{
friend class Team;
public:
	// Structs
	static const char* MovementsNames[];

	static const char* LevelNames[];

	struct AllowedMoves { PlayerMovement* moves;int numberOfMoves; };

	// c-tors, d-tors
	Player(const char* name, const char* f_name, long id, Team* team, PlayerLevel pl = LOW) 
	    : Person(name, f_name, id), m_team(NULL)                      { SetTeam(team); SetLevel(pl); m_plevel = pl; m_allowed_moves.numberOfMoves = 0; }
	Player(const Player& p)
		: Person(p.m_name, p.m_fname, p.m_id), m_team(NULL)           { m_allowed_moves.moves = NULL; m_allowed_moves.numberOfMoves = p.m_allowed_moves.numberOfMoves;
	                                                                    m_plevel = p.m_plevel; Person::operator=(p); }
	virtual ~Player()                                                 {if (m_allowed_moves.numberOfMoves) delete []m_allowed_moves.moves;}
	// Methods
	void                         SetTeam(Team* team)                  { m_team = team; }
	void                         SetLevel(PlayerLevel pl)             { m_plevel = pl; }
	const PlayerLevel            GetPLevel()                    const { return m_plevel; }
	Team*                        GetTeam()                      const { return m_team; }
	virtual const PlayerMovement MakeMove(bool hasBall)                =0;
	bool                         IsEqual(const Player* p)       const ;

	// Operators
	bool          operator==(const Player& p)                  { return m_plevel == p.m_plevel; }
	bool          operator!=(const Player& p)                  { return !(*this == p); }
	bool          operator>(const Player& p)                   { return m_plevel > p.m_plevel; }
	bool          operator>=(const Player& p)                  { return (*this == p) || (*this > p); }
	bool          operator<(const Player& p)                   { return m_plevel < p.m_plevel;  }
	bool          operator<=(const Player& p)                  { return (*this == p) || (*this < p); }

	// Methods overrides
	friend std::ostream& operator<<(std::ostream& os, const PlayerMovement& pm)
	{os << Player::MovementsNames[pm]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const PlayerLevel& pl)
	{os << Player::LevelNames[pl]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Player& p)
	{ 
		os << "Name: " << p.GetName() << " FName: " << p.GetFName() << " Level: " << Player::LevelNames[p.GetPLevel()];
		p.show(os); return os;
	}

protected:
	Team*        m_team;
	PlayerLevel  m_plevel; // Player Level
	AllowedMoves m_allowed_moves;

	// Methods
	virtual void CreateAllowedMoves()         =0;
	virtual void show(std::ostream& os) const =0;

};

#endif
