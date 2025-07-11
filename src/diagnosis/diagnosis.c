#include "../include/diagnosis.h"
#include "../include/utils.h"

// Global variables
static Disease diseases[MAX_DISEASES];
static int diseaseCount = 0;

result_t initializeDiseases(void) {
    diseaseCount = 0;
    return loadDiseasesFromFile();
}

result_t diagnosePatient(const char symptoms[][MAX_SYMPTOM_LENGTH], int symptomCount) {
    if (!symptoms || symptomCount <= 0) {
        return RESULT_ERROR;
    }

    printf("\n==================== DIAGNOSIS RESULTS ====================\n");
    
    Disease bestMatch;
    int maxScore = 0;
    bool foundMatch = false;

    for (int i = 0; i < diseaseCount; i++) {
        int score = calculateSymptomMatch(&diseases[i], symptoms, symptomCount);
        
        if (score > 0) {
            foundMatch = true;
            printf("\nPossible Disease: %s\n", diseases[i].name);
            printf("Match Score: %d/%d symptoms\n", score, symptomCount);
            printf("Severity: %s\n", diseases[i].severity);
            printf("Description: %s\n", diseases[i].description);
            
            if (score > maxScore) {
                maxScore = score;
                bestMatch = diseases[i];
            }
            
            printf("All symptoms for %s:\n", diseases[i].name);
            for (int j = 0; j < MAX_SYMPTOMS_PER_DISEASE && strlen(diseases[i].symptoms[j]) > 0; j++) {
                printf("  - %s\n", diseases[i].symptoms[j]);
            }
            printf("----------------------------------------\n");
        }
    }

    if (!foundMatch) {
        printf("No matching diseases found for the given symptoms.\n");
        printf("Please consult a healthcare professional for proper diagnosis.\n");
        return RESULT_NOT_FOUND;
    } else {
        printf("\nBest Match: %s (Score: %d/%d)\n", bestMatch.name, maxScore, symptomCount);
        printf("IMPORTANT: This is only a preliminary assessment.\n");
        printf("Please consult a qualified healthcare professional for proper diagnosis and treatment.\n");
    }
    
    printf("============================================================\n");
    return RESULT_SUCCESS;
}

result_t addDisease(const Disease* disease) {
    if (!disease || diseaseCount >= MAX_DISEASES) {
        return RESULT_ERROR;
    }

    diseases[diseaseCount] = *disease;
    diseaseCount++;
    
    saveDiseasesToFile();
    return RESULT_SUCCESS;
}

result_t displayDiseaseInfo(const char* diseaseName) {
    for (int i = 0; i < diseaseCount; i++) {
        if (stringCompareIgnoreCase(diseases[i].name, diseaseName) == 0) {
            printf("\n==================== DISEASE INFORMATION ====================\n");
            printf("Disease: %s\n", diseases[i].name);
            printf("Severity: %s\n", diseases[i].severity);
            printf("Description: %s\n", diseases[i].description);
            printf("Symptoms:\n");
            
            for (int j = 0; j < MAX_SYMPTOMS_PER_DISEASE && strlen(diseases[i].symptoms[j]) > 0; j++) {
                printf("  %d. %s\n", j + 1, diseases[i].symptoms[j]);
            }
            printf("============================================================\n");
            return RESULT_SUCCESS;
        }
    }
    return RESULT_NOT_FOUND;
}

result_t searchDiseaseBySymptom(const char* symptom) {
    bool found = false;
    printf("\n================ DISEASES WITH SYMPTOM: %s ================\n", symptom);
    
    for (int i = 0; i < diseaseCount; i++) {
        for (int j = 0; j < MAX_SYMPTOMS_PER_DISEASE; j++) {
            if (strlen(diseases[i].symptoms[j]) > 0 && 
                strstr(diseases[i].symptoms[j], symptom) != NULL) {
                printf("Disease: %s (%s)\n", diseases[i].name, diseases[i].severity);
                printf("Description: %s\n", diseases[i].description);
                printf("----------------------------------------\n");
                found = true;
                break;
            }
        }
    }
    
    if (!found) {
        printf("No diseases found with the symptom: %s\n", symptom);
        return RESULT_NOT_FOUND;
    }
    
    return RESULT_SUCCESS;
}

