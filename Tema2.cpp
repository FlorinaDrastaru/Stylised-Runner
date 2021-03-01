#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"
#include "LabCamera.h"
#include "Objects.h"


using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;
	projectionType = true;

	right = 10.f;
	left = .01f;
	bottom = .01f;
	top = 10.f;
	fov = 40.f;

	camera = new Laborator::CameraTema2();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	const string textureLoc = "Source/Laboratoare/Tema2/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crate.png").c_str(), GL_REPEAT);
		mapTextures["crate"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "a1.png").c_str(), GL_REPEAT);
		mapTextures["red"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "yellow.png").c_str(), GL_REPEAT);
		mapTextures["yellow"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "blue.png").c_str(), GL_REPEAT);
		mapTextures["blue"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "purple.png").c_str(), GL_REPEAT);
		mapTextures["purple"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "orange.png").c_str(), GL_REPEAT);
		mapTextures["orange"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "green.png").c_str(), GL_REPEAT);
		mapTextures["green"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "texture.png").c_str(), GL_REPEAT);
		mapTextures["texture"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "brick.png").c_str(), GL_REPEAT);
		mapTextures["brick"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "black.png").c_str(), GL_REPEAT);
		mapTextures["black"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "metalic.png").c_str(), GL_REPEAT);
		mapTextures["metalic"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "b2.png").c_str(), GL_REPEAT);
		mapTextures["b2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "b3.png").c_str(), GL_REPEAT);
		mapTextures["b3"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "b4.png").c_str(), GL_REPEAT);
		mapTextures["b4"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pavele.png").c_str(), GL_REPEAT);
		mapTextures["pavele"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "f.png").c_str(), GL_REPEAT);
		mapTextures["f"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "dollar.png").c_str(), GL_REPEAT);
		mapTextures["dollar"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "asphalt.png").c_str(), GL_REPEAT);
		mapTextures["asphalt"] = texture;
	}

	{
		// platforma
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{	
		// minge
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		// minge
		Mesh* mesh = new Mesh("quad");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
		
		// dreptunghiuri pentru combustibil si scor
	{
		Mesh* whiteRectangle = Objects::CreateRectangle("whiteRectangle", glm::vec3(1, 1, 1), true);
		AddMeshToList(whiteRectangle);

		Mesh* powRectangle = Objects::CreateRectangle("powRectangle", glm::vec3(0, 1, 0), true);
		AddMeshToList(powRectangle);

		Mesh* lifeRectangle = Objects::CreateRectangle("lifeRectangle", glm::vec3(1, 0, 0), true);
		AddMeshToList(lifeRectangle);
	}

	

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, Z_NEAR, Z_FAR);

	{
		Shader* shader = new Shader("BallShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

		// shader platforma rosie
	{
		Shader* shader = new Shader("RedBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderRed.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderRed.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	// shader platforma verde
	{
		Shader* shader = new Shader("GreenBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderGreen.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderGreen.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// shader platforma galbena
	{
		Shader* shader = new Shader("YellowBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderYellow.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderYellow.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// shader platforma albastra
	{
		Shader* shader = new Shader("BlueBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderBlue.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderBlue.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// shader platforma portocalie
	{
		Shader* shader = new Shader("OrangeBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderOrange.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderOrange.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// shader platforma violet
	{
		Shader* shader = new Shader("PurpleBox");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderPurple.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderPurple.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// shader animatie
	{
		Shader* shader = new Shader("VertexShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// intr-un vector, generez Z-urile pentru platforme 
	int z0 = 0;
	Z.resize(40);
	Z[0] = 0;
	// Z-ul platformei curente este mai mic decat Z-ul platformei precedente
	for (int i = 1; i < 40; i++) {
		Z[i] =  Z[i-1] - rand()%3 - 3;
	}
	
	// generez culori aleatoriu pentru fiecare platforma
	for (int k = 0; k < 40; k++) {
		for (int p = 0; p < 3; p++)
		colours[k][p] = rand() % 5;
	}
	
	
	
	for (int i = 0; i < 40; i++) {
		idx = rand() % 3;
		for (int j = 0; j < 3; j++) {
			if (idx == j)
				random[i][idx] = 0; else
				random[i][j] = 1;
		}
	}
	
	
	// completez matricea de pozitii cu Z-urile generate anterior
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 3; j++) {
			if (i != 0) {
				positions[i][0] = glm::vec3(-2, 0.1f, Z[i]);
				positions[i][1] = glm::vec3(0, 0.1f, Z[i]);
				positions[i][2] = glm::vec3(2, 0.1f, Z[i]);
			}
			else {
				positions[i][0] = glm::vec3(-2, 0.1f, 0);
				positions[i][1] = glm::vec3(0, 0.1f, 0);
				positions[i][2] = glm::vec3(2, 0.1f, 0);
			}
		}
	}

	// salvez ultima pozitie
	lastPos0 = positions[39][0];
	lastPos1 = positions[39][1];
	lastPos2 = positions[39][2];
	z.resize(10);
	z[0] = 2;

	for (int i = 1; i < 10; i++) {
		z[i] = z[i - 1] - rand() % 3 - 3;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			if (i != 0) {
				if (j == 0) {
					decor[i][j] = glm::vec3(-3.7f, 0.5f, z[i]);
				}
				else {
					decor[i][j] = glm::vec3(3.7f, 0.5f, z[i]);
				}
			}
		}
	}

	last0 = decor[9][0];
	last1 = decor[9][1];

	
	randBuildings.resize(10);
	for (int i = 0; i < 10; i++) {
		randBuildings[i] = rand() % 2;
	}

	
	for (int i = 0; i < 40; i++) {
		obst = rand() % 3;
		for (int j = 0; j < 3; j++) {
			obstacles[i][j] = positions[i][j];
			if (obst == j && random[i][obst] == 1) {
				showObst[i][j] = 1;
			}
			else if (i == 0 || i == 1) {
				showObst[i][j] = 0;
			} else {
				showObst[i][j] = 0;
			}
 
		}
	}

	lastOb0 = obstacles[39][0];
	lastOb1 = obstacles[39][1];
	lastOb2 = obstacles[39][2];

	for (int i = 0; i < 40; i++) {
		money = rand() % 3;
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				posMoney[i][j] = positions[i][j];
				posMoney[i][j].x = positions[i][j].x + 0.6;

			}
			if (j == 2) {
				posMoney[i][j] = positions[i][j];
				posMoney[i][j].x = positions[i][j].x - 0.6;
			}
			if (j == 3) {
				posMoney[i][j] = positions[i][j];
			}
			if (money == j && random[i][money] == 1 && showObst[i][money] == 0) {
				showMoney[i][j] = 1;
			}
			else if (i == 0 || i == 1) {
				showMoney[i][j] = 0;
			}
			else {
				showMoney[i][j] = 0;
			}
		}
	}

	lastM0 = posMoney[39][0];
	lastM1 = posMoney[39][1];
	lastM2 = posMoney[39][2];
}

void Tema2::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{	

	

	glm::mat4 mat7 = glm::mat4(1);
	
	mat7 *= glm::scale(mat7, glm::vec3(1.7f, 1.f, 100.f));
	mat7 *= glm::translate(mat7, glm::vec3(-5.9f, -6.f, 0.f));
	mat7 *= Objects::RotateOX(RADIANS(90));
	mat7 *= Objects::RotateOZ(RADIANS(90));

	glm::mat4 mat8 = glm::mat4(1);

	mat8 *= glm::scale(mat8, glm::vec3(1.7f, 1.f, 100.f));
	mat8 *= glm::translate(mat8, glm::vec3(5.9f, -6.f, 0.f));
	mat8 *= Objects::RotateOX(RADIANS(90));
	mat8 *= Objects::RotateOZ(RADIANS(90));
	

	RenderSimpleMesh2(meshes["quad"], shaders["BlueBox"], mat7, mapTextures["grass"], nullptr);
	RenderSimpleMesh2(meshes["quad"], shaders["BlueBox"], mat8, mapTextures["grass"], nullptr);
	glm::mat4 mat6 = glm::mat4(1);
	mat6 *= glm::scale(mat6, glm::vec3(0.7f, 0.8f, 0.001f));
	mat6 *= glm::translate(mat6, glm::vec3(1.3f, 2.f, 1.f));
	//RenderSimpleMesh2(meshes["sphere"], shaders["BlueBox"], mat6, mapTextures["brick"], nullptr);


	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 3; j++) {
			glm::mat4 mat5 = glm::mat4(1);
			mat5 = glm::translate(mat5, glm::vec3(0, 0, 0));
			obstacles[i][j].z += speed;
			mat5 = glm::translate(mat5, obstacles[i][j]);

			if (obstacles[i][j].z > 5) {
				if (j == 0) {
					obstacles[i][j] = lastOb0;
				}
				else if (j == 1) {
					obstacles[i][j] = lastOb1;
				}
				else if (j == 2) {
					obstacles[i][j] = lastOb2;
				}
			}

			//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3f, 0.01f, 2.5f));
			double x = fmax(obstacles[i][j].x - 0.5, fmin(translateX, obstacles[i][j].x + 0.5));
			double y = fmax(obstacles[i][j].y - 0.5, fmin(translateY + 0.3, obstacles[i][j].y + 0.5));
			double z = fmax(obstacles[i][j].z - 0.5, fmin(translateZ, obstacles[i][j].z + 0.5));
			double dist = sqrt((x - translateX) * (x - translateX) + (z - translateZ)
				* (z - translateZ) + (y - 0.3 - translateY) * (y - 0.3 - translateY));

			if (dist < 0.5) {
				obstCollision = true;
			}
			else {
				obstCollision = false;
			}

			if (obstCollision && random[i][j] == 1 && showObst[i][j] == 1) {
				if (glfwGetTime() > 4) {
					scor -= 0.1;
					cout << "SCOR: " << scor << endl;
				}
			}
			if (showObst[i][j] == 1) {
				RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], mat5, mapTextures["brick"], nullptr);
			}
		}
	}

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 3; j++) {
			glm::mat4 mat9 = glm::mat4(1);
			mat9 = glm::translate(mat9, glm::vec3(0, 0.2, 0));
			posMoney[i][j].z += speed;
			
			mat9 = glm::translate(mat9, glm::vec3(posMoney[i][j].x, posMoney[i][j].y, posMoney[i][j].z));
			//mat9 = glm::translate(mat9, glm::vec3(0, -1, 0));
			mat9 *= glm::scale(mat9, glm::vec3(0.5f, 0.3f, 0.5f));
			
			mat9 *= Objects::RotateOX(RADIANS(180));
			
			if (posMoney[i][j].z > 5) {
				if (j == 0) {
					posMoney[i][j] = lastM0;
				}
				else if (j == 1) {
					posMoney[i][j] = lastM1;
				}
				else if (j == 2) {
					posMoney[i][j] = lastM2;
				}
			}

			//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3f, 0.01f, 2.5f));
			double x = fmax(posMoney[i][j].x - 0.25, fmin(translateX, posMoney[i][j].x + 0.25));
			double y = fmax(posMoney[i][j].y - 0.15, fmin(translateY + 0.3, posMoney[i][j].y + 0.15));
			double z = fmax(posMoney[i][j].z - 0.25, fmin(translateZ, posMoney[i][j].z + 0.25));
			double dist = sqrt((x - translateX) * (x - translateX) + (z - translateZ)
				* (z - translateZ) + (y - 0.3 - translateY) * (y - 0.3 - translateY));

			if (dist < 0.5) {
				collMoney = true;

			}
			else {
				collMoney = false;
			}

			if (collMoney && random[i][j] == 1 && showObst[i][j] == 0 && showMoney[i][j] == 1) {
				//cout << "crestem puncte" << endl;
				if (glfwGetTime() > 7) {
					scor += 10;
					cout << "SCOR: " << scor << endl;
				}
				
				showMoney[i][j] = 0;
			}
			else {
				if (showMoney[i][j] == 1) {
					RenderSimpleMesh2(meshes["quad"], shaders["BlueBox"], mat9, mapTextures["dollar"], nullptr);
				}
			}
			

			
		}
	}
	

	glm::mat4 mat4 = glm::mat4(1);
	mat4 *= glm::scale(mat4, glm::vec3(3.f, 1.f, 100.f));
	mat4 *= Objects::RotateOX(RADIANS(90));
	mat4 *= Objects::RotateOZ(RADIANS(90));
	
	RenderSimpleMesh2(meshes["quad"], shaders["BlueBox"], mat4, mapTextures["asphalt"], nullptr);
	// desenez dreptunghiurile de combustibil
	glm::mat3 mat1 = glm::mat3(1);
	mat1 *= Objects::Translate(0, 0);
	mat1 *= Objects::Translate(-2, 2.f);
	mat1 *= Objects::Scale(power / 10000, 1);
	RenderMesh2D(meshes["powRectangle"], shaders["VertexColor"], mat1);
	
	glm::mat3 mat = glm::mat3(1);
	mat *= Objects::Translate(0, 0);
	mat *= Objects::Translate(-2, 2.f);
	RenderMesh2D(meshes["whiteRectangle"], shaders["VertexColor"], mat);

	mat = glm::mat3(1);
	mat *= Objects::Translate(0, 0);
	mat *= Objects::Translate(1, 2.f);
	mat *= Objects::Scale(scor/100, 1);
	RenderMesh2D(meshes["lifeRectangle"], shaders["VertexColor"], mat);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 2.f, 1.f));
			decor[i][j].z += speed;
			modelMatrix = glm::translate(modelMatrix, decor[i][j]);

			if (decor[i][j].z > 5) {
				if (j == 0) {
					decor[i][j] = last0;
				}
				else {
					decor[i][j] = last1;
				}
			}

			
			if (randBuildings[i] == 0) {
				RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["f"], nullptr);
			}
			else {
				RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["b4"], nullptr);
			}
		}
	}


	
	
	if (gameOn) {
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 3; j++) {
				// pozitionez mingea
				// cand cade pe platforma cu power-up sau cand e activat power-up ul de la cea portocalie, 
				// mingea este animata
				/*if ((colours[i][j] != 0 && collision) || (colours[i][j] == 0 && extraSpeed > 0)) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.3, 0));
					modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, translateY, translateZ));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
					RenderSimpleMesh(meshes["sphere"], shaders["VertexShader"], modelMatrix);
				}
				else { // in caz contrar, mingea e randata normal
					glm::mat4 modelMatrix = glm::mat4(1);
					//modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.3, 0));
					modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, 0.3 + translateY, translateZ));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
					RenderSimpleMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
				}*/
				glm::mat4 modelMatrix1 = glm::mat4(1);
				modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0.3, 0));
				modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(translateX, translateY, translateZ));
				modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.5f));
				RenderSimpleMesh2(meshes["sphere"], shaders["BallShader"], modelMatrix1, mapTextures["black"], nullptr);
				// pozitionez platformele si le modific Z-ul in functie de deplasare
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
				positions[i][j].z += speed;
				modelMatrix = glm::translate(modelMatrix, positions[i][j]);
				
				if (positions[i][j].z  > 5) {
					if (j == 0) {
						positions[i][j] = lastPos0;
					} else if (j == 1) {
						positions[i][j] = lastPos1;
					} else if (j == 2) {
						positions[i][j] = lastPos2;
					}
				}
				
				// verific coliziunile
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3f, 0.01f, 2.5f));
				double x = fmax(positions[i][j].x - 0.75, fmin(translateX, positions[i][j].x + 0.75));
				double y = fmax(positions[i][j].y - 0.05, fmin(translateY + 0.3  , positions[i][j].y + 0.05));
				double z = fmax(positions[i][j].z - 1.25, fmin(translateZ, positions[i][j].z + 1.25));
				double dist = sqrt((x - translateX) * (x - translateX) + (z - translateZ) 
					* (z - translateZ) + (y - 0.3 - translateY) * (y - 0.3 - translateY));
				
				if (dist < 0.5 * 0.5) {
					collision = true;
				} else {  
					collision = false;
				}
				if (collision == true && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["purple"], nullptr);
				} else if (colours[i][j] == 0 && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["blue"], nullptr);
				} else if (colours[i][j] == 1 && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["green"], nullptr);
				} else if (colours[i][j] == 2 && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["orange"], nullptr);
				} else if (colours[i][j] == 3 && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["red"], nullptr);
				} else if (colours[i][j] == 4 && random[i][j] == 1) {
					RenderSimpleMesh2(meshes["box"], shaders["BlueBox"], modelMatrix, mapTextures["yellow"], nullptr);
				}

				// cand cade pe platforma rosie, jocul se incheie
				if (colours[i][j] == 3 && collision) {
					Engine::Exit();
				    std::exit(0);
				}

				// cand cade pe platforma galbena, pierde combustibil
				if (colours[i][j] == 4 && collision) {
					power -= 1;
					//cout << "combustibil ramas: " << power << endl;
				}

				if (colours[i][j] == 1 && collision) {
					power += 1;
					//cout << "combustibil curent: " << power << endl;
				}

				power -= 0.005;  
				// cand cade pe platforma portocalie, e blocat la viteza mare pentru cateva secunde
				if (colours[i][j] == 2 && collision) {
					extraSpeed = 60;   
				}

				
				
			}
			
		}
	
	}
}

