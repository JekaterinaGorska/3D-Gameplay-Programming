//Jekaterina Gorska
#include <./include/Debug.h>	 
#include <./include/Cube.h>		 
#include <./include/Game.h>		
#include <./include/stb_image.h> 

#define STB_IMAGE_IMPLEMENTATION 
#include <./include/stb_image.h> 

template <typename T>
string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint vsid, 
	fsid,	 
	progID,	 
	vbo,	
	vib,	 
	to[1];	 

GLint positionID, 
	colorID,	  
	textureID,	  
	uvID,		  
	mvpID;		 

GLenum error; 

// Filename for texture
const string filename = "./assets/textures/grid.tga";
// Please see ../assets/textures/ for more textures
// const string filename = "./assets/textures/coordinates.tga";
 //const string filename1 = "./assets/textures/cube.tga";
// const string filename = "./assets/textures/grid_wip.tga";
// const string filename = "./assets/textures/minecraft.tga";
// const string filename = "./assets/textures/texture.tga";
// const string filename = "./assets/textures/texture_2.tga";
// const string filename = "../assets/textures/uvtemplate.tga";

int width;						 
int height;						 
int comp_count;					 
const int colour_components = 4; 

unsigned char *img_data;

mat4 projection, view;

Font font; 

float x_offset, y_offset, z_offset; 

Game::Game(sf::ContextSettings settings) : window(VideoMode(800, 600),
												  "Project I StarterKit 3D Game Scene",
												  sf::Style::Default,
												  settings)
{
	DEBUG_MSG("\nGame::Game() Constructor\n");
}

Game::~Game()
{
	DEBUG_MSG("\nGame::~Game() Destructor\n");

}

