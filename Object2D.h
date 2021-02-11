#pragma once

#include "OBJReader.h"
#include "Quaternion.h"
#include "Vector2D.h"

class Object2D {
private:
  Quaternion q = Quaternion(1, 0, 0, 0);
  Vector2D p = Vector2D(0, 0);
  Vector2D s = Vector2D(1, 1);
  Vector2D* verticesOriginal;
  Vector2D* vertices;
  Triangle2D* triangles;
  Vector3D* triangleVec;
  int vertexLength = 0;
  int triangleLength = 0;
  bool enabled = true;
  bool invert = false;
  
public:
  Object2D(const int maxVertices, const int maxTriangles){
    vertices = new Vector2D[maxVertices];
    verticesOriginal = new Vector2D[maxVertices];
    triangles = new Triangle2D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];

    vertexLength = maxVertices;
    triangleLength = maxTriangles;
  }

  Object2D(String dataset, const int maxVertices, const int maxTriangles){
    vertices = new Vector2D[maxVertices];
    verticesOriginal = new Vector2D[maxVertices];
    triangles = new Triangle2D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];

    OBJReader::GetTriangles(vertices, triangleVec, triangles, &vertexLength, &triangleLength, &dataset, false, false, maxVertices, maxTriangles);

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }
  }
  
  Object2D(String dataset, bool flipX, bool flipY, const int maxVertices, const int maxTriangles){
    vertices = new Vector2D[maxVertices]();
    verticesOriginal = new Vector2D[maxVertices];
    triangles = new Triangle2D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];
    
    OBJReader::GetTriangles(vertices, triangleVec, triangles, &vertexLength, &triangleLength, &dataset, flipX, flipY, maxVertices, maxTriangles);

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }
  }

  ~Object2D(){
    delete[] vertices;
    delete[] verticesOriginal;
    delete[] triangles;
    delete[] triangleVec;
  }

  void Enable(){
    enabled = true;
  }

  void Disable(){
    enabled = false;
  }

  bool IsEnabled(){
    return enabled;
  }

  void Invert(){
    invert = true;
  }

  void Revert(){
    invert = false;
  }

  bool IsInverted(){
    return invert;
  }

  Quaternion GetRotation(){
    return Quaternion(q);
  }

  Vector2D GetPosition(){
    return Vector2D(p);
  }

  Triangle2D* GetTriangles(){
    return triangles;
  }

  Vector2D* GetVertices(){
    return vertices;
  }

  Vector2D* GetVerticesOriginal(){
    return verticesOriginal;
  }

  int GetTriangleAmount(){
    return triangleLength;
  }

  int GetVertexAmount(){
    return vertexLength;
  }

  void ResetVertices(){
    for(int i = 0; i < vertexLength; i++){
      vertices[i] = verticesOriginal[i];
    }
  }
  
  Vector2D GetVertexCenter(){
    Vector2D center;
    
    for(int i = 0; i < vertexLength; i++){
      center = center + vertices[i];
    }

    center = center.Divide(vertexLength);

    return center;
  }
  
  void Rotate(Quaternion q) {
    this->q = Quaternion(q);

    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i]);
    }
  }
  
  void Rotate(Vector3D eAXYZR, Vector2D p) {
    Quaternion q = Rotation(EulerAngles(eAXYZR, EulerConstants::EulerOrderXYZR)).GetQuaternion();
    
    this->q = Quaternion(q);
  
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i] - p) + p;
    }
  }
  
  void Rotate(Quaternion q, Vector2D p) {
    this->q = Quaternion(q);

    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i] - p) + p;
    }
  }

  void RotateCenter(Quaternion q){
    Rotate(q, GetVertexCenter());
  }

  void RotateCenter(Vector3D v){
    Rotate(v, GetVertexCenter());
  }
  
  void Scale(Vector2D s){
    this->s = Vector2D(s);
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = (vertices[i]) / this->s;
    }
  }
  
  void Scale(Vector2D s, Vector2D p) {
    this->s = Vector2D(s);
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = (vertices[i] - p) * this->s + p;
    }
  }

  void ScaleCenter(Vector2D s){
    Scale(s, GetVertexCenter());
  }
  
  void Translate(Vector2D p) {
    this->p = this->p + p;
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p;
    }
  }

  void Move(Vector2D p){
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p;
    }

    this->p = p;
  }

};
