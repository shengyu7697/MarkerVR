#ifndef ROTATIONUTIL_H
#define ROTATIONUTIL_H

// Base on OpenCV's Mat and Vec
#include <opencv2/core/mat.hpp>

// Euler Angles to Rotation Matrix
cv::Mat euler2matrix(cv::Vec3f &theta);  // TODO not test yet

// Rotation Matrix to Euler Angles
cv::Vec3f matrix2Euler(const cv::Mat &R);

// Rodrigues to Euler
void rodrigues2Euler(cv::Vec3d &rvec, float &pitch, float &yaw, float &roll);
void rodrigues2Euler(cv::Vec3d &rvec, float euler[3]);

// Euler to Rodrigues
// TODO


// Other
void rodriguesRotateByEuler(cv::Vec3d &rvec, const float &pitch, const float &yaw, const float &roll);
void rodriguesRotateByEuler(cv::Vec3d &rvec, const cv::Vec3d &euler);

#endif // ROTATIONUTIL_H
