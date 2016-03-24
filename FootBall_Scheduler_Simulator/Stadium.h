#ifndef __STADIUM_H
#define __STADIUM_H



class Stadium
{
public:
	// c-tors, d-tors
	Stadium(const char* name, int maxFans)
		: m_name(NULL), m_maxFans(maxFans)  {SetName(name);};
	Stadium(const Stadium& s);
	~Stadium()                              {delete []m_name;}
	// Operators

	// Methods
	void  SetName(const char* name);
	char* GetName()                   const {return m_name;}
private:
	char* m_name;
	int   m_maxFans;
	
};


#endif