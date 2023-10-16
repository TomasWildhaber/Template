#include "LayerStack.h"

namespace Application
{
	LayerStack::LayerStack(int capacity)
	{
		layerInsert = layers.begin();
		layers.reserve(capacity);
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layerInsert = layers.emplace(layerInsert, layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end())
		{
			(*it)->OnDetach();
			layers.erase(it);
			layerInsert--;
		}
	}
}