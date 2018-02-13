/*
 * Copyright (c) 2003, 2013, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2007, 2013, Red Hat, Inc.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "asm/assembler.hpp"
#include "assembler_zero.inline.hpp"
#include "code/debugInfoRec.hpp"
#include "code/icBuffer.hpp"
#include "code/vtableStubs.hpp"
#include "interpreter/interpreter.hpp"
#include "oops/compiledICHolderOop.hpp"
#include "prims/jvmtiRedefineClassesTrace.hpp"
#include "runtime/sharedRuntime.hpp"
#include "runtime/vframeArray.hpp"
#include "vmreg_zero.inline.hpp"

#ifdef COMPILER1
#include "c1/c1_Runtime1.hpp"
#endif
#ifdef COMPILER2
#include "opto/runtime.hpp"
#endif
#ifdef SHARK
#include "compiler/compileBroker.hpp"
#include "shark/sharkCompiler.hpp"
#endif



static address zero_null_code_stub() {
  address start = ShouldNotCallThisStub();
  return start;
}

int SharedRuntime::java_calling_convention(const BasicType *sig_bt,
                                           VMRegPair *regs,
                                           int total_args_passed,
                                           int is_outgoing) {
  return 0;
}

AdapterHandlerEntry* SharedRuntime::generate_i2c2i_adapters(
                        MacroAssembler *masm,
                        int total_args_passed,
                        int comp_args_on_stack,
                        const BasicType *sig_bt,
                        const VMRegPair *regs,
                        AdapterFingerPrint *fingerprint) {
  return AdapterHandlerLibrary::new_entry(
    fingerprint,
    CAST_FROM_FN_PTR(address,zero_null_code_stub),
    CAST_FROM_FN_PTR(address,zero_null_code_stub),
    CAST_FROM_FN_PTR(address,zero_null_code_stub));
}

nmethod *SharedRuntime::generate_native_wrapper(MacroAssembler *masm,
                                                methodHandle method,
                                                int compile_id,
                                                BasicType *sig_bt,
                                                VMRegPair *regs,
                                                BasicType ret_type) {
#ifdef SHARK
  return SharkCompiler::compiler()->generate_native_wrapper(masm,
                                                            method,
                                                            compile_id,
                                                            sig_bt,
                                                            ret_type);
#else
  ShouldNotCallThis();
  return NULL;
#endif // SHARK
}

int Deoptimization::last_frame_adjust(int callee_parameters,
                                      int callee_locals) {
  return 0;
}

uint SharedRuntime::out_preserve_stack_slots() {
  ShouldNotCallThis();
  return 0;
}

JRT_LEAF(void, zero_stub())
  ShouldNotCallThis();
JRT_END


static RuntimeStub* generate_empty_runtime_stub(const char* name) {
  CodeBuffer buffer(name, 0, 0);
  return RuntimeStub::new_runtime_stub(name, &buffer, 0, 0, NULL, false);
}

static SafepointBlob* generate_empty_safepoint_blob() {
  return CAST_FROM_FN_PTR(SafepointBlob*,zero_stub);
}

static DeoptimizationBlob* generate_empty_deopt_blob() {
  return CAST_FROM_FN_PTR(DeoptimizationBlob*,zero_stub);
}


void SharedRuntime::generate_deopt_blob() {
  _deopt_blob = generate_empty_deopt_blob();
}

SafepointBlob* SharedRuntime::generate_handler_blob(address call_ptr, int poll_type) {
  return generate_empty_safepoint_blob();
}

RuntimeStub* SharedRuntime::generate_resolve_blob(address destination, const char* name) {
  return generate_empty_runtime_stub("resolve_blob");
}


int SharedRuntime::c_calling_convention(const BasicType *sig_bt,
                                         VMRegPair *regs,
                                         VMRegPair *regs2,
                                         int total_args_passed) {
  ShouldNotCallThis();
  return 0;
}

// Do we need to convert ints to longs for c calls?
bool SharedRuntime::c_calling_convention_requires_ints_as_longs() {
  ShouldNotCallThis();
  return false;
}
