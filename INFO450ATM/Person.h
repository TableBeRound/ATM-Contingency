#ifndef PERSON_H
#define PERSON_H

#pragma once

// I opted to create a Person class in case
// a future situation called for an Employee
// class. No specific ATM-related behavior 
// is defined for this class.

class Person
{
	char firstName[20];
	char lastName[20];
	char midInitial;
	char streetAddress[50];
	char cityName[20];
	char state[2];
	char ZIP[5];
	char telephoneNumber[10];

public:
	Person();
	~Person();
};

#endif