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
	GameManager();
	~GameManager() { delete[] games; delete[] teams; delete[] stadiums;}
	// Operators



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


private:
	Game* games;
	Team* teams;
	Stadium* stadiums;

};

#endif