#pragma once
#include "GlobalInclude.h"
#include <memory>
#include <map>

#define D3_WORLD_TRANSFORM "d3_world_transform"
#define D3_OBSERVER_PLANE "d3_to_observer_plane"
#define D3_VIEW_POSITION "d3_view_position"
#define D3_LIGHT_DIRECTION "d3_light_direction"
#define D3_PROJECTION_MATRIX "d3_projection_matrix"

#define IMAGE_TEXTURE_SLOT "image_texture_slot"
#define TEXT_TEXTURE_SLOT "text_texture_slot"

#define SKYBOX_PROJECTION_MATRIX "skybox_projection_matrix"
#define SKYBOX_TEXTURE_SLOT "skybox_texture_slot"
#define SKYBOX_VIEW_MATRIX "skybox_view_matrix"

enum UniformType {
  Float,
  Int,
  Bool,
  Vec2,
  Vec3,
  Vec4,
  Vec2i,
  Vec3i,
  Vec4i,
  Vec2b,
  Vec3b,
  Vec4b,
  Mat2,
  Mat3,
  Mat4,
  sampler1D,
  sampler2D,
  sampler3D,
  samplerCube,
  sampler2DArray,
  samplerCubeArray,
};

struct Uniform{
    int location;
    UniformType type;
    std::string name;
    //Possible to add last value
};

class Shader{
public:
    std::shared_ptr<unsigned int> shaderKey;
    std::map<std::string, Uniform> uniforms;
    std::string name;

    Shader(std::string name);

    void AddUniform(std::string commonName, std::string realName, UniformType dataType);

    void AssignDataToUniform(std::string commonName, void* data);
};