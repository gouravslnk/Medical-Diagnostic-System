#include "../include/utils.h"

result_t createDataDirectories(void) {
    // Create data directory if it doesn't exist
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
    
    return RESULT_SUCCESS;
}

result_t validateEmail(const char* email) {
    if (!email || strlen(email) < 5) {
        return RESULT_ERROR;
    }

    // Basic email validation - contains @ and .
    const char* at = strchr(email, '@');
    const char* dot = strrchr(email, '.');
    
    if (!at || !dot || at > dot || at == email || dot == email + strlen(email) - 1) {
        return RESULT_ERROR;
    }
    
    return RESULT_SUCCESS;
}

result_t validatePhone(const char* phone) {
    if (!phone || strlen(phone) < 10 || strlen(phone) > 15) {
        return RESULT_ERROR;
    }

    // Check if all characters are digits, spaces, hyphens, or parentheses
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i]) && phone[i] != ' ' && 
            phone[i] != '-' && phone[i] != '(' && phone[i] != ')') {
            return RESULT_ERROR;
        }
    }
    
    return RESULT_SUCCESS;
}

result_t validateBloodGroup(const char* bloodGroup) {
    if (!bloodGroup) {
        return RESULT_ERROR;
    }

    const char* validGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    int numGroups = sizeof(validGroups) / sizeof(validGroups[0]);
    
    for (int i = 0; i < numGroups; i++) {
        if (strcmp(bloodGroup, validGroups[i]) == 0) {
            return RESULT_SUCCESS;
        }
    }
    
    return RESULT_ERROR;
}

result_t getCurrentDate(char* dateBuffer, int bufferSize) {
    if (!dateBuffer || bufferSize < 11) {
        return RESULT_ERROR;
    }

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    
    strftime(dateBuffer, bufferSize, "%Y-%m-%d", tm_info);
    return RESULT_SUCCESS;
}

result_t getCurrentTime(char* timeBuffer, int bufferSize) {
    if (!timeBuffer || bufferSize < 9) {
        return RESULT_ERROR;
    }

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    
    strftime(timeBuffer, bufferSize, "%H:%M:%S", tm_info);
    return RESULT_SUCCESS;
}

result_t stringToLower(char* str) {
    if (!str) {
        return RESULT_ERROR;
    }

    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    
    return RESULT_SUCCESS;
}

result_t stringToUpper(char* str) {
    if (!str) {
        return RESULT_ERROR;
    }

    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
    
    return RESULT_SUCCESS;
}

result_t trimWhitespace(char* str) {
    if (!str) {
        return RESULT_ERROR;
    }

    // Trim leading whitespace
    char* start = str;
    while (isspace(*start)) {
        start++;
    }
    
    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        end--;
    }
    
    // Move trimmed string to beginning and null terminate
    int len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0';
    
    return RESULT_SUCCESS;
}

result_t generateUniqueId(void) {
    static int counter = 0;
    return (int)time(NULL) + (++counter);
}

result_t backupData(void) {
    char timestamp[20];
    getCurrentDate(timestamp, sizeof(timestamp));
    
    char backupDir[100];
    snprintf(backupDir, sizeof(backupDir), "backup_%s", timestamp);
    
    #ifdef _WIN32
        char command[200];
        snprintf(command, sizeof(command), "xcopy data %s /E /I", backupDir);
        system(command);
    #else
        char command[200];
        snprintf(command, sizeof(command), "cp -r data %s", backupDir);
        system(command);
    #endif
    
    return RESULT_SUCCESS;
}

result_t restoreData(void) {
    // Implementation for data restoration
    // This would typically involve listing backup directories
    // and allowing user to select which backup to restore
    printf("Data restoration feature - implementation depends on requirements\n");
    return RESULT_SUCCESS;
}

result_t logActivity(const char* activity) {
    if (!activity) {
        return RESULT_ERROR;
    }

    FILE* logFile = fopen("data/activity.log", "a");
    if (!logFile) {
        return RESULT_ERROR;
    }

    char timestamp[30];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(logFile, "[%s] %s\n", timestamp, activity);
    fclose(logFile);
    
    return RESULT_SUCCESS;
}

int stringCompareIgnoreCase(const char* str1, const char* str2) {
    if (!str1 || !str2) {
        return -1;
    }

    while (*str1 && *str2) {
        int c1 = tolower(*str1);
        int c2 = tolower(*str2);
        
        if (c1 != c2) {
            return c1 - c2;
        }
        
        str1++;
        str2++;
    }
    
    return tolower(*str1) - tolower(*str2);
}

// UI Input Functions
void pressEnterToContinue(void) {
    printf("\n" COLOR_BRIGHT_YELLOW "Press Enter to continue..." COLOR_RESET);
    fflush(stdout);
    while (getchar() != '\n');
    CLEAR_AND_HOME();
}

void getStringInput(const char* prompt, char* buffer, size_t size) {
    printf(COLOR_BRIGHT_CYAN "%s" COLOR_RESET, prompt);
    fflush(stdout);
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

int getIntInput(const char* prompt) {
    char buffer[20];
    int value;
    char* endptr;
    
    while (1) {
        printf(COLOR_BRIGHT_CYAN "%s" COLOR_RESET, prompt);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            value = (int)strtol(buffer, &endptr, 10);
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                return value;
            }
        }
        PRINT_ERROR("Invalid input. Please enter a valid integer.");
    }
}

float getFloatInput(const char* prompt) {
    char buffer[20];
    float value;
    char* endptr;
    
    while (1) {
        printf(COLOR_BRIGHT_CYAN "%s" COLOR_RESET, prompt);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            value = strtof(buffer, &endptr);
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                return value;
            }
        }
        PRINT_ERROR("Invalid input. Please enter a valid number.");
    }
}

char getCharInput(const char* prompt) {
    char buffer[10];
    
    while (1) {
        printf(COLOR_BRIGHT_CYAN "%s" COLOR_RESET, prompt);
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n') {
            return buffer[0];
        }
        PRINT_ERROR("Invalid input. Please enter a single character.");
    }
}
