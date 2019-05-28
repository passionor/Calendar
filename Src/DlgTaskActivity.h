#ifndef FRMACTIVITY_H
#define FRMACTIVITY_H

#include <QDialog>
#include <QSharedPointer>
#include <QStandardItemModel>
#include "TaskActivity.h"

namespace Ui {
class CDlgTaskActivity;
}

class CDlgTaskActivity : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgTaskActivity(CTaskActivity* task,
                              QWidget *parent = nullptr);
    virtual ~CDlgTaskActivity() override;

    int SetTask(CTaskActivity* task);
    CTaskActivity* GetTask();
    int ApplyTask();

private:
    int Init();
    
private:
    Ui::CDlgTaskActivity *ui;
    CTaskActivity* m_Task;
    QStandardItemModel *m_pModelPrompt;
    CTaskActivity::_TYPE_DATE m_TypeDate;
    CTaskActivity::_ENUM_REPEAT m_Repeat;
    
protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();
    void on_rbSolar_clicked();
    void on_rbLunar_clicked();
    void on_rbOnce_clicked();
    void on_rbEveryDay_clicked();
    void on_rbWeekly_clicked();
    void on_rbMonthly_clicked();
    void on_rbEveryYear_clicked();
    void on_rbCustom_clicked();
    void on_pbPromptAdd_clicked();
    void on_pbPromptRemove_clicked();
};

#endif // FRMACTIVITY_H
