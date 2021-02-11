#pragma once
#pragma once

#include "Quaternion.h"
#include "Triangle3D.h"
#include "Vector2D.h"

class Triangle2D {
  float denominator = 0.0f;
  
public:
	Vector2D* p1;
	Vector2D* p2;
	Vector2D* p3;
  Vector2D v0;
  Vector2D v1;
	Vector3D normal;
  Vector3D* t3p1;
  Vector3D* t3e1;
  Vector3D* t3e2;

	Triangle2D(){}

	Triangle2D(Vector2D p1, Vector2D p2, Vector2D p3) {
		this->p1 = new Vector2D(p1);
		this->p1 = new Vector2D(p2);
		this->p1 = new Vector2D(p3);

    v0 = p2 - p1;
    v1 = p3 - p1;
    
    denominator = 1.0f / (v0.X * v1.Y - v1.X * v0.Y);
	}

	Triangle2D(Quaternion camQ, Vector3D camV, Triangle3D t) {
		camV.X = -camV.X;
		camV.Y = -camV.Y;
   
		this->p1 = new Vector2D(camQ.UnrotateVector(Vector3D(*t.p1)) - camV);
		this->p2 = new Vector2D(camQ.UnrotateVector(Vector3D(*t.p2)) - camV);
		this->p3 = new Vector2D(camQ.UnrotateVector(Vector3D(*t.p3)) - camV);

		normal = t.Normal();
    
    t3p1 = t.p1;
    t3e1 = &t.edge1;
    t3e2 = &t.edge2;
    
    v0 = *p2 - *p1;
    v1 = *p3 - *p1;

    denominator = 1.0f / (v0.X * v1.Y - v1.X * v0.Y);
	}

  ~Triangle2D(){
    delete p1;
    delete p2;
    delete p3;
  }

	void Translate(Vector2D p) {
		*p1 = *p1 + p;
		*p2 = *p2 + p;
		*p3 = *p3 + p;

    v0 = *p2 - *p1;
    v1 = *p3 - *p1;

    denominator = 1.0f / (v0.X * v1.Y - v1.X * v0.Y);
	}

	bool DidIntersect(Vector2D ray, float& u, float& v, float& w) {
    float v2X = ray.X - p1->X;
    float v2Y = ray.Y - p1->Y;
    v = (v2X * v1.Y - v1.X * v2Y) * denominator;
    w = (v0.X * v2Y - v2X * v0.Y) * denominator;
		u = 1.0f - v - w;

    if (u > 0 && v > 0 && w > 0){
      return true;
    }
    else{
      return false;
    }
	}

	String ToString() {
		return p1->ToString() + " " + p2->ToString() + " " + p3->ToString();
	}
};
