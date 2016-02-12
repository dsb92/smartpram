#include "Filter_1.h"
#include "Filter_1_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelAFirCoefficients Filter_1_ChannelAFirCoefficients

/* Number of FIR filter taps are: 25 */

const uint8 CYCODE Filter_1_ChannelAFirCoefficients[Filter_1_FIR_A_SIZE] = 
{
 0x6Eu, 0xE6u, 0xFFu, 0x00u, /* Tap(0), -0.000780344009399414 */

 0x6Au, 0x4Au, 0x00u, 0x00u, /* Tap(1), 0.00227093696594238 */

 0xA9u, 0x6Du, 0x00u, 0x00u, /* Tap(2), 0.00334656238555908 */

 0x3Eu, 0x88u, 0xFFu, 0x00u, /* Tap(3), -0.00365471839904785 */

 0x23u, 0x7Bu, 0xFEu, 0x00u, /* Tap(4), -0.0118671655654907 */

 0x3Du, 0x1Au, 0x00u, 0x00u, /* Tap(5), 0.000800728797912598 */

 0x1Au, 0x99u, 0x03u, 0x00u, /* Tap(6), 0.0281097888946533 */

 0x97u, 0x2Eu, 0x02u, 0x00u, /* Tap(7), 0.0170468091964722 */

 0x6Eu, 0xC2u, 0xF9u, 0x00u, /* Tap(8), -0.0487539768218994 */

 0x8Bu, 0xF4u, 0xF6u, 0x00u, /* Tap(9), -0.0706621408462524 */

 0x94u, 0x7Du, 0x08u, 0x00u, /* Tap(10), 0.0663323402404785 */

 0xBEu, 0x00u, 0x27u, 0x00u, /* Tap(11), 0.304710149765015 */

 0xCAu, 0x8Du, 0x36u, 0x00u, /* Tap(12), 0.426202058792114 */

 0xBEu, 0x00u, 0x27u, 0x00u, /* Tap(13), 0.304710149765015 */

 0x94u, 0x7Du, 0x08u, 0x00u, /* Tap(14), 0.0663323402404785 */

 0x8Bu, 0xF4u, 0xF6u, 0x00u, /* Tap(15), -0.0706621408462524 */

 0x6Eu, 0xC2u, 0xF9u, 0x00u, /* Tap(16), -0.0487539768218994 */

 0x97u, 0x2Eu, 0x02u, 0x00u, /* Tap(17), 0.0170468091964722 */

 0x1Au, 0x99u, 0x03u, 0x00u, /* Tap(18), 0.0281097888946533 */

 0x3Du, 0x1Au, 0x00u, 0x00u, /* Tap(19), 0.000800728797912598 */

 0x23u, 0x7Bu, 0xFEu, 0x00u, /* Tap(20), -0.0118671655654907 */

 0x3Eu, 0x88u, 0xFFu, 0x00u, /* Tap(21), -0.00365471839904785 */

 0xA9u, 0x6Du, 0x00u, 0x00u, /* Tap(22), 0.00334656238555908 */

 0x6Au, 0x4Au, 0x00u, 0x00u, /* Tap(23), 0.00227093696594238 */

 0x6Eu, 0xE6u, 0xFFu, 0x00u, /* Tap(24), -0.000780344009399414 */
};

