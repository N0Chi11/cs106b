#include "random.h"  // 包含随机数生成相关的头文件
#include "gwindow.h" // 包含图形窗口相关的头文件
#include "gobjects.h" // 包含图形对象相关的头文件
#include "gevent.h" // 包含图形事件相关的头文件
#include <conio.h>  // 包含控制台输入输出相关的头文件
#include <stdio.h>  // 包含标准输入输出相关的头文件
#include <cmath>    // 包含数学函数相关的头文件
#include <time.h>   // 包含时间相关的头文件

// 自定义的颜色引用类，用于表示RGB颜色
class COLORREF{
    int R,G,B;  // 定义三个私有成员变量，分别表示红、绿、蓝三个颜色通道的值
  public:
    // 构造函数，用于初始化红、绿、蓝三个颜色通道的值
    COLORREF(int r, int g, int b): R(r),G(g),B(b){}
    // 获取红色通道的值
    int getR(){ return R; }
    // 获取绿色通道的值
    int getG(){ return G; }
    // 获取蓝色通道的值
    int getB(){ return B; }
};

// 定义图形窗口的宽度常量
const double kWindowWidth = 1200;
// 定义图形窗口的高度常量
const double kWindowHeight = 800;
//const int kTreeOrder = 8;

// 左右枝干和父枝干偏离的角度，初始化为PI/6
static double offsetAngle = PI/6; 
// 子枝干比父枝干变短的倍数，初始化为0.65
static double shortenRate = 0.65;  
//static int isShowAnimation = 1; // 是否显示树生成的过程动画

// 声明一个函数，用于将HSV颜色空间转换为RGB颜色空间
COLORREF HSVtoRGB(double H, double S,double V);
// 声明一个函数，用于绘制树
void drawTree(GWindow& window, double x, double y, double length);

// 声明一个递归函数，用于生成和绘制树的枝干
void drawTreeRec(GWindow& window, double x_start,double y_start,double length,
                 double angle, double thickness,int generation);

// 主函数，程序的入口点
int main() 
{
    // 创建一个图形窗口对象，指定窗口的宽度和高度
    GWindow window(kWindowWidth, kWindowHeight);
    // 设置窗口的背景颜色为白色
    window.setBackground("White");
    // 清空窗口的画布
    window.clearCanvas();
    // 设置窗口关闭时程序退出
    window.setExitOnClose(true);
    // 设置窗口的标题
    window.setTitle("Our Tree!");
    // 调用drawTree函数，开始绘制树，指定树的起始位置和初始枝干长度
    drawTree(window, kWindowWidth/2, kWindowHeight, 0.45*kWindowHeight*shortenRate);
    // 主函数正常返回
    return 0;
}

// 绘制树的函数，调用递归函数drawTreeRec开始绘制
void drawTree(GWindow& window, double x, double y, double length)
{
    // 调用递归函数drawTreeRec，指定起始位置、枝干长度、角度、线条宽度和代数
    drawTreeRec(window, x, y, length, PI/2, 15*shortenRate, 1);
}

// 枝干生成和绘制递归函数
// 输入参数：枝干起始x y坐标，枝干长度，枝干角度，枝干绘图线条宽度，第几代
void drawTreeRec(GWindow& window, double x_start,double y_start,double length,
                 double angle, double thickness,int generation)
{
    // 利用三角函数求出当前枝干的终点x,y坐标
    double x_end = x_start + length * cos(angle);
    double y_end = y_start - length * sin(angle);
    // 生成线条枝干对象，指定起始点和终点坐标
    GLine line(x_start, y_start, x_end, y_end);
    // 设置线条枝干的宽度
    line.setLineWidth(thickness);
    // 设置枝干为灰褐色，主树干最黑，子枝干逐渐变亮
    COLORREF  color = HSVtoRGB(250,80,0.4+generation*5);
    //COLORREF  color = HSVtoRGB(15,0.75,0.4+generation*5);
    // 设置线条的颜色，使用RGB值
    line.setColor(color.getR(), color.getG(), color.getB());
    // 画出当前枝干（画线）
    window.draw(&line);
    // 求出子枝干的代数
    int childGeneration = generation + 1;   //randomReal(1,2);
    // 生成左、右、中间三个子枝干的长度，逐渐变短，并有一定随机性
    double childLength = shortenRate * length;
    double leftChildLength = childLength * randomReal(0.9,1.1);
    double rightChildLength = childLength * randomReal(0.9,1.1);
    double centerChildLength = childLength * randomReal(0.8,1.1);

    // 当子枝干长度大于2，并且代数小于等于10，递归调用产生子枝干
    if (childLength >= 2 && childGeneration <= 9) 
    {       
        // 生成子枝干的粗细，逐渐变细
        double childThickness = thickness * 0.8;
        // 枝干绘图最细的线宽为2
        if (childThickness < 2) 
            childThickness = 2;

        // 一定概率产生左、右、中子枝干
        if(randomReal(0,1) < 0.95)
            // 递归调用drawTreeRec函数，绘制左子枝干
            drawTreeRec(window, x_end, y_end, leftChildLength, angle + offsetAngle * randomReal(0.5,1),
                        childThickness, childGeneration);
        if(randomReal(0,1) < 0.95)
            // 递归调用drawTreeRec函数，绘制右子枝干
            drawTreeRec(window, x_end, y_end, rightChildLength, angle - offsetAngle * randomReal(0.5,1),
                        childThickness, childGeneration);
        if(randomReal(0,1) < 0.85)
            // 递归调用drawTreeRec函数，绘制中间子枝干
            drawTreeRec(window, x_end, y_end, centerChildLength, angle + offsetAngle / 5 * randomReal(-1,1),
                        childThickness, childGeneration);
    }
    else // 最末端绘制樱花，画一个粉色填充圆
    {
        // 设置窗口的绘图颜色为粉色
        window.setColor("Pink");
        // 如果子枝干长度小于等于4
        if (childLength <= 4) 
            // 绘制一个半径为1的小圆
            window.fillOval(x_end - 1, y_end - 1, 2, 2);
        else  // 画一个圆，半径为子枝干长度的一半
            window.fillOval(x_end - childLength / 4, y_end - childLength / 4,
                            childLength / 2, childLength / 2);
    }
/*
    if (isShowAnimation) // 如果为1，绘制樱花树生成的过程动画
    {
        FlushBatchDraw(); // 批量绘制
        Sleep(1); // 暂停
    }*/
}

// 将HSV颜色空间转换为RGB颜色空间的函数
COLORREF HSVtoRGB(double H, double S,double V){
    // 检查输入的HSV值是否在有效范围内
    if(H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0){
        // 输出错误信息
        std::cout<<"The given HSV values are not in valid range"<<std::endl;
        // 返回黑色
        return COLORREF(0,0,0);
    }
    // 将饱和度和亮度转换为小数形式
    double s = S / 100;
    double v = V / 100;
    // 计算色度
    double C = s * v;
    // 计算辅助值
    double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    // 计算亮度偏移量
    double m = v - C;
    double r,g,b;
    // 根据色相值的范围计算RGB值
    if(H >= 0 && H < 60){
        r = C; g = X; b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X; g = C; b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0; g = C; b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0; g = X; b = C;
    }
    else if(H >= 240 && H < 300){
        r = X; g = 0; b = C;
    }
    else{
        r = C; g = 0; b = X;
    }

    // 将RGB值转换为0-255的范围，并返回COLORREF对象
    return COLORREF((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

/*
// 每帧更新函数
void update()  
{
    MOUSEMSG m;
    // 检查是否有鼠标事件
    if (MouseHit())
    {
        // 获取鼠标消息
        m = GetMouseMsg();
        // 当鼠标移动时，设定递归函数的参数
        if(m.uMsg == WM_MOUSEMOVE) 
        {
            // 鼠标从左到右，左右子枝干偏离父枝干的角度逐渐变大
            offsetAngle = mapValue(m.x,0,WIDTH,PI/10,PI/4);
            // 鼠标从上到下，子枝干比父枝干的长度缩短的更快
            shortenRate = mapValue(m.y,0,HEIGHT,0.7,0.3);
        }
        // 当鼠标左键点击时，以当前参数开始绘制一棵新数
        if (m.uMsg == WM_LBUTTONDOWN) 
        {
            cleardevice(); // 清屏
            brunch(WIDTH/2,HEIGHT,0.45*HEIGHT*shortenRate,-PI/2,15*shortenRate,1); // 递归调用
            FlushBatchDraw(); // 批量绘制
        }
        // 当鼠标右键点击时，切换是否显示过程动画
        if (m.uMsg == WM_RBUTTONDOWN) 
        {
            if (isShowAnimation==1)
                isShowAnimation = 0;
            else if (isShowAnimation==0)
                isShowAnimation = 1;
        }
    }
}
*/
