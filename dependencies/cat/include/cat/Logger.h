#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <memory>
#include "cat/TextureType.h"
#include "cat/AssetType.h"

namespace cat
{
struct Texture;
template<typename T, unsigned int N>
struct Matrix;
template<typename T, unsigned int N>
struct Vector;
struct Mesh;
struct Shading;
struct Renderable;
struct Entity;
struct EntityHandle;
struct TextureResource;

/*
NOT SAFE FOR MULTITHREADING
 */
class Logger
{
private:
    static std::ofstream logFile;
    static std::stringstream logStream;
	static std::stringstream logFileStream;
	
	static void LogOne(char32_t chr) 			
	{ logStream << "U+" << std::hex << static_cast<uint32_t>(chr) << std::dec;}
	
	static void LogOne(const std::string& msg)	
	{ logStream << msg; }

    static void LogOne(const char* msg)			
	{ logStream << msg; }

    
	static void LogOne(bool bVal)					
	{ logStream << (bVal ? "TRUE" : "FALSE"); }

    
	static void LogOne(int number)					
	{ logStream << number; }
	
    static void LogOne(unsigned int number)			
	{ logStream << number; }

	static void LogOne(long number)					
	{ logStream << number; }
    
	static void LogOne(unsigned long long number)
	{ logStream << number; }

	static void LogOne(uint64_t number)
	{ logStream << number; }
    
    static void LogOne(float number)
	{ logStream << number; }
	
	static void LogOne(double number)
	{ logStream << number; }
	
	static void LogOne(Entity entity);
	
	static void LogOne(EntityHandle entity);
	
	
	static void LogOne(void* ptr)
	{ logStream << ptr; }
	
	template<typename T>
	static void LogOne(std::shared_ptr<T> ptr)
	{ logStream << "address: " << ptr.get() << " ref count: " << ptr.use_count(); }
	
	static void LogOne(AssetType assetType)
	{ logStream << assetType; }
	
	static void LogOne(TextureType textureType)
	{ logStream << textureType; }
	    
		
	static void LogOne(TextureResource textureResource);
		
    static void LogOne(Texture thisTexture);

    static void LogOne(const Mesh& mesh);
	
	static void LogOne(const Shading& shading, const Renderable& renderable);
	
    template<typename T, unsigned int N>
    static void LogOne(const Vector<T, N>& vector)
    {
        logStream << vector.ToString() << std::endl;
    }

    template<typename T, unsigned int N>
    static void LogOne(const Matrix<T, N>& mat)
    {
        logStream << mat.ToString() << std::endl;
    }
	
public:
	static bool isError;
	
    Logger();
    ~Logger();
    
	template<typename... Args>
	static void Log(Args&&... args)
	{
		(LogOne(std::forward<Args>(args)), ...);
	}
	
    static void Init();
    
    static void Close();

    static void Log();

    static void Log(const char* file, int line, const char* func);

};
}

#define error(...)          \
do {                        \
    cat::Logger::isError = true;	\
    LOG(__VA_ARGS__);       \
    cat::Logger::Close();  	\
    std::exit(EXIT_FAILURE);\
} while (0)
#define LOG(...) do { cat::Logger::Log(__FILE__, __LINE__, __func__); cat::Logger::Log(__VA_ARGS__);cat::Logger::Log(); } while(0)
