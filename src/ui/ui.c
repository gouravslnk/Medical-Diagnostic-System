#include "../include/ui.h"
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

// Initialize ANSI color support on Windows
void initializeColorSupport(void) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void displayWelcomeMessage(void) {
    CLEAR_AND_HOME();
    printf("\n");
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET "                                                                            " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_GREEN "                    M   M EEEEE DDDD  III  CCC                             " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_GREEN "                    MM MM E     D   D  I  C                                " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_GREEN "                    M M M EEEE  D   D  I  C                                " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_GREEN "                    M   M E     D   D  I  C                                " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_GREEN "                    M   M EEEEE DDDD  III  CCC                             " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET "                                                                            " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_YELLOW "                        Your Digital Health Assistant                      " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET "                                                                            " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_YELLOW "                     *** FOR EDUCATIONAL USE ONLY ***                      " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_RED "                   *** NOT FOR REAL MEDICAL DECISIONS ***                  " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET "                                                                            " COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
    printf("\n");
}

void displayMainMenu(void) {
    printf("\n");
    printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_WHITE "                               MAIN MENU                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "++" COLOR_BRIGHT_CYAN "==============================================================================" COLOR_BRIGHT_BLUE "++\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  1. Patient Management                                                    " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  2. Diagnosis System                                                      " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  3. Doctor Appointments                                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  4. Medicine Order                                                        " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  5. Home Remedies                                                         " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  6. Reports & Analytics                                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_GREEN "  7. System Settings                                                       " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_MAGENTA "  8. Pharmacy Management                                                   " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_CYAN "  9. User Management (Admin)                                               " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_RESET COLOR_BRIGHT_RED "  0. Logout & Exit                                                         " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
}

void displayPatientMenu(void) {
    printf("\n================================================================================\n");
    printf("||                           PATIENT MANAGEMENT                            ||\n");
    printf("++==============================================================================++\n");
    printf("||  1. Register New Patient                                                ||\n");
    printf("||  2. View Patient Details                                                ||\n");
    printf("||  3. Update Patient Information                                          ||\n");
    printf("||  4. Search Patients                                                     ||\n");
    printf("||  5. List All Patients                                                   ||\n");
    printf("||  6. Delete Patient Record                                               ||\n");
    printf("||  0. Back to Main Menu                                                   ||\n");
    printf("================================================================================\n");
}

void displayDoctorMenu(void) {
    printf("\n================================================================================\n");
    printf("||                          DOCTOR APPOINTMENTS                            ||\n");
    printf("++==============================================================================++\n");
    printf("||  1. View Available Doctors                                              ||\n");
    printf("||  2. Book Appointment                                                    ||\n");
    printf("||  3. View My Appointments                                                ||\n");
    printf("||  4. Cancel Appointment                                                  ||\n");
    printf("||  5. Search Doctors by Specialty                                         ||\n");
    printf("||  6. Appointment Reports                                                 ||\n");
    printf("||  0. Back to Main Menu                                                   ||\n");
    printf("================================================================================\n");
}

void displayMedicineMenu(void) {
    printf("\n================================================================================\n");
    printf("||                            MEDICINE ORDERS                              ||\n");
    printf("++==============================================================================++\n");
    printf("||  1. Browse All Medicines                                                ||\n");
    printf("||  2. Search Medicine by Condition                                        ||\n");
    printf("||  3. Place Medicine Order                                                ||\n");
    printf("||  4. View My Orders                                                      ||\n");
    printf("||  5. Track Order Status                                                  ||\n");
    printf("||  0. Back to Main Menu                                                   ||\n");
    printf("================================================================================\n");
}

void displayRemedyMenu(void) {
    printf("\n================================================================================\n");
    printf("||                             HOME REMEDIES                               ||\n");
    printf("++==============================================================================++\n");
    printf("||  1. Browse All Remedies                                                 ||\n");
    printf("||  2. Search Remedies by Condition                                        ||\n");
    printf("||  3. View Remedy Details                                                 ||\n");
    printf("||  0. Back to Main Menu                                                   ||\n");
    printf("================================================================================\n");
}

