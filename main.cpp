//Libraries
#include <string>
#include <iostream>
#include <cmath>
//Namespace
using namespace std;
//Macros
#define DIVISION(a,b,abs_a,abs_b) \
r = modf(float(abs_a)/abs_b,&intpart); \
if (roundf((abs_a-abs_b*floorf(intpart))*1000000) == 0) { \
  r = modf(abs_a/abs_b,&intpart); \
  if (((a < 0) && (b >= 0)) || ((a >= 0) && (b < 0))) \
    result = result + "-"; \
  result = result + to_string(roundf(intpart)); \
} \
else { \
  if (((a < 0) && (b >= 0)) || ((a >= 0) && (b < 0))) \
    result = result + "-"; \
  else \
    result = result + "+"; \
  r = modf(float(abs_a)/abs_b*10000,&intpart); \
  if (roundf(r*1000000) == 0) { \
    result = result + to_string(float(abs_a)/abs_b); \
  } \
  else { \
    r = modf(float(abs_a)/abs_number20,&intpart); \
    result = result + to_string(abs_a-abs_b*floorf(intpart))+"/"+to_string(abs_b); \
    if (floorf(intpart) != 0) { \
      result = to_string(floorf(intpart)) + result; \
      if (((a < 0) && (b >= 0)) || ((a >= 0) && (b < 0))) \
        result = "-" + result; \
    } \
  } \
}
//Global variables
string enterData;

/*Доделать деление в calcLite, сделать вывод описания ошибок пользователю (необязательно, но желательно)*/

bool charIsNum(char ch) {
  char elem[10] = {'1','2','3','4','5','6','7','8','9','0'};
  for (int i = 0;i < 10;i++) {
    if (ch == elem[i])
      return true;
  }
  return false;
}

string calcLite(string str,int i) {
  //Variables
  string result = "";

  string numS1 = "";
  int n1 = i-1;
  int number10 = 0;
  int abs_number10 = 0;
  float number11 = 0.0;
  float abs_number11 = 0.0;

  string numS2 = "";
  int n2 = i+1;
  int number20 = 0;
  int abs_number20 = 0;
  float number21 = 0.0;
  float abs_number21 = 0.0;

  int numIsFloat = 0;
  //Read first number
  while (charIsNum(str[n1]) || (str[n1] == '.')) {
    numS1 = str[n1] + numS1;
    n1--;
  }
  //Read second number
  if ((str[n2] == '-') || (str[n2] == '+'))
    n2++;
  while (charIsNum(str[n2]) || (str[n2] == '.')) {
    numS2 = numS2 + str[n2];
    n2++;
  }

  //Transformation first number from string to integer
  if (numS1.find(".") == -1) {
    number10 = stoi(numS1);
    abs_number10 = abs(number10);
  }
  else {
    number11 = stof(numS1);
    abs_number11 = abs(number11);
    numIsFloat += 10;
  }

  if (str[n1] == '-') {
    number10 *= -1;
    number11 *= -1;
  }

  //Transformation second number from string to integer
  if (numS2.find(".") == -1) {
    number20 = stoi(numS2);
    abs_number20 = abs(number20);
  }
  else {
    number21 = stof(numS2);
    abs_number21= abs(number21);
    numIsFloat += 1;
  }

  if (str[i+1] == '-') {
    number20 *= -1;
    number21 *= -1;
  }

  // {cout << endl;
  // cout << number10 << endl;
  // cout << abs_number10 << endl;
  // cout << number11 << endl;
  // cout << abs_number11 << endl;
  // cout << endl;
  // cout << number20 << endl;
  // cout << abs_number20 << endl;
  // cout << number21 << endl;
  // cout << abs_number21 << endl;
  // cout << endl;
  // cout << numIsFloat << endl;
  // cout << endl;}

  //Operations
  if (str[i] == '+') {
    switch (numIsFloat) {
      case 0:
        result = to_string(number10+number20);
        break;
      case 1:
        result = to_string(number10+number21);
        break;
      case 10:
        result = to_string(number11+number20);
        break;
      case 11:
        result = to_string(number11+number21);
        break;
    }
  }
  else if (str[i] == '-') {
    switch (numIsFloat) {
      case 0:
        result = to_string(number10-number20);
        break;
      case 1:
        result = to_string(number10-number21);
        break;
      case 10:
        result = to_string(number11-number20);
        break;
      case 11:
        result = to_string(number11-number21);
        break;
    }
  }
  else if (str[i] == '*') {
    switch (numIsFloat) {
      case 0:
        result = to_string(number10*number20);
        break;
      case 1:
        result = to_string(number10*number21);
        break;
      case 10:
        result = to_string(number11*number20);
        break;
      case 11:
        result = to_string(number11*number21);
        break;
    }
  }
  else if (str[i] == '/') {
    //Variables (using in macro "DIVISION")
    float intpart = 0.0;
    float r = 0.0;
    switch (numIsFloat) {
      case 0:
        DIVISION(number10,number20,abs_number10,abs_number20)
        break;
      case 1:
        DIVISION(number10,number21,abs_number10,abs_number21)
        break;
      case 10:
        DIVISION(number11,number20,abs_number11,abs_number20)
        break;
      case 11:
        DIVISION(number11,number21,abs_number11,abs_number21)
        break;
    }
  }

  if ((result[0] != '-') && (result[0] != '+'))
    result = "+"+result;
  return result;
}

