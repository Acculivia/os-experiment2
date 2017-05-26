/*
 * =====================================================================================
 *
 *       Filename:  sched.h
 *
 *    Description:  内核的线程调度
 *
 *        Version:  1.0
 *        Created:  2013年11月22日 16时07分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

////////抢占式？？

#ifndef INCLUDE_SCHEDULER_H_
#define INCLUDE_SCHEDULER_H_

#include "task.h"

// 可调度进程链表
extern struct task_struct *running_proc_head;

// 等待进程链表
extern struct task_struct *wait_proc_head;

// 当前运行的任务
extern struct task_struct *current;
extern int active_tasks;
#define MAX_TASK_NUMBER 10
#define TIME_PIECE_NUMBER 50

// 初始化任务调度
void init_sched();

// 任务调度
void schedule();

// 任务切换准备
void change_task_to(struct task_struct *next);

// 任务切换
void switch_to(struct context *prev, struct context *next);

struct task_struct * find_task_with_priority(struct task_struct * current);

#endif 	// INCLUDE_SCHEDULER_H_
