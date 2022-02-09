#include <iostream>
#include <vector>
#include <string>
#include <deque>

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
    int x = rand() % (CONS_HT - 4);
    int y = rand() % (CONS_WD - 2);
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
  for (int i = 2; i < CONS_HT - 1; i++)
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

void print_score(int score, int body_length) {
  set_color(WHITE, B_BLACK);
  set_cursor_pos(0, 0);
  std::cout << "SCORE:";
  std::cout.width(6);
  std::cout << score;
  std::cout << "\tBODY:";
  std::cout.width(6);
  std::cout << body_length;
}

void print_snake(const std::deque<CurPos> &snake) {
  set_color(BLUE, B_BLACK);
  for (unsigned int i = 1; i < snake.size(); i++) {
    set_cursor_pos(snake[i].first, snake[i].second);
    std::cout << "*";
  }

  set_color(MAGENTA);
  set_cursor_pos(snake.front().first, snake.front().second);
  std::cout << "@";
}

int main()
{
  std::string s;
  std::cin >> s;
  std::cout << "Hello, World."
            << " ";
  std::cout << LIGHTBLACK << s << RESET << std::endl;

  std::cout << "\033[10;50H" << 343 << std::endl;

  return 0;
}
