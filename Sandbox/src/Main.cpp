#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"



const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 720;
const unsigned int FOV = 80;

int wmain()
{
	Display display((int)SCR_WIDTH, (int)SCR_HEIGHT, "Sandbox");

	
	Vertex vertices[] = { Vertex(glm::vec3( 0.0,-0.5, 0.0),glm::vec2(0.0,0.0)),
						  Vertex(glm::vec3( 0.5,-0.5, 0.0),glm::vec2(0.5,1.0)),
						  Vertex(glm::vec3( 0.5, 0.5, 0.0),glm::vec2(1.0,0.0)),
						  Vertex(glm::vec3(-0.5,-0.5, 0.0),glm::vec2(0.0,0.0)),
						  Vertex(glm::vec3( 0.0, -0.5, 0.0),glm::vec2(0.5,1.0)),
						  Vertex(glm::vec3(-0.5, 0.5, 0.0),glm::vec2(1.0,0.0))
	};
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	Shader shader("res/shaders/basicShader");
	Texture texture("res/textures/testPicture.jpg");

	Camera camera(glm::vec3(0, 0, -2), (float)FOV, (float)SCR_WIDTH /(float)SCR_HEIGHT, 0.1f, 1000.0f );

	Transform transform;
	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.5, 0.0f, 0.5f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);		

		/*transform.GetPos().x = sinCounter;
		transform.GetRot().z = counter * 5;
		transform.SetRot(glm::vec3(cosCounter, cosCounter, cosCounter));*/


		shader.Bind();		
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh.Draw();

		display.Update(camera);


		counter += 0.01f;



		if (display.IsClosed()==true)
		{
			display.~Display();
			return 0;

		}
	}
	
	
	return 0;
}
