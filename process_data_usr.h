#ifndef PROCESSDATAFROMUSR_H
#define PROCESSDATAFROMUSR_H

#include <QtCore>
#include <QObject>
#include <QPointF>
#include <QMutex>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "radarmsg.h"

class MainWindow;
class ProcessDataFromUsr : public QObject
{
	Q_OBJECT

public:
	~ProcessDataFromUsr();
    static ProcessDataFromUsr *Instance();

private slots: 
	void InitAll();
	void InitTimer();

private: 

    static QScopedPointer<ProcessDataFromUsr> self;
    ProcessDataFromUsr();

	const int kMinMsgLength = 8;      // 最小报文长度
	int   m_MaxRange        = 30000;  // 最远距离
	int   m_MaxTrackNum     = 400;    // 最大航迹批号

	//------------------------------
	int TxBufLength = 0;
	int RxBufLength = 0;
	char TxBuf[1024];
	char RxBuf[1024];

	QThread    *m_UdpThread_toUsr = nullptr;
	QUdpSocket *m_udp_toUsr       = nullptr;

    uint32_t IP_Local;    // 转换程序IP
    uint16_t Port_Local;  // 转换程序端口号
    uint32_t IP_Usr;      // 客户终端计算机IP地址
    uint16_t Port_Usr;    // 客户终端计算机端口号

	QTimer  *process_timer_;
    QThread *process_thread_;

	void UnPackTrackMsg(QByteArray arrays);        // 解析航迹数据
	void UnPackFollowTrackMsg(QByteArray arrays);  // 解析跟踪航迹数据

private: 
	// void InitAll();
	// void InitTimer();

	bool       CheckMsgSum(QByteArray array);  // 检查校验和
	QByteArray CalMsgSum(QByteArray array);    // 计算校验和

public: 
	void InitNetworkToUsr();                    //面向客户上位机的UDP初始化
	void UnPackOneMsg(const QByteArray array);  // 解包数据
	void UnpackData(QByteArray buffer);         // 接收数据并分包

signals: 
	void signal_ReceiveTrackMsg(const Track_Point track);        // 搜索航迹信号
	void signal_ReceiveFollowTrackMsg(const Track_Point track);  // 跟踪航迹信号

    void signal_Receive_Msg35H(const Message_35H msg);  // 数字状态报文

	void signal_UpdateTextEdit_T(QByteArray array);  // 更新主界面发送报文
	void signal_UpdateTextEdit_R(QByteArray array);  // 更新主界面接收报文

    void Signal_CreateSocketErr(); // 网络初始化错误
public slots: 
	void slot_onReceiveMsg();
	void slot_PackMessage();  // 打包控制命令
	void slot_PackMsg_01H();  //控制命令帧 200ms一次
    void slot_Disconect();
};

#endif // PROCESSDATAFROMUSR_H
