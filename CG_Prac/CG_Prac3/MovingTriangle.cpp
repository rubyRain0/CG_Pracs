#include "MovingTriangle.h"

using glm::mat4;
using glm::vec3;
using glm::rotate;
using glm::perspective;

int movingTriangleMain(int argc, char* argv[])
{
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// uncomment these lines if on Apple OS X
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */

	// close GL context and any other GLFW resources
	//glfwTerminate();
	float points[] = {
0.0f,  0.5f,  0.0f,
0.5f, -0.5f,  0.0f,
-0.5f, -0.5f,  0.0f
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"uniform mat4 MVP;"
		"void main() {"
		"  gl_Position = MVP*vec4(vp, 1.0);"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	while (!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//static rotate
		/*glm::mat4 model = glm::rotate(model, 30.0f, vec3(0.0f, 0.0f, 1.0f));
		GLuint location = glGetUniformLocation(shader_programme, "model");
		if (location >= 0) {
			glUniformMatrix4fv(location, 1, GL_FALSE, &model[0][0]);
		}*/

		glm::mat4 myMatrix;
		glm::vec4 myVector;
		//умн матр на вектор
		glm::vec4 transformedVector = myMatrix * myVector;

		glm::mat4 Projection = perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);


		//camera matr
		glm::mat4 View = glm::lookAt(
			glm::vec3(1, 1, 1),//camera is at
			glm::vec3(0, 0, 0),//loks at
			glm::vec3(0, 1, 0)//head is up
		);
		glm::mat4 Model(1.0f);
		//dynamic rotate
		Model = glm::translate(Model, glm::vec3(0.3f, -0.3f, 0.0f));
		Model = glm::rotate(Model, float(glfwGetTime()), vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 mvp = Projection * View * Model;
		

		GLuint location = glGetUniformLocation(shader_programme, "MVP");
		if (location >= 0) {
			glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
		}

		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glEnable(GL_DEPTH_TEST);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	return 0;
}
