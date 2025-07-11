#include "../include/medicines.h"
#include "../include/utils.h"

// Global variables
static Medicine medicines[MAX_MEDICINES];
static MedicineOrder orders[MAX_PATIENTS * 20];
static int medicineCount = 0;
static int orderCount = 0;

result_t initializeMedicines(void) {
    medicineCount = 0;
    
    // Initialize some default medicines
    strcpy(medicines[0].name, "Aspirin");
    strcpy(medicines[0].indication, "Headache");
    strcpy(medicines[0].dosage, "500mg twice daily");
    strcpy(medicines[0].manufacturer, "PharmaCorp");
    strcpy(medicines[0].expiryDate, "2025-12-31");
    medicines[0].id = 1;
    medicines[0].price = 5.99;
    medicines[0].stockQuantity = 100;
    
    strcpy(medicines[1].name, "Ibuprofen");
    strcpy(medicines[1].indication, "Pain & Inflammation");
    strcpy(medicines[1].dosage, "400mg thrice daily");
    strcpy(medicines[1].manufacturer, "MediCare");
    strcpy(medicines[1].expiryDate, "2025-11-30");
    medicines[1].id = 2;
    medicines[1].price = 8.50;
    medicines[1].stockQuantity = 75;
    
    strcpy(medicines[2].name, "Acetaminophen");
    strcpy(medicines[2].indication, "Fever & Pain");
    strcpy(medicines[2].dosage, "500mg every 6 hours");
    strcpy(medicines[2].manufacturer, "HealthPlus");
    strcpy(medicines[2].expiryDate, "2026-01-15");
    medicines[2].id = 3;
    medicines[2].price = 6.25;
    medicines[2].stockQuantity = 120;
    
    strcpy(medicines[3].name, "Amoxicillin");
    strcpy(medicines[3].indication, "Bacterial Infections");
    strcpy(medicines[3].dosage, "250mg thrice daily");
    strcpy(medicines[3].manufacturer, "AntiBio");
    strcpy(medicines[3].expiryDate, "2025-10-20");
    medicines[3].id = 4;
    medicines[3].price = 12.75;
    medicines[3].stockQuantity = 50;
    
    strcpy(medicines[4].name, "Loratadine");
    strcpy(medicines[4].indication, "Allergies");
    strcpy(medicines[4].dosage, "10mg once daily");
    strcpy(medicines[4].manufacturer, "AllergyFree");
    strcpy(medicines[4].expiryDate, "2025-09-30");
    medicines[4].id = 5;
    medicines[4].price = 9.99;
    medicines[4].stockQuantity = 80;
    
    medicineCount = 5;
    return RESULT_SUCCESS;
}

result_t initializeOrders(void) {
    orderCount = 0;
    return loadOrdersFromFile();
}

result_t searchMedicineByIndication(const char* indication) {
    bool found = false;
    printf("\n================ MEDICINES FOR: %s ================\n", indication);
    printf("%-5s %-20s %-10s %-15s %-10s %-10s\n", "ID", "Name", "Price", "Dosage", "Stock", "Expiry");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < medicineCount; i++) {
        if (strstr(medicines[i].indication, indication) != NULL) {
            printf("%-5d %-20s $%-9.2f %-15s %-10d %-10s\n",
                   medicines[i].id, medicines[i].name, medicines[i].price,
                   medicines[i].dosage, medicines[i].stockQuantity,
                   medicines[i].expiryDate);
            found = true;
        }
    }

    if (!found) {
        printf("No medicines found for indication: %s\n", indication);
        return RESULT_NOT_FOUND;
    }

    printf("===============================================================\n");
    return RESULT_SUCCESS;
}

result_t orderMedicine(int patientId, int medicineId, int quantity) {
    if (quantity <= 0 || orderCount >= MAX_PATIENTS * 20) {
        return RESULT_ERROR;
    }

    Medicine* medicine = findMedicineById(medicineId);
    if (!medicine) {
        return RESULT_NOT_FOUND;
    }

    if (medicine->stockQuantity < quantity) {
        printf("Insufficient stock. Available: %d, Requested: %d\n", 
               medicine->stockQuantity, quantity);
        return RESULT_ERROR;
    }

    // Generate new order ID
    int newOrderId = 1;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId >= newOrderId) {
            newOrderId = orders[i].orderId + 1;
        }
    }

    orders[orderCount].orderId = newOrderId;
    orders[orderCount].patientId = patientId;
    orders[orderCount].medicineId = medicineId;
    orders[orderCount].quantity = quantity;
    orders[orderCount].totalAmount = medicine->price * quantity;
    strcpy(orders[orderCount].status, "Pending");
    
    char dateStr[20];
    getCurrentDate(dateStr, sizeof(dateStr));
    strcpy(orders[orderCount].orderDate, dateStr);

    // Update stock
    medicine->stockQuantity -= quantity;

    orderCount++;
    saveOrdersToFile();
    saveMedicinesToFile();
    logActivity("Medicine order placed");

    printf("\n==================== ORDER CONFIRMATION ====================\n");
    printf("Order ID: %d\n", newOrderId);
    printf("Medicine: %s\n", medicine->name);
    printf("Quantity: %d\n", quantity);
    printf("Total Amount: $%.2f\n", orders[orderCount-1].totalAmount);
    printf("Order Date: %s\n", orders[orderCount-1].orderDate);
    printf("Status: %s\n", orders[orderCount-1].status);
    printf("Expected delivery: 3-5 business days\n");
    printf("=========================================================\n");

    return RESULT_SUCCESS;
}

