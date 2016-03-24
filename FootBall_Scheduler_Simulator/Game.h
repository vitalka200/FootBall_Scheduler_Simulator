#ifndef __GAME_H
#define __GAME_H

// Forward declaration
class Team;
class Referee;
class Player;

struct PlayerStats
{
	Player*                 pl;
	Player::PlayerMovement* moves;
	int                     yellowCards;
	int                     redCards;
	int                     moves_number;
	~PlayerStats()          {delete []moves;}
};

class Game
{
public:
	// c-tors, d-tors
	Game(Team* team, Referee* ref, int maxFans)
		: m_teams(NULL), m_referee(NULL), m_maxFans(maxFans) { }
	Game(const Game& g);
	~Game()                              {delete []m_playerStats;}
	// Operators
	int  GetMaxFans();
	void StartGame();
	void AddReferee(Referee* ref);

	PlayerStats* GetGameStats()          {return m_playerStats;}

	// Methods
private:
	Team*        m_teams;
	Referee*     m_referee;
	int          m_maxFans;
	PlayerStats* m_playerStats;
};


#endif