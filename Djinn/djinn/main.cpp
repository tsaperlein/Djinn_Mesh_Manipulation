// Include C++ headers
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <SOIL.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Shader loading utilities and other
#include <common/shader.h>
#include <common/util.h>
#include <common/camera.h>
#include <common/model.h>
#include <common/texture.h>
#include <common/light.h>
#include <common/SmokeEmitter.h>
#include <common/CoinRainEmitter.h>

//TODO delete the includes afterwards
#include <chrono>
using namespace std::chrono;

using namespace std;
using namespace glm;
using namespace ogl;

// Function prototypes
void initialize();
void createContext();
void mainLoop();
void free();
void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

#define W_WIDTH 1024
#define W_HEIGHT 768
#define TITLE "Djinn Mesh Manipulation"

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

// Number of particles created
#define NUM_COINS 200
#define NUM_PARTICLES 200

#define RAND ((float) rand()) / (float) RAND_MAX

// Creating a structure to store the material parameters of an object
struct Material {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Ns;
};

// Global variables
GLFWwindow* window;
Camera* camera;
Light* light;

// Shaders
GLuint depthProgram; // Depth Shaders
GLuint shadowMapShaderProgram; // Shadow Map Shaders
GLuint coinRainShaderProgram; // Coin Rain Shaders
GLuint blueSmokeShaderProgram; // Blue Smoke Shaders

// Djinn
Model *djinnMesh;
GLuint djinnAlbedoTexture;
mat4 djinnModelMatrix = mat4(1.0f);
float djinnTransparency = 0.0f;

// Genie Lamp
Drawable* lamp;
GLuint lampAlbedoTexture, lampRoughnessTexture, lampMetallicTexture;
mat4 lampModelMatrix = mat4(1.0f);

// Table
Drawable* table;
GLuint tableAlbedoTexture, tableRoughnessTexture;
mat4 tableModelMatrix = mat4(1.0f);

// Walls and roof(wall5)
Drawable* wall1;
mat4 wall1ModelMatrix = mat4(1.0f);
Drawable* wall2;
mat4 wall2ModelMatrix = mat4(1.0f);
Drawable* wall3;
mat4 wall3ModelMatrix = mat4(1.0f);
Drawable* wall4;
mat4 wall4ModelMatrix = mat4(1.0f);
Drawable* wall5;
mat4 wall5ModelMatrix = mat4(1.0f);
GLuint wallAlbedoTexture, wallRoughnessTexture;

// Floor
Drawable* gfloor;
GLuint floorAlbedoTexture, floorRoughnessTexture;
mat4 floorModelMatrix = mat4(1.0f);

// Clouds (for the rain of coins)
Drawable* clouds;
GLuint cloudAlbedoTexture, cloudRoughnessTexture;
mat4 cloudsModelMatrix = mat4(1.0f);
float cloudTransparency = 0.0f;

// --------------- Particles --------------------
// Coins
Drawable* coin;
GLuint coinColor, coinDiffuceColorSampler;
// The position that the rain starts
CoinRainEmitter* r_emitter;
glm::vec3 rain_emitter_pos(0.0f, 20.0f, 0.0f);

// Blue Smoke
Drawable* smoke;
GLuint smokeTexture, smokeDiffuceColorSampler;
// Where the particles of the smoke should stop being rendered
float height_threshold = 5.0f;
// The position that the smoke starts
SmokeEmitter* s_emitter;
glm::vec3 smoke_emitter_pos(0.0f, 0.0f, 0.0f);

GLuint depthFrameBuffer, depthTexture;

// Projection-View-Model Matrixes
GLuint projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionAndViewMatrix;

// Light Properties
GLuint lightPositionLocation;
GLuint lightPowerLocation;

// For the Shader, in order to send the planeCoeffs
GLuint planeLocation;

GLuint KaLocation, KdLocation, KsLocation, NsLocation;
GLuint LaLocation, LdLocation, LsLocation;

// Textures
GLuint albedoColorSampler;		// Diffuse	
GLuint roughnessColorSampler;	// Specular
GLuint metallicColorSampler;

