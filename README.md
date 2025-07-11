# Medical Diagnostic System

⚠️ **IMPORTANT MEDICAL DISCLAIMER** ⚠️  
**This is an educational project for programming practice only. Do NOT use this for actual medical decisions. Always consult qualified healthcare professionals for real medical advice, diagnosis, and treatment.**

---

## 🚀 Quick Setup & Run

### 1. **Get the Project**

```bash
git clone https://github.com/gouravslnk/Medical-Diagnostic-System.git
cd Medical-Diagnostic-System
```

### 2. **Build & Run**

```bash
# Build using Makefile (recommended)
mingw32-make

# Run the application
.\bin\medical_system.exe

# Or build manually if needed
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -o medical_system main.c src/*/*.c
```

### 3. **First Login**

- **Default Admin Account:**
  - Username: `admin`
  - Password: `admin123`
- **⚠️ IMPORTANT:** Change the default password after first login!

---

## 📁 Project Structure

```text
Medical-Diagnostic-System/
├── src/                             # Source Code Modules
│   ├── auth/
│   │   └── auth.c                   # Authentication System
│   ├── patient/
│   │   └── patient.c                # Patient Management
│   ├── diagnosis/
│   │   └── diagnosis.c              # Diagnosis Engine
│   ├── appointments/
│   │   └── appointments.c           # Appointment System
│   ├── medicines/
│   │   └── medicines.c              # Medicine Management
│   ├── remedies/
│   │   └── remedies.c               # Home Remedies
│   ├── ui/
│   │   └── ui.c                     # User Interface
│   └── utils/
│       └── utils.c                  # Utility Functions
├── include/                         # Header Files
│   ├── common.h                     # Common Definitions
│   ├── auth.h                       # Authentication Headers
│   ├── patient.h                    # Patient Management Headers
│   ├── diagnosis.h                  # Diagnosis System Headers
│   ├── appointments.h               # Appointment Headers
│   ├── medicines.h                  # Medicine Headers
│   ├── remedies.h                   # Remedies Headers
│   ├── ui.h                         # UI Headers
│   └── utils.h                      # Utility Headers
├── data/                            # Data Storage (Auto-Generated)
│   ├── users.txt                    # User Database
│   ├── session.txt                  # Active Sessions
│   ├── activity.log                 # System Activity Log
│   ├── patients.txt                 # Patient Records
│   ├── appointments.txt             # Appointment Records
│   ├── medicines.txt                # Medicine Inventory
│   ├── orders.txt                   # Medicine Orders
│   └── remedies.txt                 # Home Remedies Database
├── bin/                             # Executables
│   └── medical_system.exe           # Main Application
├── obj/                             # Object Files (Build Artifacts)
├── main.c                           # Main Application Entry
├── Makefile                         # Build Configuration
└── README.md                        # Project Documentation
```

---

**Educational C Programming Project - Not for real medical use!**
