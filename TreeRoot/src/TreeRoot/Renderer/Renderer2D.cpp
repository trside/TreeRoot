#include "trpch.h"
#include "Renderer2D.h"

#include "TreeRoot/Renderer/Shader.h"
#include "TreeRoot/Renderer/VertexArray.h"
#include "TreeRoot/Renderer/Buffers.h"

#include "TreeRoot/Renderer/RenderCommand.h"

namespace tr {

	struct SceneData
	{
		Ref<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
		Ref<VertexArray> QuadVertexArray;
	};
	
	static SceneData* s_SceneData;

	void Renderer2D::Init()
	{
		s_SceneData = new SceneData();

		s_SceneData->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
		s_SceneData->TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		s_SceneData->QuadVertexArray = VertexArray::Create();

		Ref<VertexBuffer> vertexBuffer;

		float vertices[4 * (3 + 2)] = {
			   0.0,    0.0,  0.0f,  0.0f,  0.0f,
			 100.0,    0.0,  0.0f,  1.0f,  0.0f,
			 100.0,  100.0,  0.0f,  1.0f,  1.0f,
			   0.0,  100.0,  0.0f,  0.0f,  1.0f
		};

		BufferLayout layout = {
			{ ShaderDataType::Float3, "i_Position" },
			{ ShaderDataType::Float2, "i_TexCoord" }
		};

		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout(layout);
		s_SceneData->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		Ref<IndexBuffer> indexBuffer;

		unsigned int indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };

		indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		s_SceneData->QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_SceneData->TextureShader->Bind();
		s_SceneData->TextureShader->SetShaderParameter("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_SceneData;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		s_SceneData->FlatColorShader->Bind();
		s_SceneData->FlatColorShader->SetShaderParameter("u_ProjectionView", camera.GetProjectionViewMatrix());

		s_SceneData->TextureShader->Bind();
		s_SceneData->TextureShader->SetShaderParameter("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
	{
		s_SceneData->FlatColorShader->Bind();
		s_SceneData->FlatColorShader->SetShaderParameter("u_Transform", glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f)));
		s_SceneData->FlatColorShader->SetShaderParameter("u_FlatColor", color);

		s_SceneData->QuadVertexArray->Bind();

		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), scale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture>& texture, const glm::vec4& color)
	{
		s_SceneData->TextureShader->Bind();
		s_SceneData->TextureShader->SetShaderParameter("u_Transform", glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f)));
		s_SceneData->TextureShader->SetShaderParameter("u_FlatColor", color);

		s_SceneData->QuadVertexArray->Bind();

		texture->Bind();

		RenderCommand::DrawIndexed(s_SceneData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture>& texture, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), scale, texture, color);
	}

}