#include "Objects.h"

#include <math.h>
#include <Core/Engine.h>



// mesa pentru dreptunghi
Mesh* Objects::CreateRectangle(std::string name, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, 0.2f, 0), color),
		VertexFormat(glm::vec3(1, 0.2f, 0), color),
		VertexFormat(glm::vec3(1, 0, 0), color),

	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(1);
	}
	rectangle->InitFromData(vertices, indices);
	return rectangle;
}




