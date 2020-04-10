#include "thrusterTest.h"

thrusterTest::thrusterTest(){
	timeData = new double*[1];
	timeData[0] = new double[1];
	xAccelData = new double*[1];
	xAccelData[0] = new double[1];
	yAccelData = new double*[1];
	yAccelData[0] = new double[1];
	zAccelData = new double*[1];
	zAccelData[0] = new double[1];
	xRotData = new double*[1];
	xRotData[0] = new double[1];
	yRotData = new double*[1];
	yRotData[0] = new double[1];
	zRotData = new double*[1];
	zRotData[0] = new double[1];
	dataLength = new int[1];
	dataLength[0] = 1;
	nThrusters = 1;
	currentTestThruster = 1;
}

thrusterTest::~thrusterTest(){
	clearData();

}

void thrusterTest::inputNThrusters(int numberThrusters){
	nThrusters = numberThrusters*2 + 2;
}

void thrusterTest::initiateTest(int numThrusters){
	if (numThrusters > 0 && numThrusters <= 40){
//		clearData();
//		cout << "a" << endl;
		nThrusters = numThrusters*2 + 2;
		timeData = new double*[nThrusters];
		xAccelData = new double*[nThrusters];
		yAccelData = new double*[nThrusters];
		zAccelData = new double*[nThrusters];
		xRotData = new double*[nThrusters];
		yRotData = new double*[nThrusters];
		zRotData = new double*[nThrusters];
		dataLength = new int[nThrusters];
		int i;
		for (i = 0; i < nThrusters; i++){
			timeData[i] = new double[1];
			timeData[i][0] = 0;
			xAccelData[i] = new double[1];
			xAccelData[i][0] = 0;
			yAccelData[i] = new double[1];
			yAccelData[i][0] = 0;
			zAccelData[i] = new double[1];
			zAccelData[i][0] = 0;
			xRotData[i] = new double[1];
			xRotData[i][0] = 0;
			yRotData[i] = new double[1];
			yRotData[i][0] = 0;
			zRotData[i] = new double[1];
			zRotData[i][0] = 0;
			dataLength[i] = 1;
		}
		currentTestThruster = 0;
		testIncrement = 1;
	}
	else
		cerr << "thrusterTest::initiateTest number of thrusters must be between 1 and 40" << endl;
}

// Function called continuously by software, can be at users chosen frequency, any frequency at least as high as 0.5 Hz is sufficient.
// DataRequest -1 means stop IMU. 1 means start. 2 means send current data arrays into autoInputData.
// ThrusterRequest -1 means stop thruster(thrusterRequestNum). 1 means start full power. 2 means start full power backwards. 3 means release from 90 deg.
void thrusterTest::runTest(int& thrusterRequest, int& thrusterRequestNum, int& dataRequest, bool& testComplete){
	time_t presentTime; 
	int testTime;
	testComplete = false;
	if (currentTestThruster < nThrusters - 2 ){
		if (testIncrement == 1){
			thrusterRequestNum = currentTestThruster;
			thrusterRequest = 0;
			dataRequest = 1;
			testIncrement = 2;
			presentTime = time(0);
			timeStart = presentTime;
		}
		else if (testIncrement == 2){
			presentTime = time(0);
			testTime = presentTime;
			thrusterRequestNum = currentTestThruster;
			dataRequest = 0;
			if (testTime - timeStart > 1){
				if ((currentTestThruster) % 2 == 1){
					thrusterRequest = 2;
				}
				else{
					thrusterRequest = 1;
				}
				presentTime = time(0);
				timeStart = presentTime;
				testIncrement = 3;
			}
			else
				testIncrement = 2;
		}
		else if (testIncrement == 3){
			presentTime = time(0);
			testTime = presentTime;
			thrusterRequestNum = currentTestThruster;
			dataRequest = 0;
			if (testTime - timeStart > 5){
				thrusterRequest = -1;
				dataRequest = -1;
				testIncrement = 4;
			}
			else{
				thrusterRequest = 0;
				testIncrement = 3;
			}
		}
		else if (testIncrement == 4){
			thrusterRequest = 0;
			thrusterRequestNum = currentTestThruster;
			dataRequest = 2;
			presentTime = time(0);
			timeStart = presentTime;
			testIncrement = 5;
		}
		else if (testIncrement == 5){
			presentTime = time(0);
			testTime = presentTime;
			thrusterRequest = 0;
			thrusterRequestNum = currentTestThruster;
			dataRequest = 0;
			if (testTime - timeStart >= 14){
				testIncrement = 1;
				currentTestThruster++;
			}
			else{
				testIncrement = 5;
			}
		}
	}
	else if (currentTestThruster >= nThrusters - 2){
		if (currentTestThruster < nThrusters){
			if (testIncrement == 1){
				if ((currentTestThruster) % 2 == 1){
					cout << "Place vehicle at 90 degrees from Z axis, pointing nose down or up." << endl;
				}
				else{
					cout << "Please place vehicle at 90 degrees from Z axis, with left side facing up." << endl;
				}
				presentTime = time(0);
				timeStart = presentTime;
				thrusterRequest = 0;
				dataRequest = 0;
				thrusterRequestNum = currentTestThruster;
				testIncrement = 2;
			}
			else if (testIncrement == 2){
				dataRequest = 0;
				presentTime = time(0);
				testTime = presentTime;
				thrusterRequest = 0;
				thrusterRequestNum = currentTestThruster;
				if (testTime - timeStart >= 15){
					dataRequest = 1;
					testIncrement = 3;
				}
				else {
					dataRequest = 0;
				}
			}

			else if (testIncrement == 3){
				thrusterRequest = 3;
				cout << "Release Vehicle" << endl;
				thrusterRequestNum = currentTestThruster;
				dataRequest = 0;
				presentTime = time(0);
				timeStart = presentTime;
				testIncrement = 4;
			}
			else if (testIncrement == 4){
				thrusterRequest = 0;
				thrusterRequestNum = currentTestThruster;
				presentTime = time(0);
				testTime = presentTime;
				if (testTime - timeStart >= 6){
					dataRequest = -1;
					testIncrement = 5;
				}
				else{
					dataRequest = 0;
				}
			}
			else if (testIncrement == 5){
				dataRequest = 0;
				currentTestThruster++;
				testIncrement = 1;
				presentTime = time(0);
				timeStart = presentTime;
			}
		}
		else{
			dataRequest = 0;
			thrusterRequest = 0;
			thrusterRequestNum = currentTestThruster-1;
			bool testComplete = true;
//			cout << "Calibration Testing Completed." << endl;
		}
	}
	
}

void thrusterTest::autoInputData(double* time, double* xAcc, double* yAcc, double* zAcc, double* xRot, double* yRot, double* zRot, int numDataPoints){
	if (currentTestThruster )
	IMUInput(time, currentTestThruster, 0, numDataPoints);
	IMUInput(xAcc, currentTestThruster, 1, numDataPoints);
	IMUInput(yAcc, currentTestThruster, 2, numDataPoints);
	IMUInput(zAcc, currentTestThruster, 3, numDataPoints);
	IMUInput(xRot, currentTestThruster, 4, numDataPoints);
	IMUInput(yRot, currentTestThruster, 5, numDataPoints);
	IMUInput(zRot, currentTestThruster, 6, numDataPoints);
}

void thrusterTest::IMUInput(double* data, int thrusterNum, int axis, int numDataPoints){
	if (thrusterNum >= 0 && thrusterNum < nThrusters){
		if (axis >= 0 && axis <= 6){
			if (axis == 0){
				delete[] timeData[thrusterNum];
				timeData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					timeData[thrusterNum][i] = data[i];
			}
			else if (axis == 1){
				delete[] xAccelData[thrusterNum];
				xAccelData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					xAccelData[thrusterNum][i] = data[i];
			}
			else if (axis == 2){
				delete[] xAccelData[thrusterNum];
				xAccelData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					xAccelData[thrusterNum][i] = data[i];
			}
			else if (axis == 3){
				delete[] xAccelData[thrusterNum];
				xAccelData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					xAccelData[thrusterNum][i] = data[i];
			}
			else if (axis == 4){
				delete[] xRotData[thrusterNum];
				xRotData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					xRotData[thrusterNum][i] = data[i];
			}
			else if (axis == 5){
				delete[] yRotData[thrusterNum];
				yRotData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					yRotData[thrusterNum][i] = data[i];
			}
			else if (axis == 6){
				delete[] zRotData[thrusterNum];
				zRotData[thrusterNum] = new double[numDataPoints];
				int i;
				for (i = 0; i < numDataPoints; i++)
					zRotData[thrusterNum][i] = data[i];
			}
			dataLength[thrusterNum] = numDataPoints;
		}
		else
			cerr << "thrusterTest::IMUInput axis number out of range" << endl;
	}
	else
		cerr << "thrusterTest::IMUInput thrusterNum out of range." << endl;
}

void thrusterTest::clearData(){
	int i;
	for (i = 0; i < nThrusters; i++){
		delete[] timeData[i];
		delete[] xAccelData[i];
		delete[] yAccelData[i];
		delete[] zAccelData[i];
		delete[] xRotData[i];
		delete[] yRotData[i];
		delete[] zRotData[i];
	}
	delete [] timeData;
	delete [] xAccelData;
	delete [] yAccelData;
	delete [] zAccelData;
	delete [] xRotData;
	delete [] yRotData;
	delete [] zRotData;
	delete dataLength;
};
