# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# define S 12
#define chara(player) (3-(player)) 
/*
//盤面を生成する関数
void init_board(int in_board[S][S])
{
	static int init_data[S][S] =
	{{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
	memcpy(in_board, init_data, sizeof(init_data));
	}
//盤面を描画する関数
void print_board(int board[S][S])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (board[i][j] == 1)
			{
				Circle(i*30+40,j*30+40,10).draw(Palette::White);
			}
			else if (board[i][j] == 2)
			{
				Circle(i * 30+40, j * 30+40, 10).draw(Palette::Black);
			}
		}
	}
}
//ひっくり返す関数:引数(盤面の情報,手番,置いたマス,探索する方向)
int count_turn(int board[S][S], int player,int p,int q, int d, int e)
{
	int i;
	//置いたマスから相手の石の数をカウント
	for (i = 1; board[p + i * d][q + i * e]==chara(player); i++) {};
	//カウントした後に自分の石で挟まれているか
	if (board[p + i * d][q + i * e] == chara(player))
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
//打った手がルール的にあっているかを確認する
//playerが(p,q)のマスに石が置けるかどうかを返す
int  check(int board[S][S], int player, int p, int q)
{
	//盤面の中かどうか
	if (p < 1 || p>10 || q < 1 || q > 10) return 0;
	//石がすでに置かれていないかどうか
	if (board[p][q] != 0) return 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (count_turn(board, player, p, q, i, j)) return 1;
		}
	}
	return 0;
}
//置ける石があるかどうかを確認する
int skip(int board[S][S], int player)
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (check(board, player, i, j)) return 1;
		}
	}
	return 0;
}
//手を入力する関数
void get_move(int board[S][S], int player, int *virtical, int *side)
{
	printf("Player:%d\n", player);
	Print << U"差し手を入力してください";
	while (1)
	{
		scanf_s("%d %d", virtical, side);
		if (check(board, player, *virtical, *side)) return ;
	}
}
//盤面を裏返す関数
void set_board(int board[S][S],int player,int p,int q)
{
	int count = 0;
	for (int d = -1; d < 2; d++)
	{
		for (int e = -1; e < 2; e++)
		{
			if (d == 0 && e == 0) continue;
			count = count_turn(board, player, p, q, d, e);
			for (int i = 0; i <= count; i++)
			{
				//裏返す
				board[p + i * d][q + i * e] = player;
			}
		}
	}
	//石を置く
	board[p][q] = player;
}
//石の数を数え上げる関数
void count_stone(int board[S][S], int *c1, int *c2)
{
	*c1 = 0;
	*c2 = 0;
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (board[i][j] == 1)
			{
				(*c1)++;
			}
			else
			{
				(*c2)++;
			}
		}
	}
}
//ゲームの進行を管理する関数
int game()
{
	int p = 0;
	int q = 0;
	int player = 1;
	int c1 = 0;
	int c2 = 0;
	int board[S][S];
	init_board(board);
	print_board(board);
	get_move(board, player, &p, &q);
	while (1)
	{
		//スキップおよび終了判定
		if (!skip(board, player))
		{
			Print << U"スキップします";
			player = chara(player);
			if (!skip(board, player))
			{
				Print << U"スキップします";
				break;
			}
		}
	}
	set_board(board, player, p, q);
	player = chara(player);
	count_stone(board, &c1, &c2);
	printf("白:%d 黒:%d", c1, c2);
}
*/
//ひっくり返す関数:引数(盤面の情報,手番,置いたマス,探索する方向)
int count_turn(Grid<int32>& init_data, int player, int p, int q, int d, int e)
{
	int i=0;
	//置いたマスから相手の石の数をカウント
		for (i = 1; init_data[p + i * d][q + i * e] == chara(player); i++)
		{
			if (p + (i+1) * d == -1) return 0;
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
class Board
{
private:
	//10x10の盤面
	Grid<int32> init_data = Grid<int32>(12, 12);

	//格子を描く
	void print_fence() const
	{
		for (int i=0;i<11;i++)
		{
			Line(i * Cellsize , 0, i * Cellsize , 10 * Cellsize ).draw(4, Palette::White);
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
	//セルの大きさ
	static constexpr int32 Cellsize = 50;
	static constexpr int32 width = 12;
	static constexpr int32 hight = 12;
	int32 player = 1;
	int32 posi_x = 0;
	int32 posi_y = 0;
	void update()
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
					Print << Cursor::Pos();
					Print << posi_x;
					Print << posi_y;
					if (check(init_data, player, posi_x, posi_y))
					{
						
						//石を置く
						init_data[Cursor::Pos().x / Cellsize][Cursor::Pos().y / Cellsize] = player;
						set_board(init_data, player, Cursor::Pos().x / Cellsize, Cursor::Pos().y / Cellsize);
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
	Board()
	{
		init_data[{4, 4}] = 2;
		init_data[{5, 5}] = 2;
		init_data[{5, 4}] = 1;
		init_data[{4, 5}] = 1;
	}
	//描画関数
	void draw() const
	{
		print_fence();
		print_cells();
	}
};
void Main()
{
	Board board;
	Scene::SetBackground(Palette::Green);
	constexpr Point offset(175, 30);
	while (System::Update())
	{
		Transformer2D tr(Mat3x2::Translate(offset), true);
		board.draw();
		board.update();
	}

}


