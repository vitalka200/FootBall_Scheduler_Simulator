
#include "GameManager.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define NAME_LEN 20

std::ifstream in("");

/*
*	Print the array given.
*/
template<class T>
void PrintDynamicArray(int length, std::vector<T*> arr)
{
	for (int i = 0; i < length; i++)
	{ std::cout << i + 1 << ") " << *(arr[i]) << std::endl; }
}
template<class T>
void PrintArray(int length, const std::vector<T>& arr)
{
	for (int i = 0; i < length; i++)
	{ std::cout << i + 1 << ") " << arr[i] << std::endl; }
}

/*
*	clear std::cin
*		Used for the redirection proccess of std::cin.
*/
void clearCin()
{
	std::cin.clear(); while (std::cin.get() != '\n') { continue; }
}

/*
*	Check the validity of the user input and handle exceptions.
*/
template<class T>
void scan(T& input) {
	while (true)
	{
		std::cin >> input;
		if (std::cin.good())
		{ std::cout << input << std::endl; break; }
		else
		{
			std::cout << std::endl << "Wrong input. Please reenter" << std::endl;
			clearCin();
		}
	}
	clearCin();
}



/*
*	Redirect the std::cin and std::cout to external file.
*/
void GameManager::Redirect2File(const std::string& inFileName)
{
	in = std::ifstream(inFileName);
	if (!in.good()) throw std::exception();
	// actual redirect
	std::cin.rdbuf(in.rdbuf());
}


/*
*	Redirect the std::cin and std::cout to IOS.
*/
void GameManager::Redirect2ios()
{
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(cinbuf);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(coutbuf);
}


Player* GetPlayer(Team* t) {
	int type, id, level;
	std::string name, f_name;
	std::cout << std::endl << "Type of Player : 1-forwarder, 2- Defender :  ";
	scan<int>(type);
	std::cout << std::endl << "Player name --> ";
	scan<std::string>(name);
	std::cout << std::endl << "Player first name --> ";
	scan<std::string>(f_name);
	std::cout << std::endl << "Player id --> ";
	scan<int>(id);
	std::cout << std::endl << "Player Level 0-3, 0 if Default --> ";
	scan<int>(level);
	Player* newPlayer;

	switch (type)
	{
	case 1: newPlayer = new Forwarder(name, f_name, id, t, (PlayerLevel)level);		break;
	case 2: newPlayer = new Defender(name, f_name, id, t, (PlayerLevel)level);		break;
	default:
		throw std::exception("\nThe values where invalid.\n");
	}
	return newPlayer;
}

/*
*	End
*/


GameList GameManager::operator[](const Date& d) const
{
	GameList res;
	res.games = new Game*[m_games.size()];

	for (int i = 0; i < m_stadiums.size(); i++)
	{
		GameList gameList = m_stadiums.at(i).GetGamesByDate(d);

		for (int j = 0; j < gameList.count; j++)
		{ res.games[res.count++] = gameList.games[j]; }
	}

	GameList newRes = res;
	return newRes;
}

const GameList GameManager::operator[](const TimeAndDate& tad) const
{
	GameList res;
	res.games = new Game*[m_games.size()];

	for (int i = 0; i < m_stadiums.size(); i++)
	{
		if (m_stadiums[i].GetGameByTimeAndDate(tad))
		{ res.games[res.count++] = m_stadiums[i].GetGameByTimeAndDate(tad); }
	}

	return res;
}

