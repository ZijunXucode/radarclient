#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QComboBox>

Message_01H m_gMsg01H;
Udp_Parameter m_updParm;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->InitUpdateState();
	this->GetParameter();

	this->InitTableView_Search();
	this->InitTableView_Track();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::InitWidget()
{
    m_updParm.m_Local_IP  = ui->lineEdit_LocalIP->text();
    m_updParm.m_Local_Port = ui->spinBox_LocalPort->value();

    m_updParm.m_Remote_IP = ui->lineEdit_RadarIP->text();
    m_updParm.m_Remote_Port = ui->spinBox_RadarPort->value();

    //---------------------------------------------------------------------------------------------------------------------------------
    connect(ProcessDataFromUsr::Instance(), &ProcessDataFromUsr::signal_Receive_Msg35H, this, &MainWindow::slot_Receive_Msg35H);
    connect(ProcessDataFromUsr::Instance(), &ProcessDataFromUsr::signal_ReceiveFollowTrackMsg, this, &MainWindow::slot_PackTrackInfoTtable);

    connect(ProcessDataFromUsr::Instance(), &ProcessDataFromUsr::signal_ReceiveTrackMsg, this, &MainWindow::slot_AddTrackData);
    connect(ProcessDataFromUsr::Instance(), &ProcessDataFromUsr::signal_UpdateTextEdit_T, this, &MainWindow::slot_UpdateTextEdit_T);
	connect(ProcessDataFromUsr::Instance(), &ProcessDataFromUsr::signal_UpdateTextEdit_R, this, &MainWindow::slot_UpdateTextEdit_R);


    //---------------------------------------------------------------------------------------------------------------------------------
	m_RefreshTimer = new QTimer(this);
    connect(m_RefreshTimer, &QTimer::timeout, this, &MainWindow::slot_UpdateStates);
    m_RefreshTimer->start(1000); // 1秒跟新一次数据
}

void MainWindow::slot_Receive_Msg35H(const Message_35H &msg)
{
	if (m_msg35H.pag_num != msg.pag_num)
	{
		m_msg35H         = msg;
		m_msgReceivetime = QDateTime::currentDateTime().toTime_t();
		if (!m_RefreshTimer->isActive())
		{
			m_RefreshTimer->start(1000);
			slot_UpdateStates();
		}
//        m_gRadarState.FrontLaunch_State[m_frontID] = msg.State_Excitation;
	}
}

void MainWindow::InitUpdateState()
{
	try
	{
		QString strTemp = "--";	

		ui->BtnState_System_Clock_Dect_front1->setText(strTemp);
		ui->BtnState_M10_front1->setText(strTemp);
		ui->BtnState_DDS_front1->setText(strTemp);
		ui->BtnState_Excitation_front1->setText(strTemp);
		ui->BtnState_BWQS_front1->setText(strTemp);
		ui->BtnState_lvib_2_front1->setText(strTemp);
		ui->BtnState_lvib_1_front1->setText(strTemp);
		ui->BtnState_M200_front1->setText(strTemp);
		ui->BtnState_CQPRF_front1->setText(strTemp);
		ui->BtnState_State_Excitation_front1->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front1->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front1->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front1->setText(strTemp);
		ui->lineEdit_Voltage_24_front1->setText(strTemp);
		ui->lineEdit_Current_Fre_front1->setText(strTemp);
		ui->lineEdit_Current_RfFront_front1->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front1->setText(strTemp);
		ui->lineEdit_Temp_Fre_front1->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front2->setText(strTemp);
		ui->BtnState_M10_front2->setText(strTemp);
		ui->BtnState_DDS_front2->setText(strTemp);
		ui->BtnState_Excitation_front2->setText(strTemp);
		ui->BtnState_BWQS_front2->setText(strTemp);
		ui->BtnState_lvib_2_front2->setText(strTemp);
		ui->BtnState_lvib_1_front2->setText(strTemp);
		ui->BtnState_M200_front2->setText(strTemp);
		ui->BtnState_CQPRF_front2->setText(strTemp);
		ui->BtnState_State_Excitation_front2->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front2->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front2->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front2->setText(strTemp);
		ui->lineEdit_Voltage_24_front2->setText(strTemp);
		ui->lineEdit_Current_Fre_front2->setText(strTemp);
		ui->lineEdit_Current_RfFront_front2->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front2->setText(strTemp);
		ui->lineEdit_Temp_Fre_front2->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front3->setText(strTemp);
		ui->BtnState_M10_front3->setText(strTemp);
		ui->BtnState_DDS_front3->setText(strTemp);
		ui->BtnState_Excitation_front3->setText(strTemp);
		ui->BtnState_BWQS_front3->setText(strTemp);
		ui->BtnState_lvib_2_front3->setText(strTemp);
		ui->BtnState_lvib_1_front3->setText(strTemp);
		ui->BtnState_M200_front3->setText(strTemp);
		ui->BtnState_CQPRF_front3->setText(strTemp);
		ui->BtnState_State_Excitation_front3->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front3->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front3->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front3->setText(strTemp);
		ui->lineEdit_Voltage_24_front3->setText(strTemp);
		ui->lineEdit_Current_Fre_front3->setText(strTemp);
		ui->lineEdit_Current_RfFront_front3->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front3->setText(strTemp);
		ui->lineEdit_Temp_Fre_front3->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front4->setText(strTemp);
		ui->BtnState_M10_front4->setText(strTemp);
		ui->BtnState_DDS_front4->setText(strTemp);
		ui->BtnState_Excitation_front4->setText(strTemp);
		ui->BtnState_BWQS_front4->setText(strTemp);
		ui->BtnState_lvib_2_front4->setText(strTemp);
		ui->BtnState_lvib_1_front4->setText(strTemp);
		ui->BtnState_M200_front4->setText(strTemp);
		ui->BtnState_CQPRF_front4->setText(strTemp);
		ui->BtnState_State_Excitation_front4->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front4->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front4->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front4->setText(strTemp);
		ui->lineEdit_Voltage_24_front4->setText(strTemp);
		ui->lineEdit_Current_Fre_front4->setText(strTemp);
		ui->lineEdit_Current_RfFront_front4->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front4->setText(strTemp);
		ui->lineEdit_Temp_Fre_front4->setText(strTemp);        
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.ProcessDataFromUsr::slot_UnpackData():"<<e.what();
	}
}

