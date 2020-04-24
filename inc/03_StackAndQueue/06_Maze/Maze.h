#ifndef _MAZE_H_
#define _MAZE_H_

#include <time.h>
#include "status.h"

static int maze_size;

typedef int MazeType;  //迷宫元素类型

/* 迷宫类型定义 */
typedef enum {
  WALL,      //外墙
  OBSTACLE,  //迷宫障碍
  WAY,       //路径
  DEADEND,   //死胡同
  ROUTE,     //迷宫通路
  PASSED_RIGHT,
  PASSED_DOWN,
  PASSED_LEFT,
  PASSED_UP,
} NodeType_e;

/* 方向定义 */
typedef enum {
  MAZE_DIRECTION_DEFAULT = 0,
  MAZE_DIRECTION_EAST,
  MAZE_DIRECTION_SOUTH,
  MAZE_DIRECTION_WEST,
  MAZE_DIRECTION_NORTH,
} maze_direct_e;

typedef struct maze_node_position_tag {
  int x;
  int y;
} maze_node_pos_t, *p_maze_node_pos_t;

typedef struct maze_node_tag {  
  int direc;
  maze_node_pos_t pos;
} maze_node_t, *p_maze_node_t;

typedef maze_node_t elemType_sq_stack;
#include "../src/03_StackAndQueue/01_SequenceStack/SequenceStack.cpp"

#ifdef __cplusplus
extern "C" {
#endif

// 初始化迷宫
void maze_init(std::vector<std::vector<MazeType> > &maze,
               maze_node_pos_t *start, maze_node_pos_t *end);

// 绘制迷宫
void maze_show(std::vector<std::vector<MazeType> > &maze);

// 进行寻路
Status maze_search(std::vector<std::vector<MazeType> > &maze,
                   maze_node_pos_t *start, maze_node_pos_t *end,
                   p_sq_stack_t route_Sq);

// 绘制路线
void maze_paint_route(std::vector<std::vector<MazeType> > &maze, 
                      sq_stack_t &route_sq);

#ifdef __cplusplus
}
#endif
#endif