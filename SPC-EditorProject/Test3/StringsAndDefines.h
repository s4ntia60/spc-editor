#pragma once
#include <string> 
#include "Utils.h"
//#include "Shader.cpp"


#define STRINGDEFINES StringsAndDefines::Instance()

class StringsAndDefines
{
	private:
		StringsAndDefines();
		~StringsAndDefines();

	public:
		static StringsAndDefines * Instance();
		//std::string SampleFragmet(){ return ""; };

		std::string SampleFragmet()
		{
			return LoadShader("../../Resources/Shaders/blueShaderTest.fs");
		}

};



static const int ID_TYPE_SPMainNode = 1;
static const int ID_TYPE_SPConstFloatNode = 2;
static const int ID_TYPE_SPVector2DNode = 3;
static const int ID_TYPE_SPVector3DNode = 4;
static const int ID_TYPE_SPVector4DNode = 5;
static const int ID_TYPE_SPTextureNode = 6;
static const int ID_TYPE_SPAddNode = 7;
static const int ID_TYPE_SPSubtractNode = 8;
static const int ID_TYPE_SPMultiplyNode = 9;
static const int ID_TYPE_SPPowerNode = 10;
static const int ID_TYPE_SPSqrtNode = 11;
static const int ID_TYPE_SPLogNode = 12;
static const int ID_TYPE_SPMinNode = 13;
static const int ID_TYPE_SPMaxNode = 14;
static const int ID_TYPE_SPAbsNode = 15;
static const int ID_TYPE_SPSignNode = 16;
static const int ID_TYPE_SPModNode = 17;
static const int ID_TYPE_SPClampNode = 18;
static const int ID_TYPE_SPLerpNode = 19;

static const int TOTAL_TYPES_NODES = 20;


static const std::string UNIFORM_NAME_TEXTURE_COLOR = "ColorTex";
static const std::string UNIFORM_NAME_TEXTURE_NORMAL = "NormalMapTex";
static const std::string UNIFORM_NAME_TEXTURE_SPECULAR = "SpecularMapTex";

static const std::string STANDAR_TEXTURE_PATH = "../../Resources/Images/standard.png";
static const std::string STANDAR_TEXTURE_SPECULAR_PATH = "../../Resources/Images/standardSpecular.png";
static const std::string STANDAR_TEXTURE_NORMAL_PATH = "../../Resources/Images/standardNormal.png";
static const std::string STANDAR_TEXTURE_ALPHA_PATH = "../../Resources/Images/standardAlpha.png";


static const std::string DEFAULT_VALUE_COLOR = "vec4(0.75)";
static const std::string DEFAULT_VALUE_SPECULAR = "vec4(0.55)";
static const std::string DEFAULT_VALUE_ALPHA = "vec4(1.0)";
static const std::string DEFAULT_VALUE_NORMAL = "vec4(0.48, 0.48, 0.99, 1)";
static const std::string DEFAULT_VALUE_SHININESS = "25";
static const std::string ERROR_NO_CONNECTION = "NO CONNECTION MADE";