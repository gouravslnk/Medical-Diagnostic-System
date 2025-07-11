#ifndef MEDICINES_H
#define MEDICINES_H

#include "common.h"

// Medicine structure
typedef struct {
    int id;
    char name[MAX_MEDICINE_LENGTH];
    char indication[100];
    char dosage[50];
    float price;
    int stockQuantity;
    char manufacturer[50];
    char expiryDate[20];
} Medicine;

// Order structure
typedef struct {
    int orderId;
    int patientId;
    int medicineId;
    int quantity;
    float totalAmount;
    char orderDate[20];
    char status[20]; // Pending, Shipped, Delivered, Cancelled
} MedicineOrder;

// Function declarations
result_t initializeMedicines(void);
result_t initializeOrders(void);
result_t searchMedicineByIndication(const char* indication);
result_t orderMedicine(int patientId, int medicineId, int quantity);
result_t displayMedicines(void);
result_t displayOrders(int patientId);
result_t updateOrderStatus(int orderId, const char* status);
Medicine* findMedicineById(int medicineId);
MedicineOrder* findOrderById(int orderId);
result_t addMedicine(const Medicine* medicine);
result_t updateMedicineStock(int medicineId, int newStock);
result_t saveMedicinesToFile(void);
result_t loadMedicinesFromFile(void);
result_t saveOrdersToFile(void);
result_t loadOrdersFromFile(void);

#endif // MEDICINES_H
