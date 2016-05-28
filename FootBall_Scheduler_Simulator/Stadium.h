#ifndef __STADIUM_H
#define __STADIUM_H

#include <iostream>
#include <string>
#include <vector>

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
	~GamesByTimeDateNode()                                { delete m_date; }
	GamesByTimeDateNode(const GamesByTimeDateNode& gt)
	    : m_date(NULL)                                    { *this = gt; }

	const GamesByTimeDateNode& operator=(const GamesByTimeDateNode& gt);

	//Methods
	bool         AddGame(Game* g);
	bool         RemoveGame(const Game* g);
	const Date*  GetDate()                          const { return m_date; }
	int          GetGamesCount()                    const { return m_games.size(); }
	const Game&  GetGameById(int idx)               const { return *(m_games[idx]); }
	// operators
	const GamesByTimeDateNode& operator+=(Game* g)        { AddGame(g);    return *this; }
	const GamesByTimeDateNode& operator-=(const Game* g)  { RemoveGame(g); return *this; }

	friend std::ostream& operator<<(std::ostream& os, const GamesByTimeDateNode& node);

private:
	Date*               m_date;
	std::vector<Game*>  m_games;

	// Methods
	void SetGames(std::vector<Game*> games);

	// Hidden default c-tor. available only for Stadium
	GamesByTimeDateNode() : m_date(NULL) { }
	void SetDate(const Date& d);
};

class GameList
{
public:
	Game** games;
	int    count;
	GameList() : games(NULL), count(0) { }
	GameList(const GameList& gl) : games(NULL), count(0)  { *this = gl; }
	~GameList()                                           { delete []games; }
	
	const GameList& operator=(const GameList& gl);
};

class Stadium
{
friend class GameManager;
public:
	// c-tors, d-tors
	Stadium(const std::string name = " ", int maxFans = 0)
		: m_maxFans(maxFans)                   { SetName(name); };
	Stadium(const Stadium& s)                  { *this = s; }
	~Stadium()                                 { }
	// Operators
	const Stadium& operator=(const Stadium& s);
	// Methods
	void           SetName(const std::string name)                          { m_name = name; }
	void           SetMaxFans(int maxFans)                            { m_maxFans = maxFans; }
	const std::string    GetName()                                    const { return m_name; }
	int            GetMaxFans()                                 const { return m_maxFans; }
	Game*          GetGameByTimeAndDate(const TimeAndDate& tad) const ;
	GameList       GetGamesByDate(const Date& d)                const ;
	bool           AddGame(Game* g);
	bool           RemoveGame(const Game* g);
	bool           MoveGameTime(const Game* g, const TimeAndDate& newTad);
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Stadium& s)
	{ 
		os << "Stadium Name: " << s.GetName() << " Max Fans: " << s.GetMaxFans(); 
		return os;
	}
private:
	std::string m_name;
	int         m_maxFans;
	
	std::vector<GamesByTimeDateNode> m_gameList;

	// Methods
	void            SetGameList(const std::vector<GamesByTimeDateNode> list);
};


#endif