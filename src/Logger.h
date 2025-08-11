#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

struct Texture;
struct matrix4;
struct matrix3;
struct vector4;
struct vector3;
struct vector2;
namespace solar {
    struct Mesh;
}

/*
NOT SAFE FOR MULTITHREADING
 */
class Logger
{
private:
    static std::ofstream logFile;
    static std::stringstream logStream;
public:
    Logger();
    ~Logger();
    
    static void Init();
    
    static void Close();

    static void Log();

    static void Log(const char* file, int line, const char* func);

    static void Log(const std::string& msg);

    static void Log(const char* msg);

    static void Log(int number);
    
    static void Log(float number);

    static void Log(const vector2& number);

    static void Log(void* pointer);

    static void Log(char32_t chr);

    static void Log(const std::string& msg, void* pointer);

    static void Log(Texture thisTexture);

    static void Log(const std::string& msg, int number);

    static void Log(const std::string& msg, unsigned int number);

    static void Log(const std::string& matrixName, const matrix4& mat);

    static void Log(const std::string& matrixName, const matrix3& mat);

    static void Log(const solar::Mesh& mesh);

    static void Log(const vector4& vec);
    
    static void Log(const vector3& vec);
};

#define error(MSG)                                  \
do {                                                \
    std::string _err_msg = (MSG);                   \
    std::cerr << "ERROR: " << _err_msg << std::endl;\
    LOG("ERROR: " + _err_msg);                      \
    Logger::Close();                                \
    std::exit(EXIT_FAILURE);                        \
} while (0)
