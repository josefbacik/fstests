# SPDX-License-Identifier: GPL-2.0

TOPDIR = ../..
include $(TOPDIR)/include/builddefs

TARGETS = $(basename $(wildcard *.c))

CFILES = $(TARGETS:=.c)
LDIRT = $(TARGETS)

default: depend $(TARGETS)

depend: .dep

include $(BUILDRULES)

$(TARGETS): $(CFILES)
	@echo "    [CC]    $@"
	$(Q)$(LTLINK) $@.c -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

install:
	$(INSTALL) -m 755 -d $(PKG_LIB_DIR)/src/precontent
	$(INSTALL) -m 755 $(TARGETS) $(PKG_LIB_DIR)/src/precontent

-include .dep

