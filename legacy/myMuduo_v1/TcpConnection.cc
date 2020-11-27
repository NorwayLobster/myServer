 ///
 /// @file    TcpConnection.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 12:14:53
 ///
 
#include "TcpConnection.hpp"
//TcpConnection::TcpConnection(InetAddress&localInetAddr,InetAddress&peerInetAddr,SocketIO&sockio,Socket&sock):
TcpConnection::TcpConnection(int sockfd)
:_localInetAddr(Socket::getLocalAddrBySockFd(sockfd))
,_peerInetAddr(Socket::getPeerAddrBySockFd(sockfd))
,_sock(sockfd)
,_sockIO(sockfd)
,_isShutDownWrite(false)
{
	cout<<"TcpConnection"<<endl;
}
TcpConnection::~TcpConnection(){
	if(!_isShutDownWrite){
		_isShutDownWrite=true;
		_sock.shutDownWrite();
	}
	cout<<"~TcpConnection"<<endl;
}
void TcpConnection::send(char * message,int len){
//void TcpConnection::send(const string& message){
	//string 连续地址
	_sockIO.writen((char*)&len,sizeof(size_t));
	_sockIO.writen(message,len);
//	_sockIO.writen(message.c_str(),message.size());
//	_sockIO.writen(message.c_str(),message.size());
}
string TcpConnection::receive(){
	size_t len;
	_sockIO.readn((char*)&len,sizeof(size_t));//data header
	char buf[len+1];
	_sockIO.readn(buf,len);//data body
	return string(buf);
}
void TcpConnection::shutDownWrite(){
	if(!_isShutDownWrite){
		_sock.shutDownWrite();
		_isShutDownWrite=true;
	}
}
void TcpConnection::sendInLoop(){
//	sendn();
}
string TcpConnection::info(){
//	char buf[INT_MAX];//core dump
	char buf[1000];
//	memset(buf,0,sizeof(buf));
	snprintf(buf,INT_MAX,"%s:%d->%s:%d",_localInetAddr.ip().c_str(),_localInetAddr.h_port(),_peerInetAddr.ip().c_str(),_peerInetAddr.h_port());
	return string(buf);
}
void TcpConnection::setTcpConnection_onCloseEventCb(TcpConnectionCallback cb){
	_onCloseEventCb=cb;
}
void TcpConnection::setTcpConnection_onMessageEventCb(TcpConnectionCallback cb){
	_onMessageEventCb=cb;
}
void TcpConnection::setTcpConnection_onConnectEventCb(TcpConnectionCallback cb){
	_onConnectEventCb=cb;
}
