#pragma once
#include <vector>
#include "Layer.h"

namespace Application
{
	class LayerStack
	{
	public:
		LayerStack(int capacity = 0);
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	};
}