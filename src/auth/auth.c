#include "../include/auth.h"
#include "../include/ui.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global session
Session currentSession = {0};

// File paths
static const char* USERS_FILE = "data/users.txt";
static const char* SESSION_FILE = "data/session.txt";

result_t initializeAuth(void) {
    // Initialize session
    memset(&currentSession, 0, sizeof(Session));
    
    // Check if users file exists, if not create admin account
    FILE* file = fopen(USERS_FILE, "r");
    if (!file) {
        // Create default admin account
        if (registerUser("admin", "admin123", "admin@medical.com", 
                        "System Administrator", ROLE_ADMIN) != RESULT_SUCCESS) {
            return RESULT_ERROR;
        }
        printf(COLOR_BRIGHT_GREEN "Default admin account created!\n" COLOR_RESET);
        printf(COLOR_BRIGHT_YELLOW "Username: admin, Password: admin123\n" COLOR_RESET);
        printf(COLOR_BRIGHT_RED "Please change the default password after first login!\n" COLOR_RESET);
    } else {
        fclose(file);
    }
    
    return RESULT_SUCCESS;
}

result_t registerUser(const char* username, const char* password, const char* email, 
                     const char* fullName, user_role_t role) {
    // Validate inputs
    if (!username || !password || !email || !fullName) {
        return RESULT_ERROR;
    }
    
    if (!validatePassword(password)) {
        displayError("Password must be at least 6 characters long!");
        return RESULT_ERROR;
    }
    
    if (validateEmail(email) != RESULT_SUCCESS) {
        displayError("Invalid email format!");
        return RESULT_ERROR;
    }
    
    // Check if username already exists
    if (findUserByUsername(username) != NULL) {
        displayError("Username already exists!");
        return RESULT_ERROR;
    }
    
    // Create new user
    User newUser = {0};
    
    // Generate user ID
    FILE* file = fopen(USERS_FILE, "r");
    int maxId = 0;
    if (file) {
        char line[512];
        while (fgets(line, sizeof(line), file)) {
            User tempUser;
            if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                      &tempUser.userId, tempUser.username, tempUser.password,
                      tempUser.email, tempUser.fullName, (int*)&tempUser.role,
                      (int*)&tempUser.isActive, &tempUser.lastLogin,
                      &tempUser.registrationDate, &tempUser.patientId) >= 9) {
                if (tempUser.userId > maxId) {
                    maxId = tempUser.userId;
                }
            }
        }
        fclose(file);
    }
    
    newUser.userId = maxId + 1;
    strncpy(newUser.username, username, MAX_USERNAME_LENGTH - 1);
    newUser.username[MAX_USERNAME_LENGTH - 1] = '\0';
    strncpy(newUser.password, hashPassword(password), MAX_PASSWORD_LENGTH - 1);
    newUser.password[MAX_PASSWORD_LENGTH - 1] = '\0';
    strncpy(newUser.email, email, MAX_EMAIL_LENGTH - 1);
    newUser.email[MAX_EMAIL_LENGTH - 1] = '\0';
    strncpy(newUser.fullName, fullName, MAX_NAME_LENGTH - 1);
    newUser.fullName[MAX_NAME_LENGTH - 1] = '\0';
    newUser.role = role;
    newUser.isActive = true;
    newUser.lastLogin = 0;
    newUser.registrationDate = time(NULL);
    newUser.patientId = 0; // Will be set when patient record is created
    
    // Save to file
    file = fopen(USERS_FILE, "a");
    if (!file) {
        return RESULT_ERROR;
    }
    
    fprintf(file, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
            newUser.userId, newUser.username, newUser.password,
            newUser.email, newUser.fullName, newUser.role,
            newUser.isActive, newUser.lastLogin,
            newUser.registrationDate, newUser.patientId);
    
    fclose(file);
    
    char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User registered: %s (Role: %d)", username, role);
    logActivity(logMsg);
    return RESULT_SUCCESS;
}

result_t loginUser(const char* username, const char* password) {
    if (!username || !password) {
        return RESULT_ERROR;
    }
    
    User* user = findUserByUsername(username);
    if (!user) {
        displayError("Username not found!");
        return RESULT_ERROR;
    }
    
    if (!user->isActive) {
        displayError("Account is disabled! Contact administrator.");
        return RESULT_ERROR;
    }
    
    if (!verifyPassword(password, user->password)) {
        displayError("Invalid password!");
        return RESULT_ERROR;
    }
    
    // Create session
    currentSession.userId = user->userId;
    currentSession.role = user->role;
    strncpy(currentSession.username, user->username, MAX_USERNAME_LENGTH - 1);
    currentSession.username[MAX_USERNAME_LENGTH - 1] = '\0';
    currentSession.loginTime = time(NULL);
    currentSession.isLoggedIn = true;
    
    // Update last login time
    updateLastLogin(user->userId);
    
    // Save session to file
    FILE* file = fopen(SESSION_FILE, "w");
    if (file) {
        fprintf(file, "%d,%d,%s,%lld,%d\n",
                currentSession.userId, currentSession.role,
                currentSession.username, currentSession.loginTime,
                currentSession.isLoggedIn);
        fclose(file);
    }
    
    char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User logged in: %s", username);
    logActivity(logMsg);
    return RESULT_SUCCESS;
}

