#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Serialization/json.h"
#include <Renderer/Model.h>

namespace nu
{
    class MeshRendererComponent : public RendererComponent
    {
    public:
        CLASS_PROTOTYPE(MeshRendererComponent)

            void Draw(const Renderer& renderer) override;
        void Read(const json::value_t& value) override;

        void SetModel(res_t<Model> model) { m_model = model; }

    protected:
        res_t<Model> m_model;
    };
}