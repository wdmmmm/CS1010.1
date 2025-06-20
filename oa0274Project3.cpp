#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
//#include "getNumber.cpp"
//#include "oa0274Project3_header.h"
using namespace std;

// I dont know how to split this into the 3 files, every include combination did not work and I was unable to find any helpful notes from this class on it.


const int SIZE = 5; //num of tests per student
enum eMenu {Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit = 6};
eMenu menuNum;
int i,j,k;

struct Student
{
 string name;
 int id;
 int testsTaken;
 int* scores = new int[SIZE];
 double avg;

};

int getNumber()
{
 ifstream fin;
 fin.open("student.dat");
 if (fin.fail())
 {
  cout<<"File error."<<endl;
  exit(1);
 }
 int count=0;
 string line;
 while(getline(fin, line), !fin.eof())
  {
   count = count + 1;
//   cout << "count: " << count << endl;
  }

 fin.close();
 cout << "Number of students = " << count << endl;
 return(count);

}


void addStudent()
{
 Student sOne;
 string name2;
 string sep = ",";

 ofstream output;
 output.open("student.dat", fstream::app);

 if (!output.is_open()) {
  cout << "Failed to open file" << endl;
  exit(1);
 }

 string kill = " ";
 getline(cin, kill);

 cout << "Enter last name of the student:";
 getline(cin, sOne.name);

// getline(cin, kill);

 cout << "Enter first name of the student:";
 getline(cin, name2);

 sOne.name += sep;
 sOne.name += name2;

 cout << "Enter student ID:";
 cin >> sOne.id;
 cout << "How many tests did this student take?";
 cin >> sOne.testsTaken;

 for (i = 0; i < sOne.testsTaken; i++) {
  cout << "Enter Score #" << i+1 << ":";
  cin >> sOne.scores[i];
 }

 output << sOne.name << "," << sOne.id << "," << sOne.testsTaken << ",";

 for (i = 0; i < sOne.testsTaken; i++) {
  output << sOne.scores[i] << ",";
 }

 output << endl;

 delete[] sOne.scores;
 output.close();
}

void removeStudent(int studentID)
{
 int numStudents;
 numStudents = getNumber();
 int n;
 string temp;
 string temp2;

// cout << "Check 1" << endl;

 Student* lines = new Student[numStudents];

 ifstream input;
 input.open("student.dat");

 if (!input.is_open()) {
  cout << "Failed to open file" << endl;
  exit(1);
 }

 bool idFound = false;
 string digitFind = "0123456789";

 //cout << "Check 2" << endl;

 for (i = 0; i < numStudents; i++) {
  getline(input, temp);
  size_t found = temp.find_first_of(digitFind);

  lines[i].name = temp.substr(0, found);
  temp2 = temp.substr(found);

  //cout << "temp2: " <<temp2 << endl;

  int len = temp2.length();

  for (k = 0; k < len; k++) {
   if (temp2[k] == ',') {
    temp2[k] = ' ';
   }
  }

  istringstream iss(temp2);

  iss >> lines[i].id >> lines[i].testsTaken;

  //cout << "name: " << lines[i].name << endl << "id: " << lines[i].id << endl << "tests: " << lines[i].testsTaken << endl;

  if (studentID == lines[i].id) {
   idFound = true;
   n = i;
  }


  for (j = 0; j < lines[i].testsTaken; j++) {
   iss >> lines[i].scores[j];
   //cout << "Test number #" << j << ":" <<  lines[i].scores[j] << endl;
  }
  j = 0;

 }

 input.close();

 if (idFound == true) {
  ofstream output;
  output.open("student.dat");

  if (!output.is_open()) {
   cout << "Failed to open file" << endl;
   exit(1);
  }

  for (i = 0; i < numStudents; i++) {
   if (i != n) {
    output << lines[i].name << lines[i].id << ',' << lines[i].testsTaken << ',';

    for (j = 0; j < lines[i].testsTaken; j++) {
     output << lines[i].scores[j] << ',';
    }
    j = 0;
    output << endl;
   }
  }
 output.close();
 }
 else {
  cout << "Student does not exist." << endl;
 }

 delete[] lines;
}

void display()
{
 ifstream input;
 input.open("student.dat");

 if (!input.is_open()) {
  cout << "Failed to open file" << endl;
  exit(1);
 }

 int numStudents = getNumber();
 Student* lines;
 lines = new Student[numStudents];
 string temp, temp2;

 string digitFind = "0123456789";

 for (i = 0; i < numStudents; i++) {
  getline(input, temp);
  size_t found = temp.find_first_of(digitFind);

  lines[i].name = temp.substr(0, found);
  lines[i].name.pop_back(); 

  temp2 = temp.substr(found);

  int len = temp2.length();

  for (k = 0; k < len; k++) {
   if (temp2[k] == ',') {
    temp2[k] = ' ';
   }
  }

  istringstream iss(temp2);

  iss >> lines[i].id >> lines[i].testsTaken;

  cout << setw(30) << lines[i].name << setw(15) << lines[i].id;

  for (j = 0; j < lines[i].testsTaken; j++) {
   iss >> lines[i].scores[j];
   cout << setw(5) << lines[i].scores[j];
  }
  j = 0;
  cout << endl;
 }

 input.close();
 delete[] lines;
}

