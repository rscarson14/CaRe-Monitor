/*
 * Filt.c
 *
 * Created: 7/1/2014 04:06:03 PM
 *  Author: Mike
 */ 
#include "Filt.h"

boolean RespFilt (uint16_t *rawData)
{		
	//50 order Nuttall low-pass 2^20
	//static const uint16_t RespFiltCo[] = {18,33,86,192,381,692,1174,1886,2892,4259,6050,8317,11096,14401,18212,22479,27111,31985,36943,41803,46369,50444,53839,56392,57977,58515,57977,56392,53839,50444,46369,41803,36943,31985,27111,22479,18212,14401,11096,8317,6050,4259,2892,1886,1174,692,381,192,86,33,18};
	static const uint16_t RespFiltCo[] = {13,14,18,24,33,45,61,81,106,136,172,216,268,329,400,483,579,690,816,959,1121,1304,1509,1737,1990,2271,2579,2918,3288,3691,4127,4599,5107,5652,6235,6856,7515,8212,8947,9720,10530,11376,12256,13169,14113,15086,16085,17107,18150,19210,20283,21365,22454,23543,24629,25708,26774,27823,28850,29850,30818,31751,32642,33488,34284,35026,35710,36332,36890,37379,37798,38144,38415,38610,38727,38766,38727,38610,38415,38144,37798,37379,36890,36332,35710,35026,34284,33488,32642,31751,30818,29850,28850,27823,26774,25708,24629,23543,22454,21365,20283,19210,18150,17107,16085,15086,14113,13169,12256,11376,10530,9720,8947,8212,7515,6856,6235,5652,5107,4599,4127,3691,3288,2918,2579,2271,1990,1737,1509,1304,1121,959,816,690,579,483,400,329,268,216,172,136,106,81,61,45,33,24,18,14,13};
	static uint16_t RespFiltMem[RESP_FILT_ORDER + 1];
	
	static boolean isValid = False; //data is invalid if computed using unfilled memory buffer
	static uint8_t fillCount = 0; //count values are in filter memory
	static uint16_t RespMemPtr = 0; //Keep track of oldest value in filter memory
	uint32_t result; //Accumulator

	*(RespFiltMem + RespMemPtr) = *rawData; //Add new value to memory buffer
	IncrementRingBufferHeadPtr(RespMemPtr, RESP_FILT_ORDER + 1, fillCount); 
	
	if(!isValid) //if buffer is still filling
	{
		if(fillCount >= RESP_FILT_ORDER + 1)//check how full buffer is
		{
			isValid = True;
		}
	}
	else
	{ //buffer is full; perform filtering algorithm
		
		result = 0; //zero accumulator
	
		for(int i = RESP_FILT_ORDER; i>=0; i--)
		{
			result += (uint32_t)*(RespFiltCo + i)*((uint32_t)*(RespFiltMem + RespMemPtr));
			IncrementRingBufferPtr(RespMemPtr, RESP_FILT_ORDER + 1); // TODO: either create dummy variable to satisfy fnctn req or find other way around this
		}	
		IncrementRingBufferPtr(RespMemPtr, RESP_FILT_ORDER + 1);//increment once more after calculation to point to next spot in buffer for the next new data point
		
		*rawData = (uint16_t)(result >> 21) ; //downscale result for gain and cast to 16-bit
		
	}
		return isValid; 
}

