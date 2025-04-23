
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
 * File: chifCloudsModel.cpp
 * Last Change: Updatet Debugging System
 */
 

#include "chifCloudsModel.h"
#include <glad/glad.h>
#include "chifTexture.h"


namespace chif::Graphics {

	void CloudsModel::setGui() {

		ImGui::Begin("Clouds controls: ");
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Post Proceesing");
		// ImGui::Text("This is some useful text.");               
		ImGui::Checkbox("Post Processing (Gaussian Blur)", &postProcess);
		ImGui::Checkbox("God Rays", &enableGodRays);
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Clouds rendering");

		ImGui::SliderFloat("Coverage", &coverage, 0.0f, 1.0f);
		ImGui::SliderFloat("Speed", &cloudSpeed, 0.0f, 5.0E3);
		ImGui::SliderFloat("Crispiness", &crispiness, 0.0f, 120.0f);
		ImGui::SliderFloat("Curliness", &curliness, 0.0f, 3.0f);
		ImGui::SliderFloat("Density", &density, 0.0f, 0.1f);
		ImGui::SliderFloat("Light absorption", &absorption, 0.0f, 1.5f);
		ImGui::Checkbox("Enable sugar powder effect", &enablePowder);


		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Dome controls");
		ImGui::SliderFloat("Sky dome radius", &earthRadius, 10000.0f, 5000000.0f);
		ImGui::SliderFloat("Clouds bottom height", &sphereInnerRadius, 1000.0f, 15000.0f);
		ImGui::SliderFloat("Clouds top height", &sphereOuterRadius, 1000.0f, 40000.0f);

		if (ImGui::SliderFloat("Clouds frequency", &perlinFrequency, 0.0f, 4.0f))
			generateWeatherMap();

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Clouds colors");
		glm::vec3 * cloudBottomColor = &cloudColorBottom;
		ImGui::ColorEdit3("Cloud color", (float*)cloudBottomColor);

		ImGui::End();
	}

	CloudsModel::CloudsModel(sceneElements * scene, chif::Graphics::Skybox * sky) : scene(scene), sky(sky)
	{
		initVariables();
		initShaders();
		generateModelTextures();
	}

	void CloudsModel::initShaders()
	{
		volumetricCloudsShader = new chif::Graphics::Renderer::Shader::Shader("volumetricCloudsShader", "shaders\\volumetric_clouds.comp");
		postProcessingShader = new chif::Graphics::Renderer::Shader::ScreenSpaceShader("shaders\\clouds_post.frag");

		weatherShader = new chif::Graphics::Renderer::Shader::Shader("weatherMap");
		weatherShader->attachShader("shaders\\weather.comp");
		weatherShader->linkPrograms();
	}

	void CloudsModel::generateModelTextures()
	{
		if (!perlinTex) {
			chif::Graphics::Renderer::Shader::Shader comp("perlinWorley");
			comp.attachShader("shaders/perlinworley.comp");
			comp.linkPrograms();

			this->perlinTex = chif::Graphics::generateTexture3D(128, 128, 128);

			comp.use();
			comp.setVec3("u_resolution", glm::vec3(128, 128, 128));
			chif::Backlog::Log("CloudsModel", "Computing \"perlinworley\"", chif::Backlog::LogLevel::INFO);
			glActiveTexture(GL_TEXTURE0);
			comp.setInt("outVolTex", 0);
			glBindTexture(GL_TEXTURE_3D, this->perlinTex);
			glBindImageTexture(0, this->perlinTex, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
			glDispatchCompute(INT_CEIL(128, 4), INT_CEIL(128, 4), INT_CEIL(128, 4));

			chif::Backlog::Log("CloudsModel", "Finished computing \"perlinworley\"", chif::Backlog::LogLevel::INFO);
			//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
			glGenerateMipmap(GL_TEXTURE_3D);
		}

		if (!worley32) {
			chif::Graphics::Renderer::Shader::Shader worley_git("worleyComp");
			worley_git.attachShader("shaders/worley.comp");
			worley_git.linkPrograms();

			this->worley32 = chif::Graphics::generateTexture3D(32, 32, 32);

			worley_git.use();
			//worley_git.setVec3("u_resolution", glm::vec3(32, 32, 32));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_3D, this->worley32);
			glBindImageTexture(0, this->worley32, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

			chif::Backlog::Log("CloudsModel", "Computing \"worley 32\"", chif::Backlog::LogLevel::INFO);

			glDispatchCompute(INT_CEIL(32, 4), INT_CEIL(32, 4), INT_CEIL(32, 4));

			chif::Backlog::Log("CloudsModel", "Finished computing \"worley 32\"", chif::Backlog::LogLevel::INFO);

			glGenerateMipmap(GL_TEXTURE_3D);
		}

		if (!weatherTex) {
			this->weatherTex = chif::Graphics::generateTexture2D(1024, 1024);
			
			generateWeatherMap();

			seed = scene->seed;
			oldSeed = seed;
		}
	}

	CloudsModel::~CloudsModel()
	{
		delete volumetricCloudsShader;
		delete postProcessingShader;
		delete weatherShader;
	}

	void CloudsModel::update()
	{
		seed = scene->seed;
		if (seed != oldSeed) {
			generateWeatherMap();
			oldSeed = seed;
		}
	}

	void CloudsModel::generateWeatherMap() {
		chif::Graphics::bindTexture2D(weatherTex, 0);
		weatherShader->use();
		weatherShader->setVec3("seed", scene->seed);
		weatherShader->setFloat("perlinFrequency", perlinFrequency);
		chif::Backlog::Log("CloudsModel", "Computing \"weather\"", chif::Backlog::LogLevel::INFO);
		glDispatchCompute(INT_CEIL(1024, 8), INT_CEIL(1024, 8), 1);
		chif::Backlog::Log("CloudsModel", "Finished computing \"weather\"", chif::Backlog::LogLevel::INFO);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	}

	void CloudsModel::initVariables()
	{
		cloudSpeed = 450.0;
		coverage = 0.45;
		crispiness = 40.;
		curliness = .1;
		density = 0.02;
		absorption = 0.35;

		earthRadius = 600000.0;
		sphereInnerRadius = 5000.0;
		sphereOuterRadius = 17000.0;

		perlinFrequency = 0.8;

		enableGodRays = false;
		enablePowder = false;
		postProcess = true;

		seed = glm::vec3(0.0, 0.0, 0.0);
		oldSeed = glm::vec3(0.0, 0.0, 0.0);

		cloudColorTop = (glm::vec3(169., 149., 149.)*(1.5f / 255.f));
		cloudColorBottom = (glm::vec3(65., 70., 80.)*(1.5f / 255.f));

		weatherTex = 0;
		perlinTex = 0;
		worley32 = 0;
	}
} // NAMESPACE chif::Graphics
