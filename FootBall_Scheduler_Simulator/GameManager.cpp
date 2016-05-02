
#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <time.h>
#include <stdlib.h>

#define NAME_LEN 20

using namespace std;
ifstream in("");


/*
*	For functionality And Exception handling
*/

template<class T>
void PrintArray(int length, T* arr)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << i + 1 << ")" << arr[i] << endl;
	}
}


void clearCin()
{
	cin.clear(); while (cin.get() != '\n') { continue; }
}

//try
template<class T>
void scan(T& input) {
	while (true)
	{
		std::cin >> input;
		if (cin.good())
		{
			cout << input << endl; break;
		}
		else
		{
			std::cout << endl << "Wrong input. Please reenter" << endl; clearCin();
		}
	}
	clearCin();
}




void GameManager::Redirect2File(char* inFileName)
{
	in = ifstream(inFileName);
	if (!in.good()) throw exception();
	// actual redirect
	cin.rdbuf(in.rdbuf());
}

void GameManager::Redirect2ios()
{
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(cinbuf);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(coutbuf);
}

/*
End
*/
 GameList GameManager::operator[](const Date& d) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = 0;
	int length = 0;
	for (int i = 0; i < m_stadiumsLength; i++) {
		GameList gameList = m_stadiums[i].GetGamesByDate(d);
		for (int j = 0; j < gameList.count; j++)
		{
			res.games[res.count++] = gameList.games[j];
			length++;
		}
	}
	GameList newRes;
	newRes.count = length;
	for (int i = 0; i < length; i++)
	{
		newRes.games[i] = res.games[i];
	}
	return newRes;
}

const GameList GameManager::operator[](const TimeAndDate& tad) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = 0;
	int length = 0;
	for (int i = 0; i < m_stadiumsLength; i++) {
		if (m_stadiums[i].GetGameByTimeAndDate(tad))
		{
			res.games[res.count++] = *(m_stadiums[i].GetGameByTimeAndDate(tad));
		}
	}
	return res;
}

void GameManager::CancelGame() {
	int stadium_num, game_num, game_date;
	std::cout << "choose a stadium :: \n";
	PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
	scan<int>(stadium_num);
	stadium_num--;
	std::cout << "please choose a Date :: \n";
	GamesByTimeDateNode* gamesList = m_stadiums[stadium_num].m_gameList;
	for (int i = 0; i < m_stadiums[stadium_num].m_numOfNodes; i++)
	{
		std::cout << i << " - " << gamesList[i].GetDate() << endl << "";
	}

	scan<int>(game_date);

	std::cout << "please choose a game :: \n";
	for (int i = 0; i < gamesList[game_date].GetGamesCount(); i++)
	{
		std::cout << i << " - " << gamesList[game_date].GetGameById(i) << endl << "";
	}

	scan<int>(game_num);
	m_stadiums[stadium_num].RemoveGame(&(gamesList[game_date].GetGameById(game_num)));
}

void GameManager::SellTickets() {
	int sold = 0, pick;
	srand(time(NULL));
	for (int i = 0; i < m_games[m_gamesLength - 1].GetMaxFans(); i++)
	{
		pick = rand() % 2;
		if (pick)
		{
			m_games[m_gamesLength - 1] += Fan("name");
		}
	}
}

void GameManager::ManageTrainers() {
	char name[NAME_LEN], f_name[NAME_LEN];
	long id;
	for (int i = 0; i<m_teamsLength; i++)
	{
		std::cout << endl << "team number " << i << ".\nenter Name :";
		scan(name);
		std::cout << endl << "enter first Name :";
		scan(f_name);
		std::cout << endl << "enter id :";
		scan<long>(id);
		m_teams[i] += (new Trainer(name, f_name, id));
	}
}

