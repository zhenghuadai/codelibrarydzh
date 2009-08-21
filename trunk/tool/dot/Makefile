#!/bin/bash
SRC ?= trace.data
DOTF ?= visual.dot 
#DOTF=$(wildcard *.dot)
DST=$(patsubst %.dot,%.bmp,${DOTF})

#all:flow.bmp
webKit:webKit.gif
#	for dstfile in $(DST); do \
#	make $${dstfile};\
#	done;

	

%.gif:%.dot
	dot -Tgif $< -o $@
clean:
	rm -f webKit.gif 
