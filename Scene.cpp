#include "Scene.h"
#include <cfloat>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int Scene::getWidth() {
	return ImageWidth;
}

int Scene::getHeight() {
	return ImageHeight;
}

Scene::Scene(string FilePath){
	ParseScene(FilePath); //kamerayı light sourceları falan oluşturduk simdi viewportu, pixelsizeı hesaplamak falan kaldı
	
	Vector3 myE = SceneCam.getPosition();
	Vector3 myGaze = SceneCam.getGaze();
	Vector3 myUp = SceneCam.getUp();
	Vector3 myUAxis = SceneCam.getUAxis();
	
	
	vpTopLeft = (myGaze * SceneCam.distance) + (myUAxis * SceneCam.Left) + 
				(myUp * SceneCam.Top) + myE;
	vpTopRight = (myGaze * SceneCam.distance) + (myUAxis * SceneCam.Right) +
				(myUp * SceneCam.Top) + myE;
	vpBottomLeft = (myGaze * SceneCam.distance) + (myUAxis * SceneCam.Left) +
				(myUp * SceneCam.Bottom) + myE;
	vpBottomRight = (myGaze * SceneCam.distance) + (myUAxis * SceneCam.Right) +
				(myUp * SceneCam.Bottom) + myE;
				
	PixelSizeX = (vpTopRight.x() - vpTopLeft.x()) / ImageWidth;
	PixelSizeY = (vpTopLeft.y() - vpBottomLeft.y()) / ImageHeight;
	//for optimization
	
}

Camera Scene::ReadCam(ifstream& fstr){

	float posX, posY, posZ, gazeX, gazeY, gazeZ, upX, upY, upZ, left, right, bottom, top, dist;
	fstr >> posX >> posY >> posZ >> gazeX >> gazeY >> gazeZ >> upX >> upY >> upZ >> left >> right >> bottom >> top >> dist;
	Camera nCam(posX, posY, posZ, gazeX, gazeY, gazeZ, upX, upY, upZ, left, right, bottom, top, dist);
	
	return nCam;		
}
Material Scene::ReadMaterial(ifstream& fstr){
	float aR, aG, aB, dR, dG, dB, sR, sG, sB, rR, rG, rB;
	int P;
	fstr >> aR >> aG >> aB >> dR >> dG >> dB >> sR >> sG >> sB >> P >> rR >> rG >> rB;
	Material nMat(aR, aG, aB, dR, dG, dB, sR, sG, sB, P, rR, rG, rB);
	
	return nMat;	
}

Shape* Scene::ReadTri(ifstream& fstr){
	float pos1x, pos1y, pos1z, pos2x, pos2y, pos2z, pos3x, pos3y, pos3z;
	int meteIndex;
	fstr >> pos1x >> pos1y >> pos1z >> pos2x >> pos2y >> pos2z >> pos3x >> pos3y >> pos3z >> meteIndex;
	Vector3 vec1(pos1x, pos1y, pos1z);
	Vector3 vec2(pos2x, pos2y, pos2z);
	Vector3 vec3(pos3x, pos3y, pos3z);
	Shape* p = new Triangle(vec1, vec2, vec3, meteIndex, TMin);
	
	return p;	
}


Light Scene::ReadLight(ifstream& fstr){
	float x, y, z, r, g, b;	
	fstr >> x >> y >> z >> r >> g >> b;
	Light nLight(x, y, z, r, g, b);
	
	return nLight;
}


Shape* Scene::ReadSph(ifstream& fstr){
	float x, y, z, r;
	int mat;
	fstr >> x >> y >> z >> r >> mat;
	
	Shape* p = new Sphere(x, y, z, r, mat);
	
	return p;
}

void Scene::ParseScene(string filePath){
	ifstream read;
	
	read.open(filePath.c_str());
	
	
	if(!read.good())
		return;
		
	string temp;
	int bosGec;
	
	read >> ImageWidth >> ImageHeight;
	read >> TMin;
	read >> RayReflectCount;
	
	ImageMatrix = new unsigned char[ImageWidth * ImageHeight * 3];
	
	//read >> temp;
	
	while(read.good())
	{
			
		read >> temp;
		if(temp == "#Material"){
			read >> bosGec;
			MaterialList.push_back(ReadMaterial(read));
		}
		else if(temp == "#Camera")
			SceneCam = ReadCam(read);
		else if(temp == "#Triangle")
			ShapeList.push_back(ReadTri(read));
		else if(temp == "#Sphere")
			ShapeList.push_back(ReadSph(read));
		else if(temp == "#Light")
			LightList.push_back(ReadLight(read));
		else if(temp == "#Ambient"){			
			read >> IAmbR >> IAmbG >> IAmbB;
		}
		else if(temp == "#Background"){
			read >> backR >> backG >> backB;	
		}		
	}	
	read.close();
}


void Scene::SetPxColor(int indX, int indY, unsigned char r, unsigned char g, unsigned char b){
	ImageMatrix[(indX * ImageWidth * 3) + (indY * 3)] = r;
	ImageMatrix[(indX * ImageWidth * 3) + (indY * 3) + 1] = g;
	ImageMatrix[(indX * ImageWidth * 3) + (indY * 3) + 2] = b;
}

