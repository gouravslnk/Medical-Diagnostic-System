#include "include/common.h"
#include "include/auth.h"
#include "include/patient.h"
#include "include/diagnosis.h"
#include "include/appointments.h"
#include "include/medicines.h"
#include "include/remedies.h"
#include "include/ui.h"
#include "include/utils.h"

// Function prototypes
void handlePatientManagement(void);
void handleDiagnosisSystem(void);
void handleAppointments(void);
void handleMedicineOrders(void);
void handleHomeRemedies(void);
void handleReportsAnalytics(void);
void handleSystemSettings(void);
void handlePharmacyManagement(void); // New pharmacy admin panel
void handleUserManagement(void); // New user management
void handleAccountSettings(void); // New account settings
result_t initializeSystem(void);
void cleanupSystem(void);

// Global variables
static bool systemInitialized = false;

int main(void) {
    // Initialize color support for Windows
    initializeColorSupport();
    
    // Initialize system
    if (initializeSystem() != RESULT_SUCCESS) {
        displayError("Failed to initialize system. Exiting...");
        return EXIT_FAILURE;
    }

    // Initialize authentication system
    if (initializeAuth() != RESULT_SUCCESS) {
        displayError("Failed to initialize authentication system. Exiting...");
        return EXIT_FAILURE;
    }

    displayWelcomeMessage();
    displayInfo("System initialized successfully!");
    
    // Handle authentication first
    if (handleAuthentication() != RESULT_SUCCESS) {
        displayError("Authentication failed. Exiting...");
        return EXIT_FAILURE;
    }
    
    int choice;
    bool running = true;

    while (running && isUserLoggedIn()) {
        // Display session info
        displaySessionInfo();
        
        displayMainMenu();
        choice = getMenuChoice(0, 9);

        switch (choice) {
            case 1:
                if (hasPermission(ROLE_PATIENT)) {
                    handlePatientManagement();
                } else {
                    displayError("Access denied. Patient or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 2:
                if (hasPermission(ROLE_PATIENT)) {
                    handleDiagnosisSystem();
                } else {
                    displayError("Access denied. Patient or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 3:
                if (hasPermission(ROLE_PATIENT)) {
                    handleAppointments();
                } else {
                    displayError("Access denied. Patient or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 4:
                if (hasPermission(ROLE_PATIENT)) {
                    handleMedicineOrders();
                } else {
                    displayError("Access denied. Patient or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 5:
                if (hasPermission(ROLE_PATIENT)) {
                    handleHomeRemedies();
                } else {
                    displayError("Access denied. Patient or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 6:
                if (hasPermission(ROLE_DOCTOR)) {
                    handleReportsAnalytics();
                } else {
                    displayError("Access denied. Doctor or higher privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 7:
                if (hasPermission(ROLE_ADMIN)) {
                    handleSystemSettings();
                } else {
                    displayError("Access denied. Admin privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 8:
                if (hasPermission(ROLE_PHARMACY)) {
                    handlePharmacyManagement(); // Handle pharmacy management
                } else {
                    displayError("Access denied. Pharmacy or Admin privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 9:
                if (hasPermission(ROLE_ADMIN)) {
                    handleUserManagement(); // Handle user management
                } else {
                    displayError("Access denied. Admin privileges required!");
                    pressEnterToContinue();
                }
                break;
            case 0:
                CLEAR_AND_HOME();
                printf("\n");
                printf(COLOR_BRIGHT_GREEN "Thank you for using Medical Diagnostic System!\n" COLOR_RESET);
                printf(COLOR_BRIGHT_YELLOW "Stay healthy and take care!\n" COLOR_RESET);
                printf("\n");
                logoutUser();
                running = false;
                break;
            default:
                displayError("Invalid choice. Please try again.");
                break;
        }
        
        // Check if session is still valid
        if (!isSessionValid() && running) {
            displayError("Session expired. Please login again.");
            logoutUser();
            running = false;
        }
    }

    cleanupSystem();
    return EXIT_SUCCESS;
}

result_t initializeSystem(void) {
    logActivity("System startup initiated");
    
    // Create necessary directories
    createDataDirectories();
    
    // Initialize all modules
    if (initializePatients() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeDiseases() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeDoctors() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeAppointments() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeMedicines() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeOrders() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    if (initializeRemedies() != RESULT_SUCCESS) {
        return RESULT_ERROR;
    }
    
    systemInitialized = true;
    logActivity("System initialized successfully");
    return RESULT_SUCCESS;
}

void cleanupSystem(void) {
    if (systemInitialized) {
        logActivity("System shutdown");
        // Perform any necessary cleanup
        systemInitialized = false;
    }
}

void handlePatientManagement(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayPatientMenu();
        choice = getMenuChoice(0, 6);

        switch (choice) {
            case 1: {
                // Register New Patient
                displayHeader("REGISTER NEW PATIENT");
                Patient newPatient = {0};
                
                printf("Enter patient details:\n");
                getStringInput("Name: ", newPatient.name, MAX_NAME_LENGTH);
                newPatient.age = getIntInput("Age: ");
                newPatient.weight = getFloatInput("Weight (kg): ");
                newPatient.gender = getCharInput("Gender (M/F): ");
                getStringInput("Phone: ", newPatient.phone, MAX_PHONE_LENGTH);
                getStringInput("Blood Group: ", newPatient.bloodGroup, MAX_BLOOD_GROUP_LENGTH);
                getStringInput("Medical History (optional): ", newPatient.medicalHistory, 500);
                
                if (registerPatient(&newPatient) == RESULT_SUCCESS) {
                    displaySuccess("Patient registered successfully!");
                    printf("Patient ID: %d\n", newPatient.id);
                } else {
                    displayError("Failed to register patient. Please check the entered data.");
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                // View Patient Details
                displayHeader("VIEW PATIENT DETAILS");
                int patientId;
                patientId = getIntInput("Enter Patient ID: ");
                
                if (displayPatient(patientId) != RESULT_SUCCESS) {
                    displayError("Patient not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // Update Patient Information
                displayHeader("UPDATE PATIENT INFORMATION");
                int patientId;
                patientId = getIntInput("Enter Patient ID to update: ");
                
                Patient* existingPatient = findPatientById(patientId);
                if (existingPatient) {
                    Patient updatedPatient = *existingPatient;
                    
                    printf("Current information (press Enter to keep current value):\n");
                    char tempBuffer[500];
                    
                    printf("Current Name: %s\n", updatedPatient.name);
                    getStringInput("New Name: ", tempBuffer, MAX_NAME_LENGTH);
                    if (strlen(tempBuffer) > 0) strcpy(updatedPatient.name, tempBuffer);
                    
                    printf("Current Age: %d\n", updatedPatient.age);
                    int tempAge;
                    tempAge = getIntInput("New Age: ");
                    if (tempAge > 0) {
                        updatedPatient.age = tempAge;
                    }
                    
                    if (updatePatient(patientId, &updatedPatient) == RESULT_SUCCESS) {
                        displaySuccess("Patient information updated successfully!");
                    } else {
                        displayError("Failed to update patient information.");
                    }
                } else {
                    displayError("Patient not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                // Search Patients
                displayHeader("SEARCH PATIENTS");
                char searchName[MAX_NAME_LENGTH];
                getStringInput("Enter name to search: ", searchName, MAX_NAME_LENGTH);
                
                if (searchPatientByName(searchName) != RESULT_SUCCESS) {
                    displayError("No patients found with that name.");
                }
                pressEnterToContinue();
                break;
            }
            case 5: {
                // List All Patients
                displayHeader("ALL REGISTERED PATIENTS");
                if (displayAllPatients() != RESULT_SUCCESS) {
                    displayInfo("No patients registered yet.");
                }
                pressEnterToContinue();
                break;
            }
            case 6: {
                // Delete Patient Record
                displayHeader("DELETE PATIENT RECORD");
                int patientId;
                patientId = getIntInput("Enter Patient ID to delete: ");
                
                if (findPatientById(patientId)) {
                    char confirm;
                    confirm = getCharInput("Are you sure? This action cannot be undone (y/N): ");
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        if (deletePatient(patientId) == RESULT_SUCCESS) {
                            displaySuccess("Patient record deleted successfully!");
                        } else {
                            displayError("Failed to delete patient record.");
                        }
                    } else {
                        displayInfo("Operation cancelled.");
                    }
                } else {
                    displayError("Patient not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleDiagnosisSystem(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayDiagnosisMenu();
        choice = getMenuChoice(0, 3);

        switch (choice) {
            case 1: {
                // Symptom-Based Diagnosis
                displayHeader("SYMPTOM-BASED DIAGNOSIS");
                char symptoms[5][MAX_SYMPTOM_LENGTH];
                int symptomCount = 0;
                
                printf("Enter up to 5 symptoms (enter 'done' to finish):\n");
                
                for (int i = 0; i < 5; i++) {
                    char symptom[MAX_SYMPTOM_LENGTH];
                    printf("Symptom %d: ", i + 1);
                    getStringInput("", symptom, MAX_SYMPTOM_LENGTH);
                    
                    if (strcmp(symptom, "done") == 0 || strlen(symptom) == 0) {
                        break;
                    }
                    
                    strcpy(symptoms[i], symptom);
                    symptomCount++;
                }
                
                if (symptomCount > 0) {
                    diagnosePatient((const char (*)[MAX_SYMPTOM_LENGTH])symptoms, symptomCount);
                } else {
                    displayError("No symptoms entered.");
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                // Search Disease Information
                displayHeader("DISEASE INFORMATION");
                char diseaseName[MAX_DISEASE_LENGTH];
                getStringInput("Enter disease name: ", diseaseName, MAX_DISEASE_LENGTH);
                
                if (displayDiseaseInfo(diseaseName) != RESULT_SUCCESS) {
                    displayError("Disease not found in database.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // Search by Single Symptom
                displayHeader("SEARCH BY SYMPTOM");
                char symptom[MAX_SYMPTOM_LENGTH];
                getStringInput("Enter symptom: ", symptom, MAX_SYMPTOM_LENGTH);
                
                if (searchDiseaseBySymptom(symptom) != RESULT_SUCCESS) {
                    displayError("No diseases found with that symptom.");
                }
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleAppointments(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayDoctorMenu();
        choice = getMenuChoice(0, 6);

        switch (choice) {
            case 1: {
                // View Available Doctors
                displayHeader("AVAILABLE DOCTORS");
                displayDoctors();
                pressEnterToContinue();
                break;
            }
            case 2: {
                // Book Appointment
                displayHeader("BOOK APPOINTMENT");
                int patientId, doctorId;
                char date[20], time[10];
                
                patientId = getIntInput("Enter your Patient ID: ");
                
                if (findPatientById(patientId)) {
                    displayDoctors();
                    doctorId = getIntInput("Select Doctor ID: ");
                    getStringInput("Enter appointment date (YYYY-MM-DD): ", date, 20);
                    getStringInput("Enter preferred time (HH:MM): ", time, 10);
                    
                    if (bookAppointment(patientId, doctorId, date, time) == RESULT_SUCCESS) {
                        displaySuccess("Appointment booked successfully!");
                    } else {
                        displayError("Failed to book appointment. Please check doctor ID.");
                    }
                } else {
                    displayError("Patient ID not found. Please register first.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // View My Appointments
                displayHeader("MY APPOINTMENTS");
                int patientId;
                patientId = getIntInput("Enter your Patient ID: ");
                
                if (displayAppointments(patientId) != RESULT_SUCCESS) {
                    displayInfo("No appointments found.");
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                // Cancel Appointment
                displayHeader("CANCEL APPOINTMENT");
                int appointmentId;
                appointmentId = getIntInput("Enter Appointment ID to cancel: ");
                
                if (cancelAppointment(appointmentId) == RESULT_SUCCESS) {
                    displaySuccess("Appointment cancelled successfully!");
                } else {
                    displayError("Appointment not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 5: {
                // Search Doctors by Specialty
                displayHeader("SEARCH DOCTORS BY SPECIALTY");
                char specialty[MAX_SPECIALTY_LENGTH];
                getStringInput("Enter specialty: ", specialty, MAX_SPECIALTY_LENGTH);
                
                if (displayDoctorsBySpecialty(specialty) != RESULT_SUCCESS) {
                    displayError("No doctors found for that specialty.");
                }
                pressEnterToContinue();
                break;
            }
            case 6: {
                // Appointment Reports
                displayHeader("APPOINTMENT REPORTS");
                generateAppointmentReport();
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleMedicineOrders(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayMedicineMenu();
        choice = getMenuChoice(0, 5);

        switch (choice) {
            case 1: {
                // Browse All Medicines
                displayHeader("AVAILABLE MEDICINES");
                displayMedicines();
                pressEnterToContinue();
                break;
            }
            case 2: {
                // Search Medicine by Condition
                displayHeader("SEARCH MEDICINES");
                char condition[100];
                getStringInput("Enter condition/indication: ", condition, 100);
                
                if (searchMedicineByIndication(condition) != RESULT_SUCCESS) {
                    displayError("No medicines found for that condition.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // Place Medicine Order
                displayHeader("PLACE MEDICINE ORDER");
                int patientId, medicineId, quantity;
                
                patientId = getIntInput("Enter your Patient ID: ");
                
                if (findPatientById(patientId)) {
                    displayMedicines();
                    medicineId = getIntInput("Select Medicine ID: ");
                    quantity = getIntInput("Enter quantity: ");
                    
                    if (orderMedicine(patientId, medicineId, quantity) == RESULT_SUCCESS) {
                        displaySuccess("Order placed successfully!");
                    } else {
                        displayError("Failed to place order. Please check medicine ID and stock.");
                    }
                } else {
                    displayError("Patient ID not found. Please register first.");
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                // View My Orders
                displayHeader("MY ORDERS");
                int patientId;
                patientId = getIntInput("Enter your Patient ID: ");
                
                if (displayOrders(patientId) != RESULT_SUCCESS) {
                    displayInfo("No orders found.");
                }
                pressEnterToContinue();
                break;
            }
            case 5: {
                // Track Order Status
                displayHeader("TRACK ORDER - REAL-TIME STATUS");
                int orderId;
                orderId = getIntInput("Enter Order ID: ");
                
                MedicineOrder* order = findOrderById(orderId);
                if (order) {
                    Medicine* medicine = findMedicineById(order->medicineId);
                          printf("\n");
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||                    ORDER TRACKING DETAILS                    ||\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Order ID: %-47d " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, order->orderId);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Medicine: %-47s " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, medicine ? medicine->name : "Unknown");
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Quantity: %-47d " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, order->quantity);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Total Amount: $%-42.2f " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, order->totalAmount);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Order Date: %-45s " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, order->orderDate);
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                    
                    // Color-coded status display
                    const char* statusColor = COLOR_YELLOW;
                    const char* statusIcon = "[WAIT]";
                    const char* statusMessage = "Order is being processed";
                    
                    if (strcmp(order->status, "Pending") == 0) {
                        statusColor = COLOR_YELLOW;
                        statusIcon = "[WAIT]";
                        statusMessage = "Order received, waiting for processing";
                    } else if (strcmp(order->status, "Processing") == 0) {
                        statusColor = COLOR_BLUE;
                        statusIcon = "[PREP]";
                        statusMessage = "Order is being prepared by pharmacy";
                    } else if (strcmp(order->status, "Shipped") == 0) {
                        statusColor = COLOR_CYAN;
                        statusIcon = "[SHIP]";
                        statusMessage = "Order shipped, in transit to you";
                    } else if (strcmp(order->status, "Delivered") == 0) {
                        statusColor = COLOR_BRIGHT_GREEN;
                        statusIcon = "[DONE]";
                        statusMessage = "Order successfully delivered!";
                    } else if (strcmp(order->status, "Cancelled") == 0) {
                        statusColor = COLOR_BRIGHT_RED;
                        statusIcon = "[CANC]";
                        statusMessage = "Order has been cancelled";
                    }
                          printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Status: %s%-45s%s " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, statusColor, order->status, COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " %s %s%-43s%s " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, statusIcon, statusColor, statusMessage, COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                
                // Progress bar based on status
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Progress: ");
                int progress = 0;
                if (strcmp(order->status, "Pending") == 0) progress = 1;
                else if (strcmp(order->status, "Processing") == 0) progress = 2;
                else if (strcmp(order->status, "Shipped") == 0) progress = 3;
                else if (strcmp(order->status, "Delivered") == 0) progress = 4;
                
                for (int i = 1; i <= 4; i++) {
                    if (i <= progress) {
                        printf(COLOR_BRIGHT_GREEN "#" COLOR_RESET);
                    } else {
                        printf(COLOR_BRIGHT_BLACK "-" COLOR_RESET);
                    }
                }
                
                const char* stages[] = {"Ordered", "Processing", "Shipped", "Delivered"};
                printf(" %s\n" COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, progress > 0 ? stages[progress-1] : "Unknown");
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                    
                    // Estimated delivery (simulation)
                    if (strcmp(order->status, "Shipped") == 0) {
                        PRINT_INFO("Estimated delivery: 2-3 business days");
                    } else if (strcmp(order->status, "Processing") == 0) {
                        PRINT_INFO("Your order will be shipped within 24 hours");
                    }
                    
                } else {
                    PRINT_ERROR("Order not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleHomeRemedies(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayRemedyMenu();
        choice = getMenuChoice(0, 3);

        switch (choice) {
            case 1: {
                // Browse All Remedies
                displayHeader("ALL HOME REMEDIES");
                displayAllRemedies();
                pressEnterToContinue();
                break;
            }
            case 2: {
                // Search Remedies by Condition
                displayHeader("SEARCH HOME REMEDIES");
                char condition[100];
                getStringInput("Enter condition: ", condition, 100);
                
                if (searchRemedyByIndication(condition) != RESULT_SUCCESS) {
                    displayError("No remedies found for that condition.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // View Remedy Details
                displayHeader("REMEDY DETAILS");
                int remedyId;
                remedyId = getIntInput("Enter Remedy ID: ");
                
                if (displayRemedyDetails(remedyId) != RESULT_SUCCESS) {
                    displayError("Remedy not found.");
                }
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleReportsAnalytics(void) {
    displayHeader("REPORTS & ANALYTICS");
    printf("\n1. Total registered patients: ");
    displayAllPatients();
    
    printf("\n2. Appointment statistics: ");
    generateAppointmentReport();
    
    printf("\n3. System activity log available in: data/activity.log\n");
    
    pressEnterToContinue();
}

void handleSystemSettings(void) {
    displayHeader("SYSTEM SETTINGS");
    
    printf("1. Backup Data\n");
    printf("2. System Information\n");
    printf("3. Clear Activity Log\n");
    printf("0. Back to Main Menu\n");
    
    int choice = getMenuChoice(0, 3);
    
    switch (choice) {
        case 1:
            if (backupData() == RESULT_SUCCESS) {
                displaySuccess("Data backup completed!");
            } else {
                displayError("Backup failed.");
            }
            break;
        case 2:
            printf("\n==================== SYSTEM INFORMATION ====================\n");
            printf("Medical Diagnostic System\n");
            printf("Features: Patient Management, Diagnosis, Appointments, Medicine Orders\n");
            printf("Data storage: File-based system with automatic backups\n");
            printf("=========================================================\n");
            break;
        case 3:
            remove("data/activity.log");
            displaySuccess("Activity log cleared!");
            break;
        case 0:
            return;
    }
    
    pressEnterToContinue();
}

void handlePharmacyManagement(void) {
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayHeader("PHARMACY MANAGEMENT");
        
        printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_WHITE "                         PHARMACY ADMIN PANEL                              " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "++" COLOR_BRIGHT_CYAN "==============================================================================" COLOR_BRIGHT_BLUE "++\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  1. View All Orders                                                       " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  2. Update Order Status                                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  3. Search Orders by Status                                               " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  4. Auto-Process Orders                                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  5. Manage Medicine Stock                                                 " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  6. Order Statistics                                                     " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_RED "  0. Back to Main Menu                                                     " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
        
        choice = getMenuChoice(0, 6);

        switch (choice) {
            case 1: {
                // View All Orders
                displayHeader("ALL MEDICINE ORDERS");
                
                // Read orders from file and display all
                FILE* file = fopen("data/orders.txt", "r");
                if (!file) {
                    PRINT_ERROR("No orders file found.");
                    pressEnterToContinue();
                    break;
                }
                
                char line[256];
                bool hasOrders = false;
                
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "|| OrderID | Patient | Medicine   | Qty     | Amount     | Date        | Status     ||\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                
                while (fgets(line, sizeof(line), file)) {
                    int orderId, patientId, medicineId, quantity;
                    float amount;
                    char date[20], status[20];
                    
                    if (sscanf(line, "%d,%d,%d,%d,%f,%19[^,],%19s", 
                              &orderId, &patientId, &medicineId, &quantity, 
                              &amount, date, status) == 7) {
                        
                        // Color code based on status
                        const char* statusColor = COLOR_YELLOW;
                        if (strcmp(status, "Delivered") == 0) statusColor = COLOR_BRIGHT_GREEN;
                        else if (strcmp(status, "Cancelled") == 0) statusColor = COLOR_BRIGHT_RED;
                        else if (strcmp(status, "Shipped") == 0) statusColor = COLOR_BRIGHT_BLUE;
                        
                        printf("|| %-7d | %-7d | %-10d | %-7d | $%-9.2f | %-11s | %s%-11s%s ||\n",
                               orderId, patientId, medicineId, quantity, amount, date, 
                               statusColor, status, COLOR_RESET);
                        hasOrders = true;
                    }
                }
                
                printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
                fclose(file);
                
                if (!hasOrders) {
                    PRINT_INFO("No orders found in the system.");
                }
                
                pressEnterToContinue();
                break;
            }
            case 2: {
                // Update Order Status
                displayHeader("UPDATE ORDER STATUS");
                
                int orderId = getIntInput("Enter Order ID: ");
                
                MedicineOrder* order = findOrderById(orderId);
                if (!order) {
                    PRINT_ERROR("Order not found.");
                    pressEnterToContinue();
                    break;
                }
                
                printf("\nCurrent Order Details:\n");
                printf("Order ID: %d\n", order->orderId);
                printf("Patient ID: %d\n", order->patientId);
                printf("Medicine ID: %d\n", order->medicineId);
                printf("Quantity: %d\n", order->quantity);
                printf("Total Amount: $%.2f\n", order->totalAmount);
                printf("Current Status: %s\n", order->status);
                
                printf("\nAvailable Status Options:\n");
                printf(COLOR_YELLOW "1. Pending\n" COLOR_RESET);
                printf(COLOR_BRIGHT_BLUE "2. Processing\n" COLOR_RESET);
                printf(COLOR_CYAN "3. Shipped\n" COLOR_RESET);
                printf(COLOR_BRIGHT_GREEN "4. Delivered\n" COLOR_RESET);
                printf(COLOR_BRIGHT_RED "5. Cancelled\n" COLOR_RESET);
                
                int statusChoice = getIntInput("Select new status (1-5): ");
                char newStatus[20];
                
                switch (statusChoice) {
                    case 1: strcpy(newStatus, "Pending"); break;
                    case 2: strcpy(newStatus, "Processing"); break;
                    case 3: strcpy(newStatus, "Shipped"); break;
                    case 4: strcpy(newStatus, "Delivered"); break;
                    case 5: strcpy(newStatus, "Cancelled"); break;
                    default:
                        PRINT_ERROR("Invalid status choice.");
                        pressEnterToContinue();
                        continue;
                }
                
                if (updateOrderStatus(orderId, newStatus) == RESULT_SUCCESS) {
                    PRINT_SUCCESS("Order status updated successfully!");
                    printf("Order #%d status changed to: %s\n", orderId, newStatus);
                } else {
                    PRINT_ERROR("Failed to update order status.");
                }
                
                pressEnterToContinue();
                break;
            }
            case 3: {
                // Search Orders by Status
                displayHeader("SEARCH ORDERS BY STATUS");
                
                printf("Available statuses:\n");
                printf("1. Pending\n2. Processing\n3. Shipped\n4. Delivered\n5. Cancelled\n");
                
                int statusChoice = getIntInput("Select status to search (1-5): ");
                char searchStatus[20];
                
                switch (statusChoice) {
                    case 1: strcpy(searchStatus, "Pending"); break;
                    case 2: strcpy(searchStatus, "Processing"); break;
                    case 3: strcpy(searchStatus, "Shipped"); break;
                    case 4: strcpy(searchStatus, "Delivered"); break;
                    case 5: strcpy(searchStatus, "Cancelled"); break;
                    default:
                        PRINT_ERROR("Invalid choice.");
                        pressEnterToContinue();
                        continue;
                }
                
                printf("\nOrders with status '%s':\n", searchStatus);
                printf("=========================================================================\n");
                
                FILE* file = fopen("data/orders.txt", "r");
                if (!file) {
                    PRINT_ERROR("No orders file found.");
                    pressEnterToContinue();
                    break;
                }
                
                char line[256];
                bool found = false;
                
                while (fgets(line, sizeof(line), file)) {
                    int orderId, patientId, medicineId, quantity;
                    float amount;
                    char date[20], status[20];
                    
                    if (sscanf(line, "%d,%d,%d,%d,%f,%19[^,],%19s", 
                              &orderId, &patientId, &medicineId, &quantity, 
                              &amount, date, status) == 7) {
                        
                        if (strcmp(status, searchStatus) == 0) {
                            printf("Order ID: %d | Patient: %d | Medicine: %d | Qty: %d | Amount: $%.2f | Date: %s\n",
                                   orderId, patientId, medicineId, quantity, amount, date);
                            found = true;
                        }
                    }
                }
                
                fclose(file);
                
                if (!found) {
                    PRINT_INFO("No orders found with the specified status.");
                }
                
                pressEnterToContinue();
                break;
            }
            case 4: {
                // Auto-Process Orders
                displayHeader("AUTO-PROCESS ORDERS");
                
                PRINT_INFO("Processing all pending orders automatically...");
                
                // This simulates an automated pharmacy system
                FILE* file = fopen("data/orders.txt", "r");
                if (!file) {
                    PRINT_ERROR("No orders file found.");
                    pressEnterToContinue();
                    break;
                }
                
                int processedCount = 0;
                char line[256];
                
                while (fgets(line, sizeof(line), file)) {
                    int orderId, patientId, medicineId, quantity;
                    float amount;
                    char date[20], status[20];
                    
                    if (sscanf(line, "%d,%d,%d,%d,%f,%19[^,],%19s", 
                              &orderId, &patientId, &medicineId, &quantity, 
                              &amount, date, status) == 7) {
                        
                        if (strcmp(status, "Pending") == 0) {
                            // Auto-update to "Processing"
                            if (updateOrderStatus(orderId, "Processing") == RESULT_SUCCESS) {
                                printf("Order #%d: Pending → Processing\n", orderId);
                                processedCount++;
                            }
                        }
                    }
                }
                
                fclose(file);
                
                if (processedCount > 0) {
                    PRINT_SUCCESS("Auto-processed %d pending orders to 'Processing' status.");
                } else {
                    PRINT_INFO("No pending orders found to process.");
                }
                
                pressEnterToContinue();
                break;
            }
            case 5: {
                // Manage Medicine Stock
                displayHeader("MEDICINE STOCK MANAGEMENT");
                
                int medicineId = getIntInput("Enter Medicine ID to update stock: ");
                Medicine* medicine = findMedicineById(medicineId);
                
                if (!medicine) {
                    PRINT_ERROR("Medicine not found.");
                    pressEnterToContinue();
                    break;
                }
                
                printf("Medicine: %s\n", medicine->name);
                printf("Current Stock: %d\n", medicine->stockQuantity);
                
                int newStock = getIntInput("Enter new stock quantity: ");
                
                if (updateMedicineStock(medicineId, newStock) == RESULT_SUCCESS) {
                    PRINT_SUCCESS("Medicine stock updated successfully!");
                    printf("Medicine '%s' stock updated to: %d\n", medicine->name, newStock);
                } else {
                    PRINT_ERROR("Failed to update medicine stock.");
                }
                
                pressEnterToContinue();
                break;
            }
            case 6: {
                // Order Statistics
                displayHeader("ORDER STATISTICS");
                
                FILE* file = fopen("data/orders.txt", "r");
                if (!file) {
                    PRINT_ERROR("No orders file found.");
                    pressEnterToContinue();
                    break;
                }
                
                int totalOrders = 0, pending = 0, processing = 0, shipped = 0, delivered = 0, cancelled = 0;
                float totalRevenue = 0.0;
                char line[256];
                
                while (fgets(line, sizeof(line), file)) {
                    int orderId, patientId, medicineId, quantity;
                    float amount;
                    char date[20], status[20];
                    
                    if (sscanf(line, "%d,%d,%d,%d,%f,%19[^,],%19s", 
                              &orderId, &patientId, &medicineId, &quantity, 
                              &amount, date, status) == 7) {
                        
                        totalOrders++;
                        totalRevenue += amount;
                        
                        if (strcmp(status, "Pending") == 0) pending++;
                        else if (strcmp(status, "Processing") == 0) processing++;
                        else if (strcmp(status, "Shipped") == 0) shipped++;
                        else if (strcmp(status, "Delivered") == 0) delivered++;
                        else if (strcmp(status, "Cancelled") == 0) cancelled++;
                    }
                }
                
                fclose(file);
                
                printf("\n");
                printf(COLOR_BRIGHT_CYAN "=======================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||           ORDER STATISTICS          ||\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "=======================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Total Orders: %-18d " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, totalOrders);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET " Total Revenue: $%-16.2f " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET, totalRevenue);
                printf(COLOR_BRIGHT_CYAN "=======================================\n" COLOR_RESET);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_YELLOW " Pending: %-23d" COLOR_RESET COLOR_BRIGHT_CYAN " ||\n" COLOR_RESET, pending);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BLUE " Processing: %-20d" COLOR_RESET COLOR_BRIGHT_CYAN " ||\n" COLOR_RESET, processing);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_CYAN " Shipped: %-23d" COLOR_RESET COLOR_BRIGHT_CYAN " ||\n" COLOR_RESET, shipped);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN " Delivered: %-21d" COLOR_RESET COLOR_BRIGHT_CYAN " ||\n" COLOR_RESET, delivered);
                printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_RED " Cancelled: %-21d" COLOR_RESET COLOR_BRIGHT_CYAN " ||\n" COLOR_RESET, cancelled);
                printf(COLOR_BRIGHT_CYAN "=======================================\n" COLOR_RESET);
                
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}
// Additional functions for main.c - User Management

void handleUserManagement(void) {
    if (!hasPermission(ROLE_ADMIN)) {
        displayError("Access denied. Admin privileges required!");
        pressEnterToContinue();
        return;
    }
    
    int choice;
    bool backToMain = false;

    while (!backToMain) {
        displayHeader("USER MANAGEMENT");
        
        printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_WHITE "                          USER ADMINISTRATION                              " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "++" COLOR_BRIGHT_YELLOW "=============================================================================" COLOR_BRIGHT_CYAN "++\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  1. View All Users                                                        " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  2. Create New User Account                                               " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  3. Change My Password                                                    " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_RED "  0. Back to Main Menu                                                     " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
        printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
        
        choice = getMenuChoice(0, 3);

        switch (choice) {
            case 1: {
                displayHeader("ALL USER ACCOUNTS");
                displayUsers();
                pressEnterToContinue();
                break;
            }
            case 2: {
                displayHeader("CREATE NEW USER ACCOUNT");
                
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                char email[MAX_EMAIL_LENGTH];
                char fullName[MAX_NAME_LENGTH];
                
                getStringInput("Username: ", username, MAX_USERNAME_LENGTH);
                getStringInput("Full Name: ", fullName, MAX_NAME_LENGTH);
                getStringInput("Email: ", email, MAX_EMAIL_LENGTH);
                getPasswordInput("Password (min 6 chars): ", password, MAX_PASSWORD_LENGTH);
                
                printf("\nSelect User Role:\n");
                printf("1. Patient\n2. Doctor\n3. Admin\n4. Pharmacy Staff\n");
                
                int roleChoice = getMenuChoice(1, 4);
                user_role_t role = (user_role_t)roleChoice;
                
                if (registerUser(username, password, email, fullName, role) == RESULT_SUCCESS) {
                    displaySuccess("User account created successfully!");
                } else {
                    displayError("Failed to create user account.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                displayHeader("CHANGE PASSWORD");
                
                char oldPassword[MAX_PASSWORD_LENGTH];
                char newPassword[MAX_PASSWORD_LENGTH];
                
                getPasswordInput("Current Password: ", oldPassword, MAX_PASSWORD_LENGTH);
                getPasswordInput("New Password: ", newPassword, MAX_PASSWORD_LENGTH);
                
                if (changePassword(oldPassword, newPassword) == RESULT_SUCCESS) {
                    displaySuccess("Password changed successfully!");
                } else {
                    displayError("Failed to change password.");
                }
                pressEnterToContinue();
                break;
            }
            case 0:
                backToMain = true;
                break;
        }
    }
}

void handleAccountSettings(void) {
    displayHeader("ACCOUNT SETTINGS");
    
    if (!isUserLoggedIn()) {
        displayError("Not logged in!");
        return;
    }
    
    User* user = findUserById(currentSession.userId);
    if (!user) {
        displayError("User not found!");
        return;
    }
    
    const char* roleNames[] = {"", "Patient", "Doctor", "Admin", "Pharmacy"};
    
    printf(COLOR_BRIGHT_CYAN "Account: %s (%s)\n" COLOR_RESET, user->fullName, roleNames[user->role]);
    printf("Email: %s\n", user->email);
    printf("Status: %s\n", user->isActive ? "Active" : "Disabled");
    
    pressEnterToContinue();
}