int calculateSymptomMatch(const Disease* disease, const char symptoms[][MAX_SYMPTOM_LENGTH], int symptomCount) {
    int matchCount = 0;
    
    for (int i = 0; i < symptomCount; i++) {
        for (int j = 0; j < MAX_SYMPTOMS_PER_DISEASE; j++) {
            if (strlen(disease->symptoms[j]) > 0 && 
                stringCompareIgnoreCase(symptoms[i], disease->symptoms[j]) == 0) {
                matchCount++;
                break;
            }
        }
    }
    
    return matchCount;
}

result_t loadDiseasesFromFile(void) {
    // Initialize with some default diseases
    diseaseCount = 0;
    
    // Common Cold
    strcpy(diseases[0].name, "Common_Cold");
    strcpy(diseases[0].severity, "Mild");
    strcpy(diseases[0].description, "A viral infection of the upper respiratory tract");
    strcpy(diseases[0].symptoms[0], "Runny_nose");
    strcpy(diseases[0].symptoms[1], "Sneezing");
    strcpy(diseases[0].symptoms[2], "Cough");
    strcpy(diseases[0].symptoms[3], "Sore_throat");
    strcpy(diseases[0].symptoms[4], "Mild_fever");
    
    // Influenza
    strcpy(diseases[1].name, "Influenza");
    strcpy(diseases[1].severity, "Moderate");
    strcpy(diseases[1].description, "A viral infection that attacks the respiratory system");
    strcpy(diseases[1].symptoms[0], "High_fever");
    strcpy(diseases[1].symptoms[1], "Severe_body_aches");
    strcpy(diseases[1].symptoms[2], "Chills");
    strcpy(diseases[1].symptoms[3], "Fatigue");
    strcpy(diseases[1].symptoms[4], "Dry_cough");
    
    // Asthma
    strcpy(diseases[2].name, "Asthma");
    strcpy(diseases[2].severity, "Moderate");
    strcpy(diseases[2].description, "A respiratory condition marked by attacks of spasm in the bronchi");
    strcpy(diseases[2].symptoms[0], "Shortness_of_breath");
    strcpy(diseases[2].symptoms[1], "Wheezing");
    strcpy(diseases[2].symptoms[2], "Chest_tightness");
    strcpy(diseases[2].symptoms[3], "Coughing");
    strcpy(diseases[2].symptoms[4], "Difficulty_sleeping");
    
    // Diabetes
    strcpy(diseases[3].name, "Diabetes");
    strcpy(diseases[3].severity, "Severe");
    strcpy(diseases[3].description, "A group of metabolic disorders characterized by high blood sugar");
    strcpy(diseases[3].symptoms[0], "Increased_thirst");
    strcpy(diseases[3].symptoms[1], "Frequent_urination");
    strcpy(diseases[3].symptoms[2], "Extreme_hunger");
    strcpy(diseases[3].symptoms[3], "Fatigue");
    strcpy(diseases[3].symptoms[4], "Blurry_vision");
    
    // Hypertension
    strcpy(diseases[4].name, "Hypertension");
    strcpy(diseases[4].severity, "Severe");
    strcpy(diseases[4].description, "High blood pressure that can lead to serious health problems");
    strcpy(diseases[4].symptoms[0], "Severe_headache");
    strcpy(diseases[4].symptoms[1], "Fatigue");
    strcpy(diseases[4].symptoms[2], "Vision_problems");
    strcpy(diseases[4].symptoms[3], "Chest_pain");
    strcpy(diseases[4].symptoms[4], "Difficulty_breathing");
    
    diseaseCount = 5;
    return RESULT_SUCCESS;
}

result_t saveDiseasesToFile(void) {
    FILE* file = fopen("data/diseases.txt", "w");
    if (!file) {
        return RESULT_ERROR;
    }

    for (int i = 0; i < diseaseCount; i++) {
        fprintf(file, "%s|%s|%s|", diseases[i].name, diseases[i].severity, diseases[i].description);
        for (int j = 0; j < MAX_SYMPTOMS_PER_DISEASE; j++) {
            fprintf(file, "%s", diseases[i].symptoms[j]);
            if (j < MAX_SYMPTOMS_PER_DISEASE - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return RESULT_SUCCESS;
}
