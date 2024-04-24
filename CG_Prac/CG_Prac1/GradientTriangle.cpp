#include "GradientTriangle.h";
int gradientTriangleMain(int argc, char* argv[])
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

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
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
	float colors[] = {
  0.5f, 0.0f,  0.5f,
  0.0f, 0.0f,  0.0f,
  1.0f, 0.0f,  0.0f
	};
	/////////////////////////////////////////////////////////
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	GLuint points_vbo = vbo[0];
	GLuint colours_vbo = vbo[1];

	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);
	////////////////////////////////////////////////////////////////////////////////
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	//////////////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	/////////////////////////////////////////////////////////////////////////////////////////////

	const char* vertex_shader =
		"#version 400\n"

		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_colour;"

		"out vec3 color;"

		"void main() {"
		"color = vertex_colour;"
		"gl_Position = vec4(vertex_position, 1.0); "

		"}";
	const char* fragment_shader =
		"#version 400\n"
		"in vec3 color;"
		"layout(location = 0) out vec4 fragcolor;"
		"void main() {"
		"  fragcolor = vec4(color, 1.0);"
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

	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");


	glLinkProgram(shader_programme);
	while (!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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