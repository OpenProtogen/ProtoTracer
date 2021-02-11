#pragma once

#include "Object3D.h"

class ObjectDeformer{
  public:
    enum Axis {
        XAxis,
        YAxis,
        ZAxis
    };
    
  private:
    Object3D** objects;
    int objectCount = 0;

    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis){
      if (valueCheckAxis == XAxis && positive && base.X > 0){
        return true;
      }
      else if (valueCheckAxis == XAxis && !positive && base.X < 0){
        return true;
      }
      else if (valueCheckAxis == YAxis && positive && base.Y > 0){
        return true;
      }
      else if (valueCheckAxis == YAxis && !positive && base.Y < 0){
        return true;
      }
      else if (valueCheckAxis == ZAxis && positive && base.Z > 0){
        return true;
      }
      else if (valueCheckAxis == ZAxis && !positive && base.Z < 0){
        return true;
      }
      else{
        return false;
      }
    }
    
  public:
    ObjectDeformer(Object3D* object){
      objects = new Object3D*[1];
      
      objects[0] = object;
      
      objectCount = 1;
    }

    ObjectDeformer(Object3D** objects, int objectCount){
      this->objects = objects;
      this->objectCount = objectCount;
    }

    void SinusoidalDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
          
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = (sinf((base.Y) + timeRatio * frequencyModifier) * periodModifier + cosf((base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = (sinf((base.X) + timeRatio * frequencyModifier) * periodModifier + cosf((base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = (sinf((base.X) + timeRatio * frequencyModifier) * periodModifier + cosf((base.Y) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }
    
    void DropwaveDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
          
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = -(1.0f + cosf(12.0f*sqrt(base.Y * base.Y + base.Z + base.Z) + timeRatio * frequencyModifier) * periodModifier) / (0.5f * (base.Y * base.Y + base.Z + base.Z) + 2.0f) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = -(1.0f + cosf(12.0f*sqrt(base.X * base.X + base.Z + base.Z) + timeRatio * frequencyModifier) * periodModifier) / (0.5f * (base.X * base.X + base.Z + base.Z) + 2.0f) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = -(1.0f + cosf(12.0f*sqrt(base.X * base.X + base.Y * base.Y) + timeRatio * frequencyModifier) * periodModifier) / (0.5f * (base.X * base.X + base.Y * base.Y) + 2.0f) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }

    void SineWaveSurfaceDeform(Vector3D offset, float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j] - offset;
        
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = objects[i]->GetVertices()[j].X + sinf((sqrtf(base.Y * base.Y + base.Z * base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = objects[i]->GetVertices()[j].Y + sinf((sqrtf(base.X * base.X + base.Z * base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = objects[i]->GetVertices()[j].Z + sinf((sqrtf(base.X * base.X + base.Y * base.Y) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }

    void CosineInterpolationDeformer(float* pointMultiplier, int points, float scale, float minAxis, float maxAxis, Axis selectionAxis, Axis deformAxis){
      //map axis offsets based on value range for multiplying vertex coordinates at set intervals spaced evenly across minimum and maximum range of selected axis
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          float value;
          
          switch(selectionAxis){
            case XAxis:
              value = objects[i]->GetVertices()[j].X;
              break;
            case YAxis:
              value = objects[i]->GetVertices()[j].Y;
              break;
            case ZAxis:
              value = objects[i]->GetVertices()[j].Z;
              break;
            default:
              value = 0.0f;
              break;
          }

          float stepWindow = (maxAxis - minAxis) / points;//window size for the step interval

          float roundUpWindow = Mathematics::RoundUpWindow(value, stepWindow);
          float roundDownWindow = roundUpWindow - stepWindow;
          int roundUpIndex = (roundUpWindow - minAxis) / stepWindow;
          
          float intervalMultiplier, windowRatio;
          
          if (roundUpIndex < 1){//below range
            intervalMultiplier = 1.0f;// Mathematics::CosineInterpolation(1.0f, pointMultiplier[0], windowRatio)
          }
          else if (roundUpIndex > points){//above range
            intervalMultiplier = 1.0f;// Mathematics::CosineInterpolation(pointMultiplier[points - 1], 1.0f, windowRatio)
          }
          else{
            windowRatio = (value - roundDownWindow) / stepWindow;
            intervalMultiplier = Mathematics::CosineInterpolation(pointMultiplier[roundUpIndex], pointMultiplier[roundUpIndex - 1], 1.0f - windowRatio);
          }
          
          
          //calculate where the axis fits on the range
          
          switch(deformAxis){
            case XAxis:
              objects[i]->GetVertices()[j].X = objects[i]->GetVertices()[j].X + scale * intervalMultiplier;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = objects[i]->GetVertices()[j].Y + scale * intervalMultiplier;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = objects[i]->GetVertices()[j].Z + scale * intervalMultiplier;
              break;
            default:
              break;
          }
        }
      }
    }

    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
        
          switch(clipAxis){
            case XAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.X = 0;
              break;
            case YAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.Y = 0;
              break;
            case ZAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.Z = 0;
              break;
            default:
              break;

            objects[i]->GetVertices()[j] = base;
          }
        }
      }
    }
};