void MainWindow::slot_UpdateStates()
{
	int nowtime = QDateTime::currentDateTime().toTime_t();

	QString strTemp = "--";
//	if (nowtime - m_msgReceivetime > 5)
    if (false)
	{
		ui->BtnState_System_Clock_Dect_front1->setText(strTemp);
		ui->BtnState_M10_front1->setText(strTemp);
		ui->BtnState_DDS_front1->setText(strTemp);
		ui->BtnState_Excitation_front1->setText(strTemp);
		ui->BtnState_BWQS_front1->setText(strTemp);
		ui->BtnState_lvib_2_front1->setText(strTemp);
		ui->BtnState_lvib_1_front1->setText(strTemp);
		ui->BtnState_M200_front1->setText(strTemp);
		ui->BtnState_CQPRF_front1->setText(strTemp);
		ui->BtnState_State_Excitation_front1->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front1->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front1->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front1->setText(strTemp);
		ui->lineEdit_Voltage_24_front1->setText(strTemp);
		ui->lineEdit_Current_Fre_front1->setText(strTemp);
		ui->lineEdit_Current_RfFront_front1->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front1->setText(strTemp);
		ui->lineEdit_Temp_Fre_front1->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front2->setText(strTemp);
		ui->BtnState_M10_front2->setText(strTemp);
		ui->BtnState_DDS_front2->setText(strTemp);
		ui->BtnState_Excitation_front2->setText(strTemp);
		ui->BtnState_BWQS_front2->setText(strTemp);
		ui->BtnState_lvib_2_front2->setText(strTemp);
		ui->BtnState_lvib_1_front2->setText(strTemp);
		ui->BtnState_M200_front2->setText(strTemp);
		ui->BtnState_CQPRF_front2->setText(strTemp);
		ui->BtnState_State_Excitation_front2->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front2->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front2->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front2->setText(strTemp);
		ui->lineEdit_Voltage_24_front2->setText(strTemp);
		ui->lineEdit_Current_Fre_front2->setText(strTemp);
		ui->lineEdit_Current_RfFront_front2->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front2->setText(strTemp);
		ui->lineEdit_Temp_Fre_front2->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front3->setText(strTemp);
		ui->BtnState_M10_front3->setText(strTemp);
		ui->BtnState_DDS_front3->setText(strTemp);
		ui->BtnState_Excitation_front3->setText(strTemp);
		ui->BtnState_BWQS_front3->setText(strTemp);
		ui->BtnState_lvib_2_front3->setText(strTemp);
		ui->BtnState_lvib_1_front3->setText(strTemp);
		ui->BtnState_M200_front3->setText(strTemp);
		ui->BtnState_CQPRF_front3->setText(strTemp);
		ui->BtnState_State_Excitation_front3->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front3->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front3->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front3->setText(strTemp);
		ui->lineEdit_Voltage_24_front3->setText(strTemp);
		ui->lineEdit_Current_Fre_front3->setText(strTemp);
		ui->lineEdit_Current_RfFront_front3->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front3->setText(strTemp);
		ui->lineEdit_Temp_Fre_front3->setText(strTemp);

		ui->BtnState_System_Clock_Dect_front4->setText(strTemp);
		ui->BtnState_M10_front4->setText(strTemp);
		ui->BtnState_DDS_front4->setText(strTemp);
		ui->BtnState_Excitation_front4->setText(strTemp);
		ui->BtnState_BWQS_front4->setText(strTemp);
		ui->BtnState_lvib_2_front4->setText(strTemp);
		ui->BtnState_lvib_1_front4->setText(strTemp);
		ui->BtnState_M200_front4->setText(strTemp);
		ui->BtnState_CQPRF_front4->setText(strTemp);
		ui->BtnState_State_Excitation_front4->setText(strTemp);
		ui->BtnState_State_RfFront_End_Rece_front4->setText(strTemp);
		ui->BtnState_State_RfFront_End_self_checking_front4->setText(strTemp);
		ui->lineEdit_Temp_RfFront_End_front4->setText(strTemp);
		ui->lineEdit_Voltage_24_front4->setText(strTemp);
		ui->lineEdit_Current_Fre_front4->setText(strTemp);
		ui->lineEdit_Current_RfFront_front4->setText(strTemp);
		ui->lineEdit_Temp_Zynq_front4->setText(strTemp);
		ui->lineEdit_Temp_Fre_front4->setText(strTemp);        

		// emit signal_StateChanged(0);
		if (m_RefreshTimer->isActive())
		{
			m_RefreshTimer->stop();
		}
	}
	else
	{
	//阵面1-------------------------------------------------------------------------
		//Zynq核心板温度	量化至1°有符号数，补码表示
		ui->lineEdit_Temp_Zynq_front1->setText(QString::number(m_msg35H.Temp_Zynq_front1) + "°");
		//系统时钟检测	0：正常 1：故障
		m_msg35H.System_Clock_Dect_front1 ? ui->BtnState_System_Clock_Dect_front1->setText("故障") 
											: ui->BtnState_System_Clock_Dect_front1->setText("正常");
		//CQPRF：0 正常；1 故障
		m_msg35H.CQPRF_front1 ? ui->BtnState_CQPRF_front1->setText("故障") 
								: ui->BtnState_CQPRF_front1->setText("正常");
		//200M：0 正常；1 故障
		m_msg35H.M200_front1 ? ui->BtnState_M200_front1->setText("故障") 
								: ui->BtnState_M200_front1->setText("正常");
		//一本振：0 正常；1 故障
		m_msg35H.lvib_1_front1 ? ui->BtnState_lvib_1_front1->setText("故障") 
								: ui->BtnState_lvib_1_front1->setText("正常");
		//二本振：0 正常；1 故障
		m_msg35H.lvib_2_front1 ? ui->BtnState_lvib_2_front1->setText("故障") 
								: ui->BtnState_lvib_2_front1->setText("正常");
		//激励：0 正常；1 故障
		m_msg35H.Excitation_front1 ? ui->BtnState_Excitation_front1->setText("故障") 
									: ui->BtnState_Excitation_front1->setText("正常");
		//BWQS：0 正常；1 故障
		m_msg35H.BWQS_front1 ? ui->BtnState_BWQS_front1->setText("故障") 
								: ui->BtnState_BWQS_front1->setText("正常");
		//DDS：0 正常；1 故障
		m_msg35H.DDS_front1 ? ui->BtnState_DDS_front1->setText("故障") 
								: ui->BtnState_DDS_front1->setText("正常");
		//10M：0 正常；1 故障
		m_msg35H.M10_front1 ? ui->BtnState_M10_front1->setText("故障") 
								: ui->BtnState_M10_front1->setText("正常");

		// 频综温度
		ui->lineEdit_Temp_Fre_front1->setText(QString::number(m_msg35H.Temp_Fre_front1) + "°");

		//激励状态	0：关 （激励无输出）1：开（激励输出）
		m_msg35H.State_Excitation_front1 ? ui->BtnState_State_Excitation_front1->setText("开：激励输出") 
											: ui->BtnState_State_Excitation_front1->setText("关：激励无输出");
		//射频前端状态 D0 = 1：接收数据正确； D0 = 0：接收数据错误；
		m_msg35H.State_RfFront_End_Rece_front1 ? ui->BtnState_State_RfFront_End_Rece_front1->setText("接收数据正确") 
												: ui->BtnState_State_RfFront_End_Rece_front1->setText("接收数据错误");
		//频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
		m_msg35H.State_RfFront_End_self_checking_front1 ? ui->BtnState_State_RfFront_End_self_checking_front1->setText("芯片自检正确") 
														: ui->BtnState_State_RfFront_End_self_checking_front1->setText("芯片自检错误");
		// 射频前端温度
		ui->lineEdit_Temp_RfFront_End_front1->setText(QString::number(m_msg35H.Temp_RfFront_End_front1) + "°");
		// 24V电压 量化单位 0.1V
		ui->lineEdit_Voltage_24_front1->setText(QString::number(m_msg35H.Voltage_24_front1 * 0.1, 'f', 1) + "V");
		// 频综电流 量化单位 0.1A
		ui->lineEdit_Current_Fre_front1->setText(QString::number(m_msg35H.Current_Fre_front1 * 0.1, 'f', 1) + "A");
		// 射频前端电流 量化单位 0.1A
		ui->lineEdit_Current_RfFront_front1->setText(QString::number(m_msg35H.Current_RfFront_front1 * 0.1, 'f', 1) + "A");

	//阵面2-------------------------------------------------------------------------
		//Zynq核心板温度	量化至1°有符号数，补码表示
		ui->lineEdit_Temp_Zynq_front2->setText(QString::number(m_msg35H.Temp_Zynq_front2) + "°");
		//系统时钟检测	0：正常 1：故障
		m_msg35H.System_Clock_Dect_front2 ? ui->BtnState_System_Clock_Dect_front2->setText("故障") 
											: ui->BtnState_System_Clock_Dect_front2->setText("正常");
		//CQPRF：0 正常；1 故障
		m_msg35H.CQPRF_front2 ? ui->BtnState_CQPRF_front2->setText("故障") 
								: ui->BtnState_CQPRF_front2->setText("正常");
		//200M：0 正常；1 故障
		m_msg35H.M200_front2 ? ui->BtnState_M200_front2->setText("故障") 
								: ui->BtnState_M200_front2->setText("正常");
		//一本振：0 正常；1 故障
		m_msg35H.lvib_1_front2 ? ui->BtnState_lvib_1_front2->setText("故障") 
								: ui->BtnState_lvib_1_front2->setText("正常");
		//二本振：0 正常；1 故障
		m_msg35H.lvib_2_front2 ? ui->BtnState_lvib_2_front2->setText("故障") 
								: ui->BtnState_lvib_2_front2->setText("正常");
		//激励：0 正常；1 故障
		m_msg35H.Excitation_front2 ? ui->BtnState_Excitation_front2->setText("故障") 
									: ui->BtnState_Excitation_front2->setText("正常");
		//BWQS：0 正常；1 故障
		m_msg35H.BWQS_front2 ? ui->BtnState_BWQS_front2->setText("故障") 
								: ui->BtnState_BWQS_front2->setText("正常");
		//DDS：0 正常；1 故障
		m_msg35H.DDS_front2 ? ui->BtnState_DDS_front2->setText("故障") 
								: ui->BtnState_DDS_front2->setText("正常");
		//10M：0 正常；1 故障
		m_msg35H.M10_front2 ? ui->BtnState_M10_front2->setText("故障") 
								: ui->BtnState_M10_front2->setText("正常");

		// 频综温度
		ui->lineEdit_Temp_Fre_front2->setText(QString::number(m_msg35H.Temp_Fre_front2) + "°");

		//激励状态	0：关 （激励无输出）1：开（激励输出）
		m_msg35H.State_Excitation_front2 ? ui->BtnState_State_Excitation_front2->setText("开：激励输出") 
											: ui->BtnState_State_Excitation_front2->setText("关：激励无输出");
		//射频前端状态 D0 = 1：接收数据正确； D0 = 0：接收数据错误；
		m_msg35H.State_RfFront_End_Rece_front2 ? ui->BtnState_State_RfFront_End_Rece_front2->setText("接收数据正确") 
												: ui->BtnState_State_RfFront_End_Rece_front2->setText("接收数据错误");
		//频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
		m_msg35H.State_RfFront_End_self_checking_front2 ? ui->BtnState_State_RfFront_End_self_checking_front2->setText("芯片自检正确") 
														: ui->BtnState_State_RfFront_End_self_checking_front2->setText("芯片自检错误");
		// 射频前端温度
		ui->lineEdit_Temp_RfFront_End_front2->setText(QString::number(m_msg35H.Temp_RfFront_End_front2) + "°");
		// 24V电压 量化单位 0.1V
		ui->lineEdit_Voltage_24_front2->setText(QString::number(m_msg35H.Voltage_24_front2 * 0.1, 'f', 1) + "V");
		// 频综电流 量化单位 0.1A
		ui->lineEdit_Current_Fre_front2->setText(QString::number(m_msg35H.Current_Fre_front2 * 0.1, 'f', 1) + "A");
		// 射频前端电流 量化单位 0.1A
		ui->lineEdit_Current_RfFront_front2->setText(QString::number(m_msg35H.Current_RfFront_front2 * 0.1, 'f', 1) + "A");

	//阵面3-------------------------------------------------------------------------
		//Zynq核心板温度	量化至1°有符号数，补码表示
		ui->lineEdit_Temp_Zynq_front3->setText(QString::number(m_msg35H.Temp_Zynq_front3) + "°");
		//系统时钟检测	0：正常 1：故障
		m_msg35H.System_Clock_Dect_front3 ? ui->BtnState_System_Clock_Dect_front3->setText("故障") 
											: ui->BtnState_System_Clock_Dect_front3->setText("正常");
		//CQPRF：0 正常；1 故障
		m_msg35H.CQPRF_front3 ? ui->BtnState_CQPRF_front3->setText("故障") 
								: ui->BtnState_CQPRF_front3->setText("正常");
		//200M：0 正常；1 故障
		m_msg35H.M200_front3 ? ui->BtnState_M200_front3->setText("故障") 
								: ui->BtnState_M200_front3->setText("正常");
		//一本振：0 正常；1 故障
		m_msg35H.lvib_1_front3 ? ui->BtnState_lvib_1_front3->setText("故障") 
								: ui->BtnState_lvib_1_front3->setText("正常");
		//二本振：0 正常；1 故障
		m_msg35H.lvib_2_front3 ? ui->BtnState_lvib_2_front3->setText("故障") 
								: ui->BtnState_lvib_2_front3->setText("正常");
		//激励：0 正常；1 故障
		m_msg35H.Excitation_front3 ? ui->BtnState_Excitation_front3->setText("故障") 
									: ui->BtnState_Excitation_front3->setText("正常");
		//BWQS：0 正常；1 故障
		m_msg35H.BWQS_front3 ? ui->BtnState_BWQS_front3->setText("故障") 
								: ui->BtnState_BWQS_front3->setText("正常");
		//DDS：0 正常；1 故障
		m_msg35H.DDS_front3 ? ui->BtnState_DDS_front3->setText("故障") 
								: ui->BtnState_DDS_front3->setText("正常");
		//10M：0 正常；1 故障
		m_msg35H.M10_front3 ? ui->BtnState_M10_front3->setText("故障") 
								: ui->BtnState_M10_front3->setText("正常");

		// 频综温度
		ui->lineEdit_Temp_Fre_front3->setText(QString::number(m_msg35H.Temp_Fre_front3) + "°");

		//激励状态	0：关 （激励无输出）1：开（激励输出）
		m_msg35H.State_Excitation_front3 ? ui->BtnState_State_Excitation_front3->setText("开：激励输出") 
											: ui->BtnState_State_Excitation_front3->setText("关：激励无输出");
		//射频前端状态 D0 = 1：接收数据正确； D0 = 0：接收数据错误；
		m_msg35H.State_RfFront_End_Rece_front3 ? ui->BtnState_State_RfFront_End_Rece_front3->setText("接收数据正确") 
												: ui->BtnState_State_RfFront_End_Rece_front3->setText("接收数据错误");
		//频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
		m_msg35H.State_RfFront_End_self_checking_front3 ? ui->BtnState_State_RfFront_End_self_checking_front3->setText("芯片自检正确") 
														: ui->BtnState_State_RfFront_End_self_checking_front3->setText("芯片自检错误");
		// 射频前端温度
		ui->lineEdit_Temp_RfFront_End_front3->setText(QString::number(m_msg35H.Temp_RfFront_End_front3) + "°");
		// 24V电压 量化单位 0.1V
		ui->lineEdit_Voltage_24_front3->setText(QString::number(m_msg35H.Voltage_24_front3 * 0.1, 'f', 1) + "V");
		// 频综电流 量化单位 0.1A
		ui->lineEdit_Current_Fre_front3->setText(QString::number(m_msg35H.Current_Fre_front3 * 0.1, 'f', 1) + "A");
		// 射频前端电流 量化单位 0.1A
		ui->lineEdit_Current_RfFront_front3->setText(QString::number(m_msg35H.Current_RfFront_front3 * 0.1, 'f', 1) + "A");

	//阵面4-------------------------------------------------------------------------
		//Zynq核心板温度	量化至1°有符号数，补码表示
		ui->lineEdit_Temp_Zynq_front4->setText(QString::number(m_msg35H.Temp_Zynq_front4) + "°");
		//系统时钟检测	0：正常 1：故障
		m_msg35H.System_Clock_Dect_front4 ? ui->BtnState_System_Clock_Dect_front4->setText("故障") 
											: ui->BtnState_System_Clock_Dect_front4->setText("正常");
		//CQPRF：0 正常；1 故障
		m_msg35H.CQPRF_front4 ? ui->BtnState_CQPRF_front4->setText("故障") 
								: ui->BtnState_CQPRF_front4->setText("正常");
		//200M：0 正常；1 故障
		m_msg35H.M200_front4 ? ui->BtnState_M200_front4->setText("故障") 
								: ui->BtnState_M200_front4->setText("正常");
		//一本振：0 正常；1 故障
		m_msg35H.lvib_1_front4 ? ui->BtnState_lvib_1_front4->setText("故障") 
								: ui->BtnState_lvib_1_front4->setText("正常");
		//二本振：0 正常；1 故障
		m_msg35H.lvib_2_front4 ? ui->BtnState_lvib_2_front4->setText("故障") 
								: ui->BtnState_lvib_2_front4->setText("正常");
		//激励：0 正常；1 故障
		m_msg35H.Excitation_front4 ? ui->BtnState_Excitation_front4->setText("故障") 
									: ui->BtnState_Excitation_front4->setText("正常");
		//BWQS：0 正常；1 故障
		m_msg35H.BWQS_front4 ? ui->BtnState_BWQS_front4->setText("故障") 
								: ui->BtnState_BWQS_front4->setText("正常");
		//DDS：0 正常；1 故障
		m_msg35H.DDS_front4 ? ui->BtnState_DDS_front4->setText("故障") 
								: ui->BtnState_DDS_front4->setText("正常");
		//10M：0 正常；1 故障
		m_msg35H.M10_front4 ? ui->BtnState_M10_front4->setText("故障") 
								: ui->BtnState_M10_front4->setText("正常");

		// 频综温度
		ui->lineEdit_Temp_Fre_front4->setText(QString::number(m_msg35H.Temp_Fre_front4) + "°");

		//激励状态	0：关 （激励无输出）1：开（激励输出）
		m_msg35H.State_Excitation_front4 ? ui->BtnState_State_Excitation_front4->setText("开：激励输出") 
											: ui->BtnState_State_Excitation_front4->setText("关：激励无输出");
		//射频前端状态 D0 = 1：接收数据正确； D0 = 0：接收数据错误；
		m_msg35H.State_RfFront_End_Rece_front4 ? ui->BtnState_State_RfFront_End_Rece_front4->setText("接收数据正确") 
												: ui->BtnState_State_RfFront_End_Rece_front4->setText("接收数据错误");
		//频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
		m_msg35H.State_RfFront_End_self_checking_front4 ? ui->BtnState_State_RfFront_End_self_checking_front4->setText("芯片自检正确") 
														: ui->BtnState_State_RfFront_End_self_checking_front4->setText("芯片自检错误");
		// 射频前端温度
		ui->lineEdit_Temp_RfFront_End_front4->setText(QString::number(m_msg35H.Temp_RfFront_End_front4) + "°");
		// 24V电压 量化单位 0.1V
		ui->lineEdit_Voltage_24_front4->setText(QString::number(m_msg35H.Voltage_24_front4 * 0.1, 'f', 1) + "V");
		// 频综电流 量化单位 0.1A
		ui->lineEdit_Current_Fre_front4->setText(QString::number(m_msg35H.Current_Fre_front4 * 0.1, 'f', 1) + "A");
		// 射频前端电流 量化单位 0.1A
		ui->lineEdit_Current_RfFront_front4->setText(QString::number(m_msg35H.Current_RfFront_front4 * 0.1, 'f', 1) + "A");
	}
}