float Scene::getDiffuseR(Vector3 point, Light myLight, float kdR, Vector3 normal){
	Vector3 vec = ((myLight.Pos) - point);
	vec.normalize();
	float retVal = kdR * (myLight.iR) * max((float)0, normal.dot(vec));
	return retVal;
}
float Scene::getDiffuseG(Vector3 point, Light myLight, float kdG, Vector3 normal){
	
	Vector3 vec = ((myLight.Pos) - point);
	vec.normalize();
	float retVal = kdG * (myLight.iG) * max((float)0, normal.dot(vec));
	return retVal;
}
float Scene::getDiffuseB(Vector3 point, Light myLight, float kdB, Vector3 normal){
	
	Vector3 vec = ((myLight.Pos) - point);
	vec.normalize();
	float retVal = kdB * (myLight.iB) * max((float)0, normal.dot(vec));
	return retVal;
}


float Scene::getSpecR(Vector3 point, Light myLight, float speR, Vector3 normal, int exp, Vector3 bakis){
	Vector3 vec = ((myLight.Pos) - point); //L vektörü
	vec.normalize();
	Vector3 v = bakis - point;
	v.normalize();
	Vector3 half = v + vec;
	half.normalize();
	
	float retVal = speR * (myLight.iR) * pow(max((float)0, normal.dot(half)) , exp);
	return retVal;
}
float Scene::getSpecG(Vector3 point, Light myLight, float speG, Vector3 normal, int exp, Vector3 bakis){
	Vector3 vec = ((myLight.Pos) - point); //L vektörü
	vec.normalize();
	Vector3 v = bakis - point;
	v.normalize();
	Vector3 half = v + vec;
	half.normalize();
	
	float retVal = speG * (myLight.iG) * pow(max((float)0, normal.dot(half)) , exp);
	return retVal;
}
float Scene::getSpecB(Vector3 point, Light myLight, float speB, Vector3 normal, int exp, Vector3 bakis){
	Vector3 vec = ((myLight.Pos) - point); //L vektörü
	vec.normalize();
	Vector3 v = bakis - point;
	v.normalize();
	Vector3 half = v + vec;
	half.normalize();
	
	float retVal = speB * (myLight.iB) * pow(max((float)0, normal.dot(half)) , exp);
	return retVal;
}

void Scene::RayColor(Ray viewingRay, float &colorR, float &colorG, float &colorB, int refCount, int flag){
	if(!refCount)
		return;
	vector<Shape*>::iterator it;
	vector<Shape*>::iterator end;
	end = ShapeList.end();
	float tm = FLT_MAX;
	Shape* obj = NULL;
	
	
	it = ShapeList.begin();
	while( it != end)//shapeListte bi şeyler oldugu sürece//foreach object
	{
		
		float kar = ((*it)->SIntersect(viewingRay));//karşılaştırma için alınan t
		
		if(refCount == (RayReflectCount + 1))
		{
			if((kar != FLT_MAX) && (kar < 1))
			{
				it++;
				continue;
			}
		}
		
		if((kar != FLT_MAX) && (kar > TMin))//kesişiyosa//burdaki tmin gerekli yoksa kendısıyle kesişiyo
		{
			if(kar < tm)
			{
				tm = kar;
				obj = (*it);
			}
		}
		it++;
	}
	//buraya geldiğinde en yakın objeye bakmıs demektr
	//Obj null değilse çarptıgı objenin rengini
	if(obj)
	{
		int met = obj->GetMaterial();
		colorR = MaterialList[met].ambR * IAmbR;
		colorG = MaterialList[met].ambG * IAmbG;
		colorB = MaterialList[met].ambB * IAmbB;
		
		
		Vector3 point = viewingRay.getOrigin() + tm * viewingRay.getDirection();
		Vector3 n = obj->GetNormal(point);		
		int check = LightList.size();
		for(int k = 0; k < check; k++)//check = LightList.size(); her seferinde variable oluşturmamak için constructorda hesaplattım
		{					
			Vector3 nowvec = (LightList[k].Pos) - point;//v
			nowvec.normalize();			
			Ray shadowRay(point, nowvec);			
			float shadowT = FLT_MAX; 			
			int sayi = ShapeList.size(); 
			int fbelirt = 0;
			for(int m = 0; m < sayi; m++)//her object için
			{
				
				shadowT = ShapeList[m]->SIntersect(shadowRay);
				if(shadowT != FLT_MAX && (shadowT > TMin))//flebirt bu checkin aynısını tekrarlamamak için. normalde aşağıda tekrarlıyoduk
				{
					//fbelirt = 1;					
					break;	
				}
			}
			if(shadowT != FLT_MAX && (shadowT > TMin))
			{
				continue;
			}/*
			if(fbelirt)
			{
				continue;
			}*/			
			//her light source u için diffuse hesaplıycaz
			colorR += getDiffuseR(point, LightList[k], MaterialList[met].difR, n);
			colorG += getDiffuseG(point, LightList[k], MaterialList[met].difG, n);
			colorB += getDiffuseB(point, LightList[k], MaterialList[met].difB, n);
			
			//her light sourceu için blinnphong hesaplıycaz
			colorR += getSpecR(point, LightList[k], MaterialList[met].speR, n, MaterialList[met].speExpP, viewingRay.getOrigin());
			colorG += getSpecG(point, LightList[k], MaterialList[met].speG, n, MaterialList[met].speExpP, viewingRay.getOrigin());
			colorB += getSpecB(point, LightList[k], MaterialList[met].speB, n, MaterialList[met].speExpP, viewingRay.getOrigin());
		}
		float newColorR = 0;
		float newColorG = 0;
		float newColorB = 0;
		Vector3 frt = viewingRay.getOrigin() - point;//v
		frt.normalize();
		Vector3 yeniRayinDirectionu;
		yeniRayinDirectionu = (-1 * frt) + (2 * n *n.dot(frt));
		yeniRayinDirectionu.normalize();
		Ray yeniRay(point, yeniRayinDirectionu);
		refCount--;
		flag++;
		RayColor(yeniRay , newColorR, newColorG, newColorB, refCount, flag);
		colorR += newColorR * MaterialList[met].refR;
		colorG += newColorG * MaterialList[met].refG;
		colorB += newColorB * MaterialList[met].refB;
	}
	//nullsa backgroundun rengini alacak
	else
	{
		if (flag > 0)
			return;
		colorR = backR;
		colorG = backG;
		colorB = backB;
	} 
	
		
	
}


Vector3 Scene::GetPxPos(int indX, int indY){
	Vector3 tempVec;
	tempVec.setX( vpTopLeft.x() + (indX + 0.5)*PixelSizeX );
	tempVec.setY( vpTopLeft.y() - (indY + 0.5)*PixelSizeY );
	tempVec.setZ( vpTopLeft.z() );
	
	return tempVec;
}
void Scene::GetPxIndex(Vector3 pixelPos, int& indX, int& indY){ //kontrol et
	indX = ((pixelPos.x() - vpTopLeft.x()) / PixelSizeX) - 0.5;
	indY = -1 * ( 0.5 + ( (pixelPos.y() - vpTopLeft.y()) / PixelSizeY));
}
Ray Scene::GetRay(Vector3 pxPos, Vector3 camPos){//reflectionda camPosları sektiği yer olarak gönderirsin
	Ray tempR(camPos, (pxPos - camPos));
	return tempR;
}
Ray Scene::GetRay(int pxIndX, int pxIndY, Vector3 camPos){//reflectionda camPosları sektiği yer olarak gönderirsin
	Ray tempR(camPos, ( GetPxPos(pxIndX, pxIndY) - camPos) );
	return tempR;
}
void Scene::Render(){
	/*vector<Shape*>::iterator it;
	vector<Shape*>::iterator end;
	end = ShapeList.end();
	float tm = FLT_MAX;
	Shape* obj = NULL;*/
	
	for(int i = 0; i < ImageWidth; i++)//foreach pixel
	{
		//cout<<"pixel ="<<i<<endl;
		for(int j = 0; j < ImageHeight; j++)//foreach pixel
		{
			Ray viewingRay = GetRay(i, j, SceneCam.getPosition());//calculate the viewing ray
			float colorR = 0;
			float colorG = 0;
			float colorB = 0;
			
			int flag = 0;
			RayColor(viewingRay, colorR, colorG, colorB, RayReflectCount + 1, flag);
			
			if(colorR > 255)
				colorR = 255;				
			if(colorG > 255)
				colorG = 255;
			if(colorB > 255)
				colorB = 255;
			SetPxColor(j, i, colorR, colorG, colorB);
		}
	}
}


void Scene::print() {
		cout << "Image Size: " << ImageWidth << " X " << ImageHeight << endl;
		cout << "Material Type #: " << MaterialList.size() << endl;
		cout << "Object #: " << ShapeList.size() << endl;
		cout << "Light Sources #: " << LightList.size() << endl;
		cout << "viewPortL: " << vpBottomLeft.x() << vpBottomLeft.y() << vpBottomLeft.z()<< endl;
		cout << "viewPortT: " << vpBottomRight.x() << vpBottomRight.y() << vpBottomRight.z() << endl;
		cout << "viewPortR: " << vpTopLeft.x() << vpTopLeft.y() << vpTopLeft.z() << endl;
		cout << "viewPortB: " << vpTopRight.x() << vpTopRight.y() << vpTopRight.z() << endl;
		cout << "camera: " << (SceneCam.getPosition()).z()  << endl;
		cout << "pixelW: " << PixelSizeX << endl;
		cout << "pixelH: " << PixelSizeY << endl;
		//cout << "top left pixel pos: ";
		//cout << (Image[0][0].getPos()).x() << " " << (Image[0][0].getPos()).y() << endl;
	}
