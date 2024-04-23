#pragma once

namespace tr {

	class Time
	{
	public:
		virtual ~Time() {}
		virtual float GetTime() const = 0;
		virtual float GetDeltaTime() const = 0;

		virtual void CalculateDeltaTime() = 0;
		
		static Ref<Time> Create();
	};

}