#pragma once

namespace enf
{
	class GameObject;
	class Component
	{
	public:
		virtual ~Component() = default;

		Component(Component&& other) = delete;
		Component(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;

		void SetParent(GameObject* pParent);

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
		GameObject* m_pParent{};
		Component() = default;

	private:
		bool m_Delete{};
	};
}
