#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#pragma once
#include "Person.h"

// I opted to include this class just in case
// there would be a future need for it.
class Employee :
	public Person
{
	// These could be used to look up
	// specific employee info from a 
	// database.
	char employeeNumber[15];	
	char jobNumber[10];
	char jobTitle[20];

public:
	Employee();
	~Employee();

	// Maybe an employee will have the
	// ability to freeze an account for
	// suspicious activity...but this is 
	// an ATM, so I'm not sure if these
	// behaviors (or even this class) is 
	// necessary/makes sense for this app.
	void FreezeAccount();
	void AddCustomer();
	void RemoveCustomer();
};

#endif