//线程调度。

#include "sched.h"
#include "heap.h"
#include "debug.h"

// 可调度进程链表
struct task_struct *running_proc_head = NULL;

// 等待进程链表
struct task_struct *wait_proc_head = NULL;

// 当前运行的任务
struct task_struct *current = NULL;

int active_tasks = 1;

void init_sched()
{
	active_tasks = 1;
	// 为当前执行流创建信息结构体 该结构位于当前执行流的栈最低端
	current = (struct task_struct *)(kern_stack_top - STACK_SIZE);

	current->state = TASK_RUNNABLE;
	current->pid = now_pid++;
	current->stack = current; 	// 该成员指向栈低地址
	current->mm = NULL; 		// 内核线程不需要该成员

	current->priority = 0;
	current->timepiece = TIME_PIECE_NUMBER;

	// 单向循环链表
	current->next = current;

	running_proc_head = current;
}

#ifdef SCHEDULE_FIFS
void schedule(){
	return;
}
#endif//SCHEDULE_FIFS

#ifndef SCHEDULE_FIFS
void schedule() //对时间片和优先级的调度算法
{
	struct task_struct * next = NULL;
	if(active_tasks == 1 && wait_proc_head != NULL){
		//从等待队列中调出一个task

	}
	if(current){
		//时间片
		#ifdef SCHEDULE_WITH_TIMEPIECE
		if(--current->timepiece <= 0){
		#endif//SCHEDULE_WITH_TIMEPIECE
			current->timepiece = TIME_PIECE_NUMBER;
			//优先级
			#ifdef SCHEDULE_WITH_PRIORITY
			next = find_task_with_priority(current);
			#endif//SCHEDULE_WITH_PRIORITY
			#ifndef SCHEDULE_WITH_PRIORITY
			next = current->next;
			#endif//SCHEDULE_WITH_PRIORITY
			change_task_to(next);
		#ifdef SCHEDULE_WITH_TIMEPIECE
		}
		#endif//SCHEDULE_WITH_TIMEPIECE

		#ifndef SCHEDULE_WITH_TIMEPIECE
		//优先级
		#ifdef SCHEDULE_WITH_PRIORITY
		next = find_task_with_priority(current);
		#endif//SCHEDULE_WITH_PRIORITY
		#ifndef SCHEDULE_WITH_PRIORITY
		next = current->next;
		#endif//SCHEDULE_WITH_PRIORITY
		change_task_to(next);
		#endif//SCHEDULE_WITH_TIMEPIECE
	}
}
#endif//SCHEDULE_FIFS

struct task_struct * find_task_with_priority(struct task_struct * current){
	int priority = current->priority;
	struct task_struct * next = current->next;
	if(active_tasks == MAX_TASK_NUMBER){
		//从等待队列中挑出一个
		next = wait_proc_head;
		while(next != NULL){
			if(next->priority >= current->priority){
				waiting_task_cancel(next);
				running_task_append(next);
				change_task_to(next);
			}
			next = next->next;
		}
	}
	else{
		//从运行队列中挑出一个
		while(next != current){
			if(next->priority >= current->priority) return next;
			next = next->next;
		}
	}
}

void change_task_to(struct task_struct *next)
{
	if (current != next) {
		struct task_struct *prev = current;
		current = next;
		printk("switching to proc pid:%d\n", current -> pid);
		switch_to(&(prev->context), &(current->context));
	}
}

