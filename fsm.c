#include "fsm.h"

/* 状态机注册 */
void fsm_table_regist(fsm_t *pFsm, fsm_table_t *pTable)
{
    pFsm->FsmTable = pTable;
}

/* 状态迁移 */
void fsm_state_transfer(fsm_t *pFsm, int state)
{
    pFsm->curState = state;
}

/*事件处理*/
void fsm_event_handle(fsm_t *pFsm, int event)
{
    int flag = 0;                     // 标识是否满足条件
    void (*ecent_action_fn)() = NULL; // 函数指针初始化为空
    int next_statue;

    int cur_statue = pFsm->curState;
    fsm_table_t *pActTable = pFsm->FsmTable;

    /* 获取当前动作函数 */
    for (uint8_t i = 0; i < pFsm->tableSize; i++)
    {
        // 当且仅当当前状态下来个指定的事件，才执行它 (状态检查)
        if (event == pActTable[i].event && cur_statue == pActTable[i].CurState)
        {
            flag = 1;
            ecent_action_fn = pActTable[i].eventActFun;
            next_statue = pActTable[i].NextState;
            break;
        }
    }

    if (flag) // 如果满足条件了
    {
        /* 动作执行 */
        if (ecent_action_fn)
        {
            ecent_action_fn();
        }
        /* 跳转到下一个状态(状态转移) */
        fsm_state_transfer(pFsm, next_statue);
    }
    else
    {
        // do nothing
    }
}
void fsm_init(fsm_t *pFsm, fsm_table_t *table, int init_statue, uint8_t table_size)
{
    pFsm->tableSize = table_size;
    pFsm->curState = init_statue;  // 初始化状态
    fsm_table_regist(pFsm, table); // 注册状态表
}
