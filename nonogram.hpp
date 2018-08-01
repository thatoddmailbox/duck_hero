#ifndef _NONOGRAM_HPP
#define _NONOGRAM_HPP

#include <cstdlib>
#include <vector>

namespace duckhero
{
	enum NonogramCell
	{
		Empty,
		Flagged,
		Filled
	};

	class Nonogram
	{
	public:
		int width, height;
		std::vector<std::vector<NonogramCell>> data;
		std::vector<std::vector<NonogramCell>> solution;

		bool have_hints;
		std::vector<std::vector<int>> horizontal_hints;
		std::vector<std::vector<int>> vertical_hints;

		bool mouse_down;

		Nonogram();

		void CreateDataArray();

		void GenerateHints();

		bool IsSolved();

		std::vector<std::vector<int>>& GetHorizontalHints();
		std::vector<std::vector<int>>& GetVerticalHints();
	};
}

#endif