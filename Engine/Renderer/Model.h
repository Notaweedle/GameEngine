#pragma once
#include "Mesh.h"

namespace nu
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes{ meshes } { CalculateRadius(); }
		Model(const Model& other) : m_meshes{ other.m_meshes }, m_radius{ other.m_radius } {}

		void AddMesh(const Mesh& mesh) { m_meshes.push_back(mesh); CalculateRadius(); }

		void SetMeshes(const std::vector<Mesh>& meshes) { m_meshes = meshes; CalculateRadius(); }
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

		
		float GetRadius() const { return m_radius; }

	private:
		void CalculateRadius()
		{
			m_radius = 0.0f;
			for (const Mesh& mesh : m_meshes) {
				for (const Vector2& point : mesh.GetPoints()) {
					float length = point.Length();
					if (length > m_radius) m_radius = length;
				}
			}
		}

		std::vector<Mesh> m_meshes;
		float m_radius = 0.0f;
	};
}