// For If statements inside the Shaders
GLuint useTextureLocation, alphaLocation, transparencyLocation;

GLuint depthMapSampler;
GLuint lightVPLocation;
GLuint lightDirectionLocation;
GLuint lightFarPlaneLocation;
GLuint lightNearPlaneLocation;

// locations for depthProgram
GLuint shadowViewProjectionLocation; 
GLuint shadowModelLocation;

// locations for particleProgram
GLuint particleViewProjectionLocation; 
GLuint particleModelLocation;

// To change the modelMatrixes
mat4 rotationX, rotationZ, djinn_rotation;
vec3 djinn_translation, djinn_scaling;

// To change the transparency for the djinn Mesh
vec4 planeCoeffs;
vec3 planeNormal;

// States of Game
bool coin_rain = false; 				// If it's true, the rain starts
bool blue_smoke = false; 				// If it's true, the smoke starts coming out of the lamp
bool game_paused = false; 				// If it's true, the particles stop moving
bool use_sorting = true;				// If it's true, the program uses sorting
bool use_rotations = true;				// If it's true, the program uses rotations
bool tremble_action = false;			// If it's true, the lamp trembles
bool start_cloud_transparency = false;	// If it's true, the clouds start to get non transparent

// Creating a function to upload the light parameters to the shader program
void uploadLight(const Light& light) {
	glUniform4f(LaLocation, light.La.r, light.La.g, light.La.b, light.La.a);
	glUniform4f(LdLocation, light.Ld.r, light.Ld.g, light.Ld.b, light.Ld.a);
	glUniform4f(LsLocation, light.Ls.r, light.Ls.g, light.Ls.b, light.Ls.a);
	glUniform3f(lightPositionLocation, light.lightPosition_worldspace.x, light.lightPosition_worldspace.y, light.lightPosition_worldspace.z);    
	glUniform1f(lightPowerLocation, light.power);
}

// Function that generates a Bezier Curve
std::vector<glm::vec3> generateBezierCurve(int numVertices, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    std::vector<glm::vec3> vertices;
    vertices.reserve(numVertices);

    for (int i = 0; i < numVertices; i++) {
        // Interpolate between the control points using the Bézier curve formula
        float t = (float)i / (numVertices-1);
        float u = 1.0 - t;
        float tt = t*t;
        float uu = u*u;
        float uuu = uu * u;
        float ttt = tt * t;

        glm::vec3 p = uuu * p0;
        p += 3.0f * uu * t * p1;
        p += 3.0f * u * tt * p2;
        p += ttt * p3;

        vertices.push_back(p);
    }
    return vertices;
}

// Function that interpolates between the control points using the Bézier curve formula
glm::vec3 bezier_pos(float t, std::vector<glm::vec3> control_points) {
    int numVertices = control_points.size();
    int i0 = (int)(t * numVertices);
    i0 = glm::clamp(i0, 0, numVertices - 1);
    int i1 = i0 + 1;
    i1 = glm::clamp(i1, 0, numVertices - 1);
    float u = t * numVertices - i0;
    return (1 - u) * control_points[i0] + u * control_points[i1];
}

