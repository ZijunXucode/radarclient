#ifndef RADARMSG_H
#define RADARMSG_H

#include "radar_define.h"
#include <QObject>
#include <QtEndian>

struct Udp_Parameter
{
    /**
     * @brief 系统本机IP
     */
    QString m_Local_IP; // 系统本机IP
    /**
     * @brief 系统本机端口号
     */
    uint16_t m_Local_Port; // 系统本机端口号
    /**
     * @brief 远端接收IP
     */
    QString m_Remote_IP; // 远端接收IP
    /**
     * @brief 远端接收端口号
     */
    uint16_t m_Remote_Port; // 远端接收端口号
};

#pragma pack(1) // 消息结构体

/**
 * @brief 控制命令帧 (指控->雷达) 发送，帧频200m
 */
struct Message_01H
{
    /**
     * @brief 起始标识：0xAA
     */
    uint8_t head; // 起始标识：0xAA
    /**
     * @brief 报文类别：0x01
     */
    uint8_t type; // 报文类别：0x01
    /**
     * @brief 报文长度：24
     */
    uint16_t length; // 报文长度：24
    /**
     * @brief 包序号发送一次加1
     */
    uint16_t pag_num; // 包序号发送一次加1
    /**
     * @brief 雷达接收控制 0：关接收 1：开接收
     */
    uint8_t ReceiveSwitch : 1; // 雷达接收控制 0：关接收 1：开接收
    /**
     * @brief 雷达发射控制 0：关发射 1：开发射
     */
    uint8_t LaunchSwitch : 1; // 雷达发射控制 0：关发射 1：开发射
    uint8_t : 6;
    /**
	 * @brief 备用
	 */	
	char reserved1[1];  // 备用
    /**
     * @brief 跟踪检测门限控制	门限1～门限16,默认门限6
     */
    uint8_t TrackThresholdCtrl : 4; // 跟踪检测门限控制	门限1～门限16,默认门限6
    /**
     * @brief 搜索检测门限控制	门限1～门限16,默认门限6
     */
    uint8_t SearchThresholdCtrl : 4; // 搜索检测门限控制	门限1～门限16,默认门限6
    /**
     * @brief 数字处理板自检 0：无效 1：信处自检1 2：信处自检2 3：数据处理自检
     */
    uint8_t DigitalTestSelf : 2; // 数字处理板自检 0：无效 1：信处自检1 2：信处自检2 3：数据处理自检
    uint8_t : 6;
    /**
     * @brief 北向角
     */
    uint16_t AzimuthFromNorth; // 北向角 16bits无符号 0-360°，量化0.01°
    /**
     * @brief 1号阵面天线预仰角	0～360.00°；量化：0.01°
     */
    uint16_t PreEleAngleFront1; // 1号阵面天线预仰角 默认15°	0～360.00°；量化：0.01°
    /**
     * @brief 2号阵面天线预仰角	0～360.00°；量化：0.01°
     */
    uint16_t PreEleAngleFront2; // 2号阵面天线预仰角 默认15°	0～360.00°；量化：0.01°
    /**
     * @brief 3号阵面天线预仰角	0～360.00°；量化：0.01°
     */
    uint16_t PreEleAngleFront3; // 3号阵面天线预仰角 默认15°	0～360.00°；量化：0.01°
    /**
     * @brief 4号阵面天线预仰角	0～360.00°；量化：0.01°
     */
    uint16_t PreEleAngleFront4; // 4号阵面天线预仰角 默认15°	0～360.00°；量化：0.01°
    /**
     * @brief 频点控制
     */
    uint8_t FreMode : 2 ; // 频点控制 00: 定频  01：AFT有效 10：频率捷变 11：抗异步干扰
    uint8_t : 6;
    /**
     * @brief 1号阵面频点值（定频模式下） 0-9
     */
    uint8_t FreValueFront1 : 4; // 1号阵面频点值（定频模式下） 0-9 默认5（F6）
    uint8_t : 4;
    /**
     * @brief 2号阵面频点值（定频模式下） 0-9
     */
    uint8_t FreValueFront2 : 4; // 2号阵面频点值（定频模式下） 0-9 默认5（F6）
    uint8_t : 4;    
    /**
     * @brief 3号阵面频点值（定频模式下） 0-9
     */
    uint8_t FreValueFront3 : 4; // 3号阵面频点值（定频模式下） 0-9 默认5（F6）
    uint8_t : 4;
    /**
     * @brief 4号阵面频点值（定频模式下） 0-9
     */
    uint8_t FreValueFront4 : 4; // 4号阵面频点值（定频模式下） 0-9 默认5（F6）
    uint8_t : 4;    
    /**
     * @brief 最小起航速度：0~1500，量纲：10m/s
     */
    uint8_t StartTrackSpeedMin; // 最小起航速度：0~255，量纲：10m/s
    /**
     * @brief 最大起航速度：0~1500，量纲：10m/s
     */
    uint8_t StartTrackSpeedMAX; // 最大起航速度：0~255，量纲：10m/s    
    /**
     * @brief 最小起航高度：-127～127；量纲：1m(默认-50m)
     */
    uint8_t StartTrackheightmin; // 最小起航高度：-127～127；量纲：1m(默认-50m)
    /**
     * @brief 最大起航高度：0～6000；量纲：50m(默认6000m)
     */
    uint8_t StartTrackheightmax; // 最大起航高度：0～6000；量纲：50m(默认6000m)
    /**
     * @brief 跟踪数据标记：0x0f 跟踪 0xaa 取消跟踪 发5次后清零
     */
    uint8_t TrackingDataMarker; // 跟踪数据标记：0x0f 跟踪 0xaa 取消跟踪 发5次后清零
    /**
     * @brief 跟踪目标编号
     */
    uint16_t TrackingTargetNum; // 跟踪目标编号
    /**
     * @brief 取消跟踪航迹批号	0000H：无效。多目标跟踪时，取消某一个目标，只能删除输入的批号，其他跟踪批号保持跟踪！ ffffH：清除跟踪列表，取消所有跟踪目标
     */
    uint16_t  CancelTrackID; // 取消跟踪航迹批号	0000H：无效。多目标跟踪时，取消某一个目标，只能删除输入的批号，其他跟踪批号保持跟踪！ ffffH：清除跟踪列表，取消所有跟踪目标
    /**
	 * @brief 备用
	 */	
	char reserved2[14];  // 备用
    /**
	 * @brief 校验码：所有字节相加
	 */	   
    uint16_t checkcode; // 校验码：所有字节相加（含报头）

