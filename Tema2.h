#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"

#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
	

protected:
	Laborator::CameraTema2* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	bool projectionType;
	
	std::unordered_map<std::string, Texture2D*> mapTextures;
	GLuint randomTextureID;
	GLboolean mixTextures;

	GLfloat right;
	GLfloat left;
	GLfloat bottom;
	GLfloat top;
	GLfloat fov;
	int n;
	glm::vec3 positions[40][3];
	glm::vec3 decor[10][2];
	glm::vec3 grass[10][2];
	std::vector<float> z = {};
	int random[40][3];
	std::vector<float> randBuildings = {};
	//std::vector<std::vector<glm::vec3>> positions;
	std::vector<float> Z = {};
	std::vector<float> zGrass = {};
	//std::vector<int> colours = {};
	glm::vec3 lastPos0;
	glm::vec3 lastPos1;
	glm::vec3 lastPos2;
	glm::vec3 last0;
	glm::vec3 last1;
	glm::vec3 lastOb0;
	glm::vec3 lastOb1;
	glm::vec3 lastOb2;

	float angularStep;
	int idx;


	bool collision;

	int colours[40][3];
	int collisions[40][3];

	int showMoney[40][3];
	glm::vec3 posMoney[40][3];
	int money;
	bool collMoney;
	glm::vec3 lastM0;
	glm::vec3 lastM1;
	glm::vec3 lastM2;

	glm::vec3 obstacles[40][3];
	int showObst[40][3];
	int obst;
	bool obstCollision;

	int gap = 3;

	double translateX = 0;
	double translateY = 0;
	double translateZ = 0;
	bool flag = false;

	double movePlatformZ = 0;
	bool gameOn = true;

	double speed = 0;
	double slowSpeed = 0;
	double power = 10000;
	bool touched = false;
	int extraSpeed = 0;
	double jump = 0;
	bool fall = false;

	double scor = 0;
	
};