boolean ECGFilt (uint16_t *rawData)
{
	//Nuttal 50 2^15 (zeros removed; now 46 (47 coef bc of current/zero order term)}
	//static const int16_t ECGFiltCo[] = {-1,-1,-3,-6,-11,-20,-32,-51,-77,-112,-156,-212,-279,-357,-445,-540,-639,-738,-833,-919,-991,-1046,-1081,31676,-1081,-1046,-991,-919,-833,-738,-639,-540,-445,-357,-279,-212,-156,-112,-77,-51,-32,-20,-11,-6,-3,-1,-1};
	//static const int16_t ECGFiltCo[] = {-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-0,1,2,4,6,8,11,14,18,22,26,30,35,39,44,49,54,58,62,65,67,69,69,67,64,60,53,43,32,17,-0,-20,-43,-70,-99,-132,-167,-206,-247,-291,-337,-386,-435,-486,-538,-591,-643,-694,-745,-794,-840,-884,-925,-962,-996,-1024,-1048,-1067,-1081,-1089,31676,-1089,-1081,-1067,-1048,-1024,-996,-962,-925,-884,-840,-794,-745,-694,-643,-591,-538,-486,-435,-386,-337,-291,-247,-206,-167,-132,-99,-70,-43,-20,-0,17,32,43,53,60,64,67,69,69,67,65,62,58,54,49,44,39,35,30,26,22,18,14,11,8,6,4,2,1,-0,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1};
	
	//Nuttal 176 2^15 (zeros removed; now 144) cutoffs at 3, 15 Hz
	//static const int16_t ECGFiltCo[] = {1,1,2,3,4,6,7,8,9,9,9,8,5,2,-1,-5,-9,-12,-13,-13,-11,-7,0,8,17,25,31,34,31,23,7,-16,-46,-80,-118,-155,-189,-216,-232,-237,-227,-204,-170,-127,-82,-41,-11,0,-13,-56,-131,-237,-371,-523,-683,-838,-972,-1069,-1113,-1092,-997,-822,-570,-248,132,551,988,1416,1811,2148,2405,2567,2622,2567,2405,2148,1811,1416,988,551,132,-248,-570,-822,-997,-1092,-1113,-1069,-972,-838,-683,-523,-371,-237,-131,-56,-13,0,-11,-41,-82,-127,-170,-204,-227,-237,-232,-216,-189,-155,-118,-80,-46,-16,7,23,31,34,31,25,17,8,0,-7,-11,-13,-13,-12,-9,-5,-1,2,5,8,9,9,9,8,7,6,4,3,2,1,1};
	
	
	//static const int16_t ECGFiltCo[] = {-1,-1,-1,-1,-2,-2,-2,-3,-3,-4,-4,-4,-5,-5,-6,-6,-6,-6,-6,-6,-5,-4,-3,-2,-0,2,5,8,11,15,20,25,30,35,41,47,53,59,65,71,76,81,85,88,89,90,89,86,81,74,64,52,38,20,-0,-23,-50,-79,-111,-146,-184,-225,-268,-313,-361,-409,-459,-510,-562,-613,-664,-714,-763,-810,-854,-896,-935,-970,-1001,-1029,-1051,-1069,-1082,-1090,31676,-1090,-1082,-1069,-1051,-1029,-1001,-970,-935,-896,-854,-810,-763,-714,-664,-613,-562,-510,-459,-409,-361,-313,-268,-225,-184,-146,-111,-79,-50,-23,-0,20,38,52,64,74,81,86,89,90,89,88,85,81,76,71,65,59,53,47,41,35,30,25,20,15,11,8,5,2,-0,-2,-3,-4,-5,-6,-6,-6,-6,-6,-6,-5,-5,-4,-4,-4,-3,-3,-2,-2,-2,-1,-1,-1,-1};


	//Nuttal 176 2^18 (zeros removed; now 162)
	static const int16_t ECGFiltCo[] = {-1,-2,-4,-6,-8,-11,-14,-16,-18,-18,-17,-15,-10,-4,4,12,19,23,25,21,13,-0,-17,-36,-54,-66,-68,-56,-24,30,107,205,322,449,577,693,785,840,848,801,697,540,340,115,-113,-320,-478,-566,-564,-464,-271,0,317,637,906,1066,1058,831,346,-415,-1444,-2708,-4141,-5654,-7133,-8453,-9481,-10093,-10183,-9673,-8525,-6744,-4387,-1552,1615,4939,8222,11262,13863,15855,17107,17534,17107,15855,13863,11262,8222,4939,1615,-1552,-4387,-6744,-8525,-9673,-10183,-10093,-9481,-8453,-7133,-5654,-4141,-2708,-1444,-415,346,831,1058,1066,906,637,317,0,-271,-464,-564,-566,-478,-320,-113,115,340,540,697,801,848,840,785,693,577,449,322,205,107,30,-24,-56,-68,-66,-54,-36,-17,-0,13,21,25,23,19,12,4,-4,-10,-15,-17,-18,-18,-16,-14,-11,-8,-6,-4,-2,-1};
	static int16_t ECGFiltMem[ECG_FILT_ORDER + 1];
	
	static boolean isValid = False; //data is invalid if computed using unfilled memory buffer
	static uint8_t fillCount = 0; //count values are in filter memory
	int32_t result; //Accumulator
	static uint16_t ECGMemPtr = 0; //Used when filling the memory buffer with new ADC values
	
	*(ECGFiltMem + ECGMemPtr) = *rawData; //Add new value to memory buffer
	IncrementRingBufferHeadPtr(ECGMemPtr, ECG_FILT_ORDER + 1, fillCount); //increment fill pointer***Need to change IncRingBug function
	
	if(!isValid) //if buffer is still filling
	{
		if(fillCount >= ECG_FILT_ORDER + 1)//check how full buffer is
		{
			isValid = True;
		}
	}
	else //buffer is full; perform filtering algorithm
	{
		result = 0; //zero accumulator
	
		for(int i = ECG_FILT_ORDER; i>=0; i--)
		{
			result += ((int32_t)*(ECGFiltCo + i))*((int32_t)*(ECGFiltMem + ECGMemPtr));
			IncrementRingBufferPtr(ECGMemPtr, ECG_FILT_ORDER + 1); //TODO: '' ''
		}
		
		IncrementRingBufferPtr(ECGMemPtr, ECG_FILT_ORDER+1);
		
		if(result < 200) //rectify; thresh determined empirically; needs to be verified
		{
			result = 0;
		}
		
		*rawData = (uint16_t)((result>>18)+512);
	}	
	
	return isValid;
}