#include "process_data_usr.h"
#include "mainwindow.h"

QScopedPointer<ProcessDataFromUsr> ProcessDataFromUsr::self;

ProcessDataFromUsr::ProcessDataFromUsr()
{
	// this->InitAll();
	// 移动到线程中
	process_thread_ = new QThread;
	this->moveToThread(process_thread_);

	connect(process_thread_, &QThread::started, this, &ProcessDataFromUsr::InitAll);

	process_thread_->start();
}

ProcessDataFromUsr::~ProcessDataFromUsr()
{
	try
	{
        process_thread_->deleteLater();
		process_timer_->deleteLater();

	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.~ProcessDataFromUsr()"<<e.what();
	}
}

void ProcessDataFromUsr::slot_Disconect()
{

    if (m_UdpThread_toUsr != nullptr)
    {
        m_UdpThread_toUsr->requestInterruption(); // requestInterruption() + isInterruptionRequested() 关闭线程

        m_UdpThread_toUsr->quit();
        m_UdpThread_toUsr->terminate();
        m_UdpThread_toUsr->wait();
        delete m_UdpThread_toUsr;
        m_UdpThread_toUsr = nullptr;
    }
}

ProcessDataFromUsr *ProcessDataFromUsr::Instance()
{
	if (self.isNull())
	{
		static QMutex mutex;
		QMutexLocker  locker(&mutex);
		if (self.isNull())
		{
			self.reset(new ProcessDataFromUsr);
		}
	}
	return self.data();
}

//--------------------------------------------------------------------------------------------
void ProcessDataFromUsr::InitAll() // 初始化
{
	// 注册
	qRegisterMetaType<Message_01H>("Message_01H");
    qRegisterMetaType<Message_35H>("Message_35H");
    qRegisterMetaType<Track_Point>("Track_Point");

    qRegisterMetaType<Udp_Parameter>("Udp_Parameter");

	// 初始化网络
	this->InitNetworkToUsr();

	// 初始化定时器
	this->InitTimer();
}

void ProcessDataFromUsr::InitTimer()// 初始化定时器
{
	process_timer_ = new QTimer;
    connect(process_timer_, &QTimer::timeout, this, &ProcessDataFromUsr::slot_PackMessage);
	process_timer_->start(200);
}

void ProcessDataFromUsr::InitNetworkToUsr()
{
	QByteArray rebuffer;
	try
	{
        IP_Local = IPV4StringToInteger(m_updParm.m_Local_IP); 	// 转换程序IP
        Port_Local = m_updParm.m_Local_Port; 					// 转换程序端口号
        IP_Usr = IPV4StringToInteger(m_updParm.m_Remote_IP); 	// 客户终端计算机IP地址
        Port_Usr = m_updParm.m_Remote_Port; 					// 客户终端计算机端口号

        //---------------------------------------nm
		m_UdpThread_toUsr = new QThread();
		m_udp_toUsr       = new QUdpSocket(this);
        m_udp_toUsr->bind(QHostAddress(IP_Local),Port_Local);

		connect(m_udp_toUsr,&QUdpSocket::readyRead,this,&ProcessDataFromUsr::slot_onReceiveMsg);

		m_udp_toUsr->moveToThread(m_UdpThread_toUsr);
		m_UdpThread_toUsr->start(); 
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr.InitNetworkToUsr():"<<e.what();
	}
}

//--------------------------------------------------------------------------------------------
void ProcessDataFromUsr::slot_onReceiveMsg()
{
	try
	{
		if(this->m_udp_toUsr->hasPendingDatagrams())
		{
			this->RxBufLength=this->m_udp_toUsr->readDatagram(this->RxBuf,this->m_udp_toUsr->pendingDatagramSize());
			QByteArray rebuffer = QByteArray(this->RxBuf, static_cast<int>(this->RxBufLength));
			this->UnpackData(rebuffer);
		}
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr.onReceiveMsg():"<<e.what();
	}
}

void ProcessDataFromUsr::UnpackData(QByteArray buffer)
{
	try
	{
		int length_all = buffer.size();
		if (length_all < kMinMsgLength) // 小于最小报文长度
		{
			return;
		}

		int i             = 0; // 读取数据的标号
		int realunpacknum = 0; // 解析到的位置
		while (i < (length_all - 4))
		{
			bool flag = false;
			if ((unsigned char)buffer[i] != 0xaa)
			{
				i++;
				continue;
			}

			realunpacknum = (((unsigned char)buffer[i + 2]) << 8) | ((unsigned char)buffer[i + 3]);
			if ((realunpacknum <= (length_all - i)) && (realunpacknum >= 8))
			{
				flag = CheckMsgSum(buffer.mid(i, realunpacknum));
				if (flag)
				{
					QByteArray array = buffer.mid(i, realunpacknum);
					UnPackOneMsg(array);
				}
			}
			else
			{
				i++;
				continue;
			}

			if (flag)
			{
				i = i + realunpacknum;
			}
			else
			{
				i++;
			}
		}
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr::slot_UnpackData():"<<e.what();
	}
}