void createContext()
{
    // Create and compile our GLSL program from the shaders
    shadowMapShaderProgram = loadShaders(
        "Shaders/shadowMap-shaders/ShadowMapping.vertexshader",
        "Shaders/shadowMap-shaders/ShadowMapping.fragmentshader");

    depthProgram = loadShaders(
        "Shaders/depth-shaders/Depth.vertexshader",
        "Shaders/depth-shaders/Depth.fragmentshader");

	coinRainShaderProgram = loadShaders(
        "Shaders/particles-shaders/coinRain.vertexshader",
        "Shaders/particles-shaders/coinRain.fragmentshader");

	blueSmokeShaderProgram = loadShaders(
        "Shaders/particles-shaders/blueSmoke.vertexshader",
        "Shaders/particles-shaders/blueSmoke.fragmentshader");

    // --- shadowMapShaderProgram ---
    // Model P-V-M Matrixes as uniform variables
    projectionMatrixLocation = glGetUniformLocation(shadowMapShaderProgram, "P");
    viewMatrixLocation = glGetUniformLocation(shadowMapShaderProgram, "V");
    modelMatrixLocation = glGetUniformLocation(shadowMapShaderProgram, "M");

	// PlaneCoeffs
	planeLocation = glGetUniformLocation(shadowMapShaderProgram, "planeCoeffs");

    // Model Materials as uniform variables
    KaLocation = glGetUniformLocation(shadowMapShaderProgram, "mtl.Ka");
	KdLocation = glGetUniformLocation(shadowMapShaderProgram, "mtl.Kd");
	KsLocation = glGetUniformLocation(shadowMapShaderProgram, "mtl.Ks");
	NsLocation = glGetUniformLocation(shadowMapShaderProgram, "mtl.Ns");

    // Light Properties as uniform variables
    LaLocation = glGetUniformLocation(shadowMapShaderProgram, "light.La");
	LdLocation = glGetUniformLocation(shadowMapShaderProgram, "light.Ld");
	LsLocation = glGetUniformLocation(shadowMapShaderProgram, "light.Ls");

    // Light Position-Power as uniform variables
    lightPositionLocation = glGetUniformLocation(shadowMapShaderProgram, "light.lightPosition_worldspace");
    lightPowerLocation = glGetUniformLocation(shadowMapShaderProgram, "light.power");

	// Textures
	albedoColorSampler = glGetUniformLocation(shadowMapShaderProgram, "albedoColorSampler");
	roughnessColorSampler = glGetUniformLocation(shadowMapShaderProgram, "roughnessColorSampler");
	metallicColorSampler = glGetUniformLocation(shadowMapShaderProgram, "metallicColorSampler");
	
	// If useTexture = 0, use material
	// If useTexture = 1, use texture
	// If useTexture = 2, use texture for the Djinn
	// If useTexture = 2, use texture for the clouds
	useTextureLocation = glGetUniformLocation(shadowMapShaderProgram, "useTexture"); 

	// We are sending the alpha value, and
	// If useTransparency = 0 use the transparency that is given
	// If useTransparency = 1 change the transparency of the Djinn
	alphaLocation = glGetUniformLocation(shadowMapShaderProgram, "alpha");
	transparencyLocation = glGetUniformLocation(shadowMapShaderProgram, "useTransparency");

    // Shadow Rendering
    depthMapSampler = glGetUniformLocation(shadowMapShaderProgram, "shadowMapSampler");

    // Light View-Projection Matrixes
    lightVPLocation = glGetUniformLocation(shadowMapShaderProgram, "lightVP");

    // --- depthProgram ---
	shadowViewProjectionLocation = glGetUniformLocation(depthProgram, "VP");
	shadowModelLocation = glGetUniformLocation(depthProgram, "M");

	// --- Particle Programs ---
	projectionAndViewMatrix = glGetUniformLocation(coinRainShaderProgram, "PV");
	projectionAndViewMatrix = glGetUniformLocation(blueSmokeShaderProgram, "PV");

	// Djinn
	djinnMesh = new Model("OBJs/Djinn.obj");

	djinnAlbedoTexture = loadSOIL("Textures/djinn/albedo.png");

	// Sizes of the walls, floor and the roof
	float size1 = 8.0f;
	float size2 = 34.0f;
	float size3 = 15.0f;
	float floorY1 = -3.439f;
	float floorY2 = 24.0f;

	// ------------------------- WALLS ---------------
	// Wall Vertices
	vector<vec3> wallVertices1 = {
		vec3(-size3, floorY1, -size1),
		vec3(-size3, floorY1,  size2),
		vec3(-size3, floorY2,  size2),
		vec3(-size3, floorY2,  size2),
		vec3(-size3, floorY2, -size1),
		vec3(-size3, floorY1, -size1),
	};
	vector<vec3> wallVertices2 = {
		vec3(-size3, floorY1, size2),
		vec3( size3, floorY1, size2),
		vec3( size3, floorY2, size2),
		vec3( size3, floorY2, size2),
		vec3(-size3, floorY2, size2),
		vec3(-size3, floorY1, size2),
	};
	vector<vec3> wallVertices3 = {
		vec3( size3, floorY1,  size2),
		vec3( size3, floorY1, -size1),
		vec3( size3, floorY2, -size1),
		vec3( size3, floorY2, -size1),
		vec3( size3, floorY2,  size2),
		vec3( size3, floorY1,  size2),
	};
	vector<vec3> wallVertices4 = {
		vec3( size3, floorY1, -size1),
		vec3(-size3, floorY1, -size1),
		vec3(-size3, floorY2, -size1),
		vec3(-size3, floorY2, -size1),
		vec3( size3, floorY2, -size1),
		vec3( size3, floorY1, -size1),
	};
	vector<vec3> wallVertices5 = {
		vec3(-size3, floorY2, -size1),
		vec3(-size3, floorY2,  size2),
		vec3( size3, floorY2,  size2),
		vec3( size3, floorY2,  size2),
		vec3( size3, floorY2, -size1),
		vec3(-size3, floorY2, -size1),
	};

	// Wall UVs
	vector<vec2> wallUVs = {
		vec2(0.0f, 0.0f),
		vec2(0.0f, 2.0f),
		vec2(2.0f, 2.0f),
		vec2(2.0f, 2.0f),
		vec2(2.0f, 0.0f),
		vec2(0.0f, 0.0f),
	};

    // Floor Normals
	vector<vec3> wallNormals = {
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	};

	wall1 = new Drawable(wallVertices1, wallUVs, wallNormals);
	wall2 = new Drawable(wallVertices2, wallUVs, wallNormals);
	wall3 = new Drawable(wallVertices3, wallUVs, wallNormals);
	wall4 = new Drawable(wallVertices4, wallUVs, wallNormals);
	wall5 = new Drawable(wallVertices5, wallUVs, wallNormals);

	wallAlbedoTexture = loadSOIL("Textures/wall/t3/albedo.jpg");
	wallRoughnessTexture = loadSOIL("Textures/wall/t2/roughness.jpg");

	// ------------------------- FLOOR ---------------
	// Floor Vertices
	vector<vec3> floorVertices = {
		vec3(-size3, floorY1, -size1),
		vec3(-size3, floorY1,  size2),
		vec3( size3, floorY1,  size2),
		vec3( size3, floorY1,  size2),
		vec3( size3, floorY1, -size1),
		vec3(-size3, floorY1, -size1),
	};
	// Floor UVs
	vector<vec2> floorUVs = {
		vec2(0.0f, 0.0f),
		vec2(0.0f, 4.0f),
		vec2(4.0f, 4.0f),
		vec2(4.0f, 4.0f),
		vec2(4.0f, 0.0f),
		vec2(0.0f, 0.0f),
	};
    // Floor Normals
	vector<vec3> floorNormals = {
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	};
	gfloor = new Drawable(floorVertices, floorUVs, floorNormals);

	floorAlbedoTexture = loadSOIL("Textures/floor/t4/albedo.jpg");
	floorRoughnessTexture = loadSOIL("Textures/floor/t4/roughness.jpg");

    // Lamp
    lamp = new Drawable("OBJs/genie_lamp.obj");

	lampAlbedoTexture = loadSOIL("Textures/gold/1/albedo.png");
	lampMetallicTexture = loadSOIL("Textures/gold/1/metallic.png");
	lampRoughnessTexture = loadSOIL("Textures/gold/1/roughness.png");

	// Table
	table = new Drawable("OBJs/table.obj");

	tableAlbedoTexture = loadSOIL("Textures/table/albedo.png");
	tableRoughnessTexture = loadSOIL("Textures/table/roughness.png");

	// Rain of Coins
	coin = new Drawable("OBJs/coin.obj");
	coinDiffuceColorSampler = glGetUniformLocation(coinRainShaderProgram, "texture1");
    coinColor = loadSOIL("Textures/gold/1/albedo.png");;

	// Smoke from the tip of the genie lamp
	smoke = new Drawable("OBJs/quad.obj");
	smokeDiffuceColorSampler = glGetUniformLocation(blueSmokeShaderProgram, "texture2");
    smokeTexture = loadSOIL("Textures/blue_smoke.png");

	// Clouds
	clouds = new Drawable("OBJs/clouds.obj");
    cloudAlbedoTexture = loadSOIL("Textures/cloud/albedo1.png");
	cloudRoughnessTexture = loadSOIL("Textures/cloud/roughness.png");

	// --- Depth Framebuffer and Texture (to store the depthmap) ---
    // Generate a Framebuffer
    glGenFramebuffers(1, &depthFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFrameBuffer);

    glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	// Telling opengl the required information about the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
		GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);							// Task 4.5 Texture wrapping methods
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);							// GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	// Attaching the texture to the framebuffer, so that it will monitor the depth component
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	
	// Since the depth buffer is only for the generation of the depth texture, 
	// there is no need to have a color output
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Check if Framebuffer is ok!
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glfwTerminate();
		throw runtime_error("Frame buffer not initialized correctly");
	}
	// Binding the default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glfwSetKeyCallback(window, pollKeyboard);
}

