#pragma once
#include <string>
#include <iostream>
#include "Quaternion.h"
#include "kf\kf_vector3.h"

class OutputFunctions
{
public:
	void OutputQuat(std::string name, QuaternionD quat);
	void OutputQuat(std::string name, QuaternionF quat);
	void OutputNum(std::string name, float numf);
	void OutputNum(std::string name, double numd);
	void OutputVec(std::string name, kf::Vector3f vec);

public:
	OutputFunctions();
	~OutputFunctions();
};

