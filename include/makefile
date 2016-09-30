MIDL = $(MSSDK)\bin\midl

INCLUDE = $(MSSDK)\include;$(BASECLASSES);$(INCLUDE)

all:    vidiface.h

vidiface.h:     vidiface.idl vidprop.h
    $(MIDL) -client none -notlb -h $@ $*.idl

clean: 
        erase /q vidiface.h
        erase /q vidiface_i.c
