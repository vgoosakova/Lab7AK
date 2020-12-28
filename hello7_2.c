// SPDX-License-Identifier: GPL-2-Clause

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <hello1.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Lab7: hello7_2.c\n");
MODULE_AUTHOR("Gusakova IV-82\n");

static uint n = 1;

module_param(n, uint, 0);
MODULE_PARM_DESC(n, "How many hello you want to print?\n");

static int __init init_hello(void)
{
	pr_info("hello7_2 init\n");
	helloFunction(n);
	return 0;
}

static void __exit exit_hello(void)
{
	pr_info("hello7_2 exit\n");
}

module_init(init_hello);
module_exit(exit_hello);

