#ifndef __STADIUM_H
#define __STADIUM_H

#include <iostream>

class Game;
class TimeAndDate;
class Time;
class Date;
class GameManager;

class GamesByTimeDateNode
{
friend class Stadium;
public:
	GamesByTimeDateNode(const Date& date);
	~GamesByTimeDateNode()                                { delete m_date; delete []m_games; }
	GamesByTimeDateNode(const GamesByTimeDateNode& gt)
	    : m_date(NULL), m_games(NULL)                     { *this = gt; }

	const GamesByTimeDateNode& operator=(const GamesByTimeDateNode& gt);

	//Methods
	bool         AddGame(const Game* g);
	bool         RemoveGame(const Game* g);
	const Date*  GetDate()                          const { return m_date; }
	int          GetGamesCount()                    const { return m_numOfGames; }
	const Game&  GetGameById(int idx)               const { return m_games[idx]; }
	// operators
	const GamesByTimeDateNode& operator+=(Game* g)        { AddGame(g);    return *this; }
	const GamesByTimeDateNode& operator-=(const Game* g)  { RemoveGame(g); return *this; }

	friend std::ostream& operator<<(std::ostream& os, const GamesByTimeDateNode& node);

private:
	Date*  m_date;
	Game*  m_games;
	int    m_numOfGames;

	// Methods
	void SetGames(const Game* games, int count);

	// Hidden default c-tor. available only for Stadium
	GamesByTimeDateNode() : m_date(NULL),  m_games(NULL) { }
	void SetDate(const Date* d);
};

class GameList
{
public:
	Game* games;
	int   count;
	GameList() : games(NULL), count(0) { }
	GameList(const GameList& gl) : games(NULL), count(0) { *this = gl; }
	~GameList()                                          { delete []games; }
	
	const GameList& operator=(const GameList& gl);
};

class Stadium
{
friend class GameManager;
public:
	// c-tors, d-tors
	Stadium(const char* name = " ", int maxFans = 0)
		: m_name(NULL),  m_maxFans(maxFans),
		  m_gameList(NULL), m_numOfNodes(0)    { SetName(name); };
	Stadium(const Stadium& s)
		: m_name(NULL), m_gameList(NULL),
          m_numOfNodes(0)                      { *this = s; }
	~Stadium()                                 { delete []m_name; delete[] m_gameList; }
	// Operators
	const Stadium& operator=(const Stadium& s);
	// Methods
	void           SetName(const char* name)                          { delete []m_name; m_name = strdup(name); }
	void           SetMaxFans(int maxFans)                            { m_maxFans = maxFans; }
	const char*    GetName()                                    const { return m_name; }
	int            GetMaxFans()                                 const { return m_maxFans; }
	const Game*    GetGameByTimeAndDate(const TimeAndDate& tad) const ;
	const GameList GetGamesByDate(const Date& d)                const ;
	bool           AddGame(const Game* g);
	bool           RemoveGame(const Game* g);
	bool           MoveGameTime(const Game* g, const TimeAndDate& newTad);
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Stadium& s)
	{ 
		os << "Stadium Name: " << s.GetName() << " Max Fans: " << s.GetMaxFans(); 
		return os;
	}
private:
	char* m_name;
	int   m_maxFans;
	
	GamesByTimeDateNode* m_gameList;
	int                  m_numOfNodes;

	// Methods
	void            SetGameList(const GamesByTimeDateNode* list, int count);
};


#endif