string transformation(string str) {
  int transform = 0;
  do {
    transform = 0;
    for (int i = 0;i < str.size();i++) {
      if ((str[i] == '+') || (str[i] == '-')) {
        int j = i;
        int sump = 0;
        int summ = 0;
        while ((str[j] == '+') || (str[j] == '-')) {
          if (str[j] == '+')
            sump++;
          else
            summ++;
          j++;
        }
        if (sump+summ > 1) {
          if (summ%2==0)
            str.replace(i,sump+summ,"+");
          else
            str.replace(i,sump+summ,"-");
          transform++;
        }
      }
      else if (str[i] == '*') {
        int j = i;
        int sum = 0;
        while (str[j] == '*') {
          sum++;
          j++;
        }
        if (sum > 1) {
          str.replace(i,sum,"*");
          transform++;
        }
      }
      else if (str[i] == '/') {
        int j = i;
        int sum = 0;
        while (str[j] == '/') {
          sum++;
          j++;
        }
        if (sum > 1) {
          str.replace(i,sum,"/");
          transform++;
        }
      }
      else if (str[i] == '.') {
        int j = i;
        int sum = 0;
        int openZero = 0;
        while (str[j] == '.') {
          sum++;
          j++;
        }
        if (sum > 1) {
          str.replace(i,sum,".");
          transform++;
        }
        j = i+1;
        while (charIsNum(str[j])) {
          if (str[j] == '0')
            openZero++;
          else
            openZero = 0;
          j++;
        }
        if (openZero > 0) {
          str.erase(j-openZero,openZero);
          transform++;
          if (j-openZero == i+1) {
            str.erase(i,1);
            i = i-1;
            transform++;
          }
        }
      }
      else if (str[i] == ',') {
        str[i] = '.';
        transform++;
      }
      else if (str[i] == '(') {
        if (charIsNum(str[i-1])) {
          str.insert(i,"*");
          transform++;
        }
      }
      else if (str[i] == ')') {
        if (charIsNum(str[i+1])) {
          str.insert(i+1,"*");
          transform++;
        }
      }
    }
  } while(transform != 0);
  return str;
}

