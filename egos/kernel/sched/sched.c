/*
 * =====================================================================================
 *
 *       Filename:  sched.c
 *
 *    Description:  线程调度函数
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 16时11分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "sched.h"
#include "heap.h"
#include "debug.h"

// 可调度进程链表
struct task_struct *running_proc_head = NULL;

// 等待进程链表
struct task_struct *wait_proc_head = NULL;

// 当前运行的任务
struct task_struct *current = NULL;

void init_sched()
{
	// 为当前执行流创建信息结构体 该结构位于当前执行流的栈最低端
	current = (struct task_struct *)(kern_stack_top - STACK_SIZE);

	current->state = TASK_RUNNABLE;
	current->pid = now_pid++;
	current->stack = current; 	// 该成员指向栈低地址
	current->mm = NULL; 		// 内核线程不需要该成员

	current->priority = 0;
	current->timepiece = 50;

	// 单向循环链表
	current->next = current;

	running_proc_head = current;
}

void init_sched_pri(int p)
{
	current = (struct task_struct *)(kern_stack_top - STACK_SIZE);

	current->state = TASK_RUNNABLE;
	current->pid = now_pid++;
	current->stack = current;
	current->mm = NULL;
	current->priority = p;
	current->next = current;
	running_proc_head = current;
}

void schedule()
{
	if (current && (--current->timepiece) <= 0) {//消耗时间片
		current -> timepiece = 50;
		change_task_to(current->next);
	}
}

void schedule_pri()
{
	struct task_struct * next = current->next;
	while (next != NULL && next->priority < current->priority) {  //寻找下一个满足优先级的线程
		next = next->next;
	}
	if(current && (--current->timepiece) > 0) {return;}//消耗时间片  ---> ?????抢占式？？
	if (next == NULL) { return; }  //未找到
	else{  						   //找到
		current -> timepiece = 50;
		change_task_to(next); 
	}
}

void change_task_to(struct task_struct *next)
{
	if (current != next) {
		struct task_struct *prev = current;
		current = next;
		switch_to(&(prev->context), &(current->context));
	}
}

