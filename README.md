# CarePulse

Smart Hospital Patient & Resource Allocation System  
CSC 1012 – Introduction to Computer Programming (Individual Assignment)  
University of Sri Jayewardenepura – Faculty of Applied Sciences

Simple menu-driven C program that handles patient registration, bed allocation, triage sorting and billing. Everything is done with parallel arrays (no structs) as required.

## Files

```
CarePulse/
├── main.c          all the code lives here
├── Makefile
├── .gitignore
└── README.md
```

Single file for now. No headers, no fancy folder structure.

## What the program does

- `initializeBedOccupancy` – sets the 4x20 bed matrix to empty
- `displaySpecialties`, `displayWards`, `displayBedStatus` – show the lookup tables
- `findFreeBed` – looks for the first free bed in a ward
- `registerPatient` – takes name, age, triage level, specialty, ward and days
- `calculateWaitTime`, `calculateSurcharge`, `calculateWardCost` – the three cost formulas
- `generateBill` – prints the bill for one patient
- `sortPatientsByPriority` – bubble sort (Critical → Urgent → Normal), keeps registration order for same priority
- `viewPatientInformation`, `viewAllPatients`, `showWardStatus` – basic lookup screens
- `displayReports` – shows urgency counts, total revenue, discounts, bed occupancy %, highest paying patient

## How to run

Terminal (Linux / mac / WSL / MinGW):
```
make
./carepulse
```

Code::Blocks (for the final zip submission):
1. New empty C project
2. Add main.c
3. Build & run (F9)

## Notes

- Parallel arrays only – every field is its own array indexed by the same patient number.
- The sort is stable. It only swaps when one patient has strictly higher urgency, so same-priority patients stay in the order they were registered.
- Requirement 7 (saving beds_status.txt and patient_records.txt) is still missing.
- Money prints as 56750.00 instead of 56,750.00 because printf doesn’t do thousand separators by itself. Would need a small helper if the sample output has to match exactly.

## Still left to do

- Write the project report in your own words (architecture, assumptions, GitHub link).
- Push to your own GitHub repo with at least 15 proper commits over time.
- Decide if you want to try the file-handling bonus.
- Make sure you actually understand every function – the handout is clear that pure AI code isn’t allowed.
