#include "demo_func.h"
#include "Maze.cpp"
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
    for (int i = 0; i < route_Sq.stack_len; i++) {
      // 输出路径坐标
      int row = 0, col = 0;
      row = route_Sq.base[i].pos.y;
      col = route_Sq.base[i].pos.x;
      if(i != route_Sq.stack_len - 1) {
        printf("(%d, %d)->", route_Sq.base[i].pos.x, route_Sq.base[i].pos.y);
      } else {
        printf("(%d, %d)\n", route_Sq.base[i].pos.x, route_Sq.base[i].pos.y);
      }
    }
  }
  destroy_stack_sq(&route_Sq);
  return;
}