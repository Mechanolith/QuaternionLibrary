#include "OutputFunctions.h"



OutputFunctions::OutputFunctions()
{
}


OutputFunctions::~OutputFunctions()
{
}

void OutputFunctions::OutputQuat(std::string name, QuaternionD quat)
{
	std::cout << "Outputting: " << name << std::endl;
	std::cout << "W: " << quat.w << std::endl;
	std::cout << "X: " << quat.x << std::endl;
	std::cout << "Y: " << quat.y << std::endl;
	std::cout << "Z: " << quat.z << std::endl;
	std::cout << std::endl;
}

void OutputFunctions::OutputQuat(std::string name, QuaternionF quat)
{
	std::cout << "Outputting: " << name << std::endl;
	std::cout << "W: " << quat.w << std::endl;
	std::cout << "X: " << quat.x << std::endl;
	std::cout << "Y: " << quat.y << std::endl;
	std::cout << "Z: " << quat.z << std::endl;
	std::cout << std::endl;
}

void OutputFunctions::OutputNum(std::string name, float numf)
{
	std::cout << "Outputting: " << name << std::endl;
	std::cout << name << ": " << numf << std::endl;
	std::cout << std::endl;
}

void OutputFunctions::OutputNum(std::string name, double numd)
{
	std::cout << "Outputting: " << name << std::endl;
	std::cout << name << ": " << numd << std::endl;
	std::cout << std::endl;
}

void OutputFunctions::OutputVec(std::string name, kf::Vector3f vec)
{
	std::cout << "Outputting: " << name << std::endl;
	std::cout << "X: " << vec.x << std::endl;
	std::cout << "Y: " << vec.y << std::endl;
	std::cout << "Z: " << vec.z << std::endl;
	std::cout << std::endl;
}
