#include "fsm.h"
#include <unistd.h>

typedef enum
{
    STATUS_ICE_OPEN,
    STATUS_ICE_ELEPHANT_IN,
    STATUS_ICE_CLOSE,
} status_t;

typedef enum
{
    EVENT_OPEN_ICE_BOX = 0,
    EVENT_PUSH_ELEPHANT,
    EVENT_CLOSE_ICE_BOX,
} event_t;

// 示例函数
void open_icebox() { printf("open_icebox...\n"); }
void close_icebox() { printf("close_icebox...\n"); }
void push_elephant() { printf("push_elephant...\n"); }

fsm_table_t table_elephant[] = {
    // {到来的事件，     当前的状态，     将要要执行的函数，     下一个状态}
    {EVENT_OPEN_ICE_BOX, STATUS_ICE_CLOSE, open_icebox, STATUS_ICE_OPEN},
    {EVENT_PUSH_ELEPHANT, STATUS_ICE_OPEN, push_elephant, STATUS_ICE_ELEPHANT_IN},
    {EVENT_CLOSE_ICE_BOX, STATUS_ICE_ELEPHANT_IN, close_icebox, STATUS_ICE_CLOSE},
};

int main()
{
    fsm_t fsm_push_elephant;
    fsm_init(&fsm_push_elephant, table_elephant, STATUS_ICE_CLOSE, sizeof(table_elephant) / sizeof(fsm_table_t));

    while (1)
    {
        /* 到来的事件 */
        event_t event = EVENT_OPEN_ICE_BOX;
        fsm_event_handle(&fsm_push_elephant, event);
        event = (event + 1) % 3;
        sleep(1); // 休眠1秒，方便观察
    }

    return 0;
}