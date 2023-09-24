#include <random>
#include <vector>
#include <string>
#include <sstream>

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

	static constexpr const int dx[4] = { 1,-1,0,0 };
	static constexpr const int dy[4] = { 0,0,1,-1 };

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

	//終了しているか
	bool IsDone() const {
		return this->m_turn == END_TURN;
	}

	//ターンを進める
	void Advance(const int action) {
		this->m_character.m_y += dy[action];
		this->m_character.m_x += dx[action];
		auto& point = this->m_points[m_character.m_y][m_character.m_x];
		if (point > 0) {
			this->m_gameScore += point;
			point = 0;
		}

		this->m_turn++;
	}

	//移動可能な動作
	vector<int> LegalAction() const {
		vector<int> actions;

		for (int action = 0; action < 4; action++) {
			int ny = this->m_character.m_y + dy[action];
			int nx = this->m_character.m_x + dx[action];

			if (0 <= nx && nx < W && 0 <= ny && ny < H) {
				actions.emplace_back(action);
			}

		}

		return actions;
	}

	string ToString()const {
		stringstream ss;
		ss << "turn:\t" << this->m_turn << "\n";
		ss << "score:\t" << this->m_gameScore << "\n";

		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				if (this->m_character.m_y == h && this->m_character.m_x == w) {
					ss << '@';
				}
				else if (this->m_points[h][w] > 0) {
					ss << m_points[h][w];
				}
				else {
					ss << '.';
				}
			}
		}

		return ss.str();
	}

};

