#include "Texture.h"

//Inicializamos en 0's los valores de la clase por default
Texture::Texture() {
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = (char*)"";
}

//Inicializmos en 0's los valores y guardamos la locacion de la textura
Texture::Texture(char* fileloc) {
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileloc;

}

//Funcion para cargar las texturas y configurarlas
void Texture::LoadTexture() {
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

	//Cheacmos que se haya abierto el archivo
	if (!texData) {
		printf("Failed to find: %s\n", fileLocation);
		return;
	}


	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Configuramos que se repita la textura y que use GL_LINEAR como estilo de renderizado
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

//Funcion para aplicar textura al objeto
void Texture::UseTexture() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

}

//FUncion para limpiar y destruir la textura
void Texture::ClearTexture() {
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = (char*)"";
}

//Destructor
Texture::~Texture() {
	ClearTexture();
}
