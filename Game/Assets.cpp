#include "Assets.h"
using namespace nu;

namespace Assets {
  const  Mesh hull({
        Vector2(4.0f,  0.0f),   
        Vector2(1.0f, -1.2f),   
        Vector2(-2.0f, -0.8f),   
        Vector2(-2.0f,  0.8f),   
        Vector2(1.0f,  1.2f),   
        Vector2(4.0f,  0.0f)   
    },  Color(0.494f, 0.549f, 0.329f));

const   Mesh cockpit({
        Vector2(1.8f, -0.2f),
        Vector2(0.4f, -1.0f),
        Vector2(-0.5f, -0.3f),
        Vector2(1.8f, -0.2f)    
    },  Color(0.35f, 0.80f, 1.0f));

const   Mesh wing({
        Vector2(0.0f,  1.07f),  
        Vector2(-2.5f,  2.4f),   
        Vector2(-2.0f,  0.8f),   
        Vector2(0.0f,  1.07f)   
    },  Color(0.55f, 0.55f, 0.60f));

const   Mesh flame({
        Vector2(-2.0f, -0.5f),
        Vector2(-3.6f,  0.0f),
        Vector2(-2.0f,  0.5f),
        Vector2(-2.0f, -0.5f)    
    },  Color(1.0f, 0.5f, 0.1f));


    nu::Model model_player{ std::vector<Mesh>{ hull, cockpit, wing, flame } };
    
}