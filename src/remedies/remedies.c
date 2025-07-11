#include "../include/remedies.h"
#include "../include/utils.h"

// Global variables
static HomeRemedy remedies[MAX_REMEDIES];
static int remedyCount = 0;

result_t initializeRemedies(void) {
    remedyCount = 0;
    
    // Initialize some default home remedies
    strcpy(remedies[0].name, "Ginger tea");
    strcpy(remedies[0].indication, "nausea");
    strcpy(remedies[0].instructions, "Boil fresh ginger slices in water for 10 minutes. Add honey to taste. Drink warm 2-3 times daily.");
    strcpy(remedies[0].ingredients, "Fresh ginger (1 inch), Water (1 cup), Honey (optional)");
    strcpy(remedies[0].precautions, "Avoid if allergic to ginger. Consult doctor if pregnant.");
    remedies[0].id = 1;
    
    strcpy(remedies[1].name, "Honey and Lemon");
    strcpy(remedies[1].indication, "sore_throat");
    strcpy(remedies[1].instructions, "Mix 2 tablespoons honey with fresh lemon juice in warm water. Gargle and drink slowly.");
    strcpy(remedies[1].ingredients, "Honey (2 tbsp), Fresh lemon juice (1 tbsp), Warm water (1 cup)");
    strcpy(remedies[1].precautions, "Not suitable for children under 1 year due to honey.");
    remedies[1].id = 2;
    
    strcpy(remedies[2].name, "Turmeric milk");
    strcpy(remedies[2].indication, "inflammation");
    strcpy(remedies[2].instructions, "Add 1 tsp turmeric powder to warm milk. Mix well and drink before bedtime.");
    strcpy(remedies[2].ingredients, "Turmeric powder (1 tsp), Warm milk (1 cup), Honey (optional)");
    strcpy(remedies[2].precautions, "May interact with blood thinners. Consult doctor if on medication.");
    remedies[2].id = 3;
    
    strcpy(remedies[3].name, "Garlic");
    strcpy(remedies[3].indication, "high_blood_pressure");
    strcpy(remedies[3].instructions, "Consume 1-2 raw garlic cloves daily on empty stomach or add to food.");
    strcpy(remedies[3].ingredients, "Fresh garlic cloves (1-2 pieces)");
    strcpy(remedies[3].precautions, "May cause stomach upset. Avoid before surgery. Check with doctor if on blood thinners.");
    remedies[3].id = 4;
    
    strcpy(remedies[4].name, "Chamomile tea");
    strcpy(remedies[4].indication, "insomnia");
    strcpy(remedies[4].instructions, "Steep chamomile tea bag in hot water for 5 minutes. Drink 30 minutes before bedtime.");
    strcpy(remedies[4].ingredients, "Chamomile tea bag or dried flowers (1 tsp), Hot water (1 cup)");
    strcpy(remedies[4].precautions, "Avoid if allergic to ragweed family. May interact with blood thinners.");
    remedies[4].id = 5;
    
    strcpy(remedies[5].name, "Aloe vera");
    strcpy(remedies[5].indication, "burns");
    strcpy(remedies[5].instructions, "Apply fresh aloe vera gel directly to the burn. Leave for 15-20 minutes, then gently rinse.");
    strcpy(remedies[5].ingredients, "Fresh aloe vera leaf");
    strcpy(remedies[5].precautions, "Test on small area first. Only for minor burns. Seek medical help for severe burns.");
    remedies[5].id = 6;
    
    strcpy(remedies[6].name, "Apple cider vinegar");
    strcpy(remedies[6].indication, "indigestion");
    strcpy(remedies[6].instructions, "Mix 1 tbsp apple cider vinegar in warm water. Drink 15 minutes before meals.");
    strcpy(remedies[6].ingredients, "Apple cider vinegar (1 tbsp), Warm water (1 cup)");
    strcpy(remedies[6].precautions, "May damage tooth enamel. Dilute properly. Avoid if you have ulcers.");
    remedies[6].id = 7;
    
    strcpy(remedies[7].name, "Peppermint oil");
    strcpy(remedies[7].indication, "headaches");
    strcpy(remedies[7].instructions, "Dilute peppermint oil with carrier oil. Gently massage temples and forehead.");
    strcpy(remedies[7].ingredients, "Peppermint essential oil (2-3 drops), Carrier oil like coconut oil (1 tsp)");
    strcpy(remedies[7].precautions, "Always dilute before use. Avoid contact with eyes. Test on small area first.");
    remedies[7].id = 8;
    
    remedyCount = 8;
    return RESULT_SUCCESS;
}

