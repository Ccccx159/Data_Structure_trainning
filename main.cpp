#ifdef _DEBUG
#pragma comment(lib, "opencv_world440d.lib")
#pragma comment(lib, "jsoncppd.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#pragma comment(lib, "jsoncpp.lib")
#endif

#include <direct.h>
#include <io.h>
#include <json/json.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

#define MAX_SIDES_OF_POLY (30)
#define MAX_SHIELDED_AREA_NUM (10)

Mat srcImg;
Mat tmpImg;
std::string winName;
int caliNum = 0;

typedef struct myPoint_tag {
  int x;
  int y;
} myPoint_t;

typedef struct myLine_tag {
  myPoint_t start;
  myPoint_t end;
} myLine_t;

typedef struct myPoly_tag {
  int ptNum;
  myPoint_t point[MAX_SIDES_OF_POLY];
} myPoly_t;

typedef struct cali_param_tag {
  myLine_t verticalLine[3];
  myLine_t horizontalLine;
  int verLine;
  int horLine;
  myPoly_t detectArea;
  int extAreaNum;
  myPoly_t shieldedArea[MAX_SHIELDED_AREA_NUM];
} cali_param_t;

int listFiles(std::string &dir, std::string &file) {
  using namespace std;
  dir.append("\\*");
  intptr_t handle;
  struct _finddata_t findData;
  memset(&findData, 0, sizeof(struct _finddata_t));

  handle = _findfirst(dir.c_str(), &findData);  // 查找目录中的第一个文件
  if (handle == -1) {
    cout << "Failed to find first file!\n";
    return -1;
  }
  int ret = 0;
  do {
    if (strcmp(findData.name, ".") == 0 ||
        strcmp(findData.name, "..") == 0) {  // 是否是子目录并且不为"."或".."
      continue;
    } else if (findData.attrib & _A_SUBDIR) {
      string newDir = dir;
      newDir = newDir + "\\" + findData.name;
      listFiles(newDir, file);
    } else {
      if (findData.name == file) {
        return 0;
      }
    }
  } while (_findnext(handle, &findData) == 0);  // 查找目录中的下一个文件

  _findclose(handle);  // 关闭搜索句柄

  return -1;
}

int getLabelFile(std::string &vPath, std::string &labelFile) {
  size_t pos = vPath.rfind("\\");
  std::string path;
  if (pos != std::string::npos) {
    path = vPath.substr(0, pos);
  }
  labelFile = vPath.substr(pos + 1) + ".label.json";
  if (0 != listFiles(path, labelFile)) {
    return -1;
  }

  return 0;
}

