#pragma once
#include <string>
#include <Serialization/Json.h>



#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this); }

namespace nu {
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		CLASS_PROTOTYPE(Object)

		virtual const std::string& getName() const { return m_name; }
		inline  bool IsActive() const { return m_active; }
		void SetActive(bool bol = true)  { m_active = bol; }
		virtual void SetName(const std::string& name)  { m_name = name; }

		virtual void Read(const json::value_t& value) {
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "active", m_active);


		}

		

	protected:
		std::string m_name;
		bool m_active = true;


	

	};




}