    Message_01H()
    {
        memset(this, 0, sizeof(Message_01H));
        head   = 0xAA;
        type   = 0x01;
        length = 50;
    }
    void trans()
    {
        length          = qToBigEndian(length);
        pag_num         = qToBigEndian(pag_num);

        AzimuthFromNorth = qToBigEndian(AzimuthFromNorth);

        PreEleAngleFront1 = qToBigEndian(PreEleAngleFront1);
        PreEleAngleFront2 = qToBigEndian(PreEleAngleFront2);
        PreEleAngleFront3 = qToBigEndian(PreEleAngleFront3);
        PreEleAngleFront4 = qToBigEndian(PreEleAngleFront4);

        TrackingTargetNum = qToBigEndian(TrackingTargetNum);
        CancelTrackID = qToBigEndian(CancelTrackID);
    }
};

/**
 * @brief 状态信息
 */
struct Message_35H // 状态信息
{
    // 0
    /**
     * @brief 起始标识：0xAA
     */
    uint8_t head; // 起始标识：0xAA
    // 1
    /**
     * @brief 报文类别：0x35
     */
    uint8_t type; // 报文类别：0x35
    // 2-3
    /**
     * @brief 报文长度：50
     */
    uint16_t length; // 报文长度：50
    // 4-5
    /**
     * @brief 包序号发送一次加1
     */
    uint16_t pag_num; // 包序号发送一次加1

    //1号阵面------------------------------------------------
    /**
     * @brief Zynq核心板温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Zynq_front1; // Zynq核心板温度	量化至1°有符号数，补码表示
    /**
     * @brief 系统时钟检测	0：正常 1：故障
     */
    int8_t System_Clock_Dect_front1; // 系统时钟检测	0：正常 1：故障
    /**
     * @brief 10M 0：正常 1：故障
     */
    uint8_t M10_front1 : 1; // 10M 0：正常 1：故障
    /**
     * @brief DDS 0：正常 1：故障
     */
    uint8_t DDS_front1 : 1; // DDS 0：正常 1：故障
    /**
     * @brief BWQS 0：正常 1：故障
     */
    uint8_t BWQS_front1 : 1; // BWQS 0：正常 1：故障
    /**
     * @brief 激励：0 正常；1 故障
     */
    uint8_t Excitation_front1 : 1; // 激励：0 正常；1 故障
    /**
     * @brief 二本振：0 正常；1 故障
     */
    uint8_t lvib_2_front1 : 1; // 二本振：0 正常；1 故障
    /**
     * @brief 一本振：0 正常；1 故障
     */
    uint8_t lvib_1_front1 : 1; // 一本振：0 正常；1 故障
    /**
     * @brief 200M：0 正常；1 故障
     */
    uint8_t M200_front1 : 1; // 200M：0 正常；1 故障
    /**
     * @brief CQPRF：0 正常；1 故障
     */
    uint8_t CQPRF_front1 : 1; // CQPRF：0 正常；1 故障
    /**
     * @brief 频综温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Fre_front1; // 频综温度	量化至1°有符号数，补码表示
    /**
     * @brief 激励状态	0：关 （激励无输出）1：开（激励输出）
     */
    uint8_t State_Excitation_front1 : 1; // 激励状态	0：关 （激励无输出）1：开（激励输出）
    /**
     * @brief 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
     */
    uint8_t State_RfFront_End_Rece_front1 : 1; // 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
    /**
     * @brief 频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
     */
    uint8_t State_RfFront_End_self_checking_front1 : 1; // 射频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
    /**
     * @brief 射频前端温度 −50~+150 有符号数，补码表示
     */
    int16_t Temp_RfFront_End_front1; // 射频前端温度 −50~+150 有符号数，补码表示
    /**
     * @brief 24V电压 量化单位 0.1V
     */
    int8_t Voltage_24_front1; // 24V电压 量化单位 0.1V
    /**
     * @brief 频综电流 量化单位 0.1A
     */
    int8_t Current_Fre_front1; // 频综电流 量化单位 0.1A
    /**
     * @brief 射频前端电流 量化单位 0.1A
     */
    int8_t Current_RfFront_front1; // 射频前端电流 量化单位 0.1A

    //2号阵面------------------------------------------------
    /**
     * @brief Zynq核心板温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Zynq_front2; // Zynq核心板温度	量化至1°有符号数，补码表示
    /**
     * @brief 系统时钟检测	0：正常 1：故障
     */
    int8_t System_Clock_Dect_front2; // 系统时钟检测	0：正常 1：故障
    /**
     * @brief 10M 0：正常 1：故障
     */
    uint8_t M10_front2 : 1; // 10M 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t DDS_front2 : 1; // DDS 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t BWQS_front2 : 1; // BWQS 0：正常 1：故障
    /**
     * @brief 激励：0 正常；1 故障
     */
    uint8_t Excitation_front2 : 1; // 激励：0 正常；1 故障
    /**
     * @brief 二本振：0 正常；1 故障
     */
    uint8_t lvib_2_front2 : 1; // 二本振：0 正常；1 故障
    /**
     * @brief 一本振：0 正常；1 故障
     */
    uint8_t lvib_1_front2 : 1; // 一本振：0 正常；1 故障
    /**
     * @brief 200M：0 正常；1 故障
     */
    uint8_t M200_front2 : 1; // 200M：0 正常；1 故障
    /**
     * @brief CQPRF：0 正常；1 故障
     */
    uint8_t CQPRF_front2 : 1; // CQPRF：0 正常；1 故障
    /**
     * @brief 频综温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Fre_front2; // 频综温度	量化至1°有符号数，补码表示
    /**
     * @brief 激励状态	0：关 （激励无输出）1：开（激励输出）
     */
    uint8_t State_Excitation_front2 : 1; // 激励状态	0：关 （激励无输出）1：开（激励输出）
    /**
     * @brief 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
     */
    uint8_t State_RfFront_End_Rece_front2 : 1; // 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
    /**
     * @brief 频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
     */
    uint8_t State_RfFront_End_self_checking_front2 : 1; // 射频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
    /**
     * @brief 射频前端温度 −50~+150 有符号数，补码表示
     */
    int16_t Temp_RfFront_End_front2; // 射频前端温度 −50~+150 有符号数，补码表示
    /**
     * @brief 24V电压 量化单位 0.1V
     */
    int8_t Voltage_24_front2; // 24V电压 量化单位 0.1V
    /**
     * @brief 频综电流 量化单位 0.1A
     */
    int8_t Current_Fre_front2; // 频综电流 量化单位 0.1A
    /**
     * @brief 射频前端电流 量化单位 0.1A
     */
    int8_t Current_RfFront_front2; // 射频前端电流 量化单位 0.1A

