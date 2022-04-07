#include "PCHeader.h"
#include "SpaceUtil.h"
#include "glad/glad.h"
#include "stb_image.h"
#include "OpenGLWrapper.h"

namespace Space {
	Space::OpenGLWrapper::OpenGLWrapper(const std::string& file)
	{
		float vertices[] = {
			-0.5f, -0.5f,0.0f, 0.0f, //each line represent a coordinate in the window
			-0.5f, 0.5f,0.0f, 1.0f,
			0.5f, 0.5f,1.0f, 1.0f,
			0.5f, -0.5f, 1.0f, 0.0f
		};

		unsigned indices[] = {
			0, 1, 2,//specify which vertex to use in order to construct triangles
			0, 2, 3
		};

		
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);//bind this array, activate it then we bind VBO and its attribute later

		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//to read attribute of the vertex such as coordinates, color, etc...
		//since we only have coordinates, we will have one of such function
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4* sizeof(GL_FLOAT), (void*)0);
		//this function tell opengl how to extract coordinate in pointer 0
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)8);
		glEnableVertexAttribArray(1);


		///Texture///
		glGenTextures(1, &mTex);
		glBindTexture(GL_TEXTURE_2D, mTex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

		stbi_set_flip_vertically_on_load(true);

		int numChannels;
		unsigned char* data = stbi_load(file.c_str(), &mwidth, &mheight, &numChannels, 0);

		if (data == NULL)
		{
			GAME_LOG("Error: texture didn't load");
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mwidth, mheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}


	int Space::OpenGLWrapper::GetWidth() const
	{
		return 0;
	}

}