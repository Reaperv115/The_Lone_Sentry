#pragma once
#include "Core.h"
#include "Score.h"

namespace Gameplay
{
	class GameManager
	{
		inline static Engine::Unique<GameManager> s_Instance;
	public:
		static GameManager& GetInstance()
		{
			if (s_Instance == nullptr)
				s_Instance = Engine::CreateUnique<GameManager>();
			return *s_Instance;
		}

		inline void IncrementScore() { score.ScorePoint(); }
		inline int GetScore() const { return score.GetScore(); }
	private:
		Score score;
	};
}