void GameManager::CancelGame() {

	int stadiumNum, gameNum, gameDate;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Cancel Game:" << std::endl;
	std::cout << "==========================================================" << std::endl;

	std::cout << std::endl << "Choose a stadium -->> " << std::endl;
	PrintArray<Stadium>(m_stadiums.size(), m_stadiums);
	std::cout << "--> ";
	scan<int>(stadiumNum);
	stadiumNum--;
	std::vector<GamesByTimeDateNode> gamesList = m_stadiums[stadiumNum].m_gameList;
	if (m_stadiums[stadiumNum].m_gameList.size() > 0)
	{
		std::cout << std::endl << "Choose a Date -->> " << std::endl;

		for (int i = 0; i < m_stadiums[stadiumNum].m_gameList.size(); i++)
		{ std::cout << i + 1 << " - " << gamesList[i].GetDate() << std::endl; }

		scan<int>(gameDate);
		gameDate--;
		if (gamesList[gameDate].GetGamesCount() > 0)
		{
			std::cout << std::endl << "Choose a game from list -->> " << std::endl;

			for (int i = 0; i < gamesList[gameDate].GetGamesCount(); i++)
			{ std::cout << i + 1 << " - " << gamesList[gameDate].GetGameById(i) << std::endl; }

			scan<int>(gameNum);
			gameNum--;
			m_stadiums[stadiumNum].RemoveGame(&(gamesList[gameDate].GetGameById(gameNum)));
		}
		else
		{ std::cout << "There are no games in the specific date." << std::endl; }
	}
	else
	{ std::cout << "there are no games scheduled for this stadium." << std::endl; }
}

void GameManager::SellTickets() {
	int sold = 0, pick;
	srand(time(NULL));

	for (int i = 0; i < m_games[m_games.size() - 1]->GetMaxFans(); i++)
	{
		pick = rand() % 2;

		if (pick)
		{(*(m_games[m_games.size() - 1])) += Fan("name"); }
	}
}

void GameManager::ManageTrainers() {
	std::string  name, f_name;
	long id;
	int choice, teamNum;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "ManageTrainers:" << std::endl;
	std::cout << "==========================================================" << std::endl;

	while (flagOut)
	{
		std::cout << std::endl << "Would you like to add or remove Trainer?  1 - Add, 2- Remove.  else - exit." << std::endl;
		scan<int>(choice);
		std::cout << std::endl << "Enter team number from list -->> " << std::endl;
		PrintDynamicArray(m_teams.size(), m_teams);
		std::cout << "--> ";
		scan<int>(teamNum);
		switch (choice)
		{
		case 1:
		{
			std::cout << std::endl << "Team number : " << teamNum << std::endl << "Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "First Name --> ";
			scan<std::string>(f_name);
			std::cout << std::endl << "ID --> ";
			scan<long>(id);
			*(m_teams[teamNum - 1]) += (new Trainer(name, f_name, id));
			break;
		}
		case 2:
		{
			int trainerNum;
			std::cout << std::endl << "Choose trainer from list -->> " << std::endl;
			std::cout << "--> ";
			scan<int>(trainerNum);
			*(m_teams[trainerNum]) -= &(m_teams[teamNum - 1]->GetTrainers()[trainerNum]);
			break;
		}
		default: {flagOut = false;  break; }
		}
	}

}

void GameManager::ManageReferees() {
	int  choice;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Manage Referees:" << std::endl;
	std::cout << "==========================================================" << std::endl;

	while (flagOut)
	{
		std::cout << std::endl << "Would you like to add or remove Referee ?  1 - Add, 2- Remove else - exit." << std::endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			std::string name, f_name;
			long id;

			std::cout << std::endl << "Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "First name --> ";
			scan<std::string>(f_name);
			std::cout << std::endl << "ID --> ";
			scan<long>(id);
			m_Referees.add(new Referee(name, f_name, id));

			break;
		}
		case 2:
		{
			int refNum;
			std::cout << std::endl << "Choose referee from the list -->> " << std::endl;
			std::cout << m_Referees;
			std::cout << "--> ";
			scan<int>(refNum);
			m_Referees.remove(refNum - 1);
			std::cout << std::endl << "Referee has been removed." << std::endl;
			break;
		}
		default:
		{flagOut = false; break; }
		}
	}
}

