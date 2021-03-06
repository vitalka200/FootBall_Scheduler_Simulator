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
#include <string>
#include <vector>

#define DISQUALIFY -2
#define CHANGED -1
#define FREE_TO_GO  0
#define MOVED 1


const Time Game::MAX_GAME_LEN = Time(2, 0);

Game::~Game()
{
	delete m_timeAndDate; delete []m_gameScore;
	DeletePlayerStats(m_playerStats);
}

bool Game::operator==(const Game& g) const
{
	return (*(m_teams[0]) == *(g.m_teams[0]) && *(m_teams[1]) == *(g.m_teams[1])) ||
		(*(m_teams[0]) == *(g.m_teams[1]) && *(m_teams[1]) == *(g.m_teams[0]));
}

const Game& Game::operator=(const Game& g)
{
	if (this != &g)
	{
		m_maxFans       = g.m_maxFans;
		m_wasStarted    = g.m_wasStarted;

		SetGameScore(g.m_gameScore);
		SetTeams(g.m_teams);
		SetReferees(g.m_referees);
		SetTimeAndDate(g.GetTimeAndDate());
		SetPlayerStats(g.GetGameStats());
		SetFans(g.GetFans());
	}
	return *this;
}

PlayerStats* Game::GetPlayerStats(const Player* p)
{
	PlayerStats* ps = NULL;
	int totalPlayers = GetTotalPlayers();
	for (int i = 0; i < totalPlayers; i++)
	{
		if (m_playerStats[i]->GetPlayer()->IsEqual(p))
		{ ps = m_playerStats[i]; break; }
	}
	return ps;
}

void Game::SetTimeAndDate(const TimeAndDate* tad)
{
	delete m_timeAndDate;
	m_timeAndDate = new TimeAndDate(*tad);
}

void Game::SetPlayerStats(const std::vector<PlayerStats*>& ps)
{
	DeletePlayerStats(m_playerStats);
	m_playerStats.clear();
	m_playerStats = ps;
}

void Game::SetFans(const std::vector<Fan>& fans)
{
	m_fans.clear();
	m_fans = fans;
}

void Game::SetReferees(const std::vector<Referee>& referees)
{
	m_referees.clear();
	m_referees = referees;
}

void Game::SetTeams(std::vector<Team*> teams)
{
	m_teams = teams;
	
	int totalPlayers = m_teams[0]->GetPlayerNum() + m_teams[1]->GetPlayerNum();
	int counter;
	m_playerStats = std::vector<PlayerStats*>(totalPlayers);

	Team& t1 = *(m_teams[0]);
	for (counter = 0; counter < m_teams[0]->GetPlayerNum(); counter++)
	{ m_playerStats[counter] = new PlayerStats(t1[counter]); }

	Team& t2 = *(m_teams[1]);
	for (int i = 0; counter < totalPlayers; counter++, i++)
	{ m_playerStats[counter] = new PlayerStats(t2[i]); }
}

void Game::CreateGameScore()
{
	delete []m_gameScore;
	m_gameScore = new int[2];
	m_gameScore[0] = 0; m_gameScore[1] = 0;
}

void Game::SetGameScore(int* gameScore)
{
	CreateGameScore();
	m_gameScore[0] = gameScore[0];
	m_gameScore[1] = gameScore[1];
}

void Game::DeletePlayerStats(std::vector<PlayerStats*> pStats)
{
	int totalPlayers = GetTotalPlayers();
	for (int i = 0; i < totalPlayers; i++)
	{ delete pStats[i]; }
}

Team* Game::GetWinner() const
{
	if      (m_gameScore[0] > m_gameScore[1]) return m_teams[0];
	else if (m_gameScore[1] > m_gameScore[0]) return m_teams[1];
	// There is no winner if score even or game not started
	else                                        return NULL;
}

int Game::GetTotalPlayers() const
{
	return m_teams[0]->GetPlayerNum() + m_teams[1]->GetPlayerNum();
}

bool Game::CanStartGame()
{
	return (
		// Need at least 2 players to start a game
		m_teams[0]->GetPlayerNum() > 1 &&
		m_teams[1]->GetPlayerNum() > 1 &&
		// Can't Start Game without goalkeeper
		m_teams[0]->GetGoalKeeperIndex() > 0 &&
		m_teams[1]->GetGoalKeeperIndex() > 0 &&
		// Can't start game without Trainer
		m_teams[0]->GetTrainersNum() > 0 &&
		m_teams[1]->GetTrainersNum() > 0 &&
		// Can't start game without referee
		m_referees.size() > 0
		);
}

