#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>

using namespace std;

// Define a base class Student with attributes for Student ID, Name, and GPA.
class Student 
{
    public:
        int id;
        string name;
        float gpa;

        // Constructor to initialize Student attributes
        Student(int id, const string& name, float gpa) : id(id), name(name), gpa(gpa) {}
};

// Define a derived class GraduateStudent that inherits from the base class Student.
class GraduateStudent : public Student 
{
    public:
        string researchTopic;

        // Constructor to initialize GraduateStudent attributes, including ResearchTopic.
        GraduateStudent(int id, const string& name, float gpa, const string& researchTopic)
            : Student(id, name, gpa), researchTopic(researchTopic) {}
};

// Define a templated data structure (class) for managing the student database.
template <typename T>
class StudentDatabase 
{
    public:
        StudentDatabase() 
        {
            loaded = false;
        }

        ~StudentDatabase() 
        {
            if (loaded) 
            {
                saveDataToFile("students.dat");
            }
        }

        // Function to add a student to the database
        void addStudent(const T& student) 
        {
            students.push_back(student);
        }

        // Function to delete a student from the database based on Student ID
        void deleteStudent(int studentId) 
        {
            auto it = std::remove_if(students.begin(), students.end(),
                [studentId](const T& student) 
                { return student.id == studentId; });
            if (it != students.end()) 
            {
                students.erase(it, students.end());
            } else 
            {
                throw invalid_argument("Student not found.");
            }
        }

        // Function to search for a student by their ID
        T searchStudent(int studentId) 
        {
            for (const T& student : students) 
            {
                if (student.id == studentId) 
                {
                    return student;
                }
            }
            throw invalid_argument("Student not found.");
        }

        // Function to sort students using the Quick Sort algorithm based on their Student ID
        void quicksortStudents() 
        {
            quicksort(students, 0, students.size() - 1);
        }

        void quicksort(vector<T>& students, int low, int high) 
        {
            if (low < high) 
            {
                int pivotIndex = partition(students, low, high);
                quicksort(students, low, pivotIndex - 1);
                quicksort(students, pivotIndex + 1, high);
            }
        }

        int partition(vector<T>& students, int low, int high) 
        {
            T pivot = students[high];
            int i = low - 1;
            for (int j = low; j < high; j++) 
            {
                if (students[j].id < pivot.id) 
                {
                    i++;
                    swap(students[i], students[j]);
                }
            }
            swap(students[i + 1], students[high]);
            return i + 1;
        }

        // Function to save the data to a file
        void saveDataToFile(const string& filename) 
        {
            if (file.is_open()) 
            {
                file.close();
            }
            file.open(filename);
            if (file) 
            {
                for (const T& student : students)
                {
                    // Save student information to the file, using '\t' as a delimiter
                    file << student.id << '\t' << student.name << '\t' << student.gpa << endl;
                }
                file.close();
            } else 
            {
                throw runtime_error("Failed to save data to the file.");
            }
        }

        // Function to load data from a file
        void loadDataFromFile(const string& filename) 
        {
            if (file.is_open()) 
            {
                file.close();
            }
            file.open(filename);
            if (file) 
            {
                students.clear(); // Clear existing data

                while (file) 
                {
                    int id;
                    string name;
                    float gpa;

                    file >> id;  // Read student ID
                    file.ignore();   // Consume the delimiter (tab character)
                    getline(file, name, '\t');  // Read student name until the tab character
                    file >> gpa;  // Read student GPA

                    if (typeid(T) == typeid(GraduateStudent)) 
                    {
                        string researchTopic;
                        file.ignore();   // Consume the delimiter (tab character)
                        getline(file, researchTopic, '\t');  // Read research topic until the tab character
                        students.push_back(GraduateStudent(id, name, gpa, researchTopic));
                    } else 
                    {
                        students.push_back(Student(id, name, gpa));
                    }
                }
                file.close();
                loaded = true;
            } else 
            {
                throw runtime_error("Failed to load data from the file.");
            }
        }

