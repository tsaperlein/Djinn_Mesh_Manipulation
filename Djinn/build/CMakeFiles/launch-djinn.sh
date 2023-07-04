#!/bin/sh
bindir=$(pwd)
cd /Users/tsaperlein/Desktop/DJINN/Djinn/djinn/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/tsaperlein/Desktop/DJINN/Djinn/build/djinn 
	else
		"/Users/tsaperlein/Desktop/DJINN/Djinn/build/djinn"  
	fi
else
	"/Users/tsaperlein/Desktop/DJINN/Djinn/build/djinn"  
fi