void MainWindow::slot_AddTrackData(Track_Point track)   // 增加搜索航迹数据
{
    int i = SearchCnt;

    SearchCnt = (SearchCnt<49) ? (SearchCnt+1) : 0;

	QTableWidgetItem *item = new QTableWidgetItem(QString::number(track.ID));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 0, item);

	item = new QTableWidgetItem(QString::number(track.range));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 1, item);

	item = new QTableWidgetItem(QString::number(track.azimuth, 'f', 2));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 2, item);

	item = new QTableWidgetItem(QString::number(track.elevation, 'f', 2));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 3, item);

	item = new QTableWidgetItem(QString::number(track.speed));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 4, item);

	item = new QTableWidgetItem(QString::number(track.course));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 5, item);

	item = new QTableWidgetItem("无");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setBackgroundColor(QColor(170, 170, 170));
	ui->tableWidget_Search->setItem(i, 6, item);

	i++;

    for (int j = i; j < 50; j++)
    {
        QTableWidgetItem *items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 0, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 1, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 2, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 3, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 4, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 5, items);
        items = new QTableWidgetItem("");
        ui->tableWidget_Search->setItem(j, 6, items);
    }
    ui->tableWidget_Search->viewport()->update();
}

void replaceOrAppendByID(QList<Track_Point>&tracks,const Track_Point & newTrack)
{
    int index=tracks.indexOf(newTrack);
    if(index!=-1)
    {
        tracks.replace(index,newTrack);
    }
    else
        tracks.append(newTrack);
}

