#pragma once
#include<iostream>
using namespace std;
#include "identity.h"

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
};