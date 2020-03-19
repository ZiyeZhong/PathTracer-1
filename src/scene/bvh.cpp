#include "bvh.h"

#include "CGL/CGL.h"
#include "triangle.h"

#include <iostream>
#include <stack>

using namespace std;

namespace CGL {
namespace SceneObjects {

BVHAccel::BVHAccel(const std::vector<Primitive *> &_primitives,
                   size_t max_leaf_size) {

  primitives = std::vector<Primitive *>(_primitives);
  root = construct_bvh(primitives.begin(), primitives.end(), max_leaf_size);
}

BVHAccel::~BVHAccel() {
  if (root)
    delete root;
  primitives.clear();
}

BBox BVHAccel::get_bbox() const { return root->bb; }

void BVHAccel::draw(BVHNode *node, const Color &c, float alpha) const {
  if (node->isLeaf()) {
    for (auto p = node->start; p != node->end; p++) {
      (*p)->draw(c, alpha);
    }
  } else {
    draw(node->l, c, alpha);
    draw(node->r, c, alpha);
  }
}

void BVHAccel::drawOutline(BVHNode *node, const Color &c, float alpha) const {
  if (node->isLeaf()) {
    for (auto p = node->start; p != node->end; p++) {
      (*p)->drawOutline(c, alpha);
    }
  } else {
    drawOutline(node->l, c, alpha);
    drawOutline(node->r, c, alpha);
  }
}

//bool compare_x (std::vector<Primitive *>::iterator p1, std::vector<Primitive *>::iterator p2) {
//    return ((*p1)->get_bbox().centroid().x < (*p2)->get_bbox().centroid().x);
//}

BVHNode *BVHAccel::construct_bvh(std::vector<Primitive *>::iterator start,
                                 std::vector<Primitive *>::iterator end,
                                 size_t max_leaf_size) {

  // TODO (Part 2.1):
  // Construct a BVH from the given vector of primitives and maximum leaf
  // size configuration. The starter code build a BVH aggregate with a
  // single leaf node (which is also the root) that encloses all the
  // primitives.

  BBox bbox;
  int k = 0;
//    Vector3D centriod = Vector3D(0, 0, 0);

  for (auto p = start; p != end; p++) {
    BBox bb = (*p)->get_bbox();
    bbox.expand(bb);
      k += 1;
//      Vector3D c = bb.centroid();
//      centriod += (*p)->get_bbox().centroid();
//      b_centriod.expand(c);
  }
    
//    centriod = centriod / k;
//    float c_x = centriod.x;
//    cout << "c_x=" << c_x << endl;
  BVHNode *node = new BVHNode(bbox);
//    cout << "k=" << k << endl;
    
    if (k <= max_leaf_size) {
        node->start = start;
        node->end = end;
        return node;
    } else {
        double x = bbox.extent.x;
        double y = bbox.extent.y;
        double z = bbox.extent.z;
        double splitpoint;
        int left_num = 0;
        int right_num = 0;
        BBox lbbox;
        BBox rbbox;
        BVHNode *left = new BVHNode(lbbox);
        BVHNode *right = new BVHNode(rbbox);
        auto p1 = start;
        auto p2 = end - 1;
        
        if (x > y && x > z) {
            splitpoint = bbox.min.x + (x / 2);
//            cout << "splitpoint = " << splitpoint << endl;
            while (p1 != p2) {
                Vector3D p1_c = (*p1)->get_bbox().centroid();
//                cout << "c.x = " << p1_c.x << endl;
                if (p1_c.x > splitpoint) {
//                    BBox bb = (*p1)->get_bbox();
//                    rbbox.expand(bb);
                    swap(*p1, *p2);
                    p2 = p2 - 1;
                    right_num += 1;
                } else {
    //                cout << "left" << endl;
//                    BBox bb = (*p1)->get_bbox();
//                    lbbox.expand(bb);
                    left_num += 1;
                    p1 = p1 + 1;
                }
            }
            if ((*p1)->get_bbox().centroid().x < splitpoint) {
                p1 = p1 + 1;
            }
        } else if (y > x && y > z) {
            splitpoint = bbox.min.y + (y / 2);
//            cout << "splitpoint = " << splitpoint << endl;
            while (p1 != p2) {
                Vector3D p1_c = (*p1)->get_bbox().centroid();
//                cout << "c.y = " << p1_c.y << endl;
                if (p1_c.y > splitpoint) {
//                    BBox bb = (*p1)->get_bbox();
//                    rbbox.expand(bb);
                    swap(*p1, *p2);
                    p2 = p2 - 1;
                    right_num += 1;
                } else {
    //                cout << "left" << endl;
//                    BBox bb = (*p1)->get_bbox();
//                    lbbox.expand(bb);
                    left_num += 1;
                    p1 = p1 + 1;
                }
            }
            if ((*p1)->get_bbox().centroid().y < splitpoint) {
                p1 = p1 + 1;
            }
        } else {
            splitpoint = bbox.min.z + (z / 2);
//            cout << "splitpoint = " << splitpoint << endl;
            while (p1 != p2) {
                Vector3D p1_c = (*p1)->get_bbox().centroid();
//                cout << "c.z = " << p1_c.z << endl;
                if (p1_c.z > splitpoint) {
//                    BBox bb = (*p1)->get_bbox();
//                    rbbox.expand(bb);
                    swap(*p1, *p2);
                    p2 = p2 - 1;
                    right_num += 1;
                } else {
        //               cout << "left" << endl;
//                    BBox bb = (*p1)->get_bbox();
//                    lbbox.expand(bb);
                    left_num += 1;
                    p1 = p1 + 1;
                }
            }
            if ((*p1)->get_bbox().centroid().z < splitpoint) {
                p1 = p1 + 1;
                left_num += 1;
            } else {right_num += 1;}
        }
        if (left_num == 0 || right_num == 0) {
            p1 = start + floor(k/2);
        }
        
//        cout << "left" << left_num << endl;
//        cout << "right" << right_num << endl;
        left = construct_bvh(start, p1, max_leaf_size);
        right = construct_bvh(p1, end, max_leaf_size);
        node->l = left;
        node->r = right;
    }
  return node;
}

bool BVHAccel::has_intersection(const Ray &ray, BVHNode *node) const {
  // TODO (Part 2.3):
  // Fill in the intersect function.
  // Take note that this function has a short-circuit that the
  // Intersection version cannot, since it returns as soon as it finds
  // a hit, it doesn't actually have to find the closest hit.
    
    double t0 = ray.min_t;
    double t1 = ray.max_t;
    if (node->bb.intersect(ray, t0, t1) == false) {
        return false;
    }
    if (t0 > ray.max_t || t1 < ray.min_t) {return false;}
    if (node->isLeaf()) {
        for (auto p = node->start; p != node->end; p++){
            total_isects++;
            if ((*p)->has_intersection(ray)) {return true;}
        }
    }
    bool intersect_left = has_intersection(ray, node->l);
    bool intersect_right = has_intersection(ray, node->r);
    return (intersect_left || intersect_right);
//
//  for (auto p : primitives) {
//    total_isects++;
//    if (p->has_intersection(ray))
//      return true;
//  }
//  return false;
}

bool BVHAccel::intersect(const Ray &ray, Intersection *i, BVHNode *node) const {
  // TODO (Part 2.3):
  // Fill in the intersect function.
    
    bool hit = false;
    double t0 = ray.min_t;
    double t1 = ray.max_t;
    if (node->bb.intersect(ray, t0, t1) == false) {
        return hit;
    }
    if (t0 > ray.max_t || t1 < ray.min_t) {return hit;}
    Intersection *nearest = i;
    if (node->isLeaf()) {
        for (auto p = node->start; p != node->end; p++){
            total_isects++;
            if ((*p)->intersect(ray, i)) {
                hit = true;
                if (i->t < nearest->t) {nearest = i;}
            }
        }
        i = nearest;
        return hit;
    }
    total_isects++;
    Intersection *i_l = i;
    Intersection *i_r = i;
    bool intersect_left = intersect(ray, i_l, node->l);
    bool intersect_right = intersect(ray, i_r, node->r);
    if (i_l->t > i_r->t) {nearest = i_r;}
    else {nearest = i_l;}
    i = nearest;
    return (intersect_left || intersect_right);
    
//  bool hit = false;
//  for (auto p : primitives) {
//    total_isects++;
//    hit = p->intersect(ray, i) || hit;
//  }
//  return hit;
}

} // namespace SceneObjects
} // namespace CGL
