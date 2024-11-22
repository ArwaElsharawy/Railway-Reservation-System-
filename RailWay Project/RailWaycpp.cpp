#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include<vector>
#include <cassert>
#include <unordered_map>
#include "Header.h"
#include"map"

using namespace std;
map<pair<int, int>, Trips>Maps;
unordered_map<string, User> UserMap;
User user;
vector <Trips> Trip1;
Trips trip;
vector <Train> Train1;
Train train;
vector <Ticket> Ticket1;
Ticket ticket;


void User::mapTrip(string PBoardingPoint, string PDestinationPoint)
{
	//read file trip
	ifstream TripData("Trip.txt");
	int Tnumber, delnumber, Tfare, Tday, Tmonth;
	string TBoardingPoint, TDestinationPoint;
	if (TripData.is_open()) {

		while (TripData >> Tnumber >> TBoardingPoint >> TDestinationPoint >> Tfare >> Tmonth >> Tday) {
			trip.TripNumber = Tnumber;
			trip.BoardingPoint = TBoardingPoint;
			trip.DestinationPoint = TDestinationPoint;
			trip.Fare = Tfare;
			trip.month = Tmonth;
			trip.day = Tday;

			Trip1.push_back(trip);
		}
	}


	for (int i = 0; i < Trip1.size(); i++)
	{
		if (PBoardingPoint == Trip1[i].BoardingPoint && PDestinationPoint == Trip1[i].DestinationPoint)
		{
			Maps.insert(make_pair(make_pair(Trip1[i].month, Trip1[i].day), Trip1[i]));

		}
	}
	//call in book
	for (auto MAP : Maps)
		cout << "Month : " << MAP.first.first << " " << "Day : " << MAP.first.second << "\t" << "Trip Number : " << MAP.second.TripNumber << "    AvailableSeats  " << MAP.second.AvailableSeats << endl;

	Trip1.clear();
	TripData.close();
}


User::User() {
	Email = " ";
	Password = " ";
}
void User::ReadTrainData()
{
	int Tnumber;
	string Tname;
	ifstream TrainData;
	TrainData.open("Train.txt");
	if (TrainData.is_open()) {

		while (TrainData >> Tnumber >> Tname) {
			train.TrainNumber = Tnumber;
			train.TrainName = Tname;
			Train1.push_back(train);
		}
	}
	TrainData.close();
}
void User::ReadTripData() {
	ReadTrainData();
	ifstream Temp("Trip.txt");
	fstream TripData("Trip.txt", ios::app);
	bool found = false;
	bool findtrain = false;
	int Tnumber, delnumber, Tfare, Tday, Tmonth, Tavaiablenumber, triptrainnum;
	string TBoardingPoint, TDestinationPoint;


	if (Temp.is_open()) {

		while (Temp >> Tnumber >> TBoardingPoint >> TDestinationPoint >> Tfare >> Tmonth >> Tday >> Tavaiablenumber >> triptrainnum) {
			trip.TripNumber = Tnumber;
			trip.BoardingPoint = TBoardingPoint;
			trip.DestinationPoint = TDestinationPoint;
			trip.Fare = Tfare;
			trip.month = Tmonth;
			trip.day = Tday;
			trip.AvailableSeats = Tavaiablenumber;
			trip.TrainNumber = triptrainnum;

			Trip1.push_back(trip);
		}
	}
	Temp.close();
	TripData.close();
}
void User::ReadPassData()
{
	ifstream TicketData("Reservation.txt");

	string passenger_name;
	int tripnumber, trainnumber;
	string boarding_point;
	string destination_point;
	int month;
	int day;
	int numofseats;
	if (TicketData.is_open()) {

		while (TicketData >> passenger_name >> tripnumber >> boarding_point >> destination_point >> month >> day >> numofseats >> trainnumber) {
			ticket.passenger_name = passenger_name;
			ticket.tripnumber = tripnumber;
			ticket.boarding_point = boarding_point;
			ticket.destination_point = destination_point;
			ticket.month = month;
			ticket.day = day;
			ticket.numofseats = numofseats;
			ticket.trainnumber = trainnumber;
			Ticket1.push_back(ticket);
		}
	}
	TicketData.close();
}

