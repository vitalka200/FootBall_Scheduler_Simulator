
#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <time.h>
#include <stdlib.h>

#define NAME_LEN 20

using namespace std;
ifstream in("");


//
//	For functionality And Exception handling
//


/*
*	Print the array given.
*/
template<class T>
void PrintDynamicArray(int length, T** arr)
{
	for (int i = 0; i < length; i++)
	{ std::cout << i + 1 << ") " << *(arr[i]) << endl; }
}
template<class T>
void PrintArray(int length, const T* arr)
{
	for (int i = 0; i < length; i++)
	{ std::cout << i + 1 << ") " << arr[i] << endl; }
}

/*
*	clear std::cin
*		Used for the redirection proccess of std::cin.
*/
void clearCin()
{
	cin.clear(); while (cin.get() != '\n') { continue; }
}

/*
*	Check the validity of the user input and handle exceptions.
*/
template<class T>
void scan(T& input) {
	while (true)
	{
		std::cin >> input;
		if (cin.good())
		{ cout << input << endl; break;	}
		else
		{ 
			std::cout << endl << "Wrong input. Please reenter" << endl;
			clearCin();
		}
	}
	clearCin();
}



/*
*	Redirect the std::cin and std::cout to external file.
*/
void GameManager::Redirect2File(char* inFileName)
{
	in = ifstream(inFileName);
	if (!in.good()) throw exception();
	// actual redirect
	cin.rdbuf(in.rdbuf());
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

/*
*	End
*/


GameList GameManager::operator[](const Date& d) const
{
	GameList res;
	res.games = new Game*[m_gamesLength];
	
	for (int i = 0; i < m_stadiumsLength; i++)
	{
		GameList gameList = m_stadiums[i].GetGamesByDate(d);

		for (int j = 0; j < gameList.count; j++)
		{ res.games[res.count++] = gameList.games[j]; }
	}

	GameList newRes = res;
	return newRes;
}

const GameList GameManager::operator[](const TimeAndDate& tad) const
{
	GameList res;
	res.games = new Game*[m_gamesLength];

	for (int i = 0; i < m_stadiumsLength; i++)
	{
		if (m_stadiums[i].GetGameByTimeAndDate(tad))
		{ res.games[res.count++] = m_stadiums[i].GetGameByTimeAndDate(tad); }
	}

	return res;
}

void GameManager::CancelGame() {

	int stadiumNum, gameNum, gameDate;
	std::cout << endl << "Choose a stadium -->> " << endl;
	PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
	cout << "--> ";
	scan<int>(stadiumNum);
	stadiumNum--;
	GamesByTimeDateNode* gamesList = m_stadiums[stadiumNum].m_gameList;
	if (m_stadiums[stadiumNum].m_numOfNodes > 0)
	{
		cout << endl << "Choose a Date -->> " << endl;
		
		for (int i = 0; i < m_stadiums[stadiumNum].m_numOfNodes; i++)
		{ cout << i + 1 << " - " << gamesList[i].GetDate() << endl;	}

		scan<int>(gameDate);
		gameDate--;
		if (gamesList[gameDate].GetGamesCount() > 0)
		{
			cout << endl << "Choose a game from list -->> " << endl;
			
			for (int i = 0; i < gamesList[gameDate].GetGamesCount(); i++)
			{ cout << i + 1 << " - " << gamesList[gameDate].GetGameById(i) << endl;	}

			scan<int>(gameNum);
			gameNum--;
			m_stadiums[stadiumNum].RemoveGame(&(gamesList[gameDate].GetGameById(gameNum)));
		}
		else
		{ cout << "There are no games in the specific date." << endl; }
	}
	else
	{
		cout << "there are no games scheduled for this stadium." << endl;
	}
}

void GameManager::SellTickets() {
	int sold = 0, pick;
	srand(time(NULL));

	for (int i = 0; i < m_games[m_gamesLength - 1]->GetMaxFans(); i++)
	{
		pick = rand() % 2;

		if (pick)
		{ (*(m_games[m_gamesLength - 1])) += Fan("name"); }
	}
}

void GameManager::ManageTrainers() {
	char name[NAME_LEN], f_name[NAME_LEN];
	long id;
	int choice, teamNum;
	bool flagOut = true;

	while (flagOut)
	{
		cout << endl << "Would you like to add or remove Trainer?  1 - Add, 2- Remove.  else - exit." << endl;
		scan<int>(choice);
		cout << endl << "Enter team number from list -->> " << endl;
		PrintDynamicArray(m_teamsLength, m_teams1);
		cout << "--> ";
		scan<int>(teamNum);
		switch (choice)
		{
			case 1:
			{
				std::cout << endl << "Team number : " << teamNum << endl << "Name --> ";
				scan(name);
				std::cout << endl << "First Name --> ";
				scan(f_name);
				std::cout << endl << "ID --> ";
				scan<long>(id);
				*(m_teams1[teamNum - 1]) += (new Trainer(name, f_name, id));
				break;
			}
			case 2:
			{
				int trainerNum;
				cout << endl << "Choose trainer from list -->> " << endl;
				PrintArray<Trainer>(m_teams1[teamNum - 1]->GetTrainersNum(), m_teams1[teamNum - 1]->GetTrainers());
				cout << "--> ";
				scan<int>(trainerNum);
				*(m_teams1[trainerNum]) -= &(m_teams1[teamNum - 1]->GetTrainers()[trainerNum]);
				break;
			}
			default:{flagOut = false;  break; }
		}
	}

}

void GameManager::ManageReferees() {
	int  choice;
	bool flagOut = true;

	while (flagOut)
	{
		cout << endl << "Would you like to add or remove Referee ?  1 - Add, 2- Remove else - exit." << endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
			case 1:
			{
				Referee* m_newReferees = new Referee[m_refereesLength + 1];
				
				for (int i = 0; i < m_refereesLength; i++)
				{ m_newReferees[i] = m_referees[i];	}

				char name[NAME_LEN], f_name[NAME_LEN];
				long id;
				
				for (int i = m_refereesLength; i < 1 + m_refereesLength; i++)
				{
					std::cout << endl << "Name --> ";
					scan(name);
					std::cout << endl << "First name --> ";
					scan(f_name);
					std::cout << endl << "ID --> ";
					scan<long>(id);
					m_newReferees[i] = Referee(name, f_name, id);
				}
				
				delete []m_referees;
				m_referees = m_newReferees;
				m_refereesLength += 1;
				break;
			}
			case 2:
			{
				int refNum;
				cout << endl << "Choose referee from the list -->> " << endl;
				PrintArray<Referee>(m_refereesLength, m_referees);
				cout << "--> ";
				scan<int>(refNum);
				refNum--;
				Referee* new_referee = new Referee[m_refereesLength - 1];
				
				for (int i = 0; i < refNum; i++)
				{ new_referee[i] = m_referees[i];}
				
				for (int i = refNum + 1; i < m_gamesLength; i++)
				{ new_referee[i - 1] = m_referees[i];}

				m_refereesLength--;
				delete []m_referees;
				m_referees = new_referee;
				cout << endl << "Referee has been removed." << endl;
				break;
			}
			default:
			{flagOut = false; break; }
		}
	}
}

