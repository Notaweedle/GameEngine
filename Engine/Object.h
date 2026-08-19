#pragma once
#include <string>



#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this); }

namespace nu {


	

	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		virtual const std::string& GetName() const { return m_name; }
		inline  bool IsActive() const { return m_active; }
		void SetActive(bool bol = true)  { m_active = bol; }
		virtual void SetName(const std::string& name)  { m_name = name; }


		

	protected:
		std::string m_name;
		bool m_active = true;


	

	};




}