void search(int studentID)
{
 Student* searchID = new Student;
 int numStudents = getNumber();
 bool foundID = false;

 ifstream input;
 input.open("student.dat");

 if (!input.is_open()) {
  cout << "Failed to open file" << endl;
  exit(1);
 }

 string temp, temp2;
 string digitFind = "0123456789";

 for (i = 0; i < numStudents; i++) {
  getline(input, temp);
  size_t found = temp.find_first_of(digitFind);

  searchID->name = temp.substr(0, found);
  searchID->name.pop_back();

  temp2 = temp.substr(found);

  int len = temp2.length();

  for (k = 0; k < len; k++) {
   if (temp2[k] == ',') {
    temp2[k] = ' ';
   }
  }

  istringstream iss(temp2);

  iss >> searchID->id >> searchID->testsTaken;

  if (studentID == searchID->id) {
   cout << setw(30) << searchID->name << setw(15) << searchID->id;

   for (j = 0; j < searchID->testsTaken; j++) {
    iss >> searchID->scores[j];
    cout << setw(5) << searchID->scores[j];
   }
   j = 0;
   cout << endl;
   foundID = true;
  }
 }

 if (foundID == false) {
  cout << "Student does not exist. " << endl;
 }

 searchID = nullptr;
 input.close();
 delete[] searchID;


}

int findMinimum(Student lines[])
{
 int min;
 //cout << "tests: " << lines[i].testsTaken << endl;

 if (lines[i].testsTaken == 5) {
  min = lines[i].scores[0];
 // cout << "min2min:" << min  << " inside score:" << lines[i].scores[0] << endl;

  for (k = 0; k < lines[i].testsTaken; k++) {
   if (lines[i].scores[k] < min) {
    min = lines[i].scores[k];
   // cout << "kmin:" << k << " " << min << endl;
   }
  }
 }
 if (lines[i].testsTaken <= 4) {
  min = 0;
  return min;
 }

 lines[i].testsTaken = lines[i].testsTaken - 1;
 return min;
}


void exportResults()
{
 ifstream input;
 ofstream output;
 input.open("student.dat");
 output.open("averages.dat");
 if ((!input.is_open()) || (!output.is_open())) {
  cout << "Failed to open files" << endl;
  exit(1);
 }

 int numStudents = getNumber();
 Student* lines;
 lines = new Student[numStudents];
 string temp, temp2;
 int sum = 0;
 int min;
 string digitFind = "0123456789";

 for (i = 0; i < numStudents; i++) {
  getline(input, temp);
  size_t found = temp.find_first_of(digitFind);

  lines[i].name = temp.substr(0, found);
  lines[i].name.pop_back();

  temp2 = temp.substr(found);

  int len = temp2.length();

  for (k = 0; k < len; k++) {
   if (temp2[k] == ',') {
    temp2[k] = ' ';
   }
  }

  istringstream iss(temp2);

  iss >> lines[i].id >> lines[i].testsTaken;

 // cout << setw(30) << lines[i].name << setw(15) << lines[i].id;

  for (j = 0; j < lines[i].testsTaken; j++) {
   iss >> lines[i].scores[j];

   sum = sum + lines[i].scores[j];
   //cout << setw(5) << lines[i].scores[j];
  }
  min = findMinimum(lines);
  //cout << "index 3 out score: " << lines[i].scores[j] << endl;
  //cout << "index 0 out score: " << lines[i].scores[0] << endl;
  sum = sum - min;
  //cout << "Min:" << min << " sum:" << sum << endl;

  lines[i].avg = static_cast<double>(sum) / lines[i].testsTaken;

  output << lines[i].id << "\t" << fixed << setprecision(1) << lines[i].avg << endl;

  j = 0;
  sum = 0;
  cout << endl;
 }

 cout << "Results exported to file" << endl;

 input.close();
 output.close();
 delete[] lines;
}

int main( )
{
 /* Author: Michael Ajayi (OlumideAjayi@my.unt.edu)
 Date: 4/10/25
 Instructor: Dr Maharjan
 Description: This program keeps track of grades of students using structures
and files.
 */

 int menuInput;
 int studentID;
 bool cont = true;

 do {
  cout << endl << "1. Add" << endl << "2. Remove" << endl << "3. Display" << endl << "4. Search" << endl << "5. Results" << endl << "6. Quit" << endl;

  cout << "Enter your choice: ";
  cin >> menuInput;

  menuNum = static_cast<eMenu>(menuInput);

  switch(menuNum) {
   case Add:
    addStudent();

    break;

   case Remove:
    cout << "Enter ID of student to remove:";
    cin >> studentID;
    removeStudent(studentID);

    break;
   case Display:
    display();

    break;
   case Search:
    cout << "Enter ID of student to search:";
    cin >> studentID;
    search(studentID);

    break;
   case Results:
    exportResults();

    break;
   case Quit:
    cout << "Goodbye." << endl;
    cont = false;

    break;
   default:
    cout << "Incorrect choice. Please enter again." << endl;
  }
 }
 while ((cont == true));


}
