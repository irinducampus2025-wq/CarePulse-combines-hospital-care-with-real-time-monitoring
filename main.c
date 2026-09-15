#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_SPECIALITIES 4
#define MAX_BEDS         20
#define MAX_PATIENTS     100
#define NUM_WARDS        4

double calculateWaitTime(int specialtyIndex);
double calculateSurcharge(int triageLevel, double fee);
double calculateWardCost(int daysAdmitted,int wardIndex);
void generateBill(int patientIndex);

int main (void)
{

    int choice;

    do {

        printf("\n =========================================================================\n");
        printf("                   SMART HOSPITAL & RESOURCES ALLOCATION SYSTEM\n   ");
        printf("===========================================================================\n");
        printf(" 1.View Doctor Specialities\n");
        printf(" 2.View ward informations\n");
        printf(" 3.View bed occupancy\n");
        printf(" 4.Register new patient      [ Not Build yet ]\n");
        printf(" 5.View patient by priority  [Not Build Yet]\n");
        printf(" 6.View patient informations [Not Build Yet ]\n");
        printf(" 7.View patient history      [Not Build Yet - Need requrement 7 ]\n ");
        printf(" 8.View performance report   [Not Build yet]\n");
        printf(" 0.Exit\n");
        printf("\n===========================================================================\n");
        printf("Enter Your choice :");
        scanf("%d", &choice);


        switch (choice) {
            case 1: displaySpecialties(); break;
            case 2: displayWards(); break;
            case 3: displayBedStatus(); break;
            case 4: registerPatient(); break;
            case 5: viewPatientByPriority(); break;
            case 6:sortPatientsByPriority(); break;
            case 7: printf("\n(Needs saved records to work across runs - Requirement 7)\n"); break;
            case 8: printf("\n(Reports come later - Requirement 6)\n"); break;
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
   printf("     patient ID    : PAT - %04d\n", 1001 + i);
   printf("     patient Name  : %s\n", patientName[i]);
   printf("     patient Age   : %d Years\n", patientAge[i]);
   if (discount > 0)
         printf("   (15%% Subsidy Eligible)\n");
   
   printf("Specialty          : %s\n", specialtyName[patientSpecialty[i]]);

   if (patientAdmitted[i]&& patientBedNumber[i]>=0){
    printf("Assigned Ward     : %s (Bed #%02d)\n",
           wardName[patientWard[i]], patientBedNumber[i]+1);
    }
   else {
    printf("Assigned Ward     : Not Admitted(OPD)\n");
   }
   
   printf("Urgency Level      : Level %d  ", patientTriageLevel[i]);
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
   printf("Base Consultation Fee   : LKR %10.2f\n", base);
   printf("Emergency Surcharge     : LKR %10.2f", surcharge);
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
    printf(" Ward Stay cost (%d Days) : LKR %10.2f\n" , patientDaysAdmitted[i], wardCost);
   }
   else{
    printf(" Ward Stay Cost           : LKR %10.2f\n", wardCost);
   }

   printf("==========================================================\n");
   printf("Gross Total Bill            : LKR %10.2f\n", gross);
   printf("Age Subsidy Discount       : LKR %10.2f\n", -discount);
   if (discount > 0)
    printf(" (15%%)");
    printf("\n");


    printf("==========================================================\n");
    printf("Final Payable Amount      : LKR %10.2f\n", finalAmount);

    if (waitTime <=0.01){
     printf("Estimated waiting Time   : 0.00 mins(immediate Attention)\n");
    }
    else {
      printf("Estimated Waiting Time  :%.2f mins\n", waitTime);
    }

    printf("==========================================================\n");
   }

}

void sortPatientsByPriority(void)
{
    if (patientCount <=1){
        printf("\nNot enough patients to sort. \n");
        return;
    }
     //Boubble sort - only swap when urgency is higher
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
