# CarePulse

**Combining hospital care with real-time monitoring** — a Smart Hospital
Patient & Resource Allocation System.

CSC 1012 – Introduction to Computer Programming (Individual Assignment)
University of Sri Jayewardenepura – Faculty of Applied Sciences

A modular, menu-driven C program that simulates patient intake, bed
allocation, emergency triage sorting, and medical billing, built with
parallel arrays (no structs).

## Project layout

```
CarePulse/
├── include/            Header files (one per module)
│   ├── constants.h      Fixed sizes/limits
│   ├── globals.h        Shared lookup tables & parallel arrays (extern)
│   ├── utils.h           Safe input + currency formatting helpers
│   ├── billing.h         Requirement 3 formulas
│   ├── ward.h            Bed occupancy matrix + lookup tables display
│   ├── patient.h         Registration flow + bill printout
│   ├── sorting.h         Requirement 4 priority queue
│   ├── reports.h         Requirement 6 analytics
│   └── fileio.h          Requirement 7 file persistence
├── src/                 Matching .c files, plus main.c (menu loop)
├── Makefile             Build with `make`
├── .gitignore
└── README.md
```

## How to build and run

**Using the terminal (Linux/macOS/WSL, or MinGW on Windows):**
```
make
./carepulse
```

**Using Code::Blocks:**
1. Create a new empty C project.
2. Add every file in `src/` as a source file, and every file in `include/`
   as a header file.
3. In *Project → Build Options → Search directories → Compiler*, add the
   `include` folder so `#include "globals.h"` etc. resolve correctly.
4. Build and run as usual (F9).

On exit (menu option 6), the program writes `beds_status.txt` so bed
occupancy is remembered the next time you run it. Every completed
registration is also appended to `patient_records.txt` as a permanent
log — delete both files if you want to start completely fresh.

## Design notes

- **No structs** — every patient field lives in its own array in
  `globals.c` (e.g. `patientName[i]`, `patientAge[i]`, ...), all indexed
  by the same patient index `i`, per the assignment's parallel-array
  guidance.
- **Requirement 4 sort** is a *stable* Bubble Sort: it only swaps two
  patients when one's urgency is strictly higher, so patients with the
  same urgency level keep their original registration order — that's
  the "secondary priority" rule satisfied for free.
- **Currency formatting** (`utils.c: formatCurrency`) exists because
  standard C has no built-in thousands-separator support; it manually
  inserts commas so bills print as `56,750.00` like the spec's sample
  output.

## What's still up to you

This scaffold implements every functional requirement, but the
assignment also asks you to:
- Write the **Project Report** in your own words (architecture,
  assumptions, your GitHub URL) — see `docs/Project_Report_Template.md`
  in the outer submission package for a starting structure.
- Push this to your **own GitHub repository** with at least 15
  meaningful commits spread over the project timeline — see
  `docs/GitHub_Instructions.md` for exact commands.
- Read through every function, make sure you understand it, and adjust
  naming/comments/style until it genuinely reflects how *you'd* write
  it. Your module handout is explicit that submitting unedited
  AI-generated code is not allowed — treat this as a working reference
  to learn from and build on, not a final answer to hand in as-is.
