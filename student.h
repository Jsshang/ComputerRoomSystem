#pragma once
#include<iostream>
#include<vector>
#include "identity.h"
#include "computerRoom.h"
using namespace std;


class Student : public Identity
{
public:

	Student();

	Student(int id, string name, string pwd);

	virtual void operMenu();

	void applyOrder();

	void showMyOrder();

	void showAllOrder();

	void cancelOrder();

	int m_Id;

	vector<ComputerRoom> vCom;
};