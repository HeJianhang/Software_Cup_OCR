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
using namespace cv;
using namespace cv::ml;
using namespace std;
using namespace classifier;

__declspec(dllexport) void init();
__declspec(dllexport) void destroy();
__declspec(dllexport) void ocr(const string imgPath, string& name, string& num);