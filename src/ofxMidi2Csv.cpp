//
//  ofxMidi2Csv.cpp
//  MIDITOCSV
//
//  Created by rhizomacbookproretina3 on 2013/01/10.
//
//

#include "ofxMidi2Csv.h"

void ofxMidi2Csv::convert(string inputpath, string outputpath){
	struct mhead mh;
	FILE *fp, *fo;
	long track1;
	int i, n, track1l;
	
	
#ifdef _WIN32
	
	/*  If input is from standard input, set the input file
	 mode to binary.  */
	
	if (fp == stdin) {
		_setmode(_fileno(fp), _O_BINARY);
	}
#endif
	
	
	
	fp = fopen(inputpath.c_str(), "rb");
	if(fp == NULL){
		cout << "error " << inputpath <<  endl;
		ofExit();
	}
	fo = fopen(outputpath.c_str(), "w");
	if(fo == NULL){
		cout << "error 2" << endl;
		ofExit();
	}
	
	/* Read and validate header */
	
	readMidiFileHeader(fp, &mh);
	
	if (memcmp(mh.chunktype, "MThd", sizeof mh.chunktype) != 0) {
		fprintf(stderr, "it is not a Standard MIDI File.\n");
		return 2;
	}
	
	if (ofGetLogLevel() == OF_LOG_VERBOSE) {
		fprintf(stderr, "Format %d MIDI file.  %d tracks, %d ticks per quarter note.\n",
				mh.format, mh.ntrks, mh.division);
	}
	
	
	/*	Output header  */
	
	fprintf(fo, "0, 0, Header, %d, %d, %d\n", mh.format, mh.ntrks, mh.division);
	
	/*	Process tracks */
	
	for (i = 0; i < mh.ntrks; i++) {
		struct mtrack mt;
		byte *trk;
		
		if (i == 0) {
			track1 = ftell(fp);
		}
		
		readMidiTrackHeader(fp, &mt);
		if (memcmp(mt.chunktype, "MTrk", sizeof mt.chunktype) != 0) {
			fprintf(stderr, "Track %d header is invalid.\n", i + 1);
			return 2;
		}
		
		if (ofGetLogLevel() == OF_LOG_VERBOSE) {
			fprintf(stderr, "Track %d: length %ld.\n", i + 1, mt.length);
		}
		fprintf(fo, "%d, 0, Start_track\n", i + 1);
		
		trk = (byte *) malloc(mt.length);
		if (trk == NULL) {
			fprintf(stderr, "Cannot allocate %ld bytes for track.\n",
					mt.length);
			return 2;
		}
		
		fread((char *) trk, (int) mt.length, 1, fp);
		if (i == 0) {
			track1l = (int) (ftell(fp) - track1);
		}
		
		trackcsv(fo, i + 1, trk, mt.length, mh.division);
		free(trk);
	}
	return 0;
	
}