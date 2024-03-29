# include "object.hpp"

void check_color(vec3 & color)
{
	color = max(color, vec3(0.0, 0.0, 0.0));
	color = min(color, vec3(1.0, 1.0, 1.0));
}

void Object::update_transformation(mat4 m)
{
	vec4 v_out, n_out;
	vertices_transformed.clear();
	for(unsigned int i=0; i<vertices.size(); i++)
	{
		v_out = m * vertices[i];
		vertices_transformed.push_back(v_out);
	}
	for(unsigned int i=0; i<faces.size(); i++)
	{
		faces[i].normal_transformed = m * faces[i].normal;
	}
	normals_transformed.clear();
	for(unsigned int i=0; i<normals.size(); i++)
	{
		n_out = m * normals[i];
		normals_transformed.push_back(n_out);
	}
}

void Object::update_projection(mat4x3 m)
{
	vec3 v_out;
	vertices_projected.clear();
	for(unsigned int i=0; i<vertices_transformed.size(); i++)
	{
		v_out = m * vertices_transformed[i];
		vertices_projected.push_back(vec2(v_out/v_out.z));
	}
}

void Object::draw(Window & window, vec4 light)
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		switch(draw_method)
		{
			case DRAW_WIRE :
				{
					for(unsigned int v=0; v<4; v++)
					{
						vec2 p1 = vertices_projected[faces[i].vertex_index[v]];
						vec2 p2 = vertices_projected[faces[i].vertex_index[(v+1)%4]];
						window.draw_line(p1, p2, faces[i].color);
					}
				}
				break;
			case DRAW_FILL :
				{
					if (faces[i].visible) {
						vec2 v[4];
						for (int n = 0; n < 4; n++) {
							v[n] = vertices_projected[faces[i].vertex_index[n]];
						}
						window.draw_quad(v, faces[i].color);
					}
				}
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
	for (int i = 0; i < faces.size(); i++) {
		if (dot(faces[i].normal_transformed, vertices_transformed[faces[i].vertex_index[0]]) < 0)
			faces[i].visible = true;
		else
			faces[i].visible = false;
	}
}
