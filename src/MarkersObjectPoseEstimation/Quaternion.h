#ifndef QUATERNION_H
#define QUATERNION_H

void euler2Quaternion(const float &pitch, const float &yaw, const float &roll, float *quat);
void quaternion2Euler(const float *q, float &pitch, float &yaw, float &roll);
float degrees2Radians(const float &degrees);
float radians2Degrees(const float &radians);

#ifdef USE_OPENCV
inline void euler2Quaternion(const cv::Vec3f &euler, float *quat);
inline void quaternion2Euler(const float *quat, cv::Vec3f &euler);
#endif

#endif // QUATERNION_H
