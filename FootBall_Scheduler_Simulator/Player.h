#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include "Person.h"

// Forward declaration
class Team;
class Player : Person
{
public:
	// Structs
	static enum PlayerMovement {STEAL_BALL, PASS_BALL, CATCH_BALL, MAKE_GOAL, TACKLE_BALL};
	static const char* MovementsNames[];

	enum PlayerLevel {LOW, MEDIUM, HIGH};
	static const char* LevelNames[];

	struct AllowedMoves {PlayerMovement* moves;int numberOfMoves;};

	// c-tors, d-tors
	Player(const char* name, const char* f_name, long id, int pnum, Team* team, PlayerLevel pl = LOW) 
	    : Person(name, f_name, id) {SetPNum(pnum); SetTeam(team); SetLevel(pl);}
	Player(const Player& p)
		: Person(p.m_name, p.m_fname, p.m_id)                         { m_allowed_moves.moves = NULL; *this = p; }
	~Player()                                                         {if (m_allowed_moves.numberOfMoves) delete []m_allowed_moves.moves;}
	const Player& operator=(const Player& p);
	// Methods
	void                         SetPNum(int num)                     {m_pnum = num;}
	void                         SetTeam(Team* team)                  {m_team = team;}
	void                         SetLevel(PlayerLevel pl)             {m_plevel = pl;}
	const int                    GetPNum()                      const {return m_pnum;}
	const PlayerLevel            GetPLevel()                    const {return m_plevel;}
	virtual const PlayerMovement MakeMove() =0;


	const Player& operator=(const Player& p);
	const Player& operator+=(Player::PlayerMovement* t);              
	const Player& operator-=(Player::PlayerMovement* t);
	const Player& operator>=(Defender* t);
	const Player& operator>=(Player* t)
	
	
	// Methods overrides
	friend std::ostream& operator<<(std::ostream& os, const PlayerMovement& pm)
	{os << Player::MovementsNames[pm]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const PlayerLevel& pl)
	{os << Player::LevelNames[pl]; return os;}
	friend std::ostream& operator<<(std::ostream& os, const Player& p);

protected:
	Team*        m_team;
	int          m_pnum;   // Player number in the team
	PlayerLevel  m_plevel; // Player Level
	AllowedMoves m_allowed_moves;
};
const char* Player::LevelNames[]     = {"Low", "Medium", "High"};
const char* Player::MovementsNames[] = {"Steal Ball", "Pass Ball", "Catch Ball", "Make Goal", "Tackle ball"};

#endif