void ProcessDataFromUsr::UnPackOneMsg(const QByteArray buffer) // 解包数据
{
	try
	{
		if (buffer.length() < kMinMsgLength)
		{
			return;
		}

		switch (buffer[1])
		{
			case 0x33:
				UnPackTrackMsg(buffer); // 搜索航迹报文
				break;
			case 0x34:
				UnPackFollowTrackMsg(buffer); // 跟踪航迹报文
				break;
			case 0x35: // 数字状态报文
			{
				Message_35H msg;
				memcpy(&msg, buffer, sizeof(Message_35H));

				emit signal_Receive_Msg35H(msg);
				emit signal_UpdateTextEdit_R(buffer);
			}
			default:
				break;
		}
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr.UnPackOneMsg():"<<e.what();
	}
}

bool ProcessDataFromUsr::CheckMsgSum(QByteArray array) // 检查校验和
{
	int length = array.length();
	if (length <= kMinMsgLength)
	{
		return false;
	}
	uint16_t rec_sum       = (((unsigned char)(array[length - 2] & 0xFF)) << 8) + (unsigned char)((array[length - 1] & 0xFF));
	uint16_t calculate_sum = 0;
	for (int i = 0; i < length - 2; i++)
	{
		calculate_sum += (((unsigned char)array[i]) & 0xFF);
	}

	return (rec_sum == calculate_sum);
}

QByteArray ProcessDataFromUsr::CalMsgSum(QByteArray array) // 计算校验和
{
	int length = array.size();
	if (length < kMinMsgLength)
	{
		return array;
	}

	uint16_t calculate_sum = 0;
	for (int i = 0; i < length - 2; i++)
	{
		calculate_sum += (((unsigned char)array[i]) & 0xFF);
	}
	array[length - 2] = (calculate_sum & 0xFF00) >> 8;
	array[length - 1] = (calculate_sum & 0x00FF);
	return array;
}

void ProcessDataFromUsr::UnPackTrackMsg(QByteArray arrays) // 解析搜索航迹报文
{
	int len = arrays.size();
    if (len != 40)
		return;
	uint8_t buffer[len];
	memcpy(&buffer, arrays.data(), len);

	Track_Point m_track;
	// 包序号
	m_track.pag_num = (uint16_t)((buffer[4] << 8) | buffer[5]); // 整个报文的包序号
	m_track.ID      = (uint16_t)((buffer[6] << 8) | buffer[7]);
	if (m_track.ID > m_MaxTrackNum)
	{
		return;
	}
	// 时
	m_track.hour = buffer[9];
	// 分
	m_track.min = buffer[10];
	// 秒
	m_track.sec = buffer[11];
	// 毫秒
	m_track.msec = ((buffer[12] << 8) | buffer[13]);

	// 距离
	m_track.range = (buffer[14] << 8) | buffer[15];
	if (m_track.range > m_MaxRange)
		return;

	// 方位(度)
	double tempUS   = (uint16_t)((buffer[16] << 8) | buffer[17]) * 0.01;
	m_track.azimuth = tempUS;

	// 俯仰(度)
	int16_t temps     = (int16_t)((buffer[18] << 8) | buffer[19]);
	m_track.elevation = temps * 0.01;
	if ((m_track.elevation > 90) || (m_track.elevation < (-90)))
	{
		return;
	}

	// 速度
	m_track.speed = ((uint16_t)((buffer[20] << 8) | buffer[21])) * 0.1;
	if (m_track.speed > 1024)
		return;

	// 航向(°)
	tempUS         = (uint16_t)((buffer[22] << 8) | buffer[23]);
	m_track.course = (uint16_t)(tempUS * 0.01);
	if (m_track.course > 360)
	{
		return;
	}
	// 威胁等级
	m_track.threatLevel = (uint8_t)((buffer[28] & 0xf0) >> 4);
	// 目标类型
	m_track.TargetCategory = (uint8_t)((buffer[28] & 0x0F));

	// 航迹结束标志
	m_track.track_end = (uint8_t)((buffer[29] & 0x20) >> 5);
	// 点迹录取标志
	m_track.sign_exreal = (uint8_t)((buffer[29] & 0x10) >> 4);
	// 航迹质量
	m_track.trackquality = (uint8_t)(buffer[29] & 0x0f);

	// 和强度
	m_track.STR_sum = (uint16_t)((buffer[30] << 8) | buffer[31]);
	// 信噪比
	m_track.snr = buffer[32];
	// 阵面号
	m_track.frontID = buffer[33];

	emit signal_ReceiveTrackMsg(m_track);

    emit signal_UpdateTextEdit_R(arrays);
}