void onMouse4Line(int event, int x, int y, int flags, void *privData) {
  cali_param_t *cali = (cali_param_t *)privData;
  static Point prePt = {-1, -1};
  static Point curPt = {-1, -1};
  char coordinate[12] = {0};
  if (EVENT_LBUTTONDOWN == event) {
    srcImg.copyTo(tmpImg);
    prePt = Point(x, y);
    snprintf(coordinate, 12, "(%d, %d)", x, y);
    circle(tmpImg, prePt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
    std::string strCoordinate = coordinate;
    putText(tmpImg, strCoordinate, prePt, FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(0, 0, 255), 2);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
  } else if (EVENT_MOUSEMOVE == event && (flags & EVENT_FLAG_LBUTTON)) {
    srcImg.copyTo(tmpImg);
    curPt = Point(x, y);
    line(tmpImg, prePt, curPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
    imshow(winName, tmpImg);
  } else if (EVENT_LBUTTONUP == event) {
    srcImg.copyTo(tmpImg);
    curPt = Point(x, y);
    snprintf(coordinate, 12, "(%d, %d)", x, y);
    circle(tmpImg, curPt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
    std::string strCoordinate = coordinate;
    putText(tmpImg, strCoordinate, curPt, FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(0, 0, 255), 2);
    line(tmpImg, prePt, curPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
    switch (caliNum) {
      case 0:
        cali->verticalLine[0].start.x = prePt.x;
        cali->verticalLine[0].start.y = prePt.y;
        cali->verticalLine[0].end.x = curPt.x;
        cali->verticalLine[0].end.y = curPt.y;
        break;
      case 1:
        cali->verticalLine[1].start.x = prePt.x;
        cali->verticalLine[1].start.y = prePt.y;
        cali->verticalLine[1].end.x = curPt.x;
        cali->verticalLine[1].end.y = curPt.y;
        break;
      case 2:
        cali->verticalLine[2].start.x = prePt.x;
        cali->verticalLine[2].start.y = prePt.y;
        cali->verticalLine[2].end.x = curPt.x;
        cali->verticalLine[2].end.y = curPt.y;
        break;
      case 3:
        cali->horizontalLine.start.x = prePt.x;
        cali->horizontalLine.start.y = prePt.y;
        cali->horizontalLine.end.x = curPt.x;
        cali->horizontalLine.end.y = curPt.y;
        break;
      default:
        break;
    }
    caliNum++;
  }
}

void onMouseDetectArea(int event, int x, int y, int flags, void *privData) {
  cali_param_t *cali = (cali_param_t *)privData;
  static Point firstPt = {-1, -1};
  static bool flag = false;
  static Point prePt = {-1, -1};
  static Point curPt = {-1, -1};
  char coordinate[12] = {0};
  if (EVENT_LBUTTONDOWN == event) {
    srcImg.copyTo(tmpImg);
    if (false == flag) {
      firstPt = Point(x, y);
      prePt = Point(x, y);
      circle(tmpImg, prePt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
      flag = true;
    } else {
      curPt = Point(x, y);
      circle(tmpImg, curPt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
      line(tmpImg, prePt, curPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
      prePt = Point(x, y);
    }

    snprintf(coordinate, 12, "(%d, %d)", x, y);
    std::string strCoordinate = coordinate;
    putText(tmpImg, strCoordinate, prePt, FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(0, 0, 255), 2);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
    // 填充标定结构体
    cali->detectArea.point[cali->detectArea.ptNum].x = x;
    cali->detectArea.point[cali->detectArea.ptNum].y = y;
    cali->detectArea.ptNum++;
  } else if (EVENT_RBUTTONDOWN == event) {
    srcImg.copyTo(tmpImg);
    line(tmpImg, prePt, firstPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
  }
}

void onMouseExtArea(int event, int x, int y, int flags, void *privData) {
  cali_param_t *cali = (cali_param_t *)privData;
  static Point firstPt = {-1, -1};
  static bool flag = false;
  static Point prePt = {-1, -1};
  static Point curPt = {-1, -1};
  char coordinate[12] = {0};
  if (EVENT_LBUTTONDOWN == event) {
    srcImg.copyTo(tmpImg);
    if (false == flag) {
      firstPt = Point(x, y);
      prePt = Point(x, y);
      circle(tmpImg, prePt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
      flag = true;
    } else {
      curPt = Point(x, y);
      circle(tmpImg, curPt, 3, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
      line(tmpImg, prePt, curPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
      prePt = Point(x, y);
    }

    snprintf(coordinate, 12, "(%d, %d)", x, y);
    std::string strCoordinate = coordinate;
    putText(tmpImg, strCoordinate, prePt, FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(0, 0, 255), 2);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
    // 填充标定结构体
    cali->shieldedArea[cali->extAreaNum]
        .point[cali->shieldedArea[cali->extAreaNum].ptNum]
        .x = x;
    cali->shieldedArea[cali->extAreaNum]
        .point[cali->shieldedArea[cali->extAreaNum].ptNum]
        .y = y;
    cali->shieldedArea[cali->extAreaNum].ptNum++;
  } else if (EVENT_RBUTTONDOWN == event) {
    srcImg.copyTo(tmpImg);
    line(tmpImg, prePt, firstPt, Scalar(255, 0, 0), 3, LINE_AA, 0);
    imshow(winName, tmpImg);
    tmpImg.copyTo(srcImg);
    cali->extAreaNum++;
    flag = false;
  }
}

int videoLabelFunc(VideoCapture &v, Mat &frame, int w, int h, std::string path,
                   cali_param_t *cali) {
  std::cout << "开始标定！" << std::endl;

  // 三竖一横标定
  std::cout << "开始三竖一横标定！" << std::endl;
  std::cout << "按空格开始标定！" << std::endl;
  winName = "caliWin";
  namedWindow(winName);
  Mat tmpFrame;
  while (true) {
    v >> frame;
    imshow(winName, frame);
    int key = waitKey(1);
    if (' ' == key) break;
  }
  frame.copyTo(srcImg);

  setMouseCallback(winName, onMouse4Line, (void *)cali);
  waitKey(0);
  if (caliNum < 4) {
    std::cout << "三竖一横标定失败，请重新尝试！" << std::endl;
  }

  std::cout << "三竖一横标定成功！" << std::endl;
  printf("v1: (%d, %d), (%d, %d)\n", cali->verticalLine[0].start.x,
         cali->verticalLine[0].start.y, cali->verticalLine[0].end.x,
         cali->verticalLine[0].end.y);
  printf("v2: (%d, %d), (%d, %d)\n", cali->verticalLine[1].start.x,
         cali->verticalLine[1].start.y, cali->verticalLine[1].end.x,
         cali->verticalLine[1].end.y);
  printf("v3: (%d, %d), (%d, %d)\n", cali->verticalLine[2].start.x,
         cali->verticalLine[2].start.y, cali->verticalLine[2].end.x,
         cali->verticalLine[2].end.y);
  printf("h : (%d, %d), (%d, %d)\n", cali->horizontalLine.start.x,
         cali->horizontalLine.start.y, cali->horizontalLine.end.x,
         cali->horizontalLine.end.y);
  std::cout << "输入竖线实际高度：";
  std::cin >> cali->verLine;
  std::cout << "输入横线实际长度：";
  std::cin >> cali->horLine;

  // 绘制检测区
  std::cout << "开始绘制检测区！" << std::endl;
  frame.copyTo(srcImg);
  imshow(winName, srcImg);
  setMouseCallback(winName, onMouseDetectArea, (void *)cali);
  waitKey(0);

  std::cout << "检测区绘制成功！" << std::endl;
  std::cout << "detect area coordinate:" << std::endl;
  for (int i = 0; i < cali->detectArea.ptNum; i++) {
    std::cout << cali->detectArea.point[i].x << " "
              << cali->detectArea.point[i].y << std::endl;
  }

  // 绘制屏蔽区
  int extFlag = 0;
  std::cout << "是否配置屏蔽区（是：“1”，否：“0”）：";
  std::cin >> extFlag;
  if (1 == extFlag) {
    /*frame.copyTo(srcImg);*/
    setMouseCallback(winName, onMouseExtArea, (void *)cali);
    waitKey(0);
    std::cout << "sheilded area num is [" << cali->extAreaNum
              << "]:" << std::endl;
    for (int aIdx = 0; aIdx < cali->extAreaNum; aIdx++) {
      std::cout << "sheilded area [" << aIdx << "]" << std::endl;
      for (int pIdx = 0; pIdx < cali->shieldedArea[aIdx].ptNum; pIdx++) {
        std::cout << cali->shieldedArea[aIdx].point[pIdx].x << ' '
                  << cali->shieldedArea[aIdx].point[pIdx].y << std::endl;
      }
    }
  }

  std::cout << "标定结束！" << std::endl;
  // 以json格式写入标定文件
  Json::Value jv;

  return 0;
}

int main(int argc, char *argv[]) {
  std::string vPath;
  std::cout << "input video path:";
  std::cin >> vPath;
  VideoCapture v;
  v.open(vPath);
  if (!v.isOpened()) {
    std::cout << "error! \t" << vPath << " can't open!" << std::endl;
  } else {
    std::cout << vPath << " open Success!" << std::endl;
  }

  int w = v.get(CAP_PROP_FRAME_WIDTH);
  int h = v.get(CAP_PROP_FRAME_HEIGHT);
  int fNum = v.get(CAP_PROP_FRAME_COUNT);
  printf("video's width [%d], height [%d], frameNum [%d]\n", w, h, fNum);

  Mat frame;
  // 跳过前10帧
  for (int fIdx = 0; fIdx < 10; fIdx++) {
    v >> frame;
  }

  cali_param_t cali = {0};
  // 标定函数
  std::string labelFile;
  if (0 != getLabelFile(vPath, labelFile)) {
    videoLabelFunc(v, frame, w, h, vPath, &cali);
  } else {
    std::cout << "标定文件已存在！" << std::endl;
  }

  return 0;
}