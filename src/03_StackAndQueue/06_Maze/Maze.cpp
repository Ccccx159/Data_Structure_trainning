#include "03_StackAndQueue/06_Maze/Maze.h"

void maze_init(std::vector<std::vector<MazeType> > &maze,
               maze_node_pos_t *start, maze_node_pos_t *end) {
  // 获取迷宫规模
  std::cout << "plz input maze_size=";
  std::cin >> maze_size;
  maze.resize(maze_size, std::vector<MazeType>(maze_size));

  // 用系统时间做随机数种子
  srand((unsigned)time(NULL));
  // 随机数越大，生成路径的可能性越大，迷宫中墙的生成概率为 1/randNum
  int randNum = 0;
  std::cout << "plz input randnum=";
  std::cin >> randNum;

  for (int rows = 0; rows < maze_size; rows++) {
    for (int cols = 0; cols < maze_size; cols++) {
      if (rows == 0 || cols == 0 || rows == maze_size - 1 ||
          cols == maze_size - 1) {
        maze[rows][cols] = WALL;  // 迷宫外墙
      } else {
        int tmp = rand() % randNum;  // 生成随机数填充迷宫
        if (!tmp) {
          maze[rows][cols] = OBSTACLE;  // 1/randNum的概率生成障碍
        } else {
          maze[rows][cols] = WAY;  // 其它地方加入路径
        }
      }
    }
  }

  // 迷宫入口
  start->x = 0;
  start->y = 1;
  // 迷宫出口
  end->x = maze_size - 1;
  end->y = maze_size - 2;
  // 开放入口和出口
  // 为了提高成功率，入口处和出口处临近的结点一直设为通路
  maze[start->y][start->x] = maze[start->y][start->x + 1] = WAY;
  maze[end->y][end->x] = maze[end->y][end->x - 1] = WAY;

  return;
}

// 绘制迷宫
static void maze_paint(std::vector<std::vector<MazeType> > &maze) {
  unsigned long ch_uni = 0;
  unsigned char ch_utf8[10] = {0};
  int size = 10;

  for (int rows = 0; rows < maze_size; rows++) {
    for (int cols = 0; cols < maze_size; cols++) {
      if (maze[rows][cols] == WALL) {
        printf(blue "* " defaultclr);
      } else if (maze[rows][cols] == OBSTACLE) {
        printf(yellow "+ " defaultclr);
      } else if (maze[rows][cols] == DEADEND) {
        ch_uni = 0x2718;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        printf(red "%s " defaultclr, ch_utf8);
      } else if (maze[rows][cols] == ROUTE) {
        ch_uni = 0x2605;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        printf(green "%s " defaultclr, ch_utf8);
      } else if (maze[rows][cols] == PASSED_RIGHT) {
        ch_uni = 0x2192;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        std::cout << ch_utf8 << " ";
      } else if (maze[rows][cols] == PASSED_DOWN) {
        ch_uni = 0x2193;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        std::cout << ch_utf8 << " ";
      } else if (maze[rows][cols] == PASSED_LEFT) {
        ch_uni = 0x2190;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        std::cout << ch_utf8 << " ";
      } else if (maze[rows][cols] == PASSED_UP) {
        ch_uni = 0x2191;
        enc_unicode_to_utf8_one(ch_uni, ch_utf8, size);
        std::cout << ch_utf8 << " ";
      } else {
        std::cout << "  ";
      }

      if (cols == maze_size - 1) {
        printf("\n");
      }
    }
  }
}

// 显示迷宫
void maze_show(std::vector<std::vector<MazeType> > &maze) {
  usleep(100*1000);
  system("clear");
  maze_paint(maze);  //在屏幕上画出迷宫
}

