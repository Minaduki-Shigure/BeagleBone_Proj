# 数字系统II 实验 报告四
Copyright (c) 2019 Minaduki Shigure.  
南京大学 电子科学与工程学院 吴康正 171180571  
项目repo地址：https://git.nju.edu.cn/Minaduki/beaglebone_proj

## 实验目的
1. 了解软件层次结构，学习解决依赖关系。
2. 在提供的嵌入式平台上通过源码移植一个应用软件。
3. 通过USB声卡和移植的MPlayer播放音频文件。
4. 通过HDMI显示器播放简单的视频文件。

## 实验环境
### 1. 硬件环境
实验使用了TI的BeagleBone Black开发板作为实验环境，其参数如下：
* 处理器：基于ARM Cortex-A8架构的TI AM3359 Sitara @ 1GHz
* 内存：板载512MiB DDR3
* 存储：板载4GiB 8-bit eMMC闪存
* 拓展存储：支持micro SD存储卡
* 网络界面：RJ-45接口百兆以太网
* 数字多媒体输出：micro HDMI接口
* 拓展接口：UART、GPIO、SPI、I2C等  
* USB声卡

使用的显示器：
* 分辨率：最大1920*1080
* 色彩空间：RGB565

### 2. 软件环境
* 上位机：使用Ubuntu 19.10系统的x86 PC
* Linux源码：[版本4.4.155]("https://git.nju.edu.cn/Minaduki/linux")
* Busybox源码：[版本1.30.1]("https://git.nju.edu.cn/Minaduki/beaglebone_proj/tree/master/busybox-1.30.1")
* 编译器：The GNU Compiler Collection 9.2.1
* bootloader：U-boot
* zlib源码：版本1.2.11
* libmad源码：版本0.15.1b
* ffmpeg源码：版本4.2
* mplayer源码：版本1.4

### 3. 网络环境
* 网关：192.168.208.254
* 上位机：192.168.208.35
* 开发板：192.168.208.121

## 实验原理
> 关于实验原理：  
具体的实验原理中，实验指导书有所提及的在这里不再重复叙述。这里仅进行一些补充说明。

### 依赖关系
Mplayer依赖于以下程序：
* zlib: 包含了常用的压缩程序的动态链接库
* libmad: 高品质全定点算法的 MPEG 音频解码库
* ffmpeg: 久负盛名的开源视频编解码程序

其中，Mplayer在配置时会自动下载需要的ffmpeg源码，因此不需要提前准备ffmpeg

### 关于OSS与ALSA
OSS在绝大多数的设备中已经弃用，即使需要使用`/dev/dsp`设备文件进行操作，也可以直接在配置内核时选择使用ALSA而不是OSS，因为ALSA会提供一个`/dev/dsp`设备文件以支持仅能使用OSS的旧软件。

### 关于源码的交叉编译与部署
从源码安装程序大部分需要经过以下流程：
1. 运行源码提供的配置脚本，对Makefile进行配置。大部分的软件源码会将这个脚本命名为`configure`，脚本可以用于指定编译器、库文件链接方式、目标安装位置、启用/禁用功能等多种用途，在配置脚本运行结束后，会生成可用的Makefile。
2. 使用`make`命令调用Makefile进行程序、库文件等的编译。
3. 使用`make install`命令调用Makefile将程序运行时所需要的二进制文件、库文件、头文件等复制到目标位置，并进行一些其他操作如stripe、写入环境变量等。

但是整个程序编译部署能否成功极度依赖于配置脚本的正确与否，而这个脚本往往内容复杂，很难即使发现错误并进行纠正，尤其是在交叉编译的情况下，部分软件(如MPlayer)的配置脚本只考虑了编译器的交叉编译，而对于stripe和ld等命令完全没有更换成交叉编译的版本，从而无法完成安装。实际上，在下面每一个软件的移植中，都遇到了配置脚本带来的挑战。  
不过对于大多数软件，`make install`步骤只是用于整理压缩操作，因此如果在这一步失败，可以直接使用编译后的目录中的二进制文件运行，一般可以正常运行。

### 关于帧缓冲设备的兼容
之前发现，实验使用的开发板并不能很好地兼容运行时的分辨率修改问题，而MPlayer似乎会针对视频的完整分辨率尝试修改Frame Buffer的分辨率，由于之前的Frame Buffer问题，可能会导致分辨率实际上没有发生变化，但是此时再按照修改后的分辨率进行输出，就会发生错误，具体现象和暂时的解决方案在下文详细叙述。

## 实验流程
### 1. 准备工作
#### 1.1 重新配置编译内核
使用`make menuconfig ARCH=arm`对内核进行自定义，需要保证如下条件满足：  
1. `Sound card support -> Advanced Linux Sound Architecture`处于启用状态，这样系统运行的时候就可以通过调用ALSA API或者OSS来播放声音。
2. `USB sound devices -> USB Audio/MIDI driver`处于启用状态，这样系统可以使用USB声卡进行播放。

