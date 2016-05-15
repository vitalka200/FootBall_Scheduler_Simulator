#include "TimeAndDate.h"


Time Time::operator+(const Time& t) const
{
	return Time(this->GetHour() + t.GetHour(), this->GetMinute() + t.GetMinute());
}

Time Time::operator+(int add) const
{
	return Time(this->GetHour(), this->GetMinute() + add);
}

Time Time::operator-(const Time & t) const
{
	return Time(this->GetHour() - t.GetHour(), this->GetMinute() - t.GetMinute());
}

Time Time::operator-(int remove) const
{
	return Time(this->GetHour(), this->GetMinute() - remove);
}

const Time & Time::operator+=(const Time& t)
{
	SetHour(this->GetHour()     + t.GetHour());
	SetMinute(this->GetMinute() + t.GetMinute());
	return *this;
}

const Time & Time::operator-=(const Time& t)
{
	SetHour(this->GetHour()     - t.GetHour());
	SetMinute(this->GetMinute() - t.GetMinute());
	return *this;
}

const Time& Time::operator=(const Time & t)
{
	if (*this != t)
	{
		m_hour = t.m_hour;
		m_minute = t.m_minute;
	}
	return *this;
}

Time Time::operator++(int)
{
	Time t(*this);
	++(*this);
	return t;
}

Time Time::operator--(int)
{
	Time t(*this);
	--(*this);
	return t;
}

Time Time::operator/(int value)
{
	if (value == 0) { return Time(); }
	Time newTime(m_hour/value, (m_hour%value)*60/value);
	newTime += Time(0, m_minute / value);
	return newTime;
}

bool Time::operator>(const Time& t) const
{
	return (this->m_hour > t.m_hour) || 
		(this->m_hour == t.m_hour && this->m_minute > t.m_minute);
}

void Time::SetMinute(int minute)
{
	if (minute < 0)
	{ minute = 0; }
	else if (minute > 60)
	{ m_hour += minute/60; minute %= 60; }
	m_minute = minute;
}

void Time::SetHour(int hour)
{
	if (hour < 0)
	{ hour = 0; }
	if (m_hour > 23)
	{ hour %= 24; }
	m_hour = hour;
}

const int Date::DAYS_IN_MONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int Date::DAYS_IN_YEAR    = 365;
const int Date::MONTH_NUMBER    = 12;

bool Date::operator>(const Date& d) const
{
	return (this->m_year > d.m_year) ||
		(this->m_year == d.m_year && this->m_month > d.m_month) ||
		(this->m_year == d.m_year && this->m_month == d.m_month && this->m_date > d.m_date);
}

void Date::SetYear(int year)
{
	if (year < 0)
	{ year = 0; }
	m_year = year;
}

void Date::SetMonth(int month)
{
	if (month < 0)
	{ month = 0; }
	else if (month > 12)
	{ month %= 12; }
	m_month = month;
}

void Date::SetDate(int date)
{
	if (date > DAYS_IN_YEAR)
	{
		m_year += date / DAYS_IN_YEAR;
		date %= DAYS_IN_YEAR;
	}
	if (date <= DAYS_IN_MONTH[m_month])
	{
		m_date = date;
	}
	else
	{
		for (int i = m_month; i < MONTH_NUMBER; i++)
		{
			date -= DAYS_IN_MONTH[i];
			if (date <= DAYS_IN_MONTH[i])
			{ m_date = date; }
		}
	}
}

Date Date::operator+(const Date& d) const
{
	return Date(
		this->GetYear()  + d.GetYear(),
		this->GetMonth() + d.GetMonth(),
		this->GetDate()  + d.GetDate()
	);
}

Date Date::operator+(int add) const
{
	return Date(this->GetYear(), this->GetMonth(), this->GetDate() + add);
}

Date Date::operator-(const Date & d) const
{
	return Date(
		this->GetYear()  - d.GetYear(),
		this->GetMonth() - d.GetMonth(),
		this->GetDate()  - d.GetDate()
	);
}

Date Date::operator-(int remove) const
{
	return Date(this->GetYear(), this->GetMonth(), this->GetDate() - remove);
}

const Date & Date::operator+=(const Date & d)
{
	this->SetYear(this->GetYear()   + d.GetYear());
	this->SetMonth(this->GetMonth() + d.GetMonth());
	this->SetDate(this->GetDate()   + d.GetDate());
	return *this;
}

const Date& Date::operator-=(const Date & d)
{
	this->SetYear(this->GetYear()   - d.GetYear());
	this->SetMonth(this->GetMonth() - d.GetMonth());
	this->SetDate(this->GetDate()   - d.GetDate());
	return *this;
}

Date Date::operator++(int)
{
	Date d(*this);
	++(*this);
	return d;
}

Date Date::operator--(int)
{
	Date d(*this);
	--(*this);
	return d;
}


const TimeAndDate& TimeAndDate::operator=(const TimeAndDate& t)
{
	if (*this != t)
	{
		m_time = t.m_time;
		m_date = t.m_date;
	}
	return *this;
}

bool TimeAndDate::operator>(const TimeAndDate& t) const
{
	return (this->GetDate() > t.GetDate()) || 
		(this->GetDate() == t.GetDate() && this->GetTime() > t.GetTime());
}
