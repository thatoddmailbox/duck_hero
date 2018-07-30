#include "nonogram.hpp"

namespace duckhero
{
	Nonogram::Nonogram()
	{
		width = height = 0;
		have_hints = false;
		horizontal_hints = std::vector<std::vector<int>>();
		vertical_hints = std::vector<std::vector<int>>();
		data = std::vector<std::vector<NonogramCell>>();
		solution = std::vector<std::vector<NonogramCell>>();
	}

	void Nonogram::CreateDataArray()
	{
		data = std::vector<std::vector<NonogramCell>>();
		solution = std::vector<std::vector<NonogramCell>>();

		for (int x = 0; x < width; x++)
		{
			data.push_back(std::vector<NonogramCell>());
			solution.push_back(std::vector<NonogramCell>());

			for (int y = 0; y < height; y++)
			{
				data[y].push_back(NonogramCell::Empty);
				solution[y].push_back(NonogramCell::Empty);
			}
		}
	}

	void Nonogram::GenerateHints()
	{
		horizontal_hints.clear();
		vertical_hints.clear();

		// horizontal hints
		for (int x = 0; x < width; x++)
		{
			std::vector<int> clues_for_column = std::vector<int>();

			int current_group = 0;
			for (int y = 0; y < height; y++)
			{
				NonogramCell cell_value = data[x][y];

				if (cell_value == NonogramCell::Filled)
				{
					current_group++;
				}
				else
				{
					clues_for_column.push_back(current_group);
					current_group = 0;
				}
			}

			horizontal_hints.push_back(clues_for_column);
		}

		// vertical hints
		for (int y = 0; y < height; y++)
		{
			std::vector<int> clues_for_row = std::vector<int>();

			int current_group = 0;
			for (int x = 0; x < width; x++)
			{
				NonogramCell cell_value = data[x][y];

				if (cell_value == NonogramCell::Filled)
				{
					current_group++;
				}
				else
				{
					clues_for_row.push_back(current_group);
					current_group = 0;
				}
			}

			vertical_hints.push_back(clues_for_row);
		}
	}

	std::vector<std::vector<int>>& Nonogram::GetHorizontalHints()
	{
		if (!have_hints)
		{
			GenerateHints();
		}

		return horizontal_hints;
	}

	std::vector<std::vector<int>>& Nonogram::GetVerticalHints()
	{
		if (!have_hints)
		{
			GenerateHints();
		}

		return vertical_hints;
	}
}