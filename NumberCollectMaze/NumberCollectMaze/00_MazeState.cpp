#include <random>

using namespace std;

//2次元座標構造体
struct Coord {
	int m_y;
	int m_x;

	Coord(const int y = 0, const int x = 0)
		:m_y(y), m_x(x)
	{}
};

//コンパイル時定数 ROMに埋め込める分高速?
constexpr const int H = 3;
constexpr const int W = 4;
constexpr int END_TURN = 4;
constexpr int MAX_POINT = 10;

class MazeState {
private:
	int m_points[H][W] = {};
	int m_turn = 0;

public:
	Coord m_character = Coord();
	int m_gameScore = 0;
	MazeState() {}

	//迷路生成
	MazeState(const int seed) {
		auto mtSeed = mt19937(seed);
		this->m_character.m_y = mtSeed() % H;
		this->m_character.m_x = mtSeed() % W;

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				if (y == m_character.m_y && x == m_character.m_x) {
					continue;
				}
				this->m_points[y][x] = mtSeed() % MAX_POINT;
			}
		}
	}

	bool isDone() const {
		return this->m_turn == END_TURN;
	}
};

