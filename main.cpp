#include <iostream>
#include <fstream>
#include <mecab.h>
#include <string>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "libmecab.lib")
#include "WardList.h"


#define CHECK(eval) if (! eval) { \
   const char *e = tagger ? tagger->what() : MeCab::getTaggerError(); \
   std::cerr << "Exception:" << e << std::endl; \
   delete tagger; \
   return -1; }

int main(void){
	std::string filename;
	std::cout<<"データファイル名を入力してください"<<std::endl;
	std::cin>>filename;
	std::ifstream ifs(filename);
	if(!ifs) std::cout<<"データファイルが開けません"<<std::endl;
	srand((unsigned int)time(NULL));
	MeCab::Tagger *tagger = MeCab::createTagger("");
	WordList wordlist;
	std::string line;
	while(ifs && getline(ifs,line)){
		//std::string result=tagger->parse(line.c_str());
		std::cout << "INPUT: "<<std::endl << line << std::endl;
		std::cout << "RESULT: " <<std::endl;
		const MeCab::Node* node = tagger->parseToNode(line.c_str());
		for (; node->next; node = node->next) {
			std::string result(node->surface, node->length);
			std::string nextresult(node->next->surface,node->next->length);
			std::string feature=node->feature;
			std::string nextfeature=node->next->feature;
			std::cout<<result<<std::endl;
			std::cout<<feature<<std::endl;
			//if( feature.find("名詞") != -1 ) std::cout<<"これは名詞"<<std::endl;
			//std::cout<<nextresult<<std::endl;
			wordlist.addword(result,(feature.find("名詞")!=-1),nextresult,(nextfeature.find("名詞")!=-1));
		}
		//std::cout << "RESULT: " <<std::endl<< result << std::endl;

	}
	for(int i=0;i<20;i++)std::cout<<wordlist.create_sentence()<<std::endl;
	//std::cin>>line;

}

