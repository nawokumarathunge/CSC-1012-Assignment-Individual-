#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Constants Declaration
#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define NUM_VEHICLES 3
#define FUEL_PRICE 310.0
#define INF 1e9 //For shortest root calculations

//Global Variables declarations

//Cities
char cities[MAX_CITIES][MAX_NAME_LENGTH];
int cityCount=0;

//Distance matrix
double distanceMatrix[MAX_CITIES][MAX_CITIES];

//Deliveries
int deliverySource[MAX_DELIVERIES];
int deliveryDestination[MAX_DELIVERIES];
int deliveryVehicleType[MAX_DELIVERIES];
double deliveryWeight[MAX_DELIVERIES];
double deliveryDistance[MAX_DELIVERIES];
double deliveryCost[MAX_DELIVERIES];
double deliveryEstimatedTime[MAX_DELIVERIES];
double deliveryFuelUsed[MAX_DELIVERIES];
double deliveryFuelCost[MAX_DELIVERIES];
double deliveryTotalCost[MAX_DELIVERIES];
double deliveryProfit[MAX_DELIVERIES];
double deliveryCustomerCharge[MAX_DELIVERIES];
int deliveryCount=0;

//Vehicles
char vehicleName[NUM_VEHICLES][20]={"Van","Truck","Lorry"};
int vehicleCapacity[NUM_VEHICLES]={1000,5000,10000};
double vehicleRate[NUM_VEHICLES]={30.0,40.0,80.0};
double vehicleSpeed[NUM_VEHICLES]={60.0,50.0,45.0};
double vehicleEfficiency[NUM_VEHICLES]={12.0,6.0,4.0};

//Function Prototypes
void menu();
void cityManagement();
void distanceManagement();
void newDeliveryRequest();
void viewReports();
void saveData();
void loadData();
void displayCities();
void displayDistanceTable();
int getCityIndex();
double calculateDeliveryCost(double D,double R,double W);
double calculateFuelUsed(double D,double E);
double calculateTime(double D,double S);

//File Handling Functions
void saveRoutesToFile();
void loadRoutesFromFile();
void saveDeliveriesToFile();
void loadDeliveriesFromFile();

//Shortest root function
double findShortestDistance(int source,int destination);



int main()
{

    return 0;
}
