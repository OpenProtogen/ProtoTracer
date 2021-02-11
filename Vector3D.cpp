#include "Vector3D.h"

Vector3D::Vector3D() {
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
}

Vector3D::Vector3D(const Vector3D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

Vector3D::Vector3D(float X, float Y, float Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vector3D Vector3D::Absolute() {
	return Vector3D{
		(float)fabs(this->X),
		(float)fabs(this->Y),
		(float)fabs(this->Z)
	};
}

Vector3D Vector3D::Normal() {
	return Multiply(this->Magnitude() == 0 ? 3.40282e+038f : 1.0f / this->Magnitude());
}

Vector3D Vector3D::Add(Vector3D vector) {
	return Vector3D{
		this->X + vector.X,
		this->Y + vector.Y,
		this->Z + vector.Z 
	};
}

Vector3D Vector3D::Subtract(Vector3D vector) {
	return Vector3D {
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z 
	};
}

Vector3D Vector3D::Multiply(Vector3D vector) {
	return Vector3D {
		this->X * vector.X,
		this->Y * vector.Y,
		this->Z * vector.Z 
	};
}

Vector3D Vector3D::Divide(Vector3D vector) {
	return Vector3D {
		this->X / vector.X,
		this->Y / vector.Y,
		this->Z / vector.Z 
	};
}

Vector3D Vector3D::Multiply(float scalar) {
	return Vector3D {
		this->X * scalar,
		this->Y * scalar,
		this->Z * scalar 
	};
}

Vector3D Vector3D::Divide(float scalar) {
	return Vector3D {
		this->X / scalar,
		this->Y / scalar,
		this->Z / scalar
	};

}

Vector3D Vector3D::CrossProduct(Vector3D vector) {
	return Vector3D {
		(this->Y * vector.Z) - (this->Z * vector.Y),
		(this->Z * vector.X) - (this->X * vector.Z),
		(this->X * vector.Y) - (this->Y * vector.X) 
	};
}

Vector3D Vector3D::UnitSphere() {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);
	float length = vector.Magnitude();

	if (length == 1.0f) return vector;
	if (length == 0.0f) return Vector3D(0.0f, 1.0f, 0.0f);

	return Vector3D {
		vector.X / length,
		vector.Y / length,
		vector.Z / length 
	};
}

Vector3D Vector3D::Constrain(float minimum, float maximum) {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	vector.X = Mathematics::Constrain(X, minimum, maximum);
	vector.Y = Mathematics::Constrain(Y, minimum, maximum);
	vector.Z = Mathematics::Constrain(Z, minimum, maximum);

	return vector;
}

Vector3D Vector3D::Constrain(Vector3D minimum, Vector3D maximum) {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	vector.X = Mathematics::Constrain(X, minimum.X, maximum.X);
	vector.Y = Mathematics::Constrain(Y, minimum.Y, maximum.Y);
	vector.Z = Mathematics::Constrain(Z, minimum.Z, maximum.Z);

	return vector;
}

float Vector3D::Magnitude() {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	return sqrtf(DotProduct(vector, vector));
}

float Vector3D::DotProduct(Vector3D vector) {
	return (this->X * vector.X) + (this->Y * vector.Y) + (this->Z * vector.Z);
}

float Vector3D::CalculateEuclideanDistance(Vector3D vector) {
	return sqrtf(powf(this->X - vector.X, 2.0f) + powf(this->Y - vector.Y, 2.0f) + powf(this->Z - vector.Z, 2.0f));
}

bool Vector3D::IsEqual(Vector3D vector) {
	return (this->X == vector.X) && (this->Y == vector.Y) && (this->Z == vector.Z);
}

String Vector3D::ToString() {
	String x = Mathematics::DoubleToCleanString(this->X);
	String y = Mathematics::DoubleToCleanString(this->Y);
	String z = Mathematics::DoubleToCleanString(this->Z);

	return "[" + x + ", " + y + ", " + z + "]";
}
