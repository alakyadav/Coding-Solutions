/*https://community.topcoder.com/tc?module=ProblemDetail&rd=10730&pm=7479*/
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <iomanip>

using namespace std;

class Node
{
public:
  
  int x, y, threshold, s_no;
  char id;
  bool labeled = 0;
  vector<Node*> attached;
  
  Node(int a, int b, int c, char i, int j)
  {
    x = a;
    y = b;
    threshold = c;
    id = i;
    s_no = j;
  }
};
class Alarmed
{
public:
  void add_link(Node *p1, Node *p2)
  {
    p1->attached.push_back(p2);
    p2->attached.push_back(p1);
  }
  
  bool DFS(Node *lw, Node *rw)
  {
    stack<Node*> S;
    S.push(lw);
    while(!S.empty()){
      Node* v = S.top();
      S.pop();
      if(!v->labeled){
        v->labeled = 1;
        for(auto it=v->attached.begin(); it!=v->attached.end(); it+=1)
          S.push((*it));
      }
    }
    if(rw->labeled)
      return true;
    else
      return false;
  }
  
  
  
  bool calc(double A, vector<Node*> *nodes, Node *lw, Node *rw)
  {
    for(auto it1=nodes->begin(); it1!=nodes->end(); it1+=1){
      
      int x1, y1, t1;
      t1 = (*it1)->threshold;
      x1 = (*it1)->x;
      y1 = (*it1)->y;
      double r1 = sqrt(A/t1);
      
      for(auto it2=nodes->begin(); it2!=nodes->end(); it2+=1){
        if(it1 != it2 && (*it1)->id == 'N' && (*it2)->id == 'N'){
          // Links among the sensors.
          int x2, y2, t2;
          t2 = (*it2)->threshold;
          x2 = (*it2)->x;
          y2 = (*it2)->y;
          double dist = sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));
          double r2 = sqrt(A/t2);
          if(dist <= r1 + r2)
            add_link((*it1), (*it2));}
      }
      
      // Links between the sensors and the walls.
      if((*it1)->id == 'N'){
        if(r1 >= x1)
          add_link((*it1), lw);
        if(r1 >= 100 - x1)
          add_link((*it1), rw);
        if(r1 >= y1) {
          if(x1 < 50)
            add_link((*it1), lw);
          else
            add_link((*it1), rw);
        }
        if(r1 >= 100 - y1) {
          if(x1 < 50)
            add_link((*it1), lw);
          else
            add_link((*it1), rw);
        }
        
        
        // Links between the walls.
        double dist_d1 = sqrt(pow(y1 - 0, 2) + pow(x1 - 50, 2));
        double dist_d2 = sqrt(pow(y1 - 100, 2) + pow(x1 - 50, 2));
        if(r1 >= dist_d1 || r1 >= dist_d2)
          add_link(lw, rw);
      }
      
    }
    
    
    
    bool ans = DFS(lw, rw);
    for(auto it = nodes->begin(); it != nodes->end(); it+=1){
      (*it)->attached.clear();
      (*it)->labeled = 0;
    }
    
    return ans;
  }
  
  double bin_search(double low, double high, Node* lw, Node* rw, vector<Node*> *nodes)
  {
    double mid = (low + high) / 2;
    if(mid == low || mid == high)
      return low;
    if(calc(mid, nodes, lw, rw) != calc(mid + 1e-9, nodes, lw, rw)) {
      //cout << low << " " << high << '\n';
      return mid;
    }
    
    if(calc(mid, nodes, lw, rw)) {
      double ans = bin_search(low, mid, lw, rw, nodes);
      //cout << low << " " << high << '\n';
      return ans;
    }
    
    else{
      double ans = bin_search(mid, high, lw, rw, nodes);
      //cout << low << " " << high << '\n';
      return ans;
    }
  }
  
  double noise(vector<int> x, vector<int> y, vector<int> threshold)
  {
    vector<Node*> *nodes = new vector<Node*>;
    for(unsigned int i=0; i<x.size(); i+=1) {
      Node* temp = new Node(x[i], y[i], threshold[i], 'N', i);
      nodes->push_back(temp);
    }
    Node* lw = new Node(0, 50, 1, 'L', x.size());
    Node* rw = new Node(100, 50, 1, 'R', x.size() + 1);
    nodes->push_back(lw);
    nodes->push_back(rw);
    double A = 1;
    while(!calc(A, nodes, lw, rw))
      A *= 10;
    double low = A / 10, high = A;
    //cout << low << " " << high;
    return bin_search(low, high, lw, rw, nodes);
    
  }
};
