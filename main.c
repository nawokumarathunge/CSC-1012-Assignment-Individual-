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
int getRenameCityIndex();
int getRemoveCityIndex();
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
    int i,j;
    for(i=0;i<MAX_CITIES;i++){
        for(j=0;j<MAX_CITIES;j++){
            if(i==j){
                distanceMatrix[i][j]=0;//Distance from a city to itself
            }else{
                distanceMatrix[i][j]=-1;//Distance not set yet
            }
        }
    }
    loadData(); //Auto load when startup
    menu();
    saveData(); //Auto save before exit


    return 0;

}

//Main menu function
void menu(){

    int choice;
    do{
        printf("============================================================================\n\n");
        printf("\===========LOGISTIC MANAGEMENT SYSTEM======================================\n\n");
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

            int index=getRenameCityIndex();

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

            int ind=getRemoveCityIndex();

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

//Distance Management
void distanceManagement(){

    int choice;
    do{
        printf("\n=====DISTANCE MANAGEMENT=====\n\n");
        printf("1. Enter/Edit Distance.\n");
        printf("2. Display Distance Table.\n");
        printf("0. Back\n");

        printf("\nEnter your choice:");
        scanf("%d",&choice);

        if(choice==1){
            if(cityCount<2){
                printf("\nAdd at least two cities first.\n");

            }
            displayCities();

            int a,b;

            printf("\nEnter source city index:");
            scanf("%d",&a);

            printf("Enter Destination city index:");
            scanf("%d",&b);

            if(a==b){
                printf("\nDistance from city to itself = 0.\n");

            }
            double d;

            printf("Enter Distance(km):");
            scanf("%lf",&d);

            distanceMatrix[a][b]=d;
            distanceMatrix[b][a]=d;

            printf("\nDistance Updated.\n");


        }else if(choice==2){
            displayDistanceTable();
        }
    }while(choice!=0);
}

//New delivery request
void newDeliveryRequest(){

    if(cityCount<2){
        printf("\nAdd cities and distance first.\n");
        return;
    }

    displayCities();

    int src,dest;

    printf("\nEnter Source city index:");
    scanf("%d",&src);

    printf("Enter Destination city index:");
    scanf("%d",&dest);

    if(src==dest){
        printf("\nSource and destination must differ.\n");
        return;

    }

    //Find shortest route

    double dist = findShortestDistance(src,dest);

    if(dist==INF){
        printf("No route found between these cities.\n");
        return;
    }

    printf("Shortest available route distance:%.2f km\n",dist);

    double weight;
    printf("Enter weight (kg):");
    scanf("%lf",&weight);

    printf("\nSelect vehicle type:\n");
    for(int i=0;i<NUM_VEHICLES;i++){
        printf("%d. %s\n",i+1,vehicleName[i]);
    }

    int choice;

    printf("\nEnter vehicle number:");
    scanf("%d",&choice);

    if(choice<1||choice>NUM_VEHICLES){
        printf("Invalid vehicle.\n");
        return;

    }
    int v=choice-1;

    if(weight>vehicleCapacity[v]){
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    //Calculation
    double cost=calculateDeliveryCost(dist,vehicleRate[v],weight);
    double fuelUsed=calculateFuelUsed(dist,vehicleEfficiency[v]);
    double fuelCost=fuelUsed*FUEL_PRICE;
    double operationalCost=cost+fuelCost;
    double profit=cost*0.25;
    double customerCharge=operationalCost+profit;
    double time=calculateTime(dist,vehicleSpeed[v]);

    deliverySource[deliveryCount]=src;
    deliveryDestination[deliveryCount]=dest;
    deliveryVehicleType[deliveryCount]=v;
    deliveryWeight[deliveryCount]=weight;
    deliveryDistance[deliveryCount]=dist;
    deliveryCost[deliveryCount]=cost;
    deliveryFuelUsed[deliveryCount]=fuelUsed;
    deliveryFuelCost[deliveryCount]=fuelCost;
    deliveryTotalCost[deliveryCount]=operationalCost;
    deliveryProfit[deliveryCount]=profit;
    deliveryCustomerCharge[deliveryCount]=customerCharge;
    deliveryEstimatedTime[deliveryCount]=time;

    deliveryCount++;

    //Print delivery summary
    printf("\n============================================================================\n");
    printf("\n==========DELIVERY COST ESTIMATION==========================================\n\n");
    printf("------------------------------------------------------------------------------\n");
    printf("\nFrom: %s\n",cities[src]);
    printf("To: %s\n",cities[dest]);
    printf("Distance: %.2f km\n",dist);
    printf("Vehicle: %s\n",vehicleName[v]);
    printf("Weight: %.2f kg\n",weight);
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\n",cost);
    printf("Fuel Used: %.2f LKR\n",fuelUsed);
    printf("Fuel Cost: %.2f LKR\n",fuelCost);
    printf("Operational Cost: %.2f LKR\n",operationalCost);
    printf("Profit: %.2f LKR\n",profit);
    printf("Customer Charge: %.2f LKR\n",customerCharge);
    printf("Estimated Time: %.2f hours\n",time);
    printf("\n============================================================================\n");

}

//Reports
void viewReports(){

    double totalDistance=0,totalTime=0,totalProfit=0,totalRevenue=0;

    for(int i=0;i<deliveryCount;i++){
        totalDistance+=deliveryDistance[i];
        totalTime+=deliveryEstimatedTime[i];
        totalProfit+=deliveryProfit[i];
        totalRevenue+=deliveryCustomerCharge[i];
    }

    printf("\n============================================================================\n");
    printf("\n==========REPORTS==========\n");
    printf("Total Deliveries: %d\n",deliveryCount);
    printf("Total Distance: %.2f km\n",totalDistance);
    printf("Total Revenue: %.2f LKR\n",totalRevenue);
    printf("Total Profit: %.2f LKR\n",totalProfit);

    if(deliveryCount>0){
        double avgDeliveryTime=totalTime/deliveryCount;
    printf("Average Delivery Time: %.2f LKR\n",avgDeliveryTime);
    }
    printf("\n============================================================================\n");


}

void displayCities(){

    printf("\n=====CITIES=====\n\n");
    for(int i=0;i<cityCount;i++){
        printf("%d. %s\n",i,cities[i]);
    }

}

void displayDistanceTable(){

    printf("\n=====DISPLAY DISTANCE TABLE=====\n\n");
    for(int i=0;i<cityCount;i++){
        printf("%16s",cities[i]);
    }
    printf("\n");

    for(int i=0;i<cityCount;i++){
        printf("%-6s",cities[i]);
            for(int j=0;j<cityCount;j++){
                if(distanceMatrix[i][j]<0)
                    printf("%10s","-");
                else
                    printf("%12.2f",distanceMatrix[i][j]);
        }
            printf("\n");
    }
}

int getRenameCityIndex(){
    int index;

    printf("Enter city index to rename:");
    scanf("%d",&index);
    return index;

}

int getRemoveCityIndex(){
    int index;

    printf("Enter city index to remove:");
    scanf("%d",&index);
    return index;

}

//Calculations
double calculateDeliveryCost(double D,double R,double W){

    return D*R*(1+(W/10000.0));
}

double calculateFuelUsed(double D,double E){

    return D/E;
}

double calculateTime(double D,double S){

    return D/S;
}

double findShortestDistance(int source,int destination){

    double dist[MAX_CITIES];
    int visited[MAX_CITIES]={0};

    for(int i=0;i<cityCount;i++)
        dist[i]=INF;
    dist[source]=0;

    for(int count=0;count,cityCount;count++){
        int u=-1;
        double minDist=INF;
        for(int i=0;i<cityCount;i++){
            if(!visited[i]  && dist[i]<minDist){
                minDist=dist[i];
                u=i;
            }
        }
        if(u == -1)
            break;
        visited[u]=1;

        for(int v=0;v<cityCount;v++){
            if(distanceMatrix[u][v]>0 && !visited[v]){
                double newDist=dist[u]+distanceMatrix[u][v];
                if(newDist<dist[v])
                    dist[v]=newDist;
            }
        }
    }

    return dist[destination];

}

//File handling functions

void saveRoutesToFile(){

    FILE *f = fopen("routes.txt","w");
    if(!f){
        printf("Error saving routes!\n");
        return;
    }
    //Save number of cities
    fprintf(f,"%d\n",cityCount);

    //Save city name
    for(int i=0;i<cityCount;i++){
        fprintf(f, "%s\n",cities[i]);
    }

    //Save distance matrix
    for(int i=0;i<cityCount;i++){
        for(int j=0;j<cityCount;j++){
            fprintf(f, "%.2f",distanceMatrix[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

}

void loadRoutesFromFile(){

    FILE *f=fopen("routes.txt","r");
    if(!f){
        return;
    }
    fscanf(f, "%d\n",&cityCount);

    for(int i=0;i<cityCount;i++){
        fscanf(f, "%s\n",cities[i]);
    }

    for(int i=0;i<cityCount;i++){
        for(int j=0;j<cityCount;j++){
            fscanf(f, "%lf",&distanceMatrix[i][j]);
        }
    }

    fclose(f);
}

void saveDeliveriesToFile(){

    FILE *f =fopen("deliveries.txt","w");

    if(!f)
        return;
    fprintf(f, "%d\n",deliveryCount);

    for(int i=0;i<deliveryCount;i++){
        fprintf(f, "%d %d %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n"
                ,deliverySource[i],deliveryDestination[i],deliveryVehicleType[i],deliveryWeight[i],
                deliveryDistance[i],deliveryCost[i],deliveryFuelUsed[i],deliveryFuelCost[i],
                deliveryTotalCost[i],deliveryProfit[i],deliveryCustomerCharge[i],deliveryEstimatedTime[i]);
    }

    fclose(f);

}

void loadDeliveriesFromFile(){

    FILE *f=fopen("deliveries.txt", "r");

    if(!f)
        return;

    fscanf(f, "%d\n",&deliveryCount);

    for(int i=0;i<deliveryCount;i++){
        fscanf(f, "%d %d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &deliverySource[i], &deliveryDestination[i], &deliveryVehicleType[i],
               &deliveryWeight[i], &deliveryDistance[i], &deliveryCost[i],
               &deliveryFuelUsed[i], &deliveryFuelCost[i], &deliveryTotalCost[i],
               &deliveryProfit[i], &deliveryCustomerCharge[i], &deliveryEstimatedTime[i]);
    }
    fclose(f);
}

void saveData() {
    saveRoutesToFile();
    saveDeliveriesToFile();
    printf("Data saved to files.\n");
}

void loadData() {
    loadRoutesFromFile();
    loadDeliveriesFromFile();
    printf("Data loaded (if available).\n");
}



