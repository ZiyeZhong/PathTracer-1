#include "pathtracer.h"

#include "scene/light.h"
#include "scene/sphere.h"
#include "scene/triangle.h"


using namespace CGL::SceneObjects;

namespace CGL {

PathTracer::PathTracer() {
  gridSampler = new UniformGridSampler2D();
  hemisphereSampler = new UniformHemisphereSampler3D();

  tm_gamma = 2.2f;
  tm_level = 1.0f;
  tm_key = 0.18;
  tm_wht = 5.0f;
}

PathTracer::~PathTracer() {
  delete gridSampler;
  delete hemisphereSampler;
}

void PathTracer::set_frame_size(size_t width, size_t height) {
  sampleBuffer.resize(width, height);
  sampleCountBuffer.resize(width * height);
}

void PathTracer::clear() {
  bvh = NULL;
  scene = NULL;
  camera = NULL;
  sampleBuffer.clear();
  sampleCountBuffer.clear();
  sampleBuffer.resize(0, 0);
  sampleCountBuffer.resize(0, 0);
}

void PathTracer::write_to_framebuffer(ImageBuffer &framebuffer, size_t x0,
                                      size_t y0, size_t x1, size_t y1) {
  sampleBuffer.toColor(framebuffer, x0, y0, x1, y1);
}

Spectrum
PathTracer::estimate_direct_lighting_hemisphere(const Ray &r,
                                                const Intersection &isect) {
  // Estimate the lighting from this intersection coming directly from a light.
  // For this function, sample uniformly in a hemisphere.

  // make a coordinate system for a hit point
  // with N aligned with the Z direction.
  Matrix3x3 o2w;
  make_coord_space(o2w, isect.n);
  Matrix3x3 w2o = o2w.T();

  // w_out points towards the source of the ray (e.g.,
  // toward the camera if this is a primary ray)
  const Vector3D &hit_p = r.o + r.d * isect.t;
  const Vector3D &w_out = w2o * (-r.d);

  // This is the same number of total samples as
  // estimate_direct_lighting_importance (outside of delta lights). We keep the
  // same number of samples for clarity of comparison.
  int num_samples = scene->lights.size() * ns_area_light;
  Spectrum L_out;

  // TODO (Part 3): Write your sampling loop here
  // TODO BEFORE YOU BEGIN
  // UPDATE `est_radiance_global_illumination` to return direct lighting instead of normal shading
    
    for (int i = 0; i < num_samples; i++) {
        Vector3D sample = hemisphereSampler->get_sample();
        Vector3D d_sample = o2w * sample;
        Ray r_sample = Ray(hit_p + (EPS_D * d_sample), d_sample);
        Intersection intersection;
        bool intersect = bvh->intersect(r_sample, &intersection);
        if (intersect == true) {
            Spectrum emission = intersection.bsdf->get_emission();
            Spectrum f = isect.bsdf->f(w_out, sample);
            L_out += f * emission * cos_theta(sample) / (0.5 / PI);
        }
    }
    L_out = L_out / num_samples;
    return L_out;

    
//  return Spectrum(1.0);
}

Spectrum
PathTracer::estimate_direct_lighting_importance(const Ray &r,
                                                const Intersection &isect) {
  // Estimate the lighting from this intersection coming directly from a light.
  // To implement importance sampling, sample only from lights, not uniformly in
  // a hemisphere.

  // make a coordinate system for a hit point
  // with N aligned with the Z direction.
  Matrix3x3 o2w;
  make_coord_space(o2w, isect.n);
  Matrix3x3 w2o = o2w.T();

  // w_out points towards the source of the ray (e.g.,
  // toward the camera if this is a primary ray)
  const Vector3D &hit_p = r.o + r.d * isect.t;
  const Vector3D &w_out = w2o * (-r.d);
  Spectrum L_out;

    for (auto l = scene->lights.begin(); l != scene->lights.end(); l++) {
        int num_samples;
        if ((*l)->is_delta_light()) {
            num_samples = 1;
        } else {
            num_samples = ns_area_light;
        }
        
        for (int i = 0; i < num_samples; i++) {
            Vector3D wi;
            float distance;
            float pdf;
            Spectrum l_sample = (*l)->sample_L(hit_p, &wi, &distance, &pdf);
            Vector3D wi_w2o = w2o * wi;
            
            if (wi_w2o.z >= 0) {
                Ray r_sample = Ray(hit_p + (EPS_D * wi), wi);
                r_sample.max_t = distance;
                Intersection intersection;
                bool intersect = bvh->intersect(r_sample, &intersection);
                if (intersect == false) {
                    Spectrum f = isect.bsdf->f(w_out, wi_w2o);
                    L_out += l_sample * f * cos_theta(wi_w2o) / pdf;
                }
            }
        }
        L_out = L_out / num_samples;
    }
    return L_out;
}

Spectrum PathTracer::zero_bounce_radiance(const Ray &r,
                                          const Intersection &isect) {
  // TODO: Part 3, Task 2
  // Returns the light that results from no bounces of light
    
    return isect.bsdf->get_emission();

//  return Spectrum(1.0);
}

Spectrum PathTracer::one_bounce_radiance(const Ray &r,
                                         const Intersection &isect) {
  // TODO: Part 3, Task 3
  // Returns either the direct illumination by hemisphere or importance sampling
  // depending on `direct_hemisphere_sample`
    
    if (direct_hemisphere_sample == true) {
        return estimate_direct_lighting_hemisphere(r, isect);
    } else {
        return estimate_direct_lighting_importance(r, isect);
    }

//  return Spectrum(1.0);
}

Spectrum PathTracer::at_least_one_bounce_radiance(const Ray &r,
                                                  const Intersection &isect) {
  Matrix3x3 o2w;
  make_coord_space(o2w, isect.n);
  Matrix3x3 w2o = o2w.T();

  Vector3D hit_p = r.o + r.d * isect.t;
  Vector3D w_out = w2o * (-r.d);
    

    Spectrum L_out = one_bounce_radiance(r, isect);
    if (r.depth == 0) {return zero_bounce_radiance(r, isect);}
    if (r.depth <= 1) {
        return one_bounce_radiance(r, isect);
    } else {
//        if (r.depth == max_ray_depth) {L_out = Spectrum(0, 0, 0);}
        double p = 0.65;
        Vector3D wi;
        float pdf;
        Spectrum l = isect.bsdf->sample_f(w_out, &wi, &pdf);
        if (coin_flip(p)) {
            Vector3D direction = o2w * wi;
            Ray ray = Ray(hit_p + (EPS_D * direction), direction);
            ray.depth = r.depth - 1;
            Intersection intersection;
            bool intersect = bvh->intersect(ray, &intersection);
            if (intersect) {
                    L_out += (at_least_one_bounce_radiance(ray, intersection)) * l * cos_theta(wi) / pdf / p;
            }
        }
    }
    return L_out;
}

Spectrum PathTracer::est_radiance_global_illumination(const Ray &r) {
  Intersection isect;
  Spectrum L_out;

  // You will extend this in assignment 3-2.
  // If no intersection occurs, we simply return black.
  // This changes if you implement hemispherical lighting for extra credit.

  if (!bvh->intersect(r, &isect))
    return L_out;

  // The following line of code returns a debug color depending
  // on whether ray intersection with triangles or spheres has
  // been implemented.

  // REMOVE THIS LINE when you are ready to begin Part 3.
//  L_out = (isect.t == INF_D) ? debug_shading(r.d) : normal_shading(isect.n);

  // TODO (Part 3): Return the direct illumination.

  // TODO (Part 4): Accumulate the "direct" and "indirect"
  // parts of global illumination into L_out rather than just direct

  return zero_bounce_radiance(r, isect) + at_least_one_bounce_radiance(r, isect);
}

void PathTracer::raytrace_pixel(size_t x, size_t y) {

  // TODO (Part 1.1):
  // Make a loop that generates num_samples camera rays and traces them
  // through the scene. Return the average Spectrum.
  // You should call est_radiance_global_illumination in this function.
    
  // TODO (Part 5):
  // Modify your implementation to include adaptive sampling.
  // Use the command line parameters "samplesPerBatch" and "maxTolerance"

  int num_samples = ns_aa;          // total samples to evaluate
  Vector2D origin = Vector2D(x, y); // bottom left corner of the pixel

    Spectrum s = Spectrum();
    float s1 = 0;
    float s2 = 0;
    int n = 0;
    for (n = 0; n < num_samples; n++) {
        Vector2D sample = gridSampler->get_sample();
        double x_normal = (sample.x + x) / sampleBuffer.w;
        double y_normal = (sample.y + y) / sampleBuffer.h;
        Ray r = camera->generate_ray(x_normal, y_normal);
        r.depth = max_ray_depth;
        Spectrum s0 = est_radiance_global_illumination(r);
        float illm = s0.illum();
        s1 += illm;
        s2 += illm * illm;
        s = s + s0;
        if (n % samplesPerBatch == 0 && n > 0) {
            float mean = s1 / float(n);
            float variance = sqrt((1.0 / float(n - 1.0)) * (s2 - (s1 * s1) / float(n)));
            float i = 1.96 * variance / float(sqrt(n));
            if (i <= maxTolerance * mean) {
                break;
            }
        }
    }
    sampleCountBuffer[x + y * sampleBuffer.w] = n;
    s = s / (double)n;
    sampleBuffer.update_pixel(s, x, y);
    
//  sampleBuffer.update_pixel(Spectrum(0.2, 1.0, 0.8), x, y);
//  sampleCountBuffer[x + y * sampleBuffer.w] = num_samples;
}

} // namespace CGL
