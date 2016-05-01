#include "Game.h"
#include "Fan.h"
#include "Player.h"
#include "Trainer.h"
#include "Referee.h"
#include "Goalkeeper.h"
#include "Team.h"

#include <stdlib.h>
#include <time.h>
#include <typeinfo.h>

#define DISQUALIFY -2
#define CHANGED -1
#define FREE_TO_GO  0
#define MOVED 1


const Time Game::MAX_GAME_LEN = Time(2, 0);

Game::~Game()
{
	delete[]m_fans; delete m_timeAndDate;
	DeletePlayerStats(m_playerStats); delete []m_playerStats;
}

bool Game::operator==(const Game& g) const
{
	return (m_teams[0] == g.m_teams[0] && m_teams[1] == g.m_teams[1]) ||
		(m_teams[0] == g.m_teams[1] && m_teams[1] == g.m_teams[0]);
}

const Game& Game::operator=(const Game& g)
{
	if (this != &g)
	{
		m_gameScore[0]  = g.m_gameScore[0]; 
		m_gameScore[1]  = g.m_gameScore[1];
		m_maxFans       = g.m_maxFans;

		SetTeams(g.m_teams);
		SetReferees(g.m_referees, g.m_refereesCount);
		SetTimeAndDate(g.GetTimeAndDate());
		SetPlayerStats(g.GetGameStats(), GetActualFans());
		SetFans(g.GetFans(), g.m_actualFans);
	}
	return *this;
}

PlayerStats* Game::GetPlayerStats(const Player * p)
{
	PlayerStats* ps = NULL;
	int totalPlayers = GetTotalPlayers();
	for (int i = 0; i < totalPlayers; i++)
	{
		if (m_playerStats[i]->GetPlayer()->IsEqual(p))
		{
			ps = m_playerStats[i];
		}
	}
	return ps;
}

void Game::SetTimeAndDate(const TimeAndDate* tad)
{
	delete m_timeAndDate;
	m_timeAndDate = new TimeAndDate(*tad);
}

void Game::SetPlayerStats(PlayerStats** ps, int count)
{
	DeletePlayerStats(m_playerStats); delete[]m_playerStats;

	int totalPlayers = GetTotalPlayers();
	m_playerStats    = new PlayerStats*[totalPlayers];

	for (int i = 0; i < totalPlayers; i++)
	{ m_playerStats[i] = new PlayerStats(*(ps[i])); }
}

void Game::SetFans(const Fan* fans, int count)
{
	delete []m_fans;
	m_actualFans = count;
	m_fans       = new Fan[m_actualFans];
}

void Game::SetReferees(const Referee* referees, int count)
{
	delete []m_referees;
	m_referees      = new Referee[count];
	m_refereesCount = count;
	for (int i = 0; i < count; i++)
	{ m_referees[i] = Referee(referees[i]); }
}

void Game::SetTeams(const Team* teams)
{
	delete []m_teams;
	m_teams    = new Team[2];
	m_teams[0] = teams[0];
	m_teams[1] = teams[1];
	delete []m_playerStats;
	int totalPlayers = GetTotalPlayers();
	int counter;
	m_playerStats = new PlayerStats*[totalPlayers];
	
	for (counter = 0; counter < m_teams[0].GetPlayerNum(); counter++)
	{ m_playerStats[counter] = new PlayerStats(m_teams[0][counter]); }

	for (int i = 0; counter < totalPlayers; counter++, i++)
	{ m_playerStats[counter] = new PlayerStats(m_teams[0][i]); }
}

void Game::DeletePlayerStats(PlayerStats** pStats)
{
	int totalPlayers = GetTotalPlayers();
	for (int i = 0; i < totalPlayers; i++)
	{ delete pStats[i]; }
}

const Team* Game::GetWinner() const
{
	if (m_gameScore[0] >= 0)
	{ 
		if      (m_gameScore[0] > m_gameScore[1]) return &(m_teams[0]);
		else if (m_gameScore[1] > m_gameScore[0]) return &(m_teams[1]);
	}
	// There is no winner if score even or game not started
	return NULL;
}

