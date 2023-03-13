OUT1=out1.res
OUT2=out2.res
OUT3=out3.res

ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

