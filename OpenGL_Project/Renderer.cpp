#include "Renderer.h"

Renderer::Renderer()
{
	//Initialise GLFW and hint it, in this case, OpenGL version is 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window and debug if there is an error
	this->window = glfwCreateWindow(SCREEN_WITDH, SCREEN_HEIGHT, "MODEL RENDERER PROJECT", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR::INSTANTIATE::WINDOW" << std::endl;
		glfwTerminate();
		//return -1;
	}

	//Introduce the window the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//Load GLAD, call GLAD before using GLAD methods
	gladLoadGL();
}

void Renderer::Execute()
{

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input

		//if (!io.WantCaptureMouse)
		//{
		//	ProcessInput(window);
		//}

		////DeltaTime
		//float currentFrameTime = glfwGetTime();
		//deltaTime = currentFrameTime - lastFrameTime;
		//lastFrameTime = currentFrameTime;

		////Framebuffer
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//glEnable(GL_DEPTH_TEST);

		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		////imgui 
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		////Use shader program first	
		//shader.Use();
		//shader.SetVec3("light.position", lightPos);
		//shader.SetVec3("viewPos", glm::vec3(cameraPos));

		//// light properties

		//glm::vec3 diffuseStrength = glm::vec3(1.0f);
		//glm::vec3 ambientStrength = glm::vec3(0.25f);

		//glm::vec3 lightColor = glm::vec3(1.0f);
		//glm::vec3 diffuseColor = lightColor * diffuseStrength; // decrease the influence
		//glm::vec3 ambientColor = diffuseColor * ambientStrength; // low influence
		//shader.SetVec3("light.ambient", ambientColor);
		//shader.SetVec3("light.diffuse", diffuseColor);
		//shader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		//// material properties
		//shader.SetVec3("material.ambient", glm::vec3(1.0f));
		//shader.SetVec3("material.diffuse", glm::vec3(1.0f));
		//shader.SetVec3("material.specular", glm::vec3(1.0f)); // specular lighting doesn't have full effect on this object's material
		//shader.SetFloat("material.shininess", 32.0f);

		////Camera Function
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//shader.SetMat4("view", view);
		//shader.SetVec3("lightPos", glm::vec3(lightPos.x, lightPos.y, lightPos.z));

		//// bind diffuse map
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, diffuseMap);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, specularMap);

		////Bind VAO that we want to use
		//glBindVertexArray(VAO1);

		//for (GLuint i = 0; i < 10; i++)
		//{
		//	float angle = 20.0f * i;
		//	model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	if (i % 3 == 0)
		//	{
		//		angle = glfwGetTime() * 25.0f;
		//	}
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.3f, 0.5f));
		//	shader.SetMat4("model", model);
		//	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//}

		//// render the loaded model
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		//shader.SetMat4("model", model);

		//porori.Draw(shader);
		//glBindVertexArray(0);

		////Framebuffer
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glDisable(GL_DEPTH_TEST);

		////glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		//glClear(GL_COLOR_BUFFER_BIT);

		//// also draw the lamp object - screen
		//lightShader.Use();
		//lightShader.SetMat4("view", view);

		//glBindVertexArray(lightVAO);
		//glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//ImGui::Begin("OpenGL Window in imgui");
		//{
		//	ImGui::BeginChild("Game Rendering");
		//	ImGui::GetWindowDrawList()->AddImage(
		//		(void*)texture,
		//		ImVec2(ImGui::GetCursorScreenPos()),
		//		ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x,
		//			ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
		//		ImVec2(0, 1),
		//		ImVec2(1, 0)
		//	);
		//	ImGui::EndChild();
		//}
		//ImGui::End();

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
