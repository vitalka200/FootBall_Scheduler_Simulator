#ifndef __TIMEANDDATE_H
#define __TIMEANDDATE_H

#include <iostream>

class Time
{
public:
	// c-tors, d-tors
	Time(int minute, int hour);
	Time(const Time& t);
	// Operators
	const Time& operator=(const Time& t);
	Time        operator+(const Time& t)         const;
	Time        operator+(int add)               const;
	Time        operator-(const Time& t)         const;
	Time        operator-(int remove)            const;
	const Time& operator+=(const Time& t);
	const Time& operator-=(const Time& t);
	
	const Time& operator++()    { *this = *this + 1; } // prefix
	Time        operator++(int); // postfix
	const Time& operator--()    { *this = *this - 1; } // prefix
	Time        operator--(int); // postfix

	bool        operator==(const Time& t)  const { return m_hour==t.m_hour && m_minute==t.m_minute;}
	bool        operator!=(const Time& t)  const { return !(*this == t);}
	bool        operator>(const Time& t)   const ;
	bool        operator>=(const Time& t)  const { return *this == t || *this > t;}
	bool        operator<(const Time& t)   const { return !(*this > t);}
	bool        operator<=(const Time& t)  const { return *this == t || !(*this > t);}
	// Methods
	int  GetMinute()                const { return m_minute; }
	int  GetHour()                  const { return m_hour; }
	void SetMinute(int minute);
	void SetHour(int hour);
	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Time& t)
	{ os << "Time: '" << t.GetHour() << ":" << t.GetMinute() << "'" ; return os;}
private:
	int m_minute;
	int m_hour;
};

class Date
{
public:
	// c-tors, d-tors
	Date(int date, int month, int year);
	Date(const Date& d);
	// Operators
	const Date& operator=(const Date& t);
	Date        operator+(const Date& t)         const;
	Date        operator+(int add)               const;
	Date        operator-(const Date& t)         const;
	Date        operator-(int remove)            const;
	const Date& operator+=(const Date& t);
	const Date& operator-=(const Date& t);
	
	const Date& operator++()    { *this = *this + 1; } // prefix
	Date        operator++(int); // postfix
	const Date& operator--()    { *this = *this - 1; } // prefix
	Date        operator--(int); // postfix

	bool        operator==(const Date& t)  const { return m_date==t.m_date && m_month==t.m_month && m_year==t.m_year;}
	bool        operator!=(const Date& t)  const { return !(*this == t);}
	bool        operator>(const Date& t)   const ;
	bool        operator>=(const Date& t)  const { return *this == t || *this > t;}
	bool        operator<(const Date& t)   const { return !(*this > t);}
	bool        operator<=(const Date& t)  const { return *this == t || !(*this > t);}
	// Methods
	int GetDate()                   const { return m_date; }
	int GetMonth()                  const { return m_month; }
	int GetYear()                   const { return m_year; }
	void SetYear(int year);
	void SetDate(int date);
	void SetMonth(int month);

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Date& d)
	{ os << "Date: '" << d.GetDate() << "/" << d.GetMonth() << "/" << d.GetYear() << "'"; return os;}
private:
	int m_date;
	int m_month;
	int m_year;
};

class TimeAndDate
{
public:
	// c-tors, d-tors
	TimeAndDate(const Time& t, const Date& d)
		:m_time(t), m_date(d) { }
	TimeAndDate(const TimeAndDate& tad);
	// Operators
	const TimeAndDate& operator=(const TimeAndDate& t);
	TimeAndDate        operator+(const TimeAndDate& t)          const;
	TimeAndDate        operator+(const Time& t)                 const;
	TimeAndDate        operator+(const Date& t)                 const;
	TimeAndDate        operator+(int add)                       const;
	TimeAndDate        operator-(const TimeAndDate& t)          const;
	TimeAndDate        operator-(const Time& t)                 const;
	TimeAndDate        operator-(const Date& t)                 const;
	TimeAndDate        operator-(int remove)                    const;
	const TimeAndDate& operator+=(const TimeAndDate& t);
	const TimeAndDate& operator-=(const TimeAndDate& t);
	
	const TimeAndDate& operator++()                           { *this = *this + 1; } // prefix
	TimeAndDate        operator++(int);                       // postfix
	const TimeAndDate& operator--()                           { *this = *this - 1; } // prefix
	TimeAndDate        operator--(int);                       // postfix

	bool               operator==(const TimeAndDate& t)  const { return m_time==t.m_time && m_date==t.m_date;}
	bool               operator!=(const TimeAndDate& t)  const { return !(*this == t);}
	bool               operator>(const TimeAndDate& t)   const ;
	bool               operator>=(const TimeAndDate& t)  const { return *this == t || *this > t;}
	bool               operator<(const TimeAndDate& t)   const { return !(*this > t);}
	bool               operator<=(const TimeAndDate& t)  const { return *this == t || !(*this > t);}
	// Methods

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const TimeAndDate& tad)
	{ os << tad.m_time << " " << tad.m_date; return os;}
private:
	Time m_time;
	Date m_date;
};


#endif