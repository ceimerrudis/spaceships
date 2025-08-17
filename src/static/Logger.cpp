#include "GlobalInclude.h"
#include "Logger.h"
#include "AdvancedMath.h"
#include "ObjectLoader.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;

std::ofstream Logger::logFile;
std::stringstream Logger::logStream;

Logger::Logger()
{
    error("Logger is a static class and should not be initialized");
}

Logger::~Logger()
{
}

void Logger::Close()
{
    logFile << std::endl << "Logfile closing" << std::endl;
    logFile.close();
}

void Logger::Init()
{
    logFile.open("log.txt");
    if(!logFile.is_open())
    {
        std::cerr << "failed to create log file";
    }
    logStream.clear();
}

void Logger::Log()
{
    #if defined(DEBUG) && (DEBUG == 1)
        std::cout << logStream.str();
    #endif
    logFile << logStream.str();
    logStream.str(std::string());
    logStream.clear();
}

void Logger::Log(const char* file, int line, const char* func)
{
    #if DEBUG_LOG_SOURCE
        logStream << "file: " << file << " line: " << line << " func: " << func << std::endl;
    #endif
}

void Logger::Log(bool bVal)
{
    if(bVal)
    {
        logStream << "TRUE" <<  std::endl;
    }
    else
    {
        logStream << "FALSE" <<  std::endl;
    }
}

void Logger::Log(const std::string& msg, float data)
{
    logStream << msg <<  data << std::endl;
}

void Logger::Log(const string& msg)
{
    logStream << msg << std::endl;
}

void Logger::Log(const char* msg)
{
    logStream << msg << std::endl;
}

void Logger::Log(int number)
{
    logStream << number << std::endl;
}

void Logger::Log(size_t number)
{
    logStream << number << std::endl;
}

void Logger::Log(unsigned int number)
{
    logStream << number << std::endl;
}

void Logger::Log(void* pointer){
    logStream << pointer << std::endl;
}

void Logger::Log(const std::string& msg, void* pointer)
{
    logStream << msg << pointer << std::endl;
}


void Logger::Log(const std::string& msg, int number)
{
    logStream << msg << number << std::endl;
}

void Logger::Log(const std::string& msg, unsigned int number)
{
    logStream << msg << number << std::endl;
}

void Logger::Log(const vector4& vec)
{
    logStream << vec.x() << " | " << vec.y() << " | " << vec.z()<< " | " << vec.w()<< " | " << std::endl;
}

void Logger::Log(const vector3& vec)
{
    logStream << vec.x() << " | " << vec.y() << " | " << vec.z()<< " | " << std::endl;
}


void Logger::Log(const string& matrixName, const matrix4& mat)
{
    logStream << matrixName << std::endl;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            logStream << mat(i, j) << " | ";
        }
        logStream << std::endl;
    }
}

void Logger::Log(const string& matrixName, const matrix3& mat)
{
    logStream << matrixName << std::endl;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            logStream << mat(i, j) << " | ";
        }
        logStream << std::endl;
    }
}

void Logger::Log(Texture texture)
{
    logStream << "height: " << texture.height << "\n";
    logStream << "width: " << texture.width << "\n";
    logStream << "dataFormat: " << texture.dataFormat << "\n";
    logStream << "textureKey: " << texture.textureKey << "\n";
    logStream << "textureUnit: " << texture.textureUnit << "\n";
    logStream << "textureType: " << texture.textureType << "\n";
}

void Logger::Log(const solar::Mesh& mesh) {
    logStream << "Mesh name: " << std::string(mesh.name.begin(), mesh.name.end()) << "\n";
    logStream << "Number of vertices: " << mesh.vertices.size() << "\n";
    logStream << "Number of indices: " << mesh.vertexIndices.size() << "\n";

    for (size_t i = 0; i < mesh.vertices.size(); i+=3) {
        logStream << "Vertex " << i/3 << ": Position("
                  << mesh.vertices[i+0] << ", " << mesh.vertices[i+1] << ", " << mesh.vertices[i+2] <<")"<<std::endl;
    }

    logStream << "Indices:\n";
    for (size_t i = 0; i < mesh.vertexIndices.size(); i += 3) {
        logStream << "Triangle " << i/3 << ": "
                << mesh.vertexIndices[i] << ", "
                << mesh.vertexIndices[i+1] << ", "
                << mesh.vertexIndices[i+2] << "\n";
    }
}

void Logger::Log(char32_t chr)
{
    logStream << "U+" << std::hex << static_cast<uint32_t>(chr) << std::dec << "\n";
}

void Logger::Log(float number)
{
    logStream << number << std::endl;
}

void Logger::Log(const vector2& number)
{
    logStream << number.x() << " | " << number.y() << std::endl;
}

void Logger::Log(char32_t chr, uint64_t data)
{
    logStream << "U+" << std::hex << static_cast<uint32_t>(chr) << std::dec << " | " << data << std::endl;
}