// 判断当前位置是否合法
static Status isValid(maze_node_pos_t &pt) {
  if (pt.x < 0 || pt.y < 0 || pt.x > maze_size - 1 || pt.y > maze_size - 1) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// 判断当前位置是否可以通过
static Status pass_or_not(maze_node_pos_t &pt,
                          std::vector<std::vector<MazeType> > &maze) {
  return (isValid(pt) && maze[pt.y][pt.x] == WAY) ? TRUE : FALSE;
}

// 生成route结点
static void setNodeOfRoute(elemType_sq_stack &node, maze_node_pos_t &cur,
                           maze_direct_e direc) {
  node.pos = cur;
  node.direc = direc;
}

// 前进至下一位置
static maze_node_pos_t next_position(maze_node_pos_t &cur,
                                     maze_direct_e direc) {
  maze_node_pos_t next = cur;
  switch (direc) {
    case MAZE_DIRECTION_EAST:
      next.x++;
      break;
    case MAZE_DIRECTION_SOUTH:
      next.y++;
      break;
    case MAZE_DIRECTION_WEST:
      next.x--;
      break;
    case MAZE_DIRECTION_NORTH:
      next.y--;
      break;
    default:
      LOG_ERROR("direction [%d] is invalid", direc);
      next.x = -1;
      next.y = -1;
      break;
  }
  return next;
}
// 进行寻路
Status maze_search(std::vector<std::vector<MazeType> > &maze,
                   maze_node_pos_t *start, maze_node_pos_t *end,
                   p_sq_stack_t route_Sq) {
  maze_node_pos_t curPos = (*start);
  elemType_sq_stack node_tmp = {0};
  do {
    // 判断当前位置是“通路（WAY）”，还是“障碍（OBSTACLE）”，以及当前位置是否越界
    if (TRUE == pass_or_not(curPos, maze)) {
      // 设置迷宫属性为当前探索方向
      maze[curPos.y][curPos.x] = PASSED_RIGHT;
      maze_show(maze);
      // 形成一个新的结点，并压入存储路线结点栈中暂存
      // 默认下一个路径结点向东搜索
      setNodeOfRoute(node_tmp, curPos, MAZE_DIRECTION_EAST);
      push_stack_sq(route_Sq, node_tmp);

      // 判断目前位置是否已到达终点
      if (curPos.x == end->x && curPos.y == end->y) {
        LOG_INFO("************search complete: SUCCESS************\n");
        return OK;
      } else {
        // 否则将向“东”前进一格进行探索
        curPos = next_position(curPos, MAZE_DIRECTION_EAST);
      }
    } else {
      if (FALSE == empty_stack_sq((*route_Sq))) {
        do {
          // 若栈不为空，且当前位置不通，则将位置回退一格
          pop_stack_sq(route_Sq, &node_tmp);
          if (node_tmp.direc == MAZE_DIRECTION_NORTH) {
            maze[node_tmp.pos.y][node_tmp.pos.x] = DEADEND;
            maze_show(maze);
          }
        } while (node_tmp.direc == MAZE_DIRECTION_NORTH &&
                 FALSE == empty_stack_sq((*route_Sq)));

        // 若当前位置还有其余方向未探索，则继续
        if (MAZE_DIRECTION_NORTH > node_tmp.direc) {
          node_tmp.direc++;
          push_stack_sq(route_Sq, node_tmp);
          maze[node_tmp.pos.y][node_tmp.pos.x]++;
          maze_show(maze);
          curPos = next_position(node_tmp.pos, (maze_direct_e)node_tmp.direc);
        }
      }
    }
  } while (FALSE == empty_stack_sq((*route_Sq)));

  LOG_ERROR("************search complete: FAILURE************\n");
  return ERROR;
}

// 绘制路线
void maze_paint_route(std::vector<std::vector<MazeType> > &maze, 
                      sq_stack_t &route_sq) {
  for (int i = 0; i < route_sq.stack_len; i++) {
    // 将路径绘制到对应迷宫位置上
    int row = 0, col = 0;
    row = route_sq.base[i].pos.y;
    col = route_sq.base[i].pos.x;
    maze[row][col] = ROUTE;
  }
  maze_show(maze);
}