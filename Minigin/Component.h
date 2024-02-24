#pragma once

namespace enf
{
	class Component
	{
	public:
		virtual ~Component();

		Component(Component&& other) = delete;
		Component(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;

		virtual inline void Awake(){}
		virtual inline void FixedUpdate(){}
		virtual inline void Update(){}
		virtual inline void LateUpdate(){}
		virtual inline void Render(){}

	protected:
		Component() = default;
	};
}