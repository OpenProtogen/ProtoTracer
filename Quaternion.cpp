#include "Quaternion.h"

Quaternion::Quaternion() {
	this->W = 1.0f;
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
}

Quaternion::Quaternion(const Quaternion& quaternion) {
	this->W = quaternion.W;
	this->X = quaternion.X;
	this->Y = quaternion.Y;
	this->Z = quaternion.Z;
}

Quaternion::Quaternion(Vector3D vector) {
	this->W = 0;
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
	this->W = w;
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector2D Quaternion::RotateVector(Vector2D coordinate) {
 Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
  Quaternion qv = Quaternion(0, coordinate.X, coordinate.Y, 0);
  Quaternion qr = current * qv * current.MultiplicativeInverse();

  return Vector2D {
    qr.X,
    qr.Y
  };
}

Vector2D Quaternion::UnrotateVector(Vector2D coordinate) {
  Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

  return current.Conjugate().RotateVector(coordinate);
}

Vector3D Quaternion::RotateVector(Vector3D coordinate) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	Quaternion qv = Quaternion(0, coordinate.X, coordinate.Y, coordinate.Z);
	Quaternion qr = current * qv * current.MultiplicativeInverse();

	return Vector3D {
		qr.X,
		qr.Y,
		qr.Z
	};
}

Vector3D Quaternion::UnrotateVector(Vector3D coordinate) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.Conjugate().RotateVector(coordinate);
}

Vector3D Quaternion::GetBiVector() {
	return Vector3D{
		this->X,
		this->Y,
		this->Z
	};
}

Quaternion Quaternion::SphericalInterpolation(Quaternion q1, Quaternion q2, float ratio) {
	q1 = q1.UnitQuaternion();
	q2 = q2.UnitQuaternion();

	float dot = q1.DotProduct(q2);//Cosine between the two quaternions

	if (dot < 0.0f)//Shortest path correction
	{
		q1 = q1.AdditiveInverse();
		dot = -dot;
	}

	if (dot > 0.999)//Linearly interpolates if results are close
	{
		return (q1.Add( (q2.Subtract(q1)).Multiply(ratio) )).UnitQuaternion();
	}
	else
	{
		dot = Mathematics::Constrain(dot, -1, 1);

		float theta0 = acosf(dot);
		float theta = theta0 * ratio;

		//Quaternion q3 = (q2.Subtract(q1.Multiply(dot))).UnitQuaternion();//UQ for orthonomal 
		float f1 = cosf(theta) - dot * sinf(theta) / sinf(theta0);
		float f2 = sinf(theta) / sinf(theta0);

		return q1.Multiply(f1).Add(q2.Multiply(f2)).UnitQuaternion();
	}
}

Quaternion Quaternion::Add(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion {
		current.W + quaternion.W,
		current.X + quaternion.X,
		current.Y + quaternion.Y,
		current.Z + quaternion.Z
	};
}

Quaternion Quaternion::Subtract(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion{
		current.W - quaternion.W,
		current.X - quaternion.X,
		current.Y - quaternion.Y,
		current.Z - quaternion.Z
	};
}

Quaternion Quaternion::Multiply(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	
	return Quaternion
	{
		current.W * quaternion.W - current.X * quaternion.X - current.Y * quaternion.Y - current.Z * quaternion.Z,
		current.W * quaternion.X + current.X * quaternion.W + current.Y * quaternion.Z - current.Z * quaternion.Y,
		current.W * quaternion.Y - current.X * quaternion.Z + current.Y * quaternion.W + current.Z * quaternion.X,
		current.W * quaternion.Z + current.X * quaternion.Y - current.Y * quaternion.X + current.Z * quaternion.W
	};
}

Quaternion Quaternion::Multiply(float scalar) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion{
		current.W * scalar,
		current.X * scalar,
		current.Y * scalar,
		current.Z * scalar
	};
}

Quaternion operator  *(float scalar, Quaternion q) {
	Quaternion quaternion = Quaternion(q.W, q.X, q.Y, q.Z);

	return quaternion.Multiply(scalar);
}

Quaternion operator  *(Quaternion q, float scalar) {
	Quaternion quaternion = Quaternion(q.W, q.X, q.Y, q.Z);

	return quaternion.Multiply(scalar);
}

