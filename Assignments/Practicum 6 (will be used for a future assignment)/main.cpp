#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct StudentRecord {
    int id;
    string name;
    float gpa;
};

// Function to add a new student record to the binary file
void addStudentRecord(fstream& file) {
    StudentRecord student;
    cout << "Enter Student ID: ";
    cin >> student.id;
    // You can add data validation here to ensure unique IDs.
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter GPA: ";
    cin >> student.gpa;
    // You can add GPA validation here.

    file.write(reinterpret_cast<char*>(&student), sizeof(StudentRecord));
}

// Function to search for a student's record by ID
void searchStudentRecord(fstream& file, int targetId) {
    StudentRecord student;
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&student), sizeof(StudentRecord))) {
        if (student.id == targetId) {
            cout << "Student ID: " << student.id << endl;
            cout << "Name: " << student.name << endl;
            cout << "GPA: " << student.gpa << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

// Function to implement random access to the file using ID
void randomAccessStudentRecord(fstream& file, int targetId) {
    StudentRecord student;
    file.seekg((targetId - 1) * sizeof(StudentRecord), ios::beg);
    file.read(reinterpret_cast<char*>(&student), sizeof(StudentRecord));
    cout << "Student ID: " << student.id << endl;
    cout << "Name: " << student.name << endl;
    cout << "GPA: " << student.gpa << endl;
}

// Function to sort the records based on ID
void sortRecordsByID(fstream& file) {
    vector<StudentRecord> records;
    file.seekg(0, ios::beg);
    while (file) {
        StudentRecord student;
        file.read(reinterpret_cast<char*>(&student), sizeof(StudentRecord));
        if (file) {
            records.push_back(student);
        }
    }

    sort(records.begin(), records.end(), [](const StudentRecord& a, const StudentRecord& b) {
        return a.id < b.id;
    });

    file.close();
    file.open("student_records.dat", ios::out | ios::binary);
    
    for (const StudentRecord& student : records) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(StudentRecord));
    }
}

int main() {
    fstream file("student_records.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cerr << "File could not be opened." << endl;
        return 1;
    }

    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add a New Student Record" << endl;
        cout << "2. Search for a Student" << endl;
        cout << "3. Random Access" << endl;
        cout << "4. Sort Records by ID" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                addStudentRecord(file);
                break;
            case '2':
                int searchId;
                cout << "Enter Student ID to search: ";
                cin >> searchId;
                searchStudentRecord(file, searchId);
                break;
            case '3':
                int accessId;
                cout << "Enter Student ID for random access: ";
                cin >> accessId;
                randomAccessStudentRecord(file, accessId);
                break;
            case '4':
                sortRecordsByID(file);
                cout << "Records sorted by ID." << endl;
                break;
            case '5':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != '5');

    file.close();

    return 0;
}
