// The Sampler module continuously collects light sensor readings on a background thread. 
// It samples the sensor every 1 millisecond, storing the readings in a dynamically allocated array. 
// Once every second, the module transfers these current samples into a history buffer.
// Additionally, it provides functions to retrieve the number of samples in the history, 
// compute the average light level, count the number of dips (using an exponential smoothing algorithm with defined thresholds),
// and track the total number of samples taken. 

// sampler.h
// It continuously samples the light level, and stores it internally.
// It provides access to the samples it recorded during the _previous_
// complete second.
//
// The application will do a number of actions each second which must
// be synchronized (such as computing dips and printing to the screen).
// To make easy to work with the data, the app must call
// Sampler_moveCurrentDataToHistory() each second to trigger this
// module to move the current samples into the history.
#ifndef _SAMPLER_H_
#define _SAMPLER_H_

// Begin/end the background thread which samples light levels.
void Sampler_init(void);
void Sampler_cleanup(void);

// Must be called once every 1s.
// Moves the samples that it has been collecting this second into
// the history, which makes the samples available for reads (below).
void Sampler_moveCurrentDataToHistory(void);

// Get the number of samples collected during the previous complete second.
int Sampler_getHistorySize(void);

// Get dips count.
int Sampler_getDips(void);

// Get a copy of the samples in the sample history.
// Returns a newly allocated array and sets `size` to be the
// number of elements in the returned array (output-only parameter).
// The calling code must call free() on the returned pointer.
// Note: It provides both data and size to ensure consistency.
double* Sampler_getHistory(int *size);

// Get the average light level (not tied to the history).
double Sampler_getAverageReading(void);

// Get the total number of light level samples taken so far.
long long Sampler_getNumSamplesTaken(void);

#endif