#pragma once
#include <String>
#include <iostream>
#include <vector>
#include"map"
using namespace std;


class User
{
public:
	string Email, Password;
	User();
	void SignIn();
	void Create();
	void AddTrain();
	void DeleteTrain();
	void DisplayTrains();
	void AddTrips();
	void DeleteTrips();
	void UpdateTrips();
	void DisplayAvaiableTrips();
	void viewReservation();
	void updataReservation();
	void deleteReservation();
	void BookTicket();
	void ReadTrainData();
	void ReadTripData();
	void ReadPassData();
	void mapTrip(string, string);
};

class Trips
{

public:
	int AvailableSeats;
	int TripNumber;
	int TrainNumber;
	int day, month;
	float Fare;
	string BoardingPoint, DestinationPoint;

public:
	Trips();
};
class Train
{
public:
	string TrainName;
	int  TrainNumber;

public:
	Train();
};
class Ticket {
public:
	string passenger_name;
	int tripnumber, trainnumber;
	string boarding_point;
	string destination_point;
	int month;
	int day;
	int numofseats;
	Ticket();
};