配置完成后重新编译内核。

至此，所有准备工作完成，使用新内核和根文件系统启动。

### 2. 移植zlib
1. 使用`apt-src`命令拉取源码：
```
$ apt-src install zlib
```
2. 进入源码文件夹，进行配置：
```
$ CC=arm-linux-gnueabihf-gcc ./configure --prefix=/home/minaduki/Desktop/Beaglebone_Proj/mplayer/install/zlib
```
> 其中CC用于指定当前环境下的编译器，`--prefix`字段用于配置`make install`安装的路径。  
> 如果不配置`--prefix`字段，则默认会安装到`/usr/shared`目录下，这样就会造成系统原有的程序不能工作。
3. 使用GNU/make编译并安装程序：
```
$ make
$ make install
```
> 值得一提的是，虽然我一开始在上面指定的路径中是zlib，但有的时候安装的路径会和预设的不一样，推测应该是配置脚本中存在一些bug的缘故。

查看安装路径，可以看到三个目录，分别存放头文件和库文件，以及一些share文件：
```
total 0
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 .
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 ..
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 include
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 lib
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 share
```
至此，zlib准备就绪。

### 3. 移植libmad
1. 使用`apt-src`命令拉取源码：
```
$ apt-src install libmad
```
2. 进入源码文件夹，进行配置：
```
$ ./configure --enable-fpm=arm --host=arm-linux-gnueabihf --enable-speed --prefix=/home/minaduki/Desktop/Beaglebone_Proj/mplayer/install/libmad CC=arm-linux-gnueabihf-gcc
```
> 其中CC用于指定当前环境下的编译器，`--prefix`字段用于配置`make install`安装的路径，`--host`字段用于指出交叉编译工具链的前缀，`--enable-fpm=arm`则用于启用硬件浮点运算并指定硬件浮点运算单元的平台。  
3. 使用GNU/make编译并安装程序：
> 在开始编译前，应该先打开Makefile文件，寻找所有的`-fforce-mem`字段并删除，在新版本的arm-linux-gnueabihf-gcc中，这个字段已经不再受支持，删去它不会影响编译效果。
```
$ make
$ make install
```

查看安装路径，可以看到两个目录，分别存放头文件和库文件：
```
total 0
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 .
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 ..
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 include
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 lib
```
至此，libmad准备就绪。

### 4. 移植MPlayer
1. 使用`apt-src`命令拉取源码，或者直接前往[官方网站](http://www.mplayerhq.hu/design7/news.html)下载：
```
$ apt-src install mplayer
```
2. 进入源码文件夹，进行配置：
```
$ ./configure --enable-fpm=arm --host=arm-linux-gnueabihf --enable-speed --prefix=/home/minaduki/Desktop/Beaglebone_Proj/mplayer/install/libmad CC=arm-linux-gnueabihf-gcc
```
> 其中CC用于指定当前环境下的编译器，`--prefix`字段用于配置`make install`安装的路径，`--host`字段用于指出交叉编译工具链的前缀，`--enable-fpm=arm`则用于启用硬件浮点运算并指定硬件浮点运算单元的平台。  
3. 使用GNU/make编译并安装程序：
> 在开始编译前，应该先打开Makefile文件，寻找所有的`-fforce-mem`字段并删除，在新版本的arm-linux-gnueabihf-gcc中，这个字段已经不再受支持，删去它不会影响编译效果。
```
$ make
$ make install
```

查看安装路径，可以看到两个目录，分别存放头文件和库文件：
```
total 0
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 .
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 ..
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 include
drwxrwxrwx 1 minaduki minaduki 512 Jan 12 22:07 lib
```
至此，libmad准备就绪。

### 4. 运行效果
#### 4.1 编译程序
使用`make`编译程序，然后使用`make copy`复制到根文件系统，准备测试。

#### 4.2 安装模块与创建设备文件
文件中已经准备了led.sh用于安装模块和创建，但首次使用还是手动安装，以进行直观感受：
```
/mnt # insmod led.ko
[   61.160530] led: loading out-of-tree module taints kernel.
[   61.166134] led: module license 'MIT' taints kernel.
[   61.171141] Disabling lock debugging due to kernel taint
[   61.177251] Device registered with MAJOR = 245
[   61.181816] do_init_module: 'led'->init suspiciously returned 245, it should 
follow 0/-E convention
[   61.181816] do_init_module: loading module anyway...
[   61.195911] CPU: 0 PID: 138 Comm: insmod Tainted: P           O    4.4.155+ #
11
[   61.203250] Hardware name: Generic AM33XX (Flattened Device Tree)
[   61.209409] [<c001b1cc>] (unwind_backtrace) from [<c00158d4>] (show_stack+0x2
0/0x24)
[   61.217205] [<c00158d4>] (show_stack) from [<c052809c>] (dump_stack+0x8c/0xa0
)
[   61.224474] [<c052809c>] (dump_stack) from [<c00d658c>] (do_init_module+0xa0/
0x1e8)
[   61.232169] [<c00d658c>] (do_init_module) from [<c00d892c>] (load_module+0x21
90/0x2594)
[   61.240212] [<c00d892c>] (load_module) from [<c00d8e70>] (SyS_init_module+0x1
40/0x1f4)
[   61.248174] [<c00d8e70>] (SyS_init_module) from [<c0010f20>] (ret_fast_syscal
l+0x0/0x50)
```
从内核调试信息输出可得，分配到的主设备号为245，根据此设备号，使用`mknod`命令创建一个设备`led`：
```
/ # mknod /dev/led c 245 0                                                      
/ # ls -al /dev/led                                                             
crw-r--r--    1 0        0         245,   0 Jan  1 01:01 /dev/led  
```
成功创建了一个主设备号为245，次设备号为0的块设备。

#### 4.3 调用驱动
1. 首先，使用`echo`命令访问设备文件，并输入一些数值进行测试：
```
/ # echo -n 7 > /dev/led                                                        
[  168.642410] Turning LED 0 on                                                 
[  168.645427] Turning LED 1 on                                                 
[  168.648345] Turning LED 2 on                                                 
[  168.651235] Write finished                                                   
[  168.654059] Releasing    

/ # echo -n 0 > /dev/led                                                        
[  193.203207] Turning LED 0 off                                                
[  193.206309] Turning LED 1 off                                                
[  193.209309] Turning LED 2 off                                                
[  193.212304] Write finished                                                   
[  193.215116] Releasing   

/ # echo -n 9 > /dev/led                                                     
[  274.992720] Turning LED 0 on                                                 
[  274.995638] Turning LED 1 off                                                
[  274.998671] Turning LED 2 off                                                
[  275.001672] Write finished                                                   
[  275.004491] Releasing    
```
可以看见，设备驱动正确解析了输入的数字，并点亮了对应的LED，实际LED的点亮情况与内核输出一致。  
对于输入9的情况，由于9转换为二进制是1001，而驱动只会处理后三位，因此输入9与输入1等价。
> 关于`echo -n`:  
> `-n`选项用于表示“不输出换行符”，如果不加上这个选项的话，输出会变成这样的：
```
/ # echo 7 > /dev/led                                                           
[  206.883079] Turning LED 0 on                                                 
[  206.886118] Turning LED 1 on                                                 
[  206.889038] Turning LED 2 on                                                 
[  206.891927] Write finished                                                   
[  206.894813] Turning LED 0 off                                                
[  206.897839] Turning LED 1 on                                                 
[  206.900757] Turning LED 2 off                                                
[  206.903734] Write finished                                                   
[  206.907139] Releasing           
```
> 这是由于换行符对应的ASCII码为0x0A，即二进制1010，与输入2(010)等价。

1. 使用提供的用户程序`lcdctrl`控制LED状态，可以在命令行指定LED状态：
```
/mnt # ./ledctrl 1 0 1                                                          
Writing 5 to device[  244.743726] Turning LED 0 on                              
                                                                                
[  244.748612] Turning LED 1 off                                                
[  244.751595] Turning LED 2 on                                                 
[  244.754518] Write finished                                                   
[  244.757741] Releasing     
```
3. 也可以直接打开程序，通过输入不同的值来切换LED状态：
```
/mnt # ./ledctrl                                                                
Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be 
considered as exiting                                                           
Please input:1                                                                  
[  315.227594] Turning LED 0 on                                                 
[  315.230577] Turning LED 1 off                                                
[  315.233574] Turning LED 2 off                                                
[  315.236566] Write finished                                                   
Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be 
considered as exiting                                                           
Please input:4                                                                  
[  317.243592] Turning LED 0 off                                                
[  317.246697] Turning LED 1 off                                                
[  317.249692] Turning LED 2 on                                                 
[  317.252598] Write finished                                                   
Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be 
considered as exiting                                                           
Please input:3                                                                  
[  319.611692] Turning LED 0 on                                                 
[  319.614722] Turning LED 1 on                                                 
[  319.617634] Turning LED 2 off                                                
[  319.620629] Write finished                                                   
Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be 
considered as exiting                                                           
Please input:7                                                                  
[  321.499534] Turning LED 0 on                                                 
[  321.502567] Turning LED 1 on                                                 
[  321.505473] Turning LED 2 on                                                 
[  321.508379] Write finished                                                   
Please input 0 to 7 to change status of 3 leds, an input of 8 or larger will be 
considered as exiting                                                           
Please input:8                                                                  
[  322.780032] Releasing   
```

#### 4.4 卸载设备
使用`rmmod`命令卸载设备，释放设备号：
```
/mnt # rmmod led                                                                
[  340.321003] LED module reset and removed.      
```
LED灯全部关闭，同时设备号245也被释放。