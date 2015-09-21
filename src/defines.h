/*
 * defines.h
 *
 * Created: 7-9-2015 9:16:32
 *  Author: Eigenaar
 */


#ifndef DEFINES_H_
#define DEFINES_H_

#define DEFINE_TYPE(TYPE, NAME) typedef TYPE NAME NAME; TYPE NAME

DEFINE_TYPE(enum, result) {
	success,
	failure,
};


#endif /* DEFINES_H_ */