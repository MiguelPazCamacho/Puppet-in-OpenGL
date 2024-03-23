#include "Camera.h"

Camera::Camera(){}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
	//Guardamos los valores en nuestra clase
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startMoveSpeed;

	update();


}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
	
	//Establecemos la velocidad de acuerdo al Delta time
	GLfloat velocity = moveSpeed * deltaTime;

	//Establecemos if's para al precionar una tecla
	//nos movamos por el espacio

	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A]) {
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D]) {
		position += right * velocity;
	}

	if (keys[GLFW_KEY_UP]) {
		position += up * velocity;
	}

	if (keys[GLFW_KEY_DOWN]) {
		position -= up * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {

	//Calculamos la diferencia de la posicion
	//con la antigua multiplicada por la velocidad
	//establecida para mover la camara con el mouse

	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();

}

glm::mat4 Camera::calculateViewMatrix() {
	//Calculamos la matriz a la cual vemos
	return glm::lookAt(position, position + front, up);

}

void Camera::update() {
	//Actualizamos la posiciones para movernos por el espacio
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera() {

}