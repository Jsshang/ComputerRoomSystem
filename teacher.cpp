#include <fstream>
#include "teacher.h"
#include "orderFile.h"
#include "util.h"
#include <vector>

Teacher::Teacher()
{

}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "welcome: " << this->m_Name << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1. show all appointments|\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2. valid appointments   |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0. logout               |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "please select next step: " << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "No appointment Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << ">> ";
		cout << "Appointment: " << convert(of.m_orderData[i]["date"]);
		cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
		cout << " student id: " << of.m_orderData[i]["stuId"];
		cout << " student name: " << of.m_orderData[i]["stuName"];
		cout << " Computer room: " << of.m_orderData[i]["roomId"];

		string status = " status: ";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "under review";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "approved";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "failed";
		}
		else
		{
			status += "cancelled";
		}

		cout << status << endl;

	}

	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "No appointment Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "Appointments requires review: " << endl;

	vector<int> v;
	int index = 0;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ">> ";
			cout << "Appointment: " << convert(of.m_orderData[i]["date"]);
			cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
			cout << " Computer room: " << of.m_orderData[i]["roomId"];
			string status = "status: ";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "under review";
			}
			cout << status << endl;
		}

	}

	cout << "please select which appointment you are targeting at, input 0 to exit" << endl;
	int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "please type in the result: " << endl;
				cout << "1. approved" << endl;
				cout << "2. refused" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}

				of.updateOrder();
				cout << "review completed!" << endl;
				break;
			}
		}

		cout << "Invalid selection, please try again!" << endl;

	}

	system("pause");
	system("cls");
}