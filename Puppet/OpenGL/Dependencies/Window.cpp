#include "Window.h"

//Constructor e inicializamos los valores de Window en 0's
Window::Window() {
	width = 800;
	height = 600;

	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

//Constructor de la Ventana para especificar altura y ancho
Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;

	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

}

//Inicializamos la Ventana para trabajar con OpenGL 3 y que sea compatible
int Window::Initialize() {
	//Inicializa GLFW
	if (!glfwInit()) {
		printf("GLFW initializacion failed");
		glfwTerminate();
		return 1;
	}

	//Establecemos la version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Puppet-Graficas por computadora-Miguel Paz", NULL, NULL);

	if (!mainWindow) {
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}


	//Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//Handle key + mouse Input
	createCallbacks();

	//Desaparecer el cursor
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initializacion failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	//setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

//Funcion para recibir inputs del teclado y mouse
void Window::createCallbacks() {

	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);

}

//Obtenemos el cambio del mouse del eje x
GLfloat Window::getXChange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

//Obtenemos el cambio del mouse del eje y
GLfloat Window::getYChange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

//Actualizamos los valores del arreglo de keys cuando la tecla es presionada o soltada
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {

		if (action == GLFW_PRESS) {

			theWindow->keys[key] = true;
			printf("Pressed: %d\n", key);

		}
		else if (action == GLFW_RELEASE) {

			theWindow->keys[key] = false;
			printf("Released: %d\n", key);

		}

	}
}

//Funcion para obtener los cambios de la posicion del mouse
void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mousedFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mousedFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("x:%.6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);

}

//Destructor
Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}