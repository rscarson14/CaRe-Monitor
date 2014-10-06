
#include "main.h"

int main(void)
{
	
	
#define SANDBOX 0

#if SANDBOX
	
	MasterInitialize();
	turnOnAnalog();
	ADCStartRead(0x02);
	SelectPot();
	DecreaseGain(100);
	IncreaseGain(99);
	startBlinkRespLED();
	startBlinkECGLED();
	uint16_t respData;
	uint16_t ECGData;
	uint16_t rawData;
	//uint16_t pCount;
	
	uint16_t i;
	i = 500;
	while(i--);
							ADCStopRead();
							ADCStartRead(0x00);//start reading signal channel from now on
	while(1)
	{
		i = 250;
		if(ADCDataBufferCount){
		rawData = ADCDataBuffer[ADCDataBufferTailPtr];
		IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
		ECGData = rawData;
		respData = rawData;
		RespFilt(&respData);
		ECGFilt(&ECGData);
		printf("r%u\n%u\n%u\n",respData,ECGData, rawData);
		//turnOnRespLED();
		//RespFilt(&respData);
		//while(i--);
		//ECGFilt(&ECGData);
		//turnOffRespLED();
		//LoadChar('r');
		/*
		LoadChar('\n');
		LoadChar('\r');
		SendDecimalNumber(respData);
		*/
		//LoadChar('\n');
		//LoadChar('\r');
		//LoadChar('\t');
		//SendDecimalNumber(ADCDataBufferCount);
		//LoadChar('\n');
		//LoadChar('\r');
		
		//SendDecimalNumber(ECGData);
		//LoadChar('\n');
		//LoadChar('\r');
		//SendDecimalNumber(rawData);
		//LoadChar('\n');
		//LoadChar('\r');
		
		//StartTx();
		}
		/*
		else{
			sleep_enable();
			sleep_cpu();
		}*/
		while(i--);

		
		
	}
#else
	uint16_t expectedMaximumBreath = 0;//these variables will store the maximum and minimum breath (on average) calculated during calibration
	uint16_t expectedMinimumBreath = 0;
	uint16_t expectedMaximumECG = 0;
	uint16_t breathThreshold;
	uint16_t ECGThreshold;
    
	while(1)
    {
		switch(mainState)
		{
			case Init:
			{
				MasterInitialize();
				int8_t i = 250;
				while(i--);
				mainState = WaitForPB;
			
			}
			break;

			case WaitForPB:
			{
				if(pbPressed)
				{
					mainState = Calibration;
					respTimeThresh = readSwitch();
					printf("a%u\n", respTimeThresh);
					SendString("Dur:", 4);
					SendDecimalNumber(respTimeThresh);
					turnOnAnalog();
					//TODO: freeze switch position here
				}
			}			
			break;
			
			case Calibration:
			{
				uint8_t steps = 50;
				uint16_t i;
				uint16_t maxRead;
				boolean singleStepping = False;
				static struct  //used only in this loop to determine expected max/min for breathing
				{
					uint16_t points[5];
					struct  
					{
						uint16_t value;
						uint8_t position;
					}lowestMax;
					uint8_t initialPointer;//this will be 0 and will point to the next unfilled position to store data, when it is 5, it is time to replace old data
				}maxRespPoints = {.points = {0x00, 0x00, 0x00, 0x00, 0x00}, .lowestMax = {.value = 0x3FF, .position = 0}, .initialPointer = 0};
						
				static struct  
				{
					uint16_t points[5];
					struct  
					{
						uint16_t value;
						uint8_t position;
					}highestMin;
					uint8_t initialPointer;
				}minRespPoints = {.points = {0x00, 0x00, 0x00, 0x00, 0x00}, .highestMin = {.value = 0x000, .position = 0}, .initialPointer = 0};
					
				static struct 
				{
					uint16_t points[5];//data
						
				}recentRespMemory = {.points = {0x00, 0x00, 0x00, 0x00, 0x00}};
					
				static struct  //used only in this loop to determine expected max for ECG
				{
					uint16_t points[5];
					struct
					{
						uint16_t value;
						uint8_t position;
					}lowestMax;
					uint8_t initialPointer;//this will be 0 and will point to the next unfilled position to store data, when it is 5, it is time to replace old data
					}maxECGPoints = {.points = {0x00, 0x00, 0x00, 0x00, 0x00}, .lowestMax = {.value = 0x3FF, .position = 0}, .initialPointer = 0};
						
				static struct
				{
					uint16_t points[5];//data
					
					}recentECGMemory = {.points = {0x00, 0x00, 0x00, 0x00, 0x00}};
				
				startBlinkStatusLED();

				ADCStartRead(0x02);//gain feedback channel
				SelectPot();
				DecreaseGain(100);
				IncreaseGain(49);//set to center point
				
				for(;;) 
				{
					steps /= 2;
					if(!steps)//zero
					{
						steps = 1;
					}
					maxRead = 0;
					for(i = 0;i<2;)
					{
						if(ADCDataBufferCount)
						{
							i++;
							if(ADCDataBuffer[ADCDataBufferTailPtr] > maxRead)
							{
								maxRead = ADCDataBuffer[ADCDataBufferTailPtr];
							}
							IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
						}
					}
					if(maxRead >= 0x333)//0x333 is 80 percent saturation of the adc, we want our max to be around here
					{
						
						DecreaseGain(steps);					
						LoadChar('d');
						SendDecimalNumber(steps);
						LoadChar('\n');
						LoadChar('\r');
						SendDecimalNumber(maxRead);
						LoadChar('\n');
						LoadChar('\r');
						StartTx();
						
					}
					else
					{
						
						IncreaseGain(steps);
								
						LoadChar('i');
						SendDecimalNumber(steps);
						LoadChar('\n');
						LoadChar('\r');
						SendDecimalNumber(maxRead);
						LoadChar('\n');
						LoadChar('\r');
						StartTx();	
					}
					
					if(singleStepping)
					{
						mainState = Sampling;
						DeselectPot();//freeze setting
						ADCStopRead();
						ADCStartRead(0x00);//start reading signal channel from now on
						break;
					}
					if(steps == 1)
					{
						singleStepping = True;
					}

					
										
				} 
				//Spin until filter buffers are populated
				while(1)
				{
					uint16_t RespDataFill;
					uint16_t ECGDataFill;
					if(ADCDataBufferCount)
					{	
						RespDataFill = ADCDataBuffer[ADCDataBufferTailPtr];
						ECGDataFill = RespDataFill;
						
						if(RespFilt(&RespDataFill) && ECGFilt(&ECGDataFill))
						{
							IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
							SendString("Filt Buffers Filled", 19);
							break;	
						}
						IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
					}
		
				}
				for(i = 0;i<4500;)
				{
					//SendString("inside Thresh Calc", 18);
					if(ADCDataBufferCount)
					{
						int8_t j;
						i++;
						
						for(j=4; j>0; j--)
						{
							recentRespMemory.points[j] = recentRespMemory.points[j-1];//shift data points
							recentECGMemory.points[j] = recentECGMemory.points[j-1];							
						}
						recentRespMemory.points[0] = ADCDataBuffer[ADCDataBufferTailPtr];
						IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
						recentECGMemory.points[0] = recentRespMemory.points[0];
					
						RespFilt(&recentRespMemory.points[0]);
						ECGFilt(&recentECGMemory.points[0]);
						
						
						if(i >= 5 && (recentRespMemory.points[2]>=recentRespMemory.points[0]&&recentRespMemory.points[2]>=recentRespMemory.points[1]&&recentRespMemory.points[2]>=recentRespMemory.points[3]&&recentRespMemory.points[2]>=recentRespMemory.points[4]))
						{
							if(maxRespPoints.initialPointer < 5)
							{				
								maxRespPoints.points[maxRespPoints.initialPointer] = recentRespMemory.points[2];//store the point if we don't already have 5 points and increment the initializer
								if(maxRespPoints.points[maxRespPoints.initialPointer] < maxRespPoints.lowestMax.value)
								{
									maxRespPoints.lowestMax.value = maxRespPoints.points[maxRespPoints.initialPointer];//remember the LOWEST maximum so we have a quick comparison value for new local maxes when the first five points have come in
									maxRespPoints.lowestMax.position = maxRespPoints.initialPointer;
								}
								maxRespPoints.initialPointer++; 
							}
							else
							{
								if(recentRespMemory.points[2] > maxRespPoints.lowestMax.value)
								{
									maxRespPoints.points[maxRespPoints.lowestMax.position] = recentRespMemory.points[2];//replace lowest point with new one
									maxRespPoints.lowestMax.position = 0x00;
									maxRespPoints.lowestMax.value = 0x3FF;//clear these values to be reset in the loop following
									for(j = 4; j>= 0; j--)
									{
										if(maxRespPoints.points[j] < maxRespPoints.lowestMax.value)
										{
											maxRespPoints.lowestMax.value = maxRespPoints.points[j];//record lowest
											maxRespPoints.lowestMax.position = j;
											
										}
									}
									
								}
							}
							
						}
						if(i >= 5 && (recentRespMemory.points[2] <= recentRespMemory.points[0] && recentRespMemory.points[2] <= recentRespMemory.points[1] && recentRespMemory.points[2] <= recentRespMemory.points[3] && recentRespMemory.points[2] <= recentRespMemory.points[4]))
						{
							if(minRespPoints.initialPointer < 5)
							{	
								minRespPoints.points[minRespPoints.initialPointer] = recentRespMemory.points[2];//store the point if we don't already have 5 points and increment the initializer
								if(minRespPoints.points[minRespPoints.initialPointer] > minRespPoints.highestMin.value)
								{
									minRespPoints.highestMin.value = minRespPoints.points[minRespPoints.initialPointer];//remember the HIGHEST minimum so we have a quick comparison value for new local MIns when the first five points have come in
									minRespPoints.highestMin.position = minRespPoints.initialPointer;								
								}
								minRespPoints.initialPointer++;
							}
							else
							{
								if(recentRespMemory.points[2] < minRespPoints.highestMin.value)
								{
									minRespPoints.points[minRespPoints.highestMin.position] = recentRespMemory.points[2];//replace lowest point with new one
									minRespPoints.highestMin.position = 0x00;
									minRespPoints.highestMin.value = 0x00;//clear these values to be reset in the loop following
									for(j = 4; j>= 0; j--)
									{
										if(minRespPoints.points[j] > minRespPoints.highestMin.value)
										{
											minRespPoints.highestMin.value = minRespPoints.points[j];//record lowest
											minRespPoints.highestMin.position = j;
											
										}
									}
									
								}
							};	
						}
						if(i >= 5 && (recentECGMemory.points[2]>=recentECGMemory.points[0]&&recentECGMemory.points[2]>=recentECGMemory.points[1]&&recentECGMemory.points[2]>=recentECGMemory.points[3]&&recentECGMemory.points[2]>=recentECGMemory.points[4]))
						{
							if(maxECGPoints.initialPointer < 5)
							{
								maxECGPoints.points[maxECGPoints.initialPointer] = recentECGMemory.points[2];//store the point if we don't already have 5 points and increment the initializer
								if(maxECGPoints.points[maxECGPoints.initialPointer] < maxECGPoints.lowestMax.value)
								{
									maxECGPoints.lowestMax.value = maxECGPoints.points[maxECGPoints.initialPointer];//remember the LOWEST maximum so we have a quick comparison value for new local maxes when the first five points have come in
									maxECGPoints.lowestMax.position = maxECGPoints.initialPointer;
								}

								maxECGPoints.initialPointer++;
							}
							else
							{	
								if(recentECGMemory.points[2] > maxECGPoints.lowestMax.value)
								{
									maxECGPoints.points[maxECGPoints.lowestMax.position] = recentECGMemory.points[2];//replace lowest point with new one
									maxECGPoints.lowestMax.position = 0x00;
									maxECGPoints.lowestMax.value = 0x3FF;//clear these values to be reset in the loop following
									for(j = 4; j>= 0; j--)
									{
										if(maxECGPoints.points[j] < maxECGPoints.lowestMax.value)
										{
											maxECGPoints.lowestMax.value = maxECGPoints.points[j];//record lowest
											maxECGPoints.lowestMax.position = j;	
										}
									}
									
								}
							}	
						}
					}
				}
				for(i=0;i<5;i++)
				{
					expectedMinimumBreath += minRespPoints.points[i];
					expectedMaximumBreath += maxRespPoints.points[i];
					expectedMaximumECG += maxECGPoints.points[i];
				}
					
				expectedMinimumBreath /= 5;//after this point, the max/min breath values have been calculated as an average of 5 points that were most maximum or minimum
				expectedMaximumBreath /= 5;
				expectedMaximumECG /= 5;
				ECGThreshold = (expectedMaximumECG*PERCENTAGE_CALIBRATED_ECG_THRESHOLD)/100;
				breathThreshold = ((expectedMaximumBreath-expectedMinimumBreath)*PERCENTAGE_CALIBRATED_BREATH_THRESHOLD)/100; //TODO: determine why calc thresh is lower than expected when signal has large amplitude
				printf("t%u\n%u\n", breathThreshold, ECGThreshold);
			}

			
			break;
			//here we have expected max and min breaths for the patient, the pot is calibrated, and data is streaming in from the ADC and being stored in the circular buffer. We can now enter sampling mode and watch the wave for shallow or non existent breaths, or the cessation of a heart beat
			
			case Sampling:
			{
				static struct{
					uint16_t apneaCount;
					uint16_t heartBeatCount;
					struct{
						uint16_t beatPeriod[16];
						uint8_t circularPointer;
						uint16_t sum;
						uint8_t totalSamples;
						uint8_t totalSlowHeartBeats;
					}heartRate;
					union{
						struct{
							uint8_t apneaCountExceeded:1;
							uint8_t noHeartBeatCountExceeded:1;
							uint8_t b2:1;
							uint8_t b3:1;
							uint8_t b4:1;
							uint8_t b5:1;
							uint8_t b6:1;
							uint8_t b7:1;
						}flag;
						uint8_t all;
					}flags;
				}vitalCounts = {.apneaCount  = 0, .heartBeatCount = 0, .heartRate = {.circularPointer = 0, .sum = 0, .totalSamples = 0, .totalSlowHeartBeats = 0}, .flags = { .all = 0}};
				
				
				static struct 
				{
					uint16_t newPoint;//depends on sampling rate, will contain filtered data points
					struct  
					{
						uint16_t location;
						uint16_t value;
					}maximum;
					struct 
					{
						uint16_t location;
						uint16_t value;
					}minimum;
					union
					{
						struct{
							uint8_t extremeUpdated:1;
							uint8_t resetMaxMin:1;
							uint8_t b2:1;
							uint8_t b3:1;
							uint8_t b4:1;
							uint8_t b5:1;
							uint8_t b6:1;
							uint8_t b7:1;
						}flag;
						uint8_t all;
					}flags;
				}respBuffer = {.maximum = {.location = 0, .value = 0}, .minimum = {.location = 0, .value = 0xFFFF}, .flags = {.flag = {.extremeUpdated = False, .resetMaxMin = True}}}, 
				 ECGBuffer = {.maximum = {.location = 0, .value = 0}, .minimum = {.location = 0, .value = 0}, .flags = {.flag = {.extremeUpdated = False, .resetMaxMin = True}}};	
				//SendString("Samp", 4);
				stopBlinkStatusLED();
				turnOnStatusLED();
				uint8_t breaths = 0;
				uint8_t pCount = 0;
				while(ADCDataBufferCount)
				{
					//Add newest value to buffers
					respBuffer.newPoint = ADCDataBuffer[ADCDataBufferTailPtr];
					IncrementRingBufferTailPtr(ADCDataBufferTailPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);
					ECGBuffer.newPoint = respBuffer.newPoint;
					
					//Filter Data
					RespFilt(&respBuffer.newPoint);					
					ECGFilt(&ECGBuffer.newPoint);
					
					if(pCount == 2)
					{
						printf("r%u\n%u\n%u\n",respBuffer.newPoint,ECGBuffer.newPoint, ADCDataBuffer[ADCDataBufferTailPtr]);
						printf("mh%u\n",vitalCounts.heartRate.sum >> 4);
						

						pCount = 0;
					}
					pCount++;
					/******
					*Following is the breath detection code
					*
					*s
					******/		
					respBuffer.maximum.location++;	
					respBuffer.minimum.location++;						
					if(respBuffer.maximum.location >= SAMPLE_POINTS_TO_REMEMBER)//if one of our max/mins has expired, we need to reset it here to the current point
					{
						respBuffer.maximum.value = respBuffer.newPoint;
						respBuffer.maximum.location = 0;
						respBuffer.flags.flag.extremeUpdated = True;
					}
					if(respBuffer.minimum.location >= SAMPLE_POINTS_TO_REMEMBER)
					{
						respBuffer.minimum.value = respBuffer.newPoint;
						respBuffer.minimum.location = 0;
						respBuffer.flags.flag.extremeUpdated = True;
					}
						
					if(respBuffer.flags.flag.resetMaxMin)
					{
						respBuffer.maximum.value = respBuffer.newPoint;
						respBuffer.minimum.value = respBuffer.newPoint;
						respBuffer.maximum.location = 0;
						respBuffer.minimum.location = 0;
						respBuffer.flags.flag.resetMaxMin = False;				
					}
					if(respBuffer.newPoint > respBuffer.maximum.value)//replace max/min with new point if it exceeds
					{
						respBuffer.maximum.value = respBuffer.newPoint;
						respBuffer.maximum.location = 0;
						respBuffer.flags.flag.extremeUpdated = True;
					}
					if(respBuffer.newPoint < respBuffer.minimum.value)
					{
						respBuffer.minimum.value = respBuffer.newPoint;
						respBuffer.minimum.location = 0;
						respBuffer.flags.flag.extremeUpdated = True;
					}
					if(respBuffer.flags.flag.extremeUpdated)//max or min was changed, calculate if we now reach threshold
					{
						if(respBuffer.maximum.value - respBuffer.minimum.value >= breathThreshold) //TODO: initialize threshold above
						{
							//we have a full breath here, reset and clear prior data
							respBuffer.flags.flag.resetMaxMin = True;
							vitalCounts.apneaCount = 0;//reset counter to 0
						}
						
						respBuffer.flags.flag.extremeUpdated = False;
					}
					vitalCounts.apneaCount++;
					printf("mb%u\n", vitalCounts.apneaCount);
					if(vitalCounts.apneaCount >= respTimeThresh*300)
					{
						startBlinkRespLED();
						startAlarm();
						mainState = Alarm;
						break;		
					}
					/*
					* following is the heartbeat detection code:
					*/
					if((ECGBuffer.newPoint >= ECGThreshold))
					{	
						
						if(vitalCounts.heartBeatCount)
						{//if this evaluates true this is the first trigger for this heartbeat
							
							//vitalCounts.heartRate.circularPointer++;
							//vitalCounts.heartRate.beatPeriod[vitalCounts.heartRate.circularPointer] = vitalCounts.heartBeatCount;
							IncrementRingBufferPtr(vitalCounts.heartRate.circularPointer, 16);
							if(vitalCounts.heartRate.totalSamples == 16) 
							{
								if(vitalCounts.heartBeatCount > 30)//prevents ''double-beats'' from dropping mean
								{	
									
		
									vitalCounts.heartRate.sum -= (vitalCounts.heartRate.beatPeriod[vitalCounts.heartRate.circularPointer] + 30); //30 to account for QRS width
									vitalCounts.heartRate.sum += (vitalCounts.heartBeatCount+30);//30 to account for QRS width
									vitalCounts.heartRate.beatPeriod[vitalCounts.heartRate.circularPointer] = vitalCounts.heartBeatCount;

									if((vitalCounts.heartRate.sum >> 4)>= SLOW_HEART_RATE_PERIOD)
									{
										vitalCounts.heartRate.totalSlowHeartBeats++;
										if(vitalCounts.heartRate.totalSlowHeartBeats >= NUMBER_OF_TOO_SLOW_HEARTBEATS)

										{
											SendString("Low HB", 6);
											startBlinkECGLED();
											startAlarm();
											mainState = Alarm;
											break;//leave this state immediately, do not wait to crunch rest of ADC values
										}	
									
									}
									else
									{
										vitalCounts.heartRate.totalSlowHeartBeats = 0;
									}
								}
							}
							else
							{
								if(vitalCounts.heartBeatCount > 100)
								{
									vitalCounts.heartRate.beatPeriod[vitalCounts.heartRate.circularPointer] = vitalCounts.heartBeatCount;
									vitalCounts.heartRate.sum += vitalCounts.heartBeatCount;
									vitalCounts.heartRate.totalSamples++;									
								}

							}
							vitalCounts.heartBeatCount = 0;
					
						}
						else
						{
							//we already counted this peak we are just not back below the threshold yet
						}
					}
					else
					{
						vitalCounts.heartBeatCount++;
						
						if(vitalCounts.heartBeatCount >= NO_HEART_RATE_PERIOD)
						{
							SendString("No HB", 5);
							turnOnECGLED();
							startAlarm();
							mainState = Alarm;
							break;			
						}
						
					}
														
				}
					
			}
			break;
			
			case Alarm:
			{
				//
				SendString("Alarm", 5);
			}
			break;
			
			default://error, should always have a state, decide how to handle this
			{
				mainState = Init;//we should set off a different alarm here instead of simply starting over
			}
			break;
		}
		
	
    }
#endif
}



