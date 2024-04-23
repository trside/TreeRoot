#include "trpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"	// Temporary

namespace tr {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::SetAPI()
	{
	}

	void Renderer::BeginScene(const Ref<OrthoCamera>& camera)
	{
		s_SceneData->ProjectionViewMatrix = camera->GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniform("u_PV", s_SceneData->ProjectionViewMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
