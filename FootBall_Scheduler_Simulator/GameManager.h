#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

// System includes
#include <iostream>
// Person includes
#include "Person.h"
#include "Fan.h"
#include "Trainer.h"
#include "Referee.h"
// Player includes
#include "Player.h"
#include "Goalkeeper.h"
#include "Defender.h"
#include "Forwarder.h"
// Composite data types includes
#include "Team.h"
#include "Game.h"
#include "Stadium.h"
// Other includes
#include "TimeAndDate.h"


class GameManager
{
public:
	// c-tors, d-tors
	GameManager() : m_games(NULL), m_teams(NULL), m_stadiums(NULL) { }
	~GameManager() { delete []m_games; delete []m_teams; delete []m_stadiums;}

	// Operators
	const GameManager& operator+=(const Game& g)            { AddGame(g);    return *this; }
	const GameManager& operator-=(const Game& g)            { RemoveGame(g); return *this; }
	const GameList     operator[](const Date& d)          const;
	const GameList     operator[](const TimeAndDate& tad) const;


	// Methods
	void NewGame();
	void CancelGame();
	void StartGame();
	void SendInvitations();
	void GetGameLog();
	void GetMonthSummary();
	void GetTeamSummary();
	void ManagePlayers();
	void ManageTrainers();
	void ManageReferees();
	void ManageTeams();
	void ManageGames();
	void ManageStadiums();
	void ManageGameSchedule();
	void SellTickets();
	void GetStats();

	void  AddGame(const Game& t);
	void  RemoveGame(const Game& g);

	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const GameManager& gm);

private:
	// Disable copy and assigment
	GameManager(const GameManager& gm) { }
	const GameManager& operator=(const GameManager& gm) { }

	Game*    m_games;
	Team*    m_teams;
	Referee* m_referees;
	Stadium* m_stadiums;

	// Methods
	void SellTickets(const Game* game, Fan* fan);

};

#endif