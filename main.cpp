//Libraries
#include <string>
#include <iostream>
#include <cmath>
//Namespace
using namespace std;
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
  string num1 = "";
  int n1 = i-1;
  string num2 = "";
  int n2 = i+1;
  //Read first number
  while (charIsNum(str[n1]) || (str[n1] == '.')) {
    num1 = str[n1] + num1;
    n1--;
  }
  //Read second number
  if ((str[n2] == '-') || (str[n2] == '+'))
    n2++;
  while (charIsNum(str[n2]) || (str[n2] == '.')) {
    num2 = num2 + str[n2];
    n2++;
  }
  //Variables
  int number1 = 0;
  float numberf1 = 0.0;
  bool fnum1 = false;
  int number2 = 0;
  float numberf2 = 0.0;
  bool fnum2 = false;
  //Transformation first number from string to integer
  if (num1.find(".") == -1)
    number1 = stoi(num1);
  else {
    numberf1 = stof(num1);
    fnum1 = true;
  }

  if (str[n1] == '-') {
    number1 = number1*-1;
    numberf1 = numberf1*-1;
  }
  //Transformation second number from string to integer
  if (num2.find(".") == -1)
    number2 = stoi(num2);
  else {
    numberf2 = stof(num2);
    fnum2 = true;
  }

  if (str[i+1] == '-') {
    number2 = number2*-1;
    numberf2 = numberf2*-1;
  }

  float abs_fnum1 = abs(numberf1);
  float abs_fnum2 = abs(numberf2);
  int abs_num1 = abs(number1);
  int abs_num2 = abs(number2);

  //Variables
  string result = "";
  //Operations
  if (str[i] == '+') {
    if (fnum1 && fnum2)
      result = to_string(numberf1+numberf2);
    else if (fnum1 && !fnum2)
      result = to_string(numberf1+number2);
    else if (!fnum1 && fnum2)
      result = to_string(number1+numberf2);
    else
      result = to_string(number1+number2);
  }
  else if (str[i] == '-') {
    if (fnum1 && fnum2)
      result = to_string(numberf1-numberf2);
    else if (fnum1 && !fnum2)
      result = to_string(numberf1-number2);
    else if (!fnum1 && fnum2)
      result = to_string(number1-numberf2);
    else
      result = to_string(number1-number2);
  }
  else if (str[i] == '*') {
    if (fnum1 && fnum2)
      result = to_string(numberf1*numberf2);
    else if (fnum1 && !fnum2)
      result = to_string(numberf1*number2);
    else if (!fnum1 && fnum2)
      result = to_string(number1*numberf2);
    else
      result = to_string(number1*number2);
  }
  else if (str[i] == '/') {
    if (fnum1 && fnum2) {
      //if (abs_fnum1-abs_fnum2*int(abs_fnum1/abs_fnum2))
      if (roundf((numberf1-numberf2*int(numberf1/numberf2))*1000000) == 0)
        result = to_string(int(numberf1/numberf2));
      else if (int(numberf1/numberf2) == 0)
        result = to_string(numberf1-numberf2*int(numberf1/numberf2))+"/"+to_string(numberf2);
      else
        result = to_string(int(numberf1/numberf2))+"+"+to_string(numberf1-numberf2*int(numberf1/numberf2))+"/"+to_string(numberf2);
    }
    else if (fnum1 && !fnum2) {
      if (roundf((numberf1-number2*int(numberf1/number2))*1000000) == 0)
        result = to_string(int(numberf1/number2));
      else if (int(numberf1/number2) == 0)
        result = to_string(numberf1-number2*int(numberf1/number2))+"/"+to_string(number2);
      else
        result = to_string(int(numberf1/number2))+"+"+to_string(numberf1-number2*int(numberf1/number2))+"/"+to_string(number2);
    }
    else if (!fnum1 && fnum2) {
      if (roundf((number1-numberf2*int(number1/numberf2))*1000000) == 0)
        result = to_string(int(number1/numberf2));
      else if (int(number1/numberf2) == 0)
        result = to_string(number1-numberf2*int(number1/numberf2))+"/"+to_string(numberf2);
      else
        result = to_string(int(number1/numberf2))+"+"+to_string(number1-numberf2*int(number1/numberf2))+"/"+to_string(numberf2);
    }
    else {
      if (number1%number2 == 0)
        result = to_string(int(number1/number2));
      else if (int(number1/number2) == 0)
        result = to_string(number1-number2*int(number1/number2))+"/"+to_string(number2);
      else
        result = to_string(int(number1/number2))+"+"+to_string(number1-number2*int(number1/number2))+"/"+to_string(number2);
    }
  }

  if (result[0] != '-')
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
        while (str[j] == '.') {
          sum++;
          j++;
        }
        if (sum > 1) {
          str.replace(i,sum,".");
          transform++;
        }
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
  char elem[17] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')','.'};

  for (int i = 0;i < enterData.size();i++) {
    bool correctSymbol = false;
    for(int j = 0;j < 17;j++) {
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
      if ((str.find("*") != -1) || (str.find("/") != -1)) {
        for (int i = 0;i < str.size();i++) {
          if ((str[i] == '*') || (str[i] == '/')) {
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
            while (charIsNum(str[j2]) || (str[j1] == '.')) {
              sum2++;
              j2++;
            }
            string resstr = calcLite(str,i);
            str.replace(i-sum1,sum1+sum2+1,resstr);
            i = i-sum1+resstr.size()-1;
          }
        }
      }
      else {
        for (int i = 0;i < str.size();i++) {
          if (((str[i] == '+') || (str[i] == '-')) && (i > 0)) {
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
            while (charIsNum(str[j2]) || (str[j1] == '.')) {
              sum2++;
              j2++;
            }
            string resstr = calcLite(str,i);
            str.replace(i-sum1,sum1+sum2+1,resstr);
            i = i-sum1+resstr.size()-1;
          }
        }
      }
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
        //cout << 0 << endl;
      }
      // else if (validateExamples() == -1) {
      //   cout << "Invalid enter data" << endl;
      //   continue;
      // }
      // else if (validateExamples() == -2) {
      //   cout << "Incorrect placement of brackets" << endl;
      //   continue;
      // }
      // else if (validateExamples() == -3) {
      //   cout << "The enter data is empty" << endl;
      //   continue;
      // }
      else {
        cout << "Invalid enter data (" << validateResult << ")" << endl;
      }
    }
  }
  //The end of programme
  return 0;
}
