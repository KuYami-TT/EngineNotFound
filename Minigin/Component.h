#pragma once

namespace enf
{
	class GameObject;
	class Component
	{
	public:
		friend GameObject;

		virtual ~Component() = default;

		Component(Component&& other) = delete;
		Component(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;

		[[nodiscard]]GameObject* GetParent() const;

		virtual inline void Awake(){}
		virtual inline void FixedUpdate(){}
		virtual inline void Update(){}
		virtual inline void LateUpdate(){}
		virtual inline void Render(){}

		//Mark for deletion
		void MarkForMurder();
		void LetLive();
		[[nodiscard]] bool IsMarked() const;

	protected:
		Component() = default;

	private:
		GameObject* m_ParentPtr{};
		bool m_Delete{};

		void SetParent(GameObject* parentPtr);
	};
}
