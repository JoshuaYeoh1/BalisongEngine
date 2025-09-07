#include "Mesh.h"
using namespace BalisongEngine;
using namespace BalisongEngineRenderer;

#include <glad/glad.h>

#include <iostream>
using namespace std;

// ====================================================================

Mesh::Mesh(vector<Vertex> vertices)
{
	// Assign the size of vInput to vertexCount
	vertexCount = (int)vertices.size();

	// Generate VBO, and upload data to the VBO
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//cout << "Generated buffer ID: " << id << endl;
}

Mesh::~Mesh()
{
	// Delete the VBO on mesh destruction.
	glDeleteBuffers(1, &id);
}

// ====================================================================

void Mesh::UpdateVertices(std::vector<Vertex> vertices)
{
	vertexCount = (int)vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(Vertex), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ====================================================================

unsigned int Mesh::GetID()
{
	return id;
}
int Mesh::GetVertexCount()
{
	return vertexCount;
}