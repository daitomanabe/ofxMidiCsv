/*

    	    MIDI I/O Function Definitions

*/

//extern long readlong(FILE *fp);
//extern short readshort(FILE *fp);
//extern vlint readVarLen(FILE *fp);
//extern void readMidiFileHeader(FILE *fp, struct mhead *h);
//extern void readMidiTrackHeader(FILE *fp, struct mtrack *t);
//
//extern void writelong(FILE *fp, const long l);
//extern void writeshort(FILE *fp, const short s);
//extern void writeVarLen(FILE *fp, const vlint v);
//extern void writeMidiFileHeader(FILE *fp, struct mhead *h);
//extern void writeMidiTrackHeader(FILE *fp, struct mtrack *t);
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	
	long readlong(FILE *fp);
	short readshort(FILE *fp);
	vlint readVarLen(FILE *fp);
	void readMidiFileHeader(FILE *fp, struct mhead *h);
	void readMidiTrackHeader(FILE *fp, struct mtrack *t);
	
	void writelong(FILE *fp, const long l);
	void writeshort(FILE *fp, const short s);
	void writeVarLen(FILE *fp, const vlint v);
	void writeMidiFileHeader(FILE *fp, struct mhead *h);
	void writeMidiTrackHeader(FILE *fp, struct mtrack *t);
	
#ifdef __cplusplus
}
#endif

