#include "trpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace tr {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::SetAPI()
	{
	}

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera)
	{
		s_SceneData->ProjectionViewMatrix = camera->GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetUniform("u_PV", s_SceneData->ProjectionViewMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