void displayDiagnosisMenu(void) {
    printf("\n================================================================================\n");
    printf("||                            DIAGNOSIS SYSTEM                             ||\n");
    printf("++==============================================================================++\n");
    printf("||  1. Start Symptom Assessment                                            ||\n");
    printf("||  2. View Previous Diagnoses                                             ||\n");
    printf("||  3. Update Medical History                                              ||\n");
    printf("||  4. Emergency Symptom Check                                             ||\n");
    printf("||  0. Back to Main Menu                                                   ||\n");
    printf("================================================================================\n");
}

void displayHeader(const char* title) {
    CLEAR_AND_HOME();
    printf("\n");
    PRINT_HEADER(title);
    printf("\n");
}

void displayFooter(void) {
    printf("================================================================================\n");
}

void displaySeparator(void) {
    printf("--------------------------------------------------------------------------------\n");
}

void displaySuccess(const char* message) {
    printf("\n");
    PRINT_SUCCESS(message);
    printf("\n");
}

void displayError(const char* message) {
    printf("\n");
    PRINT_ERROR(message);
    printf("\n");
}

void displayWarning(const char* message) {
    printf("\n");
    PRINT_WARNING(message);
    printf("\n");
}

void displayInfo(const char* message) {
    printf("\n");
    PRINT_INFO(message);
    printf("\n");
}

void displayMedicalDisclaimer(void) {
    printf("\n");
    printf("================================================================================\n");
    printf("||                            MEDICAL DISCLAIMER                             ||\n");
    printf("++==============================================================================++\n");
    printf("||                                                                            ||\n");
    printf("||  This system is for EDUCATIONAL PURPOSES ONLY!                            ||\n");
    printf("||                                                                            ||\n");
    printf("||  - This is NOT a replacement for professional medical advice              ||\n");
    printf("||  - Do NOT use this for real medical decisions                             ||\n");
    printf("||  - Always consult qualified healthcare professionals                      ||\n");
    printf("||  - In case of emergency, call your local emergency services              ||\n");
    printf("||                                                                            ||\n");
    printf("||  This software is provided for learning and demonstration purposes.       ||\n");
    printf("||                                                                            ||\n");
    printf("================================================================================\n");
    printf("\n");
}

void waitForKeyPress(void) {
    printf("Press any key to continue...");
    fflush(stdout);
    getchar();
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    fflush(stdout);
    while (getchar() != '\n');
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getMenuChoice(int min, int max) {
    int choice;
    char buffer[10];
    
    while (1) {
        printf(COLOR_BRIGHT_YELLOW "Enter your choice (%d-%d): " COLOR_RESET, min, max);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &choice) == 1) {
                if (choice >= min && choice <= max) {
                    return choice;
                }
            }
        }
        
        PRINT_ERROR("Invalid choice! Please try again.");
    }
}

void displayProgressBar(int percentage) {
    printf("\nProgress: [");
    for (int i = 0; i < 50; i++) {
        if (i < percentage / 2) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", percentage);
    fflush(stdout);
}

void animateLoading(const char* message) {
    printf("%s", message);
    fflush(stdout);
    
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        #ifdef _WIN32
        Sleep(500);  // Windows-specific sleep function (milliseconds)
        #else
        usleep(500000);  // Unix-like systems (microseconds)
        #endif
    }
    printf(" Done!\n");
}

void getPasswordInput(const char* prompt, char* buffer, int maxLength) {
    printf(COLOR_BRIGHT_YELLOW "%s" COLOR_RESET, prompt);
    fflush(stdout);
    
    int i = 0;
    char ch;
    
    while (i < maxLength - 1) {
        #ifdef _WIN32
        ch = _getch(); // Windows-specific function for character input without echo
        #else
        // For Unix-like systems, use termios to disable echo
        struct termios old, new;
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        new.c_lflag &= ~(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        #endif
        
        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == '\b' || ch == 127) { // Backspace or DEL
            if (i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back again
                fflush(stdout);
            }
        } else {
            buffer[i++] = ch;
            printf("*"); // Print asterisk instead of actual character
            fflush(stdout);
        }
    }
    
    buffer[i] = '\0';
    printf("\n");
}
