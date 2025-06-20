#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstring>
#include <unistd.h>
using namespace std;
 enum eMenu {Match = 1, Display = 2, Giveup = 3, Exit = 4};
 eMenu menuNum;
 bool showReal = false;

 int i,j,k;

 const int SIZE = 4;

string getName(string name)
{
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

 return name;

}
int genRandomIndex()
{
 return (rand() % SIZE);
}
void shuffle(int cards[][SIZE])
{
 int x1,x2,y1,y2,t;

 for (i = 0; i < 15; i++) {
  x1 = genRandomIndex();
  y1 = genRandomIndex();
  x2 = genRandomIndex();
  y2 = genRandomIndex();
  t = cards[x1][y1];
  cards[x1][y1] = cards[x2][y2];
  cards[x2][y2] = t;

 }
}
void initialize(int cards[][SIZE], int cardsFace[][SIZE], int SIZE, int points)
{
 int n = 1;
 points = 50;

 for (i = 0; i < SIZE; i++) {
  for (j = 0; j < SIZE; j++) {
   if (j % 2 != 0) {
    cards[i][j] = n;
    cards[i][j-1] = n;
    n++;
   }
  }
 }

 for (i = 0; i < SIZE; i++) {
  for (j = 0; j < SIZE; j++) {
   cardsFace[i][j] = 0;
  }
 }

 shuffle(cards);
}
void showCards(int cards[][SIZE], int cardsFace[][SIZE], bool showReal)
{

 if (showReal == true) {
  cout << "    0" << "\t" << "1" << "\t" << "2" << "\t" << "3" << "\t" << endl;
  cout << "-------------------------" << endl;

  for (i = 0; i < SIZE; i++) {
   cout << i << " | ";
   for (j = 0; j < SIZE; j++) {
    cout << cards[i][j] << "\t";
   }
   cout << endl;
  }
 }
 else {
  cout << "    0" << "\t" << "1" << "\t" << "2" << "\t" << "3" << "\t" << endl;
  cout << "-------------------------" << endl;

  for (i = 0; i < SIZE; i++) {
   cout << i << " | ";
   for (j = 0; j < SIZE; j++) {
    if (cardsFace[i][j] == 1) {
     cout << cards[i][j] << "\t";
    }
    else {
     cout << "*" << "\t";
    }
   }
   cout << endl;
  }
 }

}
bool allFaceUp(int cardsFace[][SIZE])
{
 bool faceUp;

 for (i = 0; i < SIZE; i++) {
  for (j = 0; j < SIZE; j++) {
   if (cardsFace[i][j] != 1) {
    return false;
   }
  }
 }

 return true;
}
bool checkInputs(int x1, int x2, int y1, int y2, int cardsFace[][SIZE], int SIZE)
{
 if ( ( (x1 >= 0) && (x1 <= (SIZE-1)) ) &&  ( (x2 >= 0) && (x2 <= (SIZE-1)) ) &&  ( (y1 >= 0) && (y1 <= (SIZE-1)) ) &&  ( (y2 >= 0) && (y2 <= (SIZE-1)) )  ) {
  if ((cardsFace[x1][y1] == 0) && (cardsFace[x2][y2] == 0)) {
   return true;
  }
  else {
   cout << "One of these cards is already faced up." << endl;
   return false;
  }
 }

 cout << "Invalid coordinates." << endl;
 return false;
}
int match(int cards[][SIZE], int cardsFace[][SIZE], int points)
{
 showCards(cards, cardsFace, showReal);
 int x1,x2,y1,y2;

 cout << "Enter coordinate for the first card: ";
 cin >> x1 >> y1;
 cout << "Enter coordinate for the second card: ";
 cin >> x2 >> y2;

 if (checkInputs(x1,x2,y1,y2, cardsFace, SIZE) == false) {
  return points;
 }

 if ((x1 == x2) && (y1 == y2)) {
  cout << "Coordinates should not match." << endl;
  return points;
 }

 if (cards[x1][y1] == cards[x2][y2]) {
  cardsFace[x1][y1] = 1;
  cardsFace[x2][y2] = 1;
  points = points + 5;
  cout << "Cards match at locations: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << endl;
  cout << "Your updated points are: " << points << endl;

  return points;
 }
 else {
  cardsFace[x1][y1] = 1;
  cardsFace[x2][y2] = 1;

  cout << "Cards do not match at locations: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << endl;
  points = points - 1;
  cout << "Your updated points are: " << points << endl;

  showCards(cards, cardsFace, showReal);
  sleep(5);
  system("clear");
  cardsFace[x1][y1] = 0;
  cardsFace[x2][y2] = 0;

  return points;
 }
 return points;
}
int display(int cards[][SIZE], int cardsFace[][SIZE], int points)
{
 if (points < 10) {
  cout << "You do not have enough points to perform this action. " << endl;
  return points;
 }

 int n;
 bool found = false;

 for (i = 0; i < SIZE; i++) {
  for (j = 0; j < SIZE; j++) {
   if (found == false) {
    if (cardsFace[i][j] == 0) {
     n = cards[i][j];
     cardsFace[i][j] = 1;
     found = true;
    }
   }
   else {
    if (n == cards[i][j]) {
     cardsFace[i][j] = 1;
    }
   }
  }
 }

 showCards(cards, cardsFace, showReal);

 points = points - 10;
 cout << "Your updated points are: "  << points << endl;
 return points;

}
int main( )
{
 /* Author: Michael Ajayi (OlumideAjayi@my.unt.edu)
 Date: 4/6/25
 Instructor: Dr Maharjan
 Description: This program is a memory matching game.
 */
 cout << endl << "Computer Science and Engineering" << endl << "CSCE 1030 - Computer Science I" << endl << "Michael Ajayi OA0274 oa0274@my.unt.edu" << endl << endl;

 srand(time(NULL));

 int menuInput;
 int points = 50;

 int cards[SIZE][SIZE];
 int cardsFace[SIZE][SIZE];

 string name;
 char choice;
 bool cont = true;

 name = getName(name);
 cout << "Welcome " << name << "." << endl;

 initialize(cards, cardsFace, SIZE, points);

// match(cards, cardsFace, points);

 do {
  cout << endl << "1. MATCH" << endl << "2. DISPLAY" << endl << "3. GIVEUP" << endl << "4. EXIT" << endl;

  cout << "Enter your choice: ";
  cin >> menuInput;

  menuNum = static_cast<eMenu>(menuInput);

  switch(menuNum) {
   case Match:
    points = match(cards, cardsFace, points);
    if (allFaceUp(cardsFace) == true) {
     cout << "You have won the game. Do you want to play another? (Y/N)";
     cin >> choice;
     choice = tolower(choice);

     while ((choice != 'y') && (choice != 'n')) {
      cout << "You must enter Y/N. " << endl;
      cin >> choice;
      choice = tolower(choice);
     }

     if (choice == 'y') {
      initialize(cards, cardsFace, SIZE, points);
     }
     else if (choice == 'n') {
      cont = false;
      cout << "Your final points are: " << points << endl;
      cout << "Goodbye, " << name << endl;
     }
    }

    break;

   case Display:
    points = display(cards, cardsFace, points);

    break;
   case Giveup:
    showReal = true;

    cout << "Location of cards were: " << endl;

    showCards(cards,cardsFace,showReal);
    cout << "Do you want to restart the game? Y/N: ";

    cin >> choice;
    choice = tolower(choice);

    while ((choice != 'y') && (choice != 'n')) {
     cout << "You must enter Y/N. " << endl;
     cin >> choice;
     choice = tolower(choice);
    }

    if (choice == 'y') {
     initialize(cards, cardsFace, SIZE, points);
    }
    else if (choice == 'n') {
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