void logoutUser(void) {
    if (currentSession.isLoggedIn) {
        char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User logged out: %s", currentSession.username);
    logActivity(logMsg);
        
        // Clear session
        memset(&currentSession, 0, sizeof(Session));
        
        // Clear session file
        remove(SESSION_FILE);
        
        displaySuccess("Logged out successfully!");
    }
}

bool isUserLoggedIn(void) {
    return currentSession.isLoggedIn && isSessionValid();
}

bool hasPermission(user_role_t requiredRole) {
    if (!isUserLoggedIn()) {
        return false;
    }
    
    // Admin has access to everything
    if (currentSession.role == ROLE_ADMIN) {
        return true;
    }
    
    // Check specific role permissions
    return currentSession.role >= requiredRole;
}

bool isSessionValid(void) {
    if (!currentSession.isLoggedIn) {
        return false;
    }
    
    time_t currentTime = time(NULL);
    return (currentTime - currentSession.loginTime) < SESSION_TIMEOUT;
}

User* findUserByUsername(const char* username) {
    static User user;
    FILE* file = fopen(USERS_FILE, "r");
    
    if (!file) {
        return NULL;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            if (strcmp(user.username, username) == 0) {
                fclose(file);
                return &user;
            }
        }
    }
    
    fclose(file);
    return NULL;
}

User* findUserById(int userId) {
    static User user;
    FILE* file = fopen(USERS_FILE, "r");
    
    if (!file) {
        return NULL;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            if (user.userId == userId) {
                fclose(file);
                return &user;
            }
        }
    }
    
    fclose(file);
    return NULL;
}

bool validatePassword(const char* password) {
    return password && strlen(password) >= 6;
}

// validateEmail function is implemented in utils.c

char* hashPassword(const char* password) {
    static char hashed[MAX_PASSWORD_LENGTH];
    
    // Simple hash function (XOR with salt)
    // In production, use proper hashing like bcrypt
    int salt = 12345;
    int len = strlen(password);
    
    for (int i = 0; i < len && i < MAX_PASSWORD_LENGTH - 1; i++) {
        hashed[i] = password[i] ^ (salt + i);
    }
    hashed[len] = '\0';
    
    return hashed;
}

bool verifyPassword(const char* password, const char* hashedPassword) {
    char* hashed = hashPassword(password);
    return strcmp(hashed, hashedPassword) == 0;
}

void updateLastLogin(int userId) {
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }
    
    char line[512];
    time_t currentTime = time(NULL);
    
    while (fgets(line, sizeof(line), file)) {
        User user;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            
            if (user.userId == userId) {
                user.lastLogin = currentTime;
            }
            
            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
                    user.userId, user.username, user.password,
                    user.email, user.fullName, user.role,
                    user.isActive, user.lastLogin,
                    user.registrationDate, user.patientId);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    remove(USERS_FILE);
    rename("data/users_temp.txt", USERS_FILE);
}

void displayLoginScreen(void) {
    CLEAR_AND_HOME();
    printf("\n");
    printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_BRIGHT_WHITE "                        MEDICAL SYSTEM LOGIN                          " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||" COLOR_BRIGHT_YELLOW "                        SECURE ACCESS PORTAL                               " COLOR_RESET COLOR_BRIGHT_BLUE "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "================================================================================\n" COLOR_RESET);
    printf("\n");
}

void displayRegistrationScreen(void) {
    CLEAR_AND_HOME();
    printf("\n");
    printf(COLOR_BRIGHT_GREEN "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "||" COLOR_BRIGHT_WHITE "                      USER REGISTRATION                              " COLOR_RESET COLOR_BRIGHT_GREEN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "||" COLOR_BRIGHT_YELLOW "                      CREATE NEW ACCOUNT                              " COLOR_RESET COLOR_BRIGHT_GREEN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "||                                                                            ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_GREEN "================================================================================\n" COLOR_RESET);
    printf("\n");
}

