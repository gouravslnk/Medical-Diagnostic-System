#include "../include/patient.h"
#include "../include/utils.h"

// Global variables
static Patient patients[MAX_PATIENTS];
static int patientCount = 0;

result_t initializePatients(void) {
    patientCount = 0;
    return loadPatientsFromFile();
}

result_t registerPatient(Patient* patient) {
    if (!patient || patientCount >= MAX_PATIENTS) {
        return RESULT_ERROR;
    }

    if (validatePatientData(patient) != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }

    patient->id = getNextPatientId();
    patient->registrationDate = time(NULL);
    
    patients[patientCount] = *patient;
    patientCount++;

    savePatientToFile(patient);
    logActivity("New patient registered");
    
    return RESULT_SUCCESS;
}

result_t displayPatient(int patientId) {
    Patient* patient = findPatientById(patientId);
    if (!patient) {
        return RESULT_NOT_FOUND;
    }

    printf("\n==================== PATIENT DETAILS ====================\n");
    printf("ID: %d\n", patient->id);
    printf("Name: %s\n", patient->name);
    printf("Age: %d years\n", patient->age);
    printf("Weight: %.2f kg\n", patient->weight);
    printf("Gender: %c\n", patient->gender);
    printf("Phone: %s\n", patient->phone);
    printf("Blood Group: %s\n", patient->bloodGroup);
    printf("Medical History: %s\n", patient->medicalHistory);
    
    char dateStr[50];
    struct tm* tm_info = localtime(&patient->registrationDate);
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Registration Date: %s\n", dateStr);
    printf("=========================================================\n");

    return RESULT_SUCCESS;
}

result_t updatePatient(int patientId, Patient* updatedData) {
    Patient* patient = findPatientById(patientId);
    if (!patient || !updatedData) {
        return RESULT_NOT_FOUND;
    }

    if (validatePatientData(updatedData) != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }

    // Keep original ID and registration date
    int originalId = patient->id;
    time_t originalRegDate = patient->registrationDate;
    
    *patient = *updatedData;
    patient->id = originalId;
    patient->registrationDate = originalRegDate;

    savePatientToFile(patient);
    logActivity("Patient data updated");
    
    return RESULT_SUCCESS;
}

result_t deletePatient(int patientId) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            // Shift remaining patients
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            logActivity("Patient deleted");
            return RESULT_SUCCESS;
        }
    }
    return RESULT_NOT_FOUND;
}

Patient* findPatientById(int patientId) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            return &patients[i];
        }
    }
    return NULL;
}

result_t savePatientToFile(const Patient* patient) {
    FILE* file = fopen("data/patients.txt", "a");
    if (!file) {
        return RESULT_ERROR;
    }

    fprintf(file, "%d|%s|%d|%.2f|%c|%s|%s|%s|%lld\n",
            patient->id, patient->name, patient->age, patient->weight,
            patient->gender, patient->phone, patient->bloodGroup,
            patient->medicalHistory, (long long)patient->registrationDate);

    fclose(file);
    return RESULT_SUCCESS;
}

result_t loadPatientsFromFile(void) {
    FILE* file = fopen("data/patients.txt", "r");
    if (!file) {
        return RESULT_SUCCESS; // File doesn't exist yet, that's OK
    }

    char line[1000];
    patientCount = 0;

    while (fgets(line, sizeof(line), file) && patientCount < MAX_PATIENTS) {
        Patient patient;
        long long tempTime;
        if (sscanf(line, "%d|%99[^|]|%d|%f|%c|%19[^|]|%9[^|]|%499[^|]|%lld",
                   &patient.id, patient.name, &patient.age, &patient.weight,
                   &patient.gender, patient.phone, patient.bloodGroup,
                   patient.medicalHistory, &tempTime) == 9) {
            patient.registrationDate = (time_t)tempTime;
            patients[patientCount++] = patient;
        }
    }

    fclose(file);
    return RESULT_SUCCESS;
}

int getNextPatientId(void) {
    int maxId = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id > maxId) {
            maxId = patients[i].id;
        }
    }
    return maxId + 1;
}

result_t displayAllPatients(void) {
    if (patientCount == 0) {
        printf("No patients registered.\n");
        return RESULT_NOT_FOUND;
    }

    printf("\n================ ALL REGISTERED PATIENTS ================\n");
    printf("%-5s %-20s %-5s %-8s %-8s %-15s %-10s\n", 
           "ID", "Name", "Age", "Weight", "Gender", "Phone", "Blood Group");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++) {
        printf("%-5d %-20s %-5d %-8.2f %-8c %-15s %-10s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].weight, patients[i].gender, patients[i].phone,
               patients[i].bloodGroup);
    }
    printf("=========================================================\n");

    return RESULT_SUCCESS;
}

result_t searchPatientByName(const char* name) {
    bool found = false;
    printf("\n================ SEARCH RESULTS ================\n");

    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].name, name) != NULL) {
            printf("ID: %d, Name: %s, Age: %d, Phone: %s\n",
                   patients[i].id, patients[i].name, patients[i].age, patients[i].phone);
            found = true;
        }
    }

    if (!found) {
        printf("No patients found with name containing '%s'\n", name);
        return RESULT_NOT_FOUND;
    }

    return RESULT_SUCCESS;
}

result_t validatePatientData(const Patient* patient) {
    if (!patient || strlen(patient->name) == 0 || patient->age <= 0 || 
        patient->age > 120 || patient->weight <= 0 || patient->weight > 500) {
        return RESULT_ERROR;
    }

    if (patient->gender != 'M' && patient->gender != 'F' && 
        patient->gender != 'm' && patient->gender != 'f') {
        return RESULT_ERROR;
    }

    if (validatePhone(patient->phone) != RESULT_SUCCESS ||
        validateBloodGroup(patient->bloodGroup) != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }

    return RESULT_SUCCESS;
}
