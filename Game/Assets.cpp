#include "Assets.h"
using namespace nu;

namespace Assets
{
    
    static const Mesh hull({
        Vector2(4.0f,  0.0f),
        Vector2(1.0f, -1.2f),
        Vector2(-2.0f, -0.8f),
        Vector2(-2.0f,  0.8f),
        Vector2(1.0f,  1.2f),
        Vector2(4.0f,  0.0f)
    }, Color(0.494f, 0.549f, 0.329f));

    static const Mesh cockpit({
        Vector2(1.8f, -0.2f),
        Vector2(0.4f, -1.0f),
        Vector2(-0.5f, -0.3f),
        Vector2(1.8f, -0.2f)
    }, Color(0.35f, 0.80f, 1.0f));

    static const Mesh wing({
        Vector2(0.0f,  1.07f),
        Vector2(-2.5f,  2.4f),
        Vector2(-2.0f,  0.8f),
        Vector2(0.0f,  1.07f)
    }, Color(0.55f, 0.55f, 0.60f));

    static const Mesh flame({
        Vector2(-2.0f, -0.5f),
        Vector2(-3.6f,  0.0f),
        Vector2(-2.0f,  0.5f),
        Vector2(-2.0f, -0.5f)
    }, Color(1.0f, 0.5f, 0.1f));

    static const Mesh eneny_a1({
        Vector2(-2.5f,-2.5f),
        Vector2(-2.5f, 2.5f),
        Vector2(2.5f, 2.5f),
        Vector2(2.5f,-2.5f),
        Vector2(-2.5f,-2.5f),
        Vector2(-2.5f, 2.5f),
        Vector2(2.5f, 2.5f),
        Vector2(-2.5f,-2.5f),
        Vector2(-2.5f, 2.5f),
        Vector2(2.5f,-2.5f),
    }, Color(0.02f, 0.73f, 0.35f));

    static const Mesh raindrop({
        Vector2(2.0f,  0.0f),
        Vector2(-0.50f,  1.01f),
        Vector2(-1.03f,  1.08f),
        Vector2(-1.52f,  0.90f),
        Vector2(-1.87f,  0.51f),
        Vector2(-2.0f,  0.0f),
        Vector2(-1.87f, -0.51f),
        Vector2(-1.52f, -0.90f),
        Vector2(-1.03f, -1.08f),
        Vector2(-0.50f, -1.01f),
        Vector2(2.0f,  0.0f),
    }, Color(0.85f, 0.40f, 0.4f));

    static const Mesh raindrop_shine({
        Vector2(-1.30f, -0.55f),
        Vector2(-1.55f, -0.25f),
        Vector2(-1.50f,  0.15f),
    }, Color(0.75f, 0.92f, 1.0f));

    static const Mesh triangle_right({
        Vector2(-2,-2),
        Vector2(-2,2),
        Vector2(2,-2),
    }, Color(1.f, 1.f, 0.f));

    static const Mesh bullet({
        Vector2(0,0),
        Vector2(2,0),
    }, Color(1.0f, 1.0f, 1.0f));

    const std::shared_ptr<nu::Model> model_player   = std::make_shared<nu::Model>(std::vector<Mesh>{ hull, cockpit, wing, flame });
    const std::shared_ptr<nu::Model> model_yeedi    = std::make_shared<nu::Model>(std::vector<Mesh>{ eneny_a1 });
    const std::shared_ptr<nu::Model> model_triangle = std::make_shared<nu::Model>(std::vector<Mesh>{ triangle_right });
    const std::shared_ptr<nu::Model> model_raincol  = std::make_shared<nu::Model>(std::vector<Mesh>{ raindrop, raindrop_shine });
    const std::shared_ptr<nu::Model> model_bullet   = std::make_shared<nu::Model>(std::vector<Mesh>{ bullet });
}
