#include <iostream>
#include <cmath>
#define precision 0.000001
#define goal 42500/15069.04
#define power 4
using namespace std;


bool equivalent(double result)
{
  return abs(result - (double)goal) < 2.0*precision;
}

double result(double interest)
{
  return (pow((1+interest),power)-1.0) / (interest*pow((1.0+interest),power));
}



int main() {
  double sum = 0;
  int count = 0;
  for( double i = 0.0; i < 1.0; i+=precision)
  {
    double candidate = result(i);
    if (equivalent(candidate))
    {
      sum += i;
      count++;
    }
  }
  cout << (double)((double)sum/(double)count);
  
}