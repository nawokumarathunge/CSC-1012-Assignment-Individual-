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

//Main menu function
void menu(){

    int choice;
    do{
        printf("\n==========LOGISTIC MANAGEMENT SYSTEM==========\n\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. New Delivery Request\n");
        printf("4. View Reports\n");
        printf("5. Save Data to Files\n");
        printf("6. Load Data from Files\n");
        printf("0. Exit\n\n");

        printf("Enter your choice:");
        scanf("%d",&choice);

        switch(choice){

        case 1:
            cityManagement();
            break;

        case 2:
            distanceManagement();
            break;

        case 3:
            newDeliveryRequest();
            break;

        case 4:
            viewReports();
            break;

        case 5:
            saveData();
            break;

        case 6:
            loadData();
            break;

        case 0:
            printf("Exit! Thank you for choosing LOGIC MANAGEMENT SYSTEM.\n");
            break;

        default:
            printf("Invalid choice.\n");


        }

    }while(choice!=0);

}

//City Management
void cityManagement(){

    int choice;

    do{
        printf("\n=====CITY MANAGEMENT=====\n\n");
        printf("1. Add new city.\n");
        printf("2. Rename city.\n");
        printf("3. Remove city.\n");
        printf("4. Display Cities.\n");
        printf("0. Back\n\n");

        printf("Enter your choice:");
        scanf("%d",&choice);

        switch(choice){

        case 1:
            if(cityCount>=MAX_CITIES){
                printf("City limit reached!\n");
            }else{
            printf("Enter City Name:");
            scanf("%s",cities[cityCount]);
            cityCount++;

            printf("\nCity Added Successfully.\n");

            }
            break;

        case 2:
            displayCities();

            int index=getCityIndex();

            if(index>=0 && index<cityCount){

                printf("Enter new name of the city:");
                scanf("%s",cities[index]);

                printf("\nCity Renamed Successfully.\n");
            }else{
                printf("Invalid Index.\n");
            }
            break;

        case 3:
            displayCities();

            int ind=getCityIndex();

            if(ind>=0 && ind<cityCount){
                for(int i=ind;i<cityCount-1;i++){
                    for(int k=0;k<MAX_NAME_LENGTH;k++){
                        cities[i][k]=cities[i+1][k];
                    }
                    for(int j=0;j<cityCount;j++){
                        distanceMatrix[i][j]=distanceMatrix[i+1][j];
                        distanceMatrix[j][i]=distanceMatrix[j][i+1];
                    }

                }
                cityCount--;
                printf("\nCity Removed successfully.\n");
            }
            break;

        case 4:
            displayCities();
            break;



        }
    }while(choice!=0);
}