void User::SignIn() {
	//read from file
	ifstream account("data.txt");
	string line1, line2;
	string mail, password;
	int adminChoice, trainChoice, tripChoice, passChoice;

start:
	bool Loggedin = false;
	cout << "\n Enter your E_mail:\n";
	cin >> mail;
	cout << " Enter your Password:\n";
	cin >> password;

	if (mail == "Admin" && password == "Admin")
	{
		int opchoice;
		Loggedin = true;
		cout << "----------WElcome Admin----------\n";
	admingo:
		cout << "Press (1) To Modify Train" << endl << " Press(2) To Modify Trips \n";
		cin >> adminChoice;
		if (adminChoice == 1)
		{
			cout << "Press (1) To Add Train \n Press(2) To Delete Train \n Press(3) To View Trains \n Press(4) To Exit \n";


			cin >> trainChoice;
			switch (trainChoice)
			{
			case 1:
				AddTrain();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			case 2:
				DeleteTrain();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			case 3:
				DisplayTrains();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			default:
				break;
			}
		}
		else if (adminChoice == 2)
		{

			cout << "Press (1) To Add Trips \n Press(2) To Delete Trips \n Press(3) To Update Trips \n Press(4) To Display Avaiable Trips \n Press(5) To Exit \n";

			cin >> tripChoice;
			switch (tripChoice)
			{
			case 1:
				AddTrips();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			case 2:
				DeleteTrips();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			case 3:
				UpdateTrips();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;
			case 4:
				DisplayAvaiableTrips();
				cout << "If you want another operation , Press (1) \n";
				cin >> opchoice;
				if (opchoice == 1)
					goto admingo;
				break;

			}
		}
		return;
	}
	else
	{
		ifstream account("data.txt");
		while (!account.eof()) {
			getline(account, line1);
			getline(account, line2);

			if (mail == line1 && password == line2) {
				cout << "-------------WElcome------------- \n";
				Loggedin = true;

				break;
			}
		}
		account.close();
	}
	if (!Loggedin) {
		cout << " Wrong E-mail or Password , please try again ....! ";
		goto start;
	}
	else
	{
		int opchoice;
	passgo:
		cout << "Press (1) To Book Ticket \n Press(2) To Delete Reservation \n Press(3) To Update Reservation \n Press(4) To View Your Resevation \n Press(5) To Exit \n";
		cout << "----------------------------------------------------------------------------------------------------------\n";

		cin >> passChoice;
		switch (passChoice)
		{
		case 1:
			BookTicket();
			cout << "If you want another operation , Press (1) \n";
			cin >> opchoice;
			if (opchoice == 1)
				goto passgo;
			break;
		case 2:
			deleteReservation();
			cout << "If you want another operation , Press (1) \n";
			cin >> opchoice;
			if (opchoice == 1)
				goto passgo;
			break;
		case 3:
			updataReservation();
			cout << "If you want another operation , Press (1) \n";
			cin >> opchoice;
			if (opchoice == 1)
				goto passgo;
			break;
		case 4:
			viewReservation();
			cout << "If you want another operation , Press (1) \n";
			cin >> opchoice;
			if (opchoice == 1)
				goto passgo;
			break;
		}

	}




}
void User::Create() {
	ifstream Temp("data.txt ");
	fstream account("data.txt ", ios::app);
	bool created = false;
	string mail, password;
	if (Temp.is_open()) {
		while (Temp >> mail >> password) {
			user.Email = mail;
			user.Password = password;
			UserMap.insert({ mail, user });
		}
	}
again:
	cout << "\t\t\t\t    Creat your Account \n";
	cout << "\t\t\t\t    -------------------\n";
	cout << " Enter your E_mail:\n";
	cin >> mail;
	if (UserMap.find(mail) == UserMap.end()) {

		cout << " Enter your Password :\n";
		cin >> password;
		user.Email == mail;
		user.Password = password;

		UserMap.insert({ mail, user });
		cout << " Your Account Created Successfully..!\n";
		created = true;

	}
	else {
		cout << " This account Already exits , Try another Email\n ";
		goto again;

	}	if (created) {
		ofstream Temp("data.txt ");

		for (auto MAP : UserMap)
			account << MAP.first << endl << MAP.second.Password << endl;
	}
	Temp.close();
	account.close();
	UserMap.clear();

}


