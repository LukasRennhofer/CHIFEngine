
/*
 *    				~ CHIFEngine ~
 *
 * Copyright (c) 2025 Lukas Rennhofer
 *
 * Licensed under the MIT License. See LICENSE file for more details.
 *
 * Author: Lukas Rennhofer
 * Date: 2025-04-01
 *
 * File: chifFontUtils.h
 * Last Change: Added Dear Imgui Light theme by Pacôme Danhiez and added Demo Profiler
*/


#pragma once

#include <glad/glad.h>

#include "../../Core/Backlog/chifBacklog.h"

class FontUtils {
public:
    FontUtils();
    ~FontUtils();

    static void loadShader(char* shaderSource, GLenum shaderType, GLuint &programId);
};
