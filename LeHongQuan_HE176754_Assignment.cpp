#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <limits>

using namespace std;

// Struct to represent a student's information
struct Student {
    string name;
    int age;
};

// Function to add a new student to the list
void createStudent(const string& filename, const string& name, int age) {
    ofstream file(filename, ios::app);
    file << name << "," << age << "\n";
    cout << "This student was added successfully.\n";
    file.close();
}

// Function to read the entire list of students from the file
vector<Student> readStudents(const string& filename) {
    ifstream file(filename);
    vector<Student> students;
    set<string> seenNames; // Set to store names that have been seen

    string line;
    while (getline(file, line)) {
        if (!line.empty()) { // Remove blank lines
            size_t pos = line.find(",");
            string name = line.substr(0, pos);
            int age = stoi(line.substr(pos + 1));
            if (age != 0 && seenNames.find(name) == seenNames.end()) {
                students.push_back({name, age});
                cout << "Name: " << name << ", Age: " << age << "\n";
                seenNames.insert(name); // Add name to set of seen names
            }
        }
    }
    file.close();
    return students;
}

// Function to update a student's information
void updateStudent(const string& filename, const string& name, int newAge) {
    ifstream file(filename);
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        string studentName = line.substr(0, line.find(","));
        if (studentName == name) {
            temp << name << "," << newAge << "\n";
            cout << "This student was updated successfully.\n";
            found = true;
        } else {
            temp << line << "\n";
        }
    }
    file.close();
    temp.close();
    if (!found) {
        cout << "No student named " << name << "\n";
    } else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}

// Function to delete a student's information
void deleteStudent(const string& filename, const string& name) {
    ifstream file(filename);
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        string studentName = line.substr(0, line.find(","));
        if (studentName != name) {
            temp << line << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    if (!found) {
        cout << "No student named " << name << "\n";
    } else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "This student was removed successfully.\n";
    }
}

int main() {
    const string filename = "students.txt";

    while (true) {
        cin.clear();
        cout << "\nSelect operation:\n";
        cout << "1. Add a student\n";
        cout << "2. Read the student list\n";
        cout << "3. Update student information\n";
        cout << "4. Remove a student\n";
        cout << "5. Exit\n";

        int choice;
        cin >> choice;
        
        // Clear the cache and ignore remaining characters in the cache
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string name;
                int age;
                cout << "Enter student name: ";
                getline(cin >> ws, name); // Ignore whitespace
                cout << "Enter student age: ";
                cin >> age;
                createStudent(filename, name, age);
                break;
            }
            case 2: {
                vector<Student> students = readStudents(filename);
                break;
            }
            case 3: {
                string name;
                int newAge;
                cout << "Enter the name of the student to update: ";
                getline(cin >> ws, name);
                cout << "Enter new age: ";
                cin >> newAge;
                updateStudent(filename, name, newAge);
                break;
            }
            case 4: {
                string name;
                cout << "Enter the name of the student to remove: ";
                getline(cin >> ws, name);
                deleteStudent(filename, name);
                break;
            }
            case 5: {
                return 0;
            }
            default:
                cout << "Invalid selection. Please select again.\n";
        }
    }

    return 0;
}

