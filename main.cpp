#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cassert>
#include <unistd.h>

#define RESET "\033[0m"
#define BLACK "\033[30m"     /* Black */
#define RED "\033[31m"       /* Red */
#define GREEN "\033[32m"     /* Green */
#define YELLOW "\033[33m"    /* Yellow */
#define BLUE "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"   /* Magenta */
#define CYAN "\033[36m"      /* Cyan */
#define WHITE "\033[37m"     /* White */
#define B_BLACK "\033[40m"   /* Background Black */
#define B_RED "\033[41m"     /* Background Red */
#define B_GREEN "\033[42m"   /* Background Green */
#define B_YELLOW "\033[43m"  /* Background Yellow */
#define B_BLUE "\033[44m"    /* Background Blue */
#define B_MAGENTA "\033[45m" /* Background Magenta */
#define B_CYAN "\033[46m"    /* Background Cyan */
#define B_WHITE "\033[47m"   /* Background White */
#define LIGHTRESET "\033[90m"
#define LIGHTBLACK "\033[90m"         /* Black */
#define LIGHTRED "\033[91m"           /* Red */
#define LIGHTGREEN "\033[92m"         /* Green */
#define LIGHTYELLOW "\033[93m"        /* Yellow */
#define LIGHTBLUE "\033[94m"          /* Blue */
#define LIGHTMAGENTA "\033[95m"       /* Magenta */
#define LIGHTCYAN "\033[96m"          /* Cyan */
#define LIGHTWHITE "\033[97m"         /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

constexpr int CONS_WD = 80;
constexpr int CONS_HT = 25;
constexpr int N_FOOD = 10;
constexpr int TERM = 50;
constexpr int EXT_FOOD = 1;
constexpr int POINT_FOOD = 100;

// down, right, up, left
constexpr int DX[] = {1, 0, -1, 0}; 
constexpr int DY[] = {0, 1, 0, -1};

typedef std::pair<int, int> CurPos;

void set_foreground_color(std::string color)
{
  std::cout << color;
}

void set_background_color(std::string color)
{
  std::cout << color;
}

void set_color(std::string fgc, std::string bgc = "")
{
  set_foreground_color(fgc);
  set_background_color(bgc);
}

void set_cursor_pos(int x, int y)
{
  std::cout << "\033[" << x << ";" << y << "H";
}

void add_foods(std::vector<CurPos> &foods, int cnt)
{
  for (int i = 0; i < cnt; i++)
  {
    int x = rand() % (CONS_HT - 4) + 2;
    int y = rand() % (CONS_WD - 2) + 1;
    foods.push_back(CurPos(x, y));
  }
}

void print_foods(const std::vector<CurPos> &foods)
{
  set_foreground_color(GREEN);
  for (unsigned int i = 0; i < foods.size(); i++)
  {
    set_cursor_pos(foods[i].first, foods[i].second);
    std::cout << "$";
  }
}

bool check_foods(std::vector<CurPos> &foods, int x, int y)
{
  for (int i = (int)foods.size() - 1; i >= 0; i--)
  {
    if (foods[i].first == x and foods[i].second == y)
    {
      foods.erase(foods.begin() + i);
      return true;
    }
  }
  return false;
}

void print_field()
{
  set_color(YELLOW, B_YELLOW);
  set_cursor_pos(1, 0);
  for (int j = 0; j < CONS_WD; j++)
  {
    std::cout << " ";
  }
  for (int i = 2; i < CONS_HT - 1; i++)
  {
    set_cursor_pos(i, 0);
    std::cout << " ";
    set_cursor_pos(i, CONS_WD - 1);
    std::cout << " ";
  }
  set_cursor_pos(CONS_HT - 2, 0);
  for (int j = 0; j < CONS_WD; j++)
  {
    std::cout << " ";
  }

  // field
  set_color(YELLOW, B_BLACK);
  for (int i = 2; i < CONS_HT - 2; i++)
  {
    set_cursor_pos(i, 1);
    for (int j = 1; j < CONS_WD - 1; j++)
    {
      std::cout << " ";
    }
  }

  set_cursor_pos(CONS_HT - 1, 0);
  for (int j = 0; j < CONS_WD; j++)
  {
    std::cout << " ";
  }
}

void print_score(int score, int body_length)
{
  set_color(WHITE, B_BLACK);
  set_cursor_pos(0, 0);
  std::cout << "SCORE:";
  std::cout.width(6);
  std::cout << score;
  std::cout << "\tBODY:";
  std::cout.width(6);
  std::cout << body_length;
}

void print_snake(const std::deque<CurPos> &snake)
{
  set_color(BLUE, B_BLACK);
  for (unsigned int i = 1; i < snake.size(); i++)
  {
    set_cursor_pos(snake[i].first, snake[i].second);
    std::cout << "*";
  }

  set_color(MAGENTA);
  set_cursor_pos(snake.front().first, snake.front().second);
  std::cout << "@";
}

void update_snake(std::deque<CurPos> &snake, int x, int y, bool extend)
{
  snake.push_front(CurPos(x, y));
  if (!extend)
  {
    set_cursor_pos(snake.back().first, snake.back().second);
    std::cout << " ";
    snake.pop_back();
  }
}

bool on_field(int x, int y)
{
  if (x < 2 or CONS_HT - 2 <= x)
    return false;
  if (y < 1 or CONS_WD - 1 <= x)
    return false;
  return true;
}

bool collapsed(const std::deque<CurPos> &snake)
{
  int x = snake[0].first;
  int y = snake[0].second;
  if (!on_field(x, y))
    return true;
  for (int i = 1; i < snake.size(); i++)
  {
    if (snake[i].first == x and snake[i].second == y)
      return true;
  }
  return false;
}

// return true if no body is there
bool check_body(const std::deque<CurPos> &snake, int dx, int dy)
{
  if (snake.size() < 2)
    return true;
  return snake[0].first + dx != snake[1].first or snake[0].second + dy != snake[1].second;
}

int main()
{
  srand((int)time(0));

  for (;;)
  {
    int score = 0;
    int dx = 0, dy = 1;
    int x = CONS_HT / 2;
    int y = CONS_WD / 2;
    std::deque<CurPos> snake;
    snake.push_back(CurPos(x, y - 2));
    snake.push_back(CurPos(x, y - 1));
    snake.push_back(CurPos(x, y));

    std::vector<CurPos> foods;
    add_foods(foods, N_FOOD);

    print_field();
    print_foods(foods);
    print_snake(snake);
    print_score(score, snake.size());
    int eating = 0;

    for (int cnt = 0;; cnt++)
    {
      char input; std::cin >> input;
      int next_idx;
      switch (input)
      {
      case 'j':
        next_idx = 0;
        break;
      case 'l':
        next_idx = 1;
        break;
      case 'k':
        next_idx = 2;
        break;
      case 'h':
        next_idx = 3;
        break;
      default:
        assert(false);
      }
      sleep(2);
    }
  }

  return 0;
}
