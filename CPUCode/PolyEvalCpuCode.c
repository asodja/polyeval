/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial)
 * Chapter: 3      Example: 1      Name: Moving Average Simple
 * MaxFile name: MovingAverageSimple
 * Summary:
 *   CPU code for the three point moving average design.
 */
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float constants[8] = { 1, 0, 2, 0, 4, 1, 6, 3 };
int32_t exponents[8] = { 3, 1, 0, 4, 1, 2, 7, 5 };

float expVals[8] = { 1, 3, 9, 27, 81, 243, 729, 2187 };
float result[8];

int main()
{
	printf("Running DFE\n");
	uint32_t maxExponents = 8;
	int32_t n = 8;
	float x = 3.0f;
	PolyEval(maxExponents, n, x, constants, exponents, result);

	for (int i = 0; i < n; i++) {
		printf("result[%d] = %f\n", i, result[i]);
	}
	printf("Polynomial result = %f\n", result[n - 1]);

	return 0;
}