Train::Train()
{
	this->TrainName = "";
	this->TrainNumber = 0;

}
void User::AddTrain()
{
	//omnia
	fstream TrainData("Train.txt", ios::app);
	ifstream Temp("Train.txt");
	int TNumber;
	string TName;

	if (Temp.is_open()) {
		while (Temp >> TNumber >> TName)
		{
			train.TrainNumber = TNumber;
			train.TrainName = TName;
			Train1.push_back(train);
		}

	}
again:
	bool find = false;
	cout << " Enter Train Number to be Added : \n";
	cin >> TNumber;
	for (int i = 0; i < Train1.size(); i++)
	{
		if (Train1[i].TrainNumber == TNumber) {
			find = true;
			break;
		}
	}
	if (find) {
		cout << " This train is Already Exit, Please change the Number\n";
		goto again;
	}
	else {
		cout << "Enter the Train Name \n";
		cin >> TName;
		train.TrainNumber = TNumber;
		train.TrainName = TName;
		Train1.push_back(train);
		ofstream Temp("Train.txt");
		for (int i = 0; i < Train1.size(); i++) {
			TrainData << Train1[i].TrainNumber << endl;
			TrainData << Train1[i].TrainName << endl;
		}
		cout << " \n-------Train Added Successfully...!-------\n";
	}

	TrainData.close();
	Temp.close();
	Train1.clear();
}
void User::DeleteTrain()
{
	//arwa hossam
	//Delete from Train File
	ifstream Temp("Train.txt");
	fstream TrainData("Train.txt", ios::app);
	int Tnumber, delnumber;
	string Tname;
	bool found = false;
	if (Temp.is_open()) {

		while (Temp >> Tnumber >> Tname) {
			train.TrainNumber = Tnumber;
			train.TrainName = Tname;
			Train1.push_back(train);
		}
	}
	cout << " Enter Train Number to be deleted: \n";
	cin >> delnumber;

	for (int i = 0; i < Train1.size(); i++) {
		if (Train1[i].TrainNumber == delnumber) {
			Train1.erase(Train1.begin() + i);
			found = true;

		}
	}
	if (found) {
		ofstream Temp("Train.txt");
		cout << "\n-------Data Deleted Successfully...!-------\n" << endl;



		for (int i = 0; i < Train1.size(); i++) {

			TrainData << Train1[i].TrainNumber << endl;
			TrainData << Train1[i].TrainName << endl;

		}

	}
	else {
		cout << "There is No Train to be Deleted" << endl;


	}
	Train1.clear();
	Temp.close();
	TrainData.close();

}
void User::DisplayTrains() {
	//omnia

	ReadTrainData();
	for (int i = 0; i < Train1.size(); i++) {
		cout << " Train Number: " << " " << Train1[i].TrainNumber << endl;

		cout << " Train Name: " << "  " << Train1[i].TrainName << endl;
	}
	// form file Directly
	//if (TrainData.is_open()) {

	//	while (TrainData >> Tnumber >> Tname) {
	//		cout << " Train Number " << " " <<Tnumber << endl;

	//	   cout << " Train Name " << "   " << Tname<< endl;
	//	}
	//}


	Train1.clear();

}


