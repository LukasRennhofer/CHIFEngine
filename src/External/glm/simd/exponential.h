
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
 * File: exponential.h
 * Last Change: 
 */
 

/// @ref simd
/// @file glm/simd/experimental.h

#pragma once

#include "platform.h"

#if GLM_ARCH & GLM_ARCH_SSE2_BIT

GLM_FUNC_QUALIFIER glm_vec4 glm_vec1_sqrt_lowp(glm_vec4 x)
{
	return _mm_mul_ss(_mm_rsqrt_ss(x), x);
}

GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_sqrt_lowp(glm_vec4 x)
{
	return _mm_mul_ps(_mm_rsqrt_ps(x), x);
}

#endif//GLM_ARCH & GLM_ARCH_SSE2_BIT