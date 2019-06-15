#include "StaticMesh.h"
#include "tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

StaticMesh::StaticMesh()
    : m_uv(false), m_normal(false)
{

}

StaticMesh StaticMesh::LoadMesh(const std::string &filename)
{

    std::vector<tinyobj::shape_t> shapes;
	{
		std::vector<tinyobj::material_t> materials;
		std::string error_string;
		if (!tinyobj::LoadObj(shapes, materials, error_string, filename.c_str())) {
			// GG
		}

        /*
		if (shapes.size() == 0)
			GG

		if (shapes[0].mesh.texcoords.size() == 0 || shapes[0].mesh.normals.size() == 0)
			GG*/
	}

    StaticMesh ret;
    glGenVertexArrays(1, &ret.vao);
    glBindVertexArray(ret.vao);

    glGenBuffers(3, ret.vbo);
    glGenBuffers(1, &ret.ibo);
    // Upload postion array
    glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.positions.size(),
        shapes[0].mesh.positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/*///////////////////////////////
	std::vector <glm::vec3> pos;
	std::vector <glm::vec3> nor;
	for (int i = 0; i < shapes[0].mesh.positions.size(); i += 3) {
		pos.push_back({ shapes[0].mesh.positions[i], shapes[0].mesh.positions[i + 1] , shapes[0].mesh.positions[i + 2] });
		nor.push_back({ shapes[0].mesh.normals[i], shapes[0].mesh.normals[i + 1] , shapes[0].mesh.normals[i + 2] });
	}
	shapes[0].mesh.positions.clear();
	shapes[0].mesh.normals.clear();
	for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
		shapes[0].mesh.positions.push_back(nor[shapes[0].mesh.indices[i]].x);
		shapes[0].mesh.positions.push_back(nor[shapes[0].mesh.indices[i]].y);
		shapes[0].mesh.positions.push_back(nor[shapes[0].mesh.indices[i]].z);

		shapes[0].mesh.normals.push_back(nor[shapes[0].mesh.indices[i]].x);
		shapes[0].mesh.normals.push_back(nor[shapes[0].mesh.indices[i]].y);
		shapes[0].mesh.normals.push_back(nor[shapes[0].mesh.indices[i]].z);

		shapes[0].mesh.indices[i] = i;
	}
	///////////////////////////////*/
    
    if (shapes[0].mesh.texcoords.size() > 0) {

        // Upload texCoord array
        glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.texcoords.size(),
            shapes[0].mesh.texcoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		ret.m_uv = true;
    }

    if (shapes[0].mesh.normals.size() > 0) {
        // Upload normal array
        glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.normals.size(),
            shapes[0].mesh.normals.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		ret.m_normal = true;
    }

    // Setup index buffer for glDrawElements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * shapes[0].mesh.indices.size(),
        shapes[0].mesh.indices.data(), GL_STATIC_DRAW);

    ret.numIndices = shapes[0].mesh.indices.size();

    glBindVertexArray(0);
    return ret;
}

StaticMesh StaticMesh::LoadMesh2(const std::string &filename)
{

	std::vector<tinyobj::shape_t> shapes;
	{
		std::vector<tinyobj::material_t> materials;
		std::string error_string;
		if (!tinyobj::LoadObj(shapes, materials, error_string, filename.c_str())) {
			// GG
		}

		/*
		if (shapes.size() == 0)
			GG

		if (shapes[0].mesh.texcoords.size() == 0 || shapes[0].mesh.normals.size() == 0)
			GG*/
	}

	StaticMesh ret;
	glGenVertexArrays(1, &ret.vao);
	glBindVertexArray(ret.vao);

	glGenBuffers(3, ret.vbo);
	glGenBuffers(1, &ret.ibo);
	// Upload postion array
	glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.positions.size(),
		shapes[0].mesh.positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	std::vector<glm::vec3> pos;
	for (int i = 0; i < shapes[0].mesh.positions.size(); i += 3) {
		pos.push_back(glm::vec3(shapes[0].mesh.positions.at(i), shapes[0].mesh.positions.at(i + 1), shapes[0].mesh.positions.at(i + 2)));
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
		glm::vec3 normal = glm::normalize(glm::cross
		(pos.at(shapes[0].mesh.indices.at(i + 1)) - pos.at(shapes[0].mesh.indices.at(i))
			, pos.at(shapes[0].mesh.indices.at(i + 2)) - pos.at(shapes[0].mesh.indices.at(i)))
		);
		shapes[0].mesh.normals[shapes[0].mesh.indices[i] * 3] = normal.x;
		shapes[0].mesh.normals[shapes[0].mesh.indices[i] * 3 + 1] = normal.y;
		shapes[0].mesh.normals[shapes[0].mesh.indices[i] * 3 + 2] = normal.z;
	}

	if (shapes[0].mesh.texcoords.size() > 0) {

		// Upload texCoord array
		glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.texcoords.size(),
			shapes[0].mesh.texcoords.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		ret.m_uv = true;
	}

	if (shapes[0].mesh.normals.size() > 0) {
		// Upload normal array
		glBindBuffer(GL_ARRAY_BUFFER, ret.vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapes[0].mesh.normals.size(),
			shapes[0].mesh.normals.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		ret.m_normal = true;
	}

	// Setup index buffer for glDrawElements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * shapes[0].mesh.indices.size(),
		shapes[0].mesh.indices.data(), GL_STATIC_DRAW);

	ret.numIndices = shapes[0].mesh.indices.size();

	glBindVertexArray(0);
	return ret;
}

void StaticMesh::release()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, vbo);
    glDeleteBuffers(1, &ibo);

}

void StaticMesh::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
}

bool StaticMesh::hasNormal() const
{
	return m_normal;
}

bool StaticMesh::hasUV() const 
{
	return m_uv;
}
