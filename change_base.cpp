#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define DEBUG (0)
void testPrint()
{
  string input = "binary";
  cout << input.substr(2,input.size()) << "\n";

}

const static unordered_map<char,int> hexMap_ = {{'0',0},{'1',1},
                                                {'2',2},{'3',3},
                                                {'4',4},{'5',5},
                                                {'6',6},{'7',7},
                                                {'8',8},{'9',9},
                                                {'A',10},{'B',11},
                                                {'C',12},{'D',13},
                                                {'E',14},{'F',15},
                                                {'a',10},{'b',11},
                                                {'c',12},{'d',13},
                                                {'e',14},{'f',15}};

void PrintNumbers(int old_base)
{
  printf("%d\n", old_base);
  printf("%#x\n", old_base);
	// cout << *request << '\n';
}

int SetDecimalVal(string &input, int &decimal)
{
  int error = 0, i = 0, base = 0;
  string substr = input.substr(0,2);
  if(substr == "0b"){
    // cout << "Binary.\n";
    base = 2;
  }
  else if(substr == "0x"){
    // cout << "Hex.\n";
    base = 16;
  }
  else {
    // cout << "Dec.\n";
    base = 10;
  }

  decimal = 0;
  int curr_dec_sum = 0;
  substr = input.substr(2,input.size());
  for_each(substr.rbegin(), substr.rend(), [&i, base, &curr_dec_sum, &error] (char c)
  {
    if(error != 0) return;
    if(base == 10)
    {
      if(!isdigit(c))
        error = -1;
    }
    if(base == 2)
    { //need overflow detection && 2/1s compliment
      // cout << "val: " << c << " " << (c=='0' || c=='1') << endl;
      if(c=='0' || c=='1')
        curr_dec_sum += ((c=='1') ? 1 : 0)<<i++;
      else
        error = -1;
    }
    else if(base == 16)
    {
      unordered_map<char, int>::const_iterator itr = hexMap_.find(c);
      if (itr == hexMap_.end())
        error = -1;
      else
        curr_dec_sum += itr->second << 4*i++;
    }
  });
  decimal =  curr_dec_sum;

  #if(DEBUG)
    cout << "base: " << base << "\n";
    cout << "decimal:" << decimal << "\n";
    cout << "error: " << error << "\n";
  #endif

  if(error == -1)
    return -1;

  if(base == 10)
    decimal = stoi(input);

  return base;
}

int SetValue(int &initial_value)
{
  string input;
  cin >> input;
  if (cin.fail())
  {
    cout << "Invalid input.\n";
    cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
  }

  if(SetDecimalVal(input,initial_value) < 0){
    cout << "failed to convert to decimal" << endl;
    return -1;
  }

  #if(DEBUG)
  cout << initial_value << endl;
  #endif

  return 0;
}

int main(int argc, char** argv)
{
  #if(DEBUG)
    testPrint();
  #endif

  int initial_value;

  cout << "Accepted base input: 0b, 0x, decimal\n";
  do
  {
    cout << "input: ";
  }	while(SetValue(initial_value) != 0);

  PrintNumbers(initial_value);

  return 0;
}
