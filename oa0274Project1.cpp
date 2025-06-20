#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cctype>
#include <stdio.h>
#include <cstdlib>
using namespace std;
int main( )
{
 /* Author: Michael Ajayi (OlumideAjayi@my.unt.edu)
 Date: 3/2/25
 Instructor: Dr Maharjan
 Description: This program is a game that involves guessing the sum and
difference of two randomly generated numbers.
 */

 cout << endl << "Computer Science and Engineering" << endl << "CSCE 1030 - Computer Science I" << endl << "Michael Ajayi OA0274 oa0274@my.unt.edu" << endl << endl;

 int points = 100;
 bool cont = true;
 int guess;
 int result;
 char cont2;
 bool display = false;

 enum eMenu {Add = 1, Subtract = 2, Display = 3, Giveup = 4, Exit = 5};

 eMenu menuNum;
 int menuInput;
 int i;

 int lowR;
 int highR = 0;

 string name;

 cout << "Enter your name: ";
 getline(cin, name);

 for (i = 0; i < name.length(); i++) {
  while ((isalpha(name.at(i)) == false) && (isspace(name.at(i)) == false)) {
   cout << "Your name can only have alphabets or spaces. Enter again." << endl;
   getline(cin, name);
   i = 0;
  }
 }

 name.at(0) = toupper(name.at(0));

 for (i = 0; i < name.length(); ++i) {
  if (isspace(name.at(i))) {
   name.at(i+1) = toupper(name.at(i+1));
  }
 }

 cout << "Welcome " << name << "." << endl;

 srand(time(NULL));

 lowR = (rand() % 50) + 100;

 while (highR <= lowR) {
  highR = (rand() % 51) + 100;
 }

 cout << "Your two random numbers have been generated." << endl;


 do {
  cout << endl << "1. ADD" << endl << "2. SUBTRACT" << endl << "3. DISPLAY" << endl << "4. GIVEUP" << endl << "5. EXIT" << endl;

  cout << "Enter your choice: ";
  cin >> menuInput;

  menuNum = static_cast<eMenu>(menuInput);

  switch(menuNum) {
   case Add:
    cout << "Enter your guess sum: ";
    cin >> guess;
    result = lowR + highR;

    if ((guess > result - 5) && (guess < result + 5)) {
     points = points + 5;
     cout << "Your guess is close enough. You win. Your updated points are: " << points << endl;
     cout << "Do you want to restart the game? Y/N: ";
     cin >> cont2;
     cont2 = tolower(cont2);

     while ((cont2 != 'y') && (cont2 != 'n')) {
       cout << "You must enter Y/N. " << endl;
       cin >> cont2;
       cont2 = tolower(cont2);
      }

     if (cont2 == 'y') {
      lowR = (rand() % 50) + 100;
      highR = (rand() % 51) + 100;
      while (highR <= lowR) {
       highR = (rand() % 51) + 100;
      }
      points = 100;
      display = false;
      cout << "Your two random numbers have been generated. " << endl;
     }
     else if (cont2 == 'n') {
      cont = false;
      cout << "Your final points are: " << points << endl;
      cout << "Goodbye, " << name << endl;
     }
    }
    else {
     points = points - 1;
     cout << "Wrong guess" << endl;
     cout << "Your updated points are: " << points << endl;
    }
    break;
   case Subtract:
    cout << "Enter your guess difference: ";
    cin >> guess;
    result = highR - lowR;

    if ((guess > result - 5) && (guess < result + 5)) {
     points = points + 5;
     cout << "Your guess is close enough. You win. Your updated points are: " << points << endl;
     cout << "Do you want to restart the game? Y/N: ";
     cin >> cont2;
     cont2 = tolower(cont2);

     while ((cont2 != 'y') && (cont2 != 'n')) {
       cout << "You must enter Y/N. " << endl;
       cin >> cont2;
       cont2 = tolower(cont2);
      }

     if (cont2 == 'y') {
      lowR = (rand() % 50) + 100;
      highR = (rand() % 51) + 100;
      while (highR <= lowR) {
       highR = (rand() % 51) + 100;
      }
      points = 100;
      display = false;
      cout << "Your two random numbers have been generated. " << endl;
     }
     else if (cont2 == 'n') {
      cont = false;
      cout << "Your final points are: " << points << endl;
      cout << "Goodbye, " << name << endl;
     }
    }
    else {
     points = points - 1;
     cout << "Wrong guess" << endl;
     cout << "Your updated points are: " << points << endl;
    }
    break;
   case Display:
    if (display == false) {
     points = points - 3;
     display = true;
     cout << "Your updated points are: " << points << endl;
     cout << "The first random number is " << lowR << endl;
    }
    else {
     cout << "You have already displayed the first number. " << endl << "The first random number is " << lowR << endl;
    }
    break;
   case Giveup:
    cout << "The two random numbers were " << lowR << " and " << highR << "." << endl;

    cout << "Do you want to restart the game? Y/N: ";
    cin >> cont2;
    cont2 = tolower(cont2);

    while ((cont2 != 'y') && (cont2 != 'n')) {
     cout << "You must enter Y/N. " << endl;
     cin >> cont2;
     cont2 = tolower(cont2);
    }
    if (cont2 == 'y') {
      lowR = (rand() % 50) + 100;
      highR = (rand() % 51) + 100;
      while (highR <= lowR) {
       highR = (rand() % 51) + 100;
      }
      points = 100;
      display = false;
      cout << "Your two random numbers have been generated. " << endl;
     }
     else if (cont2 == 'n') {
      cont = false;
      cout << "Your final points are: " << points << endl;
      cout << "Goodbye, " << name << endl;
     }

    break;
   case Exit:
    cout << "Your final points are: " << points << endl << "Goodbye, " << name << endl;
    cont = false;
    break;
   default:
    cout << "Wrong choice. Please enter again" << endl;
  }
 }
 while ((points >= 0) && (cont == true));
}

