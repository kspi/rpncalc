### Compile-time configuration.

# Possible compilation options to add to DEFS:
#   -DHISTORY - writes interactive history to ~/.rpncalc_history
# 
DEFS := -DHISTORY

CFLAGS := -g -ggdb -O0 
LIBS := -lm -lreadline
