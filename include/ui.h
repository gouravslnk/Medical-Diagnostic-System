#ifndef UI_H
#define UI_H

#include "common.h"

// Function declarations
void initializeColorSupport(void);
void displayWelcomeMessage(void);
void displayMainMenu(void);
void displayPatientMenu(void);
void displayDoctorMenu(void);
void displayMedicineMenu(void);
void displayRemedyMenu(void);
void displayDiagnosisMenu(void);
int getMenuChoice(int minChoice, int maxChoice);
void displayHeader(const char* title);
void displaySeparator(void);
void clearInputBuffer(void);
void displayError(const char* message);
void displaySuccess(const char* message);
void displayInfo(const char* message);
void getPasswordInput(const char* prompt, char* buffer, int maxLength);

#endif // UI_H
