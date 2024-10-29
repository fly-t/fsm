#include "stdio.h"
#include <stdint.h>

typedef struct FsmTable_s
{
    int event;             // 事件
    int CurState;          // 当前状态
    int NextState;         // 下一个状态
    void (*eventActFun)(); // 函数指针
} fsm_table_t;

// 状态机结构体
typedef struct
{
    int curState;          // 当前状态
    fsm_table_t *FsmTable; // 指向状态表的指针
    uint8_t tableSize;     // 状态表大小
} fsm_t;

void fsm_init(fsm_t *pFsm, fsm_table_t *table, int init_statue, uint8_t table_size);
void fsm_event_handle(fsm_t *pFsm, int event);
