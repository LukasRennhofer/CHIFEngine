/*
 *  ╔═══════════════════════════════════════════════════════════════╗
 *  ║                          ~ Vantor ~                           ║
 *  ║                                                               ║
 *  ║  This file is part of the Vantor Engine.                      ║
 *  ║  Automatically formatted by vantorFormat.py                   ║
 *  ║                                                               ║
 *  ╚═══════════════════════════════════════════════════════════════╝
 *
 *  Copyright (c) 2025 Lukas Rennhofer
 *  Licensed under the GNU General Public License, Version 3.
 *  See LICENSE file for more details.
 *
 *  Author: Lukas Rennhofer
 *  Date: 2025-05-12
 *
 *  File: vantorOpenGLRenderTarget.cpp
 *  Last Change: Automatically updated
 */

#include "vantorOpenGLRenderTarget.hpp"
#include "vantorOpenGLRenderer.hpp"

#include "../../../Core/Backlog/vantorBacklog.h"

namespace vantor::Graphics::RenderDevice::OpenGL
{
    // --------------------------------------------------------------------------------------------
    RenderTarget::RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int nrColorAttachments, bool depthAndStencil)
    {
        Width  = width;
        Height = height;
        Type   = type;

        glGenFramebuffers(1, &ID);
        glBindFramebuffer(GL_FRAMEBUFFER, ID);
        // generate all requested color attachments
        for (unsigned int i = 0; i < nrColorAttachments; ++i)
        {
            Texture texture;
            texture.FilterMin  = GL_LINEAR;
            texture.FilterMax  = GL_LINEAR;
            texture.WrapS      = GL_CLAMP_TO_EDGE;
            texture.WrapT      = GL_CLAMP_TO_EDGE;
            texture.Mipmapping = false;

            GLenum internalFormat = GL_RGBA;
            if (type == GL_HALF_FLOAT)
                internalFormat = GL_RGBA16F;
            else if (type == GL_FLOAT)
                internalFormat = GL_RGBA32F;
            texture.Generate(width, height, internalFormat, GL_RGBA, type, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture.ID, 0);
            m_ColorAttachments.push_back(texture);
        }
        // then generate Depth/Stencil texture if requested
        HasDepthAndStencil = depthAndStencil;
        if (depthAndStencil)
        {
            Texture texture;
            texture.FilterMin  = GL_LINEAR;
            texture.FilterMax  = GL_LINEAR;
            texture.WrapS      = GL_CLAMP_TO_EDGE;
            texture.WrapT      = GL_CLAMP_TO_EDGE;
            texture.Mipmapping = false;
            texture.Generate(width, height, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.ID, 0);
            m_DepthStencil = texture;
        }
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            vantor::Backlog::Log("OpenGLRenderTarget", "Framebuffer not complete!", vantor::Backlog::LogLevel::ERR);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    // --------------------------------------------------------------------------------------------
    Texture *RenderTarget::GetDepthStencilTexture() { return &m_DepthStencil; }
    // --------------------------------------------------------------------------------------------
    Texture *RenderTarget::GetColorTexture(unsigned int index)
    {
        if (index < m_ColorAttachments.size())
            return &m_ColorAttachments[index];
        else
        {
            vantor::Backlog::Log("OpenGLRenderTarget", "RenderTarget color texture requested, but not available: " + std::to_string(index),
                                 vantor::Backlog::LogLevel::WARNING);
            return nullptr;
        }
    }
    // --------------------------------------------------------------------------------------------
    void RenderTarget::Resize(unsigned int width, unsigned int height)
    {
        Width  = width;
        Height = height;

        for (unsigned int i = 0; i < m_ColorAttachments.size(); ++i)
        {
            m_ColorAttachments[i].Resize(width, height);
        }
        // generate Depth/Stencil texture if requested
        if (HasDepthAndStencil)
        {
            m_DepthStencil.Resize(width, height);
        }
    }
    // --------------------------------------------------------------------------------------------
    void RenderTarget::SetTarget(GLenum target) { m_Target = target; }
    // --------------------------------------------------------------------------------------------
    /* void RenderTarget::Bind(bool clear, bool setViewport)
     {
         glBindFramebuffer(GL_FRAMEBUFFER, ID);
         if (clear)
         {
             if (HasDepthAndStencil)
             {
                 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
     GL_STENCIL_BUFFER_BIT);
             }
             else
             {
                 glClear(GL_COLOR_BUFFER_BIT);
             }
         }
         if (setViewport)
         {
             glViewport(0, 0, Width, Height);
         }
     }*/
} // namespace vantor::Graphics::RenderDevice::OpenGL