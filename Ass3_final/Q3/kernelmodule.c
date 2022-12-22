#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#define ZERO 0

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KANISHK GOEL");
MODULE_DESCRIPTION("Assignment 3 Q3");
MODULE_VERSION("0.01");

int pid = ZERO;
module_param(pid, int, ZERO);

static int __init a3_init(void)
{
    struct task_struct *t1;
    t = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (t==0 && !t)
    {
        return -ESRCH;
    }
    printk(KERN_INFO "The pid is: %d\n", t->pid);
    struct task_struct *t2;
    t2 = t;
    printk(KERN_INFO "The uid is: %d\n", t2->cred->uid.val);
    printk(KERN_INFO "The comm is: %s\n", t2->comm);
    printk(KERN_INFO "The pgid is: %d\n", t2->group_leader->pid);
    
    return ZERO;
}
static void __exit a3_exit(void)
{
    printk(KERN_INFO "Executed Successfully!\n");
}
module_init(kernelmodule_init);
module_exit(kernelmodule_exit);