        // Function to shuffle the order of students randomly
        void shuffleStudents() 
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(students.begin(), students.end(), g);
        }

        // Function to display all students and their details
        void displayAllStudents() 
        {
            for (const T& student : students) 
            {
                cout << "Student ID: " << student.id << endl;
                cout << "Name: " << student.name << endl;
                cout << "GPA: " << student.gpa << endl;
                if (typeid(T) == typeid(GraduateStudent)) 
                {
                    const GraduateStudent& gradStudent = static_cast<const GraduateStudent&>(student);
                    cout << "Research Topic: " << gradStudent.researchTopic << endl;
                }
                cout << "--------------------------------" << endl;
            }
        }

        // Function to edit a student's GPA
        void editStudentGPA(int studentId, float newGPA) 
        {
            for (T& student : students) 
            {
                if (student.id == studentId) 
                {
                    student.gpa = newGPA;
                    return;
                }
            }
            throw invalid_argument("Student not found.");
        }

        // Function to close the file
        void close() 
        {
            file.close();
        }

    private:
        vector<T> students;
        fstream file;
        bool loaded;
};

int main() 
{
    // Create a StudentDatabase for regular students
    StudentDatabase<Student> regularStudents;

    try 
    {
        // Load student data from a file
        regularStudents.loadDataFromFile("students.dat");

        char choice;
        string newName;
        float newGPA;

        do 
        {
            cout << "Menu:" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Search Student" << endl;
            cout << "4. Shuffle Students" << endl;
            cout << "5. Display All Students" << endl;
            cout << "6. Edit Student GPA" << endl;
            cout << "7. Sort Students" << endl;
            cout << "8. Save Data to File" << endl;
            cout << "9. Load Data from File" << endl;
            cout << "0. Exit" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            if (choice >= '1' && choice <= '6') 
            {
                cin.ignore();
            }

            switch (choice) 
            {
                case '1':
                    int newId;

                    cout << "Enter Student ID: ";
                    cin >> newId;
                    cin.ignore();
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

                    try 
                    {
                        regularStudents.deleteStudent(deleteId);
                        cout << "Student with ID " << deleteId << " deleted." << endl;
                    } catch (const invalid_argument& e) 
                    {
                        cerr << e.what() << endl;
                    }
                    break;

                case '3':
                    int searchId;
                    cout << "Enter Student ID to search: ";
                    cin >> searchId;

                    try 
                    {
                        Student foundStudent = regularStudents.searchStudent(searchId);
                        cout << "Student ID: " << foundStudent.id << endl;
                        cout << "Name: " << foundStudent.name << endl;
                        cout << "GPA: " << foundStudent.gpa << endl;
                    } catch (const invalid_argument& e) 
                    {
                        cerr << e.what() << endl;
                    }
                    break;

                case '4':
                    regularStudents.shuffleStudents();
                    cout << "Students shuffled." << endl;
                    break;

                case '5':
                    regularStudents.displayAllStudents();
                    break;

                case '6':
                    int editId;
                    float newGPA;

                    cout << "Enter Student ID to edit GPA: ";
                    cin >> editId;
                    cout << "Enter new GPA: ";
                    cin >> newGPA;

                    try 
                    {
                        regularStudents.editStudentGPA(editId, newGPA);
                        cout << "Student GPA edited successfully." << endl;
                    } catch (const invalid_argument& e) 
                    {
                        cerr << e.what() << endl;
                    }
                    break;

                case '7':
                    regularStudents.quicksortStudents();
                    cout << "Students sorted by ID using quicksort." << endl;
                    break;

                case '8':
                    regularStudents.saveDataToFile("students.dat");
                    cout << "Data saved to file." << endl;
                    break;

                case '9':
                    try 
                    {
                        regularStudents.loadDataFromFile("students.dat");
                        cout << "Data loaded from file." << endl;
                    } catch (const exception& e) 
                    {
                        cerr << "An error occurred: " << e.what() << endl;
                    }
                    break;

                case '0':
                    cout << "Exiting program." << endl;
                    break;

                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != '0');
    } catch (const exception& e) 
    {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
