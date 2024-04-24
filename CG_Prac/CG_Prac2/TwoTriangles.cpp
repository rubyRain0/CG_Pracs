#include "TwoTriangles.h";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

int mainTwoTriangles(int argc, char* argv[])
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


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmenShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmenShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgramOrange = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmenShaderOrange, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmenShaderOrange);
	glShaderSource(fragmenShaderYellow, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmenShaderYellow);

	// Связываем первый программный объект
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmenShaderOrange);
	glLinkProgram(shaderProgramOrange);

	// Связываем второй программный объект, используя другой фрагментный шейдер
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmenShaderYellow);
	glLinkProgram(shaderProgramYellow);


	float firstTriangle[] = {
-0.9f, -0.5f,  0.0f,
-0.0f, -0.5f,  0.0f,
-0.45f, 0.5f,  0.0f
	};
	float secondTriangle[] = {
0.0f, -0.5f,  0.0f,
0.9f, -0.5f,  0.0f,
0.45f, 0.5f,  0.0f
	};
	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	//Настройка первого треугольника
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Настройка второго треугольника
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Теперь, когда мы рисуем треуголник, нам сначала нужно использовать вершину и оранжевый фрагментный шейдер
		glUseProgram(shaderProgramOrange);
		//Рисуем первыый треугольник, используя данный из нашего первого VAO
		glBindVertexArray(VAOs[0]);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling 
		glfwSwapBuffers(window);
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
	}

	// Опционально: освобождаем все ресурсы, как только они выполнили своё предназначение
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	// glfw: завершение, освобождение всех ранее задействованных GLFW ресурсов
	glfwTerminate();

	return 0;
}
