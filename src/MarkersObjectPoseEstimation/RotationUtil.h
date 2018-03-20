#ifndef ROTATIONUTIL_H
#define ROTATIONUTIL_H

#include <opencv2/core/mat.hpp>

cv::Mat eulerAnglesToRotationMatrix(cv::Vec3f &theta);
void rodriguesRotateByEulerAngles(cv::Vec3d &rvec, const float &pitch, const float &yaw, const float &roll);
void rodriguesRotateByEulerAngles(cv::Vec3d &rvec, const cv::Vec3d &euler);

void rodrigues2Euler(cv::Vec3d &rvec, float &pitch, float &yaw, float &roll);
void rodrigues2Euler(cv::Vec3d &rvec, float euler[3]);

#endif // ROTATIONUTIL_H