Trips::Trips() {
	AvailableSeats = 0;
	TripNumber = 0;
	Fare = 0;
	BoardingPoint = "";
	DestinationPoint = "";
	month = 0;
	day = 0;

}
void User::AddTrips()

{
	//alaa
	int trainnum;
	bool find = false;
	bool findtrain = false;

	ReadTrainData();
	cout << "Enter Number Of Trip you want to add:\n";
	cin >> trip.TripNumber;

entertrain:
	cout << "Enter Number Of Train : \n";
	cin >> trainnum;
	for (int i = 0; i < Train1.size(); i++) {

		if (Train1[i].TrainNumber == trainnum)
		{
			findtrain = true;
		}
	}

	fstream TripData("Trip.txt", ios::app);
	if (findtrain) {
		TripData << trip.TripNumber << endl;
		cout << "Enter BoardingPoint of trains in order name \n";
		cin >> trip.BoardingPoint;
		TripData << trip.BoardingPoint << endl;
		cout << "Enter DestinationPoint of trains in order name \n";
		cin >> trip.DestinationPoint;
		TripData << trip.DestinationPoint << endl;
		cout << "Enter Fare of trips  \n";
		cin >> trip.Fare;
		TripData << trip.Fare << endl;
		cout << "Enter Date of the trips: \n";
		cout << "Month: \n";
		cin >> trip.month;
		TripData << trip.month << endl;
		cout << "Day: \n";
		cin >> trip.day;
		TripData << trip.day << endl;
		trip.AvailableSeats = 20;
		TripData << trip.AvailableSeats << endl;
		trip.TrainNumber = trainnum;
		TripData << trip.TrainNumber << endl;


		Trip1.push_back(trip);


	}
	else {
		cout << " Sorry, NO train with this number can be found..!\n";
		goto entertrain;
	}

	TripData.close();
	Trip1.clear();
	Train1.clear();
}
void User::DeleteTrips()
{
	//arwa hossam
	ReadTripData();
	int  delnumber;
	bool found = false;
	cout << " Enter Trip Number to be deleted \n";
	cin >> delnumber;
	ofstream TripData("Trip.txt");

	for (int i = 0; i < Trip1.size(); i++)
	{
		if (Trip1[i].TripNumber == delnumber)
		{
			Trip1.erase(Trip1.begin() + i);
			found = true;

		}
	}
	if (found)
	{
		cout << "\n-------Data Deleted Successfully...!-------\n" << endl;
		for (int i = 0; i < Trip1.size(); i++) {

			TripData << Trip1[i].TripNumber << endl;
			TripData << Trip1[i].BoardingPoint << endl;
			TripData << Trip1[i].DestinationPoint << endl;
			TripData << Trip1[i].Fare << endl;
			TripData << Trip1[i].month << endl;
			TripData << Trip1[i].day << endl;
			TripData << Trip1[i].AvailableSeats << endl;
			TripData << Trip1[i].TrainNumber << endl;

		}

	}
	else
	{
		cout << "Sorrt, Data can not be found" << endl;
	}
	Trip1.clear();
	TripData.close();
}
void User::UpdateTrips()
{
	//arwa sh3rawy
	ReadTripData();
	int Upnumber, triptrainnum;
	bool found = false;
	bool findtrain = false;

	cout << " Enter Trip Number to be Update: \n";
	cin >> Upnumber;
	//write iin files
	ofstream TripData("Trip.txt");

	for (int i = 0; i < Trip1.size(); i++)
	{
		if (Trip1[i].TripNumber == Upnumber)
		{
			found = true;
			cout << "Data Found " << endl;
			cout << "------ Please Enter The Data You Want To Be Updated ------" << endl;
			cout << "Enter Number Of Trip:\n";
			cin >> trip.TripNumber;
			cout << "Enter BoardingPoint Of Trains In Order Name: \n";
			cin >> trip.BoardingPoint;
			cout << "Enter DestinationPoint Of Trains In Order Name: \n";
			cin >> trip.DestinationPoint;
			cout << "Enter Fare Of Trips:  \n";
			cin >> trip.Fare;
			cout << "Enter Date of the trips: \n";
			cout << "Month: \n";
			cin >> trip.month;
			cout << "Day: \n";
			cin >> trip.day;
			trip.AvailableSeats = 20;

		totrain:
			cout << "Enter Number Of Train: \n";
			cin >> triptrainnum;
			//to make sure that train true
			for (int i = 0; i < Train1.size(); i++)
			{
				if (Train1[i].TrainNumber == triptrainnum)
				{
					findtrain = true;
				}
			}


			if (findtrain)
			{
				trip.TrainNumber = triptrainnum;
				Trip1[i] = trip;

				// if train number exist  -> update 
				for (int i = 0; i < Trip1.size(); i++)
				{

					TripData << Trip1[i].TripNumber << endl;
					TripData << Trip1[i].BoardingPoint << endl;
					TripData << Trip1[i].DestinationPoint << endl;
					TripData << Trip1[i].Fare << endl;
					TripData << Trip1[i].month << endl;
					TripData << Trip1[i].day << endl;
					TripData << Trip1[i].AvailableSeats << endl;
					TripData << Trip1[i].TrainNumber << endl;


				}
			}
			else
			{
				cout << " Invalid Train Number...!!\n";
				goto totrain;
			}
		}

	}
	if (found && findtrain)
	{
		cout << " \n-------Data Updated Successfully..!-------\n";
	}
	else if (!found)
	{
		cout << "Sorry,Data can Not be Found" << endl;
	}
	Trip1.clear();
	TripData.close();
	Train1.clear();
}
void User::DisplayAvaiableTrips()
{
	//asmaa
	ReadTripData();
	cout << "The Available Trips: \n";
	for (int i = 0; i < Trip1.size(); i++) {
		if (Trip1[i].AvailableSeats != 0) {
			cout << "\nTrip Number  " << Trip1[i].TripNumber << endl;
			cout << "Boarding Point  " << Trip1[i].BoardingPoint << endl;
			cout << "Destination Point " << Trip1[i].DestinationPoint << endl;
			cout << "Trip Fare  " << Trip1[i].Fare << endl;
			cout << "Trip Date (Month)  " << Trip1[i].month << endl;
			cout << "Trip Date (day)  " << Trip1[i].day << endl;
			cout << "Trip AvaiableSeats  " << Trip1[i].AvailableSeats << endl;
			cout << "Train Number  " << Trip1[i].TrainNumber << endl;

		}
	}
	Trip1.clear();
}

