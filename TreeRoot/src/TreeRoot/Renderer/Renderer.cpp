#include "trpch.h"
#include "Renderer.h"

#include "Renderer2D.h"
#include "RenderCommand.h"

namespace tr {

	struct SceneData
	{
		glm::mat4 ProjectionViewMatrix;
	};

	static SceneData* s_SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();

		s_SceneData = new SceneData();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();

		delete s_SceneData;
	}

	void Renderer::SetAPI()
	{
	}

	void Renderer::BeginScene(const OrthoCamera& camera)
	{
		s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetShaderParameter("u_PV", s_SceneData->ProjectionViewMatrix);
		shader->SetShaderParameter("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

}