void GameManager::ManageTeams() {
	int  numberOfPlayers, level, choice, type;
	char name[NAME_LEN], f_name[NAME_LEN];
	long id;
	bool flagOut = true;

	while (flagOut)
	{
		std::cout << "Would you like to add or move Team ? 1-Add, 2-remove, else - exit." << endl;
		scan<int>(choice);
		switch (choice)
		{
			case 1:
			{
				int i;
				Team** m_NewTeams = new Team*[1 + m_teamsLength];
				
				for (i = 0; i < m_teamsLength; i++)
				{ m_NewTeams[i] = m_teams1[i];}

				std::cout << endl << "Name --> ";
				scan(name);
				std::cout << endl << "Number of Players in the team --> ";
				scan<int>(numberOfPlayers);

				Team* newTeam = new Team(name);
				m_NewTeams[i] = newTeam;
				

				for (int j = 0; j < numberOfPlayers; j++)
				{
					std::cout << endl << "Type of Player : 1-forwarder, 2- Defender, 3-GoalKeeper" << endl;
					scan<int>(type);
					std::cout << endl << "Player name --> ";
					scan(name);
					std::cout << endl << "Player first name --> ";
					scan(f_name);
					std::cout << endl << "Player id --> ";
					scan<long>(id);
					std::cout << endl << "Player Level 0-3, 0 if Default --> ";
					scan<int>(level);

					Player* newPlayer;

					switch (type)
					{
					case 1: newPlayer = new Forwarder(name, f_name, id, newTeam, (PlayerLevel)level);		break;
					case 2: newPlayer = new Defender(name, f_name, id, newTeam, (PlayerLevel)level);		break;
					case 3: newPlayer = new Goalkeeper(name, f_name, id, newTeam, (PlayerLevel)level);		break;
					default:
						throw exception("\nThe values where invalid.\n");
					}
					(*newTeam) += newPlayer;
				}
				std::cout << endl << "Trainer Name --> ";
				scan(name);
				std::cout << endl << "Trainer first Name --> ";
				scan(f_name);
				std::cout << endl << "Trainer ID --> ";
				scan<long>(id);
				(*newTeam) += new Trainer(name, f_name, id);
				delete []m_teams1;
				m_teams1 = m_NewTeams;
				m_teamsLength++;
				break;
			}
			case 2:
			{
				int teamNum;
				std::cout << "Choose a Team -->>" << endl;
				PrintDynamicArray(m_teamsLength, m_teams1);
				cout << "--> ";
				scan<int>(teamNum);
				teamNum--;
				Team** new_teams = new Team*[m_teamsLength - 1];
			
				for (int i = 0; i < teamNum; i++)
				{ new_teams[i] = m_teams1[i];}
			
				for (int i = teamNum + 1; i < m_teamsLength; i++)
				{ new_teams[i - 1] = m_teams1[i];}

				delete []m_teams1;
				m_teams1 = new_teams;
				m_teamsLength--;
				break;
			}
			default:{ flagOut = false; break; }
		}
	}
}

