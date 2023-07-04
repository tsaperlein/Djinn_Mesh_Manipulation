#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glfw3.h>
#include <glm/glm.hpp>

class Camera 
{
public:
    GLFWwindow* window;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // Initial position : on +Z
    glm::vec3 position;
    // Initial horizontal angle : toward -Z
    float horizontalAngle;
    // Initial vertical angle : none
    float verticalAngle;
    // Field of View
    float FoV;

    float speed; // units / second
    float mouseSpeed;
    float fovSpeed;

    bool action1_enabled = false;
    bool action2_enabled = false;

    bool active = true;

    Camera(GLFWwindow* window);

    void onMouseMove(double xPos, double yPos);

    void update();
};

#endif