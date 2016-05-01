#ifndef __TIMEANDDATE_H
#define __TIMEANDDATE_H

#include <iostream>

class Time
{
public:
	// c-tors, d-tors
	Time(int hour = 0, int minute = 0)                         { SetHour(hour); SetMinute(minute); }
	Time(const Time& t)                                { *this = t; }
	// Operators
	Time        operator+(const Time& t)         const;
	Time        operator+(int add)               const;
	Time        operator-(const Time& t)         const;
	Time        operator-(int remove)            const;
	const Time& operator+=(const Time& t);
	const Time& operator-=(const Time& t);
	
	const Time& operator++()    { *this = *this + 1; return *this; } // prefix
	Time        operator++(int); // postfix
	const Time& operator--()    { *this = *this - 1; return *this; } // prefix
	Time        operator--(int); // postfix
	Time        operator/(int value);

	bool        operator==(const Time& t)  const { return m_hour==t.m_hour && m_minute==t.m_minute;}
	bool        operator!=(const Time& t)  const { return !(*this == t);}
	bool        operator>(const Time& t)   const ;
	bool        operator>=(const Time& t)  const { return (*this == t) || (*this > t);}
	bool        operator<(const Time& t)   const { return (*this != t) && !(*this > t);}
	bool        operator<=(const Time& t)  const { return (*this == t) || (*this < t);}
	// Methods
	int         GetMinute()                const { return m_minute; }
	int         GetHour()                  const { return m_hour; }
	void        SetMinute(int minute);
	void        SetHour(int hour);
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
	Date(int year = 0, int month = 0, int date = 0)   { SetYear(year); SetMonth(month); SetDate(date); }

	// Operators
	Date        operator+(const Date& d)         const;
	Date        operator+(int add)               const;
	Date        operator-(const Date& d)         const;
	Date        operator-(int remove)            const;
	const Date& operator+=(const Date& d);
	const Date& operator-=(const Date& d);
	
	const Date& operator++()    { *this = *this + 1; return *this; } // prefix
	Date        operator++(int); // postfix
	const Date& operator--()    { *this = *this - 1; return *this; } // prefix
	Date        operator--(int); // postfix

	bool        operator==(const Date& d)  const { return m_date==d.m_date && m_month==d.m_month && m_year==d.m_year;}
	bool        operator!=(const Date& d)  const { return !(*this == d);}
	bool        operator>(const Date& d)   const ;
	bool        operator>=(const Date& d)  const { return (*this == d) || (*this > d);}
	bool        operator<(const Date& d)   const { return (*this != d) && !(*this > d);}
	bool        operator<=(const Date& d)  const { return (*this == d) || !(*this > d);}
	// Methods
	int        GetDate()                   const { return m_date; }
	int        GetMonth()                  const { return m_month; }
	int        GetYear()                   const { return m_year; }

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Date& d)
	{ os << "Date: '" << d.GetDate() << "/" << d.GetMonth() << "/" << d.GetYear() << "'"; return os;}
private:
	int m_date;
	int m_month;
	int m_year;
	static const int DAYS_IN_MONTH[];
	static const int DAYS_IN_YEAR;
	static const int MONTH_NUMBER;

	// Methods
	void       SetYear(int year);
	void       SetDate(int date);
	void       SetMonth(int month);
};

class TimeAndDate
{
public:
	// c-tors, d-tors
	TimeAndDate(const Time& t, const Date& d)
		:m_time(t), m_date(d) { }

	TimeAndDate(const TimeAndDate& tad);
	// Operators
	bool               operator==(const TimeAndDate& t)  const { return m_time==t.m_time && m_date==t.m_date;}
	bool               operator!=(const TimeAndDate& t)  const { return !(*this == t);}
	bool               operator>(const TimeAndDate& t)   const ;
	bool               operator>=(const TimeAndDate& t)  const { return (*this == t) || (*this > t);}
	bool               operator<(const TimeAndDate& t)   const { return (*this != t) && !(*this > t);}
	bool               operator<=(const TimeAndDate& t)  const { return (*this == t) || !(*this > t);}
	// Methods
	const Time&        GetTime()                         const { return m_time; }
	const Date&        GetDate()                         const { return m_date; }
	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const TimeAndDate& tad)
	{ os << tad.m_time << " " << tad.m_date; return os;}
private:
	Time m_time;
	Date m_date;
};

#endif