#include "Vector2D.h"

Vector2D::Vector2D() {
	this->X = 0.0;
	this->Y = 0.0;
}

Vector2D::Vector2D(const Vector2D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
}

Vector2D::Vector2D(float X, float Y) {
	this->X = X;
	this->Y = Y;
}

Vector2D::Vector2D(const Vector3D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
}

Vector2D Vector2D::Absolute() {
	return Vector2D{
		(float)fabs(this->X),
		(float)fabs(this->Y)
	};
}

Vector2D Vector2D::Normal() {
	return Multiply(this->Magnitude() == 0 ? 3.40282e+038f : 1 / this->Magnitude());
}

Vector2D Vector2D::Add(Vector2D vector) {
	return Vector2D{
		this->X + vector.X,
		this->Y + vector.Y
	};
}

Vector2D Vector2D::Subtract(Vector2D vector) {
	return Vector2D{
		this->X - vector.X,
		this->Y - vector.Y
	};
}

Vector2D Vector2D::Multiply(Vector2D vector) {
	return Vector2D{
		this->X * vector.X,
		this->Y * vector.Y
	};
}

Vector2D Vector2D::Divide(Vector2D vector) {
	return Vector2D{
		this->X / vector.X,
		this->Y / vector.Y
	};
}

Vector2D Vector2D::Multiply(float scalar) {
	return Vector2D{
		this->X * scalar,
		this->Y * scalar
	};
}

Vector2D Vector2D::Divide(float scalar) {
	return Vector2D{
		this->X / scalar,
		this->Y / scalar
	};

}

Vector3D Vector2D::CrossProduct(Vector2D vector) {
	return Vector3D{
		0.0f,
		0.0f,
		(this->X * vector.Y) - (this->Y * vector.X)
	};
}

Vector2D Vector2D::UnitCircle() {
	Vector2D vector = Vector2D(this->X, this->Y);
	float length = vector.Magnitude();

	if (length == 1) return vector;
	if (length == 0) return Vector2D(0, 1);

	return Vector2D{
		vector.X / length,
		vector.Y / length
	};
}

Vector2D Vector2D::Constrain(float minimum, float maximum) {
	Vector2D vector = Vector2D(this->X, this->Y);

	vector.X = Mathematics::Constrain(X, minimum, maximum);
	vector.Y = Mathematics::Constrain(Y, minimum, maximum);

	return vector;
}

Vector2D Vector2D::Constrain(Vector2D minimum, Vector2D maximum) {
	Vector2D vector = Vector2D(this->X, this->Y);

	vector.X = Mathematics::Constrain(X, minimum.X, maximum.X);
	vector.Y = Mathematics::Constrain(Y, minimum.Y, maximum.Y);

	return vector;
}

Vector2D Vector2D::Minimum(Vector2D v1, Vector2D v2) {
	return Vector2D{
		v1.X < v2.X ? v1.X : v2.X,
		v1.Y < v2.Y ? v1.Y : v2.Y
	};
}

Vector2D Vector2D::Maximum(Vector2D v1, Vector2D v2) {
	return Vector2D{
		v1.X > v2.X ? v1.X : v2.X,
		v1.Y > v2.Y ? v1.Y : v2.Y
	};
}

float Vector2D::Magnitude() {
	Vector2D vector = Vector2D(this->X, this->Y);

	return sqrtf(DotProduct(vector, vector));
}

float Vector2D::DotProduct(Vector2D vector) {
	return (this->X * vector.X) + (this->Y * vector.Y);
}

float Vector2D::CalculateEuclideanDistance(Vector2D vector) {
	return sqrtf(powf(this->X - vector.X, 2) + powf(this->Y - vector.Y, 2));
}

bool Vector2D::IsEqual(Vector2D vector) {
	return (this->X == vector.X) && (this->Y == vector.Y);
}

String Vector2D::ToString() {
	String x = Mathematics::DoubleToCleanString(this->X);
	String y = Mathematics::DoubleToCleanString(this->Y);

	return "[" + x + ", " + y + "]";
}