void Game::StartGame()
{
	if (!CanStartGame())
	{
		std::cout << "==========================================================" << std::endl;
		std::cout << "!!!Can't start game because start prerequisites not met!!!" << std::endl;
		std::cout << "==========================================================" << std::endl << std::endl;
		return;
	}

	m_wasStarted = true;

	srand(time(NULL));

	////////////////////////////////////////////////////////////////
	//////////// Set initial values for game start /////////////////
	////////////////////////////////////////////////////////////////
	std::vector<bool*> playersBall = std::vector<bool*>(2);
	playersBall[0] = new bool[m_teams[0]->GetPlayerNum()]();
	playersBall[1] = new bool[m_teams[1]->GetPlayerNum()]();

	std::vector<int*> playersMoved = std::vector<int*>(2);
	playersMoved[0] = new int[m_teams[0]->GetPlayerNum()]();
	playersMoved[1] = new int[m_teams[1]->GetPlayerNum()]();

	int chosenTeam1 = rand() % 2;
	int chosenPlayer1 = rand() % (m_teams[chosenTeam1]->GetPlayerNum());
	playersBall[chosenTeam1][chosenPlayer1] = true; // Set initial ball value
	m_teams[chosenTeam1]->SetIsAtacking(true);

	////////////////////////////////////////////////////////////////
	//////////////// Loop for the rest of game /////////////////////
	////////////////////////////////////////////////////////////////
	Time halfTime  = MAX_GAME_LEN/2;
	int firstTeam  = 0;
	int secondTeam = 1;

	for (Time i; i < MAX_GAME_LEN; i++)
	{
		if (i == halfTime) { firstTeam  = 1; secondTeam = 0; }

		Team& team1 = *(m_teams[firstTeam]);
		Team& team2 = *(m_teams[secondTeam]);

		for (int i = 0; i < team1.GetPlayerNum(); i++)
		{
			
			Player* p1 = team1[i];
			bool p1HaveBall = playersBall[firstTeam][i];
			PlayerMovement pm1 = p1->MakeMove(p1HaveBall);
			playersMoved[firstTeam][i] = MOVED;
			PlayerStats* gameStatsPlayer1 = GetPlayerStats(p1);
			PlayerStats* teamStatsPlayer1 = team1.GetPlayerStats(p1);
			gameStatsPlayer1->AddMove(pm1);
			teamStatsPlayer1->AddMove(pm1);

			if (typeid(*p1) == typeid(Goalkeeper) && p1HaveBall)
			{
				// we have ball and need to pass it
				int playerNumToPass = 0;
				while (playersMoved[playerNumToPass] != FREE_TO_GO && typeid(*p1) != typeid(Goalkeeper))
				{ playerNumToPass = rand() % team1.GetPlayerNum(); }

				teamStatsPlayer1->AddMove(PlayerMovement::PASS_BALL);
				gameStatsPlayer1->AddMove(PlayerMovement::PASS_BALL);

				playersBall[firstTeam][i] = false;
				playersBall[firstTeam][playerNumToPass] = true;


			}
			else if (pm1 == PlayerMovement::TACKLE_BALL)
			{
				int chosenPlayer2 = rand() % (team2.GetPlayerNum());
				Player* p2 = team2[chosenPlayer2];
				PlayerStats* gameStatsPlayer2 = GetPlayerStats(p2);
				PlayerStats* teamStatsPlayer2 = team2.GetPlayerStats(p2);
				gameStatsPlayer2->AddMove(PlayerMovement::TACKLE_BALL);
				teamStatsPlayer2->AddMove(PlayerMovement::TACKLE_BALL);

				if (*p1 > *p2)
				{ 
					playersMoved[1][chosenPlayer2] = MOVED;
				}
				else if (*p1 < *p2)
				{
					playersMoved[secondTeam][chosenPlayer2] = MOVED;
					// Update Ball information
					playersBall[secondTeam][chosenPlayer2] = true;
					playersBall[firstTeam][i] = false;
					team2.SetIsAtacking(true);
					team2.SetIsAtacking(false);
					gameStatsPlayer2->AddMove(PlayerMovement::STEAL_BALL);
					teamStatsPlayer2->AddMove(PlayerMovement::STEAL_BALL);
				}
				else
				{
					// Players have same level. Tackle can be with Referee's cards
					// and change players by one of the trainers
					Referee* activeReferee = &(m_referees[rand() % m_referees.size()]);
					CardType card = activeReferee->MakeDecision();
					int teamNumThatGotCard = rand() % 2;

					if (card == CardType::RED) // Need to remove player for the rest of game
					{

						if (teamNumThatGotCard == firstTeam)
						{ 
							playersBall[secondTeam][chosenPlayer2] = true;
							playersMoved[secondTeam][chosenPlayer2] = MOVED;
							team2.SetIsAtacking(true);
							team2.SetIsAtacking(false);
							playersBall[firstTeam][i] = false;
							playersMoved[firstTeam][i] = DISQUALIFY;
							gameStatsPlayer1->AddCard(card);
							teamStatsPlayer1->AddCard(card);
						}
						else
						{
							playersBall[secondTeam][chosenPlayer2] = false;
							playersMoved[secondTeam][chosenPlayer2] = DISQUALIFY;
							gameStatsPlayer2->AddCard(card);
							teamStatsPlayer2->AddCard(card);
						}

					}
					else if (card == CardType::YELLOW) // Trainer Decision needed
					{
						const std::vector<Trainer> trainers = m_teams[teamNumThatGotCard]->GetTrainers();
						const Trainer* activeTrainer = &(trainers[rand() % m_teams[teamNumThatGotCard]->GetTrainersNum()]);
						TrainerDecision decision = activeTrainer->MakeDecision(m_teams[teamNumThatGotCard]->IsAttacking());
						Team* teamWithCard = m_teams[teamNumThatGotCard];
						int playerNumThatGotCard = teamNumThatGotCard == firstTeam ? i : chosenPlayer2;
						PlayerStats* teamPs = teamNumThatGotCard == firstTeam ? teamStatsPlayer1 : teamStatsPlayer2;
						PlayerStats* gamePs = teamNumThatGotCard == firstTeam ? gameStatsPlayer1 : gameStatsPlayer2;
						teamPs->AddCard(card);
						gamePs->AddCard(card);

						if (gamePs->GetYellowCards() >= 2)
						{
							// We need to disqualify that player
							playersBall[teamNumThatGotCard][playerNumThatGotCard] = false;
							playersMoved[teamNumThatGotCard][playerNumThatGotCard] = DISQUALIFY;
							playersBall[teamNumThatGotCard % 1][teamNumThatGotCard == secondTeam ? i : chosenPlayer2] = true;
						}
						else if (decision == TrainerDecision::CHANGE_PLAYER)
						{
							// Decide on player to change
							int playerToExchange = 0;

							while ((playersMoved[teamNumThatGotCard][playerToExchange] != FREE_TO_GO &&
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
						playersBall[teamThatWonTackle][teamThatWonTackle == firstTeam ? i : chosenPlayer2] = true;
						playersBall[teamThatWonTackle % 1][teamThatWonTackle == secondTeam ? i : chosenPlayer2] = false;
						
					}

				}

			}
			else if (pm1 == PlayerMovement::MAKE_GOAL)
			{
				Player* gk = team2.GetGoalkeeper();
				PlayerMovement gPm = gk->MakeMove(false);

				if (*p1 > *gk || (*p1 == *gk && gPm == PlayerMovement::MISS_BALL))
				{
					team2.GetPlayerStats(gk)->AddMove(PlayerMovement::MISS_BALL);
					m_gameScore[firstTeam]++;
					gameStatsPlayer1->AddGoals();
					teamStatsPlayer1->AddGoals();
				}
				else
				{
					team2.GetPlayerStats(gk)->AddMove(PlayerMovement::CATCH_BALL);
					
				}

				playersBall[firstTeam][i] = false;
				playersBall[secondTeam][team2.GetGoalKeeperIndex()] = true;

				playersMoved[firstTeam][i] = MOVED;
				
			}

			// Done with one team loop

		}
		// Make all the rest players move
		for (int k = 0; k < team1.GetPlayerNum(); k++)
		{
			if (playersMoved[firstTeam][k] == FREE_TO_GO) // player can move
			{
				GetPlayerStats(team1[k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
				team1.GetPlayerStats(team1[k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
			}
			else if (playersMoved[firstTeam][k] == MOVED) // clean stats for next iteration
			{ playersMoved[firstTeam][k] = FREE_TO_GO; } 
		}
		for (int k = 0; k < team2.GetPlayerNum(); k++)
		{
			if (playersMoved[secondTeam][k] == FREE_TO_GO) // player can move
			{
				GetPlayerStats(team2[k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
				team2.GetPlayerStats(team2[k])->AddMove(PlayerMovement::RUN_TO_OPEN_SPACE);
			}
			else if (playersMoved[secondTeam][k] == MOVED) // clean stats for next iteration
			{ playersMoved[secondTeam][k] = FREE_TO_GO; }
		}

		
	}
	// Free unneeded memory
	delete []playersMoved[0]; delete []playersMoved[1]; 
	delete []playersBall[0]; delete []playersBall[1];
}

void Game::AddReferee(const Referee& ref)
{ m_referees.push_back(ref); }

void Game::RemoveReferee(const Referee& ref)
{
	int idxToRemove = -1;
	for (int i = 0; i < m_referees.size(); i++)
	{
		if (m_referees[i] == ref)
		{ idxToRemove = i; }
	}
	if (idxToRemove > -1)
	{ m_referees.erase(m_referees.begin() + idxToRemove); }
}

void Game::AddFan(const Fan& fan)
{ m_fans.push_back(fan); }

void Game::RemoveFan(const Fan& fan)
{
	int idxToRemove = -1;
	for (int i = 0; i < m_fans.size(); i++)
	{
		if (m_fans[i] == fan)
		{ idxToRemove = i; }
	}
	if (idxToRemove > -1)
	{ m_fans.erase(m_fans.begin() + idxToRemove); }
}

void Game::SetTime(const TimeAndDate& tad)
{
	delete m_timeAndDate;
	m_timeAndDate = new TimeAndDate(tad);
}

std::ostream & operator<<(std::ostream & os, const Game & g)
{
	os << "Game between Team: '" << g.GetTeams()[0]->GetName() << "' and Team: '" << g.GetTeams()[1]->GetName() << "'" << std::endl;
	os << "Score: '" << g.GetGameScore()[0] << "':'" << g.GetGameScore()[1] << "' ";
	os << "Fans comming: " << g.GetActualFans();
	return os;
}
