#pragma once
#include <memory>
#include <map>

namespace cat
{
#define WORLD_TRANSFORM "world_transform"
#define OBSERVER_PLANE "to_observer_plane"
#define VIEW_POSITION "view_position"
#define LIGHT_DIRECTION "light_direction"

#define POS_OFFSET "pos_offset"
#define TILE_SIZE "tile_size"

#define PROJECTION_MATRIX "projection_matrix"
#define TEXTURE_SLOT "texture_slot"

#define DEBUG_COLOR "debug_color"

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
	
	~Shader();

    void AddUniform(std::string commonName, std::string realName, UniformType dataType);

	bool HasUniform(std::string commonName);

    void AssignDataToUniform(std::string commonName, void* data);
};
}
