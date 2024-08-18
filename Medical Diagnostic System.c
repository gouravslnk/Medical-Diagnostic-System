///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/////////////////////// Medical Diagnostic System /////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// MAIN FUNCTION :
int main()
{
    FILE *nm;
    nm = fopen("name.txt", "a+");
    if (nm == NULL)
    {
        printf("error / file doesn't exist");
    }

    // MAKING A STRUCTURE PATIENT WITH ALL DIFFERNT PATIENT DETAILS
    typedef struct Patient
    {
        char name[500];
        int age;
        float weight;
        char gender;
        char phonenumber[20];
        char bloodgroup[50];
    } Patient;

    Patient arr[100];

    // Patients Records / Data :
    strcpy(arr[1].name, "Anshumaan");
    arr[1].age = 20;
    arr[1].weight = 72;
    arr[1].gender = 'M';
    strcpy(arr[1].phonenumber, "9876543210");
    strcpy(arr[1].bloodgroup, "O+");

    strcpy(arr[2].name, "Arjun");
    arr[2].age = 18;
    arr[2].weight = 55;
    arr[2].gender = 'M';
    strcpy(arr[2].phonenumber, "98760003210");
    strcpy(arr[2].bloodgroup, "A+");

    strcpy(arr[3].name, "Tushar");
    arr[3].age = 20;
    arr[3].weight = 62;
    arr[3].gender = 'M';
    strcpy(arr[3].phonenumber, "9876543210");
    strcpy(arr[3].bloodgroup, "A+");

    strcpy(arr[4].name, "Muskan");
    arr[4].age = 14;
    arr[4].weight = 25;
    arr[4].gender = 'F';
    strcpy(arr[4].phonenumber, "9876543210");
    strcpy(arr[4].bloodgroup, "B+");

    strcpy(arr[5].name, "Payal");
    arr[5].age = 19;
    arr[5].weight = 45;
    arr[5].gender = 'F';
    strcpy(arr[5].phonenumber, "9876543210");
    strcpy(arr[5].bloodgroup, "B+");

    strcpy(arr[6].name, "Rajesh");
    arr[6].age = 25;
    arr[6].weight = 78;
    arr[6].gender = 'M';
    strcpy(arr[6].phonenumber, "9876543210");
    strcpy(arr[6].bloodgroup, "O+");

    strcpy(arr[7].name, "Rajesh");
    arr[7].age = 25;
    arr[7].weight = 78;
    arr[7].gender = 'M';
    strcpy(arr[7].phonenumber, "9876543210");
    strcpy(arr[7].bloodgroup, "AB");

    strcpy(arr[8].name, "Dron Modi");
    arr[8].age = 21;
    arr[8].weight = 78;
    arr[8].gender = 'M';
    strcpy(arr[8].phonenumber, "9876543210");
    strcpy(arr[8].bloodgroup, "O+");

    strcpy(arr[9].name, "Yash");
    arr[9].age = 21;
    arr[9].weight = 90;
    arr[9].gender = 'M';
    strcpy(arr[9].phonenumber, "9876543210");
    strcpy(arr[9].bloodgroup, "A+");

    strcpy(arr[10].name, "Uday");
    arr[10].age = 20;
    arr[10].weight = 58;
    arr[10].gender = 'M';
    strcpy(arr[10].phonenumber, "9876543210");
    strcpy(arr[10].bloodgroup, "B+");

    strcpy(arr[11].name, "Raman");
    arr[11].age = 55;
    arr[11].weight = 88;
    arr[11].gender = 'M';
    strcpy(arr[11].phonenumber, "9006543210");
    strcpy(arr[11].bloodgroup, "O-");

    // ASSIGNING DOCTOR DETAILS  IN A 2D ARRAY

    char doctors[20][2][40] = {

        // Example doctor names and types
        {"Dr. Smith", "Cardiologist"},
        {"Dr. Johnson", "Pediatrician"},
        {"Dr. Lee", "Dermatologist"},
        {"Dr. Brown", "Ophthalmologist"},
        {"Dr. Garcia", "Neurologist"},
        {"Dr. Rajesh", "Orthopedic"},
        {"Dr. Chandrashekhar", "Senior_Heart_Surgeon"},
        {"Dr. Olivia Rodriguez", "Cardiologist"},
        {"Dr. Marcus Thompson", "Orthopedic Surgeon"},
        {"Dr. Emily Chen", "Pediatrician"},
        {"Dr. Victor Ramirez", "Neurologist"},
        {"Dr. Harper Bennett", "Dermatologist"},
        {"Dr. Isaac Patel", "Gastroenterologist"},
        {"Dr. Sophia Reynolds", "Obstetrician/Gynecologist"},
        {"Dr. Nolan Foster", "Emergency_Medicine_Physician"},
        {"Dr. Clara Harper", "Pulmonologist"},
        {"Dr. Elijah Chang", "Ophthalmologist"},
        {"Dr. Maya Sharma", "Rheumatologist"},
        {"Dr. Samuel Wright", "Urologist"},
        {"Dr. Grace Foster", "Endocrinologist"}

        };

    // ASSIGNING MEDICINE DETAILS IN A 2D ARRAY
    char medicines[][2][50] = {
        "Aspirin",
        "Headache",

        "Ibuprofen",
        "Pain & Inflammation",

        "Acetaminophen",
        "Fever & Pain",

        "Amoxicillin",
        "Bacterial Infections",

        "Loratadine",
        "Allergies",

        "Omeprazole",
        "Acid Reflux",

        "Simvastatin",
        "High Cholesterol",

        "Metformin",
        "Diabetes",

        "Prednisone",
        "Inflammatory Conditions",

        "Hydrochlorothiazide",
        "High Blood Pressure",

        "Albuterol",
        "Asthma",

        "Warfarin",
        "Blood Clots",

        "Citalopram",
        "Depression",

        "Levothyroxine",
        "Hypothyroidism",

        "Losartan",
        "Kidney Problems",

        "Metoprolol",
        "Heart Conditions",

        "Atorvastatin",
        "Heart Disease",

        "Gabapentin",
        "Nerve Pain",

        "Furosemide",
        "Edema",

        "Fluoxetine",
        "Mental Health Disorders",

        "Diazepam",
        "Anxiety",
    };

    // ASSIGNING HOME REMEDIES WITH THEIR USAGE IN A 2D ARRAY
    char homeRemedies[][2][100] =
    {
        {"Ginger tea", "nausea"},
        {"Honey and Lemon", "sore_throat"},
        {"Honey and Lemon", "cough"},
        {"Apple cider vinegar", "indigestion"},
        {"Apple cider vinegar", "weight_loss"},
        {"Peppermint oil", "headaches"},
        {"Peppermint oil", "muscle_pain"},
        {"Aloe vera", "burns"},
        {"Garlic", "high_blood_pressure"},
        {"Garlic", "cholestrol"},
        {"Turmeric milk", "inflammation"},
        {"Turmeric milk", "joint_pain"},
        {"Chamomile tea", "insomnia"},
        {"Chamomile tea", "stress_relief"},
        {"Eucalyptus oil", "congestion"},
        {"Coconut oil", "dry_skin"},
        {"Cinnamon tea", " antioxidant"},
        {"Yogurt", "probiotics"},
        {"Oatmeal bath", "skin_itching"},
        {"Oatmeal bath", "eczema"},
        {"Lavender oil", "anxiety"},
        {"Baking soda", "oral_hygiene"},
        {"Onion syrup", "chest_congestion"},
        {"Onion syrup", "cold_relief"},
        {"Arnica", "pain"},
        {"Lemon balm", "cold_sores"},
        {"Lemon balm", "anxiety"},
        {"Tea tree oil", "acne"},
        {"Tea tree oil", "skin_infections"},
        {"Cherry juice", "joint_inflammation"},
        {"Cherry juice", "sleep aid"},
        {"Cranberry juice", "urinary_tract_infections"},
        {"Cranberry juice", "antioxidants"},
        {"Fennel seeds", "gas_relief"},
        {"Ginseng tea", "immune_support"},
        {"Hibiscus tea", "hypertension"},
        {"Hibiscus tea", "liver_health"},
        {"Mint tea", "stomach_upset"},
        {"Mint tea", "bad_breath"},
        {"Nettle tea", "allergies"},
        {"Nettle tea", "detoxification"},
        {"Rosemary oil", "hair_growth"},
        {"Sage tea", "menopausal "},
        {"Thyme tea", "cough"},
        {"Thyme tea", "respiratory_infections"},
        {"Valerian tea", "sleep_disorders"},
        {"Valerian tea", "stress_reduction"},
        {"Witch hazel", "skin_inflammation"},
        {"Green tea", "antioxidants"},
        {"Black tea bags", "sunburns"},
        {"Black tea bags", "puffy_eyes"},
        {"Mustard plaster", "chest_congestion "},
        {"Chia seeds", "fatty_acids"},
        {"Ginger ale", "motion_sickness"},
        {"Mullein tea", "asthma_relief"},
        {"Red clover tea", "menstrual_problems"},
        {"Red clover tea", "skin_health"},
    };

    // ASSIGNING DISEASES AND SYMPTOMS
    char diseases[30][60];
    char symptoms[30][5][60];
    strcpy(diseases[0], "Common_Cold");
    strcpy(symptoms[0][0], "Runny_nose");
    strcpy(symptoms[0][1], "Sneezing");
    strcpy(symptoms[0][2], "Cough");
    strcpy(symptoms[0][3], "Sore_throat");
    strcpy(symptoms[0][4], "Mild_fever");

    strcpy(diseases[1], "Influenza(Flu)");
    strcpy(symptoms[1][0], "High_fever");
    strcpy(symptoms[1][1], "Severe_body_aches");
    strcpy(symptoms[1][2], "Chills");
    strcpy(symptoms[1][3], "Fatigue");
    strcpy(symptoms[1][4], "Dry_cough");

    strcpy(diseases[2], "Asthma");
    strcpy(symptoms[2][0], "Shortness_of_breath");
    strcpy(symptoms[2][1], "Wheezing");
    strcpy(symptoms[2][2], "Chest_tightness");
    strcpy(symptoms[2][3], "Coughing");
    strcpy(symptoms[2][4], "Difficulty_sleeping");

    strcpy(diseases[3], "Diabetes");
    strcpy(symptoms[3][0], "Increased_thirst");
    strcpy(symptoms[3][1], "Frequent_urination");
    strcpy(symptoms[3][2], "Extreme_hunger");
    strcpy(symptoms[3][3], "Fatigue");
    strcpy(symptoms[3][4], "Blurry_vision");

    strcpy(diseases[4], "Hypertension (High Blood Pressure)");
    strcpy(symptoms[4][0], "Severe_headache");
    strcpy(symptoms[4][1], "Fatigue");
    strcpy(symptoms[4][2], "Vision_problems");
    strcpy(symptoms[4][3], "Chest_pain");
    strcpy(symptoms[4][4], "Difficulty_breathing");

    strcpy(diseases[5], "Anxiety");
    strcpy(symptoms[5][0], "Excessive_worrying");
    strcpy(symptoms[5][1], "Restlessness");
    strcpy(symptoms[5][2], "Trouble_concentrating");
    strcpy(symptoms[5][3], "Muscle_tension");
    strcpy(symptoms[5][4], "Panic_attacks");

    strcpy(diseases[6], "Depression");
    strcpy(symptoms[6][0], "Persistent_sadness");
    strcpy(symptoms[6][1], "Loss_of_interest ");
    strcpy(symptoms[6][2], "Fatigue");
    strcpy(symptoms[6][3], "oversleeping");
    strcpy(symptoms[6][4], "Feelings_of_guilt");

    strcpy(diseases[7], "Migraine");
    strcpy(symptoms[7][0], "Headache");
    strcpy(symptoms[7][1], "Nausea");
    strcpy(symptoms[7][2], "Vomitting");
    strcpy(symptoms[7][3], "Aura");
    strcpy(symptoms[7][4], "Faint");

    strcpy(diseases[8], "Arthritis");
    strcpy(symptoms[8][0], "Joint_pain");
    strcpy(symptoms[8][1], "Stiffness");
    strcpy(symptoms[8][2], "Swelling");
    strcpy(symptoms[8][3], "Redness");
    strcpy(symptoms[8][4], "Decreased_motion");

    strcpy(diseases[9], "Allergies");
    strcpy(symptoms[9][0], "Sneezing");
    strcpy(symptoms[9][1], "Runny_nose");
    strcpy(symptoms[9][2], "Itchy_eyes");
    strcpy(symptoms[9][3], "Skin_rash");
    strcpy(symptoms[9][4], "Swelling");

    strcpy(diseases[10], "Pneumonia");
    strcpy(symptoms[10][0], "High_fever");
    strcpy(symptoms[10][1], "Chest_pain");
    strcpy(symptoms[10][2], "Shortness_of_breath");
    strcpy(symptoms[10][3], "Cough");
    strcpy(symptoms[10][4], "Fatigue");

    strcpy(diseases[11], "Urinary Tract Infection (UTI)");
    strcpy(symptoms[11][0], "Burning_sensation_during_urination");
    strcpy(symptoms[11][1], "Frequent_urge_to_urinate");
    strcpy(symptoms[11][2], "Bloody urine");
    strcpy(symptoms[11][3], "Pelvic_pain(in women)");
    strcpy(symptoms[11][4], "Rectal_pain(in men)");

    strcpy(diseases[12], "Gastroenteritis");
    strcpy(symptoms[12][0], "Diarrhea");
    strcpy(symptoms[12][1], "Abdominal_cramps");
    strcpy(symptoms[12][2], "Nausea");
    strcpy(symptoms[12][3], "Vomiting");
    strcpy(symptoms[12][4], "Fever");

    strcpy(diseases[13], "Osteoporosis");
    strcpy(symptoms[13][0], "Back_pain");
    strcpy(symptoms[13][1], "Loss_of_height");
    strcpy(symptoms[13][2], "Stooped_posture");
    strcpy(symptoms[13][3], "Bone_fractures");
    strcpy(symptoms[13][4], "Difficulty_in_standing");

    strcpy(diseases[14], "Eczema");
    strcpy(symptoms[14][0], "Itchy_skin");
    strcpy(symptoms[14][1], "Dry_skin");
    strcpy(symptoms[14][2], "Red_skin");
    strcpy(symptoms[14][3], "Cracked skin");
    strcpy(symptoms[14][4], "Rashes");

    strcpy(diseases[15], "Gout");
    strcpy(symptoms[15][0], "Severe_joint_pain");
    strcpy(symptoms[15][1], "Swelling_and_redness");
    strcpy(symptoms[15][2], "Limited_range_of_motion");
    strcpy(symptoms[15][3], "Tenderness");
    strcpy(symptoms[15][4], "Warmth_in_the_affected_joint");

    strcpy(diseases[16], "Hepatitis");
    strcpy(symptoms[16][0], "Fatigue");
    strcpy(symptoms[16][1], "Abdominal_pain ");
    strcpy(symptoms[16][2], "Loss_of_appetite");
    strcpy(symptoms[16][3], "Jaundice_(yellowing of the skin and eyes)");
    strcpy(symptoms[16][4], "Dark_urine");

    strcpy(diseases[17], "Peptic Ulcer");
    strcpy(symptoms[17][0], "Burning_stomach_pain");
    strcpy(symptoms[17][1], "Nausea");
    strcpy(symptoms[17][2], "Vomiting");
    strcpy(symptoms[17][3], "Bloating");
    strcpy(symptoms[17][4], "Heartburn");

    strcpy(diseases[18], "Malaria");
    strcpy(symptoms[18][0], "Fever");
    strcpy(symptoms[18][1], "Chills");
    strcpy(symptoms[18][2], "Sweating");
    strcpy(symptoms[18][3], "Headache");
    strcpy(symptoms[18][4], "Vomiting");

    strcpy(diseases[19], "Celiac Disease");
    strcpy(symptoms[19][0], "Abdominal_pain");
    strcpy(symptoms[19][1], "Diarrhea");
    strcpy(symptoms[19][2], "Weight_loss");
    strcpy(symptoms[19][3], "Bloating");
    strcpy(symptoms[19][4], "Fatigue");

    strcpy(diseases[20], "Lupus");
    strcpy(symptoms[20][0], "Fatigue");
    strcpy(symptoms[20][1], "Joint_pain");
    strcpy(symptoms[20][2], "Rash");
    strcpy(symptoms[20][3], "Fever");
    strcpy(symptoms[20][4], "Chest_pain");

    strcpy(diseases[21], "Parkinson's Disease");
    strcpy(symptoms[21][0], "Tremors");
    strcpy(symptoms[21][1], "Bradykinesia");
    strcpy(symptoms[21][2], "Muscle_rigidity");
    strcpy(symptoms[21][3], "Impaired_balance");
    strcpy(symptoms[21][4], "Speech_changes");

    strcpy(diseases[22], "Fibromyalgia");
    strcpy(symptoms[22][0], "Muscle_pain");
    strcpy(symptoms[22][1], "Fatigue");
    strcpy(symptoms[22][2], "Sleep_disturbances");
    strcpy(symptoms[22][3], "Memory_issues");
    strcpy(symptoms[22][4], "Depression");

    strcpy(diseases[23], "Crohn's Disease");
    strcpy(symptoms[23][0], "Abdominal_pain");
    strcpy(symptoms[23][1], "Diarrhea");
    strcpy(symptoms[23][2], "Weight_loss");
    strcpy(symptoms[23][3], "Fatigue");
    strcpy(symptoms[23][4], "Fever");

    strcpy(diseases[24], "Endometriosis");
    strcpy(symptoms[24][0], "Pelvic_pain");
    strcpy(symptoms[24][1], "Heavy_menstrual_bleeding");
    strcpy(symptoms[24][2], "Pain_during_intercourse");
    strcpy(symptoms[24][3], "Infertility");
    strcpy(symptoms[24][4], "Fatigue");

    strcpy(diseases[25], "Chronic Obstructive Pulmonary Disease (COPD)");
    strcpy(symptoms[25][0], "Shortness_of_breath");
    strcpy(symptoms[25][1], "Cough");
    strcpy(symptoms[25][2], "Wheezing");
    strcpy(symptoms[25][3], "Chest_tightness");
    strcpy(symptoms[25][4], "Frequent_respiratory_infections");

    strcpy(diseases[26], "Hyperthyroidism");
    strcpy(symptoms[26][0], "Weight_loss");
    strcpy(symptoms[26][1], "Rapid_heartbeat");
    strcpy(symptoms[26][2], "Sweating");
    strcpy(symptoms[26][3], "Tremors");
    strcpy(symptoms[26][4], "Fatigue");

    strcpy(diseases[27], "HIV/AIDS");
    strcpy(symptoms[27][0], "Fever");
    strcpy(symptoms[27][1], "Fatigue");
    strcpy(symptoms[27][2], "Swollen_lymph_nodes");
    strcpy(symptoms[27][3], "Sore_throat");
    strcpy(symptoms[27][4], "Rash");

    strcpy(diseases[28], "Glaucoma");
    strcpy(symptoms[28][0], "Gradual loss of peripheral vision");
    strcpy(symptoms[28][1], "Blurred_vision");
    strcpy(symptoms[28][2], "Eye_pain");
    strcpy(symptoms[28][3], "Halos");
    strcpy(symptoms[28][4], "Vomiting");

    strcpy(diseases[29], "Hypothyroidism");
    strcpy(symptoms[29][0], "Weight_gain");
    strcpy(symptoms[29][1], "Fatigue");
    strcpy(symptoms[29][2], "Dry_skin");
    strcpy(symptoms[29][3], "Constipation");
    strcpy(symptoms[29][4], "Depression");

    // disease keywords :
    char disease[3][20];
    char symptom[3][5][60];

    strcpy(disease[0], "Common_Cold");
    strcpy(symptom[0][0], "Runny_nose");
    strcpy(symptom[0][1], "Sneezing");
    strcpy(symptom[0][2], "Cough");
    strcpy(symptom[0][3], "Sore_throat");
    strcpy(symptom[0][4], "Mild_fever");

    strcpy(disease[1], "Influenza(Flu)");
    strcpy(symptom[1][0], "High_fever");
    strcpy(symptom[1][1], "Severe_body_aches");
    strcpy(symptom[1][2], "Chills");
    strcpy(symptom[1][3], "Fatigue");
    strcpy(symptom[1][4], "Dry_cough");

    strcpy(disease[2], "Asthma");
    strcpy(symptom[2][0], "Shortness_of_breath");
    strcpy(symptom[2][1], "Wheezing");
    strcpy(symptom[2][2], "Chest_tightness");
    strcpy(symptom[2][3], "Coughing");
    strcpy(symptom[2][4], "Difficulty_sleeping");

    int patientCount = 0;
    printf("\n");
    printf("\n");
    printf(" |--------------------------------------------------------------------------------|\n");
    printf(" |--------------------------------------------------------------------------------|\n");
    printf(" |--------------------------------------------------------------------------------|\n");
    printf(" |                            Welcome to DIGO !!                                  |\n");
    printf(" |                           Your Online Doctor !!                                |\n");
    printf(" |--------------------------------------------------------------------------------|\n");
    printf(" |--------------------------------------------------------------------------------|\n");
    printf(" |--------------------------------------------------------------------------------|\n");

    // REGISTERING A NEW PATIENT
    //here we are storing the patients record in file
    //using file handing

    printf("\nDo you want to register as new patient ?  (Y/N) ----->  ");
    char choice;
    scanf("%c", &choice);

    if (choice == 'y' || choice == 'Y')
    {

        fputs("\n", nm);
        printf("\n Please Enter your details : ");
        printf("\n");

        //for store name in file
        fputs("\n", nm);
        printf("\n Enter your Name : ");
        scanf("%s", arr[patientCount].name);
        fprintf(nm,"%s","Name : ");
        fputs(arr[patientCount].name, nm);
        fputs("\n", nm);


        printf("\n Enter your age : ");

        //for store age in file
        scanf("%d", &arr[patientCount].age);
        fprintf(nm,"%s","Age : ");
        fprintf(nm, "%d", arr[patientCount].age);
        fputs("\n", nm);


        //for store weight in file
        printf("\n Enter your weight in Kg : ");
        scanf("%f", &arr[patientCount].weight);
        fprintf(nm,"%s","Weight : ");
        fprintf(nm, "%f", arr[patientCount].weight);
        fputs("\n", nm);


        printf("\n Enter your Gender : ");
        scanf("%s", &arr[patientCount].gender);

        //for store phone number in file
        printf("\n Enter your Phone Number : ");
        scanf("%s", arr[patientCount].phonenumber);
        fprintf(nm,"%s","Phone Number : ");
        fputs(arr[patientCount].phonenumber, nm);
        fputs("\n", nm);


        ////for store blood group in file
        printf("\n Enter your Blood Group : ");
        scanf("%s", arr[patientCount].bloodgroup);
        fprintf(nm,"%s","Blood Group : ");
        fputs(arr[patientCount].bloodgroup, nm);
        fputs("\n", nm);


        // patient registered successfully
        patientCount++;
        printf(" \n Patient registered successfully !!! \n");


        printf("\n Now choose any one of the options Below : \n");

        //Diagnose online with keywords :
        printf("1. Diagnose Online \n");

        // for get required home remedies :
        printf("2.Get Home Remedies \n");

        // To book a appointment with doctor
        printf("3.Doctor Appointment\n");

        //for order medicine :
        printf("4.Medicine Order \n");


        // Close the file
        fclose(nm);



        //Enter Your Choice
        int newpch;
        printf("\nEnter your Choice---> ");
        scanf("%d", &newpch);
        char symp1[60];
        char symp2[60];
        char symp3[60];
        char problem[20];

        if (newpch == 1)
        {
            // TAKING PATIENTS ANY THREE SYMPTOMS
            printf("Enter Any Three  Symptoms \n");

            //Input symptom 1
            printf("Symptom 1 : ");
            scanf("%s", symp1);

            printf("\n");

            //Input Symptom 2
            printf("Symptom 2 : ");
            scanf("%s", symp2);

            printf("\n");

            //Input Symptom 3
            printf("Symptom 3 : ");
            scanf("%s", symp3);

            for (int i = 0; i < 3; i++)
            {
                int mth = 0;
                for (int j = 0; j < 5; j++)
                {
                    if ((strcmp(symp1, symptoms[i][j]) == 0))
                    {
                        mth++;
                    }
                    if ((strcmp(symp2, symptoms[i][j]) == 0))
                    {
                        mth++;
                    }
                    if ((strcmp(symp3, symptoms[i][j]) == 0))
                    {
                        mth++;
                    }
                }
                if (mth >= 3)
                {
                    printf("\nThe disease you might be suffering is %s with all symptoms : \n", diseases[i]);
                    for (int k = 0; k < 5; k++)
                    {
                        printf("%s \n", symptoms[i][k]);
                    }
                }
                else if (mth == 2)
                {
                    printf("\nThe disease you might be suffering is %s with all symptoms : \n", diseases[i]);
                    for (int k = 0; k < 5; k++)
                    {
                        printf("%s \n", symptoms[i][k]);
                    }
                }
            }
        }

        else if (newpch == 2)
        {

            // GETTING HOME REMEDIES FOR THE GIVEN DISEASE
            printf("Please Enter Problem  :");
            scanf("%s", problem);

            for (int i = 0; i <= 51; i++)
            {
                int c = strcmp(problem, homeRemedies[i][1]);
                if (c == 0)
                {
                    printf("%s should be used for %s \n", homeRemedies[i][0], homeRemedies[i][1]);
                }
            }
        }

        else if (newpch == 3)
        {


            // DOCTOR APPOINMENT
            printf("Please Select any one of The doctors from below : \n");
            for (int i = 0; i < 20; i++)
            {
                printf("Doctor %d--->%s  (%s) \n", i + 1, doctors[i][0], doctors[i][1]);
                printf("\n");
            }


            int dch;
            printf("Enter your Choice : ");
            scanf("%d", &dch);
            printf(" Your appointment is set with %s next Wednesday ", doctors[dch - 1][0]);
            printf("\n");
            printf("Please Be Present by sharp 10 am ");
            printf("\n");
            printf("\n");
        }
        else if (newpch == 4)
        {

            // ORDER MEDICINE
            //Entering Problem Faced by user
            printf("Please Enter Problem  : ");
            scanf("%s", problem);


            for (int i = 0; i <= 51; i++)
            {
                int c = strcmp(problem, medicines[i][1]);
                if (c == 0)
                {
                     //printing list of Medicines and problems
                    printf("%s should be used for %s \n", medicines[i][0], medicines[i][1]);

                    int qnt;
                    //Enter quantity of medicines
                    printf("Enter  quantity :");
                    scanf("%d", &qnt);

                    // printing Successful vorder
                    printf("Order of %s of %d strips placed successfully!!!!", medicines[i][0], qnt);
                    printf(" \n Hope you Get soon early !!\n");
                }
            }
        }
    }


    else if (choice == 'N' || choice == 'n')

    {
        int rech;
        int pn;

        printf("Do you want to Check your Records ? ( 1 for yes / 0 for No ) --->");

        printf("( 1 for yes / 0 for No ) ---> ");

        scanf("%d", &rech);

        if (rech == 1)
        {
            printf("Enter your Patient no. --> ");
            scanf("%d", &pn);

            printf("Patient details as follows : \n");

            //Displaying Name
            printf("%s\n", arr[pn].name);

            //Displaying age
            printf("%d\n", arr[pn].age);

            //Displaying Weight
            printf("%f\n", arr[pn].weight);

            //displaying Gender
            printf("%c\n", arr[pn].gender);

            //Displaying Phonenumber
            printf("%s\n", arr[pn].phonenumber);

            //displaying blood group
            printf("%s\n", arr[pn].bloodgroup);
        }
    }
}




// End of Source Code
