#
# Copyright (c) 2004, 2011, Oracle and/or its affiliates. All rights reserved.
# Copyright 2012, 2013 SAP AG. All rights reserved.
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#
# This code is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 only, as
# published by the Free Software Foundation.
#
# This code is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# version 2 for more details (a copy is included in the LICENSE file that
# accompanied this code).
#
# You should have received a copy of the GNU General Public License version
# 2 along with this work; if not, write to the Free Software Foundation,
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
# or visit www.oracle.com if you need additional information or have any
# questions.
#  
#

# produce 64 bits object files.
CFLAGS += -m64

# make c code know it is on a 64 bit platform. 
CFLAGS += -D_LP64=1

# fixes `relocation truncated to fit' error for gcc 4.1. 
CFLAGS += -mminimal-toc

# finds use ppc64 instructions, but schedule for power5
CFLAGS += -mcpu=powerpc64 -mtune=power5 -minsert-sched-nops=regroup_exact -mno-multiple -mno-string

# PPC uses safefetch stubs.
CFLAGS += -DSAFEFETCH_STUBS

# let linker produce 64 bit lib.
LFLAGS_VM += -m64

# let linker find external 64 bit libs.
LFLAGS_VM += -L/lib64

# specify lib format.
LFLAGS_VM +=  -Wl,-melf64ppc

# also build launcher as 64 bit executable.
LAUNCHERFLAGS += -m64
LAUNCHERFLAGS += -D_LP64=1
AOUT_FLAGS += -m64
AOUT_FLAGS += -L/lib64
AOUT_FLAGS +=  -Wl,-melf64ppc
