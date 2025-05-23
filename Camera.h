#ifndef CAMERA
#define CAMERA
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utility.h"
#include <glad.h> 
#include <glfw3.h>

class Camera
{
public:

	float cameraSpeed = 2.5f;
	glm::vec3 cameraPos, cameraFront, cameraUp;
	glm::mat4 view;

	glm::vec3 CameraDirection;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 1920 / 2;
	float lastY = 1080 / 2;
	double xpos = 1920 / 2, ypos = 1080 / 2;
	bool FirstMouse = true;

	Camera();
	void left(Utilites* util);
	void right(Utilites* util);
	void forward(Utilites* util);
	void backwards(Utilites* util);
	void HandleMouse(GLFWwindow* window);
	void UpdateView();
};

#endif