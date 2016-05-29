#include "Game.h"
#include "Stadium.h"
#include "TimeAndDate.h"
#include <string>
#include <vector>


GamesByTimeDateNode::GamesByTimeDateNode(const Date& date)
	: m_date(NULL)
{ m_date = new Date(date); }

const GamesByTimeDateNode& GamesByTimeDateNode::operator=(const GamesByTimeDateNode& gt)
{
	if (this != &gt)
	{
		m_date       = new Date(*gt.m_date);
		SetGames(gt.m_games);
	}
	return *this;
}

bool GamesByTimeDateNode::AddGame(Game* g)
{
	// Let's check if time available
	Time newGameTime = g->GetTimeAndDate()->GetTime();

	for (int i = 0; i < m_games.size(); i++)
	{
		Time existingGameTime = m_games[i]->GetTimeAndDate()->GetTime();
		
		if (existingGameTime == newGameTime || existingGameTime + g->MAX_GAME_LEN > newGameTime )
		{ return false;	} // We found game scheduled to the same time
		else if (newGameTime < existingGameTime && newGameTime <= existingGameTime - g->MAX_GAME_LEN)
		{
			// we found not scheduled time slice. Let's make some space
			m_games.insert(m_games.begin() + i, g);	return true;
		}
	}
	// We not found any time collisions. Let's add game
	m_games.push_back(g);
	return true;
}

bool GamesByTimeDateNode::RemoveGame(const Game* g)
{
	// Let's try to find this game
	for (int i = 0; i < m_games.size(); i++)
	{
		if ((*(m_games[i])) == *g)
		{ m_games.erase(m_games.begin() + i); return true; }
	}
	return false;
}

void GamesByTimeDateNode::SetGames(std::vector<Game*> games)
{
	m_games.clear();
	m_games = games;
}

void GamesByTimeDateNode::SetDate(const Date& d)
{
	delete m_date;
	m_date = new Date(d);
}

const GameList& GameList::operator=(const GameList& gl)
{
	if (this != &gl)
	{
		count = gl.count;
		
		games = new Game*[count];
		for (int i= 0; i < count; i++)
		{ games[i] = gl.games[i]; }
	}
	return *this;
}

const Stadium& Stadium::operator=(const Stadium& s)
{
	if (this != &s)
	{
		SetMaxFans(m_maxFans);
		SetName(s.m_name);
		SetGameList(s.m_gameList);
	}
	return *this;
}

Game* Stadium::GetGameByTimeAndDate(const TimeAndDate& tad) const
{
	GameList* glByDate = &(GetGamesByDate(tad.GetDate()));

	for (int i = 0; i < glByDate->count; i++)
	{
		if (*(glByDate->games[i]->GetTimeAndDate()) == tad)
		{ return glByDate->games[i]; }
	}
	return NULL;
}

GameList Stadium::GetGamesByDate(const Date& d) const
{
	GameList gl;

	for (int i = 0; i < m_gameList.size(); i++)
	{
		if (d == *(m_gameList[i].GetDate()))
		{
			gl.games = new Game*[m_gameList[i].m_games.size()];
			gl.count = m_gameList[i].m_games.size();

			for (int j = 0; j < m_gameList[i].m_games.size(); j++)
			{ gl.games[j] =  m_gameList[i].m_games[j]; }

			return gl;
		}
	}
	// Game not found
	return gl;
}

bool Stadium::AddGame(Game* g)
{
	for (int i = 0; i < m_gameList.size(); i++)
	{
		if (*(m_gameList[i].GetDate()) == g->GetTimeAndDate()->GetDate())
		{ return m_gameList[i].AddGame(g); }
		else if (*(m_gameList[i].GetDate()) < g->GetTimeAndDate()->GetDate())
		{
			// We can't find GameNode for specified date.
			// This date not scheduled for any game
			// Let's create one
			GamesByTimeDateNode node = GamesByTimeDateNode(g->GetTimeAndDate()->GetDate());
			node.AddGame(g);
			m_gameList.insert(m_gameList.begin() + i, node);

			return true;
		}
	}
	// We reached end of list but not found where to add new game
	// Let's add it to end of list
	GamesByTimeDateNode node = GamesByTimeDateNode(g->GetTimeAndDate()->GetDate());
	node.AddGame(g);
	m_gameList.push_back(node);
	return true;
}

bool Stadium::RemoveGame(const Game* g)
{
	// Find Date
	Date date = g->GetTimeAndDate()->GetDate();
	for (int i = 0; i < m_gameList.size(); i++)
	{
		if (*(m_gameList[i].GetDate()) == date)
		{
			// We found correct date. Let's try to remove
			return m_gameList[i].RemoveGame(g);
		}
	}
	// Game not found on all dates
	return false;
}

bool Stadium::MoveGameTime(const Game* g, const TimeAndDate& newTad)
{
	// It doen't matter if game not exists
	RemoveGame(g);
	// Create new Game with specified TimeAndDate
	Game newGame = Game(*g);
	newGame.SetTime(newTad);
	return AddGame(&newGame);
}

void Stadium::SetGameList(const std::vector<GamesByTimeDateNode> list)
{ m_gameList = list; }

std::ostream & operator<<(std::ostream& os, const GamesByTimeDateNode & node)
{
	for (int i = 0; i < node.m_games.size(); i++)
	{ os << node.m_games[i] << std::endl; }
	return os;
}