void MainWindow::slot_PackTrackInfoTtable(Track_Point track)  // 打包航迹信息
{
    for(int m = 0;m<this->trackedID.size();m++)
    {
        //检查新收到的航迹ID是否在跟踪航迹List内
        if(-1!=this->trackedID.indexOf(track.ID))
        {
            if(this->trackList.size()<=4) //跟踪航迹最多4条
            {
                for(int i = 0; i<4; i++ )
                {
                    if(0==this->trackList.size())
                    {
                       trackList.append(track);
                    }
                    else
                    {
                        replaceOrAppendByID(trackList,track);
                    }
                }
            }
        }
    }
    this->slot_AddTrackingTrackData(trackList);
}

void MainWindow::slot_AddTrackingTrackData(QList<Track_Point> track)  // 增加跟踪航迹数据
{    
    for(int j=0;j<4;j++)
    {
        if(j<track.size())
        {
            int i = j;

            QTableWidgetItem *item = new QTableWidgetItem(QString::number(track[j].ID));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 0, item);

            item = new QTableWidgetItem(QString::number(track[j].range));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 1, item);

            item = new QTableWidgetItem(QString::number(track[j].azimuth, 'f', 2));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 2, item);

            item = new QTableWidgetItem(QString::number(track[j].elevation, 'f', 2));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 3, item);

            item = new QTableWidgetItem(QString::number(track[j].speed));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 4, item);

            item = new QTableWidgetItem(QString::number(track[j].course));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 5, item);

            item = new QTableWidgetItem("无");
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setBackgroundColor(QColor(170, 170, 170));
            ui->tableWidget_Track->setItem(i, 6, item);
        }
        else
        {
            QTableWidgetItem *items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 0, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 1, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 2, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 3, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 4, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 5, items);
            items = new QTableWidgetItem("");
            ui->tableWidget_Track->setItem(j, 6, items);
        }
    }
    ui->tableWidget_Track->viewport()->update();
}

