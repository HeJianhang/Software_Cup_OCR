#pragma once
#include <stdio.h>
#include <tchar.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo/photo.hpp"
#include <algorithm> 
#include <vector>
#include <list>
#include <stack>
#include "opencv2/features2d.hpp" 
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include <yolo_v2_class.hpp>
#include <string>
#include <classifier.h>
#include <windows.h>
using namespace cv;
using namespace cv::ml;
using namespace std;
using namespace classifier;
__declspec(dllexport) std::string& trim(std::string &s);
__declspec(dllexport) void init(const string& path1, const string& path2, const string& path3, const string& path4);
__declspec(dllexport) void destroy();
__declspec(dllexport) void ocr(const string imgPath, string& name, string& num);
__declspec(dllexport) void setIsStop(bool);