void displayAuthMenu(void) {
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_WHITE "                         AUTHENTICATION MENU                              " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "++" COLOR_BRIGHT_YELLOW "==============================================================================" COLOR_BRIGHT_CYAN "++\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  1. Login to Existing Account                                            " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  2. Register New User Account                                           " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  3. Admin Login                                                         " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_GREEN "  4. Forgot Password                                                     " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||" COLOR_RESET COLOR_BRIGHT_RED "  0. Exit Application                                                    " COLOR_RESET COLOR_BRIGHT_CYAN "||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
}

result_t handleAuthentication(void) {
    while (!isUserLoggedIn()) {
        displayLoginScreen();
        displayAuthMenu();
        
        int choice = getMenuChoice(0, 4);
        
        switch (choice) {
            case 1: {
                // User Login
                displayLoginScreen();
                printf(COLOR_BRIGHT_WHITE "=== USER LOGIN ===\n" COLOR_RESET);
                
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                
                getStringInput("Username: ", username, MAX_USERNAME_LENGTH);
                getPasswordInput("Password: ", password, MAX_PASSWORD_LENGTH);
                
                if (loginUser(username, password) == RESULT_SUCCESS) {
                    displaySuccess("Login successful!");
                    printf(COLOR_BRIGHT_GREEN "Welcome, %s!\n" COLOR_RESET, currentSession.username);
                    
                    const char* roleNames[] = {"", "Patient", "Doctor", "Admin", "Pharmacy"};
                    printf(COLOR_BRIGHT_YELLOW "Role: %s\n" COLOR_RESET, roleNames[currentSession.role]);
                    
                    pressEnterToContinue();
                    return RESULT_SUCCESS;
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                // User Registration
                displayRegistrationScreen();
                printf(COLOR_BRIGHT_WHITE "=== NEW USER REGISTRATION ===\n" COLOR_RESET);
                
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                char email[MAX_EMAIL_LENGTH];
                char fullName[MAX_NAME_LENGTH];
                
                getStringInput("Username: ", username, MAX_USERNAME_LENGTH);
                getStringInput("Full Name: ", fullName, MAX_NAME_LENGTH);
                getStringInput("Email: ", email, MAX_EMAIL_LENGTH);
                getPasswordInput("Password (min 6 chars): ", password, MAX_PASSWORD_LENGTH);
                
                printf("\nSelect Account Type:\n");
                printf("1. Patient Account\n");
                printf("2. Doctor Account\n");
                
                int roleChoice = getMenuChoice(1, 2);
                user_role_t role = (roleChoice == 1) ? ROLE_PATIENT : ROLE_DOCTOR;
                
                if (registerUser(username, password, email, fullName, role) == RESULT_SUCCESS) {
                    displaySuccess("Registration successful!");
                    printf(COLOR_BRIGHT_GREEN "You can now login with your credentials.\n" COLOR_RESET);
                } else {
                    displayError("Registration failed. Please try again.");
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                // Admin Login
                displayLoginScreen();
                printf(COLOR_BRIGHT_RED "=== ADMINISTRATOR LOGIN ===\n" COLOR_RESET);
                printf(COLOR_BRIGHT_YELLOW "Admin access required for system management\n" COLOR_RESET);
                
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                
                getStringInput("Admin Username: ", username, MAX_USERNAME_LENGTH);
                getPasswordInput("Admin Password: ", password, MAX_PASSWORD_LENGTH);
                
                if (loginUser(username, password) == RESULT_SUCCESS) {
                    if (currentSession.role == ROLE_ADMIN) {
                        displaySuccess("Admin login successful!");
                        printf(COLOR_BRIGHT_RED "Administrative access granted.\n" COLOR_RESET);
                        pressEnterToContinue();
                        return RESULT_SUCCESS;
                    } else {
                        displayError("Access denied. Admin privileges required!");
                        logoutUser();
                    }
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                // Forgot Password
                displayHeader("PASSWORD RECOVERY");
                printf(COLOR_BRIGHT_YELLOW "Password recovery feature\n" COLOR_RESET);
                printf("Please contact system administrator for password reset.\n");
                printf("Email: admin@medical.com\n");
                pressEnterToContinue();
                break;
            }
            case 0: {
                // Exit
                printf(COLOR_BRIGHT_YELLOW "Thank you for using Medical Diagnostic System!\n" COLOR_RESET);
                exit(EXIT_SUCCESS);
            }
            default:
                displayError("Invalid choice!");
                break;
        }
    }
    
    return RESULT_SUCCESS;
}

void displaySessionInfo(void) {
    if (!isUserLoggedIn()) {
        return;
    }
    
    const char* roleNames[] = {"", "Patient", "Doctor", "Admin", "Pharmacy"};
    time_t sessionTime = time(NULL) - currentSession.loginTime;
    
    printf(COLOR_BRIGHT_BLUE "┌─────────────────────────────────────────────────────────────────────────────┐\n" COLOR_RESET);
    printf(COLOR_BRIGHT_BLUE "│" COLOR_RESET COLOR_BRIGHT_WHITE " Session Info: %-60s " COLOR_RESET COLOR_BRIGHT_BLUE "│\n" COLOR_RESET, currentSession.username);
    printf(COLOR_BRIGHT_BLUE "│" COLOR_RESET COLOR_BRIGHT_YELLOW " Role: %-67s " COLOR_RESET COLOR_BRIGHT_BLUE "│\n" COLOR_RESET, roleNames[currentSession.role]);
    printf(COLOR_BRIGHT_BLUE "│" COLOR_RESET COLOR_BRIGHT_GREEN " Session Time: %lld minutes %-47s " COLOR_RESET COLOR_BRIGHT_BLUE "│\n" COLOR_RESET, sessionTime / 60, "");
    printf(COLOR_BRIGHT_BLUE "└─────────────────────────────────────────────────────────────────────────────┘\n" COLOR_RESET);
}

result_t displayUsers(void) {
    if (!hasPermission(ROLE_ADMIN)) {
        displayError("Access denied. Admin privileges required!");
        return RESULT_ERROR;
    }
    
    FILE* file = fopen(USERS_FILE, "r");
    if (!file) {
        displayError("Users file not found!");
        return RESULT_ERROR;
    }
    
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "||                              USER ACCOUNTS                               ||\n" COLOR_RESET);
    printf(COLOR_BRIGHT_CYAN "================================================================================\n" COLOR_RESET);
    printf("ID   | Username        | Full Name              | Role      | Status    | Last Login\n");
    printf("---------------------------------------------------------------------------------\n");
    
    char line[512];
    const char* roleNames[] = {"", "Patient", "Doctor", "Admin", "Pharmacy"};
    
    while (fgets(line, sizeof(line), file)) {
        User user;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            
            char lastLoginStr[20] = "Never";
            if (user.lastLogin > 0) {
                struct tm* timeinfo = localtime(&user.lastLogin);
                strftime(lastLoginStr, sizeof(lastLoginStr), "%Y-%m-%d", timeinfo);
            }
            
            const char* statusColor = user.isActive ? COLOR_GREEN : COLOR_RED;
            const char* status = user.isActive ? "Active" : "Disabled";
            
            printf("%-4d | %-15s | %-22s | %-9s | %s%-9s%s | %s\n",
                   user.userId, user.username, user.fullName,
                   roleNames[user.role], statusColor, status, COLOR_RESET,
                   lastLoginStr);
        }
    }
    
    fclose(file);
    return RESULT_SUCCESS;
}

result_t changePassword(const char* oldPassword, const char* newPassword) {
    if (!isUserLoggedIn()) {
        return RESULT_ERROR;
    }
    
    User* user = findUserById(currentSession.userId);
    if (!user || !verifyPassword(oldPassword, user->password)) {
        displayError("Invalid current password!");
        return RESULT_ERROR;
    }
    
    if (!validatePassword(newPassword)) {
        displayError("New password must be at least 6 characters long!");
        return RESULT_ERROR;
    }
    
    // Update password in file
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return RESULT_ERROR;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        User tempUser;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &tempUser.userId, tempUser.username, tempUser.password,
                  tempUser.email, tempUser.fullName, (int*)&tempUser.role,
                  (int*)&tempUser.isActive, &tempUser.lastLogin,
                  &tempUser.registrationDate, &tempUser.patientId) >= 9) {
            
            if (tempUser.userId == currentSession.userId) {
                strncpy(tempUser.password, hashPassword(newPassword), MAX_PASSWORD_LENGTH - 1);
                tempUser.password[MAX_PASSWORD_LENGTH - 1] = '\0';
            }
            
            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
                    tempUser.userId, tempUser.username, tempUser.password,
                    tempUser.email, tempUser.fullName, tempUser.role,
                    tempUser.isActive, tempUser.lastLogin,
                    tempUser.registrationDate, tempUser.patientId);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    remove(USERS_FILE);
    rename("data/users_temp.txt", USERS_FILE);
    
    displaySuccess("Password changed successfully!");
    char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "Password changed for user: %s", currentSession.username);
    logActivity(logMsg);
    
    return RESULT_SUCCESS;
}