//---------------------------------------------------------------------------------------------
void MainWindow::GetParameter()
{
    // 雷达接收控制 0：关接收 1：开接收
    m_gMsg01H.ReceiveSwitch = ui->comboBox_ReceiveSwitch->currentIndex();
    // 雷达发射控制 0：关发射 1：开发射
    m_gMsg01H.LaunchSwitch = ui->comboBox_LaunchSwitch->currentIndex();

    // 搜索检测门限
    m_gMsg01H.SearchThresholdCtrl = ui->spinBox_SearchThresholdCtrl->value() - 1;
    // 跟踪检测门限
    m_gMsg01H.TrackThresholdCtrl = ui->spinBox_TrackThresholdCtrl->value() - 1;

    //数字处理板自检 0：无效 1：信处自检1 2：信处自检2 3：数据处理自检
    m_gMsg01H.DigitalTestSelf =  ui->comboBox_DigitalTestSelf->currentIndex();
    // 北向角 16bits无符号 0-360°，量化0.01°
    m_gMsg01H.AzimuthFromNorth = ui->doubleSpinBox_AzimuthFromNorth->value() / 0.01;

    // 1号阵面天线预仰角	0～360.00°；量化：0.01°
    m_gMsg01H.PreEleAngleFront1 = ui->doubleSpinBox_PreEleAngle1->value() / 0.01;
    // 2号阵面天线预仰角	0～360.00°；量化：0.01°
    m_gMsg01H.PreEleAngleFront2 = ui->doubleSpinBox_PreEleAngle2->value() / 0.01;
    // 3号阵面天线预仰角	0～360.00°；量化：0.01°
    m_gMsg01H.PreEleAngleFront3 = ui->doubleSpinBox_PreEleAngle3->value() / 0.01;
    // 14号阵面天线预仰角	0～360.00°；量化：0.01°
    m_gMsg01H.PreEleAngleFront4 = ui->doubleSpinBox_PreEleAngle4->value() / 0.01;

    // 频点控制 00: 定频  01：AFT有效 10：频率捷变 11：抗异步干扰
    m_gMsg01H.FreMode = ui->comboBox_FreMode->currentIndex();
    // 1号阵面频点值（定频模式下） 0-9
    m_gMsg01H.FreValueFront1 = ui->comboBox_FreValueFront1->currentIndex();
    // 2号阵面频点值（定频模式下） 0-9
    m_gMsg01H.FreValueFront2 = ui->comboBox_FreValueFront2->currentIndex();
    // 3号阵面频点值（定频模式下） 0-9
    m_gMsg01H.FreValueFront3 = ui->comboBox_FreValueFront3->currentIndex();
    // 4号阵面频点值（定频模式下） 0-9
    m_gMsg01H.FreValueFront4 = ui->comboBox_FreValueFront4->currentIndex();

    // 起航速度MIN
    m_gMsg01H.StartTrackSpeedMin = ui->spinBox_starttrackspeedmin->value();
    // 起航速度MAX
    m_gMsg01H.StartTrackSpeedMAX = ui->spinBox_starttrackspeedmax->value() / 2;
    // 起航高度MIN
    m_gMsg01H.StartTrackheightmin = ui->spinBox_starttrackheightmin->value();
    // 起航高度MAX
    m_gMsg01H.StartTrackheightmax = ui->spinBox_starttrackheightmax->value() / 50;
}

