#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

  // TODO (Part 2.2):
  // Implement ray - bounding box intersection test
  // If the ray intersected the bouding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.
    
    bool intersect = true;

    double t_x1 = (min.x - r.o.x) / r.d.x;
    double t_x2 = (max.x - r.o.x) / r.d.x;
    double t_y1 = (min.y - r.o.y) / r.d.y;
    double t_y2 = (max.y - r.o.y) / r.d.y;
    double t_z1 = (min.z - r.o.z) / r.d.z;
    double t_z2 = (max.z - r.o.z) / r.d.z;

    double t_x_min = std::min(t_x1, t_x2);
    double t_x_max = std::max(t_x1, t_x2);
    double t_y_min = std::min(t_y1, t_y2);
    double t_y_max = std::max(t_y1, t_y2);
    double t_z_min = std::min(t_z1, t_z2);
    double t_z_max = std::max(t_z1, t_z2);

    double newt0 = std::max({t_x_min, t_y_min, t_z_min});
    double newt1 = std::min({t_x_max, t_y_max, t_z_max});

    if (newt0 > newt1 || newt1 < 0) {intersect = false;}
    t0 = newt0;
    t1 = newt1;

  return intersect;
    

}

void BBox::draw(Color c, float alpha) const {

  glColor4f(c.r, c.g, c.b, alpha);

  // top
  glBegin(GL_LINE_STRIP);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
  glEnd();

  // bottom
  glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glEnd();

  // side
  glBegin(GL_LINES);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
  glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