void GameManager::ManageTeams() {
	int  numberOfPlayers, level, choice, type;
	std::string name, f_name;
	long id;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Manage Teams:" << std::endl;
	std::cout << "==========================================================" << std::endl;

	while (flagOut)
	{
		std::cout << "Would you like to add or move Team ? 1-Add, 2-remove, else - exit." << std::endl;
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			std::cout << std::endl << "Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "Number of Players in the team --> ";
			scan<int>(numberOfPlayers);
			Team* newTeam = new Team(name);

			for (int j = 0; j < numberOfPlayers; j++)
			{
				Player* newPlayer = GetPlayer(newTeam);
				(*newTeam) += newPlayer;

			}

			std::cout << std::endl << "Goalkeeper Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "Gaolkeeper first Name --> ";
			scan<std::string>(f_name);
			std::cout << std::endl << "Goalkeeper ID --> ";
			scan<long>(id);
			std::cout << std::endl << "Goalkeeper Level 0-3, 0 if Default --> ";
			scan<int>(level);
			(*newTeam) += new Goalkeeper(name, f_name, id, newTeam, (PlayerLevel)level);

			std::cout << std::endl << "Trainer Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "Trainer first Name --> ";
			scan<std::string>(f_name);
			std::cout << std::endl << "Trainer ID --> ";
			scan<long>(id);
			(*newTeam) += new Trainer(name, f_name, id);
			m_teams.push_back(newTeam);
			break;
		}
		case 2:
		{
			int teamNum;
			std::cout << "Choose a Team -->>" << std::endl;
			PrintDynamicArray(m_teams.size(), m_teams);
			std::cout << "--> ";
			scan<int>(teamNum);
			if (teamNum > 0 && teamNum < m_teams.size())
			{ m_teams.erase(m_teams.begin() + teamNum - 1); }
			break;
		}
		default: { flagOut = false; break; }
		}
	}
}

void GameManager::ManageGames() {
	int choice;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Managing Games:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	while (flagOut)
	{
		std::cout << std::endl << "What would you like to do?  1-Add Game, 2-Cancel Game, else-exit." << std::endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
			case 1: { NewGame();			break; }
			case 2: { CancelGame();		break; }
			default: { flagOut = false;		break; }
		}
	}
}

void GameManager::ManageStadiums()
{
	int stadiumNum, choice;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Managing Stadiums:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	while (flagOut)
	{
		std::cout << std::endl << "What would you like to do ? 1 - Add, 2 - Delete, 3 - Update, else - exit.";
		std::cout << std::endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			std::string name;
			int Maxfans;
			std::cout << std::endl << "Enter stadium Name --> ";
			scan<std::string>(name);
			std::cout << std::endl << "Enter max fans --> ";
			scan<int>(Maxfans);
			Stadium s = Stadium(name, Maxfans);
			m_stadiums.push_back(s);
			break;
		}
		case 2:
		{
			std::cout << std::endl << "Choose stadium number from list -->> " << std::endl;
			PrintArray<Stadium>(m_stadiums.size(), m_stadiums);
			std::cout << "--> ";
			scan<int>(stadiumNum);
			if (stadiumNum > 0 && stadiumNum < m_stadiums.size())
				m_stadiums.erase(m_stadiums.begin() + stadiumNum - 1);
			break;
		}
		case 3:
		{
			std::cout << std::endl << "Enter stadium number from list -->> " << std::endl;
			PrintArray<Stadium>(m_stadiums.size(), m_stadiums);
			std::cout << "--> ";
			scan<int>(stadiumNum);
			stadiumNum--;
			int updatedVal;
			std::cout << std::endl << "Choose value to be updated :  1- Name, 2- Max fans. " << std::endl;
			scan<int>(updatedVal);
			std::cout << std::endl << "Enter new value --> ";
			if (updatedVal == 1)
			{
				std::string val;
				scan<std::string>(val);
				m_stadiums[stadiumNum].SetName(val);
			}
			if (updatedVal == 2)
			{
				int val;
				scan<int>(val);
				m_stadiums[stadiumNum].SetMaxFans(val);
			}
			break;
		}
		default:
		{ flagOut = false;  break; }
		}
	}

}