void Game::initialise()
{

	DEBUG_MSG("\n******** Initialisation Procedure STARTS ********\n");

	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!(!glewInit()))
	{
		DEBUG_MSG("ERROR: GLEW INIT");
		DEBUG_MSG(glewGetErrorString(glewInit()));
		throw runtime_error("\nGLEW Init Failed\n");
	}

	DEBUG_MSG("\n******** Init GameObjects STARTS ********\n");

	for (int i = 0; i < 500;i++)
	{
		npcs.push_back(new NPC(TYPE::RED, i * 5));
		npcs.push_back(new NPC(TYPE::GREEN, i * 5));
		npcs.push_back(new NPC(TYPE::BLUE, i * 5));
	}

	player = new Player(TYPE::RED);
	player->setPosition(vec3(0.0f, 0.0f, 4.0f));


	for (auto& cube : npcs)
	{
		cube->setModelMatrix(translate(glm::mat4(1.0f), cube->getPosition()));
		std::cout << std::to_string(cube->getPosition().x) << " " << std::to_string(cube->getPosition().y) << " " << std::to_string(cube->getPosition().z) << std::endl;
	}

	DEBUG_MSG("\n******** Init GameObjects ENDS ********\n");


	for (int i = 1; i < 6; i++)
	{
	
		int uv_start_position = i * 4 * 2; 
		memcpy(&uvs[uv_start_position], &uvs[0], 2 * 4 * sizeof(GLfloat)); 
	}

	// Output GPU information to the debug console
	DEBUG_MSG("\n******** GPU information STARTS ********\n");
	// Retrieve and output GPU vendor information
	DEBUG_MSG(glGetString(GL_VENDOR));
	// Retrieve and output GPU renderer information
	DEBUG_MSG(glGetString(GL_RENDERER));
	// Retrieve and output GPU version information
	DEBUG_MSG(glGetString(GL_VERSION));
	// Retrieve and output GPU shading language version information
	DEBUG_MSG(glGetString(GL_SHADING_LANGUAGE_VERSION));
	DEBUG_MSG("\n******** GPU information ENDS ********\n");

	// Vertex Buffer Object
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	DEBUG_MSG("\n******** Model information STARTS ********\n");
	
	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	int countVERTICES = player->getVertexCount();
	int countCOLORS = player->getColorCount();
	int countUVS = player->getUVCount();
	DEBUG_MSG("\n******** Model information ENDS ********\n");

	// Vertices (3) x,y,z , Colours (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLOURS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); // Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Count of Indices
	int countINDICES = player->getIndexCount();

	DEBUG_MSG("\nVertices : " + to_string(countVERTICES));
	DEBUG_MSG("Colors : " + to_string(countCOLORS));
	DEBUG_MSG("UVs : " + to_string(countUVS));
	DEBUG_MSG("Indexes : " + to_string(countINDICES));

	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Define and compile Vertex Shader
	const char *vs_src =
		"#version 130\n\n"
		"\n"
		"in vec3 sv_position;\n"
		"in vec4 sv_colour;\n"
		"in vec2 sv_uv;\n\n"
		"\n"
		"out vec4 colour;\n"
		"out vec2 uv;\n\n"
		"\n"
		"uniform mat4 sv_mvp;\n"
		"\n"
		"void main() {\n"
		"	colour = sv_colour;\n"
		"	uv = sv_uv;\n"
		//"	gl_Position = vec4(sv_position, 1);\n"
		"	gl_Position = sv_mvp * vec4(sv_position, 1 );\n"
		"}\n"; // Vertex Shader Src


	DEBUG_MSG("\n******** Vertex Shader src STARTS ********\n");
	DEBUG_MSG(string(vs_src));
	DEBUG_MSG("\n******** Vertex Shader src ENDS ********\n");

	DEBUG_MSG("Setting Up Vertex Shader");

	// Compile Vertex Shader
	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar **)&vs_src, NULL);
	glCompileShader(vsid);

	// Check if Vertex Shader is Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE)
	{
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		GLint logLength = 0;
		glGetShaderiv(vsid, GL_INFO_LOG_LENGTH, &logLength);
		char *errorLog = new char[logLength];
		glGetShaderInfoLog(vsid, logLength, &logLength, &errorLog[0]);
		DEBUG_MSG("\n******** Vertex Shader ErrorLog STARTS ********\n");
		DEBUG_MSG(string(errorLog));
		DEBUG_MSG("\n******** Vertex Shader ErrorLog ENDS ********\n");
		throw runtime_error("\nERROR: Vertex Shader Compilation Error\n");
	}

	// Define and compile Fragment Shader
		const char *fs_src =
		"#version 130\n\n"
		"\n"
		"uniform sampler2D f_texture;\n"
		"\n"
		"in vec4 colour;\n"
		"in vec2 uv;\n"
		"\n"
		"out vec4 fColor;\n"
		"\n"
		"void main() {\n"
		"	vec4 lightColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"	fColor = lightColor * (colour + texture2D(f_texture, uv));\n"
		"\n"
		"}\n"; // Fragment Shader Src

	DEBUG_MSG("\n******** Fragment Shader src STARTS ********\n");
	DEBUG_MSG(string(fs_src));
	DEBUG_MSG("\n******** Fragment Shader src ENDS ********\n");

	DEBUG_MSG("Setting Up Fragment Shader");

	// Compile Fragment Shader
	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar **)&fs_src, NULL);
	glCompileShader(fsid);

	// Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE)
	{
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		GLint logLength = 0;
		glGetShaderiv(fsid, GL_INFO_LOG_LENGTH, &logLength);
		char *errorLog = new char[logLength];
		glGetShaderInfoLog(fsid, logLength, &logLength, &errorLog[0]);
		DEBUG_MSG("\n******** Vertex Shader ErrorLog STARTS ********\n");
		DEBUG_MSG(string(errorLog));
		DEBUG_MSG("\n******** Vertex Shader ErrorLog ENDS ********\n");
		throw runtime_error("\nERROR: Fragment Shader Compilation Error\n");
	}

	// Create and link shader program
	DEBUG_MSG("\n******** Shader Linking STARTS ********\n");
	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	// Check if Shader Program is linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1)
	{
		DEBUG_MSG("Vertex and Fragment Shader Linked");
	}
	else
	{
		throw runtime_error("\nERROR: Vertex and Fragment Shader Link Error\n");
	}
	DEBUG_MSG("\n******** Shader Linking ENDS ********\n");
	// Use Shader Program on GPU
	glUseProgram(progID);

	// Set image data
	// https://github.com/nothings/stb/blob/master/stb_image.h
	// Load texture image data
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, colour_components);

	if (img_data == NULL)
	{
		throw runtime_error("\nERROR: Texture not loaded " + filename + "\n");
	}

	// Enable 2D texturing
	DEBUG_MSG("\n******** Enabling Textures STARTS ********\n");
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Texture wrapping
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Texture filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Transfer texture image data to GPU
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,	  // 2D Texture Image
		0,				  // Mipmapping Level
		GL_RGBA,		  // GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA
		width,			  // Width
		height,			  // Height
		0,				  // Border
		GL_RGBA,		  // Bitmap
		GL_UNSIGNED_BYTE, // Specifies Data type of image data
		img_data		  // Image Data
	);

	DEBUG_MSG("\n******** Enabling Textures ENDS ********\n");

	// Set up Projection Matrix
	DEBUG_MSG("\n******** MVP STARTS ********\n");
	projection = perspective(
		45.0f,		 // Field of View 45 degrees
		4.0f / 3.0f, // Aspect ratio: 4:3
		0.1f,		 // Display Range Min : 0.1f unit
		100.0f		 // Display Range Max : 100.0f unit
	);

	// Set up Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f), 
		vec3(0.0f, 0.0f, 0.0f),	
		vec3(0.0f, 1.0f, 0.0f)	 
	);

	DEBUG_MSG("\n******** MVP ENDS ********\n");
	DEBUG_MSG("\n******** CULLING ENABLE STARTS ********\n");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	DEBUG_MSG("\n******** CULLING ENABLE ENDS ********\n");

	DEBUG_MSG("\n******** OpenGL Error Check STARTS ********\n");
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		throw runtime_error("ERROR: OpenGL Error : " + to_string(error));
	}
	DEBUG_MSG("\n******** OpenGL Error Check ENDS ********\n");

	font.loadFromFile("./assets/fonts/BBrick.ttf");

	DEBUG_MSG("\n******** Initialisation Procedure ENDS ********\n");
}


