#include "pch.h"
#include "MeshRendererComponent.h"
#include "Core/Factory.h"
#include "Renderer/Renderer.h"
#include "framework/Actor.h"

namespace nu
{
    FACTORY_REGISTER(MeshRendererComponent)

        void MeshRendererComponent::Draw(const Renderer& renderer)
    {
        if (m_model)
            renderer.DrawModel(*m_model, GetOwner()->getTransform());
    }

    void MeshRendererComponent::Read(const json::value_t& value)
    {
        // no model file-loader in this engine — leave empty for now,
        // or set the model in code with SetModel(Assets::model_player)
    }
}