#include "TrashTheCache.h"

#include "imgui.h"
#include "fmt/format.h"

enf::TrashTheCache::TrashTheCache(const std::string& widgetName)
	: Widget{ widgetName }
{
}

void enf::TrashTheCache::Render()
{
	ImGui::InputInt("# samples", &m_SampleCount);

	bool running{ m_CalcGameObject3D };

	if(running)
	{
		ImGui::BeginDisabled();
	}

	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		m_CalcGameObject3D = true;

		m_Result.clear();
		RunBenchMark<GameObject3D>(m_SampleCount, m_Result);
		m_ResultCombined["GameObject3D"] = m_Result;

		m_CalcGameObject3D = false;
	}

	if (running)
	{
		ImGui::EndDisabled();
		ImGui::Text("Wait for it...");
	}

	if (!m_Result.empty())
		DrawPlot([&](const StepSizes& stepSizes)
			{
				ImPlot::PlotLine<float>("GameObject3D", stepSizes.data(), m_Result.data(), static_cast<int>(m_Result.size()));
			}, "##GameObject3D", ImPlotFlags_Crosshairs);

	running = m_CalcGameObject3DAlt;

	if (running)
	{
		ImGui::BeginDisabled();
	}

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		m_CalcGameObject3DAlt = true;

		m_ResultAlt.clear();
		RunBenchMark<GameObject3D>(m_SampleCount, m_ResultAlt);
		m_ResultCombined["GameObject3DAlt"] = m_ResultAlt;

		m_CalcGameObject3DAlt = false;
	}

	if (running)
	{
		ImGui::EndDisabled();
		ImGui::Text("Wait for it...");
	}

	if (!m_ResultAlt.empty())
		DrawPlot([this](const StepSizes& stepSizes)->void
			{
				ImPlot::PlotLine<float>("GameObject3DAlt", stepSizes.data(), m_ResultAlt.data(), static_cast<int>(m_ResultAlt.size()));
			}, "##GameObject3DAlt", ImPlotFlags_Crosshairs);

	if (!m_Result.empty() && !m_ResultAlt.empty())
	{
		ImGui::Text("Combined:");

		DrawPlot([this](const StepSizes& stepSizes)->void 
			{
				for (auto&& result : m_ResultCombined)
					ImPlot::PlotLine<float>(result.first.data(), stepSizes.data(), result.second.data(), static_cast<int>(result.second.size()));
			}, "##combined", ImPlotFlags_Crosshairs);
	}

}

void enf::TrashTheCache::DrawPlot(const std::function<void(const StepSizes&)>& plot, const char* name,
	ImPlotFlags flags)
{
	if(ImPlot::BeginPlot(name, ImVec2{-1, 0}, flags))
	{
		ImPlot::SetupAxes("Step size", "Time",
			ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_NoLabel,
			ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoLabel);

		ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);

		const std::vector<float>& stepSizes = []()
		{
			StepSizes stepSizes;
			for (float stepSize = 1.f; stepSize <= 1024.f; stepSize *= 2.f)
			{
				stepSizes.push_back(stepSize);
			}
			return stepSizes;
		}();

		static const std::vector<double> doubleTicks(stepSizes.begin(), stepSizes.end());

		ImPlot::SetupAxisTicks(ImAxis_X1, doubleTicks.data(), int(stepSizes.size()));

		plot(stepSizes);

		ImPlot::EndPlot();
	}
}