void MainWindow::slot_UpdateTextEdit_T(const QByteArray array)
{
    ui->textEdit_T->insertPlainText(QDateTime::currentDateTime().toString("hh:mm:ss")+" "+array.toHex()+"\n");
    ui->textEdit_T->moveCursor(QTextCursor::End);
}

void MainWindow::slot_UpdateTextEdit_R(const QByteArray array)
{
    ui->textEdit_R->insertPlainText(QDateTime::currentDateTime().toString("hh:mm:ss")+" "+array.toHex()+"\n");
    ui->textEdit_R->moveCursor(QTextCursor::End);
}

void MainWindow::on_Btn_CmdSet_clicked()
{
	this->GetParameter();
}

void MainWindow::on_Btn_TrackTarget_clicked()
{
    try
	{
        if(nullptr!=ui->tableWidget_Search->currentItem())
        {
            int rowIdx=ui->tableWidget_Search->currentRow();

            m_gMsg01H.TrackingDataMarker    = 0x0f;
            m_gMsg01H.TrackingTargetNum 	= ui->tableWidget_Search->item(rowIdx,0)->text().toInt();

            if(!this->trackedID.contains(m_gMsg01H.TrackingTargetNum))
            {
                if(this->trackedID.size()<4) this->trackedID.append(m_gMsg01H.TrackingTargetNum);
            }
        }
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.MainWindow.on_Btn_TrackTarget_clicked():"<<e.what();
	}
}

