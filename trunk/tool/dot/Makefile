#!/bin/bash
SRC ?= trace.data
DOTF ?= visual.dot 
#DOTF=$(wildcard *.dot)
DST=$(patsubst %.dot,%.bmp,${DOTF})

all:flow.bmp
webKit:webKit.bmp
#	for dstfile in $(DST); do \
#	make $${dstfile};\
#	done;

	

%.bmp:%.dot
	dot -Twbmp $< -o $@
clean:
	rm -f flow.bmp
