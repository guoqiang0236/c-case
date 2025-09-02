//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//
//enum PieceColor { White, BLACK };
//
//struct PiecePos
//{
//	PiecePos(int x = 0, int y = 0) :m_x(x), m_y(y) {
//	}
//	int m_x;
//	int m_y;
//};
//
//class Piece
//{
//public:
//	Piece(PiecePos pos , PieceColor color ) :m_pos(pos), m_color(color) {
//	
//	}
//	~Piece() {
//
//	}
//	virtual void draw()
//	{
//
//	}
//protected:
//	PiecePos m_pos;
//	PieceColor m_color;
//};
//
//
//class BlackPiece :public Piece
//{
//public:
//	BlackPiece(PiecePos pos, PieceColor color):Piece(pos,color) {
//
//	}
//	~BlackPiece(){
//
//	}
//
//	void draw() override {
//		cout << "绘制一个黑棋" << endl;
//	}
//};
//
//
//class WhitePiece :public Piece
//{
//public:
//	WhitePiece(PiecePos pos, PieceColor color) :Piece(pos, color) {
//
//	}
//	~WhitePiece() {
//
//	}
//
//	void draw() override {
//		cout << "绘制一个白棋" << endl;
//	}
//};
//
//
//class PieceFactory
//{
//public:
//	PieceFactory(string blackName, string whiteName) :m_blackName(blackName), m_WhiteName(whiteName) {
//	}
//	~PieceFactory() {
//		clear();
//	}
//	void setPiece(PieceColor color, PiecePos pos) {
//		Piece* pPiece = nullptr;
//		if (color == BLACK) {
//			pPiece = new BlackPiece(pos, color);
//			cout << m_blackName << "在" << pos.m_x << "," << pos.m_y << "位置下了一颗黑棋" << endl;
//		}
//		else {
//			pPiece = new WhitePiece(pos, color);
//			cout << m_WhiteName << "在" << pos.m_x << "," << pos.m_y << "位置下了一颗白棋" << endl;
//		}
//		m_vecPiece.push_back(pPiece);
//	};
//	void clear() {
//		for(auto iter=m_vecPiece.begin(); iter != m_vecPiece.end(); iter++) {
//			delete *iter;
//		}
//	}
//private:
//	vector<Piece*>m_vecPiece;
//	string m_blackName;
//	string m_WhiteName;
//};
//
//
//

//•	享元模式的核心思想是复用对象，减少内存消耗。这里黑棋和白棋对象只创建一次，后续所有棋子都复用这两个对象，棋子的位置作为外部状态单独保存。
//•	PieceFactory 就是享元工厂，负责管理和复用棋子对象。
//•	这样做可以显著减少大量棋子对象的创建，适合棋盘类、地图类等场景。
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 枚举表示棋子的颜色
enum PieceColor { White, BLACK };

// 棋子位置结构体，保存棋子的坐标
struct PiecePos
{
	PiecePos(int x = 0, int y = 0) :m_x(x), m_y(y) {
	}
	int m_x;
	int m_y;
};

// 棋子基类，包含颜色属性和虚函数draw
class Piece
{
public:
	// 构造函数，初始化棋子颜色
	Piece(PieceColor color) : m_color(color) {

	}
	~Piece() {

	}
	// 虚函数，子类实现具体绘制方法
	virtual void draw()
	{

	}
protected:
	PieceColor m_color; // 棋子颜色
};

// 黑棋类，继承自Piece，实现draw方法
class BlackPiece :public Piece
{
public:
	BlackPiece(PieceColor color) :Piece(color) {

	}
	~BlackPiece() {

	}

	// 绘制黑棋
	void draw() override {
		cout << "绘制一个黑棋" << endl;
	}
};

// 白棋类，继承自Piece，实现draw方法
class WhitePiece :public Piece
{
public:
	WhitePiece(PieceColor color) :Piece(color) {

	}
	~WhitePiece() {

	}

	// 绘制白棋
	void draw() override {
		cout << "绘制一个白棋" << endl;
	}
};

// 棋子工厂类，享元工厂，负责创建和管理棋子对象
class PieceFactory
{
public:
	// 构造函数，初始化玩家姓名
	PieceFactory(string blackName, string whiteName) :m_blackName(blackName), m_WhiteName(whiteName) {
		m_blackPiece = nullptr;
		m_whitePiece = nullptr;
	}
	~PieceFactory() {
		clear();
	}
	// 设置棋子，享元模式：黑棋和白棋对象只创建一次，后续复用
	void setPiece(PieceColor color, PiecePos pos) {
		if (color == BLACK) {
			// 如果黑棋对象不存在，则创建
			if (m_blackPiece == nullptr)
				m_blackPiece = new BlackPiece(color);
			cout << m_blackName << "在" << pos.m_x << "," << pos.m_y << "位置下了一颗黑棋" << endl;
			m_blackPiece->draw();
		}
		else {
			// 如果白棋对象不存在，则创建
			if (m_whitePiece == nullptr)
				m_whitePiece = new WhitePiece(color);
			cout << m_WhiteName << "在" << pos.m_x << "," << pos.m_y << "位置下了一颗白棋" << endl;
			m_whitePiece->draw();
		}
		// 保存棋子位置
		m_vecPiece.push_back(pos);
	};
	// 清理棋子对象
	void clear() {
		delete m_blackPiece;
		delete m_whitePiece;
	}
private:
	vector<PiecePos>m_vecPiece; // 保存所有棋子的位置
	string m_blackName;         // 黑棋玩家姓名
	string m_WhiteName;         // 白棋玩家姓名
	Piece* m_blackPiece;       // 黑棋享元对象
	Piece* m_whitePiece;       // 白棋享元对象
};

// 主函数，模拟下棋过程
int main() {
	PieceFactory* pFactory = new PieceFactory("张三", "李四");
	pFactory->setPiece(BLACK, PiecePos(1, 1));
	pFactory->setPiece(White, PiecePos(2, 2));
	pFactory->setPiece(BLACK, PiecePos(3, 3));
	pFactory->setPiece(White, PiecePos(4, 4));
	pFactory->setPiece(BLACK, PiecePos(5, 5));
	pFactory->setPiece(White, PiecePos(6, 6));
	delete pFactory;
	return 0;
}