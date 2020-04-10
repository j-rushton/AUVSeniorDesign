// MOIRelation class assumes that angular acceleration magnitudes from thruster response and buoyancy are entered from externally. 
// MOIRelation::estimateMOIRelation contains errors.
#include <iostream>
#include <cmath>

using namespace std;


class MOIRelation{
	public: 
		MOIRelation();
		~MOIRelation();
		void configNThrusters(int nThrusters);
		void inputAngAcc(int thrusterNum, int axis, double angAcc);  // Thrusters start at thruster zero. Axis start at one.
		void inputAngAccBuoyancy(int axis,double angAcc);
		void findGreatestRotThrusters(); // After data is input, searches for the thrusters with greatest influence on each axis.
		void estimateMOIRelation();

		void getGreatestThrusters(int& thrusterX, int& thrusterY, int& thrusterZ); 
		void getMOIRelations(double& MOIRelX, double& MOIRelY, double& MOIRelZ);
		void clearData();
//	private:
		double MOIUnitX; // The following three veriables add to one and specify the magnitude of MOI in relation to the sum of MOI.
		double MOIUnitY;
		double MOIUnitZ;
		double *angAccelX;
		double *angAccelY;
		double *angAccelZ;
		double angAccelBuoyancyX;
		double angAccelBuoyancyY;
		int thrustGreatestX;
		int thrustGreatestY;
		int thrustGreatestZ;
		int numThrusters;
};