Quaternion Quaternion::Divide(Quaternion quaternion) {
	float scale = quaternion.W * quaternion.W + quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z;
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		( current.W * quaternion.W + current.X * quaternion.X + current.Y * quaternion.Y + current.Z * quaternion.Z) / scale,
		(-current.W * quaternion.X + current.X * quaternion.W + current.Y * quaternion.Z - current.Z * quaternion.Y) / scale,
		(-current.W * quaternion.Y - current.X * quaternion.Z + current.Y * quaternion.W + current.Z * quaternion.X) / scale,
		(-current.W * quaternion.Z + current.X * quaternion.Y - current.Y * quaternion.X + current.Z * quaternion.W) / scale
	};
}

Quaternion Quaternion::Divide(float scalar) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		current.W / scalar,
		current.X / scalar,
		current.Y / scalar,
		current.Z / scalar
	};
}

Quaternion Quaternion::Power(Quaternion exponent) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		(float)powf(current.W, exponent.W),
		(float)powf(current.X, exponent.X),
		(float)powf(current.Y, exponent.Y),
		(float)powf(current.Z, exponent.Z)
	};
}

Quaternion Quaternion::Power(float exponent) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		(float)powf(current.W, exponent),
		(float)powf(current.X, exponent),
		(float)powf(current.Y, exponent),
		(float)powf(current.Z, exponent)
	};
}

Quaternion Quaternion::Permutate(Vector3D permutation) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	float perm[3];

	perm[(int)permutation.X] = current.X;
	perm[(int)permutation.Y] = current.Y;
	perm[(int)permutation.Z] = current.Z;

	current.X = perm[0];
	current.Y = perm[1];
	current.Z = perm[2];

	return current;
}

Quaternion Quaternion::Absolute() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		(float)fabs(current.W),
		(float)fabs(current.X),
		(float)fabs(current.Y),
		(float)fabs(current.Z)
	};
}

Quaternion Quaternion::AdditiveInverse() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		-current.W,
		-current.X,
		-current.Y,
		-current.Z
	};
}

Quaternion Quaternion::MultiplicativeInverse() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.Conjugate().Multiply(1.0f / current.Normal());

}

Quaternion Quaternion::Conjugate() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		 current.W,
		-current.X,
		-current.Y,
		-current.Z
	};
}

Quaternion Quaternion::UnitQuaternion() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	float n = current.Normal();

	current.W = current.W / n;
	current.X = current.X / n;
	current.Y = current.Y / n;
	current.Z = current.Z / n;

	return current;
}

float Quaternion::Magnitude() {
	return sqrtf(Normal());
}

float Quaternion::DotProduct(Quaternion q) {
	return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
}

float Quaternion::Normal() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);


	return powf(current.W, 2.0f) + powf(current.X, 2.0f) + powf(current.Y, 2.0f) + powf(current.Z, 2.0f);
}

bool Quaternion::IsNaN() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsNaN(current.W) || Mathematics::IsNaN(current.X) || Mathematics::IsNaN(current.Y) || Mathematics::IsNaN(current.Z);
}

bool Quaternion::IsFinite() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsInfinite(current.W) || Mathematics::IsInfinite(current.X) || Mathematics::IsInfinite(current.Y) || Mathematics::IsInfinite(current.Z);
}

bool Quaternion::IsInfinite() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsFinite(current.W) || Mathematics::IsFinite(current.X) || Mathematics::IsFinite(current.Y) || Mathematics::IsFinite(current.Z);
}

bool Quaternion::IsNonZero() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.W != 0 && current.X != 0 && current.Y != 0 && current.Z != 0;
}

bool Quaternion::IsEqual(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return !current.IsNaN() && !quaternion.IsNaN() &&
		current.W == quaternion.W &&
		current.X == quaternion.X &&
		current.Y == quaternion.Y &&
		current.Z == quaternion.Z;
}

String Quaternion::ToString() {
	String w = Mathematics::DoubleToCleanString(this->W);
	String x = Mathematics::DoubleToCleanString(this->X);
	String y = Mathematics::DoubleToCleanString(this->Y);
	String z = Mathematics::DoubleToCleanString(this->Z);
	
	return "[" + w + ", " + x + ", " + y + ", " + z + "]";
	
}
