# Medical Diagnostic System Makefile
# Professional C pro# Compile main
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Compile auth module
$(AUTH_OBJ): $(AUTH_SRC)
	$(CC) $(CFLAGS) -c $(AUTH_SRC) -o $(AUTH_OBJ)

# Compile patient module
$(PATIENT_OBJ): $(PATIENT_SRC)
	$(CC) $(CFLAGS) -c $(PATIENT_SRC) -o $(PATIENT_OBJ)ild configuration

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# Source files
AUTH_SRC = $(SRC_DIR)/auth/auth.c
PATIENT_SRC = $(SRC_DIR)/patient/patient.c
DIAGNOSIS_SRC = $(SRC_DIR)/diagnosis/diagnosis.c
APPOINTMENTS_SRC = $(SRC_DIR)/appointments/appointments.c
MEDICINES_SRC = $(SRC_DIR)/medicines/medicines.c
REMEDIES_SRC = $(SRC_DIR)/remedies/remedies.c
UI_SRC = $(SRC_DIR)/ui/ui.c
UTILS_SRC = $(SRC_DIR)/utils/utils.c
MAIN_SRC = main.c

# Object files
AUTH_OBJ = $(OBJ_DIR)/auth.o
PATIENT_OBJ = $(OBJ_DIR)/patient.o
DIAGNOSIS_OBJ = $(OBJ_DIR)/diagnosis.o
APPOINTMENTS_OBJ = $(OBJ_DIR)/appointments.o
MEDICINES_OBJ = $(OBJ_DIR)/medicines.o
REMEDIES_OBJ = $(OBJ_DIR)/remedies.o
UI_OBJ = $(OBJ_DIR)/ui.o
UTILS_OBJ = $(OBJ_DIR)/utils.o
MAIN_OBJ = $(OBJ_DIR)/main.o

# All object files
OBJS = $(AUTH_OBJ) $(PATIENT_OBJ) $(DIAGNOSIS_OBJ) $(APPOINTMENTS_OBJ) $(MEDICINES_OBJ) $(REMEDIES_OBJ) $(UI_OBJ) $(UTILS_OBJ) $(MAIN_OBJ)

# Target executable
TARGET = $(BIN_DIR)/medical_system.exe

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@if not exist $(DATA_DIR) mkdir $(DATA_DIR)

# Build the main executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@echo Build completed successfully!

# Compile main.c
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Compile auth module
$(AUTH_OBJ): $(AUTH_SRC)
	$(CC) $(CFLAGS) -c $(AUTH_SRC) -o $(AUTH_OBJ)

# Compile patient module
$(PATIENT_OBJ): $(PATIENT_SRC)
	$(CC) $(CFLAGS) -c $(PATIENT_SRC) -o $(PATIENT_OBJ)

# Compile diagnosis module
$(DIAGNOSIS_OBJ): $(DIAGNOSIS_SRC)
	$(CC) $(CFLAGS) -c $(DIAGNOSIS_SRC) -o $(DIAGNOSIS_OBJ)

# Compile appointments module
$(APPOINTMENTS_OBJ): $(APPOINTMENTS_SRC)
	$(CC) $(CFLAGS) -c $(APPOINTMENTS_SRC) -o $(APPOINTMENTS_OBJ)

# Compile medicines module
$(MEDICINES_OBJ): $(MEDICINES_SRC)
	$(CC) $(CFLAGS) -c $(MEDICINES_SRC) -o $(MEDICINES_OBJ)

# Compile remedies module
$(REMEDIES_OBJ): $(REMEDIES_SRC)
	$(CC) $(CFLAGS) -c $(REMEDIES_SRC) -o $(REMEDIES_OBJ)

# Compile UI module
$(UI_OBJ): $(UI_SRC)
	$(CC) $(CFLAGS) -c $(UI_SRC) -o $(UI_OBJ)

# Compile utils module
$(UTILS_OBJ): $(UTILS_SRC)
	$(CC) $(CFLAGS) -c $(UTILS_SRC) -o $(UTILS_OBJ)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: directories $(TARGET)
	@echo Debug build completed!

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: directories $(TARGET)
	@echo Release build completed!

# Clean build artifacts
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
	@echo Clean completed!

# Clean data files
clean-data:
	@if exist $(DATA_DIR)\*.txt del /q $(DATA_DIR)\*.txt
	@if exist $(DATA_DIR)\*.log del /q $(DATA_DIR)\*.log
	@echo Data files cleaned!

# Install (copy to a system directory - modify as needed)
install: $(TARGET)
	@echo Installation target - modify as needed for your system

# Run the application
run: $(TARGET)
	$(TARGET)

# Help target
help:
	@echo Available targets:
	@echo   all      - Build the application (default)
	@echo   debug    - Build with debug flags
	@echo   release  - Build with optimization flags
	@echo   clean    - Remove build artifacts
	@echo   clean-data - Remove data files
	@echo   run      - Build and run the application
	@echo   install  - Install the application
	@echo   help     - Show this help message

# Declare phony targets
.PHONY: all directories debug release clean clean-data install run help
