#pragma once
#include "vector"
#include <string>
#include <glm/glm.hpp>

class Face
{
public:
	Face(std::istream& issLine);
	int GetVertexIndex(int index) const;
	int GetNormalIndex(int index) const;
	int GetTextureIndex(int index) const;
	int GetNumberOfVertexIndexes() const;
	void setFaceNormal(const glm::fvec3 normal);
	const glm::fvec3 getFaceNormal() const;

private:
	glm::fvec3 normal;
	std::vector<int> vertex_indices_;
	std::vector<int> normal_indices_;
	std::vector<int> texture_indices_;
};