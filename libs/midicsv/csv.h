#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	
	void CSVscanInit(const char *s);
	int CSVscanField(char **b_f, int *b_flen);
	int CSVfieldLength;  	    	/* Length of CSV field scanned */
	
#ifdef __cplusplus
}
#endif

