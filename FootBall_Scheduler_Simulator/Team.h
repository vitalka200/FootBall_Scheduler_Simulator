#ifndef __TEAM_H
#define __TEAM_H

// Forward declaration
class  Player;
class  Trainer;
struct PlayerStats;

class Team
{
public:
	// c-tors, d-tors
	Team(const char* name) : m_name(NULL)         {SetName(name);}
	Team(const Team& t);
	~Team()                                       {delete []m_name;}
	// Operators

	// Methods
	void         AddPlayer(Player* p);
	void         RemovePlayer();
	void         AddTrainer(Trainer* t);
	void         RemoveTrainer();
	PlayerStats* GetStats();
	void         SetName(const char* name);
	char*        GetName()                  const {return m_name;}


private:
	Player*  m_players;
	Trainer* m_trainer;
	char* m_name;
};

#endif