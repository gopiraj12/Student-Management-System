#include <bits/stdc++.h>
using namespace std;

// -------------------- PATIENT --------------------
class Patient {
public:
    int id;
    string name;
    int age;
    string disease;
    int priority;     // 1 to 5 (5 = highest)
    int arrivalTime;

    Patient() {}

    Patient(int i, string n, int a, string d, int p, int t) {
        id = i;
        name = n;
        age = a;
        disease = d;
        priority = p;
        arrivalTime = t;
    }
};

// Comparator for Priority Queue
class ComparePatient {
public:
    bool operator()(Patient &a, Patient &b) {
        if (a.priority == b.priority)
            return a.arrivalTime > b.arrivalTime; // earlier first
        return a.priority < b.priority; // higher priority first
    }
};

// -------------------- DOCTOR --------------------
class Doctor {
public:
    int id;
    string name;
    bool available;

    Doctor(int i, string n) {
        id = i;
        name = n;
        available = true;
    }
};

// -------------------- EMERGENCY ROOM --------------------
class EmergencyRoom {
private:
    priority_queue<Patient, vector<Patient>, ComparePatient> pq;
    unordered_map<int, Patient> records;
    vector<Doctor> doctors;

    int currentTime = 0;
    int patientId = 1;
    int doctorId = 1;

public:
    // Add Doctor
    void addDoctor(string name) {
        doctors.push_back(Doctor(doctorId++, name));
        cout << "Doctor Added Successfully!\n";
    }

    // Add Patient
    void addPatient(string name, int age, string disease, int priority) {
        Patient p(patientId++, name, age, disease, priority, currentTime);
        pq.push(p);
        records[p.id] = p;
        cout << "Patient Added Successfully!\n";
    }

    // Assign Doctor
    void assignDoctor() {
        for (auto &doc : doctors) {
            if (doc.available && !pq.empty()) {
                Patient p = pq.top();
                pq.pop();
                doc.available = false;

                cout << "Doctor " << doc.name 
                     << " treating Patient " << p.name 
                     << " (Priority " << p.priority << ")\n";
            }
        }
    }

    // Show Waiting Patients
    void showPatients() {
        if (pq.empty()) {
            cout << "No patients waiting.\n";
            return;
        }

        auto temp = pq;
        while (!temp.empty()) {
            Patient p = temp.top();
            cout << "ID: " << p.id
                 << " Name: " << p.name
                 << " Priority: " << p.priority << endl;
            temp.pop();
        }
    }

    // Search Patient by ID
    void searchPatient(int id) {
        if (records.find(id) != records.end()) {
            Patient p = records[id];
            cout << "Patient Found: " << p.name
                 << ", Disease: " << p.disease << endl;
        } else {
            cout << "Patient Not Found!\n";
        }
    }
};

// -------------------- MAIN --------------------
int main() {
    EmergencyRoom er;
    int choice;

    while (true) {
        cout << "\n---- Emergency Room Menu ----\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Patient\n";
        cout << "3. Assign Doctor\n";
        cout << "4. Show Waiting Patients\n";
        cout << "5. Search Patient\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string name;
            cout << "Doctor Name: ";
            cin >> name;
            er.addDoctor(name);
            break;
        }
        case 2: {
            string name, disease;
            int age, priority;
            cout << "Patient Name: ";
            cin >> name;
            cout << "Age: ";
            cin >> age;
            cout << "Disease: ";
            cin >> disease;
            cout << "Priority (1-5): ";
            cin >> priority;
            er.addPatient(name, age, disease, priority);
            break;
        }
        case 3:
            er.assignDoctor();
            break;
        case 4:
            er.showPatients();
            break;
        case 5: {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            er.searchPatient(id);
            break;
        }
        default:
            cout << "Invalid Choice!\n";
        }
    }

    return 0;
}
