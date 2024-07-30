#include "Base.h"

void TestSolution()
{
	const int WIDTH = 10;
	const int HEIGHT = 10;

	TileMap tilemap(WIDTH, HEIGHT);

	vector<int> row_answers[]{ {3},{5},{3,2},{5},{5,3},{9},{2,3},{2,4},{8},{5} };
	vector<int> col_answers[]{ {1},{8},{9},{2,3,2},{6,2},{5,2},{1,3},{6},{5},{4} };

	Solution solution(tilemap, row_answers, col_answers);

	tilemap.Show();
}

int main()
{
	TestSolution();
}