#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>

struct Texture;
template<typename T, unsigned int N>
struct Matrix;
template<typename T, unsigned int N>
struct Vector;
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

    static void Log(const std::string& msg, float data);

    static void Log(const char* msg);

    static void Log(bool bVal);

    static void Log(int number);

    static void Log(unsigned long long number);

    static void Log(unsigned int number);
    
    static void Log(float number);

    template<typename T, unsigned int N>
    static void Log(const Vector<T, N>& vector)
    {
        logStream << vector.ToString() << std::endl;
    }

    template<typename T, unsigned int N>
    static void Log(const Matrix<T, N>& mat)
    {
        logStream << mat.ToString() << std::endl;
    }

    static void Log(void* pointer);

    static void Log(char32_t chr);

    static void Log(char32_t chr, uint64_t data);

    static void Log(const std::string& msg, void* pointer);

    static void Log(Texture thisTexture);

    static void Log(const std::string& msg, int number);

    static void Log(const std::string& msg, unsigned int number);

    static void Log(const solar::Mesh& mesh);

};

#define error(MSG)                                  \
do {                                                \
    std::string _err_msg = (MSG);                   \
    std::cerr << "ERROR: " << _err_msg << std::endl;\
    LOG("ERROR: " + _err_msg);                      \
    Logger::Close();                                \
    std::exit(EXIT_FAILURE);                        \
} while (0)
