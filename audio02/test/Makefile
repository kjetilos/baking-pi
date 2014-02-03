main: main.c sound.o
	gcc $^ -o $@

sound.o: sound
	ld -r -b binary $^ -o $@ 

sound: gas.raw
	cp $^ $@

gas.raw: gas.m4a
	ffmpeg -i $^ -f u16le -acodec pcm_u16le -ar 48000 $@

clean:
	rm -f *.o main
