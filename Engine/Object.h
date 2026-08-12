#pragma once
#include <string>

namespace nu {

	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		inline const std::string& getName() const { return m_name; }
		inline bool isActive() const { return m_active; }
		inline void SetActive(bool bol) { m_active = bol; }

	protected:
		std::string m_name = "hello";
		bool m_active = true;


	private:

	};




}
