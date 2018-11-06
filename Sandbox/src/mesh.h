#ifndef MESH_H
#define MESH_H
#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{

public:
	Vertex(const glm::vec3& pos,const glm::vec2& textCoord)
	{
		this->pos = pos;
		this->texCoord = textCoord;
	}
	inline glm::vec3* GetPos(){	return &pos;}
	inline glm::vec2* GetTextCoord(){return &texCoord;}
	
private:
		glm::vec3 pos;
		glm::vec2 texCoord;

};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);

	

	void Draw();

	virtual ~Mesh();
	   	
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	enum
	{
		POSITION_VB,
		TEXTCOORD_VB,
		NUM_BUFFERS
	};


	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

};



#endif 
