DEPS = bike_app   # this will be the name of your executable

compile: main.cpp linkedlist.h node.h
	g++ main.cpp -o $(DEPS)

run: $(DEPS)
	./$(DEPS) $(var)

clean:
	rm $(DEPS)