void GameManager::ManageGames() {
	int choice = 1;
	bool flagOut = true;

	while (flagOut)
	{
		std::cout << endl << "What would you like to do?  1-Add Game, 2-Cancel Game, else-exit." << endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
			case 1:	 { NewGame();			break; }
			case 2:	 { CancelGame();		break; }
			default: { flagOut = false;		break; }
		}
	}
}

void GameManager::ManageStadiums()
{
	int stadiumNum, choice;
	bool flagOut = true;

	while (flagOut)
	{
		std::cout << endl << "What would you like to do ? 1 - Add, 2 - Delete, 3 - Update, else - exit." << endl << "--> ";
		scan<int>(choice);
		switch (choice)
		{
			case 1:
			{
				char name[NAME_LEN];
				int Maxfans;
				Stadium* newM_Stadium = new Stadium[m_stadiumsLength + 1];
				std::cout << endl << "Enter stadium Name --> ";
				scan(name);
				std::cout << endl << "Enter max fans --> ";
				scan<int>(Maxfans);
				Stadium s = Stadium(name, Maxfans);

				for (int i = 0; i < m_stadiumsLength; i++)
				{ newM_Stadium[i] = m_stadiums[i]; }

				newM_Stadium[m_stadiumsLength] = s;
				delete[]m_stadiums;
				m_stadiums = newM_Stadium;
				m_stadiumsLength++;
				break;
			}
			case 2:
			{
				std::cout << endl << "Choose stadium number from list -->> " << endl;
				PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
				cout << "--> ";
				scan<int>(stadiumNum);
				stadiumNum--;
				Stadium* m_Newstadium = new Stadium[m_stadiumsLength - 1];
				for (int i = 0; i < stadiumNum; i++)
				{
					m_Newstadium[i] = m_stadiums[i];
				}
				for (int i = stadiumNum + 1; i < m_stadiumsLength; i++)
				{
					m_Newstadium[i - 1] = m_stadiums[i];
				}
				delete[]m_stadiums;
				m_stadiums = m_Newstadium;
				m_stadiumsLength--;
				break;
			}
			case 3:
			{
				std::cout << endl << "Enter stadium number from list -->> " << endl;
				PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
				cout << "--> ";
				scan<int>(stadiumNum);
				stadiumNum--;
				Stadium* m_Newstadium = new Stadium[m_stadiumsLength - 1];
				int updatedVal;
				std::cout << endl << "Choose value to be updated :  1- Name, 2- Max fans. " << endl;
				scan<int>(updatedVal);
				std::cout << endl << "Enter new value --> ";
				if (updatedVal == 1)
				{
					char val[NAME_LEN];
					scan(val);
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
	Team** teams = new Team*[2];
	int t1, t2, minutes, hours, day, month, year, maxFans;
	cout << endl << "List of all teams -->> " << endl;
	PrintDynamicArray(m_teamsLength, m_teams1);
	cout << endl << "Enter Team number 1 id --> ";
	scan<int>(t1);
	t1--;
	cout << endl << "Enter Team number 2 id --> ";
	scan<int>(t2);
	t2--;
	teams[0] = m_teams1[t1];
	teams[1] = m_teams1[t2];
	cout << endl << "Date -->> " << endl << "Day --> ";
	scan<int>(day);
	std::cout << endl << "Month --> ";
	scan<int>(month);
	std::cout << endl << "Year --> ";
	scan<int>(year);
	std::cout << endl << "Time -->> " << endl << "Hours  --> ";
	scan<int>(hours);
	std::cout << endl << "Minutes --> ";
	scan<int>(minutes);
	std::cout << endl << "Number of maximum fans --> ";
	scan<int>(maxFans);
	Date d = Date(year, month, day);
	Time t = Time(hours, minutes);

	TimeAndDate tad = TimeAndDate(t, d);
	g = new Game(teams, tad, maxFans);
	Game** new_games = new Game*[m_gamesLength + 1];
	for (int i = 0; i < m_gamesLength; i++)
	{ new_games[i] = m_games[i]; }

	new_games[m_gamesLength] = g;
	delete []m_games;
	m_games = new_games;
	m_gamesLength++;
	delete []teams;
	AddGame(g);
}


void GameManager::AddGame(Game* g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].AddGame(g))
		{ break; }
	}
}




void GameManager::RemoveGame(const Game* g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].RemoveGame(g))
		{ break; }
	}
}


