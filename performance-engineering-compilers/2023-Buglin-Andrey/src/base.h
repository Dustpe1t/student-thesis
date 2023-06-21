#pragma once
#ifndef _BASE_H
#define _BASE_H

#include <string>
#include <stdint.h>
#include <emmintrin.h>
#include <xmmintrin.h>

using namespace std;

namespace Base
{
    class OutputFunctions; // ����� ��� ������ �����������, ������ � ������ ������������������
    class Configuration; // ����� ��� ������������ ���������
    class Benchmark; // ����� ��� ���������� ���������
    class Benchmarks; // ����� ��� �������� � ���������� ���� ����������

    typedef void     (*PrintFunction)(char* str); // ��� ������� ��� ������ ������
    typedef bool     (*InitFunction)(void); // ��� ������� �������������
    typedef bool     (*CleanupFunction)(void); // ��� ������� �������
    typedef uint64_t(*KernelFunction)(uint64_t n); // ��� ������� ���� ���������

    template<typename X4, typename X>
    class Lanes
    {
    private:
        union
        {
            X4  m128;
            X   lanes[4];
        } lanes;
    public:
        Lanes(X4 m128)
        {
            lanes.m128 = m128;
        }
        X x()
        {
            return lanes.lanes[0];
        }
        X y()
        {
            return lanes.lanes[1];
        }
        X z()
        {
            return lanes.lanes[2];
        }
        X w()
        {
            return lanes.lanes[3];
        }
    };

    typedef union
    {
        float  m128_f32[4];
        __m128 f32x4;
    } M128;

#define M128_INIT(m128) Base::M128 m128##overlay; m128##overlay.f32x4 = m128
#define M128_X(m128) (m128##overlay.m128_f32[0])
#define M128_Y(m128) (m128##overlay.m128_f32[1])
#define M128_Z(m128) (m128##overlay.m128_f32[2])
#define M128_W(m128) (m128##overlay.m128_f32[3])

    typedef union
    {
        int  m128i_i32[4];
        __m128i i32x4;
    } M128I;

#define M128I_INIT(m128i) Base::M128I m128i##overlay; m128i##overlay.i32x4 = m128i
#define M128I_X(m128i) (m128i##overlay.m128i_i32[0])
#define M128I_Y(m128i) (m128i##overlay.m128i_i32[1])
#define M128I_Z(m128i) (m128i##overlay.m128i_i32[2])
#define M128I_W(m128i) (m128i##overlay.m128i_i32[3])

    class OutputFunctions
    {
    public:
        OutputFunctions(PrintFunction PrintResult, PrintFunction PrintError, PrintFunction PrintScore)
            : PrintResult(PrintResult)
            , PrintError(PrintError)
            , PrintScore(PrintScore)
        {
        }

        PrintFunction PrintResult; // ������� ��� ������ �����������
        PrintFunction PrintError; // ������� ��� ������ ������
        PrintFunction PrintScore; // ������� ��� ������ ������ ������������������
    };

    class Configuration
    {
    public:
        Configuration(string        name,
            InitFunction    Init,
            CleanupFunction Cleanup,
            KernelFunction  Simd,
            KernelFunction  nonSimd32,
            KernelFunction  nonSimd64,
            uint64_t        iterations)
            : kernelName(name)
            , kernelInit(Init)
            , kernelCleanup(Cleanup)
            , kernelSimd(Simd)
            , kernelNonSimd32(nonSimd32)
            , kernelNonSimd64(nonSimd64)
            , kernelIterations(iterations)
        {
        }

        string           kernelName; // �������� ���������
        InitFunction     kernelInit; // ������� �������������
        CleanupFunction  kernelCleanup; // ������� �������
        KernelFunction   kernelSimd; // ������� ���� ��������� ��� SIMD
        KernelFunction   kernelNonSimd32; // ������� ���� ��������� ��� 32-������ �����������
        KernelFunction   kernelNonSimd64; // ������� ���� ��������� ��� 64-������ �����������
        uint64_t         kernelIterations; // ���������� �������� ���������
    };

    class Benchmarks
    {
    public:
        static void RunAll(OutputFunctions& outputFunctions, bool useAutoIterations); // ���������� ���� ����������
        static void Add(Benchmark* benchmark); // ���������� ���������
    };

    extern Benchmarks benchmarks; // ������ ��� �������� � ���������� ���� ����������

    class Benchmark
    {
    public:
        Benchmark(Configuration* config)
            : config(config)
            , useAutoIterations(false)
            , initOk(true)
            , cleanupOk(true)
        {
            Base::benchmarks.Add(this);
        }

        Configuration* config; // ������������ ���������
        bool           useAutoIterations; // ���� ������������� ��������������� ���������� ��������
        bool           initOk; // ���� �������� �������������
        bool           cleanupOk; // ���� �������� �������
        uint64_t       autoIterations; // �������������� ���������� ��������
        uint64_t       actualIterations; // ����������� ���������� ��������
        uint64_t       simdTime; // ����� ���������� SIMD-���������
        uint64_t       nonSimd32Time; // ����� ���������� ��������� ��� 32-������ �����������
        uint64_t       nonSimd64Time; // ����� ���������� ��������� ��� 64-������ �����������
    };
} //namespace Base
#endif