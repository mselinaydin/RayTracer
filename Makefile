all:
	g++ Camera.cpp Light.cpp main.cpp Material.cpp ppm.cpp Ray.cpp Scene.cpp Shape.cpp Sphere.cpp Triangle.cpp vector3.cpp -O2 -o raytracer
