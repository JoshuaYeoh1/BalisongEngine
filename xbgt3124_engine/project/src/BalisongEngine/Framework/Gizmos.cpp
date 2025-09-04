#include "Gizmos.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;

#include "Graphics.h"
#include "Mesh.h"
using namespace BalisongEngineRenderer;

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

vec4 Gizmos::color = { 1,1,1,1 };
float Gizmos::thickness = .005f;

// ===============================================================================

void Gizmos::DrawQuad(const vec2& size, const vec2& center, float rotation, const vec2& scale)
{
    glDisable(GL_DEPTH_TEST);

    vector<Vertex> vertices =
    {
        Vertex({ 0, size.y, 0 }, { 0, 1 }),
        Vertex({ 0, 0, 0 }, { 0, 0 }),
        Vertex({ size.x, 0, 0 }, { 1, 0 }),

        Vertex({ size.x, 0, 0 }, { 1, 0 }),
        Vertex({ size.x, size.y, 0 }, { 1, 1 }),
        Vertex({ 0, size.y, 0 }, { 0, 1 })
    };

    for (auto& vertex : vertices)
    {
        vertex.x -= size.x * .5f;
        vertex.y -= size.y * .5f;
    }

    auto quad = new Mesh(vertices);

    RenderParams param{};
    param.tint = color;
    param.translation = { center.x, center.y, 0 };
    param.rotationZ = rotation;
    param.scale = { scale.x, scale.y, 1 };

    Graphics::DrawMesh(quad, param);

    glEnable(GL_DEPTH_TEST);
}

void Gizmos::DrawLine(const vec2& from, const vec2& to)
{
    auto dir = to - from;
    auto length = glm::length(dir);
    if (length == 0) return;
    dir = normalize(dir); // cant normalize 0 length

    auto midpoint = from + dir * length * .5f;

    float radians = atan2(dir.y, dir.x);
    constexpr float pie = 3.14159265358979323846f;
    float degrees = radians * (180 / pie);
    float rotation = degrees - 90;

    DrawQuad({ thickness,length }, midpoint, rotation);
}

void Gizmos::DrawBox(const vec2& size, const vec2& center)
{
    vec2 half_size = size * .5f;

    vec2 top_right = center + half_size;
    vec2 bottom_left = center - half_size;
    vec2 top_left = { bottom_left.x, top_right.y };
    vec2 bottom_right = { top_right.x, bottom_left.y };

    DrawLine(top_left, top_right);
    DrawLine(top_right, bottom_right);
    DrawLine(bottom_right, bottom_left);
    DrawLine(bottom_left, top_left);
}

void Gizmos::DrawCircle(float radius, const vec2& center, int segments)
{
    glDisable(GL_DEPTH_TEST);

    vector<vec2> points;

    constexpr float pie = 3.14159265358979323846f;

    for (int i = 0; i < segments; i++)
    {
        float angle = 2 * pie * (float)i / segments;

        float x = center.x + radius * cos(angle);  // X position
        float y = center.y + radius * sin(angle);  // Y position

        points.push_back({ x,y });
    }

    for (int i = 0; i < points.size(); i++)
    {
        auto i2 = i+1 >= points.size() ? 0 : i+1;

        DrawLine(points[i], points[i2]);
    }

    points.clear();

    glEnable(GL_DEPTH_TEST);
}