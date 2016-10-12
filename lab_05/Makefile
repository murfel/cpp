INCLUDE=include/
CFLAGS=-I$(INCLUDE) -std=c99
OBJS := bin/main.o bin/position.o bin/clist.o

# link
proggie: $(OBJS)
	gcc $(OBJS) -o proggie

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
bin/%.o: src/%.c
	mkdir -p bin
	gcc -c $(CFLAGS) src/$*.c -o bin/$*.o
	gcc -MM $(CFLAGS) src/$*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

# remove compilation products
clean:
	rm -f proggie bin/*.o *.d