int Game::GetTotalPlayers() const
{
	return m_teams[0].GetPlayerNum() + m_teams[1].GetPlayerNum();
}

void Game::StartGame()
{
	srand(time(NULL));

	////////////////////////////////////////////////////////////////
	//////////// Set initial values for game start /////////////////
	////////////////////////////////////////////////////////////////
	bool** playersBall = new bool*[2];
	playersBall[0] = new bool[m_teams[0].GetPlayerNum()]();
	playersBall[1] = new bool[m_teams[1].GetPlayerNum()]();

	int** playersMoved = new int*[2];
	playersMoved[0] = new int[m_teams[0].GetPlayerNum()]();
	playersMoved[1] = new int[m_teams[1].GetPlayerNum()]();

	int chosenTeam1 = rand() % 2;
	int chosenPlayer1 = rand() % (m_teams[chosenTeam1].GetPlayerNum());
	playersBall[chosenTeam1][chosenPlayer1] = true; // Set initial ball value
	m_teams[chosenTeam1].SetIsAtacking(true);

	////////////////////////////////////////////////////////////////
	//////////////// Loop for the rest of game /////////////////////
	////////////////////////////////////////////////////////////////
	for (Time i; i < MAX_GAME_LEN; i++)
	{


		for (int i = 0; i < m_teams[0].GetPlayerNum(); i++)
		{
			Player* p1 = m_teams[0][i];
			bool p1HaveBall = playersBall[0][i];
			PlayerMovement pm1 = p1->MakeMove(p1HaveBall);
			playersMoved[0][i] = MOVED;
			PlayerStats* gameStatsPlayer1 = GetPlayerStats(p1);
			PlayerStats* teamStatsPlayer1 = m_teams[0].GetPlayerStats(p1);
			gameStatsPlayer1->AddMove(pm1);
			teamStatsPlayer1->AddMove(pm1);

			if (typeid(*p1) == typeid(Goalkeeper) && p1HaveBall)
			{
				// we have ball and need to pass it
				int playerNumToPass;
				while (playersMoved[playerNumToPass] != FREE_TO_GO && typeid(*p1) != typeid(Goalkeeper))
				{ playerNumToPass = rand() % m_teams[0].GetPlayerNum(); }

				teamStatsPlayer1->AddMove(PlayerMovement::PASS_BALL);
				gameStatsPlayer1->AddMove(PlayerMovement::PASS_BALL);

				playersBall[0][i] = false;
				playersBall[0][playerNumToPass] = true;


			}
			else if (pm1 == PlayerMovement::TACKLE_BALL)
			{
				int chosenPlayer2 = rand() % (m_teams[1].GetPlayerNum());
				Player* p2 = m_teams[1][chosenPlayer2];
				PlayerStats* gameStatsPlayer2 = GetPlayerStats(p2);
				PlayerStats* teamStatsPlayer2 = m_teams[1].GetPlayerStats(p2);
				gameStatsPlayer2->AddMove(PlayerMovement::TACKLE_BALL);
				teamStatsPlayer2->AddMove(PlayerMovement::TACKLE_BALL);

				if (*p1 > *p2)
				{ 
					playersMoved[1][chosenPlayer2] = MOVED;
				}
				else if (*p1 < *p2)
				{
					playersMoved[1][chosenPlayer2] = MOVED;
					// Update Ball information
					playersBall[1][chosenPlayer2] = true;
					playersBall[0][i] = false;
					m_teams[1].SetIsAtacking(true);
					m_teams[0].SetIsAtacking(false);
					gameStatsPlayer2->AddMove(PlayerMovement::STEAL_BALL);
					teamStatsPlayer2->AddMove(PlayerMovement::STEAL_BALL);
				}
				else
				{
					// Players have same level. Tackle can be with Referee's cards
					// and change players by one of the trainers
					Referee* activeReferee = &(m_referees[rand() % m_refereesCount]);
					CardType card = activeReferee->MakeDecision();
					int teamNumThatGotCard = rand() % 2;

					if (card == CardType::RED) // Need to remove player for the rest of game
					{

						if (teamNumThatGotCard == 0)
						{ 
							playersBall[1][chosenPlayer2] = true;
							playersMoved[1][chosenPlayer2] = MOVED;
							m_teams[1].SetIsAtacking(true);
							m_teams[0].SetIsAtacking(false);
							playersBall[0][i] = false;
							playersMoved[0][i] = DISQUALIFY;
							gameStatsPlayer1->AddCard(card);
							teamStatsPlayer1->AddCard(card);
						}
						else
						{
							playersBall[1][chosenPlayer2] = false;
							playersMoved[1][chosenPlayer2] = DISQUALIFY;
							gameStatsPlayer2->AddCard(card);
							teamStatsPlayer2->AddCard(card);
						}

					}
					else if (card == CardType::YELLOW) // Trainer Decision needed
					{
						const Trainer* trainers = m_teams[teamNumThatGotCard].GetTrainers();
						const Trainer* activeTrainer = &(trainers[rand() % m_teams[teamNumThatGotCard].GetTrainersNum()]);
						TrainerDecision decision = activeTrainer->MakeDecision(m_teams[teamNumThatGotCard].IsAttacking());
						Team* teamWithCard = &(m_teams[teamNumThatGotCard]);
						int playerNumThatGotCard = teamNumThatGotCard == 0 ? i : chosenPlayer2;
						PlayerStats* teamPs = teamNumThatGotCard == 0 ? teamStatsPlayer1 : teamStatsPlayer2;
						PlayerStats* gamePs = teamNumThatGotCard == 0 ? gameStatsPlayer1 : gameStatsPlayer2;
						teamPs->AddCard(card);
						gamePs->AddCard(card);

						if (gamePs->GetYellowCards() >= 2)
						{
							// We need to disqualify that player
							playersBall[teamNumThatGotCard][playerNumThatGotCard] = false;
							playersMoved[teamNumThatGotCard][playerNumThatGotCard] = DISQUALIFY;
							playersBall[teamNumThatGotCard % 1][teamNumThatGotCard == 1 ? i : chosenPlayer2] = true;
						}
						else if (decision == TrainerDecision::CHANGE_PLAYER)
						{
							// Decide on player to change
							int playerToExchange = 0;

							while ((playersMoved[teamNumThatGotCard][playerToExchange] != FREE_TO_GO ||
								playersMoved[teamNumThatGotCard][playerToExchange] != CHANGED) &&
								typeid(*p1) != typeid(Goalkeeper))
							{ playerToExchange = rand() % teamWithCard->GetPlayerNum(); }

							playersMoved[teamNumThatGotCard][playerNumThatGotCard] = CHANGED;
							playersBall[teamNumThatGotCard][playerNumThatGotCard] = false;
							playersBall[teamNumThatGotCard][playerToExchange] = true;

						}
					}
					else
					{ 
						// no card given we'll generate random team that will have ball
						int teamThatWonTackle = rand() % 2;
						playersBall[teamThatWonTackle][teamThatWonTackle == 0 ? i : chosenPlayer2] = true;
						playersBall[teamThatWonTackle % 1][teamThatWonTackle == 1 ? i : chosenPlayer2] = false;
						
					}

				}

			}
			else if (pm1 == PlayerMovement::MAKE_GOAL)
			{
				const Player* gk = m_teams[1].GetGoalkeeper();

				if (*p1 > *gk)
				{
					m_teams[1].GetPlayerStats(gk)->AddMove(PlayerMovement::MISS_BALL);

					gameStatsPlayer1->AddGoals();
					teamStatsPlayer1->AddGoals();
				}
				else
				{
					m_teams[1].GetPlayerStats(gk)->AddMove(PlayerMovement::CATCH_BALL);
					
				}

				playersBall[0][i] = false;
				playersBall[1][m_teams[1].GetGoalKeeperIndex()] = true;

				playersMoved[0][i] = MOVED;
				
			}

			// Done with one team loop

		}
		// Make all the rest players move
		for (int k = 0; k < m_teams[0].GetPlayerNum(); k++)
		{
			if (playersMoved[0][k] == FREE_TO_GO) // player can move
			{
				GetPlayerStats(m_teams[0][k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
				m_teams[0].GetPlayerStats(m_teams[0][k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
			}
			else if (playersMoved[0][k] == MOVED) // clean stats for next iteration
			{ playersMoved[0][k] = FREE_TO_GO; } 
		}
		for (int k = 0; k < m_teams[1].GetPlayerNum(); k++)
		{
			if (playersMoved[1][k] == FREE_TO_GO) // player can move
			{
				GetPlayerStats(m_teams[1][k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
				m_teams[1].GetPlayerStats(m_teams[1][k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
			}
			else if (playersMoved[1][k] == MOVED) // clean stats for next iteration
			{ playersMoved[1][k] = FREE_TO_GO; }
		}

		
	}
	// Free unneeded memory
	delete []playersMoved[0]; delete []playersMoved[1]; delete []playersMoved;
	delete []playersBall[0]; delete []playersBall[1]; delete []playersBall;
}

void Game::AddReferee(const Referee& ref)
{
	Referee* newList = new Referee[m_refereesCount + 1];
	for (int i = 0; i < m_refereesCount; i++)
	{ newList[i] = m_referees[i]; }
	newList[m_refereesCount] = ref;
	delete[] m_referees; m_referees = newList;
	m_refereesCount++;
}

void Game::RemoveReferee(const Referee& ref)
{
	Referee* newList = new Referee[m_refereesCount-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_refereesCount; i++)
	{
		if (m_referees[i] == ref)
		{ idxToRemove = i; }
	}
	if (idxToRemove >= 0)
	{
		for (int i = 0; i < idxToRemove; i++)
		{ newList[i] = m_referees[i];}
		for (int i = idxToRemove+1; i < m_refereesCount; i++)
		{ newList[i-1] = m_referees[i]; }
		delete []m_referees; m_referees = newList;
		m_refereesCount--;
	}
	else 
	{ delete []newList; }
}

void Game::AddFan(const Fan& fan)
{
	Fan* newList = new Fan[m_actualFans+1];
	for (int i = 0; i < m_actualFans; i++)
	{ newList[i] = m_fans[i]; }
	newList[m_actualFans] = fan;
	delete []m_fans; m_actualFans++;
}

void Game::RemoveFan(const Fan& fan)
{
	Fan* newList = new Fan[m_actualFans-1];
	int idxToRemove = -1;
	for (int i = 0; i < m_actualFans; i++)
	{
		if (m_fans[i] == fan)
		{ idxToRemove = i; }
	}
	if (idxToRemove >= 0)
	{
		for (int i = 0; i < idxToRemove; i++)
		{ newList[i] = m_fans[i];}
		for (int i = idxToRemove+1; i < m_actualFans; i++)
		{ newList[i-1] = m_fans[i]; }
		delete []m_fans; m_fans = newList;
		m_actualFans--;
	}
	else 
	{ delete []newList; }
}

void Game::SetTime(const TimeAndDate& tad)
{
	delete []m_timeAndDate;
	m_timeAndDate = new TimeAndDate(tad);
}

std::ostream & operator<<(std::ostream & os, const Game & g)
{
	os << "Game between '" << g.GetTeams()[0] << "' and '" << g.GetTeams()[1] << "'" << std::endl;
	os << "Score: '" << g.GetGameScore()[0] << "':'" << g.GetGameScore()[0] << "'";
	os << "Fans comming: " << g.GetActualFans();
	return os;
}
