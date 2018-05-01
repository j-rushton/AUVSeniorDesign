#include<iostream>
#include<iomanip>
#include<cmath>
#include <vector>
#include <sstream>
using namespace std;
#define e 2.71828
//Drag force calculation F = 0.5 * density of fluid * velocity^2 * drag coeff * projected area perpendicular to the velocity of the fluid.
int Drag(int v) {
  float drag_a1,p=1000,c=0.7,a;
  cout<<endl<<"Enter the projected area of the object :"<<endl;
  cin >> a;
  drag_a1 = 0.5 * p * v * v * c ;
  return drag_a1;
}

void Curve_Fit(double r[] , vector<double> x, vector<double> y)
{
  vector<double> log_y;
  int num,i;
  double a, b, c, s, sigmax=0, sigmax2=0, sigmay=0, sigmaxy=0;
  for (int i = 0; i < y.size(); ++i)
    if (y[i] == 0)
      y[i] = 0.01;
    if (y[i] < 0){
      y[i] = -y[i];
      num += 1;
      cout<<num<<endl;
    }
  for (auto& k : y)
    log_y.push_back(log(k));
  int n = x.size();
  for (auto& k : x)
    sigmax += k;
  for (auto& k : x)
    sigmax2 += k * k;
  for (auto& k: log_y)
    sigmay+=k;
  for (i=0;i<n;i++)
    sigmaxy=sigmaxy+x[i]*log_y[i];
    a=(n*sigmaxy-sigmax*sigmay)/(n*sigmax2-sigmax*sigmax);
    b=(sigmax2*sigmay-sigmax*sigmaxy)/(sigmax2*n-sigmax*sigmax);
    c=pow(e,b);
    s=c/a;
    r[0] = c;
    r[1] = a;
    r[2] = s;
}

int main(){
  float drag_a[3];
  double a, s, v, temp=0, x_steady, y_steady,curve_parameters[3];
  vector<double> x,y,log_y;
  string line;
  //User input of x and y values(linear acceleration and time)
  cout << "Enter x  separated by spaces: ";
  getline(cin, line);
  istringstream stream(line);
  while (stream >> temp)
    x.push_back(temp);
  cout << "Enter y  separated by spaces: ";
  getline(cin, line);
  istringstream stream1(line);
  while (stream1 >> temp)
    y.push_back(temp);
  if ( x.size() != y.size())
    return(-1);
  Curve_Fit(curve_parameters,x,y);
  cout<<endl<<"The equation of the curve after calling the function is: y = "<<curve_parameters[0]<<"e^"<<a<<"x"<<endl;
  s = curve_parameters[2];
  a=curve_parameters[1];
  int n = x.size();
  for (int i = 0; i < n; i++)
    {
      if (((y[i]-y[i+1])/(x[i+1]-x[i])) <= 0.2)
      {
        x_steady = x[i];
        y_steady = y[i];
      }
    }
  v = s * pow(e,a*x_steady) * -1;
  cout<<endl<<"The value of velocity after "<<x_steady<<" seconds is "<<v<<" m/s"<<endl;
  drag_a[0] = Drag(v);
  cout<<endl<<"The 1st drag value is :"<<drag_a[0]<<endl;
  return 0;
}
