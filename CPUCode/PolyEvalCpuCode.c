/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial)
 * Chapter: 3      Example: 1      Name: Moving Average Simple
 * MaxFile name: MovingAverageSimple
 * Summary:
 *   CPU code for the three point moving average design.
 */
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float dataIn[8] = { 1, 0, 2, 0, 4, 1, 6, 3 };
int32_t exps[8] = { 3, 1, 0, 4, 1, 2, 7, 5 };
float expVals[8] = { 1, 3, 9, 27, 81, 243, 729, 2187 };
float dataOut[8];

int main()
{
	printf("Running DFE\n");
	PolyEval(8, exps, expVals, dataIn, dataOut);

	for (int i = 0; i < 8; i++)
		printf("dataOut[%d] = %f\n", i, dataOut[i]);

	return 0;
}
