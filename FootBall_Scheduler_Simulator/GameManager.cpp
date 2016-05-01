#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <time.h>
#include <stdlib.h>

using namespace std;


/*
*	For functionality And Exception handling
*/

template<class T>
void PrintArray(int length, T* arr)
{
	for (int i = 0; i < length; i++)
	{
		cout << i << ")" << arr[i] << endl;
	}
}

template<class S>
void scan(S* Input) {
	S var;
	try
	{
		cin >> var;
	}
	catch (int e)
	{
		cout << endl << "\nAn exception occurred.Exception number : " << e << '\n';
		exit(0);
	}
	*Input = var;
}

void scan_chars(char* input) {
	cin >> input;
}

void GameManager::Redirect2File(char* inFileName, char* outFileName)
{
	std::ifstream in(inFileName);
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(in.rdbuf());

	std::ofstream out(outFileName);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

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
const GameList GameManager::operator[](const Date& d) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = m_gamesLength;
	int length = 0;
	for (int i = 0; i < m_stadiumsLength; i++) {
		const GameList gameList = m_stadiums[i].GetGamesByDate(d);
		for (int j = 0; j < gameList.count; j++)
		{
			res.games[res.count++] = gameList.games[j];
		}
	}
	return res;
}

const GameList GameManager::operator[](const TimeAndDate& tad) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = m_gamesLength;
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
	cout << "choose a stadium :: \n";
	PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
	scan<int>(&stadium_num);

	cout << "please choose a Date :: \n";
	GamesByTimeDateNode* gamesList = m_stadiums[stadium_num].m_gameList;
	for (int i = 0; i < m_stadiums[stadium_num].m_numOfNodes; i++)
	{
		cout << i << " - " << gamesList[i].GetDate() << endl << "";
	}

	scan<int>(&game_date);

	cout << "please choose a game :: \n";
	for (int i = 0; i < gamesList[game_date].GetGamesCount(); i++)
	{
		cout << i << " - " << gamesList[game_date].GetGameById(i) << endl << "";
	}

	scan<int>(&game_num);
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
			m_games[m_gamesLength - 1] += Fan("name" + i);
		}
	}
}

void GameManager::ManageTrainers() {
	char name[20], f_name[20];
	long id;
	for (int i = 0; i<m_teamsLength; i++)
	{
		cout << endl << "team number " << i << ".\nenter Name :";
		scan_chars(name);
		cout << endl << "enter first Name :";
		scan_chars(f_name);
		cout << endl << "enter id :";
		scan<long>(&id);
		m_teams[i] += (new Trainer(name, f_name, id));
	}
}

