#include "Shader.h"

//Inicializamos en 0's los valores de los shaders
Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

}

//Funcion para meter el codigo del Vertex Shader y fragment Shader con el codigo en strings
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {

	CompileShader(vertexCode, fragmentCode);

}

//Funcion para crear  Vertex Shader y fragment Shader a partir de una direccion de un directorio 
void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {

	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);

	//std::cout << vertexString << std::endl;
	//std::cout << fragmentString << std::endl;

	//printf("&s", vertexString);
	//printf("&s",fragmentString);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);

}

//Funcion para leer el contenido del directorio
std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::fstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		//printf("Fallo readfile");
		printf("Failed to read %s file doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;

}

//Funcion para comopilar Vertex y Frangment shader
void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Error creating shader program\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s \n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
}

//Funcion para configurar el vertex o fragment shader
void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLenght[1];
	codeLenght[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: %s \n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);

}

//Variables para obtener informacion del Shader
GLuint Shader::GetProjectionLocation() {
	return uniformProjection;
}
GLuint Shader::GetModelLocation() {
	return uniformModel;
}
GLuint Shader::GetViewLocation() {
	return uniformView;
}

//Funcion para usar Shader
void Shader::UseShader() {

	glUseProgram(shaderID);

}

//Funcion para limpiar Shader
void Shader::ClearShader() {

	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

//Destructor
Shader::~Shader() {
	ClearShader();
}