// universeBuilder.cpp : définit le point d'entrée de l'application.
//


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include <glm/common.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <MC/imgui/Utils.hpp>
#include <MC/Core/Object.hpp>

#include <MC/Graphics/ProceduralTexture.hpp>

#include <MC/Graphics/IndexBuffer.hpp>
#include <MC/Graphics/VertexArray.hpp>
#include <MC/Graphics/VertexBuffer.hpp>
#include <MC/Graphics/VertexBufferLayout.hpp>
#include <MC/Graphics/Shader.hpp>
#include <MC/Core/DataManager.hpp>

#include <MC/Core/Block.hpp>

//#include <external/perlin.hpp>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <windows.h>

void left_rotate_by_one(float arr[], int n)
{

	/* Shift operation to the left */
	int temp = arr[0], i;
	for (i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];
	arr[i] = temp;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (width > height) {
		glViewport(0, 0, width, width);
	}
	else {
		glViewport(0, 0, height, height);
	}
	// [TODO] Re-render the scene
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "ERROR while initializing glfw" << std::endl;
		abort;
	}
	glfwWindowHint(GLFW_SAMPLES, 16);

	GLFWwindow* window = glfwCreateWindow(640, 640, "Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int glewInitResult;

	glewInitResult = glewInit();
	if(glewInitResult)
		std::cout << (GLenum)glewInitResult << std::endl;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);



	
	// Setup Dear ImGui context


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();


	// Setup Platform/Renderer bindings


	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	Style();

	auto font_default = io.Fonts->AddFontDefault();

	MC::DataManager dmanager;
	dmanager.generateCubeVertexBuffer();
	dmanager.loadBlocsList();

	MC::Object obj(&dmanager, "../../../Shaders/basic.glsl");
	MC::Object obj2(&dmanager, "../../../Shaders/light.glsl");
	//dmanager.loadObj(&obj, "../../../ressources/3dmodels/face-mask.obj");
	dmanager.loadObj(&obj, "../../../ressources/3dmodels/face-mask.obj");
	dmanager.loadObj(&obj2, "../../../ressources/3dmodels/light.obj");
	//dmanager.loadObj(&obj, "../../../ressources/3dmodels/cube.obj");

	MC::ProceduralTexture ptexture(10, 10, 123456789, 4);
	ptexture.sendToGl(8, 8);

	MC::Texture texture;
	//texture.loadPNG("../../../ressources/textures/block/diamond_ore.png", 3, false);
	//texture.loadPNG("../../../ressources/3dmodels/FaceMask.png", 3, false);
	texture.loadPNG("../../../ressources/3dmodels/FaceMask.png", 3, false);

	MC::Texture texture2;
	texture2.loadPNG("../../../ressources/3dmodels/Skull/Skull.png", 3, false);


	MC::Texture normalTexture;
	//texture.loadPNG("../../../ressources/textures/block/diamond_ore.png", 3, false);
	//normalTexture.loadPNG("../../../ressources/3dmodels/Skull/normal.png", 3, false);
	normalTexture.loadPNG("./ressources/3dmodels/Skull/normal.png", 3, false);
	MC::Block dirt(&dmanager);

	float sliderValue(0.5f);

	bool my_tool_active;
	float my_color[4];
	float my_values[50] = { 0.f };


	int frameCount(0);
	double previousTime(0);
	float rotation(180);
	float pos[3] = { 0.f, 0.f, 0.f };
	float scale(1.f);

	float rotation2(180);
	float pos2[3] = { 0.f, 0.f, 0.f };
	float scale2(1.f);

	float lightpos[3] = { -1.f, -2.f, -0.7f };

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 position;
	glm::mat4 model;
	glm::mat4 MVPmatrix;
	while (!glfwWindowShouldClose(window))
	{
		projection = glm::perspective(glm::radians(60.f), 1.0f, 0.1f, 100.0f);
		view = glm::lookAt(glm::vec3(-4, -4, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

		position = glm::translate(glm::mat4(1.f), glm::vec3(pos[0], pos[1], pos[2]));
		model = position * glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.f), glm::vec3(0.5*scale, 0.5*scale, 0.5*scale));
		MVPmatrix = projection * view * model;

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 0.2)
		{
			int n = sizeof(my_values) / sizeof(my_values[0]);
			left_rotate_by_one(my_values, n);
			my_values[n-1] = frameCount/0.2f;

			frameCount = 0;
			previousTime = currentTime;
		}
		my_values[0] = 0.f;

		ImGui::Begin("Stats", &my_tool_active);

		ImGui::PlotHistogram("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		char s[50] = "";
		sprintf(s, "%i", (int)my_values[49]);
		ImGui::Text(s);
		ImGui::DragFloat("rotation", &rotation, 0.5f);
		//ImGui::SliderFloat3("position", pos, 0.f, 1.f);
		ImGui::DragFloat3("position", pos, 0.1f);
		ImGui::DragFloat("scale", &scale, 0.01f);

		ImGui::DragFloat3("light position", lightpos, 0.1f);
		ImGui::End();
		

		glUseProgram(0);
		ImGui::Render();

		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		va.bind();
		ib.bind();
		
		shader.bind();
		shader.setUniformMat4f("u_projection", MVPmatrix);

		GLCall(glDrawElements(GL_POINTS, sizeof(indexes) / sizeof(indexes[0]), GL_UNSIGNED_INT, nullptr));

		va.unbind();
		ib.unbind();
		shader.unbind();
		*/

		//dirt.render(&MVPmatrix, &ptexture);
		obj.render(&MVPmatrix, &model, &view, lightpos, { &texture, &normalTexture });

		position = glm::translate(glm::mat4(1.f), glm::vec3(lightpos[0], lightpos[1], lightpos[2]));
		model = position;// * glm::rotate(glm::mat4(1.f), glm::radians(rotation2), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.f), glm::vec3(0.5 * scale2, 0.5 * scale2, 0.5 * scale2));
		MVPmatrix = projection * view * model;

		obj2.render(&MVPmatrix, true);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		/*
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		*/
	};
	//glfwDestroyWindow(window);
	return 0;
}