void GameManager::ManageReferees() {
	int numberOfReferees, choice;
	cout << endl << "Would you like to add or remove Referee ?  1 - add, 2- remove";
	scan<int>(&choice);
	if (choice == 1) {
		cout << "Please enter number of Referees : " << endl;
		scan<int>(&numberOfReferees);
		Referee* m_newReferees = new Referee[m_refereesLength + numberOfReferees];
		for (int i = 0; i < m_refereesLength; i++)
		{
			m_newReferees[i] = m_referees[i];
		}
		char name[20], f_name[20];
		long id;
		for (int i = m_refereesLength; i < numberOfReferees + m_refereesLength; i++)
		{
			cout << endl << "enter Name:";
			scan_chars(name);
			cout << endl << "enter first name :";
			scan_chars(f_name);
			cout << endl << "enter id: ";
			scan<long>(&id);
			m_newReferees[i] = Referee(name, f_name, id);
		}
		delete[]m_referees;
		m_referees = m_newReferees;
		m_refereesLength += numberOfReferees;
	}
	else {
		int ref;
		for (int i = 0; i < m_refereesLength; i++)
			cout << i << "-" << m_referees[i] << endl;
		scan<int>(&ref);
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
	char name[20], f_name[20];
	long id;
	cout << "Would you like to add or move Team ? add - 1 , remove - 2 \n";
	scan<int>(&type);
	if (type == 1) {
		cout << "Please enter number of Teams : " << m_teamsLength << endl;
		scan<int>(&numberOfTeams);
		Team* m_NewTeams = new Team[numberOfTeams + m_teamsLength];
		cout << numberOfTeams;

		for (int i = m_teamsLength; i < m_teamsLength; i++)
		{
			m_NewTeams[i] = m_teams[i];
		}

		for (int i = m_teamsLength; i < numberOfTeams + m_teamsLength; i++)
		{
			cout << endl << "Team number : " << i + 1 << " \nenter Name:";
			scan_chars(name);
			cout << endl << "number of Players in the team :";
			scan<int>(&numberOfPlayers);
			Team t = Team(name);

			for (int i = 0; i < numberOfPlayers; i++)
			{
				cout << endl << "type of Player :: 1-forwarder , 2- Defender,3-GoalKeeper\n";
				scan<int>(&type);
				cout << endl << "Player name: ";
				scan_chars(name);
				cout << endl << "Player first name : ";
				scan_chars(f_name);
				cout << endl << "Player id: ";
				scan<long>(&id);
				cout << endl << "Player Level 0-4, 0 if Default : ";
				scan<int>(&level);
				switch (type)
				{
				case 1: t += new Forwarder(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				case 2: t += new Defender(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				case 3: t += new Goalkeeper(name, f_name, id, &m_teams[i], (PlayerLevel)level);		break;
				default:
					throw exception("\nthe values where invalid.\n");
				}
			}
			cout << endl << "enter Trainer Name :";
			scan_chars(name);
			cout << endl << "enter Trainer first Name :";
			scan_chars(f_name);
			cout << endl << "enter Trainer id :";
			scan<long>(&id);
			t += (new Trainer(name, f_name, id));
			m_NewTeams[i] = t;
		}
		m_teams = m_NewTeams;
		m_teamsLength += numberOfTeams;
	}
	else {
		int team_num;
		cout << "Please choose a team : \n";
		PrintArray<Team>(m_teamsLength, m_teams);
		scan<int>(&team_num);
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
	while (true)
	{
		cout << endl << "Please enter Choice :\n 1-Add Game , 2-Cancel Game else-exit";
		scan<int>(&c);
		if (c != 1 && c != 2)
			switch (c)
			{
			case 1:
				while (yn == 'Y') {
					cout << endl << "Would you like to add a new Game? : Y -yes,N-no";
					scan<char>(&yn);
					if (yn == 'Y') {
						NewGame();
					}
				}
				break;
			case 2:
				while (yn == 'Y') {
					cout << endl << "Would you like to Cancel Game? : Y -yes,N-no";
					scan<char>(&yn);
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
	cout << "Managing stadiums" << endl;
	cout << "What would you like to do ? 1 - Delete 2 - Update 3 - Add";
	scan<int>(&Cs);

	if (Cs != 3)
	{
		cout << "Enter stadium number from list --> \n\n";
		PrintArray<Stadium>(m_stadiumsLength, m_stadiums);
		scan<int>(&Stdm);
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
			cout << "Choose value to be updated :  1- Name 2- Max fans";
			scan<int>(&UpD);
			cout << "Enter new value";
			if (UpD == 1)
			{
				char val[20];
				scan_chars(val);
				m_stadiums[Stdm].SetName(val);
			}
			if (UpD == 2)
			{
				int val;
				scan<int>(&val);
				m_stadiums[Stdm].SetMaxFans(val);
			}
		}

	}
	else
	{
		char name[20];
		int Maxfans;
		Stadium* newM_Stadium = new Stadium[m_stadiumsLength + 1];
		cout << "Enter stadium Name : ";
		scan_chars(name);
		cout << endl << "Enter max fans : ";
		scan<int>(&Maxfans);
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
	cout << "Please choose teams : \n";
	PrintArray<Team>(m_teamsLength, m_teams);
	cout << endl << "Please enter Team number 1 id :- ";
	scan<int>(&t1);
	cout << endl << "Please enter Team number 2 id :- ";
	scan<int>(&t2);
	teams[0] = m_teams[t1];
	teams[1] = m_teams[t2];
	cout << endl << "enter date :  day month year :: ";
	scan<int>(&day);
	scan<int>(&month);
	scan<int>(&year);
	cout << endl << "enter time :  hours minutes :: ";
	scan<int>(&hours);
	scan<int>(&minutes);
	cout << endl << "Please enter number of maximum fans : ";
	scan<int>(&maxFans);
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
	m_gamesLength++;
	delete[]teams;
	AddGame(*g);
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
		cout << m_games[i] << endl;
}


void GameManager::GetMonthSummary()
{
	int year, month;
	cout << "Enter Year :";
	scan<int>(&year);

	cout << "Enter Month :";
	scan<int>(&month);
	Date d = Date(year, month);
	GameList list = (*this)[d];
	cout << "The Month summary : \n";
	for (int i = 0; i < list.count; i++) {
		cout << list.games[i] << "winner : " << list.games[i].GetWinner();
	}
}

void GameManager::GetTeamSummary()
{
	int Tm;
	cout << "Choose team number -->" << endl;
	PrintArray<Team>(m_teamsLength, m_teams);
	scan<int>(&Tm);
	cout << m_teams[Tm] << endl;
}

void GameManager::ManagePlayers()
{
	int p, Cs;
	//GetTeamSummary();
	int Tm;
	cout << "Choose team number -->" << endl;
	PrintArray<Team>(m_teamsLength, m_teams);
	scan<int>(&Tm);
	cout << m_teams[Tm] << '\n' << "What would you like to do ? 1-delete 2- update 3- add";
	scan<int>(&Cs);
	switch (Cs)
	{
	case 1:
		cout << "Enter Player number in the Team";
		scan<int>(&p);
		m_teams[Tm] -= m_teams[Tm][p];
		break;
	case 2:
		int Cs2;
		cout << "Enter Player number in the Team";
		scan<int>(&p);
		cout << endl << "What to update ? 1-name 2-strength";
		scan<int>(&Cs2);
		if (Cs2 == 1)
		{
			char name[20];
			cout << "Enter value : ";
			scan_chars(name);
			m_teams[Tm][p]->SetName(name);
		}
		if (Cs2 == 2)
		{
			int S;
			cout << "Enter value : ";
			scan<int>(&S);
			m_teams[Tm][p]->SetLevel(PlayerLevel(S));
		}
		break;
	case 3:
		int type, id, level;
		int pnum;
		char name[20], f_name[20];
		cout << endl << "type of Player :: 1-forwarder , 2- Defender,3-GoalKeeper";
		scan<int>(&type);
		cout << endl << "Player name: ";
		scan_chars(name);
		cout << endl << "Player first name : ";
		scan_chars(f_name);
		cout << endl << "Player id: ";
		scan<int>(&id);
		cout << endl << "Player number : ";
		scan<int>(&pnum);
		cout << endl << "Player Level 0-4, 0 if Default : ";
		scan<int>(&level);

		switch (type)
		{
		case 1: m_teams[Tm] += new Forwarder(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break;
		case 2: m_teams[Tm] += new Defender(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break;
		case 3: m_teams[Tm] += new Goalkeeper(name, f_name, id, &m_teams[Tm], (PlayerLevel)level);		break;
		default:
			throw exception("\nthe values where invalid.\n");
		}
		break;
	default:
		break;
	}
}

void GameManager::StartGame() {

}
void GameManager::ManageGameSchedule() {
	int c;
	cout << "What Would you like to do ? 1 - view, 2- cancel Game. \n";
	scan<int>(&c);
	if (c == 1)
	{
		if (m_gamesLength>0)
			PrintArray<Game>(m_gamesLength, m_games);
	}
	if (c == 2)
	{
		CancelGame();
	}

}
void GameManager::GetStats() {
	for (int i = 0; i < m_teamsLength; i++)
	{
		cout << m_teams[i];
		int wins = 0;
		for (int num = 0; num < m_gamesLength; num++) {
			if ((m_games[i].GetWinner()) == &m_teams[i])
				wins++;
		}
		cout << "Wins = " << wins << endl;
	}
}