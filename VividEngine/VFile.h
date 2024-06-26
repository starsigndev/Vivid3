#pragma once
#include<iostream>
#include<ostream>
#include<fstream>
#include "BasicMath.hpp"

using namespace Diligent;

//#include "Vec2.h"

enum FileMode {

	Write,Read

};

class VFile
{
public:
	static bool Exists(const char* path);

	VFile(const char* path, FileMode mode);
	void WriteInt(int v);
	void WriteFloat(float v);
	void WriteString(const char* str);
	void WriteByte(char b);
	void WriteBytes(void* data, int length);
	void WriteBool(bool b);
	void WriteVec3(float3 v);
	void WriteVec4(float4 v);
	void WriteMatrix(float4x4 v);
//	void WriteMatrix3x3(float3x3 v);
	float3 ReadVec3();
	float4 ReadVec4();

	//void WriteVec3(Vec3 v);
	void WriteLong(long v);
	void WriteLine(const char* str);


//	Vec3 ReadVec3();

	int ReadInt();
	float ReadFloat();
	char ReadByte();
	void* ReadBytes(int len);
	const char* ReadString();
	long ReadLong();
	bool ReadBool();
	float4x4 ReadMatrix();
	void Close();
	static long Length(const char * path);
	void Seek(long position);
private:
	std::ifstream istream;
	std::ofstream ostream;
	FileMode mod;
	int readPos = 0;

};

