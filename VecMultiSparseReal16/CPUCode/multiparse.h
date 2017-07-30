
#ifndef PARSE_H_
#define PARSE_H_


void error(const int status, const char * fmt, ...);

uint32_t* parse_args(int argc, char * argv[]);


#endif /* PARSE_H_ */
