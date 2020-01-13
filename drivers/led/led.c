#include "led.h"

static unsigned int major = 0; //主设备号（用于区分设备类）
//static unsigned int minor = 0;  //次设备号（用于区分哪个设备）

int led_init(void)
{
    major = register_chrdev(0, "LED", &led_fops);
    if (major < 0)
    {
        printk(KERN_ERR "Failed to register the device!\n");
        return -1;
    }
    printk("Device registered with MAJOR = %d\n", major);
    return major;
}

void cleanup_module(void)
{
    gpio_t gpio;

    gpio.pConf = ioremap(GPIO_OE, 4); /* 映 射 方 向 寄 存 器 */
    gpio.pDataIn = ioremap(GPIO_IN, 4); /* 映 射 输 入 寄 存 器 */
    gpio.pDataOut = ioremap(GPIO_OUT, 4); /* 映 射 输 出 寄 存 器 */

    led_remove_off(1);
    led_remove_off(2);
    led_remove_off(3);
    iounmap(gpio.pConf);
	iounmap(gpio.pDataOut);
    iounmap(gpio.pDataIn);

	unregister_chrdev(major, "LED");
	printk("LED module reset and removed.\n");
}

int led_open(struct inode* inode, struct file* filp)
{
    gpio_t* gpio;

    filp->private_data = kmalloc(sizeof(gpio_t), GFP_KERNEL);
    gpio = (gpio_t*)(filp->private_data);

    gpio->pConf = ioremap(GPIO_OE, 4); /* 映 射 方 向 寄 存 器 */
    gpio->pDataIn = ioremap(GPIO_IN, 4); /* 映 射 输 入 寄 存 器 */
    gpio->pDataOut = ioremap(GPIO_OUT, 4); /* 映 射 输 出 寄 存 器 */
	*(gpio->pConf) &= ~(7 << 22);
	
    return 0;
}

int led_release(struct inode* inode, struct file* filp)
{
	gpio_t* gpio = (gpio_t*)(filp->private_data);
    printk("Releasing\n");
    //led_off(1);
    //led_off(2);
    //led_off(3);
    iounmap(gpio->pConf);
	iounmap(gpio->pDataOut);
    iounmap(gpio->pDataIn);
    kfree(gpio);
	return 0;
}

ssize_t led_write(struct file* filp, const char* buff, size_t count, loff_t* led_fops)
{
    char c;
    gpio_t* gpio = (gpio_t*)(filp->private_data);

	int uncopied = copy_from_user(&c, buff, sizeof(buff));
	
    int temp[3];
    int i = 0;

    temp[0] = ((unsigned int)(c - 0x30)) & (1 << 0);
    temp[1] = ((unsigned int)(c - 0x30)) & (1 << 1);
    temp[2] = ((unsigned int)(c - 0x30)) & (1 << 2);
    
    for (i = 0; i < 3; ++i)
    {
        if (temp[i])
        {
            printk("Turning LED %d on\n", i);
            led_on(i + 1);
        }
        else
        {
            printk("Turning LED %d off\n", i);
            led_off(i + 1);
        } 
    }

    printk("Write finished\n");
    return sizeof(char) - uncopied;
}

ssize_t led_read(struct file* filp, char* buff, size_t count, loff_t* f_pos)
{
    gpio_t* gpio = (gpio_t*)(filp->private_data);
    int data = *(gpio->pDataOut);
	int copied = copy_to_user(buff, &data, count);

    return copied;
}

module_init(led_init);
MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("LED CONTROLLER");
MODULE_AUTHOR("Minaduki Shigure");