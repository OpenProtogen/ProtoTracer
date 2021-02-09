#include "Camera.h"
#include "Rotation.h"
#include "KalmanFilter.h"

//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "TemporaryObjCamera.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

//TEENSY SPECIFIC FOR WRITING TO LEDS
#include <OctoWS2811.h>

const int ledsPerStrip = 571;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//END TEENSY SPECIFIC FOR WRITING TO LEDS

Light lights[6];
Object3D* objects[8];
Object3D noseObj1 = Object3D(noseString, 10, 10);
Object3D eyeObj1 = Object3D(eyeString, 10, 10);
Object3D eyeBrowObj1 = Object3D(eyeBrowString, 10, 10);
Object3D mouthObj1 = Object3D(mouthString, 10, 10);
Object3D noseObj2 = Object3D(noseString, 10, 10);
Object3D eyeObj2 = Object3D(eyeString, 10, 10);
Object3D eyeBrowObj2 = Object3D(eyeBrowString, 10, 10);
Object3D mouthObj2 = Object3D(mouthString, 10, 10);
Scene* scene;

Camera kaiborgCam3535 = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 571, &pixelString, false, false);

void setup() {
  leds.begin();
  leds.show();

  Serial.begin(115200);
  Serial.println("Starting...");

  Serial.println("Setting lights...");
  lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 40), 1000.0f, 0.5f, 0.5f);//Set lights position, color intensity, falloff distance, and falloff curvature
  lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 40), 1000.0f, 0.5f, 0.5f);
  lights[2].Set(Vector3D(0, 0, 1000), Vector3D(40, 0, 255), 1000.0f, 0.5f, 0.5f);
  lights[3].Set(Vector3D(-1000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.5f, 0.5f);
  lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.5f, 0.5f);
  lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.5f, 0.5f);

  Serial.println("Linking objects...");
  objects[0] = &noseObj1;
  objects[1] = &eyeObj1;
  objects[2] = &eyeBrowObj1;
  objects[3] = &mouthObj1;
  objects[4] = &noseObj2;
  objects[5] = &eyeObj2;
  objects[6] = &eyeBrowObj2;
  objects[7] = &mouthObj2;

  Serial.println("Creating scene...");
  scene = new Scene(objects, lights, 8, 6);
  
  Serial.println("Beginning render...");
}

void loop() {
  for (int i = 0; i < 720; i++) {
    Serial.print("Rendering frame ");
    Serial.print(i);
    Serial.print(" of 720 at ");

    //Example of Face with slight movement, scaling, and rotation
    //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
    objects[0]->Enable();
    objects[1]->Enable();
    objects[2]->Enable();
    objects[3]->Enable();
    objects[4]->Enable();
    objects[5]->Enable();
    objects[6]->Enable();
    objects[7]->Enable();

    //Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
    objects[0]->ResetVertices();
    objects[1]->ResetVertices();
    objects[2]->ResetVertices();
    objects[3]->ResetVertices();
    objects[4]->ResetVertices();
    objects[5]->ResetVertices();
    objects[6]->ResetVertices();
    objects[7]->ResetVertices();

    //Objects can be moved to a coordinate or translated by a vector
    objects[0]->Move(Vector3D(0, 0, 50.0f));
    objects[1]->Move(Vector3D(0, 0, 50.0f));
    objects[2]->Move(Vector3D(0, 0, 50.0f));
    objects[3]->Move(Vector3D(0, 0, 50.0f));
    objects[4]->Move(Vector3D(0, 0, -50.0f));
    objects[5]->Move(Vector3D(0, 0, -50.0f));
    objects[6]->Move(Vector3D(0, 0, -50.0f));
    objects[7]->Move(Vector3D(0, 0, -50.0f));
    
    //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
    objects[0]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[1]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[2]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[3]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[4]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[5]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[6]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[7]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));

    //Objects can be scaled by origin, center, and at a point
    float s = 1.0f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.03f;
    objects[0]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[1]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[2]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[3]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[4]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[5]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[6]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[7]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    
    //Lights can be moved to any vector coordinate
    lights[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
    lights[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
    lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
    lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));

    long prev = micros();//Used to calculate the render time in seconds

    kaiborgCam3535.Rasterize(scene, 1.0f, 10);

    float dif = ((float)(micros() - prev)) / 1000000.0f;
    
    //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
    for (int i = 0; i < 571; i++) {
      leds.setPixel(i,           (byte)kaiborgCam3535.GetPixels()[i].RGB.X, (byte)kaiborgCam3535.GetPixels()[i].RGB.Y, (byte)kaiborgCam3535.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 571,     (byte)kaiborgCam3535.GetPixels()[i].RGB.X, (byte)kaiborgCam3535.GetPixels()[i].RGB.Y, (byte)kaiborgCam3535.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 571 * 2, (byte)kaiborgCam3535.GetPixels()[i].RGB.X, (byte)kaiborgCam3535.GetPixels()[i].RGB.Y, (byte)kaiborgCam3535.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 571 * 3, (byte)kaiborgCam3535.GetPixels()[i].RGB.X, (byte)kaiborgCam3535.GetPixels()[i].RGB.Y, (byte)kaiborgCam3535.GetPixels()[i].RGB.Z);
    }

    leds.show();
    //END TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY

    Serial.print(dif, 5);
    Serial.println(" seconds.");
  }
}
