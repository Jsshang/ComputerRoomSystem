# include "util.h"

string convert(string& date)
{
	if (date == "1")
	{
		return "Monday";
	}
	else if (date == "2")
	{
		return "Tuesday";
	}
	else if (date == "3")
	{
		return "Wednesday";
	}
	else if (date == "4")
	{
		return "Thursday";
	}
	else if (date == "5")
	{
		return "Friday";
	}
	else
	{
		return "error";
	}
}
