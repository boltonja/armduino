#
#  Copyright (c) 2011 Arduino.  All right reserved.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

# Makefile for compiling libchip

SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables --no-print-directory

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: silabs_acb_x
#all: libsim_sim3u167_gcc_dbg.a

silabs_acb_x:
	@echo ------------------------------------------------------------------------------------
	@echo --- Making $@
	@echo ---
	@$(MAKE) CHIP=__SIM3U167__ $(SUBMAKE_OPTIONS) OUTPUT_BIN=../../../variants/silabs_acb_x -f sim3.mk
	@echo ------------------------------------------------------------------------------------


.PHONY: libsim_sim3u167_gcc_dbg.a
libsim_sim3u167_gcc_dbg.a:
	@echo ------------------------------------------------------------------------------------
	@echo --- Making $@
	@echo ---
	@$(MAKE) CHIP=__SIM3U167__ DEBUG=1 $(SUBMAKE_OPTIONS) -f sim3.mk
	@echo ------------------------------------------------------------------------------------

.PHONY: libsim_sim3u167_gcc_rel.a
libsim_sim3u167_gcc_rel.a:
	@echo ------------------------------------------------------------------------------------
	@echo --- Making $@
	@echo ---
	@$(MAKE) CHIP=__SIM3U167__ $(SUBMAKE_OPTIONS) -f sim3.mk
	@echo ------------------------------------------------------------------------------------

.PHONY: clean
clean:
	@echo ------------------------------------------------------------------------------------
	@echo --- Cleaning sim3u167 release and debug
	@$(MAKE) CHIP=__SIM3U167__ $(SUBMAKE_OPTIONS) -f sim3.mk $@
	@$(MAKE) CHIP=__SIM3U167__ DEBUG=1 $(SUBMAKE_OPTIONS) -f sim3.mk $@
	@$(MAKE) CHIP=__SIM3U167__ $(SUBMAKE_OPTIONS) OUTPUT_BIN=../../../variants/silabs_acb_x -f sim3.mk $@
	@echo ------------------------------------------------------------------------------------


