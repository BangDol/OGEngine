#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cassert>

#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::Instance()
{
	if (!instance)
	{
		instance = new ResourceManager;
	}
	return instance;
}

void ResourceManager::DestoryInst()
{
	if (!instance)
	{
		return;
	}
	delete instance;
	instance = nullptr;
}

//obj 파일 불러오기
//불러올 수 없는 경우 false 반환
bool ResourceManager::OBJParser(
	const char* _path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec3>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	//obj 파일
		//v는 정점
		//vt는 정점의 텍스쳐 좌표
		//vn은 정점의 normal 좌표
		//f는 면
	//임시 변수
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file = fopen(_path, "r");
	if (file == NULL)
	{
		std::cout << "파일을 열 수가 없습니다" << std::endl;
		return false;
	}

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);		//줄의 첫번째 단어를 읽음
		if (res == EOF)
		{
			break;
		}
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec3 uv;
			fscanf(file, "%f %f %f\n", &uv.x, &uv.y, &uv.z);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2],
				&vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			if (matches != 12)
			{
				std::cout << "파일을 파서로 읽어올 수 없습니다" << std::endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[3]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			uvIndices.push_back(uvIndex[3]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			normalIndices.push_back(normalIndex[3]);
		}	
	}

	//각 삼각형의 정점들을 돌아본다
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];				//정점 좌표의 index는 vertexIndices에 있음
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];	//-1을 해주는 이유는 C++과 달리 OBJ는 1부터 시작하기 때문
		out_vertices.push_back(vertex);								//새로운 정점에게 좌표값을 넘겨줌
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec3 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	return true;
}

AUX_RGBImageRec* ResourceManager::LoadBMP(const char* szFilename)
{
	FILE* pFile = NULL;
	if (!szFilename)
	{
		return NULL;
	}
	pFile = fopen(szFilename, "r");
	if (pFile)
	{
		fclose(pFile);
		return auxDIBImageLoad(szFilename);
	}
	return NULL;
}

int ResourceManager::LoadGLTextures(const char* szFilePath, unsigned int MyTextureObject[])
{
	AUX_RGBImageRec* pTextureImage[1];
	int status = FALSE;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	memset(pTextureImage, 0, sizeof(void*) * 1);

	if (pTextureImage[0] = LoadBMP(szFilePath))
	{
		status = TRUE;
		glGenTextures(1, &MyTextureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
	if (pTextureImage[0])
	{
		if (pTextureImage[0]->data)
		{
			free(pTextureImage[0]->data);
		}
		free(pTextureImage[0]);
	}
	return status;
}
