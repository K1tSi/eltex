#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
 
#define procfs_nm "hi_proc"
int len,temp;
 
char *msg;

ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp )
{
	pr_info("read_proc %s\n", filp->f_path.dentry->d_name.name);
    if(count>temp)
    {
        count=temp;
    }
    temp=temp-count;
    copy_to_user(buf,msg, count);
    if(count==0)
        temp=len;
 
    return count;
}
 
ssize_t write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	pr_info("write_proc count: %d\n", count);
    copy_from_user(msg,buf,count);
    len=count;
    temp=len;
    return count;
}
 
struct proc_ops proc_fops = {
.proc_read = read_proc,
.proc_write = write_proc
};
 
void create_new_proc_entry(void)  //use of void for no arguments is compulsory now
{
    proc_create(procfs_nm, 0666,NULL,&proc_fops);
    msg=kmalloc(10*sizeof(char), GFP_KERNEL);
}
 
 
int proc_init (void) {
	pr_info("Hi proc!\n");
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
	pr_info("Good bye proc!\n");
    remove_proc_entry(procfs_nm,NULL);
    kfree(msg);
}
MODULE_LICENSE("LFM");
MODULE_AUTHOR("Nikitak");
MODULE_DESCRIPTION("A Simple Hi_proc module");
module_init(proc_init);
module_exit(proc_cleanup);
