
common  = check.o script.o
objects = $(common) update_boot0.o


edit:$(objects)
	gcc -o update_boot0 $(common) update_boot0.o
	rm -rf $(objects)


clean:
	rm -rf update_boot0 $(objects)
