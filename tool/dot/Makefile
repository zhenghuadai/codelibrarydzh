#!/bin/bash
SRC ?= trace.data
#DOTF ?= visual.dot 
DOTF=$(wildcard *.dot)
DST=$(patsubst %.dot,%.png,${DOTF})

all:
	for dstfile in $(DST); do \
	make $${dstfile};\
	done;

webKit:webKit.gif
	
define dotrule
%.$1:%.dot
	dot -T$(1) $$< -o $$@
endef

$(eval $(call dotrule,wbmp))
$(eval $(call dotrule,pdf))

%.png:%.dot
	dot -Tpng $< -o $@
%.gif:%.dot
	dot -Tgif $< -o $@
clean:
	rm -f *.wbmp *.png *.jpeg *.gif 
