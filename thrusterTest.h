// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#include <iostream>
#include <ctime>

using namespace std;


class thrusterTest{
	public:
		thrusterTest();
		~thrusterTest();
		void inputNThrusters(int numberThrusters = 1);
		void initiateTest(int numThrusters);
		void runTest(int& thrusterRequest, int& thrusterRequestNum, int& dataRequest, bool& testComplete);
		void autoInputData(double* time, double* xAcc, double* yAcc, double* zAcc, double* xRot, double* yRot, double* zRot, int numDataPoints);
		void IMUInput(double* data, int thruster = 0, int axis = 0, int numDataPoints = 1); //(axis=0 to 7 for time and each motion data,)
		void clearData();




//	private:
		int nThrusters;
		double **timeData;
		double **xAccelData;
		double **yAccelData;
		double **zAccelData;
		double **xRotData;
		double **yRotData;
		double **zRotData;
		int *dataLength;
//		double backToggle;
		
		int currentTestThruster;
		int timeStart;
		int testIncrement;

};



// TODO: reference additional headers your program requires here