void MainWindow::on_Btn_UnTrackTarget_clicked()
{
    try
	{
        if(nullptr!=ui->tableWidget_Track->currentItem())
        {
            int rowIdx=ui->tableWidget_Track->currentRow();

            m_gMsg01H.TrackingDataMarker    = 0xaa;
            m_gMsg01H.CancelTrackID 		= ui->tableWidget_Track->item(rowIdx,0)->text().toInt();

            if(this->trackedID.contains(m_gMsg01H.CancelTrackID))
            {
              this->trackedID.removeOne(m_gMsg01H.CancelTrackID);
            }

            for(int i = 0; i<this->trackList.size(); i++ )
            {
                if(this->trackList[i].ID==m_gMsg01H.CancelTrackID)
                {
                  this->trackList.removeOne(trackList[i]);
                }
            }
        }
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.MainWindow.on_Btn_UnTrackTarget_clicked():"<<e.what();
	}  
}

void MainWindow::on_Btn_ClrAllTarget_clicked()
{
    try
	{
		m_gMsg01H.TrackingDataMarker    = 0xaa;
		m_gMsg01H.CancelTrackID 		= 0xFFFF;

        if(!this->trackList.isEmpty()) this->trackList.clear();

        if(!this->trackedID.isEmpty())
        {
          this->trackedID.clear();

            for (int j = 0; j < 4; j++)
            {
                QTableWidgetItem *items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 0, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 1, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 2, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 3, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 4, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 5, items);
                items = new QTableWidgetItem("");
                ui->tableWidget_Track->setItem(j, 6, items);
            }
        }
	}
	catch(std::exception &e)
	{
		qDebug()<<"xxxxxx.MainWindow.on_Btn_ClrAllTarget_clicked():"<<e.what();
	}  
}

