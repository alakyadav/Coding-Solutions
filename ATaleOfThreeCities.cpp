/* https://www.topcoder.com/tc?module=ProblemDetail&rd=6538&pm=3543 */
#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

class ATaleOfThreeCities
{
public:
  void dist(vector<int> *x1, vector<int> *y1, vector<int> *x2, vector<int> *y2, vector<double> *target)
  {
    for(int i=0; i<x1->size(); i+=1) 
      for(int j=0; j<x2->size(); j+=1) { 
        double ans = sqrt(pow((*x2)[j] - (*x1)[i], 2) + pow((*y2)[j] - (*y1)[i], 2));
        target->push_back(ans);
      }
  }
  
  double connect(vector<int> ax, vector<int> ay, vector<int> bx,
                 vector<int> by, vector<int> cx, vector<int> cy)
  {
    vector<double> ab, bc, ac;
    dist(&ax, &ay, &bx, &by, &ab);
    dist(&bx, &by, &cx, &cy, &bc);
    dist(&cx, &cy, &ax, &ay, &ac);
    
    double min_ab, min_bc, min_ac;
    min_ab = *min_element(ab.begin(), ab.end());
    min_bc = *min_element(bc.begin(), bc.end());
    min_ac = *min_element(ac.begin(), ac.end());
    
    
    double total = min_ab + min_bc + min_ac;
    total -= max(min_ab, max(min_bc, min_ac));
    return total;
  }
};
