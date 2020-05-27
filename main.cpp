#include <iostream>
#include <cmath>
#define finePrecision 0.000001
#define broadPrecision 0.01
#define fineSensitivity 2.0*finePrecision
#define broadSensitivity 10*broadPrecision
#define goal 42500/15096.04
#define power 4
using namespace std;


bool equivalent(double result, double sensitivity)
{
  return abs(result - (double)goal) < sensitivity;
}

double POverA(double interest)
{
  return (pow((1+interest),power)-1.0) / (interest*pow((1.0+interest),power));
}

double result(double arg, double (*f)(double))
{
  return (*f)(arg);
}

double interest(bool positive, double bound)
{
  double sum = 0.0;
  int count = 0;
  bool found = false;
  if (positive)
  {
    for( double i = bound; i > 0.0; i-=finePrecision)
    {
      if (abs(result(i, POverA) - goal) < fineSensitivity)
      {
        sum += i;
        count++;
        found = true;
      }
      else if(found)
      {
        break;
      }
    }
  }

  else
  {
    for( double i = bound; i < 1.0; i+=finePrecision)
    {
      if (abs(result(i, POverA) - goal) < fineSensitivity)
      {
        sum += i;
        count++;
        found = true;
      }
      else if(found)
      {
        break;
      }
    }
  }

  return (double)((double)sum/(double)count);
}

int main() {
  double avg = 999;

  for (double j = 0.0; j < 1.0; j+=broadPrecision)
  {
    double difference = result(j, POverA) - (double)goal;
    if(abs(difference) < broadSensitivity)
    {
      if(difference < 0)
      {
        avg = interest(true, j);
      }
      else 
      {
        avg = interest(false, j);
      }
      break;
    }
  }

  cout << "calculated interest: " << avg << endl;
  cout << "result: " << result(avg, POverA) << endl;
  cout << "goal: " << goal << endl;
  cout << "difference: " << result(avg, POverA)- goal<<endl; 
  
}