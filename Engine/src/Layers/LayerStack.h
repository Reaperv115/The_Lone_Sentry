#pragma once
#include "layer.h"
#include "Core.h"
#include <vector>

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack() = default;

		void PushOverlay(Unique<Layer> overlay);
		void PushLayer(Unique<Layer> layer);
		void PopOverlay(Unique<Layer> overlay);
		void PopLayer(Unique<Layer> layer);

		std::vector<Unique<Layer>>::iterator iter;
		std::vector<Unique<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<Unique<Layer>>::iterator end() { return layers.end(); }
		std::vector<Unique<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<Unique<Layer>>::reverse_iterator rend() { return layers.rend(); }

	private:
		std::vector<Unique<Layer>> layers;
		unsigned int layerstackIndex = 0;
	};
}

