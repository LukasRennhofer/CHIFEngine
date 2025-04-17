
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
 * File: chifScreenSpaceShader.h
 * Last Change: 
 */
 

#pragma once
#include "chifShader.h"
#include <glad/glad.h>
#include "../chifDrawableObject.h"

namespace chif::Graphics::Renderer::Shader {
	class ScreenSpaceShader : drawableObject
	{
	public:
		ScreenSpaceShader(const char * fragmentPath);
		~ScreenSpaceShader();

		Shader * const getShaderPtr() {
			return shad;
		}

		Shader &getShader()
		{
			return *shad;
		}

		virtual void draw();
		static void drawQuad();

		static void disableTests() {
			//glDisable(GL_CLIP_DISTANCE0);
			glDisable(GL_DEPTH_TEST);
		}

		static void enableTests() {
			glEnable(GL_DEPTH_TEST);
		}

	private:
		Shader * shad;
		static unsigned int quadVAO, quadVBO;
		static bool initialized;

		void initializeQuad();
	};
} // NAMESPACE chif::Graphics::Renderer::Shader