#pragma once
#include "Model.h"

namespace Assets
{
    // C++17 inline variables: each is defined once here in the header and shared
    // across every translation unit that includes it (no extern + separate
    // Assets.cpp definition needed). The meshes are declared before the models
    // that use them, so within any TU they are initialized first.

    inline const nu::Mesh hull({
        nu::Vector2(4.0f,  0.0f),
        nu::Vector2(1.0f, -1.2f),
        nu::Vector2(-2.0f, -0.8f),
        nu::Vector2(-2.0f,  0.8f),
        nu::Vector2(1.0f,  1.2f),
        nu::Vector2(4.0f,  0.0f)
    }, nu::Color(0.494f, 0.549f, 0.329f));

    inline const nu::Mesh cockpit({
        nu::Vector2(1.8f, -0.2f),
        nu::Vector2(0.4f, -1.0f),
        nu::Vector2(-0.5f, -0.3f),
        nu::Vector2(1.8f, -0.2f)
    }, nu::Color(0.35f, 0.80f, 1.0f));

    inline const nu::Mesh wing({
        nu::Vector2(0.0f,  1.07f),
        nu::Vector2(-2.5f,  2.4f),
        nu::Vector2(-2.0f,  0.8f),
        nu::Vector2(0.0f,  1.07f)
    }, nu::Color(0.55f, 0.55f, 0.60f));

    inline const nu::Mesh flame({
        nu::Vector2(-2.0f, -0.5f),
        nu::Vector2(-3.6f,  0.0f),
        nu::Vector2(-2.0f,  0.5f),
        nu::Vector2(-2.0f, -0.5f)
    }, nu::Color(1.0f, 0.5f, 0.1f));

    inline const nu::Mesh eneny_a1({
        nu::Vector2(-2.5f,-2.5f),
        nu::Vector2(-2.5f, 2.5f),
        nu::Vector2(2.5f, 2.5f),
        nu::Vector2(2.5f,-2.5f),
        nu::Vector2(-2.5f,-2.5f),
        nu::Vector2(-2.5f, 2.5f),
        nu::Vector2(2.5f, 2.5f),
        nu::Vector2(-2.5f,-2.5f),
        nu::Vector2(-2.5f, 2.5f),
        nu::Vector2(2.5f,-2.5f),
    }, nu::Color(0.02f, 0.73f, 0.35f));

    inline const nu::Mesh raindrop({
        nu::Vector2(2.0f,  0.0f),
        nu::Vector2(-0.50f,  1.01f),
        nu::Vector2(-1.03f,  1.08f),
        nu::Vector2(-1.52f,  0.90f),
        nu::Vector2(-1.87f,  0.51f),
        nu::Vector2(-2.0f,  0.0f),
        nu::Vector2(-1.87f, -0.51f),
        nu::Vector2(-1.52f, -0.90f),
        nu::Vector2(-1.03f, -1.08f),
        nu::Vector2(-0.50f, -1.01f),
        nu::Vector2(2.0f,  0.0f),
    }, nu::Color(0.85f, 0.40f, 0.4f));

    inline const nu::Mesh raindrop_shine({
        nu::Vector2(-1.30f, -0.55f),
        nu::Vector2(-1.55f, -0.25f),
        nu::Vector2(-1.50f,  0.15f),
    }, nu::Color(0.75f, 0.92f, 1.0f));

    inline const nu::Mesh triangle_right({
        nu::Vector2(-2,-2),
        nu::Vector2(-2,2),
        nu::Vector2(2,-2),
    }, nu::Color(1.f, 1.f, 0.f));

    inline const nu::Mesh bullet({
        nu::Vector2(0,0),
        nu::Vector2(2,0),
    }, nu::Color(1.0f, 1.0f, 1.0f));

    inline const nu::Model model_player{ std::vector<nu::Mesh>{ hull, cockpit, wing, flame } };
    inline const nu::Model model_yeedi{ std::vector<nu::Mesh>{ eneny_a1 } };
    inline const nu::Model model_triangle{ std::vector<nu::Mesh>{ triangle_right } };
    inline const nu::Model model_raincol{ std::vector<nu::Mesh>{ raindrop, raindrop_shine } };
    inline const nu::Model model_bullet{ std::vector<nu::Mesh>{ bullet } };
}
