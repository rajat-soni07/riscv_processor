INPUT_FILES := $(wildcard ../inputfiles/*)

all:
	g++ -DMODE=0 display.cpp -o noforward
	g++ -DMODE=1 display.cpp -o forward

test:
	@for file in $(INPUT_FILES); do \
        echo "Processing forwarding for $$file"; \
        ./forward $$file 1000; \
    done

	@for file in $(INPUT_FILES); do \
        echo "Processing no-forwarding for $$file"; \
        ./noforward $$file 1000; \
    done
	
clean:
	rm -f noforward forward ../outputfiles/*