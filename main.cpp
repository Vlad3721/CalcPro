//Libraries
#include <string>
#include <iostream>
//Namespace
using namespace std;
//Global variables
string enterData;
int result = 100;
int solvingExamples() {
  return 0;
}
//Entry point
int main() {
  //Data entry cycle
  while (true) {
    //Enter data
    cout << "Enter your data:";
    getline(cin,enterData);
    //Checking entry data
    if (enterData == "exit") break;
    else if (enterData == "") {
      cout << "Invalid enter data" << endl;
      continue;
    }
    else {
      switch (solvingExamples()) {
        case 0:
          cout << result << endl;
      }
    }
  }
  //The end of programme
  return 0;
}
