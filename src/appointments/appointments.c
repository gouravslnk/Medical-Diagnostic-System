#include "../include/appointments.h"
#include "../include/utils.h"

// Global variables
static Doctor doctors[MAX_DOCTORS];
static Appointment appointments[MAX_PATIENTS * 10]; // Multiple appointments per patient
static int doctorCount = 0;
static int appointmentCount = 0;

result_t initializeDoctors(void) {
    doctorCount = 0;
    
    // Initialize some default doctors
    strcpy(doctors[0].name, "Dr. Smith");
    strcpy(doctors[0].specialty, "Cardiologist");
    doctors[0].id = 1;
    doctors[0].consultationFee = 500.0;
    doctors[0].yearsOfExperience = 15;
    strcpy(doctors[0].availability[0], "Mon: 9-17");
    strcpy(doctors[0].availability[1], "Wed: 9-17");
    strcpy(doctors[0].availability[2], "Fri: 9-17");
    
    strcpy(doctors[1].name, "Dr. Johnson");
    strcpy(doctors[1].specialty, "Pediatrician");
    doctors[1].id = 2;
    doctors[1].consultationFee = 400.0;
    doctors[1].yearsOfExperience = 12;
    strcpy(doctors[1].availability[0], "Tue: 10-18");
    strcpy(doctors[1].availability[1], "Thu: 10-18");
    strcpy(doctors[1].availability[2], "Sat: 9-15");
    
    strcpy(doctors[2].name, "Dr. Lee");
    strcpy(doctors[2].specialty, "Dermatologist");
    doctors[2].id = 3;
    doctors[2].consultationFee = 450.0;
    doctors[2].yearsOfExperience = 8;
    strcpy(doctors[2].availability[0], "Mon: 11-19");
    strcpy(doctors[2].availability[1], "Wed: 11-19");
    strcpy(doctors[2].availability[2], "Fri: 11-19");
    
    strcpy(doctors[3].name, "Dr. Brown");
    strcpy(doctors[3].specialty, "Ophthalmologist");
    doctors[3].id = 4;
    doctors[3].consultationFee = 550.0;
    doctors[3].yearsOfExperience = 20;
    strcpy(doctors[3].availability[0], "Tue: 8-16");
    strcpy(doctors[3].availability[1], "Thu: 8-16");
    strcpy(doctors[3].availability[2], "Sat: 8-14");
    
    strcpy(doctors[4].name, "Dr. Garcia");
    strcpy(doctors[4].specialty, "Neurologist");
    doctors[4].id = 5;
    doctors[4].consultationFee = 600.0;
    doctors[4].yearsOfExperience = 18;
    strcpy(doctors[4].availability[0], "Mon: 9-17");
    strcpy(doctors[4].availability[1], "Tue: 9-17");
    strcpy(doctors[4].availability[2], "Thu: 9-17");
    
    doctorCount = 5;
    return RESULT_SUCCESS;
}

result_t initializeAppointments(void) {
    appointmentCount = 0;
    return loadAppointmentsFromFile();
}

result_t bookAppointment(int patientId, int doctorId, const char* date, const char* time) {
    if (!date || !time || appointmentCount >= MAX_PATIENTS * 10) {
        return RESULT_ERROR;
    }

    Doctor* doctor = findDoctorById(doctorId);
    if (!doctor) {
        return RESULT_NOT_FOUND;
    }

    // Generate new appointment ID
    int newId = 1;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].appointmentId >= newId) {
            newId = appointments[i].appointmentId + 1;
        }
    }

    appointments[appointmentCount].appointmentId = newId;
    appointments[appointmentCount].patientId = patientId;
    appointments[appointmentCount].doctorId = doctorId;
    strcpy(appointments[appointmentCount].date, date);
    strcpy(appointments[appointmentCount].time, time);
    strcpy(appointments[appointmentCount].status, "Scheduled");
    strcpy(appointments[appointmentCount].notes, "");

    appointmentCount++;
    saveAppointmentsToFile();
    logActivity("New appointment booked");

    printf("\n==================== APPOINTMENT CONFIRMED ====================\n");
    printf("Appointment ID: %d\n", newId);
    printf("Doctor: %s (%s)\n", doctor->name, doctor->specialty);
    printf("Date: %s\n", date);
    printf("Time: %s\n", time);
    printf("Consultation Fee: $%.2f\n", doctor->consultationFee);
    printf("Status: Scheduled\n");
    printf("============================================================\n");

    return RESULT_SUCCESS;
}

result_t cancelAppointment(int appointmentId) {
    Appointment* appointment = findAppointmentById(appointmentId);
    if (!appointment) {
        return RESULT_NOT_FOUND;
    }

    strcpy(appointment->status, "Cancelled");
    saveAppointmentsToFile();
    logActivity("Appointment cancelled");

    return RESULT_SUCCESS;
}