result_t searchRemedyByIndication(const char* indication) {
    bool found = false;
    printf("\n================ HOME REMEDIES FOR: %s ================\n", indication);

    for (int i = 0; i < remedyCount; i++) {
        if (strstr(remedies[i].indication, indication) != NULL) {
            printf("\n--- %s ---\n", remedies[i].name);
            printf("Indication: %s\n", remedies[i].indication);
            printf("Ingredients: %s\n", remedies[i].ingredients);
            printf("Instructions: %s\n", remedies[i].instructions);
            printf("Precautions: %s\n", remedies[i].precautions);
            printf("----------------------------------------\n");
            found = true;
        }
    }

    if (!found) {
        printf("No home remedies found for: %s\n", indication);
        return RESULT_NOT_FOUND;
    }

    printf("\nIMPORTANT: These are traditional home remedies for information purposes only.\n");
    printf("Always consult a healthcare professional for proper medical advice.\n");
    printf("============================================================\n");

    return RESULT_SUCCESS;
}

result_t displayAllRemedies(void) {
    if (remedyCount == 0) {
        printf("No home remedies available.\n");
        return RESULT_NOT_FOUND;
    }

    printf("\n==================== ALL HOME REMEDIES ====================\n");
    printf("%-5s %-25s %-20s\n", "ID", "Remedy", "For");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < remedyCount; i++) {
        printf("%-5d %-25s %-20s\n", remedies[i].id, remedies[i].name, remedies[i].indication);
    }
    
    printf("============================================================\n");
    printf("Use remedy ID to get detailed instructions.\n");

    return RESULT_SUCCESS;
}

result_t displayRemedyDetails(int remedyId) {
    HomeRemedy* remedy = findRemedyById(remedyId);
    if (!remedy) {
        return RESULT_NOT_FOUND;
    }

    printf("\n==================== REMEDY DETAILS ====================\n");
    printf("Remedy: %s\n", remedy->name);
    printf("For: %s\n", remedy->indication);
    printf("\nIngredients:\n%s\n", remedy->ingredients);
    printf("\nInstructions:\n%s\n", remedy->instructions);
    printf("\nPrecautions:\n%s\n", remedy->precautions);
    printf("========================================================\n");
    printf("DISCLAIMER: This is for informational purposes only.\n");
    printf("Consult a healthcare professional before use.\n");

    return RESULT_SUCCESS;
}

result_t addRemedy(const HomeRemedy* remedy) {
    if (!remedy || remedyCount >= MAX_REMEDIES) {
        return RESULT_ERROR;
    }

    remedies[remedyCount] = *remedy;
    remedyCount++;
    
    saveRemediesToFile();
    return RESULT_SUCCESS;
}

HomeRemedy* findRemedyById(int remedyId) {
    for (int i = 0; i < remedyCount; i++) {
        if (remedies[i].id == remedyId) {
            return &remedies[i];
        }
    }
    return NULL;
}

result_t saveRemediesToFile(void) {
    FILE* file = fopen("data/remedies.txt", "w");
    if (!file) {
        return RESULT_ERROR;
    }

    for (int i = 0; i < remedyCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%s\n",
                remedies[i].id, remedies[i].name, remedies[i].indication,
                remedies[i].instructions, remedies[i].ingredients,
                remedies[i].precautions);
    }

    fclose(file);
    return RESULT_SUCCESS;
}

result_t loadRemediesFromFile(void) {
    FILE* file = fopen("data/remedies.txt", "r");
    if (!file) {
        return RESULT_SUCCESS; // File doesn't exist yet
    }

    char line[1000];
    remedyCount = 0;

    while (fgets(line, sizeof(line), file) && remedyCount < MAX_REMEDIES) {
        HomeRemedy remedy;
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%299[^|]|%199[^|]|%199[^\n]",
                   &remedy.id, remedy.name, remedy.indication,
                   remedy.instructions, remedy.ingredients,
                   remedy.precautions) == 6) {
            remedies[remedyCount++] = remedy;
        }
    }

    fclose(file);
    return RESULT_SUCCESS;
}
