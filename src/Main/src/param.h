#define PARAM_PARSE     0b0001<<0
#define PARAM_TYPECHECK 0b0010<<0
#define PARAM_ASML      0b0100<<0
#define PARAM_ARM       0b1000<<0

#define PARAM_OUTPUT 	0b0001<<4
#define PARAM_ASMLI 	0b0010<<4

#define TOTAL_PARSE 0b00001
#define TOTAL_TYPECHECK 0b00011
#define TOTAL_ASML 0b00111
#define TOTAL_ARM 0b01111


#define enable(param, type) do {param|=type;} while (0)
#define disable(param, type) do {param&=~type;} while(0)

#define is_enabled(param, type) param&type