result_t displayDoctors(void) {
    if (doctorCount == 0) {
        printf("No doctors available.\n");
        return RESULT_NOT_FOUND;
    }

    printf("\n==================== AVAILABLE DOCTORS ====================\n");
    printf("%-5s %-25s %-20s %-10s %-10s\n", "ID", "Name", "Specialty", "Fee ($)", "Experience");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < doctorCount; i++) {
        printf("%-5d %-25s %-20s %-10.2f %-10d\n",
               doctors[i].id, doctors[i].name, doctors[i].specialty,
               doctors[i].consultationFee, doctors[i].yearsOfExperience);
        
        printf("      Availability: ");
        for (int j = 0; j < 7 && strlen(doctors[i].availability[j]) > 0; j++) {
            printf("%s ", doctors[i].availability[j]);
        }
        printf("\n\n");
    }
    printf("============================================================\n");

    return RESULT_SUCCESS;
}

result_t displayAppointments(int patientId) {
    bool found = false;
    printf("\n================ APPOINTMENTS FOR PATIENT %d ================\n", patientId);
    printf("%-10s %-25s %-15s %-10s %-15s\n", "App ID", "Doctor", "Date", "Time", "Status");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientId == patientId) {
            Doctor* doctor = findDoctorById(appointments[i].doctorId);
            printf("%-10d %-25s %-15s %-10s %-15s\n",
                   appointments[i].appointmentId,
                   doctor ? doctor->name : "Unknown",
                   appointments[i].date,
                   appointments[i].time,
                   appointments[i].status);
            found = true;
        }
    }

    if (!found) {
        printf("No appointments found for patient %d\n", patientId);
        return RESULT_NOT_FOUND;
    }

    printf("============================================================\n");
    return RESULT_SUCCESS;
}

result_t updateAppointmentStatus(int appointmentId, const char* status) {
    Appointment* appointment = findAppointmentById(appointmentId);
    if (!appointment || !status) {
        return RESULT_NOT_FOUND;
    }

    strcpy(appointment->status, status);
    saveAppointmentsToFile();
    logActivity("Appointment status updated");

    return RESULT_SUCCESS;
}

Doctor* findDoctorById(int doctorId) {
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == doctorId) {
            return &doctors[i];
        }
    }
    return NULL;
}

Appointment* findAppointmentById(int appointmentId) {
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].appointmentId == appointmentId) {
            return &appointments[i];
        }
    }
    return NULL;
}

result_t displayDoctorsBySpecialty(const char* specialty) {
    bool found = false;
    printf("\n================ DOCTORS - SPECIALTY: %s ================\n", specialty);

    for (int i = 0; i < doctorCount; i++) {
        if (stringCompareIgnoreCase(doctors[i].specialty, specialty) == 0) {
            printf("ID: %d, Name: %s, Fee: $%.2f, Experience: %d years\n",
                   doctors[i].id, doctors[i].name, doctors[i].consultationFee,
                   doctors[i].yearsOfExperience);
            found = true;
        }
    }

    if (!found) {
        printf("No doctors found for specialty: %s\n", specialty);
        return RESULT_NOT_FOUND;
    }

    return RESULT_SUCCESS;
}

result_t saveAppointmentsToFile(void) {
    FILE* file = fopen("data/appointments.txt", "w");
    if (!file) {
        return RESULT_ERROR;
    }

    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%d|%d|%d|%s|%s|%s|%s\n",
                appointments[i].appointmentId, appointments[i].patientId,
                appointments[i].doctorId, appointments[i].date,
                appointments[i].time, appointments[i].status,
                appointments[i].notes);
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t loadAppointmentsFromFile(void) {
    FILE* file = fopen("data/appointments.txt", "r");
    if (!file) {
        return RESULT_SUCCESS; // File doesn't exist yet
    }

    char line[500];
    appointmentCount = 0;

    while (fgets(line, sizeof(line), file) && appointmentCount < MAX_PATIENTS * 10) {
        Appointment appointment;
        if (sscanf(line, "%d|%d|%d|%19[^|]|%9[^|]|%19[^|]|%199[^\n]",
                   &appointment.appointmentId, &appointment.patientId,
                   &appointment.doctorId, appointment.date,
                   appointment.time, appointment.status,
                   appointment.notes) >= 6) {
            appointments[appointmentCount++] = appointment;
        }
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t generateAppointmentReport(void) {
    printf("\n==================== APPOINTMENT REPORT ====================\n");
    printf("Total Appointments: %d\n", appointmentCount);
    
    int scheduled = 0, completed = 0, cancelled = 0;
    
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].status, "Scheduled") == 0) scheduled++;
        else if (strcmp(appointments[i].status, "Completed") == 0) completed++;
        else if (strcmp(appointments[i].status, "Cancelled") == 0) cancelled++;
    }
    
    printf("Scheduled: %d\n", scheduled);
    printf("Completed: %d\n", completed);
    printf("Cancelled: %d\n", cancelled);
    printf("============================================================\n");
    
    return RESULT_SUCCESS;
}