int validateExamples() {
  bool errorSymbol = false;
  bool errorBracket = false;
  bool errorVoid = false;
  int val1 = 0;
  int val2 = 0;
  int openBrackets = 0;
  const int heightElemArray = 17;
  char elem[heightElemArray] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')','.'};

  for (int i = 0;i < enterData.size();i++) {
    bool correctSymbol = false;
    for(int j = 0;j < heightElemArray;j++) {
      if (elem[j] == enterData[i]) {
        correctSymbol = true;
      }
    }
    if (!correctSymbol) {
      errorSymbol = true;
      break;
    }

    if (enterData[i] == '(') {
      openBrackets++;
      val1++;
    }
    else if (enterData[i] == ')') {
      if (openBrackets > 0)
        openBrackets--;
      else
        return -2;
      val2++;
    }
    else if (enterData[i] == '+') {
      if (!((i != enterData.size()-1) && (charIsNum(enterData[i+1]) || (
        (enterData[i+1] == '(') && ((enterData[i-1] != '*') && (enterData[i-1] != '/'))
        ))))
        return -4;
    }
    else if (enterData[i] == '-') {
      if (!((i != enterData.size()-1) && (charIsNum(enterData[i+1]) || (
        (enterData[i+1] == '(') && ((enterData[i-1] != '*') && (enterData[i-1] != '/'))
        ))))
        return -5;
    }
    else if (enterData[i] == '*') {
      if (!((charIsNum(enterData[i-1]) || (enterData[i-1] == ')')) &&
        (charIsNum(enterData[i+1]) || (enterData[i+1] == '(') || (enterData[i+1] == '+') || (enterData[i+1] == '-'))))
        return -6;
    }
    else if (enterData[i] == '/') {
      if (!((charIsNum(enterData[i-1]) || (enterData[i-1] == ')')) &&
        (charIsNum(enterData[i+1]) || (enterData[i+1] == '(') || (enterData[i+1] == '+') || (enterData[i+1] == '-'))))
        return -7;
    }
    else if (enterData[i] == '.') {
      if (!charIsNum(enterData[i-1]) || !charIsNum(enterData[i+1]))
        return -8;
    }
  }

  if (enterData.empty())
    return -3;
  else if ((val1 != val2) || (openBrackets != 0))
    return -2;
  else if (errorSymbol)
    return -1;
  else
    return 0;
}

string solvingExamples(string str) {
  if (str.find("(") == -1) {
    string str_save;
    do {
      str_save = str;
      for (int i = 0;i < str.size();i++) {
        if (((str[i] == '*') || (str[i] == '/')) || (((str[i] == '+') || (str[i] == '-')) && (i > 0) && (str.find("*") == -1) && (str.find("/") == -1))) {
          int sum1 = 0;
          int j1 = i-1;
          int sum2 = 0;
          int j2 = i+1;
          while (charIsNum(str[j1]) || (str[j1] == '.')) {
            sum1++;
            j1--;
          }
          if ((str[j1] == '-') || (str[j1] == '+'))
            sum1++;

            if ((str[j2] == '-') || (str[j2] == '+')) {
              sum2++;
              j2++;
            }
            while (charIsNum(str[j2]) || (str[j2] == '.')) {
              sum2++;
              j2++;
            }
            string resstr = calcLite(str,i);
            str.replace(i-sum1,sum1+sum2+1,resstr);
            i = i-sum1+resstr.size()-1;
        }
      }
      str = transformation(str);
      //cout << endl << str << endl;
    } while(((str.find("*") != -1) || (str.find("/") != -1) || (str.find("+") != -1) || (str.find("-") != -1)) && (str_save.compare(str) != 0));
  }
  else {
    bool bracketOpen = false;
    int bOpenVal = 0;
    int placeBegin = 0;
    string inBracket = "";
    for (int i = 0;i < str.size();i++) {
      if (str[i] == '(') {
        if (bracketOpen == false) {
          bracketOpen = true;
          placeBegin = i;
        }
        bOpenVal++;
      }
      else if (str[i] == ')') {
        bOpenVal--;
        if (bOpenVal == 0) {
          bracketOpen = false;
          inBracket.erase(0,1);
          string strRes = solvingExamples(inBracket);
          str.replace(placeBegin,inBracket.size()+2,strRes);
          i = placeBegin + strRes.size()-1;

          inBracket = "";
        }
      }
      if (bracketOpen == true)
        inBracket = inBracket + str[i];
    }
    str = solvingExamples(str);
  }
  str = transformation(str);
  return str;
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
      enterData = transformation(enterData);
      cout << enterData << endl;
      int validateResult = validateExamples();

      if (validateResult == 0) {
        cout << solvingExamples(enterData) << endl;
      }
      else {
        cout << "Invalid enter data (" << validateResult << ")" << endl;
      }
    }
  }
  //The end of programme
  return 0;
}
