 #include "Scene.h"
 #include "ppm.h"
 #include <iostream>
 #include <string>
 int main (int argc, char *argv[])
 {
	 Scene yazdir(argv[1]);
	 yazdir.Render();
	
	string outFileName = argv[1];
	outFileName.replace(outFileName.end() - 3, outFileName.end(), "ppm");
	const char* out = outFileName.c_str();

	writePPM(out, yazdir.ImageMatrix, yazdir.getWidth(), yazdir.getHeight());
 }
