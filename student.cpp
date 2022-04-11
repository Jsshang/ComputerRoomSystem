#include <fstream>
#include "student.h"
#include "globalFile.h"
#include "orderFile.h"
#include "util.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	// get the info about the computer room
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;

	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	ifs.close();
}

void Student::operMenu()
{
	cout << "Welcome student: " << this->m_Name << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1. make an appointment |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2. see my appointments |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3. see all appointments|\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4. cancel appointment  |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0. logout              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "Please select your operation: " << endl;
}

void Student::applyOrder()
{
	cout << "Computer rooms are allowed to be used from Monday to Friday!" << endl;
	cout << "please select the date you are applying: " << endl;
	cout << "1. Monday" << endl;
	cout << "2. Tuesday" << endl;
	cout << "3. Wednesday" << endl;
	cout << "4. Thursday" << endl;
	cout << "5. Friday" << endl;

	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "Input invalid, please try again!" << endl;
	}

	cout << "please select the time you are applying: " << endl;
	cout << "1. Morning" << endl;
	cout << "2. Afternoon" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "Input invalid, please try again!" << endl;
	}

	cout << "Please select the computer room number: " << endl;
	cout << "room 1 capacity: " << vCom[0].m_MaxNum << endl;
	cout << "room 2 capacity: " << vCom[1].m_MaxNum << endl;
	cout << "room 3 capacity: " << vCom[2].m_MaxNum << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "Input invalid, please try again!" << endl;
	}

	cout << "Appointment finished, under review!" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "No appointment record" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "Appointment: " << convert(of.m_orderData[i]["date"]);
			cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
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
	}

	system("pause");
	system("cls");

}

void Student::showAllOrder()
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

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "No appointment Record" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "Appointment succeeded or under review can be cancelled, please select" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << ">> ";
				cout << "Appointment: " << convert(of.m_orderData[i]["date"]);
				cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
				cout << " Computer room: " << of.m_orderData[i]["roomId"];

				string status = " status: ";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "under review";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "succeeded";
				}
				cout << status << endl;
			}

		}
	}

	cout << "please select one you want to cancel, input 0 to exit" << endl;
	int select = 0;
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
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "Appointment has been cancelled" << endl;
				break;
			}
		}

		cout << "Invalid input, please try again!" << endl;
	}

	system("pause");
	system("cls");
}
