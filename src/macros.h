#ifndef MACROS_H_
#define MACROS_H_

#define DEFINE_TYPE(TYPE, NAME) typedef TYPE NAME NAME; TYPE NAME

#if __GNUC__
#define INTERRUPT_ATTR __attribute__((__interrupt__))
#elif __ICCAVR32__
#define INTERRUPT_ATTR __interrupt
#endif

#define INTERRUPT_FUNCTION(FUNCTIONNAME) INTERRUPT_ATTR static void FUNCTIONNAME(void)

#define clamp(VALUE, LOWER, UPPER) (max(LOWER, min(VALUE, UPPER)))

#endif /* MACROS_H_ */