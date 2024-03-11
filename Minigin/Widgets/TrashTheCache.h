#pragma once
#include <chrono>
#include <functional>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include "implot.h"
#include "Widget.h"

namespace enf
{
	using namespace std::chrono;

	struct Transform final
	{
		float m_Matrix[16] = 
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class GameObject3D final
	{
	public:
		Transform m_Transform{};
		int m_ID{};

		GameObject3D& operator++()
		{
			m_ID++;
			return *this;
		}
	};

	class GameObject3DAlt final
	{
	public:
		Transform* m_TransformPtr{};
		int m_ID{};

		GameObject3DAlt& operator++()
		{
			m_ID++;
			return *this;
		}
	};

	class TrashTheCache final : public Widget
	{
		typedef std::vector<float> Results;
		typedef std::vector<float> StepSizes;
	public:
		TrashTheCache(const std::string& widgetName);
		~TrashTheCache() override = default;

		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;

		void Render() override;

	private:
		int m_SampleCount{ 10 };
		
		bool m_CalcGameObject3D{};
		bool m_CalcGameObject3DAlt{};

		Results m_Result{};
		Results m_ResultAlt{};
		std::map<std::string, Results> m_ResultCombined{};

		template <typename Type>
		void RunBenchMark(int sampleCount, Results& result) const
		{
			Results results;

			constexpr int arrSize{ 1000000 };
			auto arr = new Type[arrSize]{};

			for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
			{
				std::multiset<float> samples;
				for(int sample = 0; sample < sampleCount; ++sample)
				{
					auto start = high_resolution_clock::now();
					for (int i = 0; i < arrSize; i += stepSize)
					{
						++arr[i];
					}
					auto end = high_resolution_clock::now();
					const auto duration = duration_cast<microseconds>(end - start).count();
					samples.insert(static_cast<float>(duration));
				}

				if (sampleCount > 2)
				{
					samples.erase(samples.begin());
					samples.erase(std::prev(samples.end()));
				}

				const float average = std::accumulate(samples.begin(), samples.end(), 0.f) / samples.size();

				results.push_back(average);
			}

			result = results;
			delete[] arr;
		}

		void DrawPlot(const std::function<void(const StepSizes&)>& plot, const char* name, ImPlotFlags flags);
	};
}