void GameManager::ManageReferees() {
	int numberOfReferees, choice;
	std::cout << endl << "Would you like to add or remove Referee ?  1 - add, 2- remove \n";
	scan<int>(choice);
	if (choice == 1) {
		std::cout << "Please enter number of Referees : " << endl;
		scan<int>(numberOfReferees);
		Referee* m_newReferees = new Referee[m_refereesLength + numberOfReferees];
		for (int i = 0; i < m_refereesLength; i++)
		{
			m_newReferees[i] = m_referees[i];
		}
		char name[NAME_LEN], f_name[NAME_LEN];
		long id;
		for (int i = m_refereesLength; i < numberOfReferees + m_refereesLength; i++)
		{
			std::cout << endl << "enter Name:";
			scan(name);
			std::cout << endl << "enter first name :";
			scan(f_name);
			std::cout << endl << "enter id: ";
			scan<long>(id);
			m_newReferees[i] = Referee(name, f_name, id);
		}
		delete[]m_referees;
		m_referees = m_newReferees;
		m_refereesLength += numberOfReferees;
	}
	else {
		int ref;
		for (int i = 0; i < m_refereesLength; i++)
			std::cout << i << "-" << m_referees[i] << endl;
		scan<int>(ref);
		Referee* new_referee = new Referee[m_refereesLength - 1];
		for (int i = 0; i < ref; i++)
		{
			new_referee[i] = m_referees[i];
		}
		for (int i = ref + 1; i < m_gamesLength; i++)
		{
			new_referee[i - 1] = m_referees[i];
		}
		m_refereesLength--;
		delete[]m_referees;
		m_referees = new_referee;
	}
}