void MainWindow::on_Btn_Start_clicked()
{
    try
    {
        if( this->inited == true) return;

        this->InitWidget();
        this->inited = true;
    }
    catch(std::exception &e)
    {
        qDebug()<<"xxxxxx.MainWindow.on_Btn_Start_clicked():"<<e.what();
    }
}

void MainWindow::on_Btn_ClrTx_clicked()
{
    try
    {
        ui->textEdit_T->setText("");
    }
    catch(std::exception &e)
    {
        qDebug()<<"xxxxxx.MainWindow.on_Btn_Start_clicked():"<<e.what();
    }
}

void MainWindow::on_Btn_ClrRx_clicked()
{
    try
    {
        ui->textEdit_R->setText("");
    }
    catch(std::exception &e)
    {
        qDebug()<<"xxxxxx.MainWindow.on_Btn_Start_clicked():"<<e.what();
    }
}
//---------------------------------------------------------------------------------------------
void MainWindow::InitTableView_Search()
{
	// 设置选中时为整行选中
	ui->tableWidget_Search->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 设置为只读模式
	ui->tableWidget_Search->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 隐藏头
	//   ui->tableWidget_Search->horizontalHeader()->hide();
	ui->tableWidget_Search->verticalHeader()->hide();
	// 只选中一行
	ui->tableWidget_Search->setSelectionMode(QAbstractItemView::SingleSelection);
	// 自动全填充
	ui->tableWidget_Search->horizontalHeader()->setStretchLastSection(true);
	// 列宽自动分配
	ui->tableWidget_Search->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// ui->tableWidget_Search->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

	ui->tableWidget_Search->setRowCount(50);
	ui->tableWidget_Search->setColumnCount(7);
	ui->tableWidget_Search->setColumnWidth(0, 50);
	// ui->tableWidget_Search->verticalHeader()->setDefaultSectionSize(10);
	//     //设置行不能拖动
	//     ui->tableWidget_Search->verticalHeader()->setDisabled(true);
	//     //设置列不能拖动
	//     ui->tableWidget_Search->horizontalHeader()->setDisabled(true);
	//  使列宽不能拖动
	ui->tableWidget_Search->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui->tableWidget_Search->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	// 表头字体不变
	ui->tableWidget_Search->horizontalHeader()->setHighlightSections(false);
	// 表头与第一行之间
	ui->tableWidget_Search->horizontalHeader()->setStyleSheet("border-bottom-width: 0.5px;border-style: outset;border-color: rgb(229,229,229);");

	QStringList headers;
	headers << "批号"
			<< "距离(m)"
			<< "方位(°)"
			<< "俯仰(°)"
			<< "速度(m/s)"
			<< "航向(°)"
			<< "属性";

	ui->tableWidget_Search->setHorizontalHeaderLabels(headers);
}

void MainWindow::InitTableView_Track()
{
	// 设置选中时为整行选中
	ui->tableWidget_Track->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 设置为只读模式
	ui->tableWidget_Track->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 隐藏头
	//   ui->tableWidget_Track->horizontalHeader()->hide();
	ui->tableWidget_Track->verticalHeader()->hide();
	// 只选中一行
	ui->tableWidget_Track->setSelectionMode(QAbstractItemView::SingleSelection);
	// 自动全填充
	ui->tableWidget_Track->horizontalHeader()->setStretchLastSection(true);
	// 列宽自动分配
	ui->tableWidget_Track->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// ui->tableWidget_Track->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

	ui->tableWidget_Track->setRowCount(4);
	ui->tableWidget_Track->setColumnCount(7);
	ui->tableWidget_Track->setColumnWidth(0, 50);
	// ui->tableWidget_Track->verticalHeader()->setDefaultSectionSize(10);
	//     //设置行不能拖动
	//     ui->tableWidget_Track->verticalHeader()->setDisabled(true);
	//     //设置列不能拖动
	//     ui->tableWidget_Track->horizontalHeader()->setDisabled(true);
	//  使列宽不能拖动
	ui->tableWidget_Track->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui->tableWidget_Track->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	// 表头字体不变
	ui->tableWidget_Track->horizontalHeader()->setHighlightSections(false);
	// 表头与第一行之间
	ui->tableWidget_Track->horizontalHeader()->setStyleSheet("border-bottom-width: 0.5px;border-style: outset;border-color: rgb(229,229,229);");

	QStringList headers;
	headers << "批号"
			<< "距离(m)"
			<< "方位(°)"
			<< "俯仰(°)"
			<< "速度(m/s)"
			<< "航向(°)"
			<< "属性";

	ui->tableWidget_Track->setHorizontalHeaderLabels(headers);
}
