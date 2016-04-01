#include <iostream>
#include "GameManager.h"

using namespace std;

void main()
{
	GameManager* gm = new GameManager();

	gm->ManageTeams();
	gm->ManageReferees();
	gm->ManageStadiums();

	gm->ManageGames();
	gm->ManageGameSchedule();

	gm->SellTickets();
	gm->SendInvitations();

	gm->StartGame();
	gm->GetStats();
	gm->GetMonthSummary();

	delete gm;
}