void Tema2::FrameEnd() {

}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// randare cu shaderul potrivit
	glUseProgram(shader->program);
	int location = glGetUniformLocation(shader->program, "Model");

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	location = glGetUniformLocation(shader->program, "View");

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	location = glGetUniformLocation(shader->program, "Var");

	glm::vec3 Var = glm::vec3(camera->forward.x, camera->forward.y, camera->forward.z);
	glUniform3fv(location, 1, glm::value_ptr(Var));
	location = glGetUniformLocation(shader->program, "Projection");

	// matricea de proiectie
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "Time");
	glUniform1f(location, Engine::GetElapsedTime());

	// se deseneaza obiectul
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// BONUS: Deciding wether to rotate the mesh or not
	GLint locTime = glGetUniformLocation(shader->program, "time");
	GLboolean isQuad = false;

	if (mesh == meshes["square"])
	{
		isQuad = true;
	}

	GLint locIsQuad = glGetUniformLocation(shader->program, "is_quad");
	glUniform1i(locIsQuad, isQuad);

	if (mesh == meshes["sphere"])
	{
		glUniform1f(locTime, (GLfloat)Engine::GetElapsedTime());
	}
	else
	{
		glUniform1f(locTime, -1.f);
	}

	glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), mixTextures);

	if (texture1)
	{
		// Activate texture location 0
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		// Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}



	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{	
	angularStep += deltaTime;
	// mingea cade atunci cand nu mai e pe platforme
	if (translateX < -3 || translateX > 3) {
		translateY -= deltaTime;
	}
	
	speed = deltaTime * 2;
	slowSpeed = deltaTime / 100;

	// viteza se mareste dupa caderea pe platforma portocalie
	if (extraSpeed > 0) {
		extraSpeed--;
		speed = speed * 3;
	}
	else {
		speed = deltaTime * 2;
	}

	if (window->KeyHold(GLFW_KEY_A) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		translateX -= deltaTime *2;
	}

	if (window->KeyHold(GLFW_KEY_S) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
	}

	if (window->KeyHold(GLFW_KEY_D) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		translateX += deltaTime *2;
	}

	if (window->KeyHold(GLFW_KEY_W) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		speed += deltaTime * 4;
	}

	if (window->KeyHold(GLFW_KEY_S) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		speed -= deltaTime/5;
	}
	
	// verific daca s-a apasat tasta space
	int state = glfwGetKey(window->GetGLFWWindow(), GLFW_KEY_SPACE);
	if (window->KeyHold(GLFW_KEY_SPACE) && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
			flag = true;
			
	}

	// daca s-a apasat space, modific pozitia player-ului pe Y
	if (state == GLFW_PRESS) {
		translateY += 2 * deltaTime;
	}

	// cand tasta nu mai este apasata, mingea incepe sa coboare
	if ((flag && state == GLFW_RELEASE) || translateY > 2.f) {
		if (collision == false) {
			translateY -= 2 * deltaTime;
		}
		else {
			if (translateY > 0) {
				translateY -= 2 * deltaTime;
			}
		}
		if (translateY < 0) {
			flag = false;
		}
	}

	power -= speed;

	// daca nu mai e combustibil, jocul se incheie
	if (power < 0) {
		Engine::Exit();
		std::exit(0);
	}
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W))
		{
			// Translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_A))
		{
			// Translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_S))
		{
			// Translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_D))
		{
			// Translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_Q))
		{
			// Translate the camera down
			camera->TranslateUpward(-deltaTime * cameraSpeed);
		}
		if (window->KeyHold(GLFW_KEY_E))
		{
			// Translate the camera up
			camera->TranslateUpward(deltaTime * cameraSpeed);
		}
		
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0)
		{
			renderCameraTarget = false;
			// Rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL)
		{
			renderCameraTarget = true;
			// Rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// Use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

