#ifndef UTILS_H
#define UTILS_H

#include "common.h"

// Function declarations
result_t createDataDirectories(void);
result_t validateEmail(const char* email);
result_t validatePhone(const char* phone);
result_t validateBloodGroup(const char* bloodGroup);
result_t getCurrentDate(char* dateBuffer, int bufferSize);
result_t getCurrentTime(char* timeBuffer, int bufferSize);
result_t stringToLower(char* str);
result_t stringToUpper(char* str);
result_t trimWhitespace(char* str);
result_t generateUniqueId(void);
result_t backupData(void);
result_t restoreData(void);
result_t logActivity(const char* activity);
int stringCompareIgnoreCase(const char* str1, const char* str2);

// UI Input Functions
void pressEnterToContinue(void);
void getStringInput(const char* prompt, char* buffer, size_t size);
int getIntInput(const char* prompt);
float getFloatInput(const char* prompt);
char getCharInput(const char* prompt);

#endif // UTILS_H