void GameManager::GetGameLog()
{
	for (int i = 0; i < m_gamesLength; i++)
	{ std::cout << *(m_games[i]) << endl; }
}


void GameManager::GetMonthSummary()
{
	int year, month;
	bool haveGamesFlag = false;
	cout << endl << "Enter Year --> ";
	scan<int>(year);

	cout << endl << "Enter Month --> ";
	scan<int>(month);

	// For month summary we need all the gaes in all the days this month
	cout << endl << "The Month summary: " << endl;
	for (int day = 1; day <= Date::DAYS_IN_MONTH[month-1]; day++)
	{
		Date d(year, month, day);
		GameList list = (*this)[d]; // Retrieve games schedule of specific day

		if (list.count > 0)
		{
			haveGamesFlag = true;
			cout << endl << "Printing Games on Date: " << d << endl;
			PrintDynamicArray(list.count, list.games);
			for (int i = 0; i < list.count; i++)
			{
				cout << endl << *(list.games[i]) << endl << "Winner : ";

				if (list.games[i]->GetWinner())
				{ cout << list.games[i]->GetWinner() << endl; }
				else
				{ cout << "Not yet determined." << endl; }
			}
		}
	}
	if (!haveGamesFlag)
	{ cout << " There are no games plated this month." << endl; }
}

void GameManager::GetTeamSummary()
{
	int team;
	std::cout << endl << "Choose team from list -->> " << endl;
	PrintDynamicArray(m_teamsLength, m_teams1);
	cout << "--> ";
	scan<int>(team);
	team--;
	std::cout << *(m_teams1[team]) << endl;
}

void GameManager::ManagePlayers()
{
	int playerNum, choice;
	int teamNum;
	bool flagOut = true;


	std::cout << endl << "Choose team from list -->>" << endl;
	PrintDynamicArray(m_teamsLength, m_teams1);
	cout << "--> ";
	scan<int>(teamNum);
	teamNum--;

	while (flagOut){
		cout << *(m_teams1[teamNum]) << endl << "What would you like to do ? 1-Add Player, 2- Delete Player, 3-Update Player, else - exit. " << endl;
		scan<int>(choice);
		switch (choice)
		{
		case 1:
		{
			int type, id, level;
			int pnum;
			char name[NAME_LEN], f_name[NAME_LEN];
			std::cout << endl << "Type of Player : 1-forwarder, 2- Defender,3-GoalKeeper";
			scan<int>(type);
			std::cout << endl << "Player name --> ";
			scan(name);
			std::cout << endl << "Player first name --> ";
			scan(f_name);
			std::cout << endl << "Player id --> ";
			scan<int>(id);
			std::cout << endl << "Player number --> ";
			scan<int>(pnum);
			std::cout << endl << "Player Level 0-3, 0 if Default --> ";
			scan<int>(level);

			Team* chosenTeam = m_teams1[teamNum];
			Player* newPlayer;

			switch (type)
			{
			case 1: {newPlayer = new Forwarder(name, f_name, id, chosenTeam, (PlayerLevel)level);		break; }
			case 2: {newPlayer = new Defender(name, f_name, id, chosenTeam, (PlayerLevel)level);			break; }
			case 3: {newPlayer = new Goalkeeper(name, f_name, id, chosenTeam, (PlayerLevel)level);		break; }
			default:
				throw exception("\nThe values where invalid.\n");
			}
			(*chosenTeam) += newPlayer;
			break;

		}
		case 2:
		{
			std::cout << endl << "Player number in the Team --> ";
			scan<int>(playerNum);
			*(m_teams1[teamNum]) -= (*(m_teams1[teamNum]))[playerNum];
			break;

		}
		case 3:
		{
			int choice2;
			std::cout << endl << "Player number in the Team --> ";
			scan<int>(playerNum);
			std::cout << endl << "What to update ? 1-name 2-strength";
			scan<int>(choice2);
			if (choice2 == 1)
			{
				char name[NAME_LEN];
				std::cout << endl << "Enter new value --> ";
				scan(name);
				(*(m_teams1[teamNum]))[playerNum]->SetName(name);
			}
			if (choice2 == 2)
			{
				int S;
				std::cout << endl << "Enter new value --> ";
				scan<int>(S);
				(*(m_teams1[teamNum]))[playerNum]->SetLevel((PlayerLevel)S);
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

	cout << endl << "Choose game from list below -->> " << endl;
	PrintDynamicArray(m_gamesLength, m_games);
	cout << "--> ";
	scan<int>(gameNum);
	gameNum--;
	if (gameNum < m_gamesLength && gameNum >= 0)
	{
		m_games[gameNum]->StartGame();
		cout << "The Game has started. " << endl;
	}
}
void GameManager::ManageGameSchedule()
{
	int choice;
	bool flagOut = true;

	while (flagOut)
	{
		std::cout << "What Would you like to do ? 1 - view, 2- cancel Game, else - exit. \n";
		scan<int>(choice);
		switch (choice)
		{
			case 1:
			{
				if (m_gamesLength > 0)
				{ PrintDynamicArray(m_gamesLength, m_games);	}
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
	for (int i = 0; i < m_teamsLength; i++)
	{
		std::cout << *(m_teams1[i]);
		int wins = 0;
		for (int j = 0; j < m_gamesLength; j++)
		{
			Team* winner = m_games[j]->GetWinner();
			Team* teamForStats = m_teams1[i];

			if (winner && *winner == *teamForStats) { wins++;}
		}
		std::cout << " Wins = " << wins << endl;
	}
}


void GameManager::TryInputMethod()
{
	try{ Redirect2File("in.txt"); }
	catch (exception e){ std::cout << "unable to read from file.\n"; }
	if (cin.bad()) { std::cout << "Bad redirect."; }
}