#
# Leave the following lines alone!!!

%.o: %.asm
	nasm -g -f elf -l $*.lst $< -o $@

#
# End of provided rules
#

# Modify following to the name of your linked program
TARGET=mytest3.out

# Modify following to the list of component object files
OBJS=mytest3.o prt_dec.o

#
# Do not modify remainder of this Makefile
#
${TARGET}: ${OBJS}
	${LD} -g ${OBJS} -melf_i386 -o ${TARGET}

run:
	./${TARGET}