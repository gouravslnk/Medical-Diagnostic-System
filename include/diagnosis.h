#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "common.h"

// Disease structure
typedef struct {
    char name[MAX_DISEASE_LENGTH];
    char symptoms[MAX_SYMPTOMS_PER_DISEASE][MAX_SYMPTOM_LENGTH];
    char description[200];
    char severity[20]; // Mild, Moderate, Severe
} Disease;

// Function declarations
result_t initializeDiseases(void);
result_t diagnosePatient(const char symptoms[][MAX_SYMPTOM_LENGTH], int symptomCount);
result_t addDisease(const Disease* disease);
result_t displayDiseaseInfo(const char* diseaseName);
result_t searchDiseaseBySymptom(const char* symptom);
int calculateSymptomMatch(const Disease* disease, const char symptoms[][MAX_SYMPTOM_LENGTH], int symptomCount);
result_t loadDiseasesFromFile(void);
result_t saveDiseasesToFile(void);

#endif // DIAGNOSIS_H
