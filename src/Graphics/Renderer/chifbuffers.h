
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
 * File: chifBuffers.h
 * Last Change: 
 */
 

#pragma once

#include <glad/glad.h>
#include "../../Platform/chifWindow.h"

namespace chif::Graphics::Renderer::Buffer {
	void bindFrameBuffer(int frameBuffer, int width, int height);

	void unbindCurrentFrameBuffer(int scrWidth, int scrHeight);
	void unbindCurrentFrameBuffer();

	unsigned int createFrameBuffer();

	unsigned int createTextureAttachment(int width, int height);

	unsigned int * createColorAttachments(int width, int height, unsigned int nColorAttachments);

	unsigned int createDepthTextureAttachment(int width, int height);

	unsigned int createDepthBufferAttachment(int width, int height);

	unsigned int createRenderBufferAttachment(int width, int height);

	class FrameBufferObject {
		public:
			FrameBufferObject(int W, int H);
			FrameBufferObject(int W, int H, int numColorAttachments);
			unsigned int FBO, renderBuffer, depthTex;
			unsigned int tex;
			unsigned int getColorAttachmentTex(int i);
			void bind();
		private:
			int W, H;
			int nColorAttachments;
			unsigned int * colorAttachments;
	};

	class TextureSet { //for drawing compute shader
		public:
			TextureSet(int W, int H, int num);
			void bindTexture(int i, int unit);
			unsigned int getColorAttachmentTex(int i);
			int getNTextures() const {
				return nTextures;
			}

			void bind();
			
		private:
			int nTextures;
			unsigned int * texture;
	};
} // NAMESPACE chif::Graphics::Renderer::Buffer