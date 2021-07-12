//
//  Project 1 recommendations
//  Description: Program recommends items to users given
//  to a file with ratings and a file with items.
//  The user can get either basic or advanced recommendations.
//  Creative component: User can make an admin which
//  gives access to commands like delete user and delete item
//  Created by:
//  Sai Samarth, U of Illinois, Chicago,
//  CS 251: Spring 2021
//  Project #01

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ourvector.h"

using namespace std;

//
// getRatings (string s);
// Function returns an int ourvector filled with ratings
// given a string of ratings.
// The function converts individual numbers from the string into int.
//
// Return type: ourvector<int>;
//
ourvector<int> getRatings(string s) {
    stringstream ss;
    ourvector<int> output;
    string input, temp;
    int num;
       ss << s;
       while (!ss.eof()) {
           ss >> temp;
           // checks if the current input from string is a number
           if (stringstream(temp) >> num) {
               output.push_back(num);
           }
           temp = "";
       }
return output;
}
//
// checkLogin (bool& l, string user);
// Checks and prints the user logged in.
//
// Return type: NONE;
//
void checkLogin(bool& l, string user) {
    if (l) {
        cout << "\n" << "Logged in as: " << user << endl;
    } else {
        cout << "\n" << "Logged in as: N/A" << endl;
    }
}
//
// checkAdmin (bool& isAdmin, bool& l, string user, string admin);
// Prints the admin if there is one
//
// Return type: NONE;
//
void checkAdmin(bool& isAdmin, bool& l, string user, string admin) {
    if (isAdmin) {
        cout << "\n" << "Admin: " << admin;
    }
    checkLogin(l, user);
}
// loadItems (string i, ourvector<string>& items);
// Loads the items into the item ourvector
// Return type: NONE;
void loadItems(string i, ourvector<string>& items) {
    ifstream itemsFile(i);
    string item;
    getline(itemsFile, item);
    cout << "\n" << "Reading items file..." << endl;
    if (itemsFile.good()) {
        while (!itemsFile.eof()) {
            cout << item << endl;
            // prints the items
            items.push_back(item);
            getline(itemsFile, item);
        }
    } else {
        cout << "file not found" << endl;
    }
    
}
// loadRatings (string rFile, ourvector<string>& names,
// ourvector<ourvector<int>>& rating);
// Loads the ratings and names into the ourvectors.
// Return type: NONE ;
void loadRatings(string rFile, ourvector<string>& names,
ourvector<ourvector<int> >& rating) {
    ifstream ratingsFile(rFile);
    string name, ratingNum, full;
    cout << "\n" << "Reading ratings file..." << endl;
    if (ratingsFile.good()) {
        while (!ratingsFile.eof()) {
            getline(ratingsFile, name);
            if (name != "") {
            names.push_back(name);
            getline(ratingsFile, ratingNum);
            rating.push_back(getRatings(ratingNum));
            }
        }
    } else {
        cout << "file not found" << endl;
    }
    // loop to print the user and their respective ratings
    for (int i = 0; i < names.size(); i++) {
       // cout << names.at(i) << endl;
        if (names.at(i) != "") {
        cout << names.at(i) << endl;
        for (int j = 0; j < rating[i].size(); j++) {
            cout << rating[i].at(j) << " ";
        }
        }
      cout << endl;
    }
}
// login (string user, string admin, ourvector<string>& items,
// ourvector<string> names, ourvector<ourvector<int>>& rating,
// bool& l, bool& isAdmin);
// Function logs in the given user if he/she is part of the vector.
// Prints an error message if the user is not found.
// Return type: NONE;
void login(string user, string admin, ourvector<string>& items,
ourvector<string>& names, ourvector<ourvector<int> >& rating,
bool& l, bool& isAdmin) {
  for (int i = 0; i < names.size(); i++) {
      if (user == names.at(i)) {
          cout << "\n" << "Success.";
          l = true;
          if (user == admin) {
              cout << "\n"
                   << "******* New admin created *******" << endl;
              cout << "Admin Functions:" << endl;
              cout << "1. Type \"delete item\" to delete item" << endl;
              cout << "2. Type \"delete user\" to delete user" << endl;
              cout << "3. Type \"remove admin\" to remove admin privileges" << endl;
          }
          break;
      } else {
          l = false;
      }
}
if (!l) {
    cout << "\n" << "User not found, please try again.";
}
checkAdmin(isAdmin, l, user, admin);
}
//
// show (string user, ourvector<string>& items, ourvector<string>& names,
// ourvector<ourvector<int>>& rating, bool& l);
// Function shows the ratings of the given user
// Return type: NONE ;
void show(string user, ourvector<string>& items, ourvector<string>& names,
ourvector<ourvector<int> >& rating, bool& l) {
    cout << "\n" << user << "'s Ratings:" << endl;
    int row;
    // loop to find the user, breaks right after finding the user.
    for (int i = 0; i < names.size(); i++) {
        if (user == names.at(i)) {
            row = i;
            break;
        }
    }
    // prints the rating along with the name of the item
    for (int j = 0; j < rating[row].size(); j++) {
        if (rating[row].at(j) != 0) {
            cout << items.at(j) << ", " << rating[row].at(j) << "/5" << endl;
        }
    }
}
//
// basicAverage (int num, ourvector<ourvector<int>>& rating);
// 
// Function calculates the average ratings of every user for
// the given item number
//
// Return type: double;
double basicAverage(int num, ourvector<ourvector<int> >& rating) {
    double avg = 0;
    int sum = 0;
    int count = 0;
    for (int j = 0; j < rating.size(); j++) {
                sum += rating[j].at(num);
                count++;
    }
    avg = (double)(sum)/count;
    return avg;
}
// findUser (string user, ourvector<string>& names);
// Function finds the index of the given user from the ourvector names
// Return type: int;
int findUser(string user, ourvector<string>& names) {
    int num;
    for (int i = 0; i < names.size(); i++) {
        if (user == names.at(i)) {
            num = i;
            break;
        }
    }
    return num;
}
//
// averageVec (int num, ourvector<double>& averages,
// ourvector<ourvector<int>>& rating, ourvector<string>& items);
// Function pushes the averages found into an ourvector called
// averages, which is passed by reference.
// Return type: NONE ;
void averageVec(int num, ourvector<double>& averages,
ourvector<ourvector<int> >& rating, ourvector<string>& items) {
    for (int j = 0; j < rating[num].size(); j++) {
        // finds the averages of ratings that the user hasn't rated
        if (rating[num].at(j) == 0) {
            averages.push_back(basicAverage(j, rating));
        } else {
            // push back -6.0 if the user already rated the item
            averages.push_back(-6.0);
        }
    }
}
// basic (string user, ourvector<string>& items,
// ourvector<string>& names, ourvector<ourvector<int>>& rating, bool& l);
// Function suggests the top 5 items of the user based
// on the highest averages
// Return type: NONE;
void basic(string user, ourvector<string>& items,
ourvector<string>& names, ourvector<ourvector<int> >& rating, bool& l) {
    ourvector<double> averages;
    int num;
    cout << "\n" << "Basic recommendations:" << endl;
    num = findUser(user, names);
    averageVec(num, averages, rating, items);
    double max;
    int index, r;
    int c = 0;
    max = averages.at(0);
    for (int m = 0; m < 5; m++) {
        r = 0;
        index = 0;
        while (r < averages.size()) {
                if (averages.at(r) != -6.0) {
            if (max < averages.at(r)) {
                max = averages.at(r);
                index = r;
            }
                }
                r++;
            }
        if (max == -6.0) {
           if (rating[num].at(index) == 0) {
              cout << items.at(index) << endl;
              c++;
           }
        } else {
        averages.at(index) = -7.0;
        cout << items.at(index) << endl;
        c++;
        max = averages.at(0);
        }
    }
    // averages.clear();
}
// printItems (ourvector<string>& items);
// Function prints the items from the ourvector items and numbers them
// Return type: NONE;
void printItems(ourvector<string>& items) {
    cout << endl;
    int count = 0;
    for (int i = 0; i < items.size(); i++) {
        // checks if the item is not an empty string
        if (items.at(i) != " ") {
           cout << count << ". " << items.at(i) << endl;
           count++;
        } else {
        }
    }
}
// printUsers (purvector<string>& users);
// Function prints the users from the ourvector users
// Return type: NONE;
void printUsers(ourvector<string>& users) {
    cout << endl;
    for (int i = 0; i < users.size(); i++) {
        // checks if the user is not an empty string
        if (users.at(i) != " ") {
       cout << users.at(i) << endl;
        }
    }
}
// addUser (string user, ourvector<string>& names,
// ourvector<ourvector<int>>& rating, bool& l, int num);
// Function adds the given user to the ourvector names and 
// logs the user in. The user will have a rating of 0 for all items
// Return type: NONE;
void addUser(string user, ourvector<string>& names,
ourvector<ourvector<int> >& rating, bool& l, int num) {
    names.push_back(user);
    string s = "";
    for (int i = 0; i < num; i++) {
        s = s + " 0 "; 
    }
    // pushes back an ourvector with ratings of 0s
    rating.push_back(getRatings(s));
    l = true;
    cout << "Logged in as: " << user << endl;
}
// addRating (string user, int iNum, int rNum,
// ourvector<string>& names, ourvector<ourvector<int>>& rating, bool& l);
// Function is responsible for adding a new rating
// Return type: NONE;
void addRating(string user, int iNum, int rNum,
ourvector<string>& names, ourvector<ourvector<int> >& rating, bool& l) {
    int loc;
    for (int i = 0; i < names.size(); i++) {
        if (user == names.at(i)) {
            loc = i;
            break;
        }
    }
    
    rating[loc][iNum] = rNum;
}
// dotProduct (ourvector<int> person1, ourvector<int> person2);
// Function returns the dot product of ratings given two users.
// Return type: int;
int dotProduct(ourvector<int>& person1, ourvector<int>& person2) {
    int sum = 0;
    int product = 0;
    for (int i = 0; i < person1.size(); i++) {
       
            product = person1.at(i) * person2.at(i);
            sum += product;
    }
    return sum;
}
// dotVec (int num, ourvector<int>& input,
// ourvector<ourvector<int>>& rating);
// Function is responsible for making an ourvector with the dot products
// Return type: NONE;
void dotVec(int num, ourvector<int>& input, ourvector<ourvector<int> >& rating) {
    for (int j = 0; j < rating.size(); j++) {
        if (j != num) {
        input.push_back(dotProduct(rating[num], rating[j]));
        } else {
            // push back 0 if j is equal to num
            input.push_back(0);
        }
    }
}
// findMax (ourvector<int> output);
// Function returns the max from the given vector
// Return type: int;
int findMax(ourvector<int> output) {
    int max = output.at(0);
    int index = 0;
    int k = 0;
    while (k < output.size()) {
        if (max < output.at(k)) {
            max = output.at(k);
            index = k;
        }
        k++;
    }
    return index;
}
// advanced (string user, ourvector<string>& items,
// ourvector<string>& names, ourvector<ourvector<int>>& rating);
// Function recommends the top 5 titles based on the highest
// dot product between the current user and other users.
// Return type: NONE;
void advanced(string user, ourvector<string>& items,
ourvector<string>& names, ourvector<ourvector<int> >& rating) {
    ourvector<int> output;
    ourvector<int> o;
    cout << "\n" << "Advanced recommendations:" << endl;
    int num = findUser(user, names);
    dotVec(num, output, rating);
    int max;
    int ind = 0;
    int index = findMax(output);
    o = rating[index];
    int prev = -1;
    int l;
    int times = 0;
    for (int i1 = 0; i1 < 5; i1++) {
        max = -6;
        l = 0;
    while (l < o.size()) {
        if (rating[num].at(l) == 0 && o.at(l) != -6) { 
            if (max < o.at(l)) {
                max = o.at(l);
                ind = l;
            }
        }
       l++;
    }
    if (prev != ind) {
        if (rating[num].at(ind) == 0 || rating[index].at(ind) != 0) {
            o.at(ind) = -6;
            cout << items.at(ind) << endl;
            times++;
            max = 0;
            prev = ind;
        }
    }
    prev = ind;
    }
    // output.clear();
    // o.clear();
}
// makeAdmin (string adMin, string& user, ourvector<string>& items,
// ourvector<string>& names, ourvector<ourvector<int>>& rating,
// bool& l, bool& isAdmin);
// Function is responsible for making an admin
// Return type: NONE;
void makeAdmin(string adMin, string& user, ourvector<string>& items,
ourvector<string>& names, ourvector<ourvector<int> >& rating,
bool& l, bool& isAdmin) {
    for (int i = 0; i < names.size(); i++) {
        if (adMin == names.at(i)) {
           user = adMin;
           l = true;
           isAdmin = true;
           cout << "\n" <<"******* New admin created *******" << endl;
           cout << "Admin Functions:" << endl;
           cout << "1. Type \"delete item\" to delete item" << endl;
           cout << "2. Type \"delete user\" to delete user" << endl;
           cout << "3. Type \"remove admin\" to remove admin privileges" << endl;
           break;
        }
    }
    
if (!l) {
    cout << "\n" << "User not found, please try again.";
}
    checkAdmin(l, isAdmin, user, adMin);
}
// deleteUser (string user, string adMin, string deUser,
// ourvector<string>& names, ourvector<ourvector<int>>& rating);
// Function is responsible for deleting the user
// Return type: NONE;
void deleteUser(string user, string adMin, string deUser,
ourvector<string>& names, ourvector<ourvector<int> >& rating) {
    int num = 0;
    string s = " ";
    if (deUser != user && deUser != adMin) {
        for (int i = 0; i < names.size(); i++) {
            if (deUser == names.at(i)) {
                num = i;
                cout << "\n" << names.at(i) << "'s account has been deleted" << endl;
                names.at(i) = s;
                break;
            }
        }
        for(int j = 0; j < rating[num].size(); j++) {
        rating[num].at(j) = 0;
        }
    } else {
        cout << "\n" << "Cannot delete admin account, please try again." << endl;
    }
}
// deleteItem (int num, ourvector<ourvector<int>>& rating,
// ourvector<string>& items);
// Function is responsible for deleting an item and the ratings
// of the item given the item number.
// Return type: NONE;
void deleteItem(string user, string adMin, int num,
ourvector<ourvector<int> >& rating, ourvector<string>& items) {
    if(user == adMin && num < items.size()) {
    cout << "\n" << items.at(num) << " has been deleted." <<  endl;
    for (int i = 0; i < rating.size(); i++) {
        for (int j = 0; j < rating[i].size(); j++) {
            if (j == num) {
                // the rating of the deleted item is changed to 0 for every user.
                rating[i].at(j) = 0;
            }
        }
    }
    // assigns an empty string to the deleted item number
    items.at(num) = " ";
    } else {
        cout << "\n" << "Cannot delete item, please try again." << endl;
    } 
}
// mustLogIn ();
// Function prints the error message when a user must be
// logged in to call a command.
// Return type: NONE;
void mustLogIn() {
    cout << "\n" <<"-----------------------------" << endl;
    cout << "\n" <<"To complete the operation";
    cout << ", you must first login." << endl;
    cout << "Type \"login username\"." << endl;
}
// cmdPrint (string cmd, string user, string admin,
// ourvector<string>& n, ourvector<string>& i, bool& loggedIn,
// bool& adminIn);
// Function responsible for the design of the command delete.
// Returns the next command
// Return type: string;
string cmdPrint(string cmd, string user, string admin,
ourvector<string>& n, ourvector<string>& i, bool& loggedIn, bool& adminIn) {
    cout <<  "\n" <<"-----------------------------" << endl;
    string output = "";
    if (cmd == "items") {
        printItems(i);
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> output;
    } else if (cmd == "users") {
        printUsers(n);
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> output;
    } else {
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> output;
    }
    return output;
}
// cmdAdd (string cmd, string& user, string& admin,
// ourvector<string>& n, ourvector<string>& i,
// ourvector<ourvector<int>>& r, bool& loggedIn, bool& adminIn);
// Function responsible for the design of the command delete.
// Returns the next command
// Return type: string;
string cmdAdd(string cmd, string& user, string& admin,
ourvector<string>& n, ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn) {
    string output = "";
    if (cmd == "user") {
        cout <<  "\n" <<"-----------------------------" << endl;
        cout << "\n" << "Please enter the username: ";
        cin.ignore();
        getline(cin, user);
        addUser(user, n, r, loggedIn, i.size());
        cout << "Enter command or # to quit: ";
        cin >> output;
    } else if (cmd == "rating") {
        if (loggedIn) {
            cout <<  "\n" <<"-----------------------------" << endl;
            int itemNumber, newRating;
            cout << "\n" << "Item number to add/change rating: ";
            cin >> itemNumber;
            cout << "Add the rating for " << i.at(itemNumber) << ": ";
            cin >> newRating;
            addRating(user, itemNumber, newRating, n, r, loggedIn);
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> output;
        } else {
            mustLogIn();
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> output;
        }
    }
    return output;
}
// cmdBasic (string& user, string& admin, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r,
// bool& loggedIn, bool& adminIn);
// Function responsible for the design of the command delete.
// Returns the next command
// Return type: string;
string cmdBasic(string& user, string& admin, ourvector<string>& n,
ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn) {
    string cmd = "";
    if (loggedIn) {
        cout <<  "\n" <<"-----------------------------" << endl;
        basic(user, i, n, r, loggedIn);
        checkAdmin(adminIn, loggedIn, user, admin);
        cout << "Enter command or # to quit: ";
        cin >> cmd;
    } else {
        mustLogIn();
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> cmd;
    }
    return cmd;
}
// cmdAdvanced (string& user, string& admin, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r, bool& loggedIn,
// bool& adminIn);
// Function responsible for the design of the command delete.
// Returns the next command
// Return type: string;
string cmdAdvanced(string& user, string& admin, ourvector<string>& n,
ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn) {
    string cmd = "";
    if (loggedIn) {
        cout << "\n" <<"-----------------------------" << endl;
        advanced(user, i, n, r);
        checkAdmin(adminIn, loggedIn, user, admin);
        cout << "Enter command or # to quit: ";
        cin >> cmd;
    } else {
        mustLogIn();
        checkLogin(loggedIn, user);
        cout <<"Enter command or # to quit: ";
        cin >> cmd;
    }
    return cmd;
}
// cmdDelete (string cmd, string& user, string& admin, string& deUser,
// ourvector<string>& n, ourvector<string>& i, ourvector<ourvector<int>>& r,
// bool& loggedIn, bool& adminIn, int& deItem);
// Function responsible for the design of the command delete.
// Returns the next command.
// Return type: string ;
string cmdDelete(string cmd, string& user, string& admin, string& deUser,
ourvector<string>& n, ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn, int& deItem) {
    string output = "";
        if (cmd == "user") {
            printUsers(n);
            cout << "\n" << "Please enter the username: ";
            cin.ignore();
            getline(cin, deUser);
            cout << "\n" <<"-----------------------------" << endl;
            deleteUser(user, admin, deUser, n, r);
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> output;
        } else if (cmd == "item") {
            printItems(i);
            cout << "\n" << "Please enter the number of the item: ";
            cin >> cmd;
            deItem = stoi(cmd);
            cout << "\n" <<"-----------------------------" << endl;
            deleteItem(user, admin, deItem, r, i);
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> output;
        }
    return output;
}
// cmdLoad (string itemsFile, string ratingsFile, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r);
// Function responsible for the design of the command load.
// Returns the next command.
// Return type: string;
string cmdLoad(string itemsFile, string ratingsFile,
ourvector<string>& n, ourvector<string>& i, ourvector<ourvector<int> >& r) {
    string cmd = "";
    loadItems(itemsFile, i);
    loadRatings(ratingsFile, n, r);
    cout << "\n" <<"Welcome to the Recommendations App!" << endl;
    cout << "Enter command or # to quit: ";
    cin >> cmd;
    return cmd;
}
// cmdShow (string& user, string& admin, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r,
// bool& loggedIn, bool& adminIn);
// Function responsible for the design of the command show.
// Returns the next command.
// Return type: string ;
string cmdShow(string& user, string& admin, ourvector<string>& n,
ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn) {
    string cmd = "";
    if (loggedIn) {
        cout <<"\n"<< "-----------------------------" << endl;
        show(user, i, n, r, loggedIn);
        // checks if there is an admin
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> cmd;
    } else {
        mustLogIn();
        checkAdmin(adminIn, loggedIn, user, admin);
        cout <<"Enter command or # to quit: ";
        cin >> cmd;
    }
    return cmd;
}
// cmdAdmin (string& user, string& admin, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r,
// bool& loggedIn, bool& adminIn);
// Function is responsible for the design of command admin.
// Calls other functions responsible for the command.
// Returns the next command.
// Return type: string;
string cmdAdmin(string& user, string& admin, ourvector<string>& n,
ourvector<string>& i, ourvector<ourvector<int> >& r,
bool& loggedIn, bool& adminIn) {
    string cmd = "";
    cout << "\n" <<"-----------------------------" << endl;
    cin.ignore();
    getline(cin, admin);
    makeAdmin(admin, user, i, n, r, loggedIn, adminIn);
    cout << "Enter command or # to quit: ";
    cin >> cmd;
    return cmd;
}
// loop (string itemsFile, string ratingsFile, string& user,
// string& admin, string& deUser, ourvector<string>& n,
// ourvector<string>& i, ourvector<ourvector<int>>& r,
// bool& loggedIn, bool& adminIn, int& deItem);
// Function responsible for asking commands from the user
// Return type: NONE;
void loop(string itemsFile, string ratingsFile, string& user, string& admin,
string& deUser, ourvector<string>& n, ourvector<string>& i,
ourvector<ourvector<int> >& r, bool& loggedIn,
bool& adminIn, int& deItem) {
    string cmd = "";
    cout << "\n" <<"Enter command or # to quit: ";
    cin >> cmd;
    admin = "";
    // while loop keeps running until the user enters #
    while ( cmd != "#" ) {
    if (cmd == "load") {
        cin >> itemsFile;
        cin >> ratingsFile;
        cmd = cmdLoad(itemsFile, ratingsFile, n, i, r);
    } else if (cmd == "login") {
        cout << "\n" << "-----------------------------" << endl;
        cin.ignore();
        getline(cin, user);
        login(user, admin, i, n, r, loggedIn, adminIn);
        cout << "Enter command or # to quit: ";
        cin >> cmd;
     } else if(cmd == "logout") {
         if (loggedIn) {
             user = "";
             loggedIn = false;
             cout << "\n"
                  << "-----------------------------" << endl;
             cout << "Successfully logged out" << endl;
             checkAdmin(adminIn, loggedIn, user, admin);
             cout << "Enter command or # to quit: ";
             cin >> cmd;
         } else {
            cout << "\n"
                  << "-----------------------------" << endl;
            cout << "\n"
                  << "Please enter a valid command." << endl;
            cout << "Enter command or # to quit: ";
            cin >> cmd;
         }
    } else if (cmd == "show") {
        cmd = cmdShow(user, admin, n, i, r, loggedIn, adminIn);
    } else if (cmd == "basic") {
        cmd = cmdBasic(user, admin, n, i, r, loggedIn, adminIn);
    } else if (cmd == "print") {
        cin >> cmd;
        cmd = cmdPrint(cmd, user, admin, n, i, loggedIn, adminIn);
    } else if (cmd == "add") {
        cin >> cmd;
        cmd = cmdAdd(cmd, user, admin, n, i, r, loggedIn, adminIn);
    } else if (cmd == "advanced") {
        cmd = cmdAdvanced(user, admin, n, i, r, loggedIn, adminIn);
    } else if (cmd == "admin") {
        if (adminIn) {
            cin >> cmd;
            if (admin == cmd) {
                cout << "\n"
                     << "-----------------------------" << endl;
                cout << "\n*****User is already the admin******" << endl;
                checkAdmin(adminIn, loggedIn, user, admin);
                cout << "Enter command or # to quit: ";
                cin >> cmd;
            } else {
                
                cout << "\n"
                 << "-----------------------------" << endl;
                cout << "\nCannot change admin if admin does not remove his/her privileges" << endl;
                cout << "To complete the operation";
                cout << ", admin must first login." << endl;
                cout << "Type \"login username\"." << endl;

                checkAdmin(adminIn, loggedIn, user, admin);
                cout << "Enter command or # to quit: ";
                cin >> cmd;
            }
        } else {
            cmd = cmdAdmin(user, admin, n, i, r, loggedIn, adminIn);
        }
    } else if (cmd == "delete") {
            if (user == admin) {
            cout << "\n" <<"-----------------------------" << endl;
            cin >> cmd;
            cmd = cmdDelete(cmd, user, admin, deUser, n, i, r, loggedIn, adminIn, deItem);
            } else {
                cout << "\n"
                     << "-----------------------------" << endl;
                cout << "\n"
                     << "To complete the operation";
                cout << ", admin must first login." << endl;
                cout << "Type \"login username\"." << endl;
                checkAdmin(adminIn, loggedIn, user, admin);
                cout << "Enter command or # to quit: ";
                cin >> cmd;
            }
    } else if(cmd == "remove") {
        cin >> cmd;
        if (cmd == "admin" && user == admin) {
            admin = "";
            adminIn = false;
            cout << "\n"
                 << "-----------------------------" << endl;
            cout << "\nAdmin successfully removed" << endl;
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> cmd;
        } else if(cmd == "admin" && user != admin) {
            cout << "\n"
                 << "-----------------------------" << endl;
            cout << "\n"
                 << "To complete the operation";
            cout << ", you must first login." << endl;
            cout << "Type \"login username\"." << endl;
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> cmd;
        } else {
            cout << "\n"
                 << "-----------------------------" << endl;
            cout << "\n"
                 << "Please enter a valid command." << endl;
            checkAdmin(adminIn, loggedIn, user, admin);
            cout << "Enter command or # to quit: ";
            cin >> cmd;
        }
    }
    else {
        cout << "\n" <<"-----------------------------" << endl;
        cout << "\n" << "Please enter a valid command." << endl;
        checkAdmin(adminIn, loggedIn, user, admin);
        cout << "Enter command or # to quit: ";
        cin >> cmd;
        }
    }
    
}
// main ();
// Calls all the functions that run the recommendations program.
// Return type: int;
int main() {
    bool loggedIn = false;
    bool adminIn = false;
    ourvector<string> n;
    ourvector<ourvector<int> > r;
    ourvector<string> i;
    cout << "To start the app, load the data." << endl;
    cout << "Type \"load itemsFile ratingsFile\" and press enter." << endl;
    string itemsFile, ratingsFile, user, cmd, admin, deUser;
    int deItem;
    admin = "";
    loop(itemsFile, ratingsFile, user, admin, deUser, n, i, r, loggedIn, adminIn, deItem);
    cout << "\n" << "-----------------------------" << endl;
    cout << "\n" << "\n" << "Thank you for using the Recommendations app!" << endl;
    loggedIn = false;
    adminIn = false;
    return 0;
}


