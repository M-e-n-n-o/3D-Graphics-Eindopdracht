#pragma once

#include <GL/glew.h>

namespace models
{
	/*
		Structure for storing a vboID and vertexCount.

		This structure represents a Bare bones Model (A mesh without a texture).
		The vaoID, points to an ID stored by openGL and the
		vertexCount is how many triangles in the mesh there are.
	*/
	struct RawModel
	{
		GLuint vaoID;
		int vertexCount;
	};

	/*
		Structure for storing a texture (textureID) to apply to a RawModel.

		Shinedamper = The amount of shine the model gives from the angle of looking to the model
		reflectivity = The amount the model reflects light
		emissionFactor = The amount the model itself shines (does not affect other entities in the game)
	*/
	struct ModelTexture
	{
		GLuint textureID;
		float shineDamper = 1;
		float reflectivity = 0;
		float emissionFactor = 0;
	};
	
	/*
		Structure for storing a RawModel and a Texure.

		This struct represents a model with a texture.
	*/
	struct TexturedModel
	{
		RawModel rawModel;
		ModelTexture texture;
	};
}