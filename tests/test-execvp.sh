#!/bin/sh

# Test of execvp().
#
# Copyright (C) 2020-2025 Free Software Foundation, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
#
# Written by Bruno Haible <bruno@clisp.org>, 2020.

rm -rf test-execvp-subdir
mkdir test-execvp-subdir

(cd test-execvp-subdir && PATH="..:$PATH" ${CHECKER} ../test-execvp-main${EXEEXT}) > test-execvp.tmp
result=$?
test $result = 49 || { rm -rf test-execvp-subdir; exit 1; }
LC_ALL=C tr -d '\r' < test-execvp.tmp > test-execvp.out || { rm -rf test-execvp-subdir; exit 1; }

cat > test-execvp.ok <<\EOF
argc = 11
argv[1] = |abc def|
argv[2] = |abc"def"ghi|
argv[3] = |xyz"|
argv[4] = |abc\def\ghi|
argv[5] = |xyz\|
argv[6] = |???|
argv[7] = |***|
argv[8] = ||
argv[9] = |foo|
argv[10] = ||
EOF

: "${DIFF=diff}"
${DIFF} test-execvp.ok test-execvp.out
result=$?

rm -rf test-execvp-subdir test-execvp.tmp test-execvp.out test-execvp.ok

exit $result
