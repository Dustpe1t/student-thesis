#include <stdio.h>
#include "base.h"
#include "kernel-template.h"
#include "average_float32x4.h"
#include "matrix_multiplication.h"
#include "vertex_transform.h"
#include "matrix_transpose.h"
#include "matrix_inverse.h"

// ������� ��� ������ �����������, ������ � ������ ������������������
void PrintResult(char* str)
{
    printf("%s\n", str);
}

void PrintError(char* str)
{
    printf("%s\n", str);
}

void PrintScore(char* str)
{
    printf("%s\n", str);
}

int main()
{
    // �������� ������� outputFunctions ��� �������� � �������� ��������� � RunAll
    Base::OutputFunctions outputFunctions(PrintResult, PrintError, PrintScore);

    // �������� �������� ��� ������� ���������, ���������� ������� ����� ����������� � ������������
    KernelTemplate    kernelTemplate;
    AverageFloat32x4  averageFloat32x4;
    MatrixMultiplication matrixMultiplication;
    VertexTransform vertexTransform;
    MatrixTranspose matrixTranspose;
    MatrixInverse matrixInverse;

    // ������ ���� ����������� ����������
    Base::benchmarks.RunAll(outputFunctions, true);

    return 0;
}