void free()
{
    glDeleteProgram(shadowMapShaderProgram);
    glDeleteProgram(depthProgram);
	glDeleteProgram(coinRainShaderProgram);
	glDeleteProgram(blueSmokeShaderProgram);
    glfwTerminate();
}

void depth_pass(mat4 viewMatrix, mat4 projectionMatrix) {

	// Setting viewport to shadow map size
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

	// Binding the depth framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthFrameBuffer);

	// Cleaning the framebuffer depth information (stored from the last render)
	glClear(GL_DEPTH_BUFFER_BIT);

	// Selecting the new shader program that will output the depth component
	glUseProgram(depthProgram);

	// sending the view and projection matrix to the shader
	mat4 view_projection = projectionMatrix * viewMatrix;
	glUniformMatrix4fv(shadowViewProjectionLocation, 1, GL_FALSE, &view_projection[0][0]);

	// ---- rendering the scene ---- //
	// LAMP
	lampModelMatrix = mat4(1.0f);

	if (tremble_action) {
        // generate random rotation angles around x, y and z axes
        float angleX = 0.5f * (RAND - RAND);
        float angleZ = 0.1f * (RAND - RAND);

        // apply the rotation to the object
        rotationX = rotate(mat4(1.0f), angleX, glm::vec3(1.0f, 0.0f, 0.0f));
        rotationZ = rotate(mat4(1.0f), angleZ, glm::vec3(0.0f, 0.0f, 1.0f));

		lampModelMatrix *= translate(mat4(1.0f), vec3(-0.9f, -0.05f, 0)) * rotationX * rotationZ * translate(mat4(1.0f), vec3(0.9f, 0.05f, 0));
    }

	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &lampModelMatrix[0][0]);
	lamp->bind();
	lamp->draw();

	// TABLE
	tableModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &tableModelMatrix[0][0]);
	table->bind();
	table->draw();

	// WALLS
	wall1ModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &wall1ModelMatrix[0][0]);
	wall1->bind();
	wall1->draw();

	wall2ModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &wall2ModelMatrix[0][0]);
	wall2->bind();
	wall2->draw();

	wall3ModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &wall3ModelMatrix[0][0]);
	wall3->bind();
	wall3->draw();

	wall4ModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &wall4ModelMatrix[0][0]);
	wall4->bind();
	wall4->draw();

	wall5ModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &wall4ModelMatrix[0][0]);
	wall5->bind();
	wall5->draw();

	// FLOOR
	floorModelMatrix = mat4(1.0f);
	glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &floorModelMatrix[0][0]);
	gfloor->bind();
	gfloor->draw();

	if (coin_rain) {
		glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &cloudsModelMatrix[0][0]);

		clouds->bind();
		clouds->draw();
	}

	if (blue_smoke) {
		glUniformMatrix4fv(shadowModelLocation, 1, GL_FALSE, &djinnModelMatrix[0][0]);
		djinnMesh->draw();
	}

	// binding the default framebuffer again
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void lighting_pass(mat4 viewMatrix, mat4 projectionMatrix) {

	// Step 1: Binding a frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 2 * W_WIDTH, 2 * W_HEIGHT);

	// Step 2: Clearing color and depth info
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Step 3: Selecting shader program
	glUseProgram(shadowMapShaderProgram);

	// Making view and projection matrices uniform to the shader program
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// uploading the light parameters to the shader program
	uploadLight(*light);

	// Sending the shadow texture to the shaderProgram
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glUniform1i(depthMapSampler, 0);

	// Sending the light View-Projection matrix to the shader program
	mat4 light_vp = light->lightVP();
	glUniformMatrix4fv(lightVPLocation, 1, GL_FALSE, &light_vp[0][0]);

	// ------------------------------- Drawing scene objects ------------------------------- //	
	// ------------------------- LAMP (TEXTURES 1,2,3)

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &lampModelMatrix[0][0]);
    // Albedo
    glActiveTexture(GL_TEXTURE1);								
	glBindTexture(GL_TEXTURE_2D, lampAlbedoTexture);		 
	glUniform1i(albedoColorSampler, 1);		
	// Metallic
	glActiveTexture(GL_TEXTURE2);						
	glBindTexture(GL_TEXTURE_2D, lampMetallicTexture);		
	glUniform1i(metallicColorSampler, 2);	
	// Roughness
	glActiveTexture(GL_TEXTURE3);							
	glBindTexture(GL_TEXTURE_2D, lampRoughnessTexture);	
	glUniform1i(roughnessColorSampler, 3);

	/* Inside the fragment shader, there is an if statement
	whether to use the material of an object or sample a texture */
	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 1);

	lamp->bind();
	lamp->draw();

	// ---------------------------- TABLE (TEXTURES 4,5)
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &tableModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE4);							
	glBindTexture(GL_TEXTURE_2D, tableAlbedoTexture);		
	glUniform1i(albedoColorSampler, 4);					
	glActiveTexture(GL_TEXTURE5);												
	glBindTexture(GL_TEXTURE_2D, tableRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 5);	

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 1);
	table->bind();
	table->draw();

	// ---------------------------- FLOOR (TEXTURES 6,7)
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &floorModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE6);							
	glBindTexture(GL_TEXTURE_2D, floorAlbedoTexture);		
	glUniform1i(albedoColorSampler, 6);					
	glActiveTexture(GL_TEXTURE7);					
	glBindTexture(GL_TEXTURE_2D, floorRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 7);	

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 1);
	gfloor->bind();
	gfloor->draw();

	// ---------------------------- FLOOR (TEXTURES 8,9,10,11,12,13,14,15)
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &wall1ModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE8);							
	glBindTexture(GL_TEXTURE_2D, wallAlbedoTexture);		
	glUniform1i(albedoColorSampler, 8);					
	glActiveTexture(GL_TEXTURE9);					
	glBindTexture(GL_TEXTURE_2D, wallRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 9);

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 2);
	wall1->bind();
	wall1->draw();

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &wall2ModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE10);							
	glBindTexture(GL_TEXTURE_2D, wallAlbedoTexture);		
	glUniform1i(albedoColorSampler, 10);					
	glActiveTexture(GL_TEXTURE11);					
	glBindTexture(GL_TEXTURE_2D, wallRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 11);

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 2);
	wall2->bind();
	wall2->draw();

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &wall3ModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE12);							
	glBindTexture(GL_TEXTURE_2D, wallAlbedoTexture);		
	glUniform1i(albedoColorSampler, 12);					
	glActiveTexture(GL_TEXTURE13);					
	glBindTexture(GL_TEXTURE_2D, wallRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 13);

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 2);
	wall3->bind();
	wall3->draw();

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &wall4ModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE14);							
	glBindTexture(GL_TEXTURE_2D, wallAlbedoTexture);		
	glUniform1i(albedoColorSampler, 14);					
	glActiveTexture(GL_TEXTURE15);					
	glBindTexture(GL_TEXTURE_2D, wallRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 15);

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 2);
	wall4->bind();
	wall4->draw();

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &wall4ModelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE16);							
	glBindTexture(GL_TEXTURE_2D, wallAlbedoTexture);		
	glUniform1i(albedoColorSampler, 16);					
	glActiveTexture(GL_TEXTURE17);					
	glBindTexture(GL_TEXTURE_2D, wallRoughnessTexture);		
	glUniform1i(roughnessColorSampler, 17);

	glUniform1f(alphaLocation, 1.0f);
	glUniform1i(transparencyLocation, 0);
	glUniform1i(useTextureLocation, 2);
	wall5->bind();
	wall5->draw();

	if (coin_rain) {
		// ---------------------------- CLOUDS (TEXTURES 16,17)
		mat4 cloudsModelMatrix = mat4(1.0f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &cloudsModelMatrix[0][0]);

		glActiveTexture(GL_TEXTURE18);						
		glBindTexture(GL_TEXTURE_2D, cloudAlbedoTexture);		
		glUniform1i(albedoColorSampler, 18);
		glActiveTexture(GL_TEXTURE19);						
		glBindTexture(GL_TEXTURE_2D, cloudRoughnessTexture);		
		glUniform1i(roughnessColorSampler, 19);

		glUniform1f(alphaLocation, cloudTransparency);
		glUniform1i(transparencyLocation, 0);
		glUniform1i(useTextureLocation, 3);
		clouds->bind();
		clouds->draw();

		if (start_cloud_transparency) {
			cloudTransparency += 0.001f;	
		}	
	}

	if (blue_smoke) {
		// ---------------------------- DJINN (TEXTURES 18)
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &djinnModelMatrix[0][0]);

		glActiveTexture(GL_TEXTURE20);						
		glBindTexture(GL_TEXTURE_2D, djinnAlbedoTexture);		
		glUniform1i(albedoColorSampler, 20);

		planeNormal = vec3(vec4(0, 1, 0, 0));
		float d = -dot(planeNormal, vec3(5,5,0));
		planeCoeffs = vec4(planeNormal, d);

		glUniform4f(planeLocation, planeCoeffs.x, planeCoeffs.y, planeCoeffs.z, planeCoeffs.w);				

		glUniform1f(alphaLocation, djinnTransparency);
		glUniform1i(transparencyLocation, 1);
		glUniform1i(useTextureLocation, 1);
		djinnMesh->draw();
	}
}