void GameManager::NewGame() {
	Game* g = NULL;
	std::vector<Team*> teams = std::vector<Team*>(2);
	int t1, t2, minutes, hours, day, month, year, maxFans;
	std::cout << "==========================================================" << std::endl;
	std::cout << "New Game Creation:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::cout << std::endl << "List of all teams -->> " << std::endl;
	PrintDynamicArray(m_teams.size(), m_teams);
	std::cout << std::endl << "Enter Team number 1 id --> ";
	scan<int>(t1);
	t1--;
	std::cout << std::endl << "Enter Team number 2 id --> ";
	scan<int>(t2);
	t2--;
	teams[0] = m_teams[t1];
	teams[1] = m_teams[t2];
	std::cout << std::endl << "Date -->> " << std::endl << "Day --> ";
	scan<int>(day);
	std::cout << std::endl << "Month --> ";
	scan<int>(month);
	std::cout << std::endl << "Year --> ";
	scan<int>(year);
	std::cout << std::endl << "Time -->> " << std::endl << "Hours  --> ";
	scan<int>(hours);
	std::cout << std::endl << "Minutes --> ";
	scan<int>(minutes);
	std::cout << std::endl << "Number of maximum fans --> ";
	scan<int>(maxFans);
	Date d = Date(year, month, day);
	Time t = Time(hours, minutes);

	TimeAndDate tad = TimeAndDate(t, d);
	g = new Game(teams, tad, maxFans);
	std::cout << std::endl << "=== Adding referee from a list ===" << std::endl << std::endl;
	std::cout << m_Referees;
	int refereeNum = rand() % m_Referees.size();
	g->AddReferee(*m_Referees.get(refereeNum));

	std::cout << std::endl << "Chosen - " << *m_Referees.get(refereeNum) << std::endl;

	m_games.push_back(g);
	AddGame(g);
}


void GameManager::AddGame(Game* g)
{
	for (int i = 0; i<m_stadiums.size(); i++)
	{ if (m_stadiums[i].AddGame(g))	{ break; }}
}




void GameManager::RemoveGame(const Game* g)
{
	for (int i = 0; i<m_stadiums.size(); i++)
	{ if (m_stadiums[i].RemoveGame(g)) { break; } }
}


void GameManager::GetGameLog()
{
	for (int i = 0; i < m_games.size(); i++)
	{ std::cout << *(m_games[i]) << std::endl; }
}


void GameManager::GetMonthSummary()
{
	int year, month;
	bool haveGamesFlag = false;
	// For month summary we need all the games in all the days this month
	std::cout << "==========================================================" << std::endl;
	std::cout << "The Month summary: " << std::endl;
	std::cout << "==========================================================" << std::endl;

	std::cout << std::endl << "Enter Year --> ";
	scan<int>(year);

	std::cout << std::endl << "Enter Month --> ";
	scan<int>(month);

	for (int day = 1; day <= Date::DAYS_IN_MONTH[month - 1]; day++)
	{
		Date d(year, month, day);
		GameList list = (*this)[d]; // Retrieve games schedule of specific day

		if (list.count > 0)
		{
			haveGamesFlag = true;
			std::cout << std::endl << "Printing Games on Date: " << d << std::endl << std::endl;

			for (int i = 0; i < list.count; i++)
			{
				std::cout << "====== Game #" << i + 1 << " ======" << std::endl;
				std::cout << *(list.games[i]) << std::endl << "Winner: ";

				if (list.games[i]->GetWinner())
				{ std::cout << *(list.games[i]->GetWinner()) << std::endl; }
				else
				{ std::cout << "Not yet determined." << std::endl; }

				std::cout << std::endl;
			}
		}
	}
	if (!haveGamesFlag)
	{ std::cout << " There are no games planned this month." << std::endl; }
	std::cout << std::endl;
}

