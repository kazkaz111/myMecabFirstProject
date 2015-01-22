#pragma once
#include<list>

class Word{
public:
	bool existwordlist(std::list<Word>::iterator itr);
	std::string word;
	bool meishi;
	std::list<std::list<Word>::iterator> nextlist; 
};

bool Word::existwordlist(std::list<Word>::iterator itr){
	for(auto cnt_itr=nextlist.begin();cnt_itr!=nextlist.end();cnt_itr++){
		if(itr==(*cnt_itr)) return true;
	}
	return false;
}

class WordList{
public:
	WordList(void);
	void addword(const std::string& firstword,bool firstmeishi,const std::string& nextword,bool nextmeishi);
	std::string create_sentence();
	std::list<Word>::iterator sarch_word(const std::string word,bool* exist);
private:
	std::list<Word> wordlist;
	int meishi_number;
};

WordList::WordList(void){
	meishi_number=0;
}

std::list<Word>::iterator WordList::sarch_word(const std::string word,bool* exist){
	auto itr=wordlist.begin();
	for(;itr!=wordlist.end();itr++){
		if((itr->word==word)){
			*exist=true;
			return itr;
		}
	}
	*exist=false;
	return itr;
}

void WordList::addword(const std::string& firstword,bool firstmeishi,const std::string& nextword,bool nextmeishi){
	std::list<Word>::iterator first_itr,next_itr;
	bool sarchresult;
	first_itr=sarch_word(firstword,&sarchresult);
	if(!sarchresult){
		Word newword;
		newword.word=firstword;
		newword.meishi=firstmeishi;
		wordlist.push_back(newword);
		first_itr=wordlist.end();
		first_itr--;
		if(firstmeishi) meishi_number++;
	}
	next_itr=sarch_word(nextword,&sarchresult);
	if(!sarchresult){
		Word newword;
		newword.word=nextword;
		newword.meishi=nextmeishi;
		wordlist.push_back(newword);
		next_itr=wordlist.end();
		next_itr--;
		if(nextmeishi) meishi_number++;
	}
	if(!first_itr->existwordlist(next_itr)) first_itr->nextlist.push_back(next_itr);
	return;
}

std::string WordList::create_sentence(void){
	std::string result;
	int skip=rand()%meishi_number;
	auto itr=wordlist.begin();
	if(itr->meishi) skip--;
	while(skip>0){
		itr++;
		if(itr->meishi) skip--;
	}
	result=itr->word;
	std::string addstr;
	while(!(addstr=="B"||addstr=="H"||addstr=="I")){
		skip=0;
		skip=rand()%itr->nextlist.size();
		auto nextitr=itr->nextlist.begin();
		for(int i=0;i<skip;i++) nextitr++;
		addstr=(*nextitr)->word;
		result+=addstr;
		itr=(*nextitr);
	}
	return result;
}