result_t deleteUser(const char* username) {
    if (!hasPermission(ROLE_ADMIN)) {
        return RESULT_ERROR;
    }
    
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return RESULT_ERROR;
    }
    
    char line[512];
    bool found = false;
    
    while (fgets(line, sizeof(line), file)) {
        User user;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            
            if (strcmp(user.username, username) != 0) {
                fprintf(tempFile, "%s", line);
            } else {
                found = true;
            }
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (found) {
        remove(USERS_FILE);
        rename("data/users_temp.txt", USERS_FILE);
        char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User deleted: %s", username);
    logActivity(logMsg);
        return RESULT_SUCCESS;
    } else {
        remove("data/users_temp.txt");
        return RESULT_NOT_FOUND;
    }
}

result_t updateUserRole(const char* username, user_role_t newRole) {
    if (!hasPermission(ROLE_ADMIN)) {
        return RESULT_ERROR;
    }
    
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return RESULT_ERROR;
    }
    
    char line[512];
    bool found = false;
    
    while (fgets(line, sizeof(line), file)) {
        User user;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            
            if (strcmp(user.username, username) == 0) {
                user.role = newRole;
                found = true;
            }
            
            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
                    user.userId, user.username, user.password,
                    user.email, user.fullName, user.role,
                    user.isActive, user.lastLogin,
                    user.registrationDate, user.patientId);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (found) {
        remove(USERS_FILE);
        rename("data/users_temp.txt", USERS_FILE);
        char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User role updated: %s", username);
    logActivity(logMsg);
        return RESULT_SUCCESS;
    } else {
        remove("data/users_temp.txt");
        return RESULT_NOT_FOUND;
    }
}

result_t toggleUserStatus(const char* username) {
    if (!hasPermission(ROLE_ADMIN)) {
        return RESULT_ERROR;
    }
    
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return RESULT_ERROR;
    }
    
    char line[512];
    bool found = false;
    
    while (fgets(line, sizeof(line), file)) {
        User user;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &user.userId, user.username, user.password,
                  user.email, user.fullName, (int*)&user.role,
                  (int*)&user.isActive, &user.lastLogin,
                  &user.registrationDate, &user.patientId) >= 9) {
            
            if (strcmp(user.username, username) == 0) {
                user.isActive = !user.isActive;
                found = true;
            }
            
            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
                    user.userId, user.username, user.password,
                    user.email, user.fullName, user.role,
                    user.isActive, user.lastLogin,
                    user.registrationDate, user.patientId);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (found) {
        remove(USERS_FILE);
        rename("data/users_temp.txt", USERS_FILE);
        char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "User status toggled: %s", username);
    logActivity(logMsg);
        return RESULT_SUCCESS;
    } else {
        remove("data/users_temp.txt");
        return RESULT_NOT_FOUND;
    }
}

result_t resetPassword(const char* username, const char* email) {
    // Find user by username and email
    User* user = findUserByUsername(username);
    if (!user || strcmp(user->email, email) != 0) {
        return RESULT_NOT_FOUND;
    }
    
    // Generate temporary password
    char tempPassword[] = "temp123";
    
    // Update password in file
    FILE* file = fopen(USERS_FILE, "r");
    FILE* tempFile = fopen("data/users_temp.txt", "w");
    
    if (!file || !tempFile) {
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return RESULT_ERROR;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        User tempUser;
        if (sscanf(line, "%d,%49[^,],%99[^,],%99[^,],%99[^,],%d,%d,%lld,%lld,%d",
                  &tempUser.userId, tempUser.username, tempUser.password,
                  tempUser.email, tempUser.fullName, (int*)&tempUser.role,
                  (int*)&tempUser.isActive, &tempUser.lastLogin,
                  &tempUser.registrationDate, &tempUser.patientId) >= 9) {
            
            if (strcmp(tempUser.username, username) == 0) {
                strncpy(tempUser.password, hashPassword(tempPassword), MAX_PASSWORD_LENGTH - 1);
                tempUser.password[MAX_PASSWORD_LENGTH - 1] = '\0';
            }
            
            fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%d,%lld,%lld,%d\n",
                    tempUser.userId, tempUser.username, tempUser.password,
                    tempUser.email, tempUser.fullName, tempUser.role,
                    tempUser.isActive, tempUser.lastLogin,
                    tempUser.registrationDate, tempUser.patientId);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    remove(USERS_FILE);
    rename("data/users_temp.txt", USERS_FILE);
    
    printf("Password reset successful! Temporary password: %s\n", tempPassword);
    char logMsg[256];
    snprintf(logMsg, sizeof(logMsg), "Password reset for user: %s", username);
    logActivity(logMsg);
    
    return RESULT_SUCCESS;
}
