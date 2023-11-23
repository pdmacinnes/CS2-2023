#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <cstdlib>
// #include <algorithm>

using namespace std;

// Custom implementation of a dynamic array
template <typename T>
class DynamicArray 
{
public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    ~DynamicArray() 
    {
        delete[] data;
    }

    void push_back(const T& value) 
    {
        if (size >= capacity) {
            reserve(capacity * 2 + 1);
        }
        data[size++] = value;
    }

    void erase(int index) 
    {
        if (index < 0 || index >= size) 
        {
            throw out_of_range("Index out of bounds.");
        }
        for (int i = index; i < size - 1; ++i) 
        {
            data[i] = data[i + 1];
        }
        --size;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) 
        {
            throw out_of_range("Index out of bounds.");
        }
        return data[index];
    }

    const T& operator[](int index) const 
    {
        if (index < 0 || index >= size) 
        {
            throw out_of_range("Index out of bounds.");
        }
        return data[index];
    }

    int getSize() const 
    {
        return size;
    }

private:
    void reserve(int newCapacity) 
    {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) 
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    T* data;
    int size;
    int capacity;
};

class MyString 
{
public:
    char* data;
    int strLength; // Changed 'length' to 'strLength'

    MyString() : data(nullptr), strLength(0) {}

    MyString(const char* value) 
    {
        strLength = strlen(value);
        data = new char[strLength + 1];
        strcpy(data, value);
    }

    MyString(const MyString& other) : strLength(other.strLength) 
    {
        data = new char[strLength + 1];
        strcpy(data, other.data);
    }

    MyString& operator=(const MyString& other) 
    {
        if (this != &other) 
        {
            delete[] data;
            strLength = other.strLength;
            data = new char[strLength + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    ~MyString() 
    {
        delete[] data;
    }

    char& operator[](int index) 
    {
        if (index < 0 || index >= strLength) 
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return data[index];
    }

    const char& operator[](int index) const 
    {
        if (index < 0 || index >= strLength) 
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return data[index];
    }

    int strlength() const 
    {
        return strLength;
    }
};


// Define a base class Student with attributes for Student ID, Name, and GPA.
class Student 
{
public:
    int id;
    MyString name;
    float gpa;

    Student() : id(0), name(""), gpa(0.0f) {}

    Student(int id, const std::string& name, float gpa) : id(id), name(name.c_str()), gpa(gpa) {}

    Student(const Student& other) : id(other.id), name(other.name), gpa(other.gpa) {}

    Student& operator=(const Student& other) 
    {
        if (this != &other) 
        {
            id = other.id;
            name = other.name;
            gpa = other.gpa;
        }
        return *this;
    }

    ~Student() {}
};



// Define a derived class GraduateStudent that inherits from the base class Student.
class GraduateStudent : public Student 
{
public:
    MyString researchTopic;

    // Constructor to initialize GraduateStudent attributes, including ResearchTopic.
    GraduateStudent(int id, const char* name, float gpa, const char* researchTopic)
    : Student(id, name, gpa), researchTopic() 
    {
    this->researchTopic = MyString(researchTopic);
    }
};

// Custom implementation of a templated data structure for managing the student database.
template <typename T>
class StudentDatabase 
{
public:
    StudentDatabase()
        : students(), file(), loaded(false) {}

    ~StudentDatabase() 
    {
        if (loaded) {
            saveDataToFile("students.dat");
        }
    }

    void addStudent(const T& student) 
    {
        students.push_back(student);
    }

    void deleteStudent(int studentId) 
    {
        int index = findStudentIndex(studentId);
        if (index != -1) 
        {
            students.erase(index);
        } else 
        {
            throw invalid_argument("Student not found.");
        }
    }

    T searchStudent(int studentId) const 
    {
        int index = findStudentIndex(studentId);
        if (index != -1) 
        {
            return students[index];
        } else {
            throw invalid_argument("Student not found.");
        }
    }

    void quicksortStudents() 
    {
        quicksort(0, students.getSize() - 1);
    }

    void shuffleStudents() 
    {
        int n = students.getSize();
        for (int i = n - 1; i > 0; --i) 
        {
            int j = rand() % (i + 1); // Generate a random index
            swap(students[i], students[j]); // Swap elements at index i and j
        }
    }

    void displayAllStudents() const 
    {
        for (int i = 0; i < students.getSize(); ++i) 
        {
            const T& student = students[i];
            cout << "Student ID: " << student.id << endl;
            cout << "Name: " << student.name[0] << endl; // Assuming single character names
            cout << "GPA: " << student.gpa << endl;
            if (typeid(T) == typeid(GraduateStudent)) 
            {
                const GraduateStudent& gradStudent = static_cast<const GraduateStudent&>(student);
                cout << "Research Topic: " << gradStudent.researchTopic[0] << endl;
            }
            cout << "--------------------------------" << endl;
        }
    }

    void editStudentGPA(int studentId, float newGPA) 
    {
        int index = findStudentIndex(studentId);
        if (index != -1) 
        {
            students[index].gpa = newGPA;
        } else {
            throw invalid_argument("Student not found.");
        }
    }

    void saveDataToFile(const char* filename) const 
    {
    FILE* file = fopen(filename, "wb");
    if (file == nullptr) 
    {
        throw runtime_error("Unable to open file.");
    }

    int size = students.getSize();
    fwrite(&size, sizeof(int), 1, file);

    for (int i = 0; i < size; ++i) 
    {
        fwrite(&students[i].id, sizeof(int), 1, file);

        int nameLength = students[i].name.strlength(); // Get length using MyString's size() method
        fwrite(&nameLength, sizeof(int), 1, file);

        // Write each character of MyString to the file
        for (int j = 0; j < nameLength; ++j) 
        {
            fwrite(&students[i].name[j], sizeof(char), 1, file);
        }

        fwrite(&students[i].gpa, sizeof(float), 1, file);
    }

    fclose(file);
}


    void loadDataFromFile(const char* filename) 
    {
        FILE* file = fopen(filename, "rb"); // Open file in binary read mode
        if (file == nullptr) 
        {
            throw runtime_error("Unable to open file.");
        }

        int size;
        fread(&size, sizeof(int), 1, file); // Read the number of students

        for (int i = 0; i < size; ++i) 
        {
            int id;
            fread(&id, sizeof(int), 1, file); // Read student ID

            int nameLength;
            fread(&nameLength, sizeof(int), 1, file); // Read name length

            char* name = new char[nameLength + 1];
            fread(name, sizeof(char), nameLength, file); // Read name
            name[nameLength] = '\0';

            float gpa;
            fread(&gpa, sizeof(float), 1, file); // Read GPA

            addStudent(T(id, name, gpa)); // Add student to the database

            delete[] name;
        }

        fclose(file); // Close the file
    }

private:
    DynamicArray<T> students;
    fstream file;
    bool loaded;

    int findStudentIndex(int studentId) const 
    {
        for (int i = 0; i < students.getSize(); ++i) 
        {
            if (students[i].id == studentId) 
            {
                return i;
            }
        }
        return -1;
    }

    void quicksort(int low, int high) 
    {
        if (low < high) 
        {
            int pivotIndex = partition(low, high);
            quicksort(low, pivotIndex - 1);
            quicksort(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) 
    {
        T pivot = students[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) 
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input stream
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
                        cout << "Name: " << foundStudent.name.data << endl;
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