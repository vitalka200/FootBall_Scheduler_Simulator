#include "GameManager.h"

#include <ostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const GameList GameManager::operator[](const Date& d) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = m_gamesLength;
	int length = 0;
	for (int i = 0; i < m_stadiumsLength; i++){
		const GameList gameList = m_stadiums[i].GetGamesByDate(d);
		for (int j = 0; j < gameList.count; j++)
		{ res.games[res.count++] = gameList.games[j]; }
	}
	return res;
}

const GameList GameManager::operator[](const TimeAndDate& tad) const
{
	GameList res;
	res.games = new Game[m_gamesLength];
	res.count = m_gamesLength;
	int length =0 ;
	for (int i = 0; i < m_stadiumsLength; i++){
		if (m_stadiums[i].GetGameByTimeAndDate(tad))
		{ res.games[res.count++] = *(m_stadiums[i].GetGameByTimeAndDate(tad));}
	}
	return res;
}

void GameManager::CancelGame(){
	Game gameToCancel();
	int stadium_num , game_num , game_date;

	cout << "choose a stadium :: \n";
	for (int i = 0; i < m_stadiumsLength; i++)
	{
		cout << "\n" <<i << ")" << m_stadiums[i].GetName();
	}
	cin >> stadium_num;

	cout << "please choose a Date :: \n";
	GamesByTimeDateNode* gamesList = m_stadiums[stadium_num].m_gameList;
	for (int i = 0; i < m_stadiums[stadium_num].m_numOfNodes; i++)
	{cout << i << " - " << gamesList[i].GetDate() << "\n";}
	
	cin >> game_date;

	cout << "please choose a game :: \n";
	for (int i = 0; i < gamesList[game_date].GetGamesCount(); i++)
	{cout << i << " - " << gamesList[game_date].GetGameById(i) << "\n";}
	
	cin >> game_num;
	m_stadiums[stadium_num].RemoveGame(&(gamesList[game_date].GetGameById(game_num)));
}

void GameManager::SellTickets(){
	int sold = 0, pick;
	srand(time(NULL));
	for (int i = 0; i < m_games[m_gamesLength - 1].GetMaxFans(); i++)
	{
		pick = rand()%2;
		if (pick)
			{ m_games[m_gamesLength - 1] += Fan("name" + i ); }
	}
}

void GameManager::ManageTrainers(){
	//get game length.
	int length;
	char* name, *f_name;
	long id;
	for (int i = 0; i<length; i++)
	{
		cout << "\nteam number " << i << ".\nenter Name :";
		cin >> name;
		cout << "\nenter first Name :";
		cin >> f_name;
		cout << "\nenter id :";
		cin >> id;
		m_teams[i]+=(new Trainer(name, f_name, id));
	}
}

void GameManager::ManageReferees(){
	int numberOfReferees, choice;
	cout << "Would you like to add or remove Referee ? add- 1, remove - 2";
	cin >> choice;
	if (choice == 1){
		cout << "Please enter number of Referees : " << endl;
		cin >> numberOfReferees;
		char*name, *f_name;
		long id;
		for (int i = 0; i < numberOfReferees; i++)
		{
			cout << "\nenter Name:";
			cin >> name;
			cout << "\nenter first name :";
			cin >> f_name;
			cout << "\nenter id: ";
			cin >> id;
			m_referees[i] = Referee(name, f_name, id);
		}
	}
	else{
		int ref;
		for (int i = 0; i < m_RefereesLength; i++)
			cout << i << "-" << m_referees[i] << endl;
		cin >> ref;
		Referee* new_referee = new Referee[m_RefereesLength - 1];
		for (int i = 0; i < ref; i++)
			{ new_referee[i] = m_referees[i];}
		for (int i = ref + 1; i < m_gamesLength; i++)
			{ new_referee[i - 1] = m_referees[i];}
		m_RefereesLength--;
		delete []m_referees;
		m_referees = new_referee;
	}
}

