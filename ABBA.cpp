/* https://community.topcoder.com/stat?c=problem_statement&pm=13918 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class ABBA
{
public: 
  string canObtain(string initial, string target)
  {
    while(initial.length() != target.length()) {
      if(target[target.length()-1] == 'A')
        target.pop_back();
      
      else {
        target.pop_back();
        reverse(target.begin(), target.end());
      }
      
    }
    
    if(initial == target)
      return "Possible";
    else
      return "Impossible";
  }
};
