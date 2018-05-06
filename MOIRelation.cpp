

#include "MOIRelation.h"


MOIRelation::MOIRelation(){
	angAccelX = new double[1];
	angAccelX[0] = 1;
	angAccelY = new double[1];
	angAccelY[0] = 1;
	angAccelZ = new double[1];
	angAccelZ[0] = 1;

}
MOIRelation::~MOIRelation(){
	clearData();
}

void MOIRelation::configNThrusters(int nThrusters){
	numThrusters = nThrusters;
	delete angAccelX;
	delete angAccelY;
	delete angAccelZ;
	int i;
	angAccelX = new double[nThrusters];
	for (i = 0; i < nThrusters; i++){
		angAccelX[i] = 0;
	}
	angAccelY = new double[nThrusters];
	for (i = 0; i < nThrusters; i++){
		angAccelY[i] = 0;
	}
	angAccelZ = new double[nThrusters];
	for (i = 0; i < nThrusters; i++){
		angAccelZ[i] = 0;
	}
}


void MOIRelation::inputAngAcc(int thrusterNum, int axis, double angAcc){ //axis 1 = x, axis 2 = y, axis 3 = z;
	if (axis == 1)
		angAccelX[thrusterNum] = angAcc;
	else if (axis == 2)
		angAccelY[thrusterNum] = angAcc;
	else if (axis == 3)
		angAccelZ[thrusterNum] = angAcc;
}

void MOIRelation::inputAngAccBuoyancy(int axis, double angAcc){ //axis 1 = x; axis 2 = y;
	if (axis == 1)
		angAccelBuoyancyX = angAcc;
	else if (axis == 2)
		angAccelBuoyancyY = angAcc;
}

void MOIRelation::findGreatestRotThrusters(){
	int i;
	double greatestXAcc;
	double greatestYAcc;
	double greatestZAcc;
	greatestXAcc = angAccelX[0];
	greatestYAcc = angAccelY[0];
	greatestZAcc = angAccelZ[0];
	int greatestThrusterY = 0;
	int greatestThrusterZ = 0;
	int greatestThrusterX = 0;
	for (i = 1; i < numThrusters; i++){
		if (angAccelX[i] > greatestXAcc){
			greatestXAcc = angAccelX[i];
			greatestThrusterX = i;
		}
		if (angAccelY[i] > greatestYAcc){
			greatestYAcc = angAccelY[i];
			greatestThrusterY = i;
		}
		if (angAccelZ[i] > greatestZAcc){
			greatestZAcc = angAccelZ[i];
			greatestThrusterZ = i;
		}
	}
	thrustGreatestX = greatestThrusterX;
	thrustGreatestY = greatestThrusterY;
	thrustGreatestZ = greatestThrusterZ;
}


void MOIRelation::estimateMOIRelation(){  //Function assumes that two thrusters with greatest influence on Z and other axis and tangentially equidistance from COM.
	int i;
	double MOIYoverX = angAccelBuoyancyX / angAccelBuoyancyY;
	
	
	double estimatedAngAccZ;
	estimatedAngAccZ = pow(angAccelX[thrustGreatestZ] * angAccelX[thrustGreatestZ] + angAccelY[thrustGreatestZ] * angAccelY[thrustGreatestZ] + angAccelZ[thrustGreatestZ] * angAccelZ[thrustGreatestZ], 0.5);
	//  This executes if the X axis has a thruster with greater incluence on it than the Y axis.
	if (angAccelX[thrustGreatestX] / MOIYoverX > angAccelX[thrustGreatestY] * MOIYoverX){
		double estimatedAngAccX;
		double MOIZoverX;
		estimatedAngAccX = pow(angAccelX[thrustGreatestX] * angAccelX[thrustGreatestX] + angAccelY[thrustGreatestX] * angAccelY[thrustGreatestX] * MOIYoverX * MOIYoverX + angAccelZ[thrustGreatestX] * angAccelZ[thrustGreatestX], 0.5);
		MOIZoverX = estimatedAngAccX / estimatedAngAccZ;
		MOIUnitX = 1 / (MOIYoverX * (1 + MOIYoverX + MOIZoverX));
		MOIUnitY = MOIYoverX / (1 + MOIYoverX + MOIZoverX);
		MOIUnitZ = MOIZoverX / (1 + MOIYoverX + MOIZoverX);
	}
	else{
		double estimatedAngAccY;
		double MOIZoverY;
		double MOIZoverX;
		estimatedAngAccY = pow(angAccelY[thrustGreatestY] * angAccelY[thrustGreatestY] + angAccelX[thrustGreatestY] * angAccelX[thrustGreatestY] / (MOIYoverX * MOIYoverX) + angAccelZ[thrustGreatestY] * angAccelZ[thrustGreatestY], 0.5);
		MOIZoverY = estimatedAngAccY / estimatedAngAccZ;
		MOIZoverX = MOIZoverY*MOIYoverX;
		MOIUnitX = 1 / (MOIYoverX * (1 + MOIYoverX + MOIZoverX));
		MOIUnitY = MOIYoverX / (1 + MOIYoverX + MOIZoverX);
		MOIUnitZ = MOIZoverX / (1 + MOIYoverX + MOIZoverX);
	}
}

void MOIRelation::getMOIRelations(double& MOIRelX, double& MOIRelY, double& MOIRelZ){
	MOIRelX = MOIUnitX;
	MOIRelY = MOIUnitX;
	MOIRelZ = MOIUnitZ;
}

void MOIRelation::getGreatestThrusters(int& thrusterX, int& thrusterY, int& thrusterZ){
	thrusterX = thrustGreatestX;
	thrusterY = thrustGreatestY;
	thrusterZ = thrustGreatestZ;
}


void MOIRelation::clearData(){
	delete angAccelX;
	delete angAccelY;
	delete angAccelZ;
}