void GameManager::GetTeamSummary()
{
	int team;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Team Summary:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::cout << std::endl << "Choose team from list -->> " << std::endl;
	PrintDynamicArray(m_teams.size(), m_teams);
	std::cout << "--> ";
	scan<int>(team);
	team--;
	std::cout << *(m_teams[team]) << std::endl;
}

void GameManager::ManagePlayers()
{
	int playerNum, choice;
	int teamNum;
	bool flagOut = true;

	std::cout << "==========================================================" << std::endl;
	std::cout << "Manage Players:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::cout << std::endl << "Choose team from list -->>" << std::endl;
	PrintDynamicArray(m_teams.size(), m_teams);
	std::cout << "--> ";
	scan<int>(teamNum);
	teamNum--;

	while (flagOut) {
		std::cout << *(m_teams[teamNum]) << std::endl;
		std::cout << "What would you like to do ? 1-Add Player, 2- Delete Player, 3-Update Player, else - exit. " << std::endl;
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			Team* chosenTeam = m_teams[teamNum];
			Player* newPlayer = GetPlayer(chosenTeam);
			(*chosenTeam) += newPlayer;
			break;
		}
		case 2:
		{
			std::cout << std::endl << "Player number in the Team --> ";
			scan<int>(playerNum);
			*(m_teams[teamNum]) -= (*(m_teams[teamNum]))[playerNum];
			break;

		}
		case 3:
		{
			int choice2;
			std::cout << std::endl << "Player number in the Team --> ";
			scan<int>(playerNum);
			std::cout << std::endl << "What to update ? 1-name 2-strength";
			scan<int>(choice2);
			if (choice2 == 1)
			{
				std::string name;
				std::cout << std::endl << "Enter new value --> ";
				scan<std::string>(name);
				(*(m_teams[teamNum]))[playerNum]->SetName(name);
			}
			if (choice2 == 2)
			{
				int S;
				std::cout << std::endl << "Enter new value --> ";
				scan<int>(S);
				(*(m_teams[teamNum]))[playerNum]->SetLevel((PlayerLevel)S);
			}
			break;
		}
		default: { flagOut = false;  break; }
		}
	}
}

void GameManager::StartGame()
{
	int gameNum = 0;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Start Game menu:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::cout << std::endl << "Choose game from list below -->> " << std::endl;
	PrintDynamicArray(m_games.size(), m_games);
	std::cout << "--> ";
	scan<int>(gameNum);
	gameNum--;
	if (gameNum < m_games.size() && gameNum >= 0)
	{
		std::cout << std::endl << "Starting game..." << std::endl;
		m_games[gameNum]->StartGame();
	}
}
void GameManager::ManageGameSchedule()
{
	int choice;
	bool flagOut = true;
	std::cout << "==========================================================" << std::endl;
	std::cout << "Manage game schedule:" << std::endl;
	std::cout << "==========================================================" << std::endl;
	while (flagOut)
	{
		std::cout << "What Would you like to do ? 1 - view, 2- cancel Game, else - exit. \n";
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			if (m_games.size()> 0)
			{ PrintDynamicArray(m_games.size(), m_games); }
			break;
		}

		case 2:
		{
			CancelGame();
			break;
		}
		default:
		{ flagOut = false;  break; }
		}
	}
}
void GameManager::GetStats()
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "Team Stats:" << std::endl;
	std::cout << "==========================================================" << std::endl;

	for (int i = 0; i < m_teams.size(); i++)
	{
		std::cout << *(m_teams[i]);
		int wins = 0;
		for (int j = 0; j < m_games.size(); j++)
		{
			Team* winner = m_games[j]->GetWinner();
			Team* teamForStats = m_teams[i];

			if (winner && *winner == *teamForStats) { wins++; }
		}
		std::cout << " Wins = " << wins << std::endl;
	}
}


void GameManager::TryInputMethod()
{
	try { Redirect2File("in.txt"); }
	catch (std::exception e) { std::cout << "unable to read from file." << std::endl; }

	if (std::cin.bad()) { std::cout << "Bad redirect."; }
}
