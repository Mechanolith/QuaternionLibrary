#pragma once
#include <math.h>
#include "kf/kf_vector3.h"

template <typename T>

struct Quaternion
{
public:
	//Constructors
	//New Quaternion (starts as identity)
	Quaternion(T _w = 1, T _x = 0, T _y = 0, T _z = 0);

	//New Quaternion from another quaternion
	Quaternion(const Quaternion<T>& inQuat);

	//New Qauternion from angle & Axis
	Quaternion(T _angle, const kf::Vector3T<T>& _axis);

	//New Quaternion from EulerAngles
	Quaternion(const kf::Vector3T<T>& _angles);
	
	//Operators
	//Addition
	Quaternion<T> operator + (const Quaternion<T>& quat) const;
	Quaternion<T> operator += (const Quaternion<T>& quat);

	//Multiplication
	Quaternion<T> operator * (const Quaterion<T>& quat) const;
	Quaternion<T> operator *= (const Quaterion<T>& quat);

	//Functions
	//Return the Magnitude of this Quaternion (as if it were a Vector4);
	T Magnitude() const;

	//Make This Quaternion a Unit Quaternion
	void Normalise();

	//Return This Quaternion as a Unit Quaternion
	Quaternion<T> Normalised() const;

	//Return this inverse of this Quaternion
	Quaternion<T> Inverse() const;

	//Rotate A Vector3 by this Quaternion
	kf::Vector3T<T> RotateVector(const kf::Vector3T<T>& _vec) const;

	//Find the difference between this and an input Quaternion
	Quaternion<T> DifferenceBetween(const Quaternion<T>& quat) const;

	//Set the EulerAngles of this Quaternion
	void SetEulerAngles(const kf::Vector3T<T>& _angles) const;

	//Return the scalar of the dot product between this and an input Quaternion
	T Dot(const Quaternion<T>& quat) const;

public:
	T w;
	T x;
	T y;
	T z;
};

typedef Quaternion <float> QuaternionF;
typedef Quaternion <double> QuaternionD;

//Construct new Quaternion
template <typename T>
Quaternion<T>::Quaternion(T _w, T _x, T _y, T _z) : w(_w), x(_x), y(_y), z(_z)
{
}

template <typename T>
Quaternion<T>::Quaternion(const Quaternion<T>& inQuat) : w(inQuat.w), x(inQuat.x), y(inQuat.y), z(inQuat.z) 
{
}

template <typename T>
Quaternion<T>::Quaternion(T _angle, const kf::Vector3T<T>& _axis) 
{
	w = cos(_angle / 2);
	x = _axis.x * sin(_angle / 2);
	y = _axis.y * sin(_angle / 2);
	z = _axis.z * sin(_angle / 2);
}

template<typename T>
inline Quaternion<T>::Quaternion(const kf::Vector3T<T>& _angles)
{
	//This is terrible and ugle. Surely there's a better way...
	kf::Vector3T<T> xAxis = (1,0,0);
	kf::Vector3T<T> yAxis = (0,1,0);
	kf::Vector3T<T> zAxis = (0,0,1);

	Quaternion<T> xQuat = Quaternion(_angles.x, xAxis);
	Quaternion<T> yQuat = Quaternion(_angles.y, yAxis);
	Quaternion<T> zQuat = Quaternion(_angles.z, zAxis);

	Quaternion<T> outQuat = Quaternion<T>();
	outQuat *= xQuat;
	outQuat *= yQuat;
	outQuat *= zQuat;

	w = outQuat.w;
	x = outQuat.x;
	y = outQuat.y;
	z = outQuat.z;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& quat) const
{
	Quaternion<T> out;

	out.w = w + quat.w;
	out.x = x + quat.x;
	out.y = y + quat.y;
	out.z = z + quat.z;

	return out;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator+=(const Quaternion<T>& quat)
{
	w += quat.w;
	x += quat.x;
	y += quat.y;
	z += quat.z;

	return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator * (const Quaterion<T>& quat) const
{
	Quaternion<T> out;

	out.w = (w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z);
	out.x = (w * quat.x) + (x * quat.w) + (y * quat.z) - (z * quat.y);
	out.y = (w * quat.y) + (y * quat.w) + (z * quat.x) - (x * quat.z);
	out.z = (w * quat.z) + (z * quat.w) + (x * quat.y) - (y * quat.x);

	return out;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator *= (const Quaterion<T>& quat)
{
	Quaternion<T> out;

	out.w = (w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z);
	out.x = (w * quat.x) + (x * quat.w) + (y * quat.z) - (z * quat.y);
	out.y = (w * quat.y) + (y * quat.w) + (z * quat.x) - (x * quat.z);
	out.z = (w * quat.z) + (z * quat.w) + (x * quat.y) - (y * quat.x);

	this = out;

	return *this;
}

template <typename T>
T Quaternion<T>::Magnitude() const
{
	return sqrt((w * w) + (x * x) + (y * y) + (z * z));
}

template <typename T>
void Quaternion<T>::Normalise() 
{
	T magnitude = Magnitude();

	if (magnitude > 0) 
	{
		w = w / magnitude;
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
}

template <typename T>
Quaternion<T> Quaternion<T>::Normalised() const
{
	T magnitude = Magnitude();
	Quaternion<T> quat;

	if (magnitude > 0)
	{
		quat.w = w / magnitude;
		quat.x = x / magnitude;
		quat.y = y / magnitude;
		quat.z = z / magnitude;
	}

	return quat;
}

template <typename T>
Quaternion<T> Quaternion<T>::Inverse() const
{
	Quaternion<T> inv;

	inv.x *= -1;
	inv.y *= -1;
	inv.z *= -1;

	if (Magnitude() != 1) 
	{
		//Divide
	}

	return inv;
}

template<typename T>
inline kf::Vector3T<T> Quaternion<T>::RotateVector(const kf::Vector3T<T>& _vec) const
{
	Quaternion<T> vecQuat;
	vecQuat = Quaternion(0, _vec.x, _vec.y, _vec.z);

	Quaternion<T> outQuat;
	outQuat = this * vecQuat;
	outQuat *= Inverse();

	kf::Vector3T<T> outVec;
	outVec.x = outQuat.x;
	outVec.y = outQuat.y;
	outVec.z = outQuat.z;

	return outVec;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::DifferenceBetween(const Quaternion<T>& quat) const
{
	return Inverse() * quat;
}

template<typename T>
inline void Quaternion<T>::SetEulerAngles(const kf::Vector3T<T>& _angles) const
{
	Quaternion<T> quat = Quaternion<T>(_angles);

	w = quat.w;
	x = quat.x;
	y = quat.y;
	z = quat.z;
}

template<typename T>
inline T Quaternion<T>::Dot(const Quaternion<T>& quat) const
{
	return (w * quat.w) + (x * quat.x) + (y * quat.y) + (z  * quat.z);
}
