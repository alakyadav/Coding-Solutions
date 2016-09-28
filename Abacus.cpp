/* http://topcoder.bgcoder.com/print.php?id=903 */
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Abacus{
public:
  
  int s2d(string *x) {
    //cout << "In s2d\n";
    int n = x->length() - 1;
    //  cout << "Length of string, -1,  is " << n << endl;
    int total = 0;
    
    while((*x)[n] != '-') {
      total += 1;
      n -= 1;
    }
    //  cout << "Value of string is " << total << endl;
    
    return total;
  }
  
  int s2i(vector<string> *x)
  {
    //  cout << "In s2i\n";
    int n = x->size();
    //  cout << "Size of vector of string is " << n << endl;
    int j = 1, total = 0;
    
    for(int i = n-1; i >= 0; i-=1) {
      //cout << "loooop\n";
      int temp = s2d(&((*x)[i]));
      total += temp * j;
      j *= 10;
    }
    //  cout << "Number formed: " << total << endl;
    
    return total;
  }
  
  string d2s(int i)
  {
    string s;
    int diff = 12 - i;
    int ones = diff - 3;
    
    while(ones) {
      s.push_back('o');
      ones -= 1;
    }
    
    for(int j = 0; j < 3; j+=1)
      s.push_back('-');
    
    for(int j = 0; j < i; j+=1)
      s.push_back('o');
    
    return s;
  }
  
  vector<string> i2s(int i)
  {
    //cout << "In i2s\n";
    vector<string> s;
    while(i >= 1) {
      int d = i % 10;
      string temp = d2s(d);
      s.push_back(temp);
      i /= 10;
    }
    
    int len = 6 - s.size();
    string x = "ooooooooo---";
    for(int j = 0; j < len; j += 1)
      s.push_back(x);
    
    reverse(s.begin(), s.end());
    
    return s;
  }
  
  vector<string> add(vector<string> original, int val)
  {
    //cout << "In add\n"; 
    int org = s2i(&original);
    //cout << "GOT ORG = " << org << endl;
    int temp = org + val;
    //cout << "TEMP = " << temp << endl;
    vector<string> ans = i2s(temp);
    // cout << "REACHED ANS\n";
    
    
    return ans;
  }
  
};
