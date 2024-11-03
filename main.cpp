//Libraries
#include <string>
#include <iostream>
//Namespace
using namespace std;
//Global variables
string enterData;
int result = 100;

bool charIsNum(char ch) {
  char elem[10] = {'1','2','3','4','5','6','7','8','9','0'};
  for (int i = 0;i < 10;i++) {
    if (ch == elem[i])
      return true;
  }
  return false;
}



int validateExamples() {
  bool errorSymbol = false;
  bool errorBracket = false;
  bool errorVoid = false;
  int val1 = 0;
  int val2 = 0;
  char elem[16] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')'};

  for (auto i = enterData.begin();i != enterData.end();i++) {
    if (*i == '(') {
      val1++;
    }
    else if (*i == ')') {
      val2++;
    }
    for(int j = 0;j < 16;j++) {
      if (elem[j] == *i) {
        errorSymbol = true;
        break;
      }
    }
  }
  if (enterData.empty())
    errorVoid = true;
  if (val1 != val2)
    errorBracket = true;

  if (errorVoid)
    return -3;
  else if (errorSymbol)
    return -1;
  else if (errorBracket)
    return -2;
  else
    return 0;
}

int solvingExamples(string str) {
  if (str.find("(") == -1) {
    if ((str.find("*") != -1) || (str.find("/") != -1)) {
      int end_str = str.size();
      for (int i = 0;i < end_str;i++) {
        if ((str[i] == "*") || (str[i] == "/")) {
          string num1;
          int n1 = i-1;
          string num2;
          int n2 = i+1;
          while (charIsNum(str[n1])) {
            num1.insert(0,str[n1]);
            num1--;
          }
          if (str[n1] == "-")
            num1.insert(0,str[n1]);

          if (str[n2] == "-") {
            num2.insert(0,str[n2]);
            n2++;
          }
          while (charIsNum(str[n2])) {
            num2.insert(num2[n2-i-1],str[n2]);
            n2++;
          }
        }
      }
    }
  }
  else {

  }

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
    else {
      if (validateExamples() == 0) {
        cout << result << endl;
      }
      else if (validateExamples() == -1) {
        cout << "Invalid enter data" << endl;
        continue;
      }
      else if (validateExamples() == -2) {
        cout << "Incorrect placement of brackets" << endl;
        continue;
      }
      else if (validateExamples() == -3) {
        cout << "The enter data is empty" << endl;
        continue;
      }
    }
  }
  //The end of programme
  return 0;
}
