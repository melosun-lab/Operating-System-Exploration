#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry* entry;

static int proc_count_show(struct seq_file *f, void* v)
{
	struct task_struct *lst;
	int count = 0;
	for_each_process(lst)
	{
		count++;
	}
	seq_printf(f, "%d\n", count);
	return 0;
}

static int __init proc_count_init(void)
{
	pr_info("proc_count: init\n");
	entry = proc_create_single("count", 0, NULL, proc_count_show);
	return 0;
}

static void __exit proc_count_exit(void)
{
	pr_info("proc_count: exit\n");
	proc_remove(entry);
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Chuhua Sun");
MODULE_DESCRIPTION("A module that shows the current number of running processes.");
MODULE_LICENSE("GPL");
