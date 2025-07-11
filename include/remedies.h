#ifndef REMEDIES_H
#define REMEDIES_H

#include "common.h"

// Home remedy structure
typedef struct {
    int id;
    char name[MAX_REMEDY_LENGTH];
    char indication[MAX_REMEDY_LENGTH];
    char instructions[300];
    char ingredients[200];
    char precautions[200];
} HomeRemedy;

// Function declarations
result_t initializeRemedies(void);
result_t searchRemedyByIndication(const char* indication);
result_t displayAllRemedies(void);
result_t displayRemedyDetails(int remedyId);
result_t addRemedy(const HomeRemedy* remedy);
HomeRemedy* findRemedyById(int remedyId);
result_t saveRemediesToFile(void);
result_t loadRemediesFromFile(void);

#endif // REMEDIES_H