float computeTransparency(float progress) {
    float transparency;
    if (progress < 0.5f) {
        transparency = progress;
    }
    else {
        transparency = 1 - (progress - 0.5f);
    }
    return transparency;
}

void mainLoop()
{
    light->update();
	mat4 light_proj = light->projectionMatrix;
	mat4 light_view = light->viewMatrix;

	camera->position = vec3(0, 3, 8);
	camera->verticalAngle = -0.33f;

	r_emitter = new CoinRainEmitter(coin, NUM_COINS);
	s_emitter = new SmokeEmitter(smoke, NUM_PARTICLES);

	float progress = 0.0f;
	float counter = 0.0f;
	float thickness_factor = 0.0f;

	float t = glfwGetTime();
	
	do
	{
		light->update();
        mat4 light_proj = light->projectionMatrix;
        mat4 light_view = light->viewMatrix;

        depth_pass(light_view, light_proj);

        // Getting Camera Information
        camera->update();
        mat4 projectionMatrix = camera->projectionMatrix;
        mat4 viewMatrix = camera->viewMatrix;

		float currentTime = glfwGetTime();
		float dt = currentTime - t;

		// Render the scene from camera's perspective
        lighting_pass(viewMatrix, projectionMatrix);

		// Rain of coins
		r_emitter->changeParticleNumber(NUM_COINS);
		r_emitter->emitter_pos = rain_emitter_pos;
		r_emitter->use_rotations = use_rotations;
		r_emitter->use_sorting = use_sorting;

		// Smoke from the tip of the genie lamp
		s_emitter->changeParticleNumber(NUM_PARTICLES);
		s_emitter->emitter_pos = smoke_emitter_pos;
		s_emitter->use_rotations = use_rotations;
		s_emitter->use_sorting = use_sorting;
		s_emitter->height_threshold = height_threshold;

		auto PV = projectionMatrix * viewMatrix;

		// COIN RAIN
		glUseProgram(coinRainShaderProgram);

		glUniformMatrix4fv(projectionAndViewMatrix, 1, GL_FALSE, &PV[0][0]);

		// Use particle based drawing
		if (coin_rain) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, coinColor);
			glUniform1i(coinDiffuceColorSampler, 0);

			if(!game_paused) {
				r_emitter->updateParticles(currentTime, dt, camera->position);
			}
			r_emitter->renderParticles(0);
		}

		// BLUE SMOKE
		glUseProgram(blueSmokeShaderProgram);

		glUniformMatrix4fv(projectionAndViewMatrix, 1, GL_FALSE, &PV[0][0]);

		if (blue_smoke) {
			counter += 0.01f;

			vec3 p0(0.0f, 0.0f, 0.0f);
			vec3 p1(0.0f, 2.0f, 0.0f);
			vec3 p2(5.0f, 2.0f, 0.0f);
			vec3 p3(5.0f, 5.0f, 0.0f);
			std::vector<glm::vec3> control_points = generateBezierCurve(10, p0, p1, p2, p3);

			// Update the djinn's position
			if (progress < 1.0f && counter < 5.0f)
			{
				progress += dt * counter;
				
				djinn_translation = bezier_pos(progress, control_points);
				thickness_factor = length(bezier_pos(progress, control_points)) / length(p3);
				djinnTransparency = computeTransparency(progress);
			}

			djinn_scaling = vec3(thickness_factor, thickness_factor, thickness_factor);

			// If the djinn pops, stop the trembling
			if (djinn_translation.x > 4.5f) {
				tremble_action = false;
			}

			djinnModelMatrix = scale(mat4(1), djinn_scaling);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, smokeTexture);
			glUniform1i(smokeDiffuceColorSampler, 0);

			if(!game_paused) {
				s_emitter->updateParticles(currentTime, dt, camera->position);
			}
			s_emitter->renderParticles(0);
		}

		t = currentTime;

		glfwPollEvents();
        glfwSwapBuffers(window);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 glfwWindowShouldClose(window) == 0);
}