void GameManager::ManageTeams() {
	int numberOfTeams, numberOfPlayers, level, type;
	char name[NAME_LEN], f_name[NAME_LEN];
	long id;
	std::cout << "Would you like to add or move Team ? add - 1 , remove - 2 \n";
	scan<int>(type);
	if (type == 1) {
		std::cout << "Please enter number of Teams : " << endl;
		scan<int>(numberOfTeams);//call try
		Team* m_NewTeams = new Team[numberOfTeams + m_teamsLength];

		for (int i = m_teamsLength; i < m_teamsLength; i++)
		{
			m_NewTeams[i] = m_teams[i];
		}

		for (int i = m_teamsLength; i < numberOfTeams + m_teamsLength; i++)
		{
			std::cout << endl << "Team number : " << i + 1 << " \nenter Name:";
			//std::cin >> name);
			scan(name);
			std::cout << endl << "number of Players in the team :";
			scan<int>(numberOfPlayers);
			Team t = Team(name);

			for (int i = 0; i < numberOfPlayers; i++)
			{
				std::cout << endl << "type of Player :: 1-forwarder , 2- Defender,3-GoalKeeper\n";
				scan<int>(type);
				std::cout << endl << "Player name: ";
				scan(name);
				std::cout << endl << "Player first name : ";
				scan(f_name);
				std::cout << endl << "Player id: ";
				scan<long>(id);
				std::cout << endl << "Player Level 0-4, 0 if Default : ";
				scan<int>(level);
				switch (type)
				{
				case 1: t += new Forwarder(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				case 2: t += new Defender(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				case 3: t += new Goalkeeper(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				default:
					throw exception("\nthe values where invalid.\n");
				}
			}
			std::cout << endl << "enter Trainer Name :";
			scan(name);
			std::cout << endl << "enter Trainer first Name :";
			scan(f_name);
			std::cout << endl << "enter Trainer id :";
			scan<long>(id);
			t += (new Trainer(name, f_name, id));
			m_NewTeams[i] = t;
		}
		m_teams = m_NewTeams;
		m_teamsLength += numberOfTeams;
	}
	else {
		int team_num;
		std::cout << "Please choose a team : \n";
		PrintArray<Team>(m_teamsLength, m_teams);
		scan<int>(team_num);
		team_num--;
		Team * new_teams = new Team[m_teamsLength - 1];
		for (int i = 0; i < team_num; i++)
		{
			new_teams[i] = m_teams[i];
		}
		for (int i = team_num + 1; i < m_teamsLength; i++)
		{
			new_teams[i - 1] = m_teams[i];
		}
		delete[]m_teams;
		m_teams = new_teams;
		m_teamsLength--;
	}
}

void GameManager::ManageGames() {
	char yn = 'Y';
	int c = 1;
	while (1)
	{
		std::cout << endl << "Please enter Choice :\n 1-Add Game , 2-Cancel Game else-exit \n";
		scan<int>(c);
		if (c != 1 && c != 2)
			break;
		switch (c)
		{
		case 1:
			while (yn == 'Y') {
				std::cout << endl << "Would you like to add a new Game? : Y -yes,N-no \n";
				scan<char>(yn);
				if (yn == 'Y') {
					NewGame();
				}
			}
			break;
		case 2:
			while (yn == 'Y') {
				std::cout << endl << "Would you like to Cancel Game? : Y -yes,N-no \n";
				scan<char>(yn);
				if (yn == 'Y') {
					CancelGame();
				}
			}
			break;
		}
	}

}

void GameManager::ManageStadiums()
{
	int Stdm, Cs;
	std::cout << "Managing stadiums" << endl;
	std::cout << "What would you like to do ? 1 - Delete, 2 - Update, 3 - Add \n";
	scan<int>(Cs);

	if (Cs != 3)
	{
		std::cout << "Enter stadium number from list --> \n\n";
		PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
		scan<int>(Stdm);
		Stdm--;
		Stadium* m_Newstadium = new Stadium[m_stadiumsLength - 1];
		if (Cs == 1)
		{
			for (int i = 0; i < Stdm; i++)
			{
				m_Newstadium[i] = m_stadiums[i];
			}
			for (int i = Stdm + 1; i < m_stadiumsLength; i++)
			{
				m_Newstadium[i - 1] = m_stadiums[i];
			}
			m_stadiums = m_Newstadium;
			m_stadiumsLength--;
		}
		else
		{
			int UpD;
			std::cout << "Choose value to be updated :  1- Name, 2- Max fans \n";
			scan<int>(UpD);
			std::cout << "Enter new value";
			if (UpD == 1)
			{
				char val[NAME_LEN];
				scan(val);
				m_stadiums[Stdm].SetName(val);
			}
			if (UpD == 2)
			{
				int val;
				scan<int>(val);
				m_stadiums[Stdm].SetMaxFans(val);
			}
		}

	}
	else
	{
		char name[NAME_LEN];
		int Maxfans;
		Stadium* newM_Stadium = new Stadium[m_stadiumsLength + 1];
		std::cout << "Enter stadium Name : ";
		scan(name);
		std::cout << endl << "Enter max fans : ";
		scan<int>(Maxfans);
		Stadium s = Stadium(name, Maxfans);
		for (int i = 0; i < m_stadiumsLength; i++)
		{
			newM_Stadium[i] = m_stadiums[i];
		}
		newM_Stadium[m_stadiumsLength] = s;
		delete[]m_stadiums;
		m_stadiums = newM_Stadium;
		m_stadiumsLength++;
	}
}

void GameManager::NewGame() {
	Game* g = NULL;
	Team* teams = new Team[2];
	int t1, t2, minutes, hours, day, month, year, maxFans;
	std::cout << "Please choose teams : \n";
	PrintArray<Team>(m_teamsLength, m_teams);
	std::cout << endl << "Please enter Team number 1 id :- ";
	scan<int>(t1);
	t1--;
	std::cout << endl << "Please enter Team number 2 id :- ";
	scan<int>(t2);
	t2--;
	teams[0] = m_teams[t1];
	teams[1] = m_teams[t2];
	std::cout << endl << "enter date : " << "\n day: ";
	scan<int>(day);
	std::cout << "\nmonth : ";
	scan<int>(month);
	std::cout << "\nyear : ";
	scan<int>(year);
	std::cout << endl << "enter time :" << "\nhours : ";
	scan<int>(hours);
	std::cout << "\nminutes :";
	scan<int>(minutes);
	std::cout << endl << "Please enter number of maximum fans : ";
	scan<int>(maxFans);
	Date d = Date(day, month, year);
	Time t = Time(hours, minutes);
	TimeAndDate tad = TimeAndDate(t, d);
	g = new Game(teams, tad, maxFans);
	Game* new_games = new Game[m_gamesLength + 1];
	for (int i = 0; i < m_gamesLength; i++)
	{
		new_games[i] = m_games[i];
	}
	new_games[m_gamesLength] = *g;
	delete[]m_games;
	m_games = new_games;
	m_gamesLength++;
	//delete[]teams;
	//AddGame(*g);
}


void GameManager::AddGame(const Game& g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].AddGame(&g))
		{
			break;
		}
	}
}




void GameManager::RemoveGame(const Game& g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].RemoveGame(&g))
		{
			break;
		}
	}
}


void GameManager::GetGameLog()
{
	for (int i = 0; i < m_gamesLength; i++)
		std::cout << m_games[i] << endl;
}


