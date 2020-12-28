// SPDX-License-Identifier: GPL-2-Clause

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <hello1.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Gusakova IV-82\n");
MODULE_DESCRIPTION("Lab7: hello7_1.c\n");

struct timeit_list {
	struct list_head node;
	ktime_t before;
	ktime_t after;
};

static struct list_head head_node = LIST_HEAD_INIT(head_node);

int helloFunction(uint n)
{
	struct timeit_list *list, *tmp;
	uint i;

	BUG_ON(n > 10);

	if (n <= 0) {
		pr_err("Error! n < 0\n");
		return -EINVAL;
	} else if (n == 0) {
		pr_warn("Error! n < 0\n");
	} else if (n >= 5 && n <= 10) {
		pr_warn("Warning! 5 <= n <= 10\n");
	}

	for (i = 0; i < n; i++) {
		list = kmalloc(sizeof(struct timeit_list), GFP_KERNEL);
		if (i == 7)
			list = NULL;
		if (ZERO_OR_NULL_PTR(list))
			goto clean_up;

		list->before = ktime_get();
		pr_info("Hello, world!!!\n");
		list->after = ktime_get();
		list_add_tail(&list->node, &head_node);
	}
	return 0;

clean_up:
	list_for_each_entry_safe(list, tmp, &head_node, node) {
		list_del(&list->node);
		kfree(list);
	}
	pr_err("ERROR!!! Memory is out\n");
	return -ENOMEM;
}
EXPORT_SYMBOL(helloFunction);


static int __init init_hello(void)
{
	pr_info("hello7_1 init\n");
	return 0;
}


static void __exit exit_hello(void)
{
	struct timeit_list *list, *tmp;

	list_for_each_entry_safe(list, tmp, &head_node, node) {
		pr_info("Time: %lld", list->after - list->before);
		list_del(&list->node);
		kfree(list);
	}

	pr_info("hello7_1 exit\n");
}


module_init(init_hello);
module_exit(exit_hello);