void Game::update()
{


#if (DEBUG >= 2)
	DEBUG_MSG("Updating... MVP");
#endif

	if (player->isAlive())
	{

		player->update(deltaTime.asSeconds());
		for (auto& cube : npcs)
		{
			if (cube->renderable())
			{

				cube->update(deltaTime.asSeconds());
				cube->setMVPMatrix(projection * view * cube->getModelMatrix());

				if (player->checkCollision(cube))
				{
					cout << "Colliding" << endl;
					reinitialise();
				}
			}
		}
	}


#if (DEBUG >= 2)
	DEBUG_MSG("MVP : " + glm::to_string(mvp));
#endif

#if (DEBUG >= 2)
	DEBUG_MSG("Finished Updating... MVP");
#endif
}

void Game::run()
{

	initialise();
	Event event;
	Clock clock;
	
	int frameCount = 0;
	float fpsUpdateTime = 0.0f;
	
	// Main game loop
	while (isRunning)
	{
		deltaTime = clock.restart();
		frameCount++;
		fpsUpdateTime += deltaTime.asSeconds();
		if (fpsUpdateTime >= 1.0f)
		{
			
			float fps = static_cast<float>(frameCount) / fpsUpdateTime;
			std::cout << "FPS: " << fps << std::endl;
			frameCount = 0;
			fpsUpdateTime = 0.0f;
		}
	
#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

	
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		
		}
		
		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();
}


void Game::unload()
{
#if (DEBUG >= 2)
	// Output a debug message indicating that cleanup process has started
	DEBUG_MSG("Cleaning up...STARTS");
#endif

	// Detach the vertex shader from the shader program
	// Shader could be used with more than one progID
	glDetachShader(progID, vsid);

	// Detach the fragment shader from the shader program
	glDetachShader(progID, fsid);

	// Delete the vertex shader
	glDeleteShader(vsid);

	// Delete the fragment shader
	glDeleteShader(fsid);

	// Delete the shader program
	glDeleteProgram(progID);

	// Delete the vertex buffer object
	glDeleteBuffers(1, &vbo);

	// Delete the vertex index buffer object
	glDeleteBuffers(1, &vib);

	// Free the image data
	stbi_image_free(img_data);

#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...ENDS");
#endif
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	window.pushGLStates();
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;

	string hud = "Heads Up Display [" + string(toString(x)) + "][" + string(toString(y)) + "]";

	Text text(hud, font);

	text.setFillColor(sf::Color(255, 255, 255, 170));
	text.setPosition(50.f, 20.f);

	window.draw(text);

	// Restore OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

	window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Find variables within the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID == -1)
	{
		throw runtime_error("\nERROR: positionID not found\n");
	}

	colorID = glGetAttribLocation(progID, "sv_colour");
	if (colorID == -1)
	{
		throw runtime_error("\nERROR: colorID not found\n");
	}

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID == -1)
	{
		throw runtime_error("\nERROR: uvID not found\n");
	}

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID == -1)
	{
		throw runtime_error("\nERROR: textureID not found\n");
	}

	mvpID = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0)
	{
		throw runtime_error("\nERROR: mvpID not found\n");
	}

	// VBO Data....vertices, colours and UV's appended
	// Add the Vertices for all your GameOjects, Colors and UVS

	for (auto& npc : npcs)
	{
		if (npc->renderable())
		{
			renderObject(npc);
		}
	}
	renderObject(player);
	window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers with 0 (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader Program to Use
	glUseProgram(0);

	// Check for OpenGL Error code
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		DEBUG_MSG(error);
	}
}


void Game::renderObject(GameObject* obj)
{

	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), obj->getVertex());
	switch (obj->getType())
	{
	case TYPE::RED:
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLOURS * sizeof(GLfloat), red);
		break;
	case TYPE::BLUE:
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLOURS * sizeof(GLfloat), blue);
		break;
	case TYPE::GREEN:
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLOURS * sizeof(GLfloat), green);
		break;
	default:
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLOURS * sizeof(GLfloat), colours);
		break;
	}

	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLOURS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Set the model-view-projection matrix
	obj->setMVPMatrix(projection * view * obj->getModelMatrix());

	// Send transformation to shader mvp uniform [0][0] is start of array
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &obj->getMVPMatrix()[0][0]);

	// Set Active Texture .... 32 GL_TEXTURE0 .... GL_TEXTURE31
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0); // 0 .... 31

	// Set pointers for each parameter (with appropriate starting positions)
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (void*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (void*)(((3 * VERTICES) + (4 * COLOURS)) * sizeof(GLfloat)));

	// Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	// Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
}

void Game::reinitialise()
{
	player->setPosition(vec3(0.0f, 0.0f, 4.0f));


	for (auto& cube : npcs)
	{
		cube->setOriginalPosition();
		cube->setRenderable(true);
		cube->setModelMatrix(translate(glm::mat4(1.0f), cube->getPosition()));
		std::cout << std::to_string(cube->getPosition().x) << " " << std::to_string(cube->getPosition().y) << " " << std::to_string(cube->getPosition().z) << std::endl;
	}

}

void Game::restart()
{
	reinitialise();
}