Ticket::Ticket()
{
	passenger_name = "";
	tripnumber = trainnumber = 0;
	boarding_point = "";
	destination_point = "";
	month = 0;
	day = 0;
	numofseats = 0;
}
void User::viewReservation()
{

	ReadPassData();
	string name;
	cout << "--------- WELCOME TO VIEW RESEVATION---------\n";
	cout << "Please,Enter your name to show your reservation: ";
	cin >> name;
	for (int i = 0; i < Ticket1.size(); i++) {
		if (name == Ticket1[i].passenger_name) {
			cout << "Passenger Name:" << "\t" << Ticket1[i].passenger_name << endl;
			cout << "Trip Number:" << "\t " << Ticket1[i].tripnumber << endl;
			cout << "Boarding Point:" << " \t " << Ticket1[i].boarding_point << endl;
			cout << "Destination Point:" << "\t" << Ticket1[i].destination_point << endl;
			cout << "date of the trip:\n" << "Month:" << " " << Ticket1[i].month << "\t" << " Day:" << "  " << ticket.day << endl;
			cout << "Number of seats:" << "\t" << Ticket1[i].numofseats << endl;
			cout << "Train Number:" << "\t " << Ticket1[i].trainnumber << endl;
		}
	}
	Ticket1.clear();
}
void User::updataReservation()
{
	viewReservation();
	ReadTripData();
	ReadPassData();

	int num, seatsNo;
	string name;
	bool find = false;
	cout << "Please, Enter number of trip to be Updated:\n";
	cin >> num;
	cout << "Enter passenger name: \n";
	cin >> name;

	for (int i = 0; i < Ticket1.size(); i++)
	{
		if (Ticket1[i].tripnumber == num && Ticket1[i].passenger_name == name) {
			find = true;
			seatsNo = Ticket1[i].numofseats;
			Ticket1.erase(Ticket1.begin() + i);

		}
	}

	if (find)
	{
		for (int j = 0; j < Trip1.size(); j++)
		{
			if (Trip1[j].TripNumber == num)
			{
				Trip1[j].AvailableSeats = Trip1[j].AvailableSeats + seatsNo;
			}
		}
		ofstream TripData("Trip.txt");

		for (int i = 0; i < Trip1.size(); i++) {

			TripData << Trip1[i].TripNumber << endl;
			TripData << Trip1[i].BoardingPoint << endl;
			TripData << Trip1[i].DestinationPoint << endl;
			TripData << Trip1[i].Fare << endl;
			TripData << Trip1[i].month << endl;
			TripData << Trip1[i].day << endl;
			TripData << Trip1[i].AvailableSeats << endl;
			TripData << Trip1[i].TrainNumber << endl;


		}
		ofstream TicketData;
		TicketData.open("Reservation.txt");
		for (int i = 0; i < Ticket1.size(); i++) {
			TicketData << Ticket1[i].passenger_name << endl;
			TicketData << Ticket1[i].tripnumber << endl;
			TicketData << Ticket1[i].boarding_point << endl;
			TicketData << Ticket1[i].destination_point << endl;
			TicketData << Ticket1[i].month << endl;
			TicketData << Ticket1[i].day << endl;
			TicketData << Ticket1[i].numofseats << endl;
			TicketData << Ticket1[i].trainnumber << endl;

		}
		TicketData.close();
		TripData.close();
		Trip1.clear();
		Ticket1.clear();
		BookTicket();
	}
	else
	{
		cout << " Sorry, There is no trip \n";
		Trip1.clear();
		Ticket1.clear();
	}
}
void User::deleteReservation()
{
	viewReservation();
	ReadTripData();
	ReadPassData();
	int num, seatsNo;
	string name;
	bool find = false;
	cout << "PLease,Enter number of trip to be deleted : \n";
	cin >> num;
	cout << "Enter passenger name: \n";
	cin >> name;

	for (int i = 0; i < Ticket1.size(); i++) {
		if (Ticket1[i].tripnumber == num && Ticket1[i].passenger_name == name) {
			find = true;
			seatsNo = Ticket1[i].numofseats;
			Ticket1.erase(Ticket1.begin() + i);
		}
	}

	if (find) {
		cout << "\n------- Deleted successfully! -------\n";
		for (int j = 0; j < Trip1.size(); j++)
		{
			if (Trip1[j].TripNumber == num)
			{
				Trip1[j].AvailableSeats = Trip1[j].AvailableSeats + seatsNo;
			}
		}
		ofstream TripData("Trip.txt");

		for (int i = 0; i < Trip1.size(); i++) {

			TripData << Trip1[i].TripNumber << endl;
			TripData << Trip1[i].BoardingPoint << endl;
			TripData << Trip1[i].DestinationPoint << endl;
			TripData << Trip1[i].Fare << endl;
			TripData << Trip1[i].month << endl;
			TripData << Trip1[i].day << endl;
			TripData << Trip1[i].AvailableSeats << endl;
			TripData << Trip1[i].TrainNumber << endl;


		}
		ofstream TicketData;
		TicketData.open("Reservation.txt");
		for (int i = 0; i < Ticket1.size(); i++) {
			TicketData << Ticket1[i].passenger_name << endl;
			TicketData << Ticket1[i].tripnumber << endl;
			TicketData << Ticket1[i].boarding_point << endl;
			TicketData << Ticket1[i].destination_point << endl;
			TicketData << Ticket1[i].month << endl;
			TicketData << Ticket1[i].day << endl;
			TicketData << Ticket1[i].numofseats << endl;
			TicketData << Ticket1[i].trainnumber << endl;

		}
		TicketData.close();
		TripData.close();
	}

	Ticket1.clear();
	Trip1.clear();
}
void User::BookTicket()
{
	ReadTripData();
	ReadPassData();

	string Pname, PBoardingPoint, PDestinationPoint;
	int Pmonth, Pday, PNumberofSeats, tripNo, trainNo;
	bool find = false;
	bool Booked = false;

	cout << "------Please Enter The Data To confirm your booking------ :\n";
	cout << "Enter Your Name :\n";
	cin >> Pname;
	cout << "Enter your Boarding point  :\n";
	cin >> PBoardingPoint;
	cout << "Enter your Destination point \n";
	cin >> PDestinationPoint;
	cout << "Enter the date of the booking:\n";
	cout << "Month :\n";
	cin >> Pmonth;
	cout << "Day:\n";
	cin >> Pday;
	cout << "Enter the number of seats you want to reserve :\n";
	cin >> PNumberofSeats;

	for (int i = 0; i < Trip1.size(); i++)
	{
		if (Trip1[i].BoardingPoint == PBoardingPoint && Trip1[i].DestinationPoint == PDestinationPoint && Trip1[i].month == Pmonth && Trip1[i].day == Pday)
		{
			find = true;
			if (Trip1[i].AvailableSeats >= PNumberofSeats && find == true)
			{

				Booked = true;
				Trip1[i].AvailableSeats = Trip1[i].AvailableSeats - PNumberofSeats;
				trainNo = Trip1[i].TrainNumber;
				tripNo = Trip1[i].TripNumber;
			}
		}
	}

	if (!find)
	{
		cout << "Sorry, This trip is not found in our system!\n";
	}

	if (Booked == true && find == true) {
		cout << "\n-------Your trip is Booked Successfully! -------\n";
		ticket.boarding_point = PBoardingPoint;
		ticket.destination_point = PDestinationPoint;
		ticket.month = Pmonth;
		ticket.day = Pday;
		ticket.passenger_name = Pname;
		ticket.tripnumber = tripNo;
		ticket.numofseats = PNumberofSeats;
		ticket.trainnumber = trainNo;

		Ticket1.push_back(ticket);

		ofstream TripData("Trip.txt");

		for (int i = 0; i < Trip1.size(); i++) {

			TripData << Trip1[i].TripNumber << endl;
			TripData << Trip1[i].BoardingPoint << endl;
			TripData << Trip1[i].DestinationPoint << endl;
			TripData << Trip1[i].Fare << endl;
			TripData << Trip1[i].month << endl;
			TripData << Trip1[i].day << endl;
			TripData << Trip1[i].AvailableSeats << endl;
			TripData << Trip1[i].TrainNumber << endl;


		}

		ofstream PassengerData("Reservation.txt");
		for (int i = 0; i < Ticket1.size(); i++) {
			PassengerData << Ticket1[i].passenger_name << endl;
			PassengerData << Ticket1[i].tripnumber << endl;
			PassengerData << Ticket1[i].boarding_point << endl;
			PassengerData << Ticket1[i].destination_point << endl;
			PassengerData << Ticket1[i].month << endl;
			PassengerData << Ticket1[i].day << endl;
			PassengerData << Ticket1[i].numofseats << endl;
			PassengerData << Ticket1[i].trainnumber << endl;

		}
		TripData.close();
		PassengerData.close();


	}
	else if (Booked == false && find == true) {
		cout << " Sorry,This Trip is Full !    " << endl;
		cout << "You can reserve another trip";
		mapTrip(PBoardingPoint, PDestinationPoint);
	}
	Trip1.clear();
	Ticket1.clear();
	//	TripData.close();

}