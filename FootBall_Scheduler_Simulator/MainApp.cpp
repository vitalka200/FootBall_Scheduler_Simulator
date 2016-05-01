#include <iostream>
#include "GameManager.h"

using namespace std;

void main()
{
	Game* g = new Game();
	GameManager* gm = new GameManager();

	gm->ManageTeams();
	gm->ManageReferees();
	gm->ManageStadiums();

	gm->ManageGames();
	gm->ManageGameSchedule();

	gm->SellTickets();

	gm->StartGame();
	gm->GetStats();
	gm->GetMonthSummary();

	delete gm;
}