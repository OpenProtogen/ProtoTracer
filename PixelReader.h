#pragma once

#include "Vector3D.h"
#include "Pixel.h"

class PixelReader {
private:
	String getValue(String data, char separator, int index) {
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

	unsigned int countChar(String data, char search) {
		int count = 0;

		for (unsigned int i = 0; i < data.length(); i++) {
			if (data.charAt(i) == search) {
				count++;
			}
		}

		return count;
	}

public:
	PixelReader() {}

	void GetPixels(Pixel* pixels, unsigned int count, const String* value, bool flipX, bool flipY) {
		String line;

		for (unsigned int i = 0; i < countChar(*value, '\n') + 1; i++) {
			line = getValue(*value, '\n', i);
     
      if(i > count) break;//maxed out pixels available to memory, cancel reading

			if (countChar(line, ',') > 2) {
				float x, y;

				x = getValue(line, ',', 1).toFloat();
				y = getValue(line, ',', 2).toFloat();

        if (flipX){
          x = -x;
        }
        if (flipY){
          y = -y;
        }

				pixels[i] = Pixel(x, y);

        Serial.print("Pixel ");
        Serial.print(i);
        Serial.print(" X: ");
        Serial.print(x);
        Serial.print(" Y: ");
        Serial.println(y);
			}
		}
	}

	void GetPixels(Pixel* pixels, int pixWidth, int pixHeight, float distance){
    int currentPixel = 0;
    
		for (int i = 0; i < pixWidth; i++) {
			for (int k = 0; k < pixHeight; k++) {
				pixels[currentPixel] = Pixel(i * distance, k * distance);

        Serial.print("Pixel ");
        Serial.print(currentPixel);
        Serial.print(" X: ");
        Serial.print(pixels[currentPixel].X);
        Serial.print(" Y: ");
        Serial.println(pixels[currentPixel].Y);
        currentPixel++;
			}
		}
	}
};
