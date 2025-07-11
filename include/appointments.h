#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include "common.h"

// Doctor structure
typedef struct {
    int id;
    char name[MAX_DOCTOR_NAME_LENGTH];
    char specialty[MAX_SPECIALTY_LENGTH];
    char availability[7][20]; // Days of week availability
    float consultationFee;
    int yearsOfExperience;
} Doctor;

// Appointment structure
typedef struct {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[20];
    char time[10];
    char status[20]; // Scheduled, Completed, Cancelled
    char notes[200];
} Appointment;

// Function declarations
result_t initializeDoctors(void);
result_t initializeAppointments(void);
result_t bookAppointment(int patientId, int doctorId, const char* date, const char* time);
result_t cancelAppointment(int appointmentId);
result_t displayDoctors(void);
result_t displayAppointments(int patientId);
result_t updateAppointmentStatus(int appointmentId, const char* status);
Doctor* findDoctorById(int doctorId);
Appointment* findAppointmentById(int appointmentId);
result_t displayDoctorsBySpecialty(const char* specialty);
result_t saveAppointmentsToFile(void);
result_t loadAppointmentsFromFile(void);
result_t generateAppointmentReport(void);

#endif // APPOINTMENTS_H
