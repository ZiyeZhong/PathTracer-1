#include "triangle.h"

#include "CGL/CGL.h"
#include "GL/glew.h"

namespace CGL {
namespace SceneObjects {

Triangle::Triangle(const Mesh *mesh, size_t v1, size_t v2, size_t v3) {
  p1 = mesh->positions[v1];
  p2 = mesh->positions[v2];
  p3 = mesh->positions[v3];
  n1 = mesh->normals[v1];
  n2 = mesh->normals[v2];
  n3 = mesh->normals[v3];
  bbox = BBox(p1);
  bbox.expand(p2);
  bbox.expand(p3);

  bsdf = mesh->get_bsdf();
}

BBox Triangle::get_bbox() const { return bbox; }


bool Triangle::has_intersection(const Ray &r) const {
  // Part 1, Task 3: implement ray-triangle intersection
  // The difference between this function and the next function is that the next
  // function records the "intersection" while this function only tests whether
  // there is a intersection.

    Vector3D origin = r.o;
    Vector3D direction = r.d;
    Vector3D e2 = p2 - p1;
    Vector3D e3 = p3 - p1;

    Vector3D s = origin - p1;
    Vector3D s2 = cross(direction, e3);
    Vector3D s3 = cross(s, e2);
        
    double t = dot(s3, e3) / dot(s2, e2);
    double b2 = dot(s2, s) / dot(s2, e2);
    double b3 = dot(s3, direction) / dot(s2, e2);
    double b1 = 1 - b2 - b3;
        
    if (b1 >= 1 || b1 <= 0) {return false;}
    if (b2 >= 1 || b2 <= 0) {return false;}
    if (b3 >= 1 || b3 <= 0) {return false;}
    if (t > r.max_t || t < r.min_t) {return false;}
    
    r.max_t = t;
    return true;
    
}

bool Triangle::intersect(const Ray &r, Intersection *isect) const {
  // Part 1, Task 3:
  // implement ray-triangle intersection. When an intersection takes
  // place, the Intersection data should be updated accordingly

    if (has_intersection(r) == false) {
        return false;
    }    
    
//    Vector3D p = r.o + r.max_t * r.d;
    Vector3D e2 = p2 - p1;
    Vector3D e3 = p3 - p1;
    Vector3D s = r.o - p1;
    Vector3D s2 = cross(r.d, e3);
    Vector3D s3 = cross(s, e2);
    
//    double t = dot(s3, e3) / dot(s2, e2);
    double b2 = dot(s2, s) / dot(s2, e2);
    double b3 = dot(s3, r.d) / dot(s2, e2);
    double b1 = 1 - b2 - b3;

    Vector3D n = b1 * n1 + b2 * n2 + b3 * n3;
    n.normalize();
    isect->n = n;
    
    isect->primitive = this;
    isect->bsdf = get_bsdf();
//    r.max_t = t;
    isect->t = r.max_t;
    
  return true;
}

void Triangle::draw(const Color &c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_TRIANGLES);
  glVertex3d(p1.x, p1.y, p1.z);
  glVertex3d(p2.x, p2.y, p2.z);
  glVertex3d(p3.x, p3.y, p3.z);
  glEnd();
}

void Triangle::drawOutline(const Color &c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_LINE_LOOP);
  glVertex3d(p1.x, p1.y, p1.z);
  glVertex3d(p2.x, p2.y, p2.z);
  glVertex3d(p3.x, p3.y, p3.z);
  glEnd();
}

} // namespace SceneObjects
} // namespace CGL
