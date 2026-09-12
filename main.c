#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_SPECIALITIES 4
#define MAX_BEDS         20
#define MAX_PATIENTS     100
#define NUM_WORDS        4
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
            case 5: viewPatientInformation(); break;
            case 6: printf("\n(Priority sorting comes later - Requirement 4)\n"); break;
            case 7: printf("\n(Needs saved records to work across runs - Requirement 7)\n"); break;
            case 8: printf("\n(Reports come later - Requirement 6)\n"); break;
            case 0: printf("\nExiting. Goodbye!\n"); break;
            default: printf("\nInvalid choice, try again.\n");
        }
    }while (choice !=0);

    return 0;
} 