void GameManager::ManageTeams(){
	int numberOfTeams, numberOfP, level, pnum, type;
	char*name, *f_name;
	long id;
	cout << "Would you like to add or move Team ? add - 1 , remove - 2 \n";
	cin >> type;
	if (type == 1){
		cout << "Please enter number of Referees : " << endl;
		cin >> numberOfTeams;
		for (int i = 0; i < numberOfTeams; i++)
		{
			cout << "\nTeam number : " << i << " \nenter Name:";
			cin >> name;
			m_teams[i] = Team(name);
			cout << "\nnumber of Players in the team :";
			cin >> numberOfP;
			for (int i = 0; i < numberOfP; i++)
			{
				cout << "\ntype of Player :: 1-forwarder , 2- Defender,3-GoalKeeper";
				cin >> type;
				cout << "\nPlayer name: ";
				cin >> name;
				cout << "\nPlayer first name : ";
				cin >> f_name;
				cout << "\nPlayer id: ";
				cin >> id;
				cout << "\nPlayer Level 0-4, 0 if Default : ";
				cin >> level;
				switch (type)
				{
				case 1: m_teams[i] += new Forwarder(name, f_name, id, pnum, &m_teams[i], (PlayerLevel)level);		break;
				case 2: m_teams[i] += new Defender(name, f_name, id, pnum, &m_teams[i], (PlayerLevel)level);		break;
				case 3: m_teams[i] += new Goalkeeper(name, f_name, id, pnum, &m_teams[i], (PlayerLevel)level);		break;
				default:
					throw exception("\nthe values where invalid.\n");
				}
			}
		}
		ManageTrainers();
	}
	else {
		int team_num;
		cout << "Please choose a team : \n";
		for (int i = 0; i < m_teamsLength; i++)
		{ cout << i << "-" << m_teams[i] << endl; }
		cin >> team_num;
		Team * new_teams = new Team[m_teamsLength - 1];
		for (int i = 0; i < team_num; i++)
			{ new_teams[i] = m_teams[i]; }
		for (int i = team_num + 1; i < m_teamsLength; i++)
			{ new_teams[i-1] = m_teams[i]; }
		delete []m_teams;
		m_teams = new_teams;
		m_teamsLength--;
	}
}

void GameManager::ManageGames(){
	char yn = 'Y';
	int c = 1;
	while (c == 1 || c == 2)
	{
		cout << "\nPlease enter Choice :\n 1-Add Game , 2-Cancel Game else-exit";
		cin >> c;
		switch (c)
		{
		case 1:
			while (yn == 'Y'){
				cout << "\nWould you like to add a new Game? : Y -yes,N-no";
				cin >> yn;
				if (yn == 'Y'){
					NewGame();
				}
			}
		case 2:
			while (yn == 'Y'){
				cout << "\nWould you like to Cancel Game? : Y -yes,N-no";
				cin >> yn;
				if (yn == 'Y'){
					CancelGame();
				}
			}
		}
	}

}

void GameManager::NewGame(){
	Game* g = NULL;
	Team* teams = new Team[2];
	int t1, t2, minutes, hours, day, month, year, maxFans, length;
	cout << "Please choose teams : \n";
	for (int i = 0; i < m_teamsLength; i++)
	{ cout << i << "-" << m_teams[i] << endl; }
	cout << "\nPlease enter Team number 1 id :- ";
	cin >> t1;
	cout << "\nPlease enter Team number 2 id :- ";
	cin >> t2;
	teams[0] = m_teams[t1];
	teams[1] = m_teams[t2];
	cout << "\nenter date :  day month year :: ";
	cin >> day >> month >> year;
	cout << "\nenter time :  hourse minutes :: ";
	cin >> hours >> minutes;
	cout << "\nPlease enter number of maximum fans : ";
	cin >> maxFans;
	Date d = Date(day, month, year);
	Time t = Time(hours, minutes);
	TimeAndDate tad = TimeAndDate(t, d);
	g = new Game(teams, tad, maxFans);
	Game* new_games  = new Game[m_gamesLength + 1];
	for (int i = 0; i < m_gamesLength; i++)
		{ new_games[i] = m_games[i]; }
	new_games[m_gamesLength] = *g;
	m_gamesLength++;
	free(teams);
	AddGame(*g);
}


void GameManager::AddGame(const Game& g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].AddGame(&g))
		{ break; }
	}
}




void GameManager::RemoveGame(const Game& g)
{
	for (int i = 0; i<m_stadiumsLength; i++)
	{
		if (m_stadiums[i].RemoveGame(&g))
		{ break; }
	}
}
