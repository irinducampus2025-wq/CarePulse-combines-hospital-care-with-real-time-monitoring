#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_SPECIALTIES 4
#define MAX_BEDS         20
#define MAX_PATIENTS     100
#define NUM_WARDS        4
// Doctor specialty lookup table
const char specialtyName[NUM_SPECIALTIES][30]={"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const double baseFee[NUM_SPECIALTIES]         ={1500.00, 2500.00, 4500.00, 5000.00};
const int consultMinutes[NUM_SPECIALTIES]     ={15, 20, 30, 30};
const int dailyCap[NUM_SPECIALTIES]           ={30, 20, 12, 10};

//Running queue count per specialty
int queueCount[NUM_SPECIALTIES] = {0, 0, 0, 0};

//Hospital ward lookup tables
const char wardName[NUM_WARDS][30]={"General ward", "Paediatric Ward", "Surgical ward", "ICU (Intensive Care Unit)"};
const double wardDailyRate[NUM_WARDS]={3000.00, 6000.00, 12000.00, 25000.00};
const int wardBedCapacity[NUM_WARDS] = {20, 10, 10, 5};

//Bed occupancy matrix
int bedOccupancy[NUM_WARDS][MAX_BEDS];

//patient parallel array
char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int patientTriageLevel[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int patientDaysAdmitted[MAX_PATIENTS];
int patientBedNumber[MAX_PATIENTS];
char patientDiagnosis[MAX_PATIENTS][100];
char patientCondition[MAX_PATIENTS][30];
int patientCount=0;


// function prototypes
double calculateWaitTime(int specialtyIndex);
double calculateSurcharge(int triageLevel, double fee);
double calculateWardCost(int daysAdmitted,int wardIndex);
void generateBill(int patientIndex);
void sortPatientsByPriority(void);
void displayReports(void);
void initializeBedOccupancy(void);
void displaySpecialties(void);
void displayWards(void);
void displayBedStatus(void);
int findFreeBed (int wardIndex);
void registerPatient(void);
void viewPatientInformation(void);
void viewAllPatients (void);
void showWardStatus (int wardIndex);

int main (void)
{

    initializeBedOccupancy();
    int choice = -1;

    do {

        printf("\n==================================================================================\n");
        printf("                   SMART HOSPITAL & RESOURCES ALLOCATION SYSTEM\n");
        printf("==================================================================================\n");
        printf("                   1.View Doctor Specialities\n");
        printf("                   2.View ward informations\n");
        printf("                   3.View bed occupancy\n");
        printf("                   4.Register new patient      \n");
        printf("                   5.View patient by priority  \n");
        printf("                   6.View patient informations \n");
        printf("                   7.View All Registered Patients\n");
        printf("                   8.View performance report   \n");
        printf("                   0.Exit\n");
        printf("\n=================================================================================\n");
        printf("Enter Your choice :");
        scanf("%d", &choice);


        switch (choice) {
            case 1: displaySpecialties(); break;
            case 2: displayWards(); break;
            case 3: displayBedStatus(); break;
            case 4: registerPatient(); break;
            case 5: sortPatientsByPriority(); break;
            case 6: viewPatientInformation(); break;
            case 7: viewAllPatients(); break;
            case 8: displayReports(); break;
            case 0: printf("\nExiting. Goodbye!\n"); break;
            default: printf("\nInvalid choice, try again.\n");
        }
    }while (choice !=0);

    return 0;
} 

double calculateWaitTime(int specialtyIndex)
{
    return (double)queueCount[specialtyIndex]* consultMinutes[specialtyIndex];

}

double calculateSurcharge(int triageLevel, double fee)
{
    if (triageLevel == 2)
        return fee*0.20;
    else if(triageLevel==3)
        return fee*0.50;
    else 
        return 0.0;
}

double calculateWardCost(int daysAdmitted,int wardIndex)
{
    if (daysAdmitted <= 0 || wardIndex < 0)
        return 0.0;
    return daysAdmitted *wardDailyRate[wardIndex];
}

void generateBill(int patientIndex)
{
    int i=patientIndex;
    double base = baseFee[patientSpecialty[i]];
    double surcharge =calculateSurcharge(patientTriageLevel[i],base);
    double wardCost = calculateWardCost(patientDaysAdmitted[i],patientWard[i]);
    double gross = base + surcharge + wardCost;

    double discount = 0.0;
    if (patientAge[i]<5||patientAge[i]>65)
        discount = gross * 0.15;
   double finalAmount = gross - discount;
   double waitTime = calculateWaitTime(patientSpecialty[i]);


   printf("\n==========================================================\n");
   printf("        SMART HOSPITAL ADMISSION AND BILL \n");
   printf("==========================================================\n");
   printf("     patient ID     : PAT - %04d\n", 1001 + i);
   printf("     patient Name   : %s\n", patientName[i]);
   printf("     patient Age    : %d Years\n", patientAge[i]);
   if (discount > 0)
         printf("   (15%% Subsidy Eligible)\n");
   
   printf("     Specialty      : %s\n", specialtyName[patientSpecialty[i]]);

   if (patientAdmitted[i]&& patientBedNumber[i]>=0){
    printf("     Assigned Ward  : %s (Bed #%02d)\n",
           wardName[patientWard[i]], patientBedNumber[i]+1);
    }
   else {
    printf("    Assigned Ward   : Not Admitted (OPD)\n");
   }
   
   printf("     Urgency Level  : Level %d  ", patientTriageLevel[i]);
   if (patientTriageLevel[i] == 1){
       printf("(Normal)\n");
   }
   else if (patientTriageLevel[i]==2){
       printf("(Urgent)\n");
   }
   else {
       printf("(Critical)\n");
   }
   printf("\n==========================================================\n");
   printf("Base Consultation Fee     : LKR %10.2f\n", base);
   printf("Emergency Surcharge       : LKR %10.2f", surcharge);
   if (patientTriageLevel[i]==2){
    printf(" (20%%)\n");
   }
   else if (patientTriageLevel[i]==3){
    printf(" (50%%)\n");
    
   }
   else{
    printf("\n");
   }
   printf("\n");
   if (patientDaysAdmitted[i]>0){
    printf("Ward Stay cost (%d Days)   : LKR %10.2f\n" , patientDaysAdmitted[i], wardCost);
   }
   else{
    printf("Ward Stay Cost             : LKR %10.2f\n", wardCost);
   }

   printf("==========================================================\n");
   printf("Gross Total Bill          : LKR %10.2f\n", gross);
   printf("Age Subsidy Discount      : LKR %10.2f\n", -discount);
   if (discount > 0)
    printf(" (15%%)");
    printf("\n");


    printf("==========================================================\n");
    printf("Final Payable Amount      : LKR %10.2f\n", finalAmount);

    if (waitTime <=0.01){
     printf(" Estimated waiting Time  : 0.00 mins(Immediate Attention)\n");
    }
    else {
      printf("Estimated Waiting Time    :%.2f mins\n", waitTime);
    }

    printf("==========================================================\n");
    }



void sortPatientsByPriority(void)
{
    if (patientCount <=1){
        printf("\nNot enough patients to sort. \n");
        return;
    }
     //Bubble sort - only swap when urgency is higher
    for (int i=0; i<patientCount-1; i++){
        for (int j=0; j <patientCount -i-1; j++){
           //swap only if the next patient has higher urgency
            if (patientTriageLevel[j]<patientTriageLevel[j+1]){
                //swap all patient parallel array

                // Name
                char tempName[50];
                strcpy(tempName,patientName[j]);
                strcpy(patientName[j],patientName[j+1]);
                strcpy(patientName[j+1], tempName);
                //Age
                int tempAge =patientAge[j];
                patientAge[j]= patientAge[j+1];
                patientAge[j+1]=tempAge;
                //urgency
                int tempUrgency=patientTriageLevel[j];
                patientTriageLevel[j]=patientTriageLevel[j+1];
                patientTriageLevel[j+1]=tempUrgency;
                //specialty
                int tempSpec=patientSpecialty[j];
                patientSpecialty[j]=patientSpecialty[j+1];
                patientSpecialty[j+1]=tempSpec;
                //Admitted flag
                int tempAdmitted=patientAdmitted[j];
                patientAdmitted[j]=patientAdmitted[j+1];
                patientAdmitted[j+1]=tempAdmitted;
                //Ward
                int tempWard=patientWard[j];
                patientWard[j]=patientWard[j+1];
                patientWard[j+1]=tempWard;
                //Days admitted
                int tempDays=patientDaysAdmitted[j];
                patientDaysAdmitted[j]=patientDaysAdmitted[j+1];
                patientDaysAdmitted[j+1]=tempDays;
                //Bed number
                int tempBed= patientBedNumber[j];
                patientBedNumber[j]=patientBedNumber[j+1];
                patientBedNumber[j+1]=tempBed;
                //diagnosis
                char tempDiag[100];
                strcpy(tempDiag,patientDiagnosis[j]);
                strcpy(patientDiagnosis[j],patientDiagnosis[j+1]);
                strcpy(patientDiagnosis[j+1],tempDiag);
                //condition
                char tempCond[30];
                strcpy(tempCond, patientCondition[j]);
                strcpy(patientCondition[j],patientCondition[j+1]);
                strcpy(patientCondition[j+1],tempCond);



           }
        }
    }
    printf("\n=========Patients Sorted by Priority (Critical -> Urgent -> Normal =========\n)");
    for (int i=0 ; i<patientCount ;i++){
        printf("%d. %-20s|Urgency :%d | Specialty : %s\n", i+1,patientName[i],patientTriageLevel[i],specialtyName[patientSpecialty[i]]);
        
    }
    printf("==================================================================================\n");
} 


void displayReports(void)
{
    if (patientCount == 0){
        printf("\nNo patients registered yet. Cannot generate reports.\n");
        return;
    }
    //1. patient by urgency level
    int normal=0,urgent=0,critical=0;

    for (int i=0 ; i<patientCount ; i++){
        if (patientTriageLevel[i]==1)
         normal++;
        else if(patientTriageLevel[i]==2) 
         urgent++;
        else if (patientTriageLevel[i]==3) 
         critical++; 
    }
    printf("\n==================== PERFORMANCE REPORTS ====================\n");
    printf(" 1.Patient by urgency level\n");
    printf("   Total patients Registered : %d\n", patientCount);
    printf("   - Normal   (Level 1)  : %d\n", normal);
    printf("   - Urgent    (Level 2) : %d\n ", urgent);
    printf("  - Critical (Level 3)  : %d\n", critical);

    //2. Total revenue and Total discount
    double totalRevenue =0.0;
    double totalDiscount =0.0;

    for (int i =0; i<patientCount; i++){
        double base = baseFee[patientSpecialty[i]];
        double surcharge = calculateSurcharge(patientTriageLevel[i], base);
        double wardCost = calculateWardCost(patientDaysAdmitted[i], patientWard[i]);
        double gross = base + surcharge + wardCost;

        double discount =0.0;
        if (patientAge[i]<5 || patientAge[i] >65){
             discount = gross * 0.15;
            }
            totalRevenue += (gross - discount);
            totalDiscount += discount;
    }

    printf("\n 2. Financial Summary\n");
    printf("    Total Revenue Earned     : LKR %.2f\n ", totalRevenue);
    printf("   Total Discount Granted   : LKR %.2f\n", totalDiscount);

    //3. Bed occupancy percentage per ward

    printf("\n 3. Bed Occupancy per Ward\n");
    for (int w=0; w<NUM_WARDS; w++){
        int occupied = 0;
        for (int b=0 ; b< wardBedCapacity[w]; b++){
            if (bedOccupancy[w][b]==1)
              occupied++;
        }
        double percentage =0.0;
        if (wardBedCapacity[w]>0){
          percentage = (occupied * 100.0)/ wardBedCapacity[w];
        }
        printf("   %-25s : %2d / %2d beds occupied (%.1f%%)\n",wardName[w],occupied,wardBedCapacity[w],percentage);
    }
    //4.Highest paying patient

    int highestIndex = 0;
    double highestBill = 0.0;
    
    for (int i =0 ;i <patientCount;i++){
        double base = baseFee[patientSpecialty[i]];
        double surcharge =calculateSurcharge(patientTriageLevel[i], base);
        double wardCost= calculateWardCost(patientDaysAdmitted[i],patientWard[i]);
        double gross = base + surcharge + wardCost;

        double discount = 0.0;
        if (patientAge[i] <5 || patientAge [i] > 65)
          discount = gross *0.15; 
        

        double finalBill = gross - discount;

        if (finalBill > highestBill){
            highestBill = finalBill;
            highestIndex = i;
        }
    }
    printf("\n 4. Highest Paying Patient\n");
    printf("  Name : %s\n", patientName[highestIndex] );
    printf("  Bill : LKR %.2f\n", highestBill);

    printf("=============================================================\n");
}   

void initializeBedOccupancy(void)
{
    for (int ward =0; ward <NUM_WARDS; ward++){
        for (int bed = 0; bed<MAX_BEDS; bed++){
            bedOccupancy[ward][bed]=0;
        }
    }

}

void displaySpecialties(void)
{
    printf("\n%-4s %-25s %-12s %-10s %-8s\n", "ID", "Specialty", "Fee (LKR)", "Time/Pt", "Cap" );
    for (int i=0;i<NUM_SPECIALTIES;i++){
        printf("%-4d %-25s %-12.2f %-10d %-8d\n",i+1, specialtyName[i],baseFee[i], consultMinutes[i], dailyCap[i]);
    }

}

void displayWards(void)
{
    printf("\n%-4s %-25s %-15s %-8s \n","ID", "Ward", "Rate/Day (LKR)", "Beds");
    for (int i=0; i<NUM_WARDS;i++){
        printf("%-4d %-25s %-15.2f %-8d \n", i+1, wardName[i], wardDailyRate[i], wardBedCapacity[i]);
    }
}

void displayBedStatus(void)
{
    printf("\nBed Occupancy (0=Available, 1=Occupied)\n");
    for (int ward =0;ward<NUM_WARDS;ward++){
        printf("%-25s : ",wardName[ward]);
        for (int bed =0 ; bed < wardBedCapacity[ward]; bed++){
            printf("%d ", bedOccupancy[ward][bed]);
        }
        printf("\n");
    }
}

int findFreeBed (int wardIndex)
{
    for (int bed =0 ; bed < wardBedCapacity[wardIndex];bed++){
        if (bedOccupancy[wardIndex][bed]==0){
            return bed;
        }
    }
    return -1;
}

void registerPatient(void)
{
    if(patientCount >=MAX_PATIENTS){
        printf("\n Sorry, the system is full - no more patients can be added.\n");
        return;
    }
    int i = patientCount;
    printf("\n----- New patient Registration -----");

    printf("patient name : ");
    scanf(" %49[^\n]", patientName[i]);

    printf("patient age : ");
    scanf(" %d", &patientAge[i]);

    do{
        printf("Urgency level (1=Normal, 2=Urgent, 3=Critical): ");
        scanf("%d", &patientTriageLevel[i]);
    }while (patientTriageLevel[i]<1|| patientTriageLevel[i]>3);

    printf("Diagnosis (what's wrong with the patient): ");
    scanf(" %99[^\n]", patientDiagnosis[i]);

    printf("Current condition (e.g. Stable, Critical, Recovering): ");
    scanf(" %29[^\n]", patientCondition[i]);

    displaySpecialties();

    int chosenSpecialty;
    do{
        printf("Choose specialty ID (1-%d): ", NUM_SPECIALTIES);
        scanf("%d", &chosenSpecialty);
    }while (chosenSpecialty <1 || chosenSpecialty > NUM_SPECIALTIES);
    patientSpecialty[i] = chosenSpecialty - 1;

    queueCount[patientSpecialty[i]]++;
    int admitted;
    do{
        printf("Admit to a ward? (1=Yes, 0=No): ");
        scanf("%d" ,&admitted);
    }while (admitted != 0 && admitted != 1);
    patientAdmitted[i]=admitted;

    if (admitted== 1 ){
        printf("\nAvailable Wards:\n");
        for (int w=0;w<NUM_WARDS;w++){
            printf("%d . %s\n", w+1, wardName[w]);
        }
       int chosenWard;
       do{
         printf("Chosen Ward ID (1-%d): ", NUM_WARDS);
         scanf("%d", &chosenWard);
       }while (chosenWard <1 || chosenWard >NUM_WARDS);
       patientWard[i] = chosenWard -1;
       showWardStatus(patientWard[i]);
    
       printf("Number of days admitted : " );
       scanf("%d", &patientDaysAdmitted[i]);

       int bed =findFreeBed(patientWard[i]);
       if (bed ==-1){
       printf(" Sorry ,%s has no free beds right now \n ",wardName[patientWard[i]]);
       patientBedNumber[i]=-1;
       }else{
             bedOccupancy[patientWard[i]][bed]=1;
             patientBedNumber[i]= bed;
             printf("Assigned to %s , bed #%02d.\n", wardName[patientWard[i]], bed+1);
       }
       
    }else{
         patientWard[i]=-1;
         patientDaysAdmitted[i]=0;
         patientBedNumber[i]= -1;
    }
         patientCount++;
         generateBill(i);
         queueCount[patientSpecialty[i]]++;
}

void viewPatientInformation(void)
{
   if (patientCount ==0){
       printf("\n No Patient registered yet .\n");
       return;
   }
       printf("\n ----- Registered Patients -----");
       for (int i=0;i<patientCount;i++){
         printf("%d. %s \n",i+1, patientName[i]);
       }

       int pick;
       printf("Enter the number of the patient to view :");
       scanf("%d", &pick);

       if (pick <1||pick >patientCount){
       printf("\n That number doesn't match any patient.\n ");
       return;
       }

       int i =pick-1;

       printf("\n----- Patient Details -----\n");
       printf("Name            :%s\n",patientName[i]);
       printf("Age             :%d\n",patientAge[i]);
       printf("Urgency         :%d\n",patientTriageLevel[i]);
       printf("Specialty       :%s\n", specialtyName[patientSpecialty[i]]);
       printf("Diagnosis       :%s\n", patientDiagnosis[i]);
       printf("Condition       :%s\n", patientCondition[i]);


       if (patientAdmitted[i]){
            printf("Ward            :%s(Bed #%02d)\n",wardName[patientWard[i]],patientBedNumber[i]+1);
            printf("Days Admitted   :%d\n", patientDaysAdmitted[i]);
            
       }else {
       printf("Status                : Outpatient(OPD, not admitted)\n");
       }
}

void viewAllPatients (void)
{
    if (patientCount == 0){
        printf("\nNo patients registered yet.\n");
        return;
    }

    printf("\n===== All registered Patients =====");

    for (int i=0;i<patientCount;i++){
        printf("\n----- Patient %d -----\n ",i+1);
        printf("\nName            :%s\n",patientName[i]);
        printf("Age             :%d\n",patientAge[i]);
        printf("Urgency         :%d\n",patientTriageLevel[i]);
        printf("Specialty       :%s\n", specialtyName[patientSpecialty[i]]);
        printf("Diagnosis       :%s\n", patientDiagnosis[i]);
        printf("Condition       :%s\n", patientCondition[i]);

        if (patientAdmitted[i] &&patientBedNumber[i]>=0){
        printf("Ward            :%s (BED #%02d)\n", wardName[patientWard[i]],patientBedNumber[i]+1);
        printf("Days admitted   :%d\n", patientDaysAdmitted[i]);

        }else {
            printf("Status          :Outpatient (OPD)\n");
        }

    }
    printf("\n======================================\n");
}

void showWardStatus (int wardIndex)
{
    printf("\n----- Current Status of %s -----\n", wardName[wardIndex]);

    printf("Beds: ");
    for (int b =0; b <wardBedCapacity[wardIndex];b++){
        printf("%d ", bedOccupancy[wardIndex][b]);

    }
    printf("\n(0=Available , 1=Occupied)\n");

    int found =0;
    printf("\nPatients currently in this ward : \n");
    for (int i=0; i < patientCount ;i++ ){
        if (patientAdmitted[i]&&patientWard[i]== wardIndex){
            printf(" - %s (Bed #%02d)\n", patientName[i],patientBedNumber[i]+1);
            found = 1;
        }
    }
    if (!found){
        printf("  (No patient currently assigned)\n");
    }
    printf("-------------------------------------\n");
}