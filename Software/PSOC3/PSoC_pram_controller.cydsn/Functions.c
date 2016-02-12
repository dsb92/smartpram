#include "Functions.h"

int8 analyzeSound( float* arr, uint8 size )
{
	float total = 0;	// Total values of all elements
	float average = 0;	// Average value of all elements
	float max = arr[2];	// Set max to the first element we analyze
	float min = arr[2]; // Set min to the first element we analyze
	float range = 0;
	int countSamples009 = 0;	// Counts ammount of elements with a value higher than 0,09
	int countSamples008 = 0;	// Counts ammount of elements with a value higher than 0,08
	int8 result;	// Contains the resulting noise level. This will range from 0 to 100.
	
	int i;	// For-loop counter
	
	for( i = 2; i < size; i++ ) // Skip sample 0 and 1. Often starts with a fake high value
	{
		total += arr[i];	// Add the current element to total
		
		if( arr[i] < min ) 	// If lowest so far: save in min
			min = arr[i];
		
		if( arr[i] > max ) 	// If highest so far: save in max
			max = arr[i];
		
		if( arr[i] > 0.09 )		// If higher than 0,09: increment respective counter
			countSamples009++;
		if( arr[i] > 0.08 )		// If higher than 0,08: increment respective counter
			countSamples008++;	
	}
	
	// Calculate average value
	average = total / (float)(size - 2);
	
	// Calculate range of values
	range = max - min;
	
	// Roof of the scale: 0.16 V average is 100%, 0.00 V average is 0%.
	if( average > 0.16 )
		result = 100;
	else
		result = (int8)((1000*average)/(1.6));	// Result is scaled to only range from 0 and 100.
		// Everything between 0V and 0.16V (the roof of the scale), is translated to the matching
		// value on the 0 to 100 scale.
		
	// Reduce result 30% if signal has a low range of peak-to-peak values
	// Reduce result 30% if signal has few peak-to-peaks under 0,08 and 0,09 V.
	if( range < 0.1 )
		result = result * 0.7;
	if( (countSamples008 + countSamples009) < (0.5 * (size - 2)) )
		result = result * 0.7;
	
	return result;
}

int8 analyzeTemp( int16 tempFromADC ){
	int8 realTemp;
	realTemp = (int8)((tempFromADC/748.98) +23.205);
	return realTemp;
}

/* [] END OF FILE */
