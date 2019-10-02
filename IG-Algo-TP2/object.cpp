# include "object.hpp"
# include <iostream>

void check_color(vec3 & color)
{
	color = max(color, vec3(0.0, 0.0, 0.0));
	color = min(color, vec3(1.0, 1.0, 1.0));
}

void Object::update_transformation(mat4 m)
{
	vertices_transformed.clear();
	for (int i = 0; i < vertices.size(); i++) {
		vertices_transformed.push_back(m*vertices[i]);
	}
	for(int i=0; i< normals.size(); i++){
		normals_transformed.push_back(m*normals[i]);
	}
}

void Object::update_projection(mat4 m)
{
	vertices_projected.clear();
	for (int i = 0; i < vertices_transformed.size(); i++) {
		vec4 v = m*vertices_transformed[i];
		vertices_projected.push_back(vec2(v.x, v.y));
	}
}

void Object::draw(Window & window, vec4 light)
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		switch(draw_method)
		{
			case DRAW_WIRE :
				for (int j = 0; j < faces[i].vertex_index.size()-1; j++) {
					window.draw_line(vertices_projected[faces[i].vertex_index[j]], vertices_projected[faces[i].vertex_index[j+1]], faces[i].color);
				}
				window.draw_line(vertices_projected[faces[i].vertex_index[0]], vertices_projected[faces[i].vertex_index[faces[i].vertex_index.size()-1]], faces[i].color);
				break;
			case DRAW_FILL :
				// TODO => TP03 //
				break;
			case DRAW_LAMBERT :
				// TODO => TP04 //
				break;
			case DRAW_GOURAUD :
				// TODO => TP04 //
				break;
			default :
				break;
		}
	}
}

void Object::backface_culling(mat4 trans_matrix)
{
	// TODO => TP03 //
}