void GameManager::GetMonthSummary()
{
	int year, month;
	std::cout << "Enter Year :";
	scan<int>(year);

	std::cout << "Enter Month :";
	scan<int>(month);
	Date d = Date(year, month);
	GameList list = (*this)[d];

	PrintArray<Game>(list.count, list.games);
	if (list.count==0)
	{
		cout << "There are no games this month!." << endl;
	}
	else
	{
		std::cout << "The Month summary: \n";
		for (int i = 0; i < list.count; i++) {
			std::cout << list.games[i] << "winner";
			if (list.games[i].GetWinner())
				std::cout << list.games[i].GetWinner() << endl;
			else
				std::cout << "Not yet determined" << endl;
		}
	}


}

void GameManager::GetTeamSummary()
{
	int Tm;
	std::cout << "Choose team number -->" << endl;
	PrintArray<Team>(m_teamsLength, m_teams);
	scan<int>(Tm);
	Tm--;
	std::cout << m_teams[Tm] << endl;
}

void GameManager::ManagePlayers()
{
	int p, Cs;
	//GetTeamSummary();
	int Tm;
	std::cout << "Choose team number -->" << endl;
	PrintArray<Team>(m_teamsLength, m_teams);
	scan<int>(Tm);
	Tm--;
	std::cout << m_teams[Tm] << '\n' << "What would you like to do ? 1-delete 2- update 3- add \n";
	scan<int>(Cs);
	switch (Cs)
	{
	case 1:
	{
		std::cout << "Enter Player number in the Team";
		scan<int>(p);
		m_teams[Tm] -= m_teams[Tm][p];
		break;
	}
	case 2:
	{
		int Cs2;
		std::cout << "Enter Player number in the Team";
		scan<int>(p);
		std::cout << endl << "What to update ? 1-name 2-strength";
		scan<int>(Cs2);
		if (Cs2 == 1)
		{
			char name[NAME_LEN];
			std::cout << "Enter value : ";
			scan(name);
			m_teams[Tm][p]->SetName(name);
		}
		if (Cs2 == 2)
		{
			int S;
			std::cout << "Enter value : ";
			scan<int>(S);
			m_teams[Tm][p]->SetLevel(PlayerLevel(S));
		}
		break;
	}
	case 3:
	{
		int type, id, level;
		int pnum;
		char name[NAME_LEN], f_name[NAME_LEN];
		std::cout << endl << "type of Player :: 1-forwarder , 2- Defender,3-GoalKeeper";
		scan<int>(type);
		std::cout << endl << "Player name: ";
		scan(name);
		std::cout << endl << "Player first name : ";
		scan(f_name);
		std::cout << endl << "Player id: ";
		scan<int>(id);
		std::cout << endl << "Player number : ";
		scan<int>(pnum);
		std::cout << endl << "Player Level 0-4, 0 if Default : ";
		scan<int>(level);

		switch (type)
		{
		case 1: {m_teams[Tm] += new Forwarder(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break; }
		case 2: {m_teams[Tm] += new Defender(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break; }
		case 3: {m_teams[Tm] += new Goalkeeper(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break; }
		default:
			throw exception("\nthe values where invalid.\n");
		}
		break;
	}
	default:
	{	break; }
	}
}

void GameManager::StartGame()
{

}
void GameManager::ManageGameSchedule()
{
	int c;
	bool caseWhile = true;
	std::cout << "What Would you like to do ? 1 - view, 2- cancel Game. \n";
	scan<int>(c);
	switch (c)
	{
	case 1:
	{
		if (m_gamesLength > 0)
		{
			PrintArray<Game>(m_gamesLength, m_games);
		}
		break;
	}
	case 2:
	{
		CancelGame();
		break;
	}
	default:
	{break; }
	}
}
void GameManager::GetStats()
{
	for (int i = 0; i < m_teamsLength; i++)
	{
		std::cout << m_teams[i];
		int wins = 0;
		for (int num = 0; num < m_gamesLength; num++){
			if ((m_games[i].GetWinner()) == &m_teams[i])
				wins++;
		}
		std::cout << "Wins = " << wins << endl;
	}
}


void GameManager::TryInputMethod()
{
	try{ Redirect2File("in.txt"); }
	catch (exception e){ std::cout << "unable to read from file.\n"; }
	if (cin.bad()) { std::cout << "Bad redirect."; }
}