#include <linux/types.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/uaccess.h>

#define GPIO_BASE                       0x4804C000
#define GPIO_OE                         (GPIO_BASE +0x134)
#define GPIO_IN                         (GPIO_BASE +0x138)
#define GPIO_OUT                        (GPIO_BASE +0x13C)

//#define readb(addr) (*(volatile unsigned char*) __io_virt (addr))
//#define readw(addr) (*(volatile unsigned short*) __io_virt (addr))
//#define readl(addr) (*(volatile unsigned int*) __io_virt (addr))
//#define writeb(b,addr) (*(volatile unsigned char*) __io_virt (addr) = (b))
//#define writew(b,addr) (*(volatile unsigned short*) __io_virt (addr) = (b))
//#define writel(b,addr) (*(volatile unsigned int*) __io_virt (addr) = (b))

#define led_on(index) (*(gpio->pDataOut) |= (1 << (21 + index)))
#define led_off(index) (*(gpio->pDataOut) &= ~(1 << (21 + index)))
#define led_remove_off(index) (*(gpio.pDataOut) &= ~(1 << (21 + index)))

int led_open(struct inode* inode, struct file* filp);
int led_release(struct inode* inode, struct file* filp);
ssize_t led_read(struct file* filp, char* buff, size_t count, loff_t* f_pos);
ssize_t led_write(struct file* filp, const char* buff, size_t count, loff_t* f_pos);

typedef struct 
{
	volatile int* pConf;
	volatile int* pDataIn;
	volatile int* pDataOut;
} gpio_t;

struct file_operations led_fops =
{
    .open = led_open,
    .write = led_write,
    .read = led_read,
    .release = led_release
};