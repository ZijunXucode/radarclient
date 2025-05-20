#ifndef RADAR_DEFINE_H
#define RADAR_DEFINE_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <QtCore>

static uint32_t IPV4StringToInteger(const QString &ip)
{
	QStringList ips = ip.split(".");
	if (ips.size() == 4)
	{
		return ips.at(3).toInt() | ips.at(2).toInt() << 8 | ips.at(1).toInt() << 16 | ips.at(0).toInt() << 24;
	}
	return 0;
}

static QString IPV4IntegerToString(const uint32_t &Uint_ip)
{
	QString ipcount1 = QString::number((Uint_ip & 0xff000000) >> 24);
	QString ipcount2 = QString::number((Uint_ip & 0x00ff0000) >> 16);
	QString ipcount3 = QString::number((Uint_ip & 0x0000ff00) >> 8);
	QString ipcount4 = QString::number((Uint_ip & 0x000000ff));
	QString IP_addr  = ipcount1 + "." + ipcount2 + "." + ipcount3 + "." + ipcount4;
	return IP_addr;
}

/*/
 * @brief 航迹信息结构体
 */
struct Track_Point
{
	/**
	 * @brief 包序号	2字节，1-65536，量化1
	 */
	uint16_t pag_num;  // 包序号	2字节，1-65536，量化1
	/**
	 * @brief 航迹批号	2字节，取值范围根据项目需求自定义
	 */
	int ID = -1;  // 航迹批号	2字节，取值范围根据项目需求自定义

	uint8_t hour;  // 时
	uint8_t min;   // 分
	uint8_t sec;   // 秒
	double  msec;  // 毫秒

	/**
	 * @brief 目标距离(m)	2字节，量化：1m，取值范围根据项目需求自定义
	 */
	double range;  // 目标距离(m)	2字节，量化：1m，取值范围根据项目需求自定义
	/**
	 * @brief 目标方位(°)	2字节，360/65536°，跟踪为0-5999.99mil,6000/65536mil
	 */
	double azimuth;  // 目标方位(°)	2字节，360/65536°，跟踪为0-5999.99mil,6000/65536mil
	/**
	 * @brief 目标俯仰(°)	2字节，360/65536°补码，取值范围根据项目需求自定义，跟踪为0-5999.99mil,6000/65536mil
	 */
	double elevation;  // 目标俯仰(°)	2字节，360/65536°补码，取值范围根据项目需求自定义
	/**
	 * @brief 目标航速	2字节，量化，1m/s，取值范围根据项目需求自定义
	 */
	double speed = 0;  // 目标航速	2字节，量化，1m/s，取值范围根据项目需求自定义
	/**
	 * @brief 目标航向(°)	2字节，360/65536°，
	 */
	double course;  // 目标航向(°)	2字节，360/65536°，
	/**
	 * @brief 威胁等级	4位，1-10 等级越高威胁越大
	 */
	int threatLevel;  // 威胁等级	4位，1-10 等级越高威胁越大
	/**
	 * @brief 目标类别	4位，取值范围根据项目需求自定义
	 */
	int TargetCategory;  // 目标类别	4位，取值范围根据项目需求自定义
	/**
     * @brief 航迹结束标志	 1位，0无效，1有效
	 */
	uint8_t track_end;  // 航迹结束标志	1位，0无效，1有效
	/**
	 * @brief 点迹外推/录取点标志	0：录取点 1：外推点
	 */
	uint8_t sign_exreal;  // 点迹外推/录取点标志	0：录取点 1：外推点
	/**
	 * @brief 航迹质量	4位，1-10
	 */
	int8_t trackquality;  // 航迹质量	4位，1-10
	/**
	 * @brief 和强度	2字节，0~65536,量化1，需归一化，聚心后强度
	 */
	uint16_t STR_sum;  // 和强度	2字节，0~65536,量化1，需归一化，聚心后强度
	/**
	 * @brief 信噪比(dB)	1字节，聚心后信噪比
	 */
	ushort snr;  // 信噪比(dB)	1字节，聚心后信噪比
    /**
     * @brief 阵面号
     */
    int frontID;  // 阵面号

    /**
     * @brief 跟踪状态 （跟踪航迹报文用）
     */
    uint8_t state_track;//跟踪状态 （跟踪航迹报文用）

	Track_Point()
	{
		memset(this, 0, sizeof(Track_Point));
	}

    bool operator==(const Track_Point &other)
    const{ return ID==other.ID; }
};

#endif  // RADAR_DEFINE_H
