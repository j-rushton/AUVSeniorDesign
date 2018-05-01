#include<iostream>
#include<cmath>
#include<fstream>
#include<sstream>
#include<vector>
#include<typeinfo>
#include<time.h>
using namespace std;
#define e 2.71828
void CSV_file_reader(vector<double> &t, vector<double> &gx, vector<double> &gy, vector<double> &gz, vector<double> &ax, vector<double> &ay, vector<double> &az);
int max_angular_vel_mag(vector<double> gyrox, vector<double> gyroy, vector<double> gyroz);
int max_linear_acc_mag(vector<double> accelx, vector<double> accely, vector<double> accelz);
void magnitude(vector<double> &gx, vector<double> &gy, vector<double> &gz, vector<double> &ax, vector<double> &ay, vector<double> &az);
void Curve_Fit(double r[] , vector<double> x, vector<double> y);

int main()
{
    int i, av_pos, la_pos;
	vector<double> t, gx, gy, gz, ax, ay, az;
    double a,s,v,curve_parameters[3],x_steady, y_steady;
    CSV_file_reader(t,gx,gy,gz,ax,ay,az);//This will collect all the data from the csv file.
    Curve_Fit(curve_parameters,t,ax);//This will perform the exponential regression on the parameters passed
    cout<<endl<<"ax: The equation of the curve after calling the function is: y = "<<curve_parameters[0]<<"e^"<<curve_parameters[1]<<"x"<<endl;
    av_pos = max_angular_vel_mag(gx,gy,gz);//This will give us the position where the angular velocity vector's magnitude is maximum
    la_pos = max_linear_acc_mag(ax,ay,az);//This will give us the position where the linear acceleration vector's magnitude is maximum
    cout<<"The av position is: "<<av_pos<<endl;//Just printing the position of angular velocity(av)
    cout<<"The la position is: "<<la_pos<<endl;//same as above just linear acc instead of angular acceleration
    cout<<"The angular velocity vector whose magnitude is maximum is: "<<gx[av_pos]<<"i + "<<gy[av_pos]<<"j + "<<gz[av_pos]<<"k"<<" at time t = "<<t[av_pos]/1000000<<" seconds"<<endl;
    cout<<"The linear acceleration vector whose magnitude is maximum is: "<<ax[la_pos]<<"i + "<<ay[la_pos]<<"j + "<<az[la_pos]<<"k"<<" at time t = "<<t[la_pos]/1000000<<" seconds"<<endl;
	return 0;
}
//This will read the data file.
void CSV_file_reader(vector<double> &t, vector<double> &gx, vector<double> &gy, vector<double> &gz, vector<double> &ax, vector<double> &ay, vector<double> &az)
{
    int i;
    double temp=0,angular_velocity_vector[3],linear_acceleration_vector[3];
    string time,gyrox,gyroy,gyroz,accelx,accely,accelz;
    ifstream ip("data.csv");
    if(!ip.is_open()) std::cout<<"ERROR: FILE DIDN'T OPEN"<<endl;
    while(!ip.eof())
    {
        getline(ip,time,',');
        istringstream stream(time);
        while (stream >> temp)
            t.push_back(temp);

        getline(ip,gyrox,',');
        istringstream stream1(gyrox);
        while (stream1 >> temp)
            gx.push_back(temp);

        getline(ip,gyroy,',');
        istringstream stream2(gyroy);
        while (stream2 >> temp)
            gy.push_back(temp);

        getline(ip,gyroz,',');
        istringstream stream3(gyroz);
        while (stream3 >> temp)
            gz.push_back(temp);

        getline(ip,accelx,',');
        istringstream stream4(accelx);
        while (stream4 >> temp)
            ax.push_back(temp);

        getline(ip,accely,',');
        istringstream stream5(accely);
        while (stream5 >> temp)
            ay.push_back(temp);

        getline(ip,accelz,'\n');
        istringstream stream6(accelz);
        while (stream6 >> temp)
            az.push_back(temp);
    }
}

// This will return the position of the maximum magnitude of the angular velocity vector
int max_angular_vel_mag(vector<double> gyrox, vector<double> gyroy, vector<double> gyroz)
{
    double max_item; int maxIndex=0,i;
    for (i = 0; i < gyrox.size(); ++i)
    {
        if (i == 0)
            max_item = gyrox[i]*gyrox[i] + gyroy[i]*gyroy[i] + gyroz[i]*gyroz[i];
        else
            if ( gyrox[i]*gyrox[i] + gyroy[i]*gyroy[i] + gyroz[i]*gyroz[i] >= max_item)
                {
                    maxIndex = i;
                    max_item = gyrox[i]*gyrox[i] + gyroy[i]*gyroy[i] + gyroz[i]*gyroz[i];
                }
    }
    return maxIndex;
}

// This will return the position of the maximum magnitude of the linear acceleration vector
int max_linear_acc_mag(vector<double> accelx, vector<double> accely, vector<double> accelz)
{
    double max_item; int maxIndex=0,i;
    for (i = 0; i < accelx.size(); ++i)
        if (i == 0)
            max_item = accelx[i]*accelx[i] + accely[i]*accely[i] + accelz[i]*accelz[i] ;
        else
            if ( accelx[i]*accelx[i] + accely[i]*accely[i] + accelz[i]*accelz[i] >= max_item)
            {
                maxIndex = i;
                max_item = accelx[i]*accelx[i] + accely[i]*accely[i] + accelz[i]*accelz[i];
            }
    return maxIndex;
}
//I really think we dont need this.
void magnitude(vector<double> &gx, vector<double> &gy, vector<double> &gz, vector<double> &ax, vector<double> &ay, vector<double> &az)
{

    for (int i = 0; i < gx.size(); ++i)
    {
        if (gx[i] < 0)
        {
            gx[i] = -gx[i];

        }
    }
    for (int i = 0; i < gy.size(); ++i)
    {
        if (gy[i] < 0)
        {
            gy[i] = -gy[i];
        }
    }
    for (int i = 0; i < gz.size(); ++i)
    {
        if (gz[i] < 0)
        {
            gz[i] = -gz[i];
        }
    }
    for (int i = 0; i < ax.size(); ++i)
    {
        if (ax[i] < 0)
        {
            ax[i] = -ax[i];
        }
    }
    for (int i = 0; i < ay.size(); ++i)
    {
        if (ay[i] < 0)
        {
            ay[i] = -ay[i];
        }
    }
    for (int i = 0; i < az.size(); ++i)
    {
        if (az[i] < 0)
        {
            az[i] = -az[i];
        }
    }
}

//This function will perform the exponential regression
void Curve_Fit(double r[] , vector<double> x, vector<double> y)
{
  vector<double> log_y;
  int num=0,i;
  double a, b, c, s, sigmax=0, sigmax2=0, sigmay=0, sigmaxy=0;
  //This for loop converts all the zeroes into 0.01 and all negative values into positive
  for (int i = 0; i < y.size(); ++i)
  {
    if (y[i] == 0)
      y[i] = 0.01;
    if (y[i] < 0)
    {
      y[i] = -y[i];
      num += 1;// This is to count how many -ve values are there
  	}
  }
  cout<<"There are "<<num<<" negative values out of "<<y.size()<<endl;
  //Calculations for finding the exponential regression
  for (i=0; i < y.size(); ++i)
    log_y.push_back(log(y[i]));
  int n = x.size();
  for (i=0; i < x.size(); ++i)
    sigmax += x[i];
  for (i=0; i < x.size(); ++i)
    sigmax2 += x[i]+x[i];
  for (i=0; i < y.size(); ++i)
    sigmay+=y[i];
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
