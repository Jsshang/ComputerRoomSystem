#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Identity.h"

class Teacher :public Identity
{
public:

	Teacher();

	Teacher(int empId, string name, string pwd);

	virtual void operMenu();

	void showAllOrder();

	void validOrder();

	int m_EmpId;
};