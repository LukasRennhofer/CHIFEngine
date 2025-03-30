
/*
 *    				~ CHIFEngine ~
 *               
 * Copyright (c) 2025 Lukas Rennhofer
 *
 * Licensed under the MIT License. See LICENSE file for more details.
 *
 * Author: Lukas Rennhofer
 * Date: 2025-03-08
 *
 * File: chifWater.h
 * Last Change: 
 */
 

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
//#include <model.h>
#include "Renderer/chifShader.h"
#include "Renderer/chifBuffers.h"
#include "../Platform/chifWindow.h"
#include "chifDrawableObject.h"
#include "../Utils/sdl2Utils.h"

namespace chif::Graphics {
	class Water : public drawableObject
	{
	public:
		Water(glm::vec2 position, float scale, float height);
		virtual ~Water();
		virtual void draw();
		virtual void setGui();
		void bindRefractionFBO();
		void bindReflectionFBO();
		void unbindFBO();

		void setPosition(glm::vec2 position, float scale, float height) {
			glm::mat4 identity;
			glm::mat4 scaleMatrix = glm::scale(identity, glm::vec3(scale, scale, scale));
			glm::mat4 transMatrix = glm::translate(identity, glm::vec3(position.x, height, position.y));
			this->modelMatrix = transMatrix * scaleMatrix;
		}

		void setHeight(float height) {
			float scale = modelMatrix[0][0];
			float position_x = modelMatrix[3][0];
			float position_z = modelMatrix[3][2];

			glm::mat4 identity;
			glm::mat4 scaleMatrix = glm::scale(identity, glm::vec3(scale, scale, scale));
			glm::mat4 transMatrix = glm::translate(identity, glm::vec3(position_x, height, position_z));
			this->modelMatrix = transMatrix * scaleMatrix;
		}

		float getHeight() {
			return height;
		}

		glm::mat4 getModelMatrix() {
			return modelMatrix;
		}

		static const int FBOw = 1280;
		static const int FBOh = 720;

		chif::Graphics::Renderer::Buffer::FrameBufferObject const& getReflectionFBO() {
			return *reflectionFBO;
		}

	private:
		void drawVertices();

		unsigned int planeVAO, planeVBO, planeEBO;
		float scale, height;
		chif::Graphics::Renderer::Buffer::FrameBufferObject * reflectionFBO;
		chif::Graphics::Renderer::Buffer::FrameBufferObject * refractionFBO;

		unsigned int dudvMap, normalMap;
		glm::mat4 modelMatrix;
		chif::Graphics::Renderer::Shader::Shader * shad;
		//Model * waterPlane;
	};
} // NAMESPACE chif::Graphics