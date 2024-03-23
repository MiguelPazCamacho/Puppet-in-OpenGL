#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <stack>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//Nuestras librerias
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"


//Variables para matematicas
const float toRadians = acos(-1) / 180.0f;
const float Pi = acos(-1);

//Objetos de nuestras librerias
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

//Variables para las texturas
Texture metalTexture;
Texture alfombraTexture;
Texture jeansTexture;
Texture shoesTexture;

//Variables para el Delta time
GLfloat deltatime = 0.0f;
GLfloat lastTime = 0.0f;


//Vertex Shader
static const char* vShader = "res/shaders/shader.vert";

//Fragment Shader
static const char* fShader = "res/shaders/shader.frag";

//Funcion para crear Vertex Shader y Fragment Shader
void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CreateObjects() {

	//Dibujamos con triangulos la figura
	//por ello pasamos de 3 en 3 las caras
	//del triangulo
	unsigned int indices[] = {
		0, 3, 1,
		2, 3, 0,
		0, 1, 2,
		2, 4, 3,
		1, 5, 3,
		2, 6, 4,
		4, 7, 6,
		5, 3, 4,
		5, 7 ,4,
		1, 6, 2,
		1, 5 ,6,
		6, 7, 5
	};

	GLfloat vertices[]{
		//x,y,z inidican la posicion del vetice en el plano(3D)
		// u, v indican la posicion del vertice en la textura(2D)
		//x	,	y,		z,		u,	v
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,//0
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,	//1
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, //2
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //3
		0.5f, 0.5f, -0.5f,	1.0f, 1.0f, //4
		-0.5f, 0.5f, 0.5f,	1.0f, 0.0f,	//5
		0.5f, -0.5f, 0.5f,	0.0f, 1.0f,	//6
		0.5f, 0.5f, 0.5f,	0.0f, 0.0f	//7
	};

	//Creamos las Figuras
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 40, 36);
	for (int i = 0;i < 18;i++) {
		meshList.push_back(obj1);
	}
	


}

int main() {

	//Creamos una Ventana con este tamano
	//y la inicializamos
	mainWindow = Window(800, 600);
	mainWindow.Initialize();

	//Creamos los objetos 
	//Creamos los Shaders con fragment shader y vertex shader
	CreateObjects();
	CreateShaders();

	//Inicializamos la posicion de la camara
	camera = Camera(glm::vec3(0.0f,0.0f,-5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.00f, 1.0f);

	//Cargamos Texturas de la carpeta
	metalTexture = Texture((char*)"res/textures/metal.PNG");
	metalTexture.LoadTexture();
	alfombraTexture = Texture((char*)"res/textures/alfombra.PNG");
	alfombraTexture.LoadTexture();
	jeansTexture = Texture((char*)"res/textures/jeans.PNG");
	jeansTexture.LoadTexture();
	shoesTexture = Texture((char*)"res/textures/shoes.PNG");
	shoesTexture.LoadTexture();
	
	//Inicializamos los valores para dar perspectiva al shader
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Inicializacion ImGui
	ImGui::CreateContext();
	ImGuiIO& io =ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(mainWindow.getWindow(), false);
	ImGui::StyleColorsDark();
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//Declaramos los Angulos de las piezas
	float Torso_alpha = 0.0f;
	float Torso_theta = 0.0f;
	float Torso_phi = 0.0f;
	float Cuello_alpha = 0.0f;
	float Cuello_theta = 0.0f;
	float Cuello_phi = 0.0f;
	float BDerecho_theta = 0.0f;
	float BDerecho_phi = 0.0f;
	float BIzquierdo_theta = 0.0f;
	float BIzquierdo_phi = 0.0f;
	float MusloDerecho_theta = 0.0f;
	float MusloDerecho_phi = 0.0f;
	float MusloIzquierdo_theta = 0.0f;
	float MusloIzquierdo_phi = 0.0f;
	float ADerecho_phi = 0.0f;
	float AIzquierdo_phi = 0.0f;
	float PantDerecho_theta = 0.0f;
	float PantIzquierdo_theta = 0.0f;
	float MDerecho_theta = 0.0f;
	float MDerecho_phi = 0.0f;
	float MIzquierdo_theta = 0.0f;
	float MIzquierdo_phi = 0.0f;
	float PieDerecho_theta = 0.0f;
	float PieDerecho_phi = 0.0f;
	float PieIzquierdo_theta = 0.0f;
	float PieIzquierdo_phi = 0.0f;

	std::stack<glm::mat4> MatrixStack;

	// Loop until window closed
	while (!mainWindow.getShouldClose() && glfwGetKey(mainWindow.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {

		//Camara (Delta time)
		GLfloat now = glfwGetTime();
		deltatime = now - lastTime;
		lastTime = now;

		//Iniciamos el frame para el ImGui
		ImGui_ImplGlfwGL3_NewFrame();

		//Get+ Handle user  input events
		glfwPollEvents();

	
		//Activamos el control de camara con las teclas
		camera.keyControl(mainWindow.getsKeys(), deltatime);
		
		//Aquí desactivo el control de camara con el mouse
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		
		

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Inicializamos estos valores para dibujar las figuras
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();

		glm::mat4 model;
		
		//Torso
		float Torso_ancho = 0.8f;
		float Torso_alto = 1.0f;
		float Torso_largo = 0.5f;
		model = glm::rotate(model, Torso_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, Torso_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, Torso_alpha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(Torso_ancho, Torso_alto, Torso_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		metalTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/Torso_ancho, 1/Torso_alto, 1/Torso_largo));

		MatrixStack.push(model);

		//Hombros
		float Hombros_ancho = 1.6f;
		float Hombros_alto = 0.2f;
		float Hombros_largo = 0.5f;
		model = glm::translate(model, glm::vec3(0.0f, Torso_alto/2+Hombros_alto/2, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Hombros_ancho, Hombros_alto, Hombros_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[1]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/Hombros_ancho, 1/Hombros_alto, 1/Hombros_largo));

		MatrixStack.push(model);

		//Cuello
		float Cuello_ancho = 0.3f;
		float Cuello_alto = 0.35f;
		float Cuello_largo = 0.3f;
		model = glm::translate(model, glm::vec3((Cuello_alto / 2) * cos(Pi / 2 + Cuello_phi * toRadians), (Cuello_alto / 2) * cos(-Cuello_theta * toRadians) * sin(Pi / 2 + Cuello_phi * toRadians), (Cuello_alto / 2) * sin(Pi + Cuello_theta * toRadians)));
		model = glm::rotate(model, Cuello_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, Cuello_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, Cuello_alpha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(Cuello_ancho, Cuello_alto, Cuello_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		metalTexture.UseTexture();
		meshList[2]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/Cuello_ancho, 1/Cuello_alto, 1/Cuello_largo));

		

		//Cabeza
		float Cabeza_ancho = 0.6f;
		float Cabeza_alto = 0.7f;
		float Cabeza_largo = 0.6f;
		model = glm::translate(model, glm::vec3(0.0f,  Cuello_alto/2  + Cabeza_alto/2, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Cabeza_ancho, Cabeza_alto, Cabeza_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		metalTexture.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/Cabeza_ancho, 1/Cabeza_alto, 1/Cabeza_largo));

	
		//Nariz
		float Nariz_ancho = 0.1f;
		float Nariz_alto = 0.2f;
		float Nariz_largo = 0.1f;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -Cabeza_largo/2 ));
		model = glm::scale(model, glm::vec3(Nariz_ancho, Nariz_alto, Nariz_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[4]->RenderMesh();

		
	
		model = MatrixStack.top();
		
		//Brazo Derecho
		float BDerecho_ancho = 0.3f;
		float BDerecho_alto = 0.7f;
		float BDerecho_largo = 0.3f;
		model = glm::translate(model, glm::vec3( (Hombros_ancho * 0.75 / 2), -(BDerecho_alto / 2)  , 0 ));
		//model = glm::translate(model, glm::vec3(0, 0, 0));

		model = glm::translate(model, glm::vec3(-(Hombros_ancho * 0.75 / 2), -(-(BDerecho_alto / 2)), 0));
		model = glm::rotate(model, BDerecho_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3((Hombros_ancho * 0.75 / 2), (-(BDerecho_alto / 2) ), 0));

		model = glm::translate(model, glm::vec3(0, -(-(BDerecho_alto / 2) - (Hombros_alto / 2)), 0));
		model = glm::rotate(model, BDerecho_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0, (-(BDerecho_alto / 2) - (Hombros_alto / 2)), 0));

		model = glm::scale(model, glm::vec3(BDerecho_ancho, BDerecho_alto, BDerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[5]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/BDerecho_ancho, 1/BDerecho_alto, 1/BDerecho_largo));
	

		//Antebrazo Derecho
		float ADerecho_ancho = 0.25f;
		float ADerecho_alto = 0.9f;
		float ADerecho_largo = 0.25f;
		model = glm::translate(model, glm::vec3(0, -(ADerecho_alto / 2)  - (BDerecho_alto / 2), 0.0f ));
		model = glm::translate(model, glm::vec3(0, (ADerecho_alto / 2) , 0.0f));
		model = glm::rotate(model, -ADerecho_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0, -(ADerecho_alto / 2) , 0.0f));
		model = glm::scale(model, glm::vec3(ADerecho_ancho, ADerecho_alto, ADerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[6]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/ADerecho_ancho, 1/ADerecho_alto, 1/ADerecho_largo));
		

		//Mano Derecha
		float MDerecho_ancho = 0.1f;
		float MDerecho_alto = 0.3f;
		float MDerecho_largo = 0.20f;
		model = glm::translate(model, glm::vec3(0, -(MDerecho_alto / 2)  + (-ADerecho_alto / 2), 0 ));
		model = glm::translate(model, glm::vec3(0, (MDerecho_alto / 2) , 0));
		model = glm::rotate(model, MDerecho_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0, -(MDerecho_alto / 2), 0));
		model = glm::translate(model, glm::vec3(0, (MDerecho_alto / 2), 0));
		model = glm::rotate(model, MDerecho_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0, -(MDerecho_alto / 2), 0));
		model = glm::scale(model, glm::vec3(MDerecho_ancho, MDerecho_alto, MDerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		metalTexture.UseTexture();
		meshList[7]->RenderMesh();

		
		
		model = MatrixStack.top();

		//Brazo Izquierdo
		float BIzquierdo_ancho = 0.3f;
		float BIzquierdo_alto = 0.7f;
		float BIzquierdo_largo = 0.3f;
		model = glm::translate(model, glm::vec3((BIzquierdo_alto / 2) * cos(  Pi/2 + BIzquierdo_phi * toRadians) + (-Hombros_ancho * 0.75 / 2), (BIzquierdo_alto/2)* cos(-BIzquierdo_theta*toRadians)  * sin(-Pi / 2 + BIzquierdo_phi * toRadians) , (BIzquierdo_alto / 2) * sin(Pi + BIzquierdo_theta * toRadians)  ));
		model = glm::rotate(model, BIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model,  -BIzquierdo_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(BIzquierdo_ancho, BIzquierdo_alto, BIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[8]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/BIzquierdo_ancho, 1/BIzquierdo_alto, 1/ BIzquierdo_largo));

		//Antebrazo Izquierdo
		float AIzquierdo_ancho = 0.25f;
		float AIzquierdo_alto = 0.9f;
		float AIzquierdo_largo = 0.25f;
		//model = glm::mat4();
		model = glm::translate(model, glm::vec3((AIzquierdo_alto / 2) * cos(Pi / 2 - AIzquierdo_phi * toRadians),  (AIzquierdo_alto/2)* sin(-Pi / 2 + AIzquierdo_phi * toRadians) +(- BIzquierdo_alto/2), 0.0f));
		//model = glm::rotate(model, BIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, AIzquierdo_phi* toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(AIzquierdo_ancho, AIzquierdo_alto, AIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[9]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/AIzquierdo_ancho, 1/AIzquierdo_alto, 1/AIzquierdo_largo));

		//Mano Izquierda
		float MIzquierdo_ancho = 0.1f;
		float MIzquierdo_alto = 0.3f;
		float MIzquierdo_largo = 0.20f;
		model = glm::translate(model, glm::vec3((MIzquierdo_alto / 2) * cos(Pi / 2 + MIzquierdo_phi * toRadians), (MIzquierdo_alto / 2) * cos(Pi-MIzquierdo_theta * toRadians) * sin(Pi / 2 + MIzquierdo_phi * toRadians)+(-AIzquierdo_alto/2), (MIzquierdo_alto / 2) * sin(Pi + MIzquierdo_theta * toRadians)));
		model = glm::rotate(model, MIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -MIzquierdo_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(MIzquierdo_ancho, MIzquierdo_alto, MIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		alfombraTexture.UseTexture();
		meshList[10]->RenderMesh();

		MatrixStack.pop();
		model=MatrixStack.top();

		//Cadera
		float Cadera_ancho = 0.8f;
		float Cadera_alto = 0.3f;
		float Cadera_largo = 0.5f;
		model = glm::translate(model, glm::vec3(0, -Torso_alto / 2 - Cadera_alto/2, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Cadera_ancho, Cadera_alto, Cadera_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		jeansTexture.UseTexture();
		meshList[11]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/Cadera_ancho, 1/Cadera_alto, 1/Cadera_largo));

		MatrixStack.push(model);

		//Muslo Derecho
		float MusloDerecho_ancho = 0.4;
		float MusloDerecho_alto = 0.8f;
		float MusloDerecho_largo = 0.4f;
		model = glm::translate(model, glm::vec3((MusloDerecho_alto / 2) * cos(Pi / 2 - MusloDerecho_phi * toRadians) + (Cadera_ancho * 0.55 / 2), (MusloDerecho_alto / 2) * cos(MusloDerecho_theta * toRadians) * sin(-Pi / 2 + MusloDerecho_phi * toRadians) + (-Cadera_alto / 2), (MusloDerecho_alto / 2) * sin(Pi + MusloDerecho_theta * toRadians)));
		model = glm::rotate(model, MusloDerecho_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, MusloDerecho_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(MusloDerecho_ancho, MusloDerecho_alto, MusloDerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		jeansTexture.UseTexture();
		meshList[12]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/MusloDerecho_ancho, 1/MusloDerecho_alto, 1/MusloDerecho_largo));

		//Pantorrilla Derecha
		float PantDerecho_ancho = 0.3;
		float PantDerecho_alto = 1.0f;
		float PantDerecho_largo = 0.3f;
		model = glm::translate(model, glm::vec3(0.0f, (PantDerecho_alto / 2) * cos(Pi - PantDerecho_theta * toRadians) + (-MusloDerecho_alto / 2), (PantDerecho_alto / 2) * sin(Pi + PantDerecho_theta * toRadians)));
		model = glm::rotate(model, PantDerecho_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(PantDerecho_ancho, PantDerecho_alto, PantDerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		jeansTexture.UseTexture();
		meshList[13]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/PantDerecho_ancho, 1/PantDerecho_alto, 1/PantDerecho_largo));

		//Pie Derecho
		float PieDerecho_ancho = 0.3;
		float PieDerecho_alto = 0.2;
		float PieDerecho_largo = 0.5f;
		model = glm::translate(model, glm::vec3((PieDerecho_alto / 2) * cos(Pi / 2 - PieDerecho_phi * toRadians), (PieDerecho_alto / 2) * cos(Pi - PieDerecho_theta * toRadians) * sin(Pi / 2 + PieDerecho_phi * toRadians) + (-PantDerecho_alto / 2), (PieDerecho_alto / 2) * sin(Pi + PieDerecho_theta * toRadians) + (-PieDerecho_ancho * 0.5f)));
		model = glm::rotate(model, PieDerecho_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, PieDerecho_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(PieDerecho_ancho, PieDerecho_alto, PieDerecho_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		shoesTexture.UseTexture();
		meshList[14]->RenderMesh();

		model = MatrixStack.top();
		
		//Muslo Izquierdo
		float MusloIzquierdo_ancho = 0.4;
		float MusloIzquierdo_alto = 0.8f;
		float MusloIzquierdo_largo = 0.4f;
		model = glm::translate(model, glm::vec3( (MusloIzquierdo_alto/2)*cos(Pi/2+ MusloIzquierdo_phi *toRadians) + (-Cadera_ancho * 0.55 / 2), (MusloIzquierdo_alto / 2)* cos( MusloIzquierdo_theta * toRadians) * sin(-Pi / 2 + MusloIzquierdo_phi * toRadians) + (-Cadera_alto / 2), (MusloIzquierdo_alto / 2) * sin(Pi + MusloIzquierdo_theta * toRadians)));
		model = glm::rotate(model, MusloIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, - MusloIzquierdo_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(MusloIzquierdo_ancho, MusloIzquierdo_alto, MusloIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		jeansTexture.UseTexture();
		meshList[15]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/MusloIzquierdo_ancho, 1/MusloIzquierdo_alto, 1/MusloIzquierdo_largo));

		//Pantorrilla Izquierda
		float PantIzquierdo_ancho = 0.3;
		float PantIzquierdo_alto = 1.0f;
		float PantIzquierdo_largo = 0.3f;
		model = glm::translate(model, glm::vec3( 0.0f , (PantIzquierdo_alto / 2) * cos(Pi-PantIzquierdo_theta * toRadians) +(- MusloIzquierdo_alto / 2), (PantIzquierdo_alto / 2) * sin(Pi + PantIzquierdo_theta * toRadians)));
		model = glm::rotate(model,  PantIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(PantIzquierdo_ancho, PantIzquierdo_alto, PantIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		jeansTexture.UseTexture();
		meshList[16]->RenderMesh();

		model = glm::scale(model, glm::vec3(1/PantIzquierdo_ancho, 1/PantIzquierdo_alto, 1/PantIzquierdo_largo));

		//Pie Izquierdo
		float PieIzquierdo_ancho = 0.3;
		float PieIzquierdo_alto = 0.2;
		float PieIzquierdo_largo = 0.5f;
		model = glm::translate(model, glm::vec3((PieIzquierdo_alto / 2) * cos(Pi / 2 + PieIzquierdo_phi * toRadians), (PieIzquierdo_alto / 2) * cos(Pi - PieIzquierdo_theta * toRadians) * sin(Pi / 2 + PieIzquierdo_phi * toRadians) +(- PantIzquierdo_alto / 2), (PieIzquierdo_alto / 2) * sin(Pi + PieIzquierdo_theta * toRadians) +(- PieIzquierdo_ancho * 0.5f) ));
		model = glm::rotate(model, PieIzquierdo_theta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -PieIzquierdo_phi * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(PieIzquierdo_ancho, PieIzquierdo_alto, PieIzquierdo_largo));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		shoesTexture.UseTexture();
		meshList[17]->RenderMesh();
		
		MatrixStack.pop();
		MatrixStack.pop();

		glUseProgram(0);
		
		io.MouseDrawCursor= true;
		
		//Aqui configuramos el menu del ImGui
		//para modificar los angulos de cada pieza

		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Puppet \n");
			ImGui::Text("Torso:");
			ImGui::SliderFloat("Alpha#1", &Torso_alpha, -180.0f, 180.0f);
			ImGui::SliderFloat("Theta#1", &Torso_theta, -180.0f, 180.0f);
			ImGui::SliderFloat("Phi#1", &Torso_phi, -180.0f, 180.0f);

			ImGui::Text("Cuello:");
			ImGui::SliderFloat("Alpha#2", &Cuello_alpha, -80.0f, 80.0f);
			ImGui::SliderFloat("Theta#2", &Cuello_theta, -45.0f, 45.0f);
			ImGui::SliderFloat("Phi#2", &Cuello_phi, -45.0f, 45.0f);

			ImGui::Text("Brazo Derecho:");
			ImGui::SliderFloat("Theta#3", &BDerecho_theta, -90.0f, 180.0f);             
			ImGui::SliderFloat("Phi#3", &BDerecho_phi, 0.0f, 90.0f);

			ImGui::Text("Ante Brazo Derecho:");
			ImGui::SliderFloat("Phi#4", &ADerecho_phi, 0.0f, 135.0f);

			ImGui::Text("Mano Derecha:");
			ImGui::SliderFloat("Theta#5", &MDerecho_theta, -5.0f, 5.0f);
			ImGui::SliderFloat("Phi#5", &MDerecho_phi, -50.0f, 50.0f);

			ImGui::Text("Brazo Izquierdo:");
			ImGui::SliderFloat("Theta#6", &BIzquierdo_theta, -90.0f, 180.0f);
			ImGui::SliderFloat("Phi#6", &BIzquierdo_phi, 0.0f, 90.0f);

			ImGui::Text("Ante Brazo Izquierdo:");
			ImGui::SliderFloat("Phi#7", &AIzquierdo_phi, 0.0f, 135.0f);

			ImGui::Text("Mano Izquierda:");
			ImGui::SliderFloat("Theta#8", &MIzquierdo_theta, -5.0f, 5.0f);
			ImGui::SliderFloat("Phi#8", &MIzquierdo_phi, -50.0f, 50.0f);

			ImGui::Text("Muslo Derecho:");
			ImGui::SliderFloat("Theta#9", &MusloDerecho_theta, -90.0f, 90.0f);
			ImGui::SliderFloat("Phi#9", &MusloDerecho_phi, 0.0f, 45.0f);

			ImGui::Text("Pantorrila Derecha:");
			ImGui::SliderFloat("Theta#10", &PantDerecho_theta, 0.0f, -90.0f);

			ImGui::Text("Pie Derecho:");
			ImGui::SliderFloat("Theta#11", &PieDerecho_theta, -35.0f, 15.0f);
			ImGui::SliderFloat("Phi#11", &PieDerecho_phi, -20.0f, 20.0f);
			
			ImGui::Text("Muslo Izquierdo:");
			ImGui::SliderFloat("Theta#12", &MusloIzquierdo_theta, -90.0f, 90.0f);
			ImGui::SliderFloat("Phi#12", &MusloIzquierdo_phi, 0.0f, 45.0f);

			ImGui::Text("Pantorrila Izquierda:");
			ImGui::SliderFloat("Theta#13", &PantIzquierdo_theta, 0.0f, -90.0f);

			ImGui::Text("Pie Izquierdo:");
			ImGui::SliderFloat("Theta#14", &PieIzquierdo_theta, -35.0f, 15.0f);
			ImGui::SliderFloat("Phi#14", &PieIzquierdo_phi, -20.0f, 20.0f);

			//Reseteamos a 0.0f los angulos de todas las piezas
			if (ImGui::Button("Reset Puppet")) {
				//Angulos
				Torso_alpha = 0.0f;
				Torso_theta = 0.0f;
				Torso_phi = 0.0f;
				Cuello_alpha = 0.0f;
				Cuello_theta = 0.0f;
				Cuello_phi = 0.0f;
				BDerecho_theta = 0.0f;
				BDerecho_phi = 0.0f;
				BIzquierdo_theta = 0.0f;
				BIzquierdo_phi = 0.0f;
				MusloDerecho_theta = 0.0f;
				MusloDerecho_phi = 0.0f;
				MusloIzquierdo_theta = 0.0f;
				MusloIzquierdo_phi = 0.0f;
				ADerecho_phi = 0.0f;
				AIzquierdo_phi = 0.0f;
				PantDerecho_theta = 0.0f;
				PantIzquierdo_theta = 0.0f;
				MDerecho_theta = 0.0f;
				MDerecho_phi = 0.0f;
				MIzquierdo_theta = 0.0f;
				MIzquierdo_phi = 0.0f;
				PieDerecho_theta = 0.0f;
				PieDerecho_phi = 0.0f;
				PieIzquierdo_theta = 0.0f;
				PieIzquierdo_phi = 0.0f;

			}
				

			ImGui::Text("[ESC] Cerrar programa");

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		//Dibujamos el menu ImGui
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		mainWindow.swapBuffers();

	}

	//Destruimos el menu ImGui
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	return 0;
}