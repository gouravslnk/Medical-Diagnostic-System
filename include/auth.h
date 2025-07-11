#ifndef AUTH_H
#define AUTH_H

#include "common.h"

// Authentication constants
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_USERS 500
#define SESSION_TIMEOUT 3600 // 1 hour in seconds

// User roles
typedef enum {
    ROLE_PATIENT = 1,
    ROLE_DOCTOR = 2,
    ROLE_ADMIN = 3,
    ROLE_PHARMACY = 4
} user_role_t;

// User structure
typedef struct {
    int userId;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char fullName[MAX_NAME_LENGTH];
    user_role_t role;
    bool isActive;
    time_t lastLogin;
    time_t registrationDate;
    int patientId; // For patients, links to Patient record
} User;

// Session structure
typedef struct {
    int userId;
    user_role_t role;
    char username[MAX_USERNAME_LENGTH];
    time_t loginTime;
    bool isLoggedIn;
} Session;

// Global session
extern Session currentSession;

// Authentication functions
result_t initializeAuth(void);
result_t registerUser(const char* username, const char* password, const char* email, 
                     const char* fullName, user_role_t role);
result_t loginUser(const char* username, const char* password);
void logoutUser(void);
bool isUserLoggedIn(void);
bool hasPermission(user_role_t requiredRole);
result_t changePassword(const char* oldPassword, const char* newPassword);
result_t resetPassword(const char* username, const char* email);

// User management functions
result_t displayUsers(void);
result_t deleteUser(const char* username);
result_t updateUserRole(const char* username, user_role_t newRole);
result_t toggleUserStatus(const char* username);
User* findUserByUsername(const char* username);
User* findUserById(int userId);

// Security functions
bool validatePassword(const char* password);
// Email validation handled by utils.h
char* hashPassword(const char* password);
bool verifyPassword(const char* password, const char* hashedPassword);

// Login screen functions
void displayLoginScreen(void);
void displayRegistrationScreen(void);
void displayAuthMenu(void);
result_t handleAuthentication(void);

// Session management
void updateLastLogin(int userId);
bool isSessionValid(void);
void displaySessionInfo(void);

#endif // AUTH_H
