#pragma once

#include <Vector.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Triangle2D.h"
#include "Triangle3D.h"

// v X Y Z
//f l1 l2 l3 l4
class OBJReader {
private:
	static String getValue(String data, char separator, int index) {
		int found = 0;
		int strIndex[] = { 0, -1 };
		int maxIndex = data.length() - 1;

		for (int i = 0; i <= maxIndex && found <= index; i++) {
			if (data.charAt(i) == separator || i == maxIndex) {
				found++;
				strIndex[0] = strIndex[1] + 1;
				strIndex[1] = (i == maxIndex) ? i + 1 : i;
			}
		}

		return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
	}

	static int countChar(String data, char search) {
		int count = 0;

		for (unsigned int i = 0; i < data.length(); i++) {
			if (data.charAt(i) == search) {
				count++;
			}
		}

		return count;
	}

public:
	static void GetTriangles(Vector3D* vertexArray, Vector3D* triangleVecArray, Triangle3D* triangleArray, int* vertexLength, int* triangleLength, const String* value, bool flipX, bool flipY, const int maxVertices, const int maxTriangles) {
		String line;
    
		//read obj data and parse
		for (int i = 0; i < countChar(*value, '\n') + 1; i++) {
			line = getValue(*value, '\n', i);

			if (countChar(line, ' ') > 2) {
				if (getValue(line, ' ', 0).equals("v")) {
					Vector3D vertex;

					vertex.X = getValue(line, ' ', 1).toFloat();
					vertex.Y = getValue(line, ' ', 2).toFloat();
					vertex.Z = getValue(line, ' ', 3).toFloat();

          if (flipX) vertex.X = -vertex.X;
          if (flipY) vertex.Y = -vertex.Y;

					vertexArray[*vertexLength].X = vertex.X;
          vertexArray[*vertexLength].Y = vertex.Y;
          vertexArray[*vertexLength].Z = vertex.Z;
          (*vertexLength)++;
          
          if (*vertexLength > maxVertices) break;
				}
				else if (getValue(line, ' ', 0).equals("f")) {
					int x, y, z;

					x = getValue(line, ' ', 1).toInt() - 1;
					y = getValue(line, ' ', 2).toInt() - 1;
					z = getValue(line, ' ', 3).toInt() - 1;
					
          triangleVecArray[*triangleLength].X = x;
          triangleVecArray[*triangleLength].Y = y;
          triangleVecArray[*triangleLength].Z = z;
          (*triangleLength)++;
          
          if (*triangleLength > maxTriangles) break;
				}
			}
		}

    for (int i = 0; i < *triangleLength; i++) {
      triangleArray[i].p1 = &vertexArray[(int)triangleVecArray[i].X];
      triangleArray[i].p2 = &vertexArray[(int)triangleVecArray[i].Y];
      triangleArray[i].p3 = &vertexArray[(int)triangleVecArray[i].Z];
    }
	}

 static void GetTriangles(Vector2D* vertexArray, Vector3D* triangleVecArray, Triangle2D* triangleArray, int* vertexLength, int* triangleLength, const String* value, bool flipX, bool flipY, const int maxVertices, const int maxTriangles) {
   String line;
    
    //read obj data and parse
    for (int i = 0; i < countChar(*value, '\n') + 1; i++) {
      line = getValue(*value, '\n', i);

      if (countChar(line, ' ') > 2) {
        if (getValue(line, ' ', 0).equals("v")) {
          Vector2D vertex;

          vertex.X = getValue(line, ' ', 1).toFloat();
          vertex.Y = getValue(line, ' ', 2).toFloat();

          if (flipX) vertex.X = -vertex.X;
          if (flipY) vertex.Y = -vertex.Y;

          vertexArray[*vertexLength].X = vertex.X;
          vertexArray[*vertexLength].Y = vertex.Y;
          (*vertexLength)++;
          
          if (*vertexLength > maxVertices) break;
        }
        else if (getValue(line, ' ', 0).equals("f")) {
          int x, y, z;

          x = getValue(line, ' ', 1).toInt() - 1;
          y = getValue(line, ' ', 2).toInt() - 1;
          z = getValue(line, ' ', 3).toInt() - 1;
          
          triangleVecArray[*triangleLength].X = x;
          triangleVecArray[*triangleLength].Y = y;
          triangleVecArray[*triangleLength].Z = z;
          (*triangleLength)++;
          
          if (*triangleLength > maxTriangles) break;
        }
      }
    }

    for (int i = 0; i < *triangleLength; i++) {
      triangleArray[i].p1 = &vertexArray[(int)triangleVecArray[i].X];
      triangleArray[i].p2 = &vertexArray[(int)triangleVecArray[i].Y];
      triangleArray[i].p3 = &vertexArray[(int)triangleVecArray[i].Z];
    }
  }
};
