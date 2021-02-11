#pragma once

#include "Mathematics.h"
#include "Vector2D.h"
#include "Vector3D.h"

typedef struct Quaternion {
public:
	float W = 1.0f;
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	Quaternion();
	Quaternion(const Quaternion& quaternion);
	Quaternion(Vector3D vector);
	Quaternion(float W, float X, float Y, float Z);

  Vector2D RotateVector(Vector2D coordinate);
  Vector2D UnrotateVector(Vector2D coordinate);
	Vector3D RotateVector(Vector3D coordinate);
	Vector3D UnrotateVector(Vector3D coordinate);
	Vector3D GetBiVector();

	Quaternion Add(Quaternion quaternion);
	Quaternion Subtract(Quaternion quaternion);
	Quaternion Multiply(Quaternion quaternion);
	Quaternion Multiply(float scalar);
	Quaternion Divide(Quaternion quaternion);
	Quaternion Divide(float scalar);
	Quaternion Power(Quaternion quaternion);

	Quaternion Power(float exponent);
	Quaternion Permutate(Vector3D permutation);

	Quaternion Absolute();
	Quaternion AdditiveInverse();
	Quaternion MultiplicativeInverse();
	Quaternion Conjugate();
	Quaternion UnitQuaternion();

	float Magnitude();
	float DotProduct(Quaternion quaternion);
	float Normal();

	bool IsNaN();
	bool IsFinite();
	bool IsInfinite();
	bool IsNonZero();
	bool IsEqual(Quaternion quaternion);

	String ToString();

	//Static functions
	static Quaternion SphericalInterpolation(Quaternion q1, Quaternion q2, float ratio);

	static Quaternion Add(Quaternion q1, Quaternion q2) {
		return q1.Add(q2);
	}

	static Quaternion Subtract(Quaternion q1, Quaternion q2) {
		return q1.Subtract(q2);
	}

	static Quaternion Multiply(Quaternion q1, Quaternion q2) {
		return q1.Multiply(q2);
	}

	static Quaternion Divide(Quaternion q1, Quaternion q2) {
		return q1.Divide(q2);
	}

	static Quaternion Power(Quaternion q1, Quaternion q2) {
		return q1.Power(q2);
	}

	static float DotProduct(Quaternion q1, Quaternion q2) {
		return q1.DotProduct(q2);
	}


	static Quaternion Power(Quaternion quaternion, float exponent) {
		return quaternion.Power(exponent);
	}

	static Quaternion Permutate(Quaternion quaternion, Vector3D vector) {
		return quaternion.Permutate(vector);
	}

	static Quaternion Absolute(Quaternion quaternion) {
		return quaternion.Absolute();
	}

	static Quaternion AdditiveInverse(Quaternion quaternion) {
		return quaternion.AdditiveInverse();
	}

	static Quaternion MultiplicativeInverse(Quaternion quaternion) {
		return quaternion.MultiplicativeInverse();
	}

	static Quaternion Conjugate(Quaternion quaternion) {
		return quaternion.Conjugate();
	}

	static Quaternion UnitQuaternion(Quaternion quaternion) {
		return quaternion.UnitQuaternion();
	}

	static float Magnitude(Quaternion quaternion) {
		return quaternion.Magnitude();
	}

	static float Normal(Quaternion quaternion) {
		return quaternion.Normal();
	}

	//Operator overloads
	bool operator ==(Quaternion quaternion) {
		return this->IsEqual(quaternion);
	}

	bool operator !=(Quaternion quaternion) {
		return !(this->IsEqual(quaternion));
	}

	Quaternion operator =(Quaternion quaternion) {
		this->W = quaternion.W;
		this->X = quaternion.X;
		this->Y = quaternion.Y;
		this->Z = quaternion.Z;
		
		return quaternion;
	}

	Quaternion operator  +(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Add(quaternion);
	}

	Quaternion operator  -(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Subtract(quaternion);
	}

	Quaternion operator  *(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Multiply(quaternion);
	}

	Quaternion operator  /(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Divide(quaternion);
	}


	Quaternion operator  /(float value) {
		Quaternion q = Quaternion(*this);

		return q.Divide(value);
	}

	friend Quaternion operator *(float scalar, Quaternion q);
	friend Quaternion operator *(Quaternion q, float scalar);
} Quaternion;
