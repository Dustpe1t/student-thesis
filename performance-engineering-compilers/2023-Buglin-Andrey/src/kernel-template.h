#pragma once
#ifndef _KERNEL_TEMPLATE_H
#define _KERNEL_TEMPLATE_H

#include <stdio.h>
#include "base.h"

class KernelTemplate : public Base::Benchmark
{
public:
    KernelTemplate()
        : Base::Benchmark(
            new Base::Configuration(
                string("kernel template"), // �������� ���������
                Init, // ������� �������������
                Cleanup, // ������� �������
                Simd, // ������� ���� ��� SIMD
                NonSimd, // ������� ���� ��� 32-������ �����������
                NonSimd, // ������� ���� ��� 64-������ �����������
                1000)) {} // ���������� ��������

    static uint64_t preventOptimize;

    static bool Init()
    {
        return true;
    };

    static bool Cleanup()
    {
        return true;
    };

    static uint64_t Simd(uint64_t n)
    {
        uint64_t s = 0;
        for (uint64_t i = 0; i < n; ++i)
        {
            preventOptimize++;
            s += i;
        }
        return s;
    };

    static uint64_t NonSimd(uint64_t n)
    {
        uint64_t s = 0;
        for (uint64_t i = 0; i < n; ++i)
        {
            preventOptimize++;
            s += i;
        }
        return s;
    };
};

uint64_t KernelTemplate::preventOptimize = 0;

#endif