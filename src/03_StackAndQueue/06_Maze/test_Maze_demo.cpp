#include "demo_func.h"
#include "03_StackAndQueue/06_Maze/Maze.h"
using namespace std;

void test_Maze_demo() {
  int ret = OK;
  vector<vector<MazeType> >maze;
  maze_node_pos_t start = {0};
  maze_node_pos_t end = {0};
  // 初始化迷宫
  maze_init(maze, &start, &end);
  maze_show(maze);
  // 开始寻路
  sq_stack_t route_Sq = {0};
  init_stack_sq(&route_Sq);
  ret = maze_search(maze, &start, &end, &route_Sq);

  if (ret == OK) {
    // 绘制结果
    maze_paint_route(maze, route_Sq);
  }
  destroy_stack_sq(&route_Sq);
  return;
}