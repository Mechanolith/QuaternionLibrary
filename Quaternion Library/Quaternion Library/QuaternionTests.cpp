#include <iostream>
#include <string>
#include "Quaternion.h"
#include "windows.h"
#include "OutputFunctions.h"

int main() 
{
	OutputFunctions output = OutputFunctions();

	//General Variables
	kf::Vector3f& xAxis = kf::Vector3f(1, 0, 0);
	kf::Vector3f& yAxis = kf::Vector3f(0, 1, 0);
	kf::Vector3f& zAxis = kf::Vector3f(0, 0, 1);

	//Test Identity Construction
	QuaternionF fQuat = Quaternion<float>();	
	output.OutputQuat("F Quat Identity", fQuat);
	
	//Test Euler Assign
	kf::Vector3f& newAngles = kf::Vector3f(90.0f,0.0f,0.0f);
	fQuat.SetEulerAngles(newAngles);
	output.OutputQuat("F Quat 90 X Rot", fQuat);

	//Test Euler Construction
	QuaternionF eQuat = Quaternion<float>(newAngles);
	output.OutputQuat("Euler Quat Constructor", eQuat);

	//Test Axis/Angle Construction
	QuaternionF aaQuat = Quaternion<float>(90.0f, xAxis);
	output.OutputQuat("Angle/Axis Quat Constructor", aaQuat);

	//Test Multiplication
	QuaternionF mQuat = Quaternion<float>(90.0f, yAxis);
	QuaternionF zQuat = Quaternion<float>(90.0f, zAxis);
	mQuat *= aaQuat;
	mQuat *= zQuat;
	output.OutputQuat("Multiplied Quat", mQuat);

	//Test From-Quaternion Constructor
	QuaternionF fqQuat = Quaternion<float>(mQuat);
	output.OutputQuat("From-Quaternion Quat", fqQuat);

	//Test Inverse
	QuaternionF invQuat = Quaternion<float>(fqQuat.Inverse());
	output.OutputQuat("Inverse Quat", invQuat);

	//Test Distance Between
	QuaternionF idQuat = Quaternion<float>();
	output.OutputQuat("Distance Between Quat", idQuat.DifferenceBetween(aaQuat));

	//Test Dot Product
	output.OutputNum("Dot Scalar", zQuat.Dot(aaQuat));

	//Test Rotate Vector
	kf::Vector3f& testVec = kf::Vector3f(xAxis);
	QuaternionF yQuat = Quaternion<float>(90.0f, yAxis);
	output.OutputVec("Rotated Vector", yQuat.RotateVector(testVec));

	//Test Addition
	output.OutputQuat("Added Quats", yQuat + zQuat);

	//Test Additive Assign
	QuaternionF addQuat = yQuat;
	addQuat += zQuat;
	output.OutputQuat("Added Assign Quat", addQuat);

	//Test Magnitude
	output.OutputNum("zQuat Magnitude", zQuat.Magnitude());

	//Test Normalisation
	QuaternionF normQuat = QuaternionF(0.0f, 10.0f, 0.0f, 0.0f);
	output.OutputQuat("Normalised (Return) Quat", normQuat.Normalised());
	normQuat.Normalise();
	output.OutputQuat("Normalised (Assign) Quat", normQuat);

	//End
	std::cout << "Main function has run." << std::endl;
	std::cout << std::endl;

	return 0;
}

