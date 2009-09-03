#  - ADD_PLUGIN(name [WITH_PREFIX] file1 .. fileN)
#
#  Create a plugin from the given source files.
#  If WITH_PREFIX is given, the resulting plugin will have the
#  prefix "lib", otherwise it won't.
#
# Copyright (c) 2006, Alexander Neundorf, <neundorf@kde.org>
# Copyright (c) 2006, Laurent Montel, <montel@kde.org>
# Copyright (c) 2006, Andreas Schneider, <mail@cynapses.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

macro (ADD_PLUGIN _target_NAME _with_PREFIX)

  if (${_with_PREFIX} STREQUAL "WITH_PREFIX")
    set(_first_SRC)
  else (${_with_PREFIX} STREQUAL "WITH_PREFIX")
    set(_first_SRC ${_with_PREFIX})
  endif (${_with_PREFIX} STREQUAL "WITH_PREFIX")

  add_library(${_target_NAME} MODULE ${_first_SRC} ${ARGN})

  if (_first_SRC)
    set_target_properties(${_target_NAME} PROPERTIES PREFIX "")
  endif (_first_SRC)

endmacro (ADD_PLUGIN _name _sources)
