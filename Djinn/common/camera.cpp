#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

using namespace glm;

Camera::Camera(GLFWwindow* window) : window(window) {
    position = vec3(0, 0, 5);
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    FoV = 45.0f;
    speed = 8.0f;
    mouseSpeed = 0.001f;
    fovSpeed = 2.0f;

    bool action1_enabled = false;
    bool action2_enabled = false;
}

void Camera::onMouseMove(double xPos, double yPos) {

    static double lastxPos = xPos;
    static double lastyPos = yPos;

    if (active) {
        horizontalAngle += mouseSpeed * (lastxPos - xPos);
        verticalAngle += mouseSpeed * (lastyPos - yPos);
    }
    lastxPos = xPos;
    lastyPos = yPos;
}

void Camera::update(void) {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Task 5.4: right and up vectors of the camera coordinate system
    // use spherical coordinates
    vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    vec3 right(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector
    vec3 up = cross(right, direction);

    // Task 5.5: update camera position using the direction/right vectors
    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        position += up * deltaTime * speed;
        //std::cout << up.x << up.y << up.z << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        position -= up * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        action1_enabled = true;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        action2_enabled = true;
    }
    float limit = 2.0f;

    if (action1_enabled) {
        if (abs(position.y - 23.0f) < limit && abs(position.z - 33.0f) < 1.5 * limit) {
            action1_enabled = false;
            position = vec3(0.0f, 23.0f, 33.0f); // Set the camera's position to the exact target position
        } else {
            position += up * deltaTime * speed * 0.35f;
            position -= direction * deltaTime * speed;
        }
    }

    if (action2_enabled) {
        if (abs(position.y - 3.0f) < 0.3 * limit && abs(position.z - 8.0f) < 0.5 * limit) {
            action2_enabled = false;
            position = vec3(0.0f, 3.0f, 8.0f); // Set the camera's position to the exact target position
        } else {
            position -= up * deltaTime * speed * 0.35f;
            position += direction * deltaTime * speed;
        }
    }

    // Task 5.6: handle zoom in/out effects
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (radians(FoV) > 0.1 + radians(fovSpeed))
        FoV -= fovSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (radians(FoV) < 3.14 - radians(fovSpeed))
        FoV += fovSpeed;
    }

    // Task 5.7: construct projection and view matrices
    projectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 200.0f);
    viewMatrix = lookAt(
        position,
        position + direction,
        up
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}