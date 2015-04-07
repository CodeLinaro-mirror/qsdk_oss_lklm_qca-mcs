/*
 * Copyright (c) 2012, 2015 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "mc_netfilter.h"
#include "mc_netlink.h"
#include "mc_snooping.h"
#include "mc_forward.h"

static int __init mc_init(void)
{
	if (mc_netlink_init())
		goto err0;

	if (mc_netfilter_init())
		goto err1;

	if (mc_snooping_init())
		goto err2;

	if (mc_forward_init())
		goto err3;

	printk("QCA multicast snooping installed successfully\n");
	return 0;
err3:
	mc_snooping_exit();
err2:
	mc_netfilter_exit();
err1:
	mc_netlink_exit();
err0:
	printk("QCA multicast snooping failed to install\n");
	return -1;
}

static void __exit mc_exit(void)
{
	mc_forward_exit();
	mc_netlink_exit();
	mc_netfilter_exit();
	mc_snooping_exit();

	printk("QCA multicast snooping uninstalled\n");
}


module_init(mc_init);
module_exit(mc_exit);
MODULE_LICENSE("GPL v2");

