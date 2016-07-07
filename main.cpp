#include <stdio.h>
#include <graphics.h>


int ini(void);
int game(void);

int ini(void)
{

    // 初始化画面大小
	initgraph(809,500);
    // random初始化
	randomize();
	setbkmode(TRANSPARENT);
    // 获得窗口句柄
 	HWND hWnd = getHWnd();
    // 使用 API 函数修改窗口名称
	SetWindowText(hWnd, TEXT("Flappy 2048"));

    // 定义图片变量，加载loading图片
	PIMAGE loading=newimage();
	getimage(loading,"pic\\loading.png");
    // 显示图片
	putimage(0,0,loading);

	// 设置字体颜色，字体，对齐方式，坐标
    setcolor(BLACK);
	setfont(0,0,"微软雅黑");
    settextjustify(CENTER_TEXT, TOP_TEXT);
    xyprintf(404,470,"Copyright Flappy 2048 Group");
    // 图片显示时间
	delay_ms(1500);
    // 清空loading图片
	delimage(loading);
}

int game(void)
{
    // 定义变量时间，方块高度，柱子位置，柱子多高
    int time = 0;
    int birdheight = 250;
    int a = 0, b = 0, c = 0, point = 0;
    int speed = 100;
    float v = 0.0;
    // 定义文件指针，存储最高分数
    FILE *fp;
    int bestpoint;
    int x,y;
    // 定义柱子结构体
    struct post {
        int x;
        int h;
    }post[3];

    // 定义图片变量，加载图片
    PIMAGE background = newimage();
    PIMAGE bird = newimage();
    PIMAGE post_u = newimage();
    PIMAGE shadow = newimage();
    PIMAGE backgroundshadow = newimage();

    getimage(background,"pic\\background.png");
    getimage(bird,"pic\\bird.png");
    getimage(post_u,"pic\\post.png");
    getimage(shadow,"pic\\shadow.png");
    getimage(backgroundshadow,"pic\\backgroundshadow.png");

    while(1)
    {
        // 初始化操作
        time = 0;
        birdheight = 200;
        point = 0;
        a = 0; b = 0; c = 0;
        v = 0;

        // 柱子的初始位置
        post[0].x = 500;
        post[1].x = 865;
        post[2].x = 1231;
        post[0].h = 14.5;


        fp=fopen("best.txt","r");
        fscanf(fp,"%d",&bestpoint);
        fclose(fp);
        while(1)
        {

            time += 1;

            // 监听鼠标键盘操作，改变方块速度
            if((time-b)>1&&(keystate(VK_LBUTTON)||keystate(VK_SPACE)))
            {
                v=-180;
                b=time;
            }
            // 计算方块的位置，当方块落到下边缘时向上弹起
            if(birdheight > 490 && v > 0 )
                v = -0.8*v;
            v+=9.8;
            birdheight+=((v*1.9)/speed);

            // 柱子的移动，当柱子移出左侧时，重置到右侧，接着另外两个柱子移动
			 for(c=0;c<3;c++)
			 {
 				post[c].x-=2;
 				if(post[c].x<=-107)
 					post[c].x=999;
				if(post[c].x==500 || post[c].x==501)
				{
					post[c].h=random(3)*122-230;
				}
 			}

            // 计算分数，当柱子移动到方块位置时分数加1，同时记录最高分数
			for(c=0;c<3;c++)
			{
				if(post[c].x==118 || post[c].x==119)
					point++;
			}

            if(bestpoint<point)
                bestpoint = point;


			// 显示图像，按先后顺序叠加图像，同时达到遮挡部分图像的效果

			// 显示背景
			putimage(0,0,background);

            // 显示柱子
			for(c=0;c<3;c++)
			{
				putimage_withalpha(NULL,post_u,post[c].x,post[c].h);
				putimage_withalpha(NULL,post_u,post[c].x,(post[c].h+487));
			}

            putimage_withalpha(NULL,backgroundshadow,0,0);

            // 方块颜色，分数越高，变换颜色

            if(point >= 0 && point < 2)
            {
                getimage(bird,"pic\\bird2.png");
                speed = 100;
            }
            if(point >= 2 && point < 4)
            {
                getimage(bird,"pic\\bird4.png");
                speed = 102;
            }
            if(point >= 4 && point < 8)
            {
                getimage(bird,"pic\\bird8.png");
                speed = 104;
            }
            if(point >= 8 && point < 16)
            {
                getimage(bird,"pic\\bird16.png");
                speed = 106;
            }
            if(point >= 16 && point < 32)
            {
                getimage(bird,"pic\\bird32.png");
                speed = 108;
            }
            if(point >= 32 && point < 64)
            {
                getimage(bird,"pic\\bird64.png");
                speed = 110;
            }
            if(point >= 64 && point < 128)
            {
                getimage(bird,"pic\\bird128.png");
                speed = 112;
            }
            if(point >= 128 && point < 256)
            {
                getimage(bird,"pic\\bird256.png");
                speed = 114;
            }
            if(point >= 256 && point < 512)
            {
                getimage(bird,"pic\\bird512.png");
                speed = 116;
            }
            if(point >= 512 && point < 1024)
            {
                getimage(bird,"pic\\bird1024.png");
                speed = 118;
            }
            if(point >= 1024 && point < 2048)
            {
                getimage(bird,"pic\\bird2048.png");
                speed = 120;
            }

            // 显示方块
            putimage_withalpha(NULL,bird,14,birdheight);



            // 碰撞检测

            if(post[0].x>=14&&post[0].x<=121&&(post[0].h>(birdheight-230)||(post[0].h+490)<birdheight+107))
 				point = 0;
		 	if(post[1].x>=14&&post[1].x<=121&&(post[1].h>(birdheight-230)||(post[1].h+490)<birdheight+107))
 				point = 0;
		 	if(post[2].x>=14&&post[2].x<=121&&(post[2].h>(birdheight-230)||(post[2].h+490)<birdheight+107))
 				point = 0;

			if(birdheight < -50 || birdheight > 393)
                point = 0;


            putimage(500,0,shadow);


            // 显示分数

			setcolor(EGERGB(119,110,101));
			setfont(60,0,"Arial Black"); // 第一个参数为高度。第二个参数为宽度，0为默认比例
			settextjustify(CENTER_TEXT, TOP_TEXT);
			xyprintf(654,40,"SCORE");
			xyprintf(654,100,"%d",point);
			xyprintf(654,190,"BEST");
			xyprintf(654,250,"%d",bestpoint);
			xyprintf(654,380,"RESET");
            xyprintf(66,birdheight+26,"%d",point);


            // 监听鼠标操作，如果单击reset区域，分数重置为零
            if(keystate(VK_LBUTTON))
            {
                mousepos(&x,&y);
                if(x>575&&x<740&&y>380&&y<430)
                    point = bestpoint = 0;
            }
            // 存储最佳成绩
            fp=fopen("best.txt","w");
            fprintf(fp,"%d",bestpoint);
            fclose(fp);
            delay_fps(speed);
        }
    }
}

int WinMain(void)
{
	ini();
	game();

	return 0;
}
