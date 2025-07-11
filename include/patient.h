#ifndef PATIENT_H
#define PATIENT_H

#include "common.h"

// Patient structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float weight;
    char gender;
    char phone[MAX_PHONE_LENGTH];
    char bloodGroup[MAX_BLOOD_GROUP_LENGTH];
    char medicalHistory[500];
    time_t registrationDate;
} Patient;

// Function declarations
result_t initializePatients(void);
result_t registerPatient(Patient* patient);
result_t displayPatient(int patientId);
result_t updatePatient(int patientId, Patient* updatedData);
result_t deletePatient(int patientId);
Patient* findPatientById(int patientId);
result_t savePatientToFile(const Patient* patient);
result_t loadPatientsFromFile(void);
int getNextPatientId(void);
result_t displayAllPatients(void);
result_t searchPatientByName(const char* name);
result_t validatePatientData(const Patient* patient);

#endif // PATIENT_H
