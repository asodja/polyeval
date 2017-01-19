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
float dataOut[8];

int main()
{
	printf("Running DFE\n");
	PolyEval(8, dataIn, dataOut);

	for (int i = 0; i < 8; i++) // Ignore edge values
		printf("dataOut[%d] = %f\n", i, dataOut[i]);

	return 0;
}
