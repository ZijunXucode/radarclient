#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>
#include <QString>

#include "process_data_usr.h"
#include "radarmsg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern Message_01H m_gMsg01H;
extern Udp_Parameter m_updParm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitTableView_Search();  // 初始化搜索航迹显示框
    void InitTableView_Track();  // 初始化航跟踪迹显示框    
    
    void InitUpdateState();
    void GetParameter();  // 定时更新状态

private:
    Ui::MainWindow *ui;
    void InitWidget();

    /**
     * @brief 刷新状态定时器
     */
    QTimer *m_RefreshTimer = nullptr;  // 刷新状态定时器

    /**
     * @brief 最后接收的时间
     */
    uint m_msgReceivetime = 0;  // 最后接收的时间
    int m_frontID = -1;
    Message_35H m_msg35H;

    uint16_t SearchCnt = 0;
    uint16_t trackCnt = 0;
    bool inited =false;

    QList<uint16_t> trackedID;
    QList<Track_Point> trackList;

public slots:
    void slot_Receive_Msg35H(const Message_35H &msg);
    void slot_UpdateStates();

    void slot_AddTrackData(Track_Point track);  // 增加搜索航迹数据
    void slot_AddTrackingTrackData(QList<Track_Point> track);  // 增加跟踪航迹数据
    void slot_UpdateTextEdit_T(const QByteArray array);
    void slot_UpdateTextEdit_R(const QByteArray array);
    void slot_PackTrackInfoTtable(Track_Point track);  // 打包航迹信息

private slots:
    void on_Btn_CmdSet_clicked();    
    void on_Btn_TrackTarget_clicked();
    void on_Btn_UnTrackTarget_clicked();
    void on_Btn_ClrAllTarget_clicked();
    void on_Btn_Start_clicked();
    void on_Btn_ClrTx_clicked();
    void on_Btn_ClrRx_clicked();
};
#endif // MAINWINDOW_H