void ProcessDataFromUsr::UnPackFollowTrackMsg(QByteArray arrays) // 解析跟踪航迹报文
{

	int len = arrays.size();
    if (len != 56)
		return;
	uint8_t buffer[len];
	memcpy(&buffer, arrays.data(), len);

	Track_Point m_track;
	// 包序号
	m_track.pag_num = (uint16_t)((buffer[4] << 8) | buffer[5]); // 整个报文的包序号
	m_track.ID      = (uint16_t)((buffer[6] << 8) | buffer[7]);
	if ((m_track.ID > m_MaxTrackNum) || (m_track.ID <= 0))
	{
		return;
	}
	// 时
	m_track.hour = buffer[9];
	// 分
	m_track.min = buffer[10];
	// 秒
	m_track.sec = buffer[11];
	// 毫秒
	m_track.msec = ((buffer[12] << 8) | buffer[13]) * 0.1;

	// 距离
	m_track.range = (buffer[14] << 8) | buffer[15];
	if (m_track.range > m_MaxRange)
		return;

	// 方位(度)
	uint16_t tempUS = (uint16_t)((buffer[16] << 8) | buffer[17]);
	m_track.azimuth = tempUS * 0.01;

	// 俯仰(度)
	double temps      = (int16_t)((buffer[18] << 8) | buffer[19]) * 0.01;
	m_track.elevation = temps;

	// // 高度
	// m_track.height = m_track.range * sin(m_track.elevation * M_PI / 180.0);

	// 速度
	m_track.speed = (uint16_t)((buffer[20] << 8) | buffer[21]);
	if (m_track.speed > 1024)
		return;

	// 航向(°)
	tempUS         = (uint16_t)((buffer[22] << 8) | buffer[23]);
	m_track.course = tempUS * 0.01;

	// 威胁等级
	m_track.threatLevel = (uint8_t)((buffer[28] & 0xF0) >> 4);
	// 目标类型
	m_track.TargetCategory = (uint8_t)((buffer[28] & 0x0F));

	// 航迹结束标志
	m_track.track_end = (uint8_t)((buffer[29] & 0x20) >> 5);
	// 点迹录取标志
	m_track.sign_exreal = (uint8_t)((buffer[29] & 0x10) >> 4);
	// 航迹质量
	m_track.trackquality = (uint8_t)(buffer[29] & 0x0f);

	// 强度
	m_track.STR_sum = (buffer[30] << 8) | buffer[31];

	// 信噪比
	m_track.snr = buffer[32];

	// 跟踪状态
	m_track.state_track = buffer[33];

	// 阵面ID
	m_track.frontID = buffer[50];

	emit signal_ReceiveFollowTrackMsg(m_track);

    emit signal_UpdateTextEdit_R(arrays);
}

//--------------------------------------------------------------------------------------------
void ProcessDataFromUsr::slot_PackMessage() // 打包发送控制指令
{
    this->slot_PackMsg_01H(); //控制命令帧 200ms一次
}

void ProcessDataFromUsr::slot_PackMsg_01H() //控制命令帧 200ms一次
{
	try
	{
        m_gMsg01H.pag_num++;

        Message_01H msg_01H=m_gMsg01H;
        msg_01H.trans();

		QByteArray buffer;
        buffer.append(reinterpret_cast<char *>(&msg_01H), sizeof(Message_01H));
		buffer = CalMsgSum(buffer);
		m_udp_toUsr->writeDatagram(buffer,buffer.length(),QHostAddress(IP_Usr),Port_Usr);
		
        emit signal_UpdateTextEdit_T(buffer);
		//--------------------------------------------------------------
		static int calnum = 0;
		if (m_gMsg01H.TrackingDataMarker == 0x0f)
		{
			calnum++;
			if (calnum >= 5)
			{
				m_gMsg01H.TrackingDataMarker    = 0;
				m_gMsg01H.TrackingTargetNum 	= 0;
				calnum                      	= 0;
			}
		}
		if (m_gMsg01H.TrackingDataMarker == 0xaa)
		{
			calnum++;
			if (calnum >= 5)
			{
				m_gMsg01H.TrackingDataMarker    = 0;
				m_gMsg01H.CancelTrackID 		= 0;
				calnum                  		= 0;
			}
		}
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr.slot_PackMsg_01H():"<<e.what();
	}
}
