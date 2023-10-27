#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Student {
public:
    int id;
    string name;
    float gpa;

    Student(int id, const string& name, float gpa) : id(id), name(name), gpa(gpa) {}
};

class GraduateStudent : public Student {
public:
    string researchTopic;

    GraduateStudent(int id, const string& name, float gpa, const string& researchTopic)
        : Student(id, name, gpa), researchTopic(researchTopic) {}
};

template <typename T>
class StudentDatabase {
public:
    StudentDatabase() {
        loaded = false;
    }

    ~StudentDatabase() {
        if (loaded) {
            saveDataToFile("students.dat");
        }
    }

    void addStudent(const T& student) {
        students.push_back(student);
    }

    void deleteStudent(int studentId) {
        auto it = std::remove_if(students.begin(), students.end(),
            [studentId](const T& student) { return student.id == studentId; });
        if (it != students.end()) {
            students.erase(it, students.end());
        } else {
            throw invalid_argument("Student not found.");
        }
    }

    T searchStudent(int studentId) {
        for (const T& student : students) {
            if (student.id == studentId) {
                return student;
            }
        }
        throw invalid_argument("Student not found.");
    }

    void quicksortStudents() {
        quicksort(students, 0, students.size() - 1);
    }

    void quicksort(vector<T>& students, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(students, low, high);
            quicksort(students, low, pivotIndex - 1);
            quicksort(students, pivotIndex + 1, high);
        }
    }

    int partition(vector<T>& students, int low, int high) {
        T pivot = students[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (students[j].id < pivot.id) {
                i++;
                swap(students[i], students[j]);
            }
        }
        swap(students[i + 1], students[high]);
        return i + 1;
    }

    void saveDataToFile(const string& filename) {
        if (file.is_open()) {
            file.close();
        }
        file.open(filename);
        if (file) {
            for (const T& student : students) {
                file << student.id << " " << student.name << " " << student.gpa << endl;
            }
            file.close();
        } else {
            throw runtime_error("Failed to save data to the file.");
        }
    }

    void loadDataFromFile(const string& filename) {
        if (file.is_open()) {
            file.close();
        }
        file.open(filename);
        if (file) {
            T student;
            students.clear(); // Clear existing data
            while (file >> student.id >> student.name >> student.gpa) {
                students.push_back(student);
            }
            file.close();
            loaded = true;
        } else {
            throw runtime_error("Failed to load data from the file.");
        }
    }

    void close() {
        if (file.is_open()) {
            file.close();
        }
    }

private:
    vector<T> students;
    fstream file;
    bool loaded;
};

int main() {
    StudentDatabase<Student> regularStudents;

    try {
        regularStudents.loadDataFromFile("students.dat");

        char choice;
        do {
            cout << "Menu:" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Search Student" << endl;
            cout << "4. Sort Students" << endl;
            cout << "5. Save Data to File" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            cin.ignore(); // Clear the newline character

            switch (choice) {
                case '1':
                    int newId;
                    string newName;
                    float newGPA;

                    cout << "Enter Student ID: ";
                    cin >> newId;
                    cin.ignore(); // Consume newline character
                    cout << "Enter Name: ";
                    getline(cin, newName);
                    cout << "Enter GPA: ";
                    cin >> newGPA;

                    regularStudents.addStudent(Student(newId, newName, newGPA));
                    cout << "Student added successfully." << endl;
                    break;

                case '2':
                    int deleteId;
                    cout << "Enter Student ID to delete: ";
                    cin >> deleteId;

                    try {
                        regularStudents.deleteStudent(deleteId);
                        cout << "Student with ID " << deleteId << " deleted." << endl;
                    } catch (const invalid_argument& e) {
                        cerr << e.what() << endl;
                    }
                    break;

                case '3':
                    int searchId;
                    cout << "Enter Student ID to search: ";
                    cin >> searchId;

                    try {
                        Student foundStudent = regularStudents.searchStudent(searchId);
                        cout << "Student ID: " << foundStudent.id << endl;
                        cout << "Name: " << foundStudent.name << endl;
                        cout << "GPA: " << foundStudent.gpa << endl;
                    } catch (const invalid_argument& e) {
                        cerr << e.what() << endl;
                    }
                    break;

                case '4':
                    regularStudents.quicksortStudents();
                    cout << "Students sorted by ID using quicksort." << endl;
                    break;
                case '5':
                    regularStudents.saveDataToFile("students.dat");
                    cout << "Data saved to file." << endl;
                    break;
                case '6':
                    cout << "Exiting program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != '6');
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
