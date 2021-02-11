#pragma once

#include "Scene.h"

class Animation{
protected:
  float fade = 0.0f;
  
  Scene* scene;

public:
  Scene* GetScene(){
    return scene;
  }

  virtual void FadeIn(float stepRatio) = 0;
  virtual void FadeOut(float stepRatio) = 0;
  virtual void Update(float ratio) = 0;
};