result_t displayMedicines(void) {
    if (medicineCount == 0) {
        printf("No medicines available.\n");
        return RESULT_NOT_FOUND;
    }

    printf("\n==================== AVAILABLE MEDICINES ====================\n");
    printf("%-5s %-20s %-20s %-10s %-10s %-15s\n", "ID", "Name", "Indication", "Price", "Stock", "Manufacturer");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < medicineCount; i++) {
        printf("%-5d %-20s %-20s $%-9.2f %-10d %-15s\n",
               medicines[i].id, medicines[i].name, medicines[i].indication,
               medicines[i].price, medicines[i].stockQuantity, medicines[i].manufacturer);
        printf("      Dosage: %s, Expiry: %s\n", medicines[i].dosage, medicines[i].expiryDate);
        printf("\n");
    }
    printf("================================================================\n");

    return RESULT_SUCCESS;
}

result_t displayOrders(int patientId) {
    bool found = false;
    printf("\n================ ORDERS FOR PATIENT %d ================\n", patientId);
    printf("%-10s %-20s %-10s %-12s %-15s %-15s\n", "Order ID", "Medicine", "Quantity", "Amount", "Date", "Status");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].patientId == patientId) {
            Medicine* medicine = findMedicineById(orders[i].medicineId);
            printf("%-10d %-20s %-10d $%-11.2f %-15s %-15s\n",
                   orders[i].orderId,
                   medicine ? medicine->name : "Unknown",
                   orders[i].quantity,
                   orders[i].totalAmount,
                   orders[i].orderDate,
                   orders[i].status);
            found = true;
        }
    }

    if (!found) {
        printf("No orders found for patient %d\n", patientId);
        return RESULT_NOT_FOUND;
    }

    printf("=========================================================================\n");
    return RESULT_SUCCESS;
}

result_t updateOrderStatus(int orderId, const char* status) {
    MedicineOrder* order = findOrderById(orderId);
    if (!order || !status) {
        return RESULT_NOT_FOUND;
    }

    strcpy(order->status, status);
    saveOrdersToFile();
    logActivity("Order status updated");

    return RESULT_SUCCESS;
}

Medicine* findMedicineById(int medicineId) {
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == medicineId) {
            return &medicines[i];
        }
    }
    return NULL;
}

MedicineOrder* findOrderById(int orderId) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            return &orders[i];
        }
    }
    return NULL;
}

result_t addMedicine(const Medicine* medicine) {
    if (!medicine || medicineCount >= MAX_MEDICINES) {
        return RESULT_ERROR;
    }

    medicines[medicineCount] = *medicine;
    medicineCount++;
    
    saveMedicinesToFile();
    return RESULT_SUCCESS;
}

result_t updateMedicineStock(int medicineId, int newStock) {
    Medicine* medicine = findMedicineById(medicineId);
    if (!medicine) {
        return RESULT_NOT_FOUND;
    }

    medicine->stockQuantity = newStock;
    saveMedicinesToFile();
    logActivity("Medicine stock updated");

    return RESULT_SUCCESS;
}

result_t saveMedicinesToFile(void) {
    FILE* file = fopen("data/medicines.txt", "w");
    if (!file) {
        return RESULT_ERROR;
    }

    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%.2f|%d|%s|%s\n",
                medicines[i].id, medicines[i].name, medicines[i].indication,
                medicines[i].dosage, medicines[i].price, medicines[i].stockQuantity,
                medicines[i].manufacturer, medicines[i].expiryDate);
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t loadMedicinesFromFile(void) {
    FILE* file = fopen("data/medicines.txt", "r");
    if (!file) {
        return RESULT_SUCCESS; // File doesn't exist yet
    }

    char line[500];
    medicineCount = 0;

    while (fgets(line, sizeof(line), file) && medicineCount < MAX_MEDICINES) {
        Medicine medicine;
        if (sscanf(line, "%d|%49[^|]|%99[^|]|%49[^|]|%f|%d|%49[^|]|%19[^\n]",
                   &medicine.id, medicine.name, medicine.indication,
                   medicine.dosage, &medicine.price, &medicine.stockQuantity,
                   medicine.manufacturer, medicine.expiryDate) == 8) {
            medicines[medicineCount++] = medicine;
        }
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t saveOrdersToFile(void) {
    FILE* file = fopen("data/orders.txt", "w");
    if (!file) {
        return RESULT_ERROR;
    }

    for (int i = 0; i < orderCount; i++) {
        fprintf(file, "%d|%d|%d|%d|%.2f|%s|%s\n",
                orders[i].orderId, orders[i].patientId, orders[i].medicineId,
                orders[i].quantity, orders[i].totalAmount,
                orders[i].orderDate, orders[i].status);
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t loadOrdersFromFile(void) {
    FILE* file = fopen("data/orders.txt", "r");
    if (!file) {
        return RESULT_SUCCESS; // File doesn't exist yet
    }

    char line[300];
    orderCount = 0;

    while (fgets(line, sizeof(line), file) && orderCount < MAX_PATIENTS * 20) {
        MedicineOrder order;
        if (sscanf(line, "%d|%d|%d|%d|%f|%19[^|]|%19[^\n]",
                   &order.orderId, &order.patientId, &order.medicineId,
                   &order.quantity, &order.totalAmount,
                   order.orderDate, order.status) == 7) {
            orders[orderCount++] = order;
        }
    }

    fclose(file);
    return RESULT_SUCCESS;
}