    //3号阵面------------------------------------------------
    /**
     * @brief Zynq核心板温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Zynq_front3; // Zynq核心板温度	量化至1°有符号数，补码表示
    /**
     * @brief 系统时钟检测	0：正常 1：故障
     */
    int8_t System_Clock_Dect_front3; // 系统时钟检测	0：正常 1：故障
    /**
     * @brief 10M 0：正常 1：故障
     */
    uint8_t M10_front3 : 1; // 10M 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t DDS_front3 : 1; // DDS 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t BWQS_front3 : 1; // BWQS 0：正常 1：故障
    /**
     * @brief 激励：0 正常；1 故障
     */
    uint8_t Excitation_front3 : 1; // 激励：0 正常；1 故障
    /**
     * @brief 二本振：0 正常；1 故障
     */
    uint8_t lvib_2_front3 : 1; // 二本振：0 正常；1 故障
    /**
     * @brief 一本振：0 正常；1 故障
     */
    uint8_t lvib_1_front3 : 1; // 一本振：0 正常；1 故障
    /**
     * @brief 200M：0 正常；1 故障
     */
    uint8_t M200_front3 : 1; // 200M：0 正常；1 故障
    /**
     * @brief CQPRF：0 正常；1 故障
     */
    uint8_t CQPRF_front3 : 1; // CQPRF：0 正常；1 故障
    /**
     * @brief 频综温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Fre_front3; // 频综温度	量化至1°有符号数，补码表示
    /**
     * @brief 激励状态	0：关 （激励无输出）1：开（激励输出）
     */
    uint8_t State_Excitation_front3 : 1; // 激励状态	0：关 （激励无输出）1：开（激励输出）
    /**
     * @brief 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
     */
    uint8_t State_RfFront_End_Rece_front3 : 1; // 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
    /**
     * @brief 频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
     */
    uint8_t State_RfFront_End_self_checking_front3 : 1; // 射频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
    /**
     * @brief 射频前端温度 −50~+150 有符号数，补码表示
     */
    int16_t Temp_RfFront_End_front3; // 射频前端温度 −50~+150 有符号数，补码表示
    /**
     * @brief 24V电压 量化单位 0.1V
     */
    int8_t Voltage_24_front3; // 24V电压 量化单位 0.1V
    /**
     * @brief 频综电流 量化单位 0.1A
     */
    int8_t Current_Fre_front3; // 频综电流 量化单位 0.1A
    /**
     * @brief 射频前端电流 量化单位 0.1A
     */
    int8_t Current_RfFront_front3; // 射频前端电流 量化单位 0.1A

    //4号阵面------------------------------------------------
    /**
     * @brief Zynq核心板温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Zynq_front4; // Zynq核心板温度	量化至1°有符号数，补码表示
    /**
     * @brief 系统时钟检测	0：正常 1：故障
     */
    int8_t System_Clock_Dect_front4; // 系统时钟检测	0：正常 1：故障
    /**
     * @brief 10M 0：正常 1：故障
     */
    uint8_t M10_front4 : 1; // 10M 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t DDS_front4 : 1; // DDS 0：正常 1：故障
    /**
     * @brief 0：正常 1：故障
     */
    uint8_t BWQS_front4 : 1; // BWQS 0：正常 1：故障
    /**
     * @brief 激励：0 正常；1 故障
     */
    uint8_t Excitation_front4 : 1; // 激励：0 正常；1 故障
    /**
     * @brief 二本振：0 正常；1 故障
     */
    uint8_t lvib_2_front4 : 1; // 二本振：0 正常；1 故障
    /**
     * @brief 一本振：0 正常；1 故障
     */
    uint8_t lvib_1_front4 : 1; // 一本振：0 正常；1 故障
    /**
     * @brief 200M：0 正常；1 故障
     */
    uint8_t M200_front4 : 1; // 200M：0 正常；1 故障
    /**
     * @brief CQPRF：0 正常；1 故障
     */
    uint8_t CQPRF_front4 : 1; // CQPRF：0 正常；1 故障
    /**
     * @brief 频综温度	量化至1°有符号数，补码表示
     */
    int8_t Temp_Fre_front4; // 频综温度	量化至1°有符号数，补码表示
    /**
     * @brief 激励状态	0：关 （激励无输出）1：开（激励输出）
     */
    uint8_t State_Excitation_front4 : 1; // 激励状态	0：关 （激励无输出）1：开（激励输出）
    /**
     * @brief 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
     */
    uint8_t State_RfFront_End_Rece_front4 : 1; // 射频前端状态D0 = 1：接收数据正确； D0 = 0：接收数据错误；
    /**
     * @brief 频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
     */
    uint8_t State_RfFront_End_self_checking_front4 : 1; // 射频前端状态D1= 1：芯片自检正确； D1 = 0：芯片自检错误；
    /**
     * @brief 射频前端温度 −50~+150 有符号数，补码表示
     */
    int16_t Temp_RfFront_End_front4; // 射频前端温度 −50~+150 有符号数，补码表示
    /**
     * @brief 24V电压 量化单位 0.1V
     */
    int8_t Voltage_24_front4; // 24V电压 量化单位 0.1V
    /**
     * @brief 频综电流 量化单位 0.1A
     */
    int8_t Current_Fre_front4; // 频综电流 量化单位 0.1A
    /**
     * @brief 射频前端电流 量化单位 0.1A
     */
    int8_t Current_RfFront_front4; // 射频前端电流 量化单位 0.1A

    // 48-49
    uint16_t : 16;
    // 50-51
    uint16_t checkcode; // 校验码：所有字节相加
};

#pragma pack()

#endif // RADARMSG_H
