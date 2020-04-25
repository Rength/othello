# include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include<HamFramework.hpp>
# define S 12
#define chara(player) (3-(player)) 
enum class State
{
	Title,
	Game
};

using MyApp = SceneManager<State>;
class Title : public MyApp::Scene
{
	private:
		//開始ボタン
		Rect startButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
		//Transition:滑らかに光らせる
		Transition startTransition = Transition(0.4s, 0.2s);
		//終了ボタン
		Rect exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
		Transition exitTransition = Transition(0.4s, 0.2s);
	public:
	Title(const InitData& init)
		:IScene(init)
	{}
	void update() override
	{
		startTransition.update(startButton.mouseOver());
		exitTransition.update(exitButton.mouseOver());
		//ボタンに重なっているときはカーソルを指に
		if (startButton.mouseOver()||exitButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
		if (startButton.leftClicked())
		{
			changeScene(State::Game);
		}
		if (exitButton.leftClicked())
		{
			System::Exit();
		}
	}
	void draw() const override
	{
		const String titletext = U"オセロ";
		const Vec2 center(Scene::Center().x-200, 120);
		//位置を少しずらして二回描画(影っぽくなる)
		FontAsset(U"Title")(titletext).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
		FontAsset(U"Title")(titletext).drawAt(center);
		startButton.draw(ColorF(1.0, startTransition.value())).drawFrame(2);
		exitButton.draw(ColorF(1.0, exitTransition.value())).drawFrame(2);
		//drawAt:指定した座標を中心に描画
		FontAsset(U"Menu")(U"start").drawAt(startButton.center(), ColorF(0.25));
		FontAsset(U"Menu")(U"exit").drawAt(exitButton.center(), ColorF(0.25));
	}
};
class Game : public MyApp::Scene
{
	private:
	static constexpr int32 Cellsize = 50;
	static constexpr int32 width = 12;
	static constexpr int32 hight = 12;
	//10x10の盤面
	Grid<int32> init_data = Grid<int32>(12, 12);
	//ひっくり返す関数:引数(盤面の情報,手番,置いたマス,探索する方向)
	int count_turn(Grid<int32>& init_data, int player, int p, int q, int d, int e)
	{
		int i = 0;
		//置いたマスから相手の石の数をカウント
		for (i = 1; init_data[p + i * d][q + i * e] == chara(player); i++)
		{
			if (p + (i + 1) * d == -1) return 0;
		}
		//カウントした後に自分の石で挟まれているか
		if (init_data[p + i * d][q + i * e] == player)
		{
			//挟まれていれば相手の石の数を返す
			return i - 1;
		}
		else
		{
			//挟まれていなければ何もしない
			return 0;
		}

	}
	//盤面を裏返す関数
	void set_board(Grid<int32>& init_data, int player, int p, int q)
	{
		int count = 0;
		for (int d = -1; d < 2; d++)
		{
			for (int e = -1; e < 2; e++)
			{
				if (p == 0 && d == -1) continue;
				if (d == 0 && e == 0) continue;
				count = count_turn(init_data, player, p, q, d, e);
				for (int i = 0; i <= count; i++)
				{
					//裏返す
					init_data[p + i * d][q + i * e] = player;
				}
			}
		}

	}
	void game_counter(Grid<int32>& init_data)
	{
		int32 white_counter = 0;
		int32 black_counter = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (init_data[i][j] == 1) black_counter += 1;
				if (init_data[i][j] == 2) white_counter += 1;
			}
		}
		Print << U"黒：" << white_counter << U"白：" << black_counter;
	}
	//打った手がルール的にあっているかを確認する
	//playerが(p,q)のマスに石が置けるかどうかを返す
	int  check(Grid<int32>& init_data, int player, int p, int q)
	{
		//盤面の中かどうか
		if (p < 0 || p > 9 || q < 0 || q > 9) return 0;
		//石がすでに置かれていないかどうか
		if (init_data[p][q] != 0) return 0;
		//置けるマスなら1を返す
		//8方向探索
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (p == 0 && i == -1) continue;
				if (count_turn(init_data, player, p, q, i, j)) return 1;
			}
		}

		return 0;
	}
	//置ける石があるかどうかを確認する
	int skip(Grid<int32>& init_data, int player)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (check(init_data, player, j, i)) return 1;
			}
		}
		return 0;
	}
	//格子を描く
	void print_fence() const
	{
		for (int i = 0; i < 11; i++)
		{
			Line(i * Cellsize, 0, i * Cellsize, 10 * Cellsize).draw(4, Palette::White);
			Line(0, i * Cellsize, 10 * Cellsize, i * Cellsize).draw(4, Palette::White);
		}
	}
	//セルを描く
	void print_cells() const
	{
		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{
				//セル
				const Rect cell(i * Cellsize, j * Cellsize, Cellsize, Cellsize);
				//セルの情報
				const int32 mark = init_data[i][j];
				if (mark == 1)
				{
					//白を置く
					Circle(cell.center(), Cellsize * 0.6 - 10).draw(ColorF(0.2));
					continue;
				}
				else if (mark == 2)
				{
					//黒を置く
					Circle(cell.center(), Cellsize * 0.6 - 10).draw(ColorF(255));
					continue;
				}
				//セルがマウスオーバー
				if (cell.mouseOver())
				{
					cell.stretched(-2).draw(ColorF(1.0, 0.6));
				}
			}
		}
	}
	public:
	int32 player = 1;
	int32 posi_x = 0;
	int32 posi_y = 0;
	Game(const InitData& init)
		:IScene(init)
	{
		init_data[{4, 4}] = 2;
		init_data[{5, 5}] = 2;
		init_data[{5, 4}] = 1;
		init_data[{4, 5}] = 1;
	}
	void update() override
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				//セル
				const Rect cell(i * Cellsize, j * Cellsize, Cellsize, Cellsize);
				//セルの情報
				const int32 mark = init_data[i][j];

				//セルが空腹で置けるマスかつクリックされたとき
				if ((mark == 0) && cell.leftClicked())
				{
					posi_x = Cursor::Pos().x / Cellsize;
					posi_y = Cursor::Pos().y / Cellsize;
					//Print << Cursor::Pos();
					//Print << posi_x;
					//Print << posi_y;
					if (check(init_data, player, posi_x, posi_y))
					{

						//石を置く
						init_data[Cursor::Pos().x / Cellsize][Cursor::Pos().y / Cellsize] = player;
						set_board(init_data, player, Cursor::Pos().x / Cellsize, Cursor::Pos().y / Cellsize);
						//石の数を表示
						game_counter(init_data);
						//プレイヤーチェンジ
						player = chara(player);
					}
					else if (check(init_data, player, posi_x, posi_y) == 0 && skip(init_data, player) == 0)
					{
						player = chara(player);
						Print << U"スキップします";
					}
				}
			}
		}
	}
	void draw() const override
	{
		print_fence();
		print_cells();
	}
};


void Main()
{
	FontAsset::Register(U"Title", 100, Typeface::Black);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	Scene::SetBackground(Palette::Green);
	Window::SetTitle(U"Title");
	MyApp manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	constexpr Point offset(175, 30);
	//Board board;
	while (System::Update())
	{
		Transformer2D tr(Mat3x2::Translate(offset), true);
		if (!manager.update())
		{
			break;
		}
	}

}


