#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/input.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

int *p;
volatile int xx, yy;
volatile int flagS = 1, flag0 = 0;
volatile int cnt;
volatile int shibaishu = 0;

int show_bmp(char *PATH, int lcd_fd, int sx, int sy, int w, int h){

    flagS = 0;
    sy = -sy;
    p = (int *)mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (p == MAP_FAILED){// 映射失败
        printf("mmap error!\n");
        return -1;
    }
    int bmp_fd = open(PATH, O_RDONLY);
    if(p == MAP_FAILED || bmp_fd == -1){
        printf("show Failed\n");
    }

    // 读取图片数据
    char bmp_buff[w*h*3];
    lseek(bmp_fd, 54, SEEK_SET);
    read(bmp_fd, bmp_buff, w*h*3);


    int x, y;
    int k, offset = 0;
    if((w*3)%4==0)
	{
		offset=0;
	}
	else
	{		
		offset=4-(w*3)%4;
	}
    for(y = 0; y < h; y++){
        k = y*w*3+y*offset;
        for(x = 0; x < w; x++){
            *(p + 800*(h - 1 - (y + sy)) + (x + sx)) = bmp_buff[k] | bmp_buff[k + 1]<<8 | bmp_buff[k + 2]<<16;
            k+=3;
        }
    }

    munmap(p, 800*480*4);
    close(bmp_fd);
    flagS = 1;
    return 0;
}

void show_num(int num, int lcd_fd){
    int shi, ge;
    shi = num / 10;
    ge = num % 10;
    
    //计数板
    switch(shi){
        case 0:
            show_bmp("./0.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 1:
            show_bmp("./1.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 2:
            show_bmp("./2.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 3:
            show_bmp("./3.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 4:
            show_bmp("./4.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 5:
            show_bmp("./5.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 6:
            show_bmp("./6.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 7:
            show_bmp("./7.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 8:
            show_bmp("./8.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;

        case 9:
            show_bmp("./9.bmp", lcd_fd, 799 - 301, 479 - 150, 150, 150);
        break;
    }
    switch(ge){
        case 0:
            show_bmp("./0.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 1:
            show_bmp("./1.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 2:
            show_bmp("./2.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 3:
            show_bmp("./3.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 4:
            show_bmp("./4.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 5:
            show_bmp("./5.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 6:
            show_bmp("./6.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 7:
            show_bmp("./7.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 8:
            show_bmp("./8.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;

        case 9:
            show_bmp("./9.bmp", lcd_fd, 799 - 150, 479 - 150, 150, 150);
        break;
    }
    
}

void *touchFun(void *arg){
    // 创建触摸相关变量
    int ts_fd;
    struct input_event ts_buf;
    ts_fd = open("/dev/input/event0",O_RDONLY);
    if(ts_fd == -1){// 打开失败
        printf("open ts failed!\n");
    }
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {// 打开失败
        printf("open lcd error!\n");
    }
    int x, y;
    while(1){
        read(ts_fd, &ts_buf, sizeof(ts_buf));
        if(ts_buf.type == EV_ABS && ts_buf.code == ABS_X)//判断是否发生X轴绝对位移事件
        {
            x = ts_buf.value;
        }
        if(ts_buf.type == EV_ABS && ts_buf.code == ABS_Y)//判断是否发生Y轴绝对位移事件
        {
            y = ts_buf.value;
        }
        if(ts_buf.type == EV_KEY && ts_buf.code == BTN_TOUCH && ts_buf.value == 0)//松手检测
        {
            sleep(0.5);
            if(x*800/1024 > xx*160 && x*800/1024<(xx+1)*160 && y*480/600 >yy*160 && y*480/600 <(yy +1)*160)
            {
                printf("good\n");
                if(flagS!=1){
                    usleep(10000);
                }
                show_bmp("./xiangmudishuyun.bmp", lcd_fd, xx*160, yy*160, 160, 160);//打击过后
                if(flag0){
                    cnt++;
                    flag0 = 0;
                }
            }
            else 
            {
                printf("failed\n");
                shibaishu++;
                if(shibaishu>3){
                    shibaishu = 0;
                    flag0 = 1;
                }
            }
            if(flagS!=1){
                usleep(10000);
            }
            show_num(cnt, lcd_fd);
        } 
    }
}



int main(void){

    // 打开 lcd 显示文件
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {// 打开失败
        printf("open lcd error!\n");
        return -1;  
    }
    
    srand(time(NULL));

    pthread_t tid;
    pthread_create(&tid, NULL, touchFun, NULL);

    int x, y;
    while(1){
        xx = rand() % 3;
        yy = rand() % 3;

        if(flagS!=1)
        {
            usleep(10000);
        }
        show_bmp("./xiangmudishu.bmp", lcd_fd, xx*160, yy*160, 160, 160);//打击前
        sleep(1);
        if(flagS!=1)
        {
            usleep(10000);
        }
        show_bmp("./beijing.bmp", lcd_fd, 0, 0, 800, 480);
        flag0 = 1;
        if(cnt >= 20)
        {
            if(flagS!=1){
                usleep(10000);
            }
            show_bmp("./shengli.bmp", lcd_fd, 0, 0, 800, 480);
            return -1;
        }
        if(shibaishu == 3)
        {
            if(flagS!=1){
                usleep(10000);
            }
            show_bmp("./shibai.bmp", lcd_fd, 0, 0, 800, 480);
            return -1;
        }
        show_num(cnt, lcd_fd);
    }

    // 取消映射、关闭fb
    close(lcd_fd); 
    return 0;
}
