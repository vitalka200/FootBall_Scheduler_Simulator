#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

// System includes
#include <iostream>
#include <vector>
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
#include "LinkedList.h"
using namespace std;

class GameManager
{
public:
	// c-tors, d-tors
	GameManager() { TryInputMethod(); }
	~GameManager() {  }

	// Operators
	const GameManager& operator+=(Game& g) { AddGame(&g);    return *this; }
	const GameManager& operator-=(const Game& g) { RemoveGame(&g); return *this; }
	GameList           operator[](const Date& d)          const;
	const GameList     operator[](const TimeAndDate& tad) const;


	// Methods
	void NewGame();
	void CancelGame();
	void StartGame();
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

	void  AddGame(Game* g);
	void  RemoveGame(const Game* g);

private:
	// Disable copy and assigment
	GameManager(const GameManager& gm) { }
	const GameManager& operator=(const GameManager& gm) { }

	std::vector<Game*> m_games;
	std::vector<Team*> m_teams;
	LinkedList<Referee*> m_Referees;
	std::vector<Stadium> m_stadiums;


	// Methods
	void SellTickets(const Game* game, Fan* fan);
	void Redirect2File(std::string inFileName);
	void Redirect2ios();
	void TryInputMethod();


};

#endif
