//============================================================================
// Name        : My_Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#define STARTTIME 0930
#define BASEDATE "2013,01,29"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <map>
#include <stdio.h>
#include <list>

using namespace std;
/*
bool LoadEndTime(){
	TiXmlDocument m_xmlServer;
	if(!m_xmlServer.LoadFile("./bars.xml")){
		printf("file not exist or wrong format: bars.xml\n");
		return false;
		//bSucc = false;
	}else{
		TiXmlElement *pRoot = m_xmlServer.RootElement();
		//m_xmlServer.SaveFile()
		TiXmlElement *pNode = 	pRoot->FirstChildElement();
		while(pNode!=NULL){
			cout<<pNode->FirstChildElement()<<endl;
			//cout<<pNode->FirstAttribute()->value;
			//pNode-
			//pNode->nex
			pNode = pNode->NextSiblingElement();
		}
	}

	return false;
}*/
void byteorder(){
	union{
		short value;
		char union_bytes[sizeof( short )];
	} test;
	test.value = 0x0102;
	if( (test.union_bytes[0] == 1 ) && (test.union_bytes[1] == 2) ){
		cout<<"big endian"<<endl;
	}else if(test.union_bytes[0]==2 && test.union_bytes[1] == 1	){
		cout<<"little endian"<<endl;
	}else{
		cout<<"unknown..."<<endl;
	}
}
static bool stop = false;
static void handle_term(int sig){
	stop = true;
	cout<<"handel_term"<<endl;
}
void ShowMsg(const char*str){
	cout<<str<<endl;
}

int main() {
	/*map<int,string> m_AllSockets;
	list<int> close_sockets;
	signal(SIGTERM,handle_term);
	int _socket = socket(PF_INET, SOCK_STREAM, 0);
	cout<<_socket<<" Main Socket"<<endl;
	sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(2202);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int _bind = bind(_socket,(sockaddr *)&my_addr,sizeof(my_addr));
	assert(_bind!=-1);
	int _listen = listen(_socket,1);
	cout<<_bind<<" "<<_listen<<" "<<errno<<"start..."<<endl;
	int maxFD = _socket;
	fd_set fd_r;
	fd_set fd_w;
	fd_set fd_e;
	timeval timeout;
	timeout.tv_sec=1;
	timeout.tv_usec=0;

	while (!stop){
		//cout<<"sss"<<endl;
		FD_ZERO(&fd_r);
		FD_ZERO(&fd_w);
		FD_ZERO(&fd_e);
		FD_SET(_socket,&fd_r);
		FD_SET(_socket,&fd_w);
		if(!m_AllSockets.empty()){
			map<int,string>::iterator it = m_AllSockets.begin();
			map<int,string>::iterator end = m_AllSockets.end();
			while(it!=end){
				FD_SET(it->first,&fd_r);
				FD_SET(it->first,&fd_e);
				it++;
			}
		}
		int _select = select(maxFD+1,&fd_r,&fd_w,&fd_e,&timeout);

		if(_select == -1){
			cout<<_select<<" : "<<strerror(errno)<<endl;
		}else if(_select == 0){
			//cout<<"sss "<<endl;
			continue;
		}else{
			if(!m_AllSockets.empty()){
				map<int,string>::iterator it = m_AllSockets.begin();
				map<int,string>::iterator end = m_AllSockets.end();
				while(it!=end){
					if(FD_ISSET(it->first,&fd_e)){
						cout<<"error"<<endl;
					}
					if(FD_ISSET(it->first,&fd_r)){
						cout<<"recive data.."<<endl;
						int buf_size = 1024;
						char buffer[buf_size];
						memset(buffer,0,sizeof(buffer));
						int ret = recv(it->first,buffer,buf_size - 1,0);
						if(ret<=0){
							close_sockets.push_back(it->first);
						}
						cout<<"get :"<<ret<<" "<<strerror(errno)<<" "<<buffer<<endl;
					}
					it++;
				}
			}

			list<int>::iterator start = close_sockets.begin();
			list<int>::iterator end   = close_sockets.end();
			while(start!=end){
				map<int,string>::iterator c = m_AllSockets.find(*start);
				if(c!=m_AllSockets.end()){
					m_AllSockets.erase(*start);
					close(*start);
					printf("client disconnected:%d\n",*start);
				}
				start++;
			}
			close_sockets.clear();

			if(FD_ISSET(_socket,&fd_r)){
				cout<<"connect...."<<endl;
				sockaddr_in client;
				socklen_t client_addrlength = sizeof(client);
				//bool flag = true;
				int client_fd = accept(_socket,(sockaddr *)&client,&client_addrlength);
				if(maxFD<client_fd){
					maxFD = client_fd;
				}
				m_AllSockets.insert(pair<int,string>(client_fd,inet_ntoa(client.sin_addr)));
				cout<<"Client: "<<maxFD<< " "<<inet_ntoa(client.sin_addr)<<" "<<client.sin_port<<" "<<m_AllSockets.size()<<endl;

			}

			if(FD_ISSET(_socket,&fd_w)){
				cout<<"fd_w"<<endl;
			}
		}
		//cout<<"s"<<endl;
	}
	cout<<"end..."<<endl;
	close(_socket);*/
	char cBuf[128];
	strcpy(cBuf,"this is My_Test ShowMsg!");
	ShowMsg(cBuf);
	return 0;
}

















/*
	tm tm_;
	time_t t_;
	char buf[128]= {0};

	strcpy(buf, "2012-01-01 14:00:00");
	strptime(buf, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间
	tm_.tm_isdst = -1;
	t_  = mktime(&tm_); //将tm时间转换为秒时间
	t_ += 3600;  //秒数加3600

	tm_ = *localtime(&t_);//输出时间
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", &tm_);
	std::cout << buf << std::endl;

	cout<<" haha:"<<((5&2)>>1)<<" "<<(2&1)<<endl;
*/
