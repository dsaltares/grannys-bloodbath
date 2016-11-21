#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "animation.h"

using namespace std;

Animation::Animation(const char* frms,int delay2):delay(delay2){

	unsigned size=strlen(frms)+1;
	char* temporary=new char[size];
	char* next;
	NumberFrames=0;

	strcpy(temporary,frms);

	for(next = strtok(temporary, ","); next; ){
		frames.push_back(atoi(next));
		NumberFrames++;
		next = strtok(NULL, ",\0");
    }

	frames.push_back(-1);
	CounterDelay=0;
	ActualFrame=0;

	//free(temporary);
	delete[] temporary;
}

Animation::Animation(int begin,int end,int delay):delay(delay){

	NumberFrames=0;

	for(int i=begin;i<=end;++i){
		frames.push_back(i);
		NumberFrames++;
	}
	frames.push_back(-1);
	CounterDelay=0;
	ActualFrame=0;
}

bool Animation::update(){

	if((++CounterDelay)>=delay){
		CounterDelay=0;
		if(frames[++ActualFrame]==-1){
			ActualFrame=0;
			return true;
		}
	}

	return false;
}
