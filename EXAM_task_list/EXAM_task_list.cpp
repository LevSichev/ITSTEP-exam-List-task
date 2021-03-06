/*
Создайте приложение «Список дел».
Приложение должно позволять:
	+■ Добавление дел. У дела есть: 
		• название;
		• приоритет;
		• описание;
		• дата, время исполнения.
	+■ Удаление дел.
	+■ Редактирование дел. - Task.Set(values)
	+■ Поиск дел по: - SelectBySpecificValue()
		• названию;
		• приоритету;
		• описанию;
		• дате и времени исполнения.
	+■ Отображение списка дел: - SelectBySpecificValue() с условиями
		• на день;
		• на неделю;
		• на месяц.
	+■ При отображении должна быть возможность сортировки: - перегрузка SelectBySpecificValue?
		• по приоритету;
		• по дате и времени исполнения.

*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

enum Priorities
{
	high = 1,
	medium = 2,
	low = 3,
	misc = 4
};

enum DayWeekOrMonth
{
	day = 1,
	week = 2,
	month = 3
};

struct MyTime
{
	int day = 1, month = 1, year = 1970, hour = 0, minute = 0;

	//set from a string of format "dd.mm.yyyy hh:mm"
	void Set(string input)
	{
		day = stoi(input.substr(0, 2));
		month = stoi(input.substr(3, 2));
		year = stoi(input.substr(6, 4));
		hour = stoi(input.substr(11, 2));
		minute = stoi(input.substr(14, 2));
	}

	//convert date 
	string ToStr()
	{
		return (to_string(day) + "." + to_string(month) + "." + to_string(year)+ " " + to_string(hour) + ":" + to_string(minute));
	}

};

class Task
{
public:

	string name, description;
	MyTime date;
	Priorities priority;

	//set the task's data to specified values
	Task(string n, Priorities p, string desc, string dat)
	{
		name = n;
		priority = p;
		description = desc;
		date.Set(dat);
	};
	Task() : Task("default", high , "a default task", "1.01.2022")
	{

	}

	void Set(string n, Priorities p, string desc, string dat)
	{
		name = n;
		priority = p;
		description = desc;
		date.Set(dat);
	};

	string PrioToStr()
	{
		switch (this->priority)
		{
		case high:
			return "high";
			break;
		case medium:
			return "medium";
			break;
		case low:
			return "low";
			break;
		case misc:
			return "misc";
			break;
		default:
			break;
		}
	}

	void Print()
	{
		cout << "==========================" << endl;
		cout << "name: " << name << endl;
		cout << "priority: " << PrioToStr() << endl;
		cout << "description: " << description << endl;
		cout << "date: " << date.ToStr() << endl;
		cout << "==========================" << endl;
	}

	~Task()
	{
		//no dynamic variables and pointer stuff, so it's kinda not required?..
		cout << "deleted" << endl;
	}
};

//show every task with one specific value, works for name, priorities, descriptions and dates
void SelectBySpecificValue(vector<Task>& boo, string specificValue, char searchby, int size)
{
	cout << "tasks that contain \" " << specificValue << "\" in field ";
	switch (searchby)
	{
	case 'n':
		cout << "name:" << endl;
		break;
	case 'p':
		cout << "priority:" << endl;
		break;
	case 'd':
		cout << "description:" << endl;
		break;
	case 't':
		cout << "date and time:" << endl;
		break;
	default:
		break;
	}
	switch (searchby)
	{
	case 'n':
		for (int i = 0; i < size; i++)
		{
			if (boo[i].name == specificValue)
				boo[i].Print();
		}
		break;
	case 'p':
		for (int i = 0; i < size; i++)
		{
			if (boo[i].PrioToStr() == specificValue)
				boo[i].Print();
		}
		break;
	case 'd':
		for (int i = 0; i < size; i++)
		{
			if (boo[i].description == specificValue)
				boo[i].Print();
		}
		break;
	case 't':
		for (int i = 0; i < size; i++)
		{
			if (boo[i].date.ToStr() == specificValue)
				boo[i].Print();
		}
		break;
	default:
		break;
	}
}

void SelectByTimePeriod(vector<Task>& tsk, int size, DayWeekOrMonth dwm)
{
	MyTime todaystruct;
	time_t now = time(0);
	tm* ltm = localtime(&now);

	string todaystr = (to_string(ltm->tm_mday) + "." + to_string(ltm->tm_mon) + "." + to_string(ltm->tm_year + 1900) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min));

	todaystruct.Set(todaystr);

	for (int i = 0; i < size; i++)
	{
		if ((tsk[i].date.month == todaystruct.month) && (tsk[i].date.year == todaystruct.year))
		{
			switch (dwm)
			{
			case day:
				if ((tsk[i].date.day == todaystruct.day))
				{
					tsk[i].Print();
				}
				break;
			case week:
				if (((tsk[i].date.day - todaystruct.day) <= 7))
				{
					tsk[i].Print();
				}
				break;
			case month:
				tsk[i].Print();
				break;
			default:
				break;
			}
		}
	}
}

void SortByPriority(vector<Task>& tsk, int size)
{
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (int(tsk[j].priority) > int(tsk[j + 1].priority))
			{
				swap(tsk[j], tsk[j + 1]);
			}
		}
	}
}

bool DateIsGreater(MyTime date1, MyTime date2)
{
	if (date1.year > date2.year)
		return true;
	if (date1.month > date2.month)
		return true;
	if (date1.day > date2.day)
		return true;
	if (date1.hour > date2.hour)
		return true;
	if (date1.minute > date2.minute)
		return true;

	return false;
}

void SortByDateTime(vector<Task>& tsk, int size)
{
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (DateIsGreater(tsk[i].date, tsk[i+1].date))
			{
				swap(tsk[j], tsk[j + 1]);
			}
		}
	}
}

////generate a random string using a set range of characters
//void StrArrGen(string &st, int size, int minChar, int maxChar)
//{
//	if (minChar > maxChar)
//	{
//		swap(minChar, maxChar);
//	}
//	for (int i = 0; i < size; i++)
//	{
//		st.push_back(char(rand() % (maxChar - minChar) + minChar));
//	}
//}

void TaskAppend(vector<Task>& tsk, Task toAppend)
{
	tsk.push_back(toAppend);
}

void TaskDelete(vector<Task>& tsk, int size, int pos)
{
	tsk.erase(tsk.begin()+pos);
}

int main()
{
	//TODO: add a dynamic array of tasks, some ASCII GUI
	cout << "hell" << endl;
    return 0;
}

