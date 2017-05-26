#include "gdt.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "task.h"
#include "sched.h"
#include "string.h"
#include "debug.h"
#include "common.h"

// 全局 pid 值
pid_t now_pid = 0;

// 内核线程创建
int32_t kernel_thread(int (*fn)(void *), void *arg)
{
	struct task_struct *new_task = (struct task_struct *)kmalloc(STACK_SIZE);
	assert(new_task != NULL, "kern_thread: kmalloc error");

	printk("%d size alloced\n", STACK_SIZE);

	// 将栈低端结构信息初始化为 0 
	bzero(new_task, sizeof(struct task_struct));

	new_task->state = TASK_RUNNABLE;
	new_task->stack = current;
	new_task->pid = now_pid++;
	new_task->timepiece = TIME_PIECE_NUMBER;
	new_task->mm = NULL;

	printk("taskaddr: %x\n", new_task);

	uint32_t *stack_top = (uint32_t *)((uint32_t)new_task + STACK_SIZE);

	//
	*(--stack_top) = (uint32_t)new_task;
	//

	*(--stack_top) = (uint32_t)arg;
	*(--stack_top) = (uint32_t)kthread_exit;
	*(--stack_top) = (uint32_t)fn;

	//new_task->context.esp = (uint32_t)new_task + STACK_SIZE - sizeof(uint32_t) * 3;
	new_task->context.esp = (uint32_t)new_task + STACK_SIZE - sizeof(uint32_t) * 4;

	// 设置新任务的标志寄存器未屏蔽中断，很重要
	new_task->context.eflags = 0x200;
	new_task->next = running_proc_head;
	
	// 找到当前进任务队列，插入到末尾
	if(active_tasks <= MAX_TASK_NUMBER){
		running_task_append(new_task);
	}
	//最大线程数已满，填入等待队列中
	else{
		wait_task_append(new_task);
	}
	return new_task->pid;
}

void running_task_append(struct task_struct * task){
	active_tasks += 1;
	struct task_struct *tail = running_proc_head;
	assert(tail != NULL, "Must init sched!");
	while (tail->next != running_proc_head) {
		tail = tail->next;
	}
	tail->next = task;
	task->next = running_proc_head;
}

void wait_task_append(struct task_struct * task){
	struct task_struct * tail = wait_proc_head;
	if(tail == NULL) wait_proc_head = task;
	else{
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = task;
		task->next = NULL;
	}
}

void running_task_cancel(struct task_struct * task){
	struct task_struct * prev = task;
	while(prev->next != task) prev = prev->next;
	prev->next = task->next;
}

void waiting_task_cancel(struct task_struct * task){
	struct task_struct * prev = wait_proc_head;
	while(prev->next != task) prev = prev->next;
	prev->next = task->next;
}

#ifdef SCHEDULE_FIFS//先来先服务算法
void kthread_exit(){
	register uint32_t val asm ("eax");

	printk("current task: %x\n", current);

	printk("Thread %d exited with value %d\n", current -> pid, val);

	//从调度链表中移除线程
	struct task_struct *prev = running_proc_head;
	while (prev -> next != current) prev = prev -> next;
	prev -> next = current -> next;
	////kfree(current);//???????

	if(wait_proc_head != NULL && active_tasks == 1){
		//从等待队列中挑出一个线程
		running_task_append(wait_proc_head);
		wait_proc_head = wait_proc_head->next;
	}

	//直接换到下一个线程中
	change_task_to(current->next);
}
#endif

#ifndef SCHEDULE_FIFS
void kthread_exit()
{
	register uint32_t val asm ("eax");

	printk("current task: %x\n", current);

	printk("Thread %d exited with value %d\n", current -> pid, val);

	//从调度链表中移除线程
	struct task_struct *prev = running_proc_head;
	while (prev -> next != current) prev = prev -> next;
	prev -> next = current -> next;
	//kfree(current);//???????
}
#endif//SCHEDULE_FIFS

