#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Constants
#define MAX_PATIENTS 1000
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_BLOOD_GROUP_LENGTH 10
#define MAX_SYMPTOM_LENGTH 60
#define MAX_DISEASE_LENGTH 60
#define MAX_MEDICINE_LENGTH 50
#define MAX_DOCTOR_NAME_LENGTH 50
#define MAX_SPECIALTY_LENGTH 50
#define MAX_REMEDY_LENGTH 100
#define MAX_SYMPTOMS_PER_DISEASE 5
#define MAX_DISEASES 50
#define MAX_DOCTORS 50
#define MAX_MEDICINES 50
#define MAX_REMEDIES 100

// Error codes
#define SUCCESS 0
#define ERROR_FILE_NOT_FOUND 1
#define ERROR_INVALID_INPUT 2
#define ERROR_MEMORY_ALLOCATION 3
#define ERROR_PATIENT_NOT_FOUND 4

// Function return types
typedef enum {
    RESULT_SUCCESS,
    RESULT_ERROR,
    RESULT_NOT_FOUND
} result_t;

// Utility macros
#define CLEAR_SCREEN() system("cls")
#define PAUSE_SYSTEM() system("pause")

// ANSI Color codes for terminal styling
#define COLOR_RESET     "\033[0m"
#define COLOR_BLACK     "\033[30m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_WHITE     "\033[37m"

// Bright colors
#define COLOR_BRIGHT_BLACK   "\033[90m"
#define COLOR_BRIGHT_RED     "\033[91m"
#define COLOR_BRIGHT_GREEN   "\033[92m"
#define COLOR_BRIGHT_YELLOW  "\033[93m"
#define COLOR_BRIGHT_BLUE    "\033[94m"
#define COLOR_BRIGHT_MAGENTA "\033[95m"
#define COLOR_BRIGHT_CYAN    "\033[96m"
#define COLOR_BRIGHT_WHITE   "\033[97m"

// Background colors
#define COLOR_BG_BLACK   "\033[40m"
#define COLOR_BG_RED     "\033[41m"
#define COLOR_BG_GREEN   "\033[42m"
#define COLOR_BG_YELLOW  "\033[43m"
#define COLOR_BG_BLUE    "\033[44m"
#define COLOR_BG_MAGENTA "\033[45m"
#define COLOR_BG_CYAN    "\033[46m"
#define COLOR_BG_WHITE   "\033[47m"

// Text styles
#define STYLE_BOLD      "\033[1m"
#define STYLE_DIM       "\033[2m"
#define STYLE_ITALIC    "\033[3m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_BLINK     "\033[5m"
#define STYLE_REVERSE   "\033[7m"

// Utility functions for clean interface
#define CLEAR_AND_HOME() printf("\033[2J\033[H")
#define CLEAR_LINE() printf("\033[2K\r")
#define MOVE_CURSOR_UP(n) printf("\033[%dA", n)
#define MOVE_CURSOR_DOWN(n) printf("\033[%dB", n)
#define SAVE_CURSOR() printf("\033[s")
#define RESTORE_CURSOR() printf("\033[u")

// Enhanced display macros
#define PRINT_SUCCESS(msg) printf(COLOR_BRIGHT_GREEN "[SUCCESS] " COLOR_RESET COLOR_GREEN "%s" COLOR_RESET "\n", msg)
#define PRINT_ERROR(msg) printf(COLOR_BRIGHT_RED "[ERROR] " COLOR_RESET COLOR_RED "%s" COLOR_RESET "\n", msg)
#define PRINT_INFO(msg) printf(COLOR_BRIGHT_CYAN "[INFO] " COLOR_RESET COLOR_CYAN "%s" COLOR_RESET "\n", msg)
#define PRINT_WARNING(msg) printf(COLOR_BRIGHT_YELLOW "[WARNING] " COLOR_RESET COLOR_YELLOW "%s" COLOR_RESET "\n", msg)
#define PRINT_HEADER(msg) printf(COLOR_BRIGHT_BLUE "=== " COLOR_RESET COLOR_BRIGHT_WHITE "%s" COLOR_RESET COLOR_BRIGHT_BLUE " ===" COLOR_RESET "\n", msg)

#endif // COMMON_H
