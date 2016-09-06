myping: myping.c 
	gcc -o myping myping.c error.c -I. -Wall -ggdb

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ myping
