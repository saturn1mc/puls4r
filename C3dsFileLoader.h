//
// File: 3dsFileLoader.h
// Created by: <Andrea Ingegneri>
//

#ifndef _C3DSFILELOADER_H_
#define _C3DSFILELOADER_H_

#include <string>
#include <fstream>

#include "C3dsFileFormat.h"

using namespace std;

class C3dsFileLoader : public C3dsFileFormat
{
public:
	// Constructor
	C3dsFileLoader() : C3dsFileFormat(), PC(0), mFileSize(0) {}
	// Denstructor
	virtual ~C3dsFileLoader() {}
	// Methods
	void ProcessFile(string FileName);
	
private:
	void movePC(long forward);
	bool ParseChunks();
	bool ReadBlock(char *dest, long size);
	float ReadRealNumber();
	bool SkipChunk(chunk3ds &chunk);
	void FileSize();
	bool isOk();
	void ReadASCIIZ(char *dest);
	void ReadRGBF();
	void ReadRGBB();
	void ReadObjBlock();
	void ReadVertList();
	void ReadFaceList();
	void ReadFaceMat();
	void ReadMapList();
	void ReadSmoothList();
	void ReadTrMatrix();
	void ReadLight();
	void ReadSpotLight();
	void ReadCamera();
	void ReadMatName();
	void ReadMapFile();
	void ReadFrames();
	void ReadTrackObjName();
	void ReadTrackPos();
	void ReadTrackRot();
	void ReadTrackScale();
	void ReadObjNumber();
	void ReadObjChunk();
	void ReadOneUnit();
	void ReadViewPortData();
	void ReadViewUser();
	void ReadViewTop();
	void ReadViewBottom();
	void ReadViewLeft();
	void ReadViewRight();
	void ReadViewFront();
	void ReadViewBack();
	void ReadViewCamera();
	void ReadViewPortLayout();
	void ReadViewPortSize();
	void EndReading();
	
	ifstream	mInputFile;
protected:
	
	long PC; // File Pointer
	long mFileSize;
	
	// Inheritable functions for polymorphism
	virtual void User3dVert(float x, float y, float z);
	virtual void User3dFace(unsigned short A, unsigned short B, unsigned short C, unsigned short Flags);
	virtual void UserCamera(float px, float py, float pz, float tx, float ty, float tz, float Bank, float Lens);
	virtual void UserFaceMaterial(string Name, int Number);
	virtual	void UserMapVertex(float U, float V);
	virtual void UserTransformMatrix(const Transform3dsMatrix &Transform, const Translate3dsMatrix &Translate);
	virtual void UserLight(float x, float y, float z);
	virtual void UserSpotLight(float x, float y, float z, float HotSpot, float FallOff);
	virtual void UserMatName(const string Name);
	virtual void UserMapFile(const string FileName);
	virtual void UserFrames(long Start, long End);
	virtual void UserTrackObjectName(const string Name, int Key1, int Key2, int Key3);
	virtual void UserTrackPos(int Frame, long Flags, float x, float y, float z);
	virtual void UserTrackRot(int Frame, long Flags, float DegX, float DegY, float DegZ);
	virtual void UserTrackScale(int Frame, long Flags, float ScaleX, float ScaleY, float ScaleZ);
	virtual void UserObjNumber(int ObjNumber);
	virtual void UserObjName(string Name);
	virtual void UserChunkObj();
	virtual void UserOneUnit(float Unit);
	virtual void UserViewPortLayout(ViewPortLayout &Layout);
	virtual void UserViewPortSize(int PosX, int PosY, int Width, int Height);
	virtual void UserViewPortData(ViewPortData &Data);
	virtual	void UserViewUser(float x, float y, float z, float Width, float XYangle, float YZangle, float BackAngle);
	virtual void UserViewCamera(string CameraName);
	virtual void UserEndOfFile();
};

#endif	//_C3DSFILELOADER_H_