void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        game_paused = !game_paused;
    }

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		tremble_action = true;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        blue_smoke = !blue_smoke;
		s_emitter = new SmokeEmitter(smoke, NUM_PARTICLES);
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        coin_rain = !coin_rain;
		cloudTransparency = 0.0f;
		start_cloud_transparency = true;
		r_emitter = new CoinRainEmitter(coin, NUM_COINS);
	}

	// // Release Button: It's setting the timer to 0.0f
	// if (key == GLFW_KEY_R && action == GLFW_PRESS) {
	// 	glfwSetTime(0.0f);
	// }

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera->active = true;
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->active = false;
        }

    }
}

void initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, TITLE, NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw runtime_error(string(string("Failed to open GLFW window.") +
            " If you have an Intel GPU, they are not 3.3 compatible." +
            "Try the 2.1 version.\n"));
    }
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw runtime_error("Failed to initialize GLEW\n");
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, W_WIDTH / 2, W_HEIGHT / 2);

    // Gray background color
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Keyboard Inputs
    glfwSetKeyCallback(window, pollKeyboard);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

	// enable textures
    glEnable(GL_TEXTURE_2D);

	// enable point size when drawing points
    glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Log
    logGLParameters();

    // Create camera
    camera = new Camera(window);

    // Creating a custom light 
	light = new Light(window,
		vec4{ 1, 1, 1, 1 },
		vec4{ 1, 1, 1, 1 },
		vec4{ 1, 1, 1, 1 },
		vec3{ 0, 10, 10 },
		150.0f
	);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
                                 camera->onMouseMove(xpos, ypos);
                             }
    );
}

int main(void)
{
    try
    {
        initialize();
        createContext();
        mainLoop();
        free();
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
        getchar();
        free();
        return -1;
    }

    return 0;
}
