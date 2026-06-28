#pragma once


namespace Gameplay
{
	class Score
	{
	public:
		Score();
		
		void ScorePoint();

		inline int GetScore() const { return score; }
	private:
		int score;
	};
}