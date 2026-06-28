#include "gepch.h"
#include "LayerStack.h"

void Engine::LayerStack::PushOverlay(Unique<Layer> overlay)
{
	layers.emplace(begin() + layerstackIndex, std::move(overlay));
	layers[layerstackIndex]->OnAttach();
	layerstackIndex++;
}

void Engine::LayerStack::PushLayer(Unique<Layer> layer)
{
	layers.emplace(begin() + layerstackIndex, std::move(layer));
	layers[layerstackIndex]->OnAttach();
	layerstackIndex++;
}

void Engine::LayerStack::PopOverlay(Unique<Layer> overlay)
{
	layers.erase(std::find(begin(), end(), std::move(overlay)));
	layerstackIndex--;
}

void Engine::LayerStack::PopLayer(Unique<Layer> layer)
{
	layers.erase(std::find(begin(), end(), std::move(layer)));
	layerstackIndex--;
}
