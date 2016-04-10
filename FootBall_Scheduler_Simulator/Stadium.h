#ifndef __STADIUM_H
#define __STADIUM_H

#include <iostream>

class Game;
class TimeAndDate;
class Time;
class Date;

class GamesByTimeDateNode
{
public:
	GamesByTimeDateNode(const Date& date)
		: m_date(NULL), m_times(NULL), m_games(NULL)      { m_date = new Date(date);}
	~GamesByTimeDateNode()                                { delete []m_date; }
	//Methods
	void         AddGame(Game* g);
	void         RemoveGame(const Game* g);
	const Date*  GetDate()                          const { return m_date; }
	// operators
	const GamesByTimeDateNode& operator+=(Game* g)        { AddGame(g);    return *this; }
	const GamesByTimeDateNode& operator-=(const Game* g)  { RemoveGame(g); return *this; }
private:
	Date*  m_date;
	Time*  m_times;
	Game*  m_games;

	// Disable copy and assigment
	GamesByTimeDateNode(const GamesByTimeDateNode& gt);
	const GamesByTimeDateNode& operator=(const GamesByTimeDateNode& gt);

};

class Stadium
{
public:
	// c-tors, d-tors
	Stadium(const char* name, int maxFans)
		: m_name(NULL),  m_maxFans(maxFans),
		  m_gameList(NULL)                     { SetName(name); };
	Stadium(const Stadium& s)
		: m_name(NULL), m_gameList(NULL)       { *this = s; }
	~Stadium()                                 { delete []m_name; delete[] m_gameList; }
	// Operators
	const Stadium& operator=(const Stadium& s);
	// Methods
	void        SetName(const char* name)                          { delete []m_name; m_name = strdup(name); }
	void        SetMaxFans(int maxFans)                            { m_maxFans = maxFans; }
	const char* GetName()                                    const { return m_name; }
	int         GetMaxFans()                                 const { return m_maxFans; }
	Game*       GetGameByTimeAndDate(const TimeAndDate& tad) const ;
	Game*       GetGamesByDate(const Date& d)                const ;
	void        AddGame(Game* g);
	void        RemoveGame(Game* g);
	void        MoveGameTime(Game* g, const TimeAndDate& newTad);
	
	// Method overrides
	friend std::ostream& operator<<(std::ostream& os, const Stadium& s);
private:
	char* m_name;
	int   m_maxFans;

	
	GamesByTimeDateNode* m